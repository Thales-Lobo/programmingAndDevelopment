#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
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

int random_number(int lower, int upper)
{
    return((rand() % (upper - lower + 1)) + lower);
}

int main()
{
    int backlog = 1; //single connection

    int server_fd, new_socket;
    struct sockaddr_in addr;
    int addrlen = sizeof(addr);
 
    // Creating socket 
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        default_error("socket creation!");
    }

    addr.sin_family = AF_INET; //IPV4
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(PORT);
 
    //Attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr*)&addr, addrlen) < 0) {
        default_error("bind!");
    }
    if (listen(server_fd, backlog) < 0) {
        default_error("listen!");
    }
    if ((new_socket = accept(server_fd, (struct sockaddr*)&addr, (socklen_t*)&addrlen)) < 0) {
        default_error("accept!");
    }

    int counter = 1;
    while(running)
    {
        int rand_msg = random_number(1, 99);
        write(new_socket, &rand_msg, sizeof(int));
        printf("Sender Process '%d' sent the data[%d]\n", getpid(), counter);

        counter++;
        sleep(1);
    }
 
    close(new_socket);
    close(server_fd);
    return EXIT_SUCCESS;
}