
/* 
File name is linked_list.c
 Purpose: file contains functions for manipulating singly linked list
 
 Revisions
 Doron Nussbaum 2018

 
 
 
 
 Copyright 2018 Doron Nussbaum
 
 */

/******************************************************************/
// INCLUDE 

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "linked_list.h"


/************************************************************************/
// Define 



/************************************************************************/

/*
Purpose: insert a new node into the list as the first element
input
id - id of person
firstName - first name of person
familyName - family name of person

input/output
head - head of linked list

return
A pointer to the node that was allocated.  

NULL - if the operation was not successful

*/

PersonalInfo *insertToList(PersonalInfo **head, unsigned int id, 
        char *firstName, char *familyName)
{
	//Memory allocation
   PersonalInfo *p = NULL;
   p = (PersonalInfo *) malloc(sizeof(PersonalInfo));
   if(p == NULL) return NULL;
   
   //Setting data
   strncpy(p->firstName, firstName, 15);
   strncpy(p->familyName, familyName, 15);
   p-> id = id;
   //Making new node and updating
   p->next = *head;
   *head = p;
   return p;


}


/************************************************************************/
/*
Purpose: insert a new node into the list after the given node  

Input
node - the node after which the new node must be added to the list
id - id of person
firstName - first name of person
familyName - family name of person


return
A pointer to the node that was allocated.  

NULL - if the operation was not successful

*/


PersonalInfo *insertAfter(PersonalInfo *node, unsigned int id, char *firstName, char *familyName)
{
	//Allocating memory 
	PersonalInfo *p = NULL;
	p = (PersonalInfo *) malloc(sizeof(PersonalInfo));
	if(p==NULL) return NULL;
	
	//Setting data
	p->id = id;
	strncpy(p->firstName, firstName, 15);
	strncpy(p->familyName, familyName, 15);
	
	//Inserting node after
	p->next=node->next;
	node->next = p;
	return p;

}

/************************************************************************/
/*
Purpose: create a new node and insert it into the end of the list
Input
head - the head of the list
id - id of person
firstName - first name of person
familyName - family name of person


return
A pointer to the node that was allocated.  

NULL - if the operation was not successful

*/


PersonalInfo *insertLast(PersonalInfo **head, unsigned int id, char *firstName, char *familyName)
{
	//Allocating Memory
	PersonalInfo *p = NULL;
	p = (PersonalInfo *)malloc(sizeof(PersonalInfo));
	PersonalInfo *temp = NULL;
	temp = *head;
	if(p==NULL) return NULL; //Check if empty

	//Setting data
	p->id = id;
	strncpy(p->firstName, firstName, 15);
	strncpy(p->familyName, familyName, 15);
	
	//Checking if size is 0
	if(listSize(temp) == 0){ 
		*head = p;
		return p;
	}
	//Finding last node
	while(temp->next != NULL){
		temp = temp->next;	
	}
	//Create new node
	temp->next = p;
	p->next = NULL;
	return p;

}


/************************************************************************/
/*
Purpose: search for the first node with the matching firstName
Input
head - the head of the list
firstName - first name of person

return
a pointer to the node that was found.
NULL - if no node was found or list empty

*/


PersonalInfo *searchByName(PersonalInfo *head, char *firstName)
{
	//Check if empty
	if(head == NULL) return NULL;
	
	//Search by name
	while(head!= NULL){
		if(strcmp(head->firstName, firstName) ==0){
			return head;
		}
		head = head->next;
	}
	return NULL;

}

/************************************************************************/
/*
Purpose: search for the first node with the matching id
Input
head - the head of the list
id - id of person person

return
a pointer to the node that was allocated.  

NULL - if no node was found or list empty 

*/


PersonalInfo *searchById(PersonalInfo *head, unsigned int id)
{
	//Checks if empty then searches by ID
	while(head!= NULL){
		if(head->id == id) return head;
		head = head->next;
	}
	return NULL;
    
}

/***************************************************************/

/*
Purpose: delete the first node from the list
Input
head - the head of the list

output
head - the head of the list
firstName - first name of delted record
familyName - family name of deleted recrod
id - id of deleted record


return

0 if node was deleted
1 if node was not deleted or list is empty

*/


int deleteFromList(PersonalInfo **head, unsigned int *id,
	char *firstName, char *familyName)

{
	//If empty, return 1
    if(*head == NULL) return 1;
	PersonalInfo *del = NULL;
	del = *head;
	//Setting data
	strncpy(firstName, del->firstName, 15);
	strncpy(familyName, del->familyName, 15);
	*id = del->id;
	//Update head and free old node
	*head = del->next;
	free(del);
	
	return 0;

}


/***************************************************************/

/*
Purpose: delete the last node from the list
Input
head - the head of the list

output
head - the head of the list
firstName - first name of delted record
familyName - family name of deleted recrod
id - id of deleted record


return

0 if node was deleted  
1 if node was not deleted or list is empty 

*/


int deleteLast(PersonalInfo **head, unsigned int *id,
                char *firstName, char *familyName)

{
	//If list is empty return 1
    if(*head == NULL) return 1;
	PersonalInfo *p = NULL;
	p = *head;
	
	//Setting data
	strncpy(firstName, p->firstName, 15);
	strncpy(familyName, p->familyName, 15);
	*id = p->id;

	if(listSize(*head) == 1){
		*head = NULL;
		free(p);
		return 0;
	}
	while(p->next->next !=NULL){
		p = p->next;
	}
	free(p->next);
	p->next = NULL;
	return 0;

}



/************************************************************************/

/*
Purpose: delete the record after the given node 
Input
node - a node in the list

output
firstName - first name of delted record
familyName - family name of deleted recrod
id - id of deleted record


return
0 if node was deleted 
1 if node was not deleted (either input node is NULL or input node was the lastnode in the list)

*/



int deleteAfter(PersonalInfo *node, unsigned int *id,
                char *firstName, char *familyName)

{
    if (node == NULL || node->next == NULL) return 1;
	PersonalInfo *del = NULL;
	del = node->next;
	node->next = del->next;
	
	//Setting data
	strncpy(firstName, del->firstName, 15);
	strncpy(familyName, del->familyName, 15);
	*id = del->id;
	
	free(del); //Free up old node space
	return 0; 

}

/************************************************************************/

/*
Purpose: delete the first node with the matching firstName
Input
head - the head of the list
firstName - first name of person

output
head - the head of the list
firstName - first name of deleted record
familyName - family name of deleted recrod
id - id of deleted record


return
0  if node was deleted
1 if node was not found (e.g., list is empty, no such node exists)

*/


int deleteNodeByName(PersonalInfo **head, char *firstName,
	char *familyName, unsigned int *id)
{
	//If list is empty, return 1
	if (*head == NULL) return 1;
	PersonalInfo *del = NULL;
	del = *head;
	PersonalInfo *p = NULL;
	
	while(del != NULL && strcmp(del->firstName, firstName) != 0){
			p = del;
			del = del->next;
	}
	if(del == NULL) return 1; //If we can't find node
	if(*head == del){ //If we found node
		*head = del->next;
		*id = del->id;
		strncpy(firstName, del->firstName, 15);
		strncpy(familyName, del->familyName, 15);
		free(del);
		return 0;
	}
	//Setting
	strncpy(firstName, del->firstName, 15);
	strncpy(familyName, del->familyName, 15);
	*id = del->id;
	p->next = del->next;
	free(del);
	return 0;


}
/************************************************************************/
/*
Purpose: deletes all nodes from the list
input/output
head - the head of the list


*/


void deleteList(PersonalInfo **head)
{
	PersonalInfo *pres = NULL;
	PersonalInfo *next = NULL;
	//Go through the list and set next node, free and iterate
	while(pres != NULL) {
		next = pres->next;
		free(pres);
		pres = next;
	}
	*head = NULL; 


}



/************************************************************************/
/*
Purpose: prints the fields of a node
input:
node - a pointer to a given node

*/


void printNode(PersonalInfo *node)
{
	printf("%-20s %-20s %7d \n",node->firstName, node->familyName, node->id);

}


/************************************************************************/
/*
Purpose: prints all the records in the list

input
head - the head of the list
*/


void printList(PersonalInfo *head)
{
	PersonalInfo *pres= NULL;
	pres = head;
	//If node isn't empty, print and iterate
	while (pres != NULL) {
		printNode(pres);
		pres = pres->next;
	} 



}

/************************************************************************/
/*
Purpose: counts the number of nodes in the list
input
head - the head of the list

return 
the number of nodes in the list

*/


int listSize(PersonalInfo *head)
{
	int count = 0;
	//If node isn't empty, add 1 to count and move
	while(head!= NULL){
		count++;
		head = head->next;
	}
	return count;



}

/************************************************************************/
/*
Purpose: counts the number of nodes in the list with a matching firstName
input
head - the head of the list

return 
the number of nodes in the list that match the firstName


*/


int countRecords(PersonalInfo *head, char *firstName)
{
	int count = 0;
	if(head == NULL) return 0; //if list is empty

	while(head != NULL){
		if(strcmp(head->firstName, firstName) == 0) count++;
		head = head->next;
	}
	return count;


}




/************************************************************************/
/*

Purpose: removes all duplicates records from the list.  Duplicate records are determined by their first name. 
You can assume that the listed is sorted by first name.

input
head - the head of the  list



*/




void removeDuplicates(PersonalInfo *head)
{
	if (head == NULL) return;

	PersonalInfo *p = NULL;
	p = head;
	PersonalInfo *curr = NULL;

	while (p->next != NULL){
		if (strcmp(p->firstName, p->next->firstName) == 0){
			curr = p->next->next;
			free(p->next);
			p->next = curr;
		}
		else{
			p = p->next;
		}
	}
}

