#pragma once

/* Code from https://github.com/Ph-k/Manage-STuDents. Philippos Koumparos (github.com/Ph-k)*/

typedef struct Student Student; //Forward declaration of Student

void initialize(int hashTableSize);
int insert(char* StudentID, char* lastName, char* firstName, int zip, int year, float gpa);
int silentInsert(char* StudentID, char* lastName, char* firstName, int zip, int year, float gpa,int *duplicates);
Student* lookUp(char* studentId);
void top(int num,int year);
double avarage(int year);
char* minimum(int year);
void count();
int number(int year);
void topPostal(int rank,int size);
int delete(char* studentId);
int terminate();
void printSchema();//Function that prints all the data structures and their data (not requested)