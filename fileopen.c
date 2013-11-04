/* Description: CreateFile module handles the files created when using w2c
 * Author: Andrew Reyes
 * Date Created: 11-01-2013 */
 
#include "fileopen.h"
#include "createdir.h"
 
#include <stdio.h>
#include <string.h>

void fileOpen(void)
{
	char filename[100];
	char input3[4];
	
	extern char *check;
	extern char directory[100];
	extern FILE *file;
	
	printf("\n");	
	printf("Please enter filename: ");
	
	/* Prompts for filename input then deletes null terminator */
	check = fgets(filename, 99, stdin);             
	check[strlen(filename) - 1] = '\0';	           
							
	/* If no input, program will terminate */
	if(strlen(filename) <= 0)				
	{							
		printf("\n");                               
		printf("Nothing was entered...\n");         
		printf("Program terminating\n");
		printf("Thank you for using Write 2 Chordpro!!!\n\n");            
		return 0;	
	} 
	/* If there is input, add extension to filename, then 
	filename to directory. Use directory from here */
	else                                            
	{                                               
		strcat(filename, EXTENSION);     
		strcat(directory, filename);              
	}                                               
		
	file = fopen(directory, "r");
	
	if(file == NULL)
	{
	}
	else  
	{						
		printf("File exists. Continue?(y or n) ");
		
		check = fgets(input3, 3, stdin);
		check[strlen(input3) - 1] = '\0';
	}	
	if(strcmp(input3, "y") == 0 || strcmp(input3, "Y") == 0)
	{
	}
	else if(strcmp(input3, "n") == 0 || strcmp(input3, "N") == 0)
	{
		printf("\n");
		printf("Thank you for using Write 2 Chordpro!!!\n\n");
		return 0;
	}
	
	/* Creates file */
	file = fopen(directory, "a+");
}