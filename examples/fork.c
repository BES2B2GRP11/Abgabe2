/*
 * =====================================================================================
 *
 *       Filename:  fork.c
 *
 *    Description:  shows a fork 
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
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include "fork.h"

int main(int argc, char** argv)
{
	argc=argc;
	argv=argv;	
	pid_t fork_pid;
	
	fork_pid = fork();
	
	if(fork_pid == 0)
	{
		//Child process
		fprintf(stdout,"Child process with pid %d ppid %d\n", getpid(), getppid());
	}else if(fork_pid < 0)
	{
		//Fork failed
		fprintf(stderr,"[FATAL] fork() failed %s\n",strerror(errno));
		exit(errno);
	}else{
		//parent process
		fprintf(stdout,"Parent process with pid %d ppid %d\n", getpid(), getppid());
	}
	
  return (EXIT_SUCCESS);
}
