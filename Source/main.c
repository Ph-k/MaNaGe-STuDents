/* Code from https://github.com/Ph-k/Manage-STuDents. Philippos Koumparos (github.com/Ph-k)*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Controller.h"
#include "fileReader.h"

int main(int argc, char *argv[]){
	
	//Default program parameters
	int hashTableSize=300000;
	size_t maxInputStingSize = 50;
	
	char *inputFile=NULL,*configFile=NULL;
	
	//Reading arguments from console
	for(int i=1; i<argc; i++){
		if( strcmp(argv[i],"-i") == 0 ){
			inputFile = argv[i+1];
		}
		if( strcmp(argv[i],"-c") == 0){
			configFile = argv[i+1];
		}
		i++;
	}
	
	if (configFile != NULL){//Configuring program parameters if an according file was given
		if (configInitialization(configFile,&hashTableSize,&maxInputStingSize) == -1){
			printf("Error opening file '%s'\n",configFile);
		} else printf("HashTable size set to %d. And maximum input is %zu characters\n",hashTableSize,maxInputStingSize);
	}
	
	initialize(hashTableSize); //Initializing program structures
	
	if(inputFile != NULL)//Initializing program data if according file was given
		if (fileInitialization(inputFile) == -1){
			printf("Error opening file '%s'\n",inputFile);
		}
	
	int execution = 1, zip, year, num;
	float gpa;
	char command='\0',*string,*studentID,*lastName,*firstName,*inputBuffer = malloc(sizeof(char) * maxInputStingSize);

	memset(inputBuffer,0,maxInputStingSize);
	
	while( execution == 1 ){
		
		printf(">");
		getline(&inputBuffer,&maxInputStingSize,stdin);//Reading user input
		
		string = strtok(inputBuffer, " ");//Getting first argument of user input
		command = string[0];//The first letter is enough to understand the requested command
		
		switch(command){
			case 'i'://Insert
				
				studentID = strtok(NULL, " "); 
				
				lastName = strtok(NULL, " "); 
				
				firstName = strtok(NULL, " "); 
				
				if(studentID==NULL || lastName==NULL || firstName==NULL) break;
				
				string = strtok(NULL, " "); 
				if(string==NULL) break;
				zip = atoi(string);
				
				string = strtok(NULL, " "); 
				if(string==NULL) break;
				year = atoi(string);
				
				string = strtok(NULL, " "); 
				if(string==NULL) break;
				gpa = atof(string);
				//If all the data were typed, they are inserted to the data structure using the Controller.c function (more there)
				insert(studentID,lastName,firstName,zip,year,gpa);
				break;
				
			case 'l'://Look up a student if the data was typed correclty using the Controller.c function
				studentID = strtok(NULL, " ");
				if(studentID==NULL) break;
				strtok(studentID, "\n");
				
				lookUp(studentID);
				break;
				
			case 'd'://Deleting student
				studentID = strtok(NULL, " "); 
				if(studentID==NULL) break;
				strtok(studentID, "\n");
				
				delete(studentID);
				break;
			
			case 'n'://Number of students in a year
				string = strtok(NULL, " ");
				if(string==NULL) break;
				
				number(atoi(string));
				break;
				
			case 't'://Top n students of a year
				string = strtok(NULL, " ");
				if(string==NULL) break;
				num = atoi(string);
				
				string = strtok(NULL, " ");
				if(string==NULL) break;
				year = atoi(string);
				
				top(num,year);
				break;
				
			case 'a'://Avarage gpa of a year
				string = strtok(NULL, " ");
				if(string==NULL) break;
				
				avarage(atoi(string));
				break;
				
			case 'm'://Students with the minumun gpa of a year
				string = strtok(NULL, " ");
				if(string==NULL) break;
				
				minimum(atoi(string));
				break;
				
			case 'c'://Printing the count of students for each year
				count();
				break;
				
			case 'p'://Finding rankTH postal code
				string = strtok(NULL, " ");
				if(string==NULL) break;
				
				/*The second argument is the size an arrey used in controller.c
				default size is half the size of the hash table but can be expanded if needed
				more about that on Controller.c function topPosta()l. And on LinkedList.c functions extendArrey() and postalCodesFill()*/
				topPostal(atoi(string),hashTableSize/2);
				break;

			case 'e'://Terminating the program
				execution =  0;//By breaking the execution loop;
				break;
			
			default:
				printf("Unvalid command!\n");
			
		}
		
		memset(inputBuffer,0,maxInputStingSize);//Clearing buffer from previously red data
	}
	
	free(inputBuffer);
	
	terminate();//Freeing all the memory the data structures used
	return 0;
}
