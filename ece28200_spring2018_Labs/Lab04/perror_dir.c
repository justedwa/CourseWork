//--perror_file.c-------------------------
#include <stdio.h>
#include <stdlib.h> // for exit() function
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    int fd;

    if ( argc < 2 ){
            printf("Usage: %s <Directory>\n", argv[0]);
            exit(1);
    }
    
    fd = chdir(argv[1]);
    // printf will output user's formatted string, while perror will output
    // the system error msg corresponding to errno
    if (fd == -1){
            printf("Opening directory \"%s\" failed.\n", argv[1]);
            perror("");
    }
    else{
            printf("The directory \"%s\" was opened w/o problem.\n", argv[1]);
            perror("");
    }
    
    return 0;
}
