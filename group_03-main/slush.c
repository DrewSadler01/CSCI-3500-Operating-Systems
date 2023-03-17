#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<ctype.h>
#include<string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#define BUFFSIZE 1024

//GRADING NOTE: Command handling and pipelining appear to work correctly,
// and CTRL-C is handled appropriately. However, the CD command is not
// implemented. Extra credit not attempted.

// Code structure looks good- more verbose variable names (rather than "j")
// are preferred.

// Score: 95/100

void signalHandling( int signum ) { printf("\n"); }

int main(int argc, char* argv[]) {
    while(1) {

        signal(SIGINT, signalHandling);

        int max_arg = 15;
        int max_argv_size = max_arg + 2;
        char* cmd;
        char* my_argv[max_argv_size];
        char buff[BUFFSIZE];
        char* get_ret = fgets(buff, BUFFSIZE, stdin);
        if(get_ret == NULL){
        	break;
        }
        buff[strcspn(buff, "\n")] = 0;
        char* token = strtok(buff, "(");
        cmd = token;
        my_argv[0] = cmd;
        int error_int = 15;
        int after_last = 1;
        while(token != NULL){
            token = strtok(NULL, "(");
            my_argv[after_last] = token;
            if(token != NULL){
		if(strcmp(token," ") == 0){
			error_int = 1;
		}
	    }
            after_last++;
        }
        if (error_int < after_last) {
            printf("Invalid null command \n");
            break;
            }
  
        my_argv[after_last -1] = NULL;
        int j = 0;
        while(1){
        if(j == after_last - 1)
            break;		
        j++;	
        }
        
        int oldfd;
        int pipefd[2];
        pipe(pipefd);

        for(int i = after_last - 2; i >= 0; i--)
        {
            if(i != 0 ){
            int forkid = fork();
                if(forkid == 0){                                        
                    int dupret = dup2(pipefd[1], STDOUT_FILENO);       
                    if(i != (after_last - 2)){
                        int dupret2 = dup2(oldfd, STDIN_FILENO);}
                    char *cmd_dir;
                    char* child_argv[max_argv_size];
                    char* child_token = strtok(my_argv[i], " ");       
                    cmd = child_token;
                    child_argv[0] = cmd;
                    int child_last = 1;
                    while(1){
                        child_token = strtok(NULL, " ");
                        if(child_token == NULL)
                            break;
                        else if (child_token )


                        child_argv[child_last] = child_token;
                        child_last++;
                    }
                    child_argv[child_last] = NULL;
                        

                    int ret = execvp(child_argv[0], child_argv);
                    if (ret == -1) {
                        if(errno == 2 || errno == 3) {
                            perror("program not found.");
                            return 0;
                            }
                        
                    }
                }
                        oldfd = pipefd[0];
                close(pipefd[1]);
                pipe(pipefd);
                continue;
            }else{
                close(pipefd[1]);
                int forkid = fork();
                if(forkid == 0){
                    int dupret = dup2(oldfd, STDIN_FILENO);
                    char *cmd_dir;
                    char* child_argv[max_argv_size];
                    char* child_token = strtok(my_argv[i], " ");
                    cmd = child_token;
                    child_argv[0] = cmd;
                    int child_last = 1;
                    while(1){
                        child_token = strtok(NULL, " ");
                        if(child_token == NULL)
                            break;
                        child_argv[child_last] = child_token;
                        child_last++;
                    }
                    child_argv[child_last] = NULL;
                        
                    int ret = execvp(child_argv[0], child_argv);
                    if (ret == -1) {
                        
                      perror("program not found.");
                      return 0;
       
                        
                    }
                    
                }	
                waitpid(forkid, NULL, 0);
            }

        }
    }    
}

