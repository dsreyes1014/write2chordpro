/* Description: CREATEDIR.C module 
   Author: Andrew Reyes
   Date Created: 11-01-2013 */
   
#include "createdir.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

extern char directory[100];

void createDir(void)
{	
	char user[30];
	
	char *userVariable = "USER";
	char *homeDir = "home";
	char *programDir = "W2C";
	
	/* Checks environment's user variable */ 
	sprintf(user, "%s", getenv(userVariable));
	
	/* Prints out program directory for directory creation */
	sprintf(directory, "/%s/%s/%s/", homeDir, user, programDir);

	/* Creates directory */
	mkdir(directory, S_IRWXU);
}
