/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmation système - TP n°1
 *
 * server_2.c
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
    //signal handling
    struct sigaction sa;
    sa.sa_handler = stop_handler;

    //With the "-s INT" option, the "interupt signal" (SIGINT) is sent, while the 
    //command kill send only the "terminate signal" (SIGTERM). 
    //Adding "sigaction(SIGTERM, &sa, NULL)" as it follows, we can handle the terminate signal 

    //The "kill -9" command causes the OS to directly kill the process and ends its operation, not showing the message
    //it's equally not possible to contemplate this signal in this very code for this given reason
    //The command "kill" doesn't affect the used terminal, while the addition of the option "-s KILL" ends 
    // the parent process, wich is the terminal itself

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
    
    /////////////////////////////

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

    printf("Goodbye World!\n");
        
    return EXIT_SUCCESS;
}