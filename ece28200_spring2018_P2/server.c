#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include "game.h"
#include <unistd.h>
//Function Prototypes


/* TCP/IP Server */
int main(){
	//creating variables for select()
	fd_set readfds;
	int ret;
	int score1;
	struct timeval timeout;
	FD_ZERO(&readfds);
	timeout.tv_sec = 0;
	timeout.tv_usec = 1000;
	
	//create socket
	int servsock;
	char buff[128];
	char send[512] = "Some Stuff for now";
	servsock = socket(AF_INET,SOCK_STREAM,0);
	//set server address
	struct sockaddr_in serveradd;
	serveradd.sin_family = AF_INET; //type
	serveradd.sin_port = htons(4200); //port
	serveradd.sin_addr.s_addr = INADDR_ANY; //local ip
	if (setsockopt(servsock, SOL_SOCKET, SO_REUSEADDR, &(int){ 1 }, sizeof(int)) < 0)
    		error("setsockopt(SO_REUSEADDR) failed");
	//bind socket
	if(bind(servsock, (struct sockaddr*) &serveradd,sizeof(serveradd)) == -1){
		perror("Error: ");
		exit(0);
	}
	listen(servsock,5); //listen on socket max 5 clients
	printf("Waiting for Player 1\n");
	int client1; //socket for client
	client1 = accept(servsock, NULL,NULL); //accept client connection
	printf("Player 1 Connected!\nWaiting for Player 2\n");
	int client2;
	client2 = accept(servsock,NULL,NULL);
	printf("Player 2 Connected!\n");
	//write(client1, send, sizeof(send)); //send some data
	FD_SET(client1,&readfds); //adding client to file descriptors set and master set
	FD_SET(client2,&readfds);
	//variables needed for running
    int i,k;

    //can make  p2ch and p2mainch
    char ch = 'd';
	char ch2 = 'a';
    char* mainch = (char*)malloc(sizeof(char));
	*mainch = 'd';
	char* mainch2 = (char*)malloc(sizeof(char));
	*mainch2 = 'a';
    //only one game array 2x2
    int gamearr[SCREENWIDTH][SCREENHEIGHT];

    //player 1 vars
    int lose = 0;
    int *conditionp;
    int sneklength = 1;
    int *sneklengthp;
    sneklengthp = &sneklength;
    conditionp = &lose;

    //player 2 vars
    int lose2 = 0;
    int *conditionp2;
    int sneklength2 = 1;
    int *sneklengthp2;
    sneklengthp2 = &sneklength2;
    conditionp2 = &lose2;


    //initialize game only fills out array with starting values
    initializegame(gamearr);
    addfood(gamearr);
	write(client1, gamearr, sizeof(gamearr));
	write(client2, gamearr, sizeof(gamearr));
	
	 while(1)
    {	

		ret = select(client2+1,&readfds,NULL,NULL,&timeout); 
		
		if((FD_ISSET(client1,&readfds))){
			read(client1,mainch,sizeof(mainch));
			printf("1:%c\n",*mainch);
		}
		if((FD_ISSET(client2,&readfds))){
			read(client2,mainch2,sizeof(mainch2));
			printf("2:%c\n",*mainch2);
		}
        	if(!(*mainch == 'a' && ch == 'd') && !(*mainch == 's' && ch == 'w') && !(*mainch == 'w' && ch == 's') && !(*mainch == 'd' && ch == 'a'))
			ch = *mainch;
		if(!(*mainch2 == 'a' && ch2 == 'd') && !(*mainch2 == 's' && ch2 == 'w') && !(*mainch2 == 'w' && ch2 == 's') && !(*mainch2 == 'd' && ch2 == 'a'))
			ch2 = *mainch2;
		
		
		//ch = *mainch;
		//ch2 = *mainch;
        	if(ch == 'x' || ch2 == 'x'){
			printf("Player Exited");
            		break;
		}
        	updategame(gamearr,ch,sneklengthp,conditionp,ch2,sneklengthp2,conditionp2);
		write(client1,gamearr,sizeof(gamearr));
		write(client2,gamearr,sizeof(gamearr));
		write(client1,&lose,sizeof(lose));
		write(client1,&lose2,sizeof(lose2));
		write(client2,&lose,sizeof(lose));
		write(client2,&lose2,sizeof(lose2));
		write(client1,&sneklength,sizeof(sneklength));
		write(client1,&sneklength2,sizeof(sneklength2));
		write(client2,&sneklength,sizeof(sneklength));
		write(client2,&sneklength2,sizeof(sneklength2));
        if(lose || lose2)
        {
            break;
        }
		FD_ZERO(&readfds);
		FD_SET(client1,&readfds);
		FD_SET(client2,&readfds);
		timeout.tv_usec = 1000;
		timeout.tv_sec = 0;
		if(!ret)
			usleep(75000);
		else
			usleep(75000);
    }
	//close sockets
	printf("GAME OVER\n");
	close(servsock);
	close(client1);


	return 0;

}





