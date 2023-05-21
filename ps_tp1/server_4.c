/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmation système - TP n°1
 *
 * server_4.c
 */

// for printf()
#include <stdio.h>
// For rand(), srand(), sleep(), EXIT_SUCCESS
#include <stdlib.h>
// For time()
#include <time.h>
// For getpid(), getppid()
#include <unistd.h>
// For boolean variables
#include<stdbool.h>
// For signal manipulation
#include <signal.h>
//
#include <sys/wait.h>

//global variable running (default = true)
bool running = true;

//stop_handler function
void stop_handler(int sig)
{
    printf("\nSignal %d received!\n", sig);
    running = false;
}

void exit_message()
{
    printf("Program end!\n");
}

int main()
{
    int fd[2];

    if(pipe(fd) == -1)
    {
        perror("An error ocurred with opening the pipe!\n");
        exit(EXIT_FAILURE);
    }

    //signal handling
    struct sigaction sa;
    sa.sa_handler = stop_handler;

    if(sigaction(SIGINT, &sa, NULL) == -1 || sigaction(SIGTERM, &sa, NULL) == -1)
    {
        perror("sigaction error!");
        exit(EXIT_FAILURE);
    }

    if(atexit(exit_message) == -1)
    {
        perror("satexit error!");
        exit(EXIT_FAILURE);
    }

    printf("Hello World!\n");

    int fork_pid = fork();

    if(fork_pid == -1)
        {
        perror("An error occurred with fork!\n");
        exit(EXIT_FAILURE);
        }

    while(running)
    {
        printf("pid = %d\nppid = %d\n", getpid(), getppid());
        printf("\n");

        //The parent process send the number to the child process, wich displays it:
        //child process
        if(fork_pid == 0)
        {
            int rand_child;

            if(read(fd[0], &rand_child, sizeof(int)) == -1)
            {
                perror("An error occurred with reading!\n");
                exit(EXIT_FAILURE);           
            }
            printf("Random number = %d\n", rand_child);
        }

        //parent process
        else
        {
            int rand_parent = rand()%(99 + 1);

            if(write(fd[1], &rand_parent, sizeof(int)) == -1)
            {
                perror("An error occurred with writing!\n");
                exit(EXIT_FAILURE);           
            }
        }

        sleep(1);
    }

    //When killed, parent process send a kill signal to child process
    //in the same way, when the child process is killed, the parent process follows it
    //obs: both (child and parent) display the "Goodbye World!" when ended
    if(fork_pid == 0) //child
    {
        kill(getppid(), SIGTERM); 
    }
    else //parent
    {
        kill(fork_pid, SIGTERM);
    }

    close(fd[0]);   //read
    close(fd[1]);   //write
    printf("Goodbye World!\n");
        
    return EXIT_SUCCESS;
}
