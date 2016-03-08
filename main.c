/*  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  */
/*  File Type :  main.c                                                      */
/*  File Name : CommandLine                                        */
/*  Student Name : Hazert                                               */
/*  Student ID : 1330003036                                           */
/*  Created by Hazert on 15/10/2.                                   */
/*  Copyright © 2015年 Hazert. All rights reserved       */
/*  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#define SIZE 1024

int main(void) {
    while (1) {
    //Declare a buf[] to store temporary value, which is typed by user
    char buf[SIZE];
    
    // Ask the user to type a command:
    write(1, "Type a Command: \n", 17);
    //write command into buf[]
    write(0, buf, SIZE);

    for(int i = 0;i<SIZE;i++){
        if (buf[i] == '\n') {
            buf[i] = '\0';
            break;
        }
    }
    
    if(strncmp(buf, "exit",5)==0){
        break;
    }
        //Use fork() function to create a child process
       pid_t pID = fork();
        //pID is fork() return value, which can be process identifier
        if (pID == 0) {     /* Child process */
            //write(1, "This is Child process \n", 24);
            
            //nread is used to replace the end value,which user input, into 0;
            int nread;
            nread=read(0,buf,1024);
            buf[nread-1]= 0 ;
            
            //A system call, which is used to replace current process and execute user's command
            execlp(buf,buf,(char *)0);
        }else if (pID < 0){     /* Error Occurred */
            execlp("/bin/ls", "ls", NULL);
            exit(EXIT_FAILURE);
        }else{      /* Parent process */
            //write(1, "This is Parent process \n", 25);
            int returnStatus;
            
            // Parent process waits here for child to terminate.
            waitpid(pID, &returnStatus, 0);
            // Verify child process terminated without error.
            if (returnStatus == 0)
            {
                write(1, "The Child Process terminated normally. \n" , 41);
            }
            
            if (returnStatus == 1)
            {
                write(1, "The Child Process terminated with an error!.\n", 46);
            }
        }
        }
    return 0;
}