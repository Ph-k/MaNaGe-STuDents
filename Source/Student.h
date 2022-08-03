#pragma once

/* Code from https://github.com/Ph-k/Manage-STuDents. Philippos Koumparos (github.com/Ph-k)*/

struct Student{ //Struct representing all the required information for a student
	char* StudentID;
	char* firstName;
	char* lastName;
	char* town;
	int postCode;
	int firstRegistration;
	float marksMean;
};

typedef struct Student Student;

Student* createStudent(char* StudentID, char* lastName, char* firstName, int postCode, int firstRegistration, float marksMean);
int deleteStudent(Student* student);
void printStudent(Student* student);