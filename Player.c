/*  This is based on the client file that he gave us after project one felt like we can use this
    as our basic scaffolding. Then build more off of it
*/
#include <stdio.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <netdb.h> 
#include <string.h> 
#include <unistd.h> 
#include <stdlib.h> 

#define MAX_SIZE 2048 

int choice;

int main(int argc, char * argv[]) 
{ 
    FILE *fp; 
    struct hostent *hp; 
    struct sockaddr_in sin; 
    char *host, *port; 
    char buf[MAX_SIZE]; 
    int s; 
    int len; 
 
    if (argc==3) { 
        host = argv[1]; 
        port = argv[2]; 
    } 
    else { 
        fprintf(stderr, "usage: %s host port\n", argv[0]); 
        exit(1); 
    } 
 

    hp = gethostbyname(host); 
    if (!hp) { 
        fprintf(stderr, "%s: unknown host\n", host); 
        exit(1); 
    } 
 

    bzero((char *)&sin, sizeof(sin)); 
    sin.sin_family = AF_INET; 
    bcopy(hp->h_addr, (char *)&sin.sin_addr, hp->h_length); 
    sin.sin_port = htons(atoi(port)); 

    if ((s = socket(PF_INET, SOCK_STREAM, 0)) < 0) { 
        perror("simplex-talk: socket"); 
        exit(1); 
    } 
    if (connect(s, (struct sockaddr *)&sin, sizeof(sin)) < 0) 
    { 
        perror("simplex-talk: connect"); 
        close(s); 
        exit(1); 
    } 
 
    int size = 1; //Only need 1 digit, but we can change this
    while(1) { 
        scanf("%d", &choice);
        sprintf(buf, "%d", choice);
        if(send(s, buf, size, 0) < 0) { 
            perror("client: send"); 
        } 
        recv(s, buf, sizeof(buf), 0);
        printf("\nReceive: ");
        fwrite(buf, sizeof(buf), 1, stdout); 
    }
 
    close(s); 
    return 0;
} 