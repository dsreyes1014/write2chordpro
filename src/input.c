/* 
 *  Description: INPUT.C module
 * Author: Andrew Reyes
 * Date Created: 11-01-2013 
 */
 
#include "input.h"

#include <stdio.h>
#include <string.h>

extern char *check;
extern FILE *file;

void input(void)
{
	char title[100];
	char artist[100];
	char genre[100];
	char key[20];
	
	printf("\n");
	printf("Enter title: ");
	
	/* Prompts for title input then deletes null terminator */
	check = fgets(title, 99, stdin);                
	check[strlen(title) - 1] = '\0';                
                                                    

	if(strlen(title) <= 0)
	{
		printf("Already modified\n");
	}
	else
	{
		fprintf(file, "{title: %s}\n", title);  /* Appends title to directory */  
	}                                               
    
	printf("\n");                                                
	printf("Enter name of artist(s): "); 
	
	/* Prompts for artist input then deletes null terminator */
	check = fgets(artist, 99, stdin);               
	check[strlen(artist) - 1] = '\0';               
	                                                
	if(strlen(artist) <= 0)
	{
		printf("Already modified\n");
	}
	else
	{
		fprintf(file, "{subtitle: %s}\n", artist); /* Appends subtitle to directory */  
	}                                               
		
	printf("\n");
	printf("Enter genre: ");
	
	/* Prompts for genre input then deletes null terminator */
	check = fgets(genre, 99, stdin);                
	check[strlen(genre) -1] = '\0';                 
	                                                
	if(strlen(genre) <= 0)
	{
		printf("Already modified\n");
	}
	else
	{
		fprintf(file, "{tags: %s}\n", genre); /* Appends genre to directory */  
	}                                              
	
	printf("\n");
	printf("Enter the musical key of song: ");
	
	/* Prompts for key input then deletes null terminator */
	check = fgets(key, 99, stdin);                
	check[strlen(key) -1] = '\0';                 
	                                                
	if(strlen(key) <= 0)
	{
		printf("Already modified\n");
	}
	else
	{
		fprintf(file, "{key: %s}\n", key); /* Appends key to directory */  
	}
	
	fclose(file);
}