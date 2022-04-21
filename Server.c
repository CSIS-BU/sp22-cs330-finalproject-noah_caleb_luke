/*  This is based on the server file that he gave us after project one felt like we can use this
    as our basic scaffolding. Then build more off of it
*/

#include <stdio.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <netdb.h> 
 
#include <strings.h> 
#include <stdlib.h> 
#include <unistd.h> 

#include <string.h> 
 
#define MAX_PENDING  5 
#define MAX_SIZE 2048 
 
char square[10] = { 'o', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
int choice, player;

int checkForWin();
void displayBoard();
void markBoard(char mark);

int main(int argc, char** argv) 
{ 
    struct sockaddr_in sin; 
    char buf[MAX_SIZE]; 
    int buf_len; 
    socklen_t addr_len; 
    int s;
    int sNum = 0; 
    char *port; 
 
    if(argc==2) { 
        port = argv[1]; 
    } 
    else { 
        fprintf(stderr, "usage: %s port\n", argv[0]); 
        exit(1); 
    } 
 
    /* build address data structure */ 
    bzero((char *)&sin, sizeof(sin)); 
    sin.sin_family = AF_INET; 
    sin.sin_addr.s_addr = INADDR_ANY; 
    sin.sin_port = htons(atoi(port)); 
 
    /* setup passive open */ 
    if ((s = socket(PF_INET, SOCK_STREAM, 0)) < 0) { 
        perror("simplex-talk: socket"); 
        exit(1); 
    } 
    if ((bind(s, (struct sockaddr *)&sin, sizeof(sin))) < 0) { 
        perror("simplex-talk: bind"); 
        exit(1); 
    } 
    listen(s, MAX_PENDING); 
 
    /* wait for connection, then receive and print text */ 
    while(1) { 
        int new_s;
        if ((new_s = accept(s, (struct sockaddr *)&sin, &addr_len)) < 0) { 
            fprintf(stderr, "error: %s accept\n", argv[0]); 
            exit(1); 
        } 
        sNum++;
        pid_t pid = fork();
        if (pid == 0) {//Child
            //close(s);
            //printf("Child %d\n", sNum);
            //wait(1);
            memset (buf,'\0',sizeof(buf));//Empty char
            while ( (buf_len = recv(new_s, buf, sizeof(buf), 0)) ) { 
                printf("\nChild %d: ", sNum);
                fwrite(buf, 1, buf_len, stdout);
                fflush(stdout); 
                if(send(new_s, buf, sizeof(buf), 0) < 0) { //Sends back
                    perror("server: send"); 
                } 
            } 


            /*
            int gameStatus;
            char mark;
            player = 1;
            do {
                displayBoard();
                //change turns
                player = (player % 2) ? 1 : 2;

                //Get Input
                printf("Player %d,enter a number: ", player);
                scanf("%d", &choice);
                //set the correct character based on player turn
                mark = (player == 1) ? 'X' : 'O';
                //set board based on user choice or invalid choice
                markBoard(mark);
                gameStatus = checkForWin();
                player++;

            } while (gameStatus == -1);

            if (gameStatus == 1) //player = 2
            {
                printf("==>Player %d win \n\n", --player);
            }
            else 
            {
                printf("==>Game draw\n\n");
            }*/


            fflush(stdout); 
            close(new_s); 
            exit(1);
        }
        else if (pid < 0) {
            perror("[error] fork");
            exit(1);
        }
        printf("Client Connected\n");
    } 
    close(s); 
 
    return 0; 
} 

int checkForWin()
{
	int returnValue = 0;

	if (square[1] == square[2] && square[2] == square[3])
	{
		returnValue = 1;
	}
	else if (square[4] == square[5] && square[5] == square[6])
	{
		returnValue = 1;
	}
	else if (square[7] == square[8] && square[8] == square[9])
	{
		returnValue = 1;
	}
	else if (square[1] == square[4] && square[4] == square[7])
	{
		returnValue = 1;
	}
	else if (square[2] == square[5] && square[5] == square[8]) 
	{
		returnValue = 1;
	}
	else if (square[3] == square[6] && square[6] == square[9]) 
	{
		returnValue = 1;
	}
	else if (square[1] == square[5] && square[5] == square[9]) 
	{
		returnValue = 1;
	}
	else if (square[3] == square[5] && square[5] == square[7])
	{
		returnValue = 1;
	}
	else if (square[1] != '1' && square[2] != '2' && square[3] != '3' && square[4] != '4' && square[5] != '5' && square[6] != '6' 
			&& square[7] != '7' && square[8] != '8' && square[9] != '9')
	{
		returnValue = 0;
	}
	else
	{
		returnValue = -1;
	}

	return returnValue;
}

void displayBoard()
{
	system("cls");

	printf("\n\n\tTic Tac Toe\n\n");

	printf("Player 1 (X)  -  Player 2 (O)\n\n\n");

	printf("     |     |     \n");
	printf("  %c  |  %c  |  %c \n", square[1], square[2], square[3]);

	printf("_____|_____|_____\n");
	printf("     |     |     \n");

	printf("  %c  |  %c  |  %c \n", square[4], square[5], square[6]);

	printf("_____|_____|_____\n");
	printf("     |     |     \n");

	printf("  %c  |  %c  |  %c \n", square[7], square[8], square[9]);

	printf("     |     |     \n\n");
}

void markBoard(char mark)
{
	if (choice == 1 && square[1] == '1') 
	{
		square[1] = mark;
	}
	else if (choice == 2 && square[2] == '2')
	{
		square[2] = mark;
	}
	else if (choice == 3 && square[3] == '3')
	{
		square[3] = mark;
	}
	else if (choice == 4 && square[4] == '4')
	{
		square[4] = mark;
	}
	else if (choice == 5 && square[5] == '5')
	{
		square[5] = mark;
	}
	else if (choice == 6 && square[6] == '6')
	{
		square[6] = mark;
	}
	else if (choice == 7 && square[7] == '7')
	{
		square[7] = mark;
	}
	else if (choice == 8 && square[8] == '8')
	{
		square[8] = mark;
	}
	else if (choice == 9 && square[9] == '9')
	{
		square[9] = mark;
	}
	else
	{
		printf("Invalid move ");

		player--;
	}
}