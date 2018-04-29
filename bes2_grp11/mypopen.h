/*
 * =====================================================================================
 *
 *       Filename:  mypopen.h
 *
 *    Description:  Mypopen library header file
 *
 *        Version:  1.0.0
 *        Created:  04/10/2018 09:40:05 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ovidiu - Dan Bogat [ic17b501], ic17b501@technikum-wien.at
 * =====================================================================================
 */
#ifndef __mypopen_h
#define __mypopen_h

#include <stdio.h>


/* Dynamisch wachsende, gelinkte Liste an geoeffneten File-Pointern mit der geoeffneten PID */
/* popen returniert einen FILE pointer; */
/* pclose soll diesen schliessen, wenn der schreibende prozess damit fertig ist. */
/* Daher muessen popen und pclose(filepointer) vom gleichen Pointer reden koennen. Dafuer ist diese Struktur.  */
/* Es muss keine GelinkteListe sein. Minimalistische (alte) Beispiel haben auch nur die PID, oder eine Kombination  */
/* von pid und fileno(filedescriptor) in einem int oder int-array.  */
/* 
 * ===  STRUCT  ========================================================================
 *         Name:  pid
 *  Description:  Eine gelinkte Liste für FILE Pointer des Parents
 * =====================================================================================
 *
 *//*!
    * @author Ovidiu - Dan Bogat
    *	@brief Eine gelinkte Liste fuer FILE Pointer
    * @details
    * auch wenn laut den Test-Cases von popentest wir nur eines verwenden sollen
    * Es wurde initial mit einer Liste gelöst, anstatt mit einzelnen globalen variablen
    * Das ermöglich mehrere Forks, Childs, Pipes,.... im Zuge der Aufgabe2 jedoch nicht gebraucht
    * Da es aber funktional und sauber ist, und qualitativ hochwertiger als eine ander Lösung, 
    * bleibt es bestehen.
    *	@version 1.0.0
    *	@date 2018/04/28
    *
    * =====================================================================================
    */
static struct pid
{
  FILE *fp;
  pid_t pid;
  struct pid *next;
  int dirty_pipe;
} *pidlist;

extern void signalHandler(int);
extern FILE* mypopen(const char*, const char*);
extern int mypclose(FILE*);

#endif /* mypopen.h */
