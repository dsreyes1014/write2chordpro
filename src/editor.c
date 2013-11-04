/* Description: EDITOR.C module
 * Author: Andrew Reyes
 * Date Created: 11-02-2013 */
 
#include "editor.h"

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

extern char *check;
extern char directory[];

void editor(void)
{
	char editor[35];
	char pathProgram[100] = "/usr/bin/";
	
	printf("\n");
	printf("Enter choice of editor to input lyrics and chords: ");
	
	/* Prompts for editor input then deletes null terminator */
	check = fgets(editor, 34, stdin);
	check[strlen(editor) - 1] = '\0';
	
	if(strlen(editor) <= 0)
	{
	}
	else 
	{		
		printf("Opening editor...\n");
		
		int pid = fork();
		int status = 0;
		
		if(pid == 0)
		{		

			char programPath[100]; 
		
			char *path = programPath;
			char *arg0 = editor;
			char *arg1 = directory;

			sprintf(programPath, "%s%s", pathProgram, editor); 
	
			execl(path, arg0, arg1, NULL);
		}
		else 
			{
				wait(&status);
			}
	}
	
	printf("\n");
	printf("Thank you for using Write 2 Chordpro!!!\n\n");
}