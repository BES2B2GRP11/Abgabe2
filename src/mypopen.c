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
/*  Der fork Prozess + pipe() */
/*                                  int pdesc[2]                                           */
/*  +----------+                      +                                                    */
/*  | pdesc[1] |                      |                                                    */
/*  +----------+                      |                                                    */
/*  |          |                      v                                                    */
/*  |          | <-----------------+pipe(pdesc)                                            */
/*  | pipe     |                      +                                                    */
/*  |          |                      |                                                    */
/*  |          |                      +----------------+ pdesc[0] lesen                    */
/*  |          |                      |                  pdesc[1] schreiben                */
/*  +----------+                      v                                                    */
/*  | pdesc[0] |                    fork()                                                 */
/*  +----------+                      +                                                    */
/*                                    |                                                    */
/*                                    |                                                    */
/*                                    |                                                    */
/*                      +-------------+-------------+                                      */
/*                      |                           |                                      */
/*                      |                           |                                      */
/*                      v                           v                                      */
/*                 vater mit                    kind mit                                   */
/*                 pdesc[0]                     pdesc[0] <- eigene Kopie                   */
/*                 pdesc[1]                     pdesc[1] <- eigene Kopie                   */
/* popen mode(r): */
/* Elternprozess liest von der pipe und kann pdesc[1] somit schlieszen. */
/* Kindprozess schreibt in die Pipe und kann pdesc[0] schlieszen */
/* */
/* popen mode(w) */
/* Elternprozess liest von der pipe und kann pdesc[0] somit schlieszen. */
/* Kindprozess schreibt in die Pipe und kann pdesc[1] schlieszen */
/* */
/* popen verwendet fdopen nach dem fork. */
/* fdopen kennt mehrere typen / modes, r,w,r+,w+ */
/* es machen nur r und w beim popen sinn */
/* Somit werden nur r oder w akzeptiert, wodurch die pipe nur halfduplex (nur in eine richtung moeglich) ist :) */
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include "mypopen.h"

FILE* popen(const char* cmd, const char* mode)
{
  cmd=cmd;
  pid_t pid;
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

  
  /*        Fork und pid      */
  /*         +---------+      */
  /*      +--+  fork() +-+    */
  /*      |  +---------+ |    */
  /*      |              |    */
  /* +----v---+     +----v--+ */
  /* | parent |     | child | */
  /* +--------+     +-------+ */
  /* |return  |     |wenn   | */
  /* | von    |     |fork() | */
  /* |fork()  |     |klappt | */
  /* |ist pid |     |kann   | */
  /* | vom    |     |pid    | */
  /* |child   |     |hier   | */
  /* |oder -1 |     |nur    | */
  /* |bei     |     |0      | */
  /* |Fehler  |     |sein   | */
  /* +--------+     +-------+ */
  /*                          */
  
  /* Es wird gleich im Switchgeforked - spart eine variable */
  /* Der Return-Wert vom fork() wird auch nur 1 mal in diesem Aufruf */
  /* von popen abgefragt */
  switch( pid=fork() )
  {
    case -1: 
      /* Fehler fall, kann dennoch eintretten -- sind noch im parent */
      /* Alles schlieszen was irgendwie offen ist */
      /* ERRNO wird hier auch schon automatisch von fork() als syscall richtig gesetzt */
      return NULL;
    case 0:
      /* Nur der Kindprozess kann den returnwert 0 haben */
      /* Child */
      break;
  }
  
  /* Vater */
  
  return NULL;
}

int pclose(FILE* stream)
{
  stream=stream;
  return 0;
}
