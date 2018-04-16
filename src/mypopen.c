/*
 * =====================================================================================
 *
 *       Filename:  mypopen.c
 *
 *    Description:  Mypopen library
 *
 *        Version:  1.0.0
 *        Created:  04/10/2018 09:40:05 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ovidiu - Dan Bogat [ic17b501], ic17b501@technikum-wien.at
 * =====================================================================================
 */
#include <stdio.h>
#include "mypopen.h"

FILE* popen(const char* cmd, const char* mode)
{
  FILE *f;
  f=fopen("/tmp/1","r");
  if(f == NULL)
  {
    
  }
  cmd=cmd;
  mode=mode;
  return f;
}

int pclose(FILE* stream)
{
  stream=stream;
  return 0;
}