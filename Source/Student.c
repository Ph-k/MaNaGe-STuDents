/* Code from https://github.com/Ph-k/MaNaGe-STuDents. Philippos Koumparos (github.com/Ph-k)*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "Student.h"

Student* createStudent(char* StudentID, char* lastName, char* firstName,int postCode, int firstRegistration, float marksMean){

	Student* newStudent = malloc(sizeof(Student)); //Allocating memory for student struct

	newStudent->StudentID = malloc( (strlen(StudentID)+1)*sizeof(char) ); //Allocating memory for stutendID string, according to the given string size
	if(newStudent->StudentID==NULL) return NULL; //Memory allocation failed
	strcpy(newStudent->StudentID,StudentID); //Copying string value

	newStudent->firstName = malloc( (strlen(firstName)+1)*sizeof(char) ); //Same as above
	if(newStudent->firstName==NULL) return NULL; //Memory allocation failed
	strcpy(newStudent->firstName,firstName);

	newStudent->lastName = malloc( (strlen(lastName)+1)*sizeof(char) ); //Same as above
	if(newStudent->lastName==NULL) return NULL; //Memory allocation failed
	strcpy(newStudent->lastName,lastName);

	//Setting interger values
	newStudent->postCode = postCode;

	newStudent->firstRegistration = firstRegistration;

	newStudent->marksMean = marksMean;
		
	return newStudent; //Return student struct
}

void printStudent(Student* student){ //Printing a student data to terminal
	if(student == NULL) return;
	printf("StudentID: %s | first name: %s | last name: %s | zip: %d | fisrt year: %d | gpa: %f\n",
		student->StudentID,student->firstName,student->lastName,student->postCode,student->firstRegistration,
		student->marksMean);
}

int deleteStudent(Student* student){
	if( student == NULL) return 0; //If no student was given, there is nothing to free
	free(student->StudentID);
	free(student->firstName);
	free(student->lastName);
	free(student);
	return 1;
}