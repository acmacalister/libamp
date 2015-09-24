////////////////////////////////////////////////////////////////////////////////
//
//  string_test.c
//
//  Created by Austin Cherry on 9/17/15.
//  Copyright (c) 2015 Vluxe. All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#include "string.h"
#include <stdio.h>
#include <stdlib.h>

void stringTest(void) {
  bool b = strcontains("seafood", "foo");
  printf("%d\n", b);

  b = strcontains("seafood", "asdf");
  printf("%d\n", b);

  b = strhasprefix("seafood", "sea");
  printf("%d\n", b);

  b = strhasprefix("seafood", "asdf");
  printf("%d\n", b);

  b = strhassuffix("seafood", "food");
  printf("%d\n", b);

  b = strhassuffix("seafood", "asdf");
  printf("%d\n", b);


  const char *str = strreplace("oink oink oink", "k", "ky", 2);
  printf("%s\n", str);
  str = NULL;

  str = strreplace("oink oink oink", "oink", "moo", -1);
  printf("%s\n", str);
  str = NULL;


  const char *values[] = {"foo", "bar", "baz"};
  str = strjoin(values, 3, ", ");
  printf("%s\n", str);

  str = strrepeat(str, 3);
  printf("%s\n", str);

  str = strupper(str);
  printf("%s\n", str);

  str = strlower(str);
  printf("%s\n", str);
  str = NULL;

  str = strformat("Austin is %s and %d years of age.", "awesome", 24);
  printf("%s\n", str);
  str = NULL;

  str = strtitle("her royal highness");
  printf("%s\n", str);
  str = NULL;

  int count = 0;
  const char **array = strsplit("foo, bar, baz", ", ", &count);
  for(int i = 0; i < count; i++) {
    printf("%s\n", array[i]);
  }
}

int main(int argc, const char *argv[]) {
  stringTest();
  return 0;
}