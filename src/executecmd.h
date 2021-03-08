#ifndef __EXECMD__
#define __EXECMD__

#include <stdio.h>
#include <stdlib.h>
#include "csapp.h"




// function which execute cmd and uses piprec if it existes, i is the position of the cmd , in and out for the redirections
int  executecmd( char ** cmd , char * in , char * out , char ** cmdsuiv , int pipeprec  , int i   ) ;

// cleanup all the processes child ,  n is the number of children
void cleanzombies( int n , int isBg ) ;

#endif
