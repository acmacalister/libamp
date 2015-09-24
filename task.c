////////////////////////////////////////////////////////////////////////////////
//
//  task.c
//
//  Created by Austin Cherry on 9/17/15.
//  Copyright (c) 2015 Vluxe. All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include "string.h"
#include "list.h"
#include "task.h"

#define SINGLE_QUOTE  '\''
#define DOUBLE_QUOTE  '\"'

////////////////////////////////////////////////////////////////////////////////
const char **convert(List *l) {
  const char **newArray = (const char**)malloc((l->count+1)*sizeof(const char *));
  newArray[l->count] = NULL;
  int i = 0;
  LIST_ITERATE(l, cur) {
    newArray[i] = strdup((const char *)cur->value);
    i++;
  }
  return newArray;
}
////////////////////////////////////////////////////////////////////////////////
const char **getArgs(const char *command) {
  List *l = newList();
  char *buffer = strdup(command);
  char *param = buffer;
  while(param && *param) {
    char *next = (char *)nextws(param);
    if((*param == SINGLE_QUOTE) || (*param == DOUBLE_QUOTE)) {
      char quoteChar = *param++;
      char *closingQuote = strchr(param, quoteChar);
      if(closingQuote) {
        next = closingQuote;
      }
    }

    if(next && *next) {
      *next++ = 0;
    }

    llpushBack(l, strdup(param));
    param = (char *)skipws(next);
  }
  free(buffer);
  const char **args = convert(l);
  freeList(l);
  return args;
}
////////////////////////////////////////////////////////////////////////////////
bool doesFileExist(const char *path) {
  if(path) {
    int status;
    struct stat st_buf;
    status = stat(path, &st_buf);

    if(status == 0) {
      return true;
    }
  }
  return false;
}
////////////////////////////////////////////////////////////////////////////////
const char *runTask(const char *command) {
  const char **a = getArgs(command);
  int pipefd[2];
  pipe(pipefd);
  char readBuffer[1024] = {0};
  pid_t pid = fork();
  if(pid == 0) {
    dup2(pipefd[0], STDIN_FILENO);
    close(pipefd[0]);
    dup2(pipefd[1], STDOUT_FILENO);
    dup2(pipefd[1], STDERR_FILENO);
    close(pipefd[1]);

    const char **args = getArgs(command);
    const char *name = args[0];

    if(doesFileExist(name)) {
      execv(name, (char *const *)args); // execv takes over. Should end contol flow.
    }

    const char *path = getenv("PATH");
    if(path) {
      int num;
      const char **array = strsplit(path, ":", &num);
      for(int i = 0; i < num; i++) {
        const char *fullPath = strformat("%s/%s", array[i], name);
        if(doesFileExist(fullPath)) {
          execv(fullPath, (char *const *)args); // execv takes over. Should end contol flow.
        }
        free((void *)fullPath);
      }
      free(array);
    }
    // some cool failure stuff.
  }
  int status = 0;
  waitpid(pid, &status, 0 );

  FILE *output = fdopen(pipefd[0], "r");

  char *collect = (char*)malloc(1);
  strcpy(collect,"");
  while(true) {
    long bytes = read(pipefd[0], readBuffer, 1024);
    if(bytes <= 0) {
      break;
    }
    const char *appended = strappend(collect, readBuffer);
    if(appended) {
      free(collect);
      collect = (char *)appended;
    }
    memset(readBuffer, 0, sizeof(readBuffer));

    if(bytes > 0 && bytes < 1024) {
      break;
    }
  }
  // we need some sort of failure handler. 
  return collect; 
}
////////////////////////////////////////////////////////////////////////////////
