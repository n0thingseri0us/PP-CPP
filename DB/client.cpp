#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <iostream>
#include <string>
#include <sys/poll.h>
#include <cerrno>
#include <cctype>
#include <algorithm>
#include <exception>

#define  SERVER_PORT     5555
#define  SERVER_NAME    "127.0.0.1"
#define  BUFLEN          512

#define disconnect_code 3
#define err_code 2
#define print_code 1
#define no_print_code 0

#define column_name 0
#define column_group 1
#define column_rating 2
#define column_info 3

int  writeStrToServer (int fd);
int  PrintFromServer (int fd);
int  PrintStrFromServer (int fd);
void send_int(int fd, int number);
void send_str(int fd, const char * str);


void send_int(int fd, int number)
{
	send(fd, &number, sizeof(number), MSG_WAITALL);
}


void send_str(int fd, const char *str)
{
	int len = strlen(str);
	send_int(fd, len);
	send(fd, str, len, MSG_WAITALL);
}



int  main (void){
    int err;
    int sock;
    struct sockaddr_in server_addr;
    struct hostent    *hostinfo;

    hostinfo = gethostbyname(SERVER_NAME);
    if ( hostinfo==NULL ) {
        fprintf (stderr, "Unknown host %s.\n",SERVER_NAME);
        exit (EXIT_FAILURE);
    }

    server_addr.sin_family = PF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr = *(struct in_addr*) hostinfo->h_addr;

   
    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror ("Client: socket was not created");
        exit (EXIT_FAILURE);
    }

    
    err = connect (sock, reinterpret_cast<sockaddr *> (&server_addr), sizeof(server_addr));
    if (err < 0) {
        perror ("Client:  connect failure");
        exit (EXIT_FAILURE);
    }
    fprintf (stdout, "Client: Connection is ready\n");

    
    while(1) {
        if (writeStrToServer(sock) < 0) break;
        if (PrintFromServer(sock) < 0) break;
	}

    fprintf (stdout, "Client: The end\n");

    close (sock);
    exit (EXIT_SUCCESS);
}

int writeStrToServer(int fd){
    char buf[BUFLEN];

    std::cout << "Client: Send to server > ";
    if (fgets(buf, BUFLEN, stdin) == NULL) {
	    printf("Client: Message error\n");
    }
    if(strlen(buf) > 1) buf[strlen(buf) - 1] = 0;

    send_str(fd, buf);
   
    return 0;
}


int PrintFromServer(int fd){
    int code;
    recv(fd, &code, sizeof(code), MSG_WAITALL);

    if(code == 0){
        PrintStrFromServer(fd);
        std::cout << std::endl;
        return -1;
    }

    if(code == 1){
        PrintStrFromServer(fd);
        std::cout << std::endl;
        return -1;
    }

    if(code == 2){
        PrintStrFromServer(fd);
        std::cout << std::endl;
        return 0;
    }

    if(code == 3){
        PrintStrFromServer(fd);
        std::cout << std::endl;
        return 0;
    }
    return 0;
}

int PrintStrFromServer(int fd){
	int len;
	int bytes_read;
	bytes_read = recv(fd, &len, sizeof(len), MSG_WAITALL); // считываем длину сообщения
	if (bytes_read != sizeof(len)) {
        std::cout << "Server Error!" << std::endl;
		return -1;
	}
    if(len < 0){
        std::cout << "Server Error!" << std::endl;
		return -1;
	}
	char *msg = new char[len];
	bytes_read = recv(fd, msg, len, MSG_WAITALL); // читаем сообщение целиком
	if (bytes_read != len) {
		delete[] msg;
        std::cout << "Server Error!" << std::endl;
		return -1;
	}
    std::string str = std::string(msg, len);
    std::cout << str;
    delete[] msg;
    return 0;
}
