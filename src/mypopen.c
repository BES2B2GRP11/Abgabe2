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
/* -- Bei dieser Art von pipe, es gibt auch andere, vollduplex z.B. je nach Bedarf -- */
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <paths.h>   /* Definiert Standard Pfade, mitunter fuer die Shell ('/bin/sh') */
#include <sys/wait.h>
#include "mypopen.h"


FILE* mypopen(const char* cmd, const char* mode)
{
  struct pid* volatile current;
  pid_t pid;
  FILE *fp; /* wenn alles klappt, wird dieser returniert :) */
  int pdesc[2]; /* Pipe deskriptoren */
  char *argument_pointer[] = {"sh","-c",NULL,NULL}; /* wir fuehren immer "sh -c" aus fuer jedes cmd - argument_pointer[2] wird dann zu cmd */

  /* Die Loesung mit der gelinkten liste ist trotzdem besser. */
  /* Aber sei es drum... wenn man es so verlangt, verlangt man es so */
  if (pidlist != NULL)
  {
    errno = EAGAIN;
    return NULL;
  }
  
  /* mode Sentinels */
  /* TEST 04 */
	if(mode == NULL)
	{
		errno = EINVAL;
		return NULL;
	} /* TEST 04 */
	
	if ( mode[1] != '\0' )
    {
      /* Wir haben mehr als nur einen char */
      errno = EINVAL;
      return NULL;
    }
  
  /* mode kann in diesem Fall nur noch aus einem Buchstaben bestehen */
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
  
  
  /* einen knoten der gelinkten Liste erstellen */
  /* die struct ist in mypopen.h */
  /* andere implementierungen ohne header file haben die definition gleich im source file */
  if((current = malloc(sizeof(struct pid))) == NULL)
    return NULL;
  
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
      /* wir raeumen auf und returnieren NULL */
      (void) close(pdesc[0]); // (void) weil return von close hier uninteressant ist
      (void) close(pdesc[1]); // (void) weil return von close hier uninteressant ist
      free(current);          // An diesem Punkt haben wir einen Speicher von malloc erhalten
      return NULL;
      /* NIE ERREICHBARER PUKNT IM CODE */
    case 0:
      { 
        /* BONUS {} nach case 0 aber nicht case -1 :)) labels are not statemnts */ 
        /* Nur der Kindprozess kann den returnwert 0 haben */
        /* Child */
        
        /* Wir brauchen einen Zeiger p um die Liste von pids zu iterieren */
        struct pid* volatile p;
      
        /* Wir schließen alle dem Child lokalen Kopien aller Filepointer, welche von anderen popen-childs erstellt wurden */
        /* Diese brauchen wir nicht */
        for(p=pidlist;p;p=p->next)
          (void) close(fileno(p->fp)); 
      
      
        /* wir prüfen die Art der Kommunikation mit dem Parten-Prozss */
        /* wir werden als child entweder lesen oder schrieben */
        /* und schließen daher den jeweils anderen pdesc[] */
        /* mode kann nach den ersten checks in dem Source nur noch aus einem Buchstaben bestehen */
        /* es wurde auf ausschlieszlich 'r' oder 'w' geprueft, somit reicht ein if-else */
        /* 'r' und 'w' gibt an, wie der Parten die pipe verwenden will, und child richtet sich dannach */
        if(*mode == 'r')
          {
            /* 'r' oder 'w' gibt in diesem Kontext immer an, wie der Parent-Prozess mit der PIPE arbeiten will */
            /* 'r' --> Parent will lesen aus der PIPE - Kind muss schreiben */
            /* 'w' --> Parent will schreiben in die PIPE - Kund muss lesen */
            /* Parent will lesen ('r'), somit muessen wir schreiben */
            /* pdesc[0] --> zum Lesen (gueltig fuer beide mit jeweils eigener Kopie) */
            /* pdesc[1] --> zum Schreiben (gueltig fuer beide mit jeweils eigener Kopie) */
            /* */
            /* Wir koennen pdesc[0] schliessen, da wir es nie brauchen werden */
            /* wir setzen unseren STDOUT gleich pdesc[1] */
            /* Wenn ab nun irgendeine Funktion vom child aufgerufen wird die auf etwas auf STDOUT aus gibt, */
            /* wandert es dadurch (dup) direkt in die PIPE */
            /* danke (dup2) ist STDOUT somit eine Kopie von pdesc[1], und pdesc[1] selbst kann nach erfolgreichem dup */
            /* geschlossen werden (es wird dupliziert) */
            (void) close(pdesc[0]);
            //if(pdesc[1] != STDOUT_FILENO)
            //{
            (void) dup2(pdesc[1], STDOUT_FILENO);
            (void) close(pdesc[1]);
            //}
            /* hier sollte laut man der dup2 nichts tun, wenn oldfd und newfd das gleiche sind, und newfd returnieren */
            /* somit sollte das if statement unnoetigt sein */
          }else{
          /* mode kann nur noch 'w' sein */
          /* spielegverkehrt zu oben */
          (void) close(pdesc[1]);
          (void) dup2(pdesc[0],STDIN_FILENO);
          (void) close(pdesc[0]);
        }
        /* FERTIG MIT DEM EINRICHTEN DER PIPE FUER DAS CHILD */
        
        /* CMD ausfuehren */
        /* argument_pointer[2] wird auf cmd gesetzt fuer exec */
        /* dadurch haben wir: */
        /* +----------------------------------------------------------+ */
        /* |                                                          | */
        /* |                   arguments_pointer                      | */
        /* |                                                          | */
        /* |     +----------+ +---------+  +-------+  +--------+      | */
        /* |     |   "sh"   | |  "-c"   |  | *cmd  |  |  NULL  |      | */
        /* |     +----------+ +---------+  +-------+  +--------+      | */
        /* |                                                          | */
        /* +----------------------------------------------------------+ */
        argument_pointer[2] = (char *)cmd;
        /* Somit haben wir alles fuer den exec Aufruf vorbereitet: Pipe, und das Commando samt argumente */
        
        execve(_PATH_BSHELL, argument_pointer, NULL);
        
        /* Wir koennen nicht wissen was nun genau schiefgelaufen ist */
        /* Es kann das Kommando nicht ausgefuehrt werden weil, */
        /* das Kommando nicht gefunden werden konne */
        /* Oder weil das Kommand einen Library-Funktion aufruft, welche schiefgelaufen ist */
        /* /bin/sh kann schiefgehen, etc.... */
        /* Weil wir das hier nicht wissen koennen returnieren wir 127 */
        _exit(127);
        /* DIESER PUNKT IM CODE HIER WIRD NIE ERREICHT */
      }
    }
  
  /* Vater */
  /* Siehe child prozess zum Einrichten der pipe bezueglich r und w */
  /* Parent-Prozess macht es spiegelverkehrt */
  /* Es wird gleich der FILEPOINTER richtig gesetzt */
  /* dafuer wird mit fdopen ein FileDeskriptor, mit mode (r,w) geoeffnet */
  /* fp ist dann lediglich ein Pointer drauf */
  if(*mode == 'r')
    {
      fp = fdopen(pdesc[0],mode);
      (void) close(pdesc[1]);
    }else{
    fp = fdopen(pdesc[1],mode);
    (void) close(pdesc[0]);
  }
  
  
  
  /* Wir erweitern die gelinkte Liste um den filepointer, und der PID vom Child prozess der dann reinschreiben soll */
  /* pclose wird dann auf diese pid warten (muessen), bevor der Filepointer geschlossen wird */
  /* CURRENT ist nur ein einzelner, nicht zusammenhaengender Block */
  current->fp = fp;
  current->pid = pid;
  current->next = pidlist; /* Hier wird das next vom current auf das erste element der liste gesetzt (pidlist weisz wo der Anfang ist) */
  pidlist = current;       /* hier wird der Zeiger pidlist auf das neue element gesetzt, wodurch current effektiv am Anfang der Liste eingefuegt wurde */
  /* ist pidlist null, so ist dies das erste element der liste und current->next == NULL */
  /* dadurch funktioniert die forschleife (p=pidlist;p;p->next) auch wunder bar, da mit ';p;' geschaut wird, oder p == NULL ist */
  
  return fp;
}

int mypclose(FILE* stream)
{
	struct pid* volatile prev;
  struct pid* volatile curr;
  int pstat;
  pid_t pid;
  
	/* Test 12 */
	/* mypopen wurden noch nicht erfolgreich aufgerufen */
	/* pidlist muss hier NULL sein */
	if(pidlist == NULL)
	{
		errno=ECHILD;
		return -1;
	} /* Test 12 Done */
	
	/* Test 03 */
	if(stream == NULL)
	{
		errno=EINVAL;
		return -1;
	} /* Test 03 Done */
	
  if(fileno(stream) == -1 || stream == NULL)
  {
    errno=ECHILD;
    return -1;
  }
  
  for(prev = NULL, curr = pidlist; curr; prev = curr, curr=curr->next)
	{
		if(fileno(curr->fp) == fileno(stream))
       break;
		else
		{
			errno=EINVAL;
			return -1;
		}
	}
  
	if(curr == NULL)
  {
    errno=ECHILD;
    return -1;
  }
  	
	
  (void)fclose(stream);
  
  do {
    pid = waitpid(curr->pid, &pstat, 0);
	} while (pid == -1 && errno == EINTR);
  
  if (prev == NULL)
    pidlist = curr->next;
	else
    prev->next = curr->next;
	free(curr);
  
	/* Test 14 */
	/* WIFEXITED prueft ob der Child sich regulaer beendet hat. Falls nicht returniert es FALSE */
	if(! WIFEXITED(pstat) )
	{
		errno=ECHILD;
		return -1;
	}/* Test 14 Done */
	
	
	/* Test 13 -- WEXITSTATUS vom pstat -- holt den returncode raus siehe man waitpid */
	return (pid == -1 ? -1 : WEXITSTATUS(pstat));
}
