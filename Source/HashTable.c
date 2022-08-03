/* Code from https://github.com/Ph-k/MaNaGe-STuDents. Philippos Koumparos (github.com/Ph-k)*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Student.h"
#include "HashTable.h"

hashTable* newHashTable(unsigned int size){
	unsigned int i; 

	hashTable* hashT = malloc(sizeof(hashTable)); //Allocating hashtable structure
	
	if(hashT==NULL) return NULL; //if the above memory allocation was not successful 
	
	hashT->size = size; //Initializing hashtable size
	hashT->table = malloc(sizeof(hashNode*) * size); //Allocating table of (size) pointers to hashNodes

	for(i=0; i<hashT->size; i++){
		hashT->table[i]=NULL; //Initializing the empty hash table
	}

	return hashT; //Returning the memory location of the hash table
}

unsigned int h(char* k,unsigned int size){ //Hash function
	unsigned int i, hash = 5381; //The hash is initialized as the lenght of the key logigal or with a prime number

	for (i=0; i<strlen(k); i++){
		//Each character in the key string characters are used along with some logical operations in order to create the hash
		hash ^= k[i] * 31;
		hash ^= hash << 7;
	}

	return hash%size; //(hash)mod(size) is used to not superpass the size of the hash table
}

int HashInsert(hashTable* hashT, Student* newStudent){
	hashNode** hashCell = &(hashT->table[ h(newStudent->StudentID, hashT->size) ]); //& needed since the cell record might need to be modified
	
	while(*hashCell != NULL){//If another student exist in this cell, the list of the cell is traversed untill the end
		if(strcmp((*hashCell)->student->StudentID,newStudent->StudentID)==0) return -1;//If the key (studentID) exist in the hash table, the student is not inserted
		hashCell = &((*hashCell)->next);
	}

	if(*hashCell == NULL){
		(*hashCell) = malloc(sizeof(hashNode)); //Allocating memory for the new student record
		(*hashCell)->student = newStudent; //Initializing student information
		(*hashCell)->next = NULL;
		return 1; //Successfull insertion
	}
	
	return 0;

}

Student* hashFind(hashTable* hashT,char *studentId){
	hashNode* hashCell = (hashT->table[h(studentId, hashT->size)]);	
	
	while( hashCell!=NULL && strcmp(hashCell->student->StudentID,studentId)!=0 ){//If there are collisions at this cell 
		hashCell = hashCell->next; //The record is searched in the list
	}
	
	return (hashCell != NULL) ? hashCell->student : NULL; //If the record was found, it's memory location is returned. Otherwise NULL
}

void printhash(hashTable* hashT){ //Function that prints the hash table and its data (not requested)
	hashNode* hashCell;
	
	printf("-----------------------------------\n");
	
	for(int i=0; i<hashT->size; i++ ){
		hashCell = hashT->table[i];
		printf("%d. ",i);
		while( hashCell !=NULL ){
			printf("[%s]-> ",hashCell->student->StudentID);
			hashCell = hashCell->next;
		}
		
		printf("NULL\n");
	}
	
	printf("-----------------------------------\n");
}

int hashDelete(hashTable* hashT,char *studentId){
	hashNode **hashCell = &(hashT->table[h(studentId, hashT->size)]); //& since modification might be needed
	hashNode *prevCell = *hashCell, *cellToBeDeleted;
	
	if((*hashCell) == NULL) return -1; //Hash table is empty case

	if(strcmp( (*hashCell)->student->StudentID,studentId)==0 ){ //If there are no collisions, or the student is found at the beginning of the list
		cellToBeDeleted = (*hashCell);
		(*hashCell) = (*hashCell)->next; //The value of the cell is set to the next student record (NULL if none)
		deleteStudent(cellToBeDeleted->student); //Memory of the student record is freed
		free(cellToBeDeleted); //Memory of the hashnode is freed
		return 1;
	}
	
	prevCell = (*hashCell); //If the student was not found first
	cellToBeDeleted = (*hashCell);
	while( cellToBeDeleted!=NULL && strcmp(cellToBeDeleted->student->StudentID,studentId)!=0 ){//It's record is searched along the list
		prevCell = cellToBeDeleted;
		cellToBeDeleted = cellToBeDeleted->next;
	}
	
	if(cellToBeDeleted == NULL) return -1; //If his record is not found, according error code is returned
	
	//If the record was found
	prevCell->next = cellToBeDeleted->next; //As above the next record takes it's place
	deleteStudent(cellToBeDeleted->student); //Memory of student is freed
	free(cellToBeDeleted); //Memory of hashnode is freed
	return 1;
	
}

int destroyHashTable(hashTable* hashT){
	hashNode *hashCell,*cellToBeDeleted;
	
	for(int i=0; i<hashT->size; i++ ){ //For all the cells in the hash table
		hashCell = hashT->table[i]; 
		
		while( hashCell !=NULL ){ //And each record that might be in a list form
			//All the momory is freed
			deleteStudent(hashCell->student); 
			cellToBeDeleted = hashCell;			
			hashCell = hashCell->next;
			free(cellToBeDeleted);
		}
	}
	
	//In the end
	free(hashT->table); //The memory of the table of the hash table is freed
	free(hashT); //And the hashtable structure
	return 1;
}