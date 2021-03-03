#include "executecmd.h"



void executecmd( char ** cmd , char * in , char * out , char ** envp ) {
    pid_t pid ;
    int des1,des2 ;
      pid  = Fork () ;
      switch (pid)
        {
            case -1:
                fprintf(stderr, "Erreur de fork\n");
                exit(2);
                break ;

            case 0 : // fils
                if(out){
                  des1 = Open( out , O_WRONLY | O_CREAT | O_TRUNC, 0644 ) ;
                  dup2(des1,1);


                }
                if(in){
                  des2 = Open( in , O_RDONLY, 0 ) ;
                  dup2(des2,0);
                }
                //int lg = strlen(cmd[0]) ;
                //char *path = malloc ( (6+lg) * sizeof(char) ) ;
                //strcpy(path,"/bin/" );
                //strcat (path, cmd[0]);
                //Execve(path, cmd, envp) ;
                //free(path);
                Execvp(cmd[0], cmd) ;
                if (in) Close(des1);
                if ( out ) Close(des2);
                //if ( err == -1) printf("%s: command not found \n",cmd[0] );;
                return ;
                break;
            default:
                  while (!(wait(NULL) == pid)) ;
                break;
    }
}
