/*
 * =====================================================================================
 *
 *       Filename:  exec.c
 *
 *    Description:  shows exec
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
#include "exec.h"

int main(int argc, char** argv)
{
	argc=argc;
	argv=argv;	
	pid_t fork_pid;
	char *const args[] = {"/bin/ls", "-l",NULL};
	
	fork_pid = fork();
	
	if(fork_pid == 0)
	{
		//Child process
		execv("/bin/ls",args);
		fprintf(stderr,"[FATAL] %s\n",strerror(errno));
		exit(errno);
	}else if(fork_pid < 0)
	{
		//Fork failed
		fprintf(stderr,"[FATAL] fork() failed %s\n",strerror(errno));
		exit(errno);
	}else{
		//parent process
	}
	
  return (EXIT_SUCCESS);
}
