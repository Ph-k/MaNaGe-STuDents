#pragma once

/* Code from https://github.com/Ph-k/MaNaGe-STuDents. Philippos Koumparos (github.com/Ph-k)*/

typedef struct Student Student; //Forward declaration of Student

struct hashNode{ //Value of the cells of the hashtable
	Student* student; //Item (student)
	struct hashNode* next; //Pointer to the next student (in case of collision, else NULL)
};
typedef struct hashNode hashNode;

struct hashTable{ //HashTable sturcture
	struct hashNode** table; //The table
	unsigned int size; //It's size
};
typedef struct hashTable hashTable;

hashTable* newHashTable(unsigned int size); //Fuction that creates the hashtable
int HashInsert(hashTable* hashT, Student* newStudent); //Function inderting student to the hashtable
unsigned int h(char* k,unsigned int size); //Hashing function
int destroyHashTable(hashTable* hashT); //Function that frees the memory that both the hashtable and the student records have allocated
Student* hashFind(hashTable* hashT,char *studentId); //Seaching student in the hashtable
int hashDelete(hashTable* hashT,char *studentId); //Deleting student
void printhash(hashTable* hashT); ////Function that prints the hash table and its data (not requested)