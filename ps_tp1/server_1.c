/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmation système - TP n°1
 *
 * server_1.c
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


int main()
{
    printf("Hello World!\n");

    while(true)
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

