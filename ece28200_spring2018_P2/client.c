#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <curses.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#define SCREENHEIGHT 30
#define SCREENWIDTH 70
#define MAXLENGTH 100

void terminalmode(int choice);
void drawgame(int arr[][SCREENHEIGHT], int length1, int length2);
/* TCP/IP Client */
int main(){
	int flg = 0;
	int lose;
	int lose2;
	int length1 = 0;
	int length2 = 0;
	//info* game = (info*)malloc(sizeof(info));
	int gamearr[SCREENWIDTH][SCREENHEIGHT];
	char* ch = (char*)malloc(sizeof(char));
	//noecho();
    terminalmode(flg);

	//create socket
	int netsock;
	//char resp[512];
	netsock = socket(AF_INET,SOCK_STREAM,0);

	//give an address to the socket
	struct sockaddr_in serveradd;
	serveradd.sin_family = AF_INET; //set type of connection
	serveradd.sin_port = htons(4200);	//sets port
	serveradd.sin_addr.s_addr = INADDR_ANY; //set address

	if (connect(netsock,(struct sockaddr *)&serveradd,sizeof(serveradd)) == -1){
		perror("Connect: "); //connect to socket
		exit(0);
	}
	initscr();
	read(netsock,gamearr,sizeof(gamearr));
	drawgame(gamearr,length1,length2);
	fflush(stdin);
	while(1){
	//get some data from the server
	//read(netsock, &resp, sizeof(resp)); //socket, buffer, buffer size, flags
	//print data recieved
	//printf("Recieved: %s\n",resp);
	//close connection

		*ch = getchar();
		if(*ch == 'a' || *ch == 's' || *ch == 'd' || *ch == 'w')
			write(netsock,ch,sizeof(ch));
		if(*ch == 'x'){
			write(netsock,ch,sizeof(ch));
			close(netsock);
			exit(0);
		}
		read(netsock,gamearr,sizeof(gamearr));
		read(netsock,&lose,sizeof(lose));
		read(netsock,&lose2,sizeof(lose2));
		read(netsock,&length1,sizeof(length1));
		read(netsock,&length2,sizeof(length2));
		if(lose | lose2)
			break;
		drawgame(gamearr,length1,length2);
		fflush(stdin);
	}
	sleep(2);
	if(lose && !lose2)
		mvprintw(15,35,"Player 2 Wins!\n");
	if(lose2 && !lose)
		mvprintw(15,35,"Player 1 Wins!\n");
	if(lose && lose2)
		mvprintw(15,35,"Touched Tips!\n");
	refresh();
	sleep(5);
	endwin();
	terminalmode(1);
	close(netsock);
	free(ch);
	return 0;

}

void terminalmode(int choice)
{
    //get setup and get termios info
    struct termios info;
    tcgetattr(0,&info);
    fcntl(0, F_SETFL, O_NONBLOCK);

    //if 0 turn OFF Canonical mode
    if(choice == 0)
    {
        info.c_lflag &= ~(ICANON|ECHO);
    }
    //if 1 turn Canonical mode ON
    else if(choice == 1)
    {
        info.c_lflag |= (ICANON|ECHO);
    }
    //set new terminal mode
    tcsetattr(0,TCSANOW,&info);

}

void drawgame(int arr[][SCREENHEIGHT],int length1, int length2)
{
    int i,k;
    char str[5];
    mvprintw(5,SCREENWIDTH+5,"Player 1 Score: %d",length1);
    mvprintw(6,SCREENWIDTH+5,"Player 2 Score: %d",length2);

    for(i=0;i<SCREENWIDTH;i++)
    {
        for(k=0;k<SCREENHEIGHT;k++)
        {
            if(arr[i][k] == 9)
            {
                move(k,i);
                addstr("X");
            }
            else if(arr[i][k] == 1 || arr[i][k] == 2 )
            {
                move(k,i);
                addstr("O");
            }
            else if(arr[i][k] == 0)
            {
                move(k,i);
                addstr(" ");
            }
            else if(arr[i][k] == 8)
            {
                move(k,i);
                addstr("*");
            }
            else if (arr[i][k]<MAXLENGTH && arr[i][k]>10  || (arr[i][k]<(2*MAXLENGTH+10) && arr[i][k]>=MAXLENGTH ))
            {
                move(k,i);
                addstr("@");
            }
        }
    }
    refresh();
}
