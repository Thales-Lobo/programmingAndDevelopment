/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmation système - TP n°1
 *
 * client_5.c
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
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>


//global variable running (default = true)
bool running = true;

//stop_handler function
void stop_handler(int sig)
{
    printf("\nSignal %d received!\n", sig);
    running = false;
}

void default_error(char *error_type)
{
    char error_msg[50] = {"An error occured with "};
    strcat(error_msg, error_type);
    strcat(error_msg, "!\n");

    perror(error_msg);
    exit(EXIT_FAILURE); 
}

int main()
{
    //signal handling
    struct sigaction sa;
    sa.sa_handler = stop_handler;

    if(sigaction(SIGINT, &sa, NULL) == -1 || sigaction(SIGTERM, &sa, NULL) == -1)
    {
        default_error("sigaction error!");
    }

    int fd;
    char *myfifo = "./myfifo";

    int rand_msg;
    int counter = 1;
    if((fd = open(myfifo, O_RDONLY)) == -1)
    {                
        default_error("open()");
    }

    while(running)
    {
        if (read(fd, &rand_msg, sizeof(int)) <= 0)
        {                
            default_error("read()");
        }
        else
        {
            printf("Random Number [%d] = %d\n", counter, rand_msg);
        }
        counter++;
    }
    close(fd);
    return EXIT_SUCCESS;
}