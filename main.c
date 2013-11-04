/* Description: Opens and/or creates files, edits it, and saves it in Chordpro format*/
/* Author: Andrew Reyes */
/* Date: 10-28-2013 */
/* Last Updated: 10-31-2013 */

#include "createdir.h"
#include "openfile.h"
#include "input.h"
#include "editor.h"

#include <stdio.h>
#include <errno.h>

FILE *file;
char directory[100];
char filename[100];
char *check;
int r;

int main(void)
{	
	createDir();
	openFile();
	
	if(r == 1)
	{
		return 0;
	}
	
	input();
	editor();
					
	/* int dir; */
	                                                 
	/* dir = mkdir(directory, S_IRWXU); */
	
	/* if(dir == -1)
	{
		int errmsg = errno;
		if(errmsg == EEXIST)
		{
			printf("Directory exists\n\n");
		}
	}
	 */                   
	return 0;
}

	
