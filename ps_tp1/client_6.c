/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmation système - TP n°1
 *
 * client_6.c
 */
#include <stdlib.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdbool.h>
#define PORT 8080

//global variable running (default = true)
bool running = true;
 
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
    int sock, client_fd;
    struct sockaddr_in addr;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        default_error("socket creation!");
    }
 
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    addr.sin_port = htons(PORT);
 
    if ((client_fd = connect(sock, (struct sockaddr*)&addr, sizeof(addr))) < 0) {
        default_error("connection!");
    }

    int rand_msg;
    int counter = 1;
    while(running)
    {
        if (read(sock, &rand_msg, sizeof(int)) <= 0){                
            default_error("read()");
        }
        else{
            printf("Random Number [%d] = %d\n", counter, rand_msg);
        }
        counter++;
    }

    close(sock);
    close(client_fd);
    return EXIT_SUCCESS;
}
