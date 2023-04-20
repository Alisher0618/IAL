/*
* TASK - A one-way linear list
*/

#include "headers/c201.h"

#include <stdio.h>
#include <stdlib.h>

int error_flag;
int solved;

/*
* Prints a notification that an error has occurred.
*/
void List_Error() {
	printf("*ERROR* The program has performed an illegal operation.\n");
	error_flag = TRUE;
}

/*
* Initializes the list before using it for the first time 
* This initialization will never be performed on top of an already initialized one
* list and therefore do not treat this option. 
*/
void List_Init( List *list ) {
	list->activeElement = NULL;
	list->firstElement = NULL;
}

/*
* Clears all elements of the list and returns the list to the state it was in
* after initialization. 
**/
void List_Dispose( List *list ) {
	ListElementPtr lstElem;

	while(list->firstElement != NULL){
		lstElem = list->firstElement;
		list->firstElement = lstElem->nextElement;
		free(lstElem);
	}
}

/*
* Inserts an element with a date value at the beginning of the list.
* In case there is not enough memory for the new element during the malloc operation,
* calls the List_Error() function.
*/
void List_InsertFirst( List *list, int data ) {
	
	ListElementPtr NewElementPtr = (ListElementPtr) malloc( sizeof(struct ListElement));

	if(NewElementPtr == NULL){
		List_Error();
	}
	
	NewElementPtr->data = data;
	NewElementPtr->nextElement = list->firstElement;
	list->firstElement = NewElementPtr;
}

/*
* Sets the activity of the list to its first element.
*/
void List_First( List *list ) {
	list->activeElement = list->firstElement;
}

/*
* Returns the value of the first element of the list through the dataPtr parameter.
* If list is empty, it calls the List_Error() function.
*/
void List_GetFirst( List *list, int *dataPtr ) {
	if(list->firstElement == NULL){
		List_Error();
	}else{
		*dataPtr = list->firstElement->data;
	}
	
}

/*
* Deletes the first element of the list and frees the memory used by it.
* If the interrupted element was active, the activity of the list is lost.
* If the leaf list was empty, nothing happens.
*/
void List_DeleteFirst( List *list ) {
	ListElementPtr fstElem;
	if(list->firstElement != NULL){
		fstElem = list->firstElement;
		list->firstElement = fstElem->nextElement;
		free(fstElem);
	}
}

/*
* Clears the element of the list after the active element and frees the memory used by it.
* If the list is not active or if the last element of the list is active,
* nothing happens.
*/
void List_DeleteAfter( List *list ) {
	ListElementPtr elemPtr;
	if(list->activeElement != NULL){
		if(list->activeElement->nextElement != NULL){
			elemPtr = list->activeElement->nextElement;
			list->activeElement->nextElement = elemPtr->nextElement;
			free(elemPtr);
		}
	}
}

/*
* Inserts an element with a data value after the active element of the list.
* If the list was not active, nothing happens.
* In case there is not enough memory for the new element during the malloc operation,
* calls the List_Error() function.
*/
void List_InsertAfter( List *list, int data ) {
	if(list->activeElement != NULL){
		ListElementPtr NewElemPtr = (ListElementPtr) malloc(sizeof(struct ListElement));
		if(NewElemPtr == NULL){
			List_Error();
		}
		NewElemPtr->data = data;
		NewElemPtr->nextElement = list->activeElement->nextElement;
		list->activeElement->nextElement = NewElemPtr;	
	}
}

/*
* Returns the value of the active element of the list via the dataPtr parameter.
* If the list is not active, it calls the List_Error() function.
*/
void List_GetValue( List *list, int *dataPtr ) {
	if(list->activeElement == NULL){
		List_Error();
	}else{
		*dataPtr = list->activeElement->data;
	}
}

/*
* Overwrites the data of the active list element with the date value.
* If the list is not active, it does nothing.
*/
void List_SetValue( List *list, int data ) {
	if(list->activeElement != NULL){
		list->activeElement->data = data;
	}
}

/*
* Moves the activity to the next element of the list.
* Note that this operation may make the active list inactive.
* If the passed list is not active, the function does nothing.
*/
void List_Next( List *list ) {
	ListElementPtr nextAct;
	if(list->activeElement != NULL){
		nextAct = list->activeElement->nextElement;
		list->activeElement = nextAct;
	}
}

/*
* Returns a non-zero value if list is active, otherwise returns 0.
*/
int List_IsActive( List *list ) {
	return (list->activeElement) ? TRUE : FALSE;
}
