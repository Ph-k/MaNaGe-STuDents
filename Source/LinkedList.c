
/* Code from https://github.com/Ph-k/Manage-STuDents. Philippos Koumparos (github.com/Ph-k)*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "LinkedList.h"
#include "Student.h"

listNode* createList(){
	return NULL;//A new empty list is just a pointer to NULL
}

listNode* listInsert(listNode** head,Student* student){//Function inserting student to inverted index struct
	int studentYears = student->firstRegistration; //Getting the students year
	studentNode* newStudent;
	
	if( *head == NULL ){ //CASE 1. The list is empty
		*head = malloc(sizeof(listNode)); //Creating a new node to hold the list of the students along for a given year
		(*head)->year = studentYears; //The yaer of the list node is the same as the years of their students
		(*head)->next = NULL; //Only one node (this node) is in the list
		
		(*head)->students =  malloc(sizeof(studentNode)); //Allocating memory for the student node for the list of students

		newStudent = (*head)->students; //The list of students for this year starts from this student
		newStudent->student = student; //Student information is "saved" with the use of a pointer to the student
		newStudent->next = NULL; //This is the only student for this given year
		
		return *head;
	}
	
	listNode *temp = *head, *preTemp = *head, *newYear;
	int yearExist = 0;
	
	while (temp != NULL){//CASE 2. the year of the student exist in the list
		if(temp->year == studentYears){//Seacrhing for the year in the year list
			
			yearExist = 1;
			
			newStudent = malloc(sizeof(studentNode)); //Allocating memory for student list node
			newStudent->student = student; //Saving pointer to student
			newStudent->next = temp->students; //Inserting student in the top of the student list
			temp->students = newStudent;
			
			return *head;
		}
		preTemp = temp;
		temp = temp->next;
	}

	if(yearExist == 0){ //CASE 3 .The year was not in the list, this student is the first of this year
		preTemp->next = malloc(sizeof(listNode)); //preTemp is last node of the year list, new year will be inserted after it
		newYear = preTemp->next; //this new year node location
		
		newYear->year = studentYears; //Initializing the year of the node
		newYear->next = NULL;
		
		newYear->students =  malloc(sizeof(studentNode)); //Memory for the firt student

		newStudent = newYear->students; //This is the only student, and his student node is inserted
		newStudent->student = student;
		newStudent->next = NULL;
		return *head;
	}
	
	return NULL; //If none of the above cases where executed, something unespected happend, NULL is returned as error code
}

void printList(listNode* head){ //Function that prints the inverted index structure and its data (not requested)
	studentNode* Snode;
	
	while(head!=NULL){
		printf("%d: ",head->year);
		Snode = head->students;
		while(Snode != NULL){
			printf("[%s]-> ", Snode->student->StudentID);
			Snode = Snode->next;
		}
		printf("\n");
		head = head->next;
	}
	
}

int listDelete(listNode** head,char *studentId){
	listNode *listNodeIndex = *head,*listNodePrev = *head;
	studentNode *Snode, *SnodePrev;
	
	while(listNodeIndex!=NULL){//Searching for the year node of the given studentID
		Snode = listNodeIndex->students;
		
		if( strcmp(Snode->student->StudentID,studentId)==0 ){ //CASE 1, the student is the first student in the student list of the year
			if( Snode->next == NULL){//If this is the only student, the year should be deleted as well
				free(Snode);//Deleting node for student (the deletion of the student itself is handled from the hash table)
				
				if(listNodeIndex == *head){//If this the first year node, the head value of the list should change
					*head = listNodeIndex->next;//Pointing to the next year
				}else{
					listNodePrev->next = listNodeIndex->next;//Otherwise, the previous year node, points to the next
				}
				
				free(listNodeIndex);//Year node memory is freed
				return 1;
			}else{//The student was not the only one
				listNodeIndex->students = Snode->next;//So the first student in the year node is the next one
				free(Snode);//Deletion of student node
				return 1;
			}
		}
		
		SnodePrev = Snode;
		while(Snode != NULL){//CASE 2, the student was not the first and now is searched depper in the year list
			if( strcmp(Snode->student->StudentID,studentId)==0 ){//If his ID is found depper in the list
				SnodePrev->next = Snode->next; //The list sequence is fixed
				free(Snode); //And the memory he has allocaded is freed
				return 1;
			}
			SnodePrev = Snode;
			Snode = Snode->next;
		}
		listNodePrev = listNodeIndex;
		listNodeIndex = listNodeIndex->next;
	}
	
	return -1;//If none of the above cases where executed, the student does not exist
}

int countYear(listNode* head, int year){
	int counter=0;
	studentNode* Snode;
	
	while(head!=NULL){//For each year node
		if(head->year==year){//The requested year is searched
			Snode = head->students;
			while(Snode != NULL){//For each student in the year
				counter++;//The counter is incrimented by one
				Snode = Snode->next;
			}
			return counter;//And after all the students have been counted, the sum is returned
		}
		head = head->next;
	}
	
	return -1;//Otherwise the year did not exist
}

int mergeSort(studentNode** studentList){//This mergeSort is modified to sort a student list of a given year (used in yearSort line 232)
	
	if( (*studentList)==NULL || (*studentList)->next==NULL ) return 0; //At least two nodes can be sorted
	
	studentNode *first = (*studentList)->next,*second = *studentList,*sortedIndex,*sorted = NULL,*middle;
	
	//Finding the middle node, using a pointer (middle) that traverses only one node for every two node the (first) node has traversed
	int i=0;
	while(first->next!=NULL){
		first=first->next;
		if(i==2){
			second = second->next;
			i=0;
		}else i++;
	}
	
	middle = second->next;//The second that which will be sorted
	second->next = NULL;//The first half
	
	//Recursively sorting each half
	if( mergeSort(studentList)!=0 ) return -1;
	if( mergeSort(&middle)!=0 ) return -1;

	if(*studentList!=NULL && middle!=NULL){
		first=*studentList;
		second=middle;
	}else if(*studentList==NULL && middle!=NULL){//If only the second half has nodes, there is nothing to merge, the first sorted half is returned
		*studentList=middle;
		return 0;
	}else if(*studentList!=NULL && middle==NULL){//Same if only the first half has nodes
		return 0;
	}

	//Ohtherwise the first node og teh sorted list must be the bigger one
	if(first->student->marksMean > second->student->marksMean){ 
		sorted = first;
		first = first->next;
		sortedIndex = sorted;
	}else if(first->student->marksMean < second->student->marksMean){
		sorted = second;
		second = second->next;
		sortedIndex = sorted;
	}else{//If both nodes have the same value, they should be both inserted at the front
		sorted = first;
		first = first->next;
		sorted->next=second;
		second = second->next;
		sortedIndex = sorted->next;
	}
	
	while(first!=NULL && second!=NULL){//Merging the rest of the halfs
		//By inserting the node with the biggest gpa in the merge list
		if(first->student->marksMean > second->student->marksMean){
			sortedIndex->next=first;
			first = first->next;
		}else if(first->student->marksMean < second->student->marksMean){
			sortedIndex->next=second;
			second = second->next;
		}else{//And if they happen to have the same value, they are both inserted
			sortedIndex->next=first;
			first = first->next;
			
			sortedIndex=sortedIndex->next;
			
			sortedIndex->next=second;
			second = second->next;
		}
		sortedIndex=sortedIndex->next;
	}
	
	while(first!=NULL){//If there are remaining nodes in the first half
		//They are inserted as they are, since they are sorted, and there are not more nodes on the other half to compare
		sortedIndex->next=first;
		first = first->next;
		sortedIndex=sortedIndex->next;
	}
	
	//Same as above (line 214) but for the case of the second half
	while(second!=NULL){
		sortedIndex->next=second;
		second = second->next;
		sortedIndex=sortedIndex->next;
	}
	
	*studentList=sorted;//Returning the merge sorted list
	return 0;
}

studentNode* yearSort(listNode *head,int year){//This function returns the student list of the requested year, sorted
	int sortedFlag = 0;
	studentNode *Snode;
	
	while(head!=NULL){
		if(head->year==year){//If the year is found
			//It is first checked if the student list is sorted
			Snode = head->students;
			while(Snode!= NULL){
				if(Snode->next == NULL) break; //If one, it is sorted
				
				if(Snode->student->marksMean < Snode->next->student->marksMean){
					sortedFlag = 1;//If at least one student is found to violate the decreased sorted list, the list is not sorted 
					break;
				}
				Snode = Snode->next;
			}
			
			if(sortedFlag==0){//If the student list is sorted 
				return Snode = head->students; //It is returned as it is
			}else{ //Otherwise it is sorted, using the above custom mergesort
				if (mergeSort(&(head->students)) == 0) 
					return head->students; //If mergesort succesfully sorted the list, it is returned
				else 
					return NULL;
			}
			
		}
		head = head->next;
	}
	
	return NULL;//If the year was not found, NULL is returned
}

double yearAvarage(listNode *head,int year){
	double sum = 0.0;
	int counter = 0;
	studentNode *Snode;
	
	while(head!=NULL){//To calculate the avarage of a given year
		if(head->year==year){//It needs first to be found
			
			Snode = head->students;
			while(Snode!= NULL){//And then all the sum of the marks of the students is calculated, along with their count
				sum += Snode->student->marksMean;
				counter++;
				Snode = Snode->next;
			}
			
			//Note: there is always at least one student (no empty years), so counter>=1
			return sum/counter; //the avarage is sumOfGpa's/TheirCount
			
		}
		head = head->next;
	}
	
	return -1.0;//If no such year exist, NULL is returned
}

char* yearMinimum(listNode *head,int year){
	studentNode *Snode;
	Student *Smin;
	
	while(head!=NULL){//To calculate the minimum gpa of a given year
		if(head->year==year){//First the year needs to be found
			
			
			Smin = head->students->student;//Then we can consider that the first gpa is also the minimun
			Snode = head->students->next;
			
			while(Snode!= NULL){//For the rest of the students
				if(Snode->student->marksMean < Smin->marksMean){//If there is one found with a smaller gpa
					Smin = Snode->student;//He is our new minumun
				}
				Snode = Snode->next;
			}
		
		
			Snode = head->students;
			
			printf("list(%s,",Smin->StudentID);//We found one student with the smallest gpa, but there might be more with the same, minimum gpa
			
			while(Snode!= NULL){
				if(Snode->student->marksMean == Smin->marksMean && strcmp(Snode->student->StudentID,Smin->StudentID)!=0 ){//Excluding the "saved" minimum
					printf("%s,",Snode->student->StudentID);//All these students are printed
				}
				Snode = Snode->next;
			}
		
			printf(")\n");
			return Smin->StudentID;
			
		}
		head = head->next;
	}
	return NULL;//Null is case of no enroled students
}

int yearsCount(listNode *head){
	int counter;
	studentNode* Snode;
	
	if(head==NULL) return -1;//If there are no students (thus years), NULL is returned
	
	printf("list(");
	
	while(head!=NULL){//For each year
		counter = 0;
		printf("{%d, ",head->year);//The year is printed
		
		Snode = head->students;
		while(Snode != NULL){//And all the students of this year are counted
			counter++;
			Snode = Snode->next;
		}
		printf("%d}",counter);//Then the count of the students is printed
		
		head = head->next;
	}
	
	printf(")\n");
	return 0;
}


//This function takes an arrey, and creates a new one with the same records but double the size
void extendArrey(postCodeStruct **postArrey,int *startIndex,int *endIndex,int *arreySize){
	*arreySize = (*arreySize) * 2; //Doubling the size
	postCodeStruct *newArrey = malloc(*arreySize * sizeof(postArrey));//Allocating memory
	
	for(int i=*startIndex; i<=*endIndex; i++){//Copying values
		newArrey[i].postCode = (*postArrey)[i].postCode;
		newArrey[i].count = (*postArrey)[i].count;
	}
	
	free(*postArrey);//Freeing memory of old small arrey
	*postArrey = newArrey;//setting arrey pointer, to point to the new doubled arrey
}

//Given the inverdex index, it fills the given arrey from startIndex to endIndex with all the postal codes and their respective sums
int postalCodesFill(listNode *head,postCodeStruct **givenPostArrey,int *startIndex,int *endIndex,int *arreySize){
	int searchStart,searchEnd,mid,currentPCode,index,j,fillCase=0,inserted;
	studentNode* Snode;
	postCodeStruct *postArrey = *givenPostArrey;
	
	if(head==NULL) return -2;//If the list is empty, no students are enroled, error code
	if(head->students==NULL) return -1;
		
	while(head!=NULL){//For each year
		
		Snode = head->students;
		while(Snode != NULL){//For all the students in a year
			currentPCode=Snode->student->postCode;
			
			//We place their post code acoordingly (for now we maintain a sorted arrey from the biggest postal code to the smaller)
			switch (fillCase){
				case 0://If there are no posts in the arrey
					postArrey[0].postCode = currentPCode;//The first is inserted in the beggining
					postArrey[0].count = 1; 
					fillCase++;
					break;

				case 1://If there is only one post code...
					if(postArrey[0].postCode!=currentPCode){//...the second post code is inserted if it differs from the first and only one
						if(postArrey[0].postCode >= currentPCode){//After the first one if it smaller
							postArrey[1].postCode = currentPCode;
							postArrey[1].count = 1; 
						}else{//In the beggining if it is bigger from the first one
							postArrey[1].postCode = postArrey[0].postCode;//Shifting the old first
							postArrey[1].count = postArrey[0].count;
							postArrey[0].postCode = currentPCode;//Inserting the new as first 
							postArrey[0].count = 1; 
						}
						
						*endIndex += 1;
						fillCase++;
					}else{//...and the same postal code is given
						postArrey[0].count += 1;//It's sum is incrimented by one
					}
					break;

				//If there are more than 2 post codes we search using binary search since it is fast and we have a sorted to postal codes arrey
				default:
					searchStart = *startIndex;
					searchEnd = *endIndex;
					inserted = 0;
					//Typical binary search algorithm
					while(searchEnd>=searchStart){//binary search
						mid = (searchStart + searchEnd)/2;
						if(postArrey[mid].postCode>currentPCode){
							searchStart=mid+1;//If the post code we search is smaller than the midean one, we search right
						}else if (postArrey[mid].postCode<currentPCode){
							searchEnd=mid-1;//If it is bigger we search left
						}else{//In case we happen to found the postal code (it existed in the arrey) 
							postArrey[mid].count += 1;//We only incriment it's count by one
							inserted = 1;//And note that we find it
							break;
						}
					}
					
					if(inserted == 0){//If the post code was not found, we will insert it while maintaining the sort arrey
						//When binary search failed finding the post code, the mid pointed to were our postal code should be
						if( postArrey[mid].postCode > currentPCode){//If our post code is smaller than the one found
							index = mid + 1; //Our postal code takes the place next to it (more on what index does on line 444)
						}else if( postArrey[mid].postCode < currentPCode ){
							index = mid;//If our postal code is bigger than the one found, it takes it's place
						}
						
						if(*endIndex + 1 >= *arreySize) {//If the arrey does not have cells to fill for the new postal code
							extendArrey(givenPostArrey,startIndex,endIndex,arreySize);//It is extended using a custom function
							postArrey = *givenPostArrey;//The new (extended) post arrey
						}
						
						//The index indicates were our new post should be placed in order to keep our arrey sorted (using the mid from the binsearch)
						for(j=*endIndex+1; j>index; j--){//All the post codes after the index should be shifted in order to maintain their values
							postArrey[j].postCode=postArrey[j-1].postCode;//Shift data
							postArrey[j].count=postArrey[j-1].count;
						}
						postArrey[index].postCode = currentPCode;//After the shift completes, we can place our post code to it's sorted possion
						postArrey[index].count = 1; //And since it's new, we start it's count from one
						
						*endIndex += 1;//One item was inserted to the arrey, and thus the size is incrimented
				
					}
			}
	
			Snode = Snode->next;
		}
		
		
		head = head->next;
	}
	

	return 0;
}

int destroyList(listNode** head){
	listNode *temp = *head, *nodeToDelete;
	studentNode *SnodeToDelete;
	//To destroy the list we only need to free the memory of it's nodes, since the student deletion is handled from the hashtable
	while(temp!=NULL){
		
		studentNode* Snode = temp->students;
		while(Snode != NULL){
			SnodeToDelete = Snode;//Keeping the location of the next student
			Snode = Snode->next;
			free(SnodeToDelete);//Freeing memory of current (student) node
		}
		nodeToDelete = temp;
		temp = temp->next;
		free(nodeToDelete);//Freeing memory of current (year) node
	}
	
	*head = NULL;
	return 1;
}