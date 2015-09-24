////////////////////////////////////////////////////////////////////////////////
//
//  string.h
//
//  Created by Austin Cherry on 9/17/15.
//  Copyright (c) 2015 Vluxe. All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef __AMP__String__
#define __AMP__String__

#include <string.h>
#include <stdbool.h>

/**
 The websocket connected to its host.
 @param socket is the current socket object.
 */
bool strcontains(const char *string, const char *substring);

/**
 The websocket connected to its host.
 @param socket is the current socket object.
 */
bool strhasprefix(const char *string, const char *prefix);

/**
 The websocket connected to its host.
 @param socket is the current socket object.
 */
bool strhassuffix(const char *string, const char *suffix);

/**
 The websocket connected to its host.
 @param socket is the current socket object.
 */
const char *strjoin(const char *strings[], int stringsCount, const char *sep);

/**
 The websocket connected to its host.
 @param socket is the current socket object.
 */
const char *strrepeat(const char *string, int n);

/**
 The websocket connected to its host.
 @param socket is the current socket object.
 */
const char *strreplace(const char *string, const char *toReplace, const char *replacing, int n);

/**
 The websocket connected to its host.
 @param socket is the current socket object.
 */
const char **strsplit(const char *string, const char *sep, int *num);

/**
 The websocket connected to its host.
 @param socket is the current socket object.
 */
const char *strtitle(const char *string);

/**
 The websocket connected to its host.
 @param socket is the current socket object.
 */
const char *strlower(const char *string);

/**
 The websocket connected to its host.
 @param socket is the current socket object.
 */
const char *strupper(const char *string);

/**
 The websocket connected to its host.
 @param socket is the current socket object.
 */
const char *strformat(const char *string, ...);

/**
 The websocket connected to its host.
 @param socket is the current socket object.
 */
const char *strappend(const char *string, const char *string2);

/**
 Return a pointer to the first non-whitespace character in string.
 @param socket is the current socket object.
 */
const char *skipws(const char *string);

/**
 Trims any trailing whitespace from the string.
 @param socket is the current socket object.
 */
const char *trimws(const char *string);

/**
 Return a pointer to the next whitespace character in string.
 @param socket is the current socket object.
 */
const char *nextws(const char *string);


/**
 Reverse the characters of a string.
 @param socket is the current socket object.
 */
const char *reverse(const char *string);

#endif /* defined(__AMP__String__) */