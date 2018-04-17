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
#include <errno.h>
#include <stdio.h>
#include "mypopen.h"

FILE* popen(const char* cmd, const char* mode)
{
  cmd=cmd;
  
  /* mode Sentinels */
  if ( mode[1] != '\0' )
  {
    /* Wir haben mehr als nur einen char */
    errno = EINVAL;
    return NULL;
  }
  
  if ( *mode != 'r' && *mode != 'w' )
  {
    /* Wir akzeptieren nur 'r' oder 'w' fuer mode */
    errno = EINVAL;
    return NULL;
  }
  /* Das ist analog zum Original popen */
  /* Nur etwas besser */
  /* Alternativ kann man den rest ignorieren */
  /* ENDE mode Sentinels */
  
  
  return NULL;
}

int pclose(FILE* stream)
{
  stream=stream;
  return 0;
}