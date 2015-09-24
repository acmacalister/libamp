////////////////////////////////////////////////////////////////////////////////
//
//  string.c
//
//  Created by Austin Cherry on 9/17/15.
//  Copyright (c) 2015 Vluxe. All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#include "string.h"
#include <stdlib.h>
#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>

////////////////////////////////////////////////////////////////////////////////
bool strcontains(const char *string, const char *substring) {
  const char *str = strstr(string, substring);
  if(str) {
    return true;
  }
  return false;
}
////////////////////////////////////////////////////////////////////////////////
bool strhasprefix(const char *string, const char *prefix) {
  int length = strlen(prefix);
  if(length > strlen(string)) {
    return false;
  }

  for(int i = 0; i < length; i++) {
    if(prefix[i] != string[i]) {
      return false;
    }
  }

  return true;
}
////////////////////////////////////////////////////////////////////////////////
bool strhassuffix(const char *string, const char *suffix) {
  int length = strlen(suffix);
  int strLength = strlen(string);

  if(length > strLength) {
    return false;
  }

  for(int i = length; i >= 0; i--) {
    if(suffix[i] != string[strLength]) {
      return false;
    }
    strLength--;
  }

  return true;
}
////////////////////////////////////////////////////////////////////////////////
const char *strjoin(const char *strings[], int stringsCount, const char *sep) {
  int length = strlen(sep);

  int size = length*stringsCount;
  for(int i = 0; i < stringsCount; i++) {
    size += strlen(strings[i]);
  }

  char *newString = (char *)malloc(size+1);
  for(int i = 0; i < stringsCount; i++) {
    strcat(newString, strings[i]);
    if(i < stringsCount-1) {
      strcat(newString, sep);
    }
  }

  return newString;
}
////////////////////////////////////////////////////////////////////////////////
const char *strrepeat(const char *string, int n) {
  char *newString = (char *)malloc((strlen(string)*n)+1);
  for(int i = 0; i < n; i++) {
    strcat(newString, string);
  }

  return newString;
}
////////////////////////////////////////////////////////////////////////////////
const char *strreplace(const char *string, const char *toReplace, const char *replacing, int n) {
  int positions[256]; // hardset buf size. This COULD be a problem if you had to replace over 256 
  bool untilEnd = false; // sub strings in a string.
  if(n <= 0) {
    untilEnd = true;
  }
  int count = 0;
  char *tmp = (char *)string;
  while((tmp = strstr(tmp, toReplace))) {
    positions[count] = (tmp - string);
    tmp++;
    count++;
    if(count == n && !untilEnd) {
      break;
    }
  }

  int replacingLen = strlen(replacing);
  int toRepLen = strlen(toReplace);
  int len = strlen(string);
  int length = len + count*(replacingLen-toRepLen);
  char *newString = (char *)malloc(length+1);

  int k = 0;
  int j = 0;
  for(int i = 0; i < len; i++) {
    if(i == positions[k]) {
      strcat(newString, replacing);
      i = i+toRepLen-1;
      j = j+replacingLen;
      k++;
    } else {
      newString[j] = string[i];
      j++;
    }
  }
  newString[length] = '\0';

  return newString;
}
////////////////////////////////////////////////////////////////////////////////
const char **strsplit(const char *string, const char *sep, int *num) {
  int count = 0;
  const char *tmp = string;
  while((tmp = strstr(tmp, sep))) {
    tmp++;
    count++;
  }

  *num = count;
  const char **newArray = (const char**)malloc((count+1)*sizeof(const char *));
  newArray[count] = NULL;
  char *str = strdup(string);
  char *token = strtok(str, sep);
  for(int i = 0; i < count; i++) {
    newArray[i] = token;
    token = strtok(NULL, sep);
  }

  free(str);
  return newArray;
}
////////////////////////////////////////////////////////////////////////////////
const char *strtitle(const char *string) {
  int length = strlen(string);
  char *newString = (char *)malloc(length+1);
  for(int i = 0; i < length; i++) {
    char c = string[i];
    if('a' <= c && c <= 'z' && (i == 0 || isspace(string[i-1]) > 0)) {
      c -= 'a' - 'A';
    }

    newString[i] = c;
  }

  return newString;
}
////////////////////////////////////////////////////////////////////////////////
const char *strlower(const char *string) {
  int length = strlen(string);
  char *newString = (char *)malloc(length+1);
  for(int i = 0; i < length; i++) {
    newString[i] = tolower(string[i]);
  }

  return newString;
}
////////////////////////////////////////////////////////////////////////////////
const char *strupper(const char *string) {
  int length = strlen(string);
  char *newString = (char *)malloc(length+1);
  for(int i = 0; i < length; i++) {
    newString[i] = toupper(string[i]);
  }

  return newString;
}
////////////////////////////////////////////////////////////////////////////////
const char *strformat(const char *string, ...) {
  va_list args;
  va_start(args, string);
  int size = vsnprintf(NULL, 0, string, args)+1;
  va_end(args);

  char *newString = (char *)malloc(size+1);

  va_start(args, string);
  vsnprintf(newString, size, string, args);
  va_end(args);

  return newString;
}
////////////////////////////////////////////////////////////////////////////////
const char *strappend(const char *string, const char *string2) {
  if(!string || !string2) {
    return NULL;
  }

  int length = strlen(string) + strlen(string2);
  char *newString = (char *)malloc((length+1)*sizeof(char));
  strcpy(newString, string);
  strcat(newString, string2);
  return newString;
}
////////////////////////////////////////////////////////////////////////////////
char *end(const char *string) {
  if (string && *string) {
    return( (char*)(string + strlen(string)-1));
  }
    
  return (char*)string;
}
////////////////////////////////////////////////////////////////////////////////
const char *skipws(const char *string) {
  if(string) { // should we copy string to be inline with other non destructive funcs?
    while(isspace(*string)) {
      string++;
    }
  }

  return (char *)string;
}
////////////////////////////////////////////////////////////////////////////////
const char *trimws(const char *string) {
  char *str = strdup(string);

  if(str) {
    while(isspace(*end(str))) {
      *end(str) = 0;
    }
  }

  return (char *)str;
}
////////////////////////////////////////////////////////////////////////////////
const char *nextws(const char *string) {
  if(string) {
    if(isspace(*string)) {
      string++;
    }
    while(*string && !isspace(*string)) {
      string++;
    }
  }

  return string;
}
////////////////////////////////////////////////////////////////////////////////
const char *reverse(const char *string) {
  char *str = strdup(string); // copy all the things!

  // some Bob Covey magic!
  int swapcount = (int)strlen(str)/2;
  
  char *front = str;
  char *back = end(str);
  while (swapcount--) {
    char ch = *front;
    *front++ = *back;
    *back-- = ch;
  }
  return str;
}
////////////////////////////////////////////////////////////////////////////////