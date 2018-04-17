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
#include <unistd.h>
#include <stdio.h>
#include "mypopen.h"

FILE* popen(const char* cmd, const char* mode)
{
  cmd=cmd;
  int pdesc[2]; /* Pipe deskriptoren */
  
  
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
  
  
  /* herstellen der pipe */
  if ( pipe(pdesc) < 0 )
  {
    /* pipe() returniert -1 bei einem Fehler */
    /* pipe() ist ein system-call und setzt errno bereits richtig */
    /* pdesc[0] ist ein integer, als Filedeskriptor zum Lesen aus der pipe */
    /* pdesc[1] ist ein integer, als Filedeskriptor zum Schreiben in die pipe */
    /*                +------------+               */
    /* pdesc[1]+------>    PIPE    +---->pdesc[0]  */
    /*                +------------+               */
    /* Die Pipe arbeitet "First-in-first-out" beim Lesen */
    return NULL;
  }
  /* ENDE herstellen der pipe */
  
  return NULL;
}

int pclose(FILE* stream)
{
  stream=stream;
  return 0;
}