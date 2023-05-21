/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmation système - TP n°1
 *
 * server_3.c
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
    //creation of child process, distinguishable by looking the "ppid" number and recognizing the parent and child process
    //both can be stopped by "CRTL-C"
    int fork_pid = fork();

    //signal handling
    struct sigaction sa;
    sa.sa_handler = stop_handler;

    if(sigaction(SIGINT, &sa, NULL) == -1 || sigaction(SIGTERM, &sa, NULL) == -1)
    {
        perror("sigaction error!");
        exit(EXIT_FAILURE);
    }

    //This message is shown anytime the program is endend, except for the case when the command "kill -9" is
    //used, resulting in the immediate interuption of the process

    if(atexit(exit_message) == -1)
    {
        perror("satexit error!");
        exit(EXIT_FAILURE);
    }

    printf("Hello World!\n");

    while(running)
    {
        printf("pid = %d\n", getpid());
        printf("ppid = %d\n", getppid());

        int rand_n = rand()%(99 + 1);
        printf("rand = %d\n", rand_n);
        printf("\n");

        sleep(1);
    }

    //obs: a kill signal sent to a child process turns it into a "zombie process", waiting to be reaped by the parent process
    //using function wait(), in the parent process, waits until the child process is finished, and displays the related exit status
    //with parent process completely killed, child process is realocated to another process (1 by default)
    if (fork_pid != 0)
    {
        int child_status;
        wait(&child_status);
        printf("Exit status = %d\n", WEXITSTATUS(child_status));
    }

    printf("Goodbye World!\n");
        
    return EXIT_SUCCESS;
}