//Shell program
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<readline/readline.h>
#include<readline/history.h>
#include<term.h>
#include<ncurses.h>

int In(char* str)
{
    usleep(10000); //delays for printing purposes
    char* buf;
    //reads buff and assigns pointer to inputString
    buf = readline("\n>>> ");
    if (strlen(buf) != 0) {
        add_history(buf);
        strcpy(str, buf);
        return 0;
    } else {
        return 1;
    }
    //returns value based on input size (1 for 0 args)
}


// Executes args without a pipe
void execArgs(char** splitStr)
{
    // forking
    //printf("test");
    //sleep(1);
    pid_t pid = fork();
    int exitstatus;

    if (pid == -1) {
        printf("\nFailed forking");
        return;
    } else if (pid == 0) {
        if (execvp(splitStr[0], splitStr) < 0) {
            printf("\nCould not execute");
        }
        exit(0);
    } else {
        // waiting for child to terminate
        while(wait(&exitstatus) != pid)
        ;
        //printf("child exited with status %d,%d\n",exitstatus>>8, exitstatus&0377);
        return;
    }
}

// Piped args execute here
void execPipeArgs(char** splitStr, char** splitpipestr)
{
    int pipefd[2],exitstatus;
    pid_t p1, p2;
    //printf("test");
    if (pipe(pipefd) < 0) {
        printf("\nError creating pipe");
        return;
    }
    p1 = fork();
    if (p1 < 0) {
        printf("\nCould not fork");
        return;
    }

    if (p1 == 0) {
        // Child 1 executing..
        // It only needs to write at the write end
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);

        if (execvp(splitStr[0], splitStr) < 0) {
            printf("\nCould not execute command");
            exit(0);
        }
    }
        p2 = fork();
        if(p2 == 0) {
        // Parent executing

        if (p2 < 0) {
            printf("\nCould not fork");
            return;
        }

        if (p2 == 0) {
            close(pipefd[1]);
            dup2(pipefd[0], STDIN_FILENO);
            close(pipefd[0]);
            //printf("test12");
            if (execvp(splitpipestr[0], splitpipestr) < 0) {
                printf("\nCould not execute command");
                exit(0);
            }
        } //else {
            //waiting for children
            while(wait(&exitstatus) != p1)
            ;
            //printf("child exited with status %d,%d\n",exitstatus>>8, exitstatus&0377);
            while(wait(&exitstatus) != p2)
            ;
            //printf("child exited with status %d,%d\n",exitstatus>>8, exitstatus&0377);
        //}
    }
}
// function for finding pipe
int SplitPipe(char* str, char** strpiped)
{
    int i;
    for (i = 0; i < 2; i++) {
        strpiped[i] = strsep(&str, "|"); //splits string at pipe if it exists
        if (strpiped[i] == NULL)
            break;
    }

    if (strpiped[1] == NULL)
        return 0; // returns zero if no pipe is found.
    else {
        return 1;
    }
}

// function for parsing command words
void SplitSpace(char* str, char** splitStr)
{
    int i;
    //splits string by spaces using strsep instead of strtok
    for (i = 0; i < 100; i++) {
        splitStr[i] = strsep(&str, " ");

        if (splitStr[i] == NULL)
            break;
        if (strlen(splitStr[i]) == 0)
            i--;
    }
}

int SplitString(char* str, char** splitStr, char** splitpipestr)
{

    char* strpiped[2];
    int piped = 0;

    piped = SplitPipe(str, strpiped);

    if (piped) {
        SplitSpace(strpiped[0], splitStr);
        SplitSpace(strpiped[1], splitpipestr);
    }
    else {
         SplitSpace(str, splitStr);
    }
        return 1 + piped;
}

int main()
{
    char str[512], *Args[100];
    char* PipeArgs[100]; //sets up arrays for storage
    int flag = 0; //flag for determining pipe
    while (1) {
        flag = 0;
        if (In(str)) //takes input
            continue;
        flag = SplitString(str,Args, PipeArgs);

        // execute
        if (flag == 1)
            //puts(*Args);
            execArgs(Args);

        if (flag == 2)
            //puts(*Args);
            //puts(*PipeArgs);
            execPipeArgs(Args, PipeArgs);
        fflush(stdin); //flushes buffers for next input
        fflush(stdout);
    }
    return 0;
}
