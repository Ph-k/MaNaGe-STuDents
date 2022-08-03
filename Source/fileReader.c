
/* Code from https://github.com/Ph-k/Manage-STuDents. Philippos Koumparos (github.com/Ph-k)*/

#include <stdlib.h>
#include <stdio.h>
#include "Controller.h"

int fileInitialization(char* filename){ //Function inserting students from a given file
	FILE *fp = fopen(filename,"r"); //Opening file
	
	if (fp == NULL) return -1; //If file does not exist error code is returned
	
	printf("Initializing program from file: %s\n",filename);
	
	char Id[50], lastName[50], firstName[50];

	int post, year,duplicates;
	float gpa;

	while( fscanf(fp, "%s", Id) != EOF ){ //While we have not reached the end of file (reading studentID which should be the first information to be given)

		fscanf(fp, "%s", lastName); //After the studentID the last name of the student should be in the text file

		fscanf(fp, "%s", firstName); //Accordingly the rest information of the studen is red

		fscanf(fp, "%d", &post);

		fscanf(fp, "%d", &year);

		fscanf(fp, "%f", &gpa);

		silentInsert(Id,lastName,firstName,post,year,gpa,&duplicates); //Inserting the new student (more on what silentInsert does, on controller.c)
	}
	printf("Initialization completed, %d duplicated records found and not inserted\n",duplicates);
	fclose(fp); //Closing file
	return 0;
}

int configInitialization(char* filename,int *hashTableSize,size_t *maxInputStingSize){ //Function is initializing the program variables from given file
	FILE *fp = fopen(filename,"r");//Opening File

	if (fp == NULL) return -1; //If file does not exist error code is returned
	
	printf("Configuration filename: %s\n",filename);
	
	int temp;
	
	//The size of the hash table, and the maximum number of characters that can be typed as input are red at their respective positions
	if (fscanf(fp, "%d", &temp) != EOF) *hashTableSize = temp;
	
	if (fscanf(fp, "%d", &temp) != EOF) *maxInputStingSize = temp;
	
	fclose(fp);
	return 0;
}