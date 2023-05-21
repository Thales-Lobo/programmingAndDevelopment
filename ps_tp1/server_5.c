/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmation système - TP n°1
 *
 * server_5.c
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

int random_number(int lower, int upper)
{
    return((rand() % (upper - lower + 1)) + lower);
}

////////////////////////////main////////////////////////////
int main()
{
    //signal handling
    struct sigaction sa;
    sa.sa_handler = stop_handler;

    if(sigaction(SIGINT, &sa, NULL) == -1 || sigaction(SIGTERM, &sa, NULL) == -1 || sigaction(SIGPIPE, &sa, NULL) == -1)
    {
        default_error("sigaction error!");
    }
    sigaction(SIGPIPE, &sa, NULL);
    //
    int fd;
    int counter = 1;
    char *myfifo = "./myfifo";

    if(mkfifo(myfifo, 0666) == -1)
    {                
        default_error("mkfifo()");
    }


    if((fd = open(myfifo, O_WRONLY)) == -1)
    {                
        default_error("open()");
    }
    //loop
    while(running)
    {
        int rand_msg = random_number(1, 99);

        write(fd, &rand_msg, sizeof(int));

        printf("Sender Process '%d' sent the data[%d]\n", getpid(), counter);

        counter++;
        sleep(1);
    }

    close(fd);
    printf("server_5 ended!");

    return EXIT_SUCCESS;
}