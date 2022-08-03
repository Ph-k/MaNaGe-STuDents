#pragma once

/* Code from https://github.com/Ph-k/MaNaGe-STuDents. Philippos Koumparos (github.com/Ph-k)*/

typedef struct Student Student; //Forward declaration of Student
typedef struct postCodeStruct postCodeStruct; //

struct studentNode{
	Student* student;
	struct studentNode* next;
};
typedef struct studentNode studentNode;

//The listnodes represent a given year
struct listNode{
	int year;
	studentNode* students;//And point the list of students of that year
	struct listNode* next;
};
typedef struct listNode listNode;

listNode* createList();//Initializes inverted index data structure
listNode* listInsert(listNode** head,Student* student);//Inserts student as requested in the assignment
int listDelete(listNode** head,char *studentId);
int countYear(listNode* head, int year);
studentNode* yearSort(listNode *head,int year);
double yearAvarage(listNode *head,int year);
char* yearMinimum(listNode *head,int year);
int yearsCount(listNode *head);
int postalCodesFill(listNode *head,postCodeStruct **givenPostArrey,int *startIndex,int *endIndex,int *arreySize);
int destroyList(listNode** head);
void printList(listNode* head);//Function that prints the inverted index structure and its data (not requested)

//This is a cell of a postCodeStruct arrey used in extendArrey and postalCodesFill
struct postCodeStruct{
	int count;
	int postCode;
};
typedef struct postCodeStruct postCodeStruct;