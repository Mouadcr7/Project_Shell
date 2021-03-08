/*
 * Copyright (C) 2002, Simon Nieuviarts
 */

#include <stdio.h>
#include <stdlib.h>
#include "readcmd.h"
#include "csapp.h"
#include "executecmd.h"
#include <string.h>

void handler(int sig) { /* nouveau traitant */
	pid_t pid;
	int statut;
	pid = waitpid(-1, &statut, WNOHANG|WUNTRACED) ; /* attend un fils quelconque */
	return;
}
int main(int argc, char const *argv[], char ** envp) {
	Signal(SIGCHLD, handler) ;
	while (1) {
		struct cmdline *l;
		int i, j;
		printf("shell> ");
		l = readcmd();

		/* If input stream closed, normal termination */
		if (!l) {
			printf("exit\n");
			exit(0);
		}

		if (l->err) {
			/* Syntax error, read another command */
			printf("shell: %s\n", l->err);
			continue;
		}

		//if (l->in) printf("in: %s\n", l->in);
		//if (l->out) printf("out: %s\n", l->out);

		/* Display each command of the pipe */;
		int pipeprec = 0  ;  // a file descriptor returned from the previous call of executecmd ( necessary for managing pipes)
		int nbprocess = 0 ; // the number of process ( equal to the nb of cmds in a line )

		for (i=0; l->seq[i]!=0; i++) {
			char **cmd = l->seq[i];
			if ( ! strcmp(cmd[0],"quit") ) exit(0) ;
			pipeprec = executecmd(  cmd, l->in , l->out ,  l->seq[i+1] , pipeprec ,  i   ) ;
			nbprocess ++ ;
		}
		printf("\n");
		cleanzombies(nbprocess, l->isBg);
		nbprocess = 0 ;
	}
}
