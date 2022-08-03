
/* Code from https://github.com/Ph-k/MaNaGe-STuDents. Philippos Koumparos (github.com/Ph-k)*/

#include <stdio.h>
#include <stdlib.h>
#include "HashTable.h"
#include "Student.h"
#include "LinkedList.h"


static hashTable* hashT;
static listNode* list;
static int initialized = 0;

void initialize(int hashTableSize){
	//To initialize the program, it's two data structures are initialized
	hashT = newHashTable(hashTableSize);
	list = createList();
	initialized = 1;
}

int insert(char* StudentID, char* lastName, char* firstName, int zip, int year, float gpa){
	if(initialized == 0) return -1; //If the data structures have not been initialized, error code is returned
	
	Student* newStudent = createStudent(StudentID,lastName,firstName,zip,year,gpa);//Student is created, according to given data

	if(HashInsert(hashT,newStudent) != -1){//If the insertion to the hash table was succesfull, (the student is not a duplicate)
		listInsert(&list,newStudent); //The student is also inserted to the inverted index
		printf("Student %s inserted\n",StudentID);
		return 1;
	}else{//Otherwise
		printf("Student %s exists\n",StudentID);
		deleteStudent(newStudent);//The student was a duplicate and was not inserted, the previous allocated memory for the student memory is freed
		return -1;
	}
	
}


//silentInsert works the exact same way as the above insert function, but it does not print messages. It only counts duplicates
int silentInsert(char* StudentID, char* lastName, char* firstName, int zip, int year, float gpa,int *duplicates){
	static int dup = 0; //Static int remains the same along all the calls of the function
	Student* newStudent = createStudent(StudentID,lastName,firstName,zip,year,gpa);

	if(HashInsert(hashT,newStudent) != -1){
		listInsert(&list,newStudent);
		*duplicates = dup; //Duplicate count is copied to the variable the caller function indicated 
		return 1;
	}else{
		dup++; //HashInsert failed due to duplicate studentID, the counter is incremented
		deleteStudent(newStudent);
		*duplicates = dup; //Duplicate count is copied to the variable the caller function indicated 
		return -1;
	}
}

Student* lookUp(char* studentId){
	Student* student = hashFind(hashT,studentId);//The student is searched using the hashtable
	if(student != NULL){
		printStudent(student);//If the student was found in the hashtable, his information is printed with a student.c function
	}else{
		printf("Student %s does not exist\n",studentId);
	}
	return student;
}

int delete(char* studentId){
	if(hashFind(hashT,studentId) != NULL){//In order to delete a student
		listDelete(&list,studentId);//He has first to be removed from the inverted index structure
		hashDelete(hashT,studentId);//And after from the hashtable (since the hashtable also free the momory of the students)
		printf("Record %s deleted\n",studentId);
		return 1;
	}else{//If the student was not found though, error message is printed
		printf("Student %s does not exist\n",studentId);
		return -1;
	}
}

int number(int year){
	int studentCount = countYear(list,year);//LinkedList.c function counts the students of a given year
	
	if(studentCount != -1){//countYear returns -1 if there are no students for the given year
		printf("%d student%c in %d\n",studentCount,(studentCount>1)? 's':' ' ,year);
		return studentCount;
	}else{
		printf("No students enrolled in %d\n",year);
		return 0;
	}
}

void top(int num,int year){
	studentNode *yearTopList = yearSort(list,year),*last; //returns a sorted list of students from the "best" to the "worst" 
	
	if(yearTopList!=NULL){
		printf("list(");
		for(int i=0; i<num; i++){ //For the number of the requested students
			printf("%s",yearTopList->student->StudentID); //Their ID's are printed
			last = yearTopList; //The current/printed student is saved
			yearTopList = yearTopList->next; //The pointer moves to the next
			if(yearTopList==NULL){
				break; // The itteration ends if there are no more students to be printed
			}
			if(num-1!=i) printf(", ");
		}
		
		yearTopList = last->next; //From the last printed student
		while(yearTopList!=NULL){
			if(yearTopList->student->marksMean!=last->student->marksMean) break; //While there are students with the same gpa
			//they must be printed since they are all the numTH best students
			printf(", %s",yearTopList->student->StudentID);
			yearTopList = yearTopList->next;
		}
		
		printf(")\n");	
	}else{
		printf("No students enrolled in %d\n",year);
	}
}

double avarage(int year){
	double result = yearAvarage(list,year);//Function returns the avarage gpa of all the students of a given year
	if(result != -1.0){//If no students are enrolled, yearAvarage returns -1.0 (since no avarage gpa can take that value)
		printf("%f\n",result);
	}else{
		printf("No students enrolled in %d\n",year);
	}
	return result;
}

char* minimum(int year){
	char* result = yearMinimum(list,year);//The function prints all the students of a given year, who have the (same) smallest gpa
	if(result == NULL){//If no students are enrolled in that year yearMinimum does not print anything and returns NULL
		printf("No students enrolled in %d\n",year);
	}
	return result;
}

void count(){
	if( yearsCount(list) == -1){ //yearsCount prints the sum of students that are active in each years
		printf("No students are enrolled\n");//yearsCount returns -1 and prints nothing if no students are enrolled
	}
}

int cmpfunc (const void * a, const void * b) {//Function that compares to postalcodes based on their given count
   return (*(postCodeStruct*)b).count - (*(postCodeStruct*)a).count;
}

void topPostal(int rank,int size){
	if(!(rank>0)) {printf("Rank must be a positive integer\n"); return;}
	int i,j,startIndex=0,endIndex=0,arreySize;
	arreySize = (size<2)? 2 : size;//arreySize is the initial size of the posts arrey (must be bigger than 2)
	postCodeStruct *postArrey = malloc(arreySize * sizeof(postArrey));
	
	if(postalCodesFill(list,&postArrey,&startIndex,&endIndex,&arreySize) == 0){//postalCodesFill returns an arrey with all post codes and their counts (more on LinkedList.c)

		qsort(postArrey,endIndex+1,sizeof(postCodeStruct),cmpfunc); //This arrey is sorted according to the counts of the post codes (bigger to smaller) 
		
		j=0;
		//Calculating the location of the requested rank
		for(i=startIndex; i<endIndex; i++){
			if(postArrey[i].count!=postArrey[i+1].count) j++; //A new rank location is discovered in the array, when two consequent cells have a different count of students
			if(j==rank) break;
		}
		if(i==endIndex) j++; //The last cell does not have a different cell in count after it, so in this case the rank is increased
		if(j!=rank){
			printf("No such rank, maximum rank is: %d\n",j);
		}else{//If the requested rank existed
			printf("list(%d",postArrey[i].postCode); //The rankTH post code is printed
			
			//Along with the postal codes that have the same count, thus belong to the same rank
			//Τhese same rank posts are either left or right of that one found rank
			for(j=i+1; j<=endIndex; j++){//Searching and printing right
				if(postArrey[j].count != postArrey[i].count) break;
				printf(", %d",postArrey[j].postCode);
			}
			for(j=i-1; j>=startIndex; j--){//Searching and printing left
				if(postArrey[j].count != postArrey[i].count) break;
				printf(", %d",postArrey[j].postCode);
			}
			printf(") %s %d most popular\n", (j == i-1)? "is" : "are", rank);
		}

	}else{
		printf("No students are enrolled\n");
	}
	
	free(postArrey);
}

void printSchema(){ //Function that prints all the data structures and their data (not requested)
	printf("hash table:\n");
	printhash(hashT);
	printf("inverted index:\n");
	printList(list);
}

int terminate(){//To terminate the program
	printf("exit program\n");
	//The memory from all data structures needs to be freed
	destroyList(&list);
	destroyHashTable(hashT);
	return 1;
}