#include "executecmd.h"

#define READ  0
#define WRITE 1

int  executecmd( char ** cmd , char * in , char * out , char ** cmdsuiv , int pipeprec, int i   ) {
    pid_t pid ;
    int des1,des2 ;
    int p[2];
      pipe(p);
      pid  = Fork () ;
      switch (pid)
        {
            case -1:
                fprintf(stderr, "Erreur de fork\n");
                exit(2);
                break ;

            case 0 : // fils
                if ( i == 0 && ( ! cmdsuiv )  ){
                  if(in){
                    des2 = Open( in , O_RDONLY, 0 ) ;
                    dup2(des2, STDIN_FILENO);
                    Close(des2);
                  }
                  if(out){
                    des1 = Open( out , O_WRONLY | O_CREAT | O_TRUNC, 0644 ) ;
                    dup2(des1, STDOUT_FILENO);
                    Close(des1);
                  }
                }
                else if ( i==0 && cmdsuiv  ) {
                  if(in){
                    des2 = Open( in , O_RDONLY, 0 ) ;
                    dup2(des2,0);
                    Close(des2);
                  }
                  dup2( p[WRITE], STDOUT_FILENO );
                  Execvp(cmd[0], cmd) ;

                }
                else if ( i && cmdsuiv ) {
                  dup2(pipeprec, STDIN_FILENO);
                  dup2(p[WRITE], STDOUT_FILENO);
                }
                else {
                  if(out){
                    des1 = Open( out , O_WRONLY | O_CREAT | O_TRUNC, 0644 ) ;
                    dup2(des1,1);
                    Close(des1);
                  }
                  dup2(pipeprec, STDIN_FILENO);
                }
                  Execvp(cmd[0], cmd) ;
                break;
            default:
                    if ( pipeprec ) close(pipeprec);
                    close(p[WRITE]);
                    if ( ! cmdsuiv ) close(p[READ]);
                break;

    }
    return p[READ];
}
      void cleanzombies( int n){
        for (int i = 0 ; i < n ; i++  ){
          wait(NULL);
        }
      }
