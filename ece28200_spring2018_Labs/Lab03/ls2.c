/* ls2.c
 *	purpose  list contents of directory or directories
 *	action   if no args, use .  else list files in args
 *	note     uses stat and pwd.h and grp.h 
 *	BUG: try ls2 /tmp  
 */
#include	<stdio.h>
#include	<sys/types.h>
#include	<dirent.h>
#include	<sys/stat.h>
#include        <stdlib.h>

void do_ls(char[],int *,int *, int *);
void dostat(char *, int *, int *);
void show_file_info( char *, struct stat *, int *, int *);
void mode_to_letters( int , char [] );
char *uid_to_name( uid_t );
char *gid_to_name( gid_t );

main(int ac, char *av[])
{
	int* flcnt = (int *) malloc(sizeof(int));
	int* wrcnt = (int *) malloc(sizeof(int));
	int* flgs = (int *) malloc(sizeof(int));
	*flgs = 0;
	int x;
	char buf1[256];
	for(x=0;x<ac;x++)
	{
		if(strcmp(av[x],"--detail") == 0)
		{
			*flgs = 1;
			printf("Current working directory:\n");
			getcwd(buf1, sizeof(buf1));
			printf("%s\n",buf1);
		}
	}
		
	if ( ac == 1 || (ac == 2 && (strcmp(av[1],"--detail") == 0)))
		do_ls( ".",flcnt,flgs,wrcnt);
	else
		while ( --ac ){
			if(strcmp(av[ac],"--detail") != 0)
			{
				printf("%s:\n", *++av );
				do_ls( *av,flcnt,flgs,wrcnt);
			}
		}
	if(*flgs == 1)
	{
		printf("Number of Directories: %d\n",*flcnt);
		printf("Writeable Files: %d\n",*wrcnt);
	}
	free(flcnt);
	free(wrcnt);
	free(flgs);
}

void do_ls( char dirname[],int* flcnt,int* flgs,int* wrcnt )
/*
 *	list files in directory called dirname
 */
{
	int a = 0;
	DIR		*dir_ptr;		/* the directory */
	struct dirent	*direntp;		/* each entry	 */

	if ( ( dir_ptr = opendir( dirname ) ) == NULL )
		fprintf(stderr,"ls1: cannot open %s\n", dirname);
	else
	{
		while ( ( direntp = readdir( dir_ptr ) ) != NULL )
		{
			if(direntp->d_type == DT_DIR)
			{
				(*flcnt)++;
			}
			dostat( direntp->d_name,flgs,wrcnt);
			
		}
		closedir(dir_ptr);
	}
}

void dostat( char *filename, int* flgs,int* wrcnt )
{
	struct stat info;

	if ( stat(filename, &info) == -1 )		/* cannot stat	 */
		perror( filename );			/* say why	 */
	else					/* else show info	 */
		show_file_info( filename, &info,flgs, wrcnt);
}

void show_file_info( char *filename, struct stat *info_p, int* flgs, int* wrcnt )
/*
 * display the info about 'filename'.  The info is stored in struct at *info_p
 */
{ 
	int cuid = getuid();
	int cgid = getgid();
	//printf("UID: %d\n",cuid);
	//printf("GID: %d\n",cgid);
	//printf("%d",info_p->st_uid);
	if((*flgs) == 0)
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
	else
	{
		if( (info_p->st_mode && S_IWUSR && info_p->st_uid == cuid) || (info_p->st_mode && S_IWGRP && info_p->st_gid == cgid) || info_p->st_mode && S_IWOTH )
		{	
			*wrcnt = *wrcnt + 1; 
		}	
	}
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
