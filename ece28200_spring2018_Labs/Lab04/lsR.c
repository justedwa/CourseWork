/* ls2.c
 *	purpose  list contents of directory or directories
 *	action   if no args, use .  else list files in args
 *	note     uses stat and pwd.h and grp.h 
 *	BUG: try ls2 /tmp  
 */
#include	<stdio.h>
#include        <stdlib.h>
#include	<sys/types.h>
#include	<dirent.h>
#include	<sys/stat.h>
#include        <string.h>
#include        <unistd.h>

void do_ls(char[], int *);
void dostat(char *);
void show_file_info( char *, struct stat *);
void mode_to_letters( int , char [] );
char *uid_to_name( uid_t );
char *gid_to_name( gid_t );

main(int ac, char *av[])
{
	int* lv = (int *) malloc(sizeof(int));
	if ( ac == 1 ) //if there is only 1 arg show current directory
		do_ls( ".",lv );
	else //otherwise show specified
		{
			printf("%s:\n", av[1] );//show directory looking into
			chdir(av[1]); //change to that directory
			do_ls( ".",lv ); //open directory to read contents
		}
	free(lv); //frees pointer used to store level
}

void do_ls( char dirname[], int* lv )
/*
 *	list files in directory called dirname
 */
{
	DIR		*dir_ptr;		/* the directory */
	struct dirent	*direntp;		/* each entry	 */
	int a = 0; //working variable for indents
	char dirs[1024][256]; //stores directories within each directory	
	int x = 0; //working variable for loop
	int z = 0; //working var for keeping track of dirs
	a = *lv;
	char cwd[256]; //defines a string for the current working directory
	getcwd(cwd, sizeof(cwd)); //fetches and prints current working directory
	printf("\n%s\n",cwd);
	if ( ( dir_ptr = opendir( dirname ) ) == NULL ){ //if the directory is unable to be opened print an error
		fprintf(stderr,"ls1: cannot open %s\n", dirname);
		perror(""); //prints system error output
	}
	else{ //otherwise open the directory and read the contents
		while((direntp=readdir(dir_ptr)) != NULL) //checks to see if there are contents still to be read
		{
			if(direntp->d_type == DT_DIR) // if there is a directory then place it in a string array used later
			{
				strcpy(dirs[z],direntp->d_name);
				z++;
				
				//dostat(direntp->d_name);
				//if(strcmp(direntp->d_name,".") == 0 || strcmp(direntp->d_name,"..") == 0)
				//	continue;
				//printf("%s\n",direntp->d_name);
				for(x = 0;x<a;x++) //print spaces corresponding to level stored in a
				{
					printf("  ");
				}
				dostat(direntp->d_name); //print the file stats
				//printf("%s\n",direntp->d_name);
				//chdir(direntp->d_name);
				//*lv = *lv + 1;
				//do_ls(".",lv);
				//chdir("..");
				//*lv = *lv - 1;
			}
			else //if the file is not a directory print spaces and display stats
			{
				for(x=0;x<a;x++)
				{
					printf("  ");
				}
				dostat(direntp->d_name);
			}
		}
		for(x=0;x<z;x++) //loop through directories within current directory and call dols to print their contents
		{
			chdir(dirs[x]); //changes current dir to the next dir in the array
			*lv = *lv + 1; //changes level with each node you travel further into the directory tree
			do_ls(".",lv);
			chdir(".."); //returns to previous dir
			*lv = *lv - 1; //resets level
		}	
	}
	closedir(dir_ptr); //closes directory
}


void dostat( char *filename )
{
	struct stat info;

	if ( stat(filename, &info) == -1 )		/* cannot stat	 */
		perror( filename );			/* say why	 */
	else					/* else show info	 */
		show_file_info( filename, &info );
}

void show_file_info( char *filename, struct stat *info_p )
/*
 * display the info about 'filename'.  The info is stored in struct at *info_p
 */
{
	char	*uid_to_name(), *ctime(), *gid_to_name(), *filemode();
	void	mode_to_letters();
        char    modestr[11];

	mode_to_letters( info_p->st_mode, modestr );

	printf( "%s"    , modestr );
	printf( "%4d "  , (int) info_p->st_nlink);	
	printf( "%-8s " , uid_to_name(info_p->st_uid) );
	printf( "%-8s " , gid_to_name(info_p->st_gid) );
	printf( "%8ld " , (long)info_p->st_size);
	printf( "%.12s ", 4+ctime(&info_p->st_mtime));
	printf( "%s\n"  , filename );

}

/*
 * utility functions
 */

/*
 * This function takes a mode value and a char array
 * and puts into the char array the file type and the 
 * nine letters that correspond to the bits in mode.
 * NOTE: It does not code setuid, setgid, and sticky
 * codes
 */
void mode_to_letters( int mode, char str[] )
{
    strcpy( str, "----------" );           /* default=no perms */

    if ( S_ISDIR(mode) )  str[0] = 'd';    /* directory?       */
    if ( S_ISCHR(mode) )  str[0] = 'c';    /* char devices     */
    if ( S_ISBLK(mode) )  str[0] = 'b';    /* block device     */

    if ( mode & S_IRUSR ) str[1] = 'r';    /* 3 bits for user  */
    if ( mode & S_IWUSR ) str[2] = 'w';
    if ( mode & S_IXUSR ) str[3] = 'x';

    if ( mode & S_IRGRP ) str[4] = 'r';    /* 3 bits for group */
    if ( mode & S_IWGRP ) str[5] = 'w';
    if ( mode & S_IXGRP ) str[6] = 'x';

    if ( mode & S_IROTH ) str[7] = 'r';    /* 3 bits for other */
    if ( mode & S_IWOTH ) str[8] = 'w';
    if ( mode & S_IXOTH ) str[9] = 'x';
}

#include	<pwd.h>

char *uid_to_name( uid_t uid )
/* 
 *	returns pointer to username associated with uid, uses getpw()
 */	
{
	struct	passwd *getpwuid(), *pw_ptr;
	static  char numstr[10];

	if ( ( pw_ptr = getpwuid( uid ) ) == NULL ){
		sprintf(numstr,"%d", uid);
		return numstr;
	}
	else
		return pw_ptr->pw_name ;
}

#include	<grp.h>

char *gid_to_name( gid_t gid )
/*
 *	returns pointer to group number gid. used getgrgid(3)
 */
{
	struct group *getgrgid(), *grp_ptr;
	static  char numstr[10];

	if ( ( grp_ptr = getgrgid(gid) ) == NULL ){
		sprintf(numstr,"%d", gid);
		return numstr;
	}
	else
		return grp_ptr->gr_name;
}
