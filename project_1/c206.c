/*  
* TASK - A doubly linked linear list
*/

#include "c206.h"

int error_flag;
int solved;

/**
* Prints a notification that an error has occurred.
*/
void DLL_Error() {
	printf("*ERROR* The program has performed an illegal operation.\n");
	error_flag = TRUE;
}

/**
* Initializes the list before using it for the first time
* This initialization will never be performed on top of an already initialized list
*/
void DLL_Init( DLList *list ) {
	list->firstElement = NULL;
	list->activeElement = NULL;
	list->lastElement = NULL;
}

/**
* Clears all elements of the list and returns the list to the state it was in after initialization.
*/
void DLL_Dispose( DLList *list ) {
	DLLElementPtr lstElem;
	
	while(list->firstElement != NULL){
		lstElem = list->firstElement;
		if(list->firstElement != list->lastElement){
			list->firstElement = lstElem->nextElement;
			free(lstElem);
		}else{
			list->lastElement = NULL;
		}
		
	}
}

/**
* Inserts a new element at the beginning of the list.
* In case there is not enough memory for the new element during the malloc operation,
* calls the DLL_Error() function.
*/
void DLL_InsertFirst( DLList *list, int data ) {
	DLLElementPtr newElem = (DLLElementPtr) malloc(sizeof(struct DLLElement));

	if(newElem == NULL){
		DLL_Error();
	}
	newElem->nextElement = list->firstElement;
	newElem->previousElement = NULL;	
	newElem->data = data;

	if(list->firstElement != NULL){
		list->firstElement->previousElement = newElem;
	}else{					
		list->lastElement = newElem;
	}
	list->firstElement = newElem;

}

/**
* Inserts a new element at the end of the list (symmetric operation to DLL_InsertFirst).
* In case there is not enough memory for the new element during the malloc operation,
* calls the DLL_Error() function.
*/
void DLL_InsertLast( DLList *list, int data ) {
	DLLElementPtr newElem = (DLLElementPtr) malloc(sizeof(struct DLLElement));

	if(newElem == NULL){
		DLL_Error();
	}

	newElem->nextElement = NULL;
	newElem->previousElement = list->lastElement;	
	newElem->data = data;

	if(list->lastElement != NULL){ 
		list->lastElement->nextElement = newElem;
	}else{					
		list->firstElement = newElem;
	}
	list->lastElement = newElem;
}

/**
* Sets the first element of the list as active.
*/
void DLL_First( DLList *list ) {
	list->activeElement = list->firstElement;
}

/**
* Sets the last element of the list as active. 
*/
void DLL_Last( DLList *list ) {
	list->activeElement = list->lastElement;
}

/**
* Returns the value of the first element of the list through the dataPtr parameter.
* If list is empty, calls DLL_Error() function.
*/
void DLL_GetFirst( DLList *list, int *dataPtr ) {
	if(list->firstElement == NULL){
		DLL_Error();
	}else{
		*dataPtr = list->firstElement->data;
	}
}

/**
* Returns the value of the last element of the list through the dataPtr parameter.
* If list is empty, calls DLL_Error() function.
*/
void DLL_GetLast( DLList *list, int *dataPtr ) {
	if(list->lastElement == NULL){
		DLL_Error();
	}else{
		*dataPtr = list->lastElement->data;
	}
}

/**
* Clears the first element of the list.
* If the first element was active, the activity is lost.
* If the list was empty, nothing happens.
*/
void DLL_DeleteFirst( DLList *list ) {
	DLLElementPtr delFstPtr;
	if(list->firstElement != NULL){
		delFstPtr = list->firstElement;
		if(list->activeElement == list->firstElement){
			list->activeElement = NULL;
		}
		else if(list->firstElement == list->lastElement){
			list->firstElement = NULL;
			list->lastElement = NULL;
		}else{
			list->firstElement = list->firstElement->nextElement;
			list->firstElement->previousElement = NULL;	
		}	
		free(delFstPtr);		
	}
}

/**
* Clears the last element of the list.
* If the first element was active, the activity is lost.
* If the list was empty, nothing happens.
 */
void DLL_DeleteLast( DLList *list ) {
	DLLElementPtr delLastPtr;
	if(list->lastElement != NULL){
		delLastPtr = list->lastElement;
		if(list->activeElement == list->lastElement){
			list->activeElement = NULL;
		}
		else if(list->lastElement == list->firstElement){
			list->firstElement = NULL;
			list->lastElement = NULL;
		}else{
			list->lastElement = list->lastElement->previousElement;
			list->lastElement->nextElement = NULL;

		}
		free(delLastPtr);		
	}
}

/**
* Clears the list element after the active element.
* If list is inactive or if the element is active
* the last element of the list, nothing happens.
*/
void DLL_DeleteAfter( DLList *list ) {
	if(list->activeElement != NULL){
		if(list->activeElement->nextElement != NULL){
			DLLElementPtr delElem;
			delElem = list->activeElement->nextElement;
			list->activeElement->nextElement = delElem->nextElement;

			if(delElem == list->lastElement){
				list->lastElement = list->activeElement;
			}else{
				delElem->nextElement->previousElement = list->activeElement;
			}
			
			free(delElem);
		}
	}
}

/**
* Clears the list element before the active element.
* If list is inactive or if the element is active
* the last element of the list, nothing happens.
*/
void DLL_DeleteBefore( DLList *list ) {
	if(list->activeElement != NULL){
		if(list->activeElement->previousElement != NULL){
			DLLElementPtr delElem;
			delElem = list->activeElement->previousElement;
			list->activeElement->previousElement = delElem->previousElement;

			if(delElem == list->firstElement){
				list->firstElement = list->activeElement;
			}else{
				delElem->previousElement->nextElement = list->activeElement;
			}
			
			free(delElem);
		}
	}
}

/**
* Inserts an element after the active element of the list.
* If list was not active, nothing happens.
* In case there is not enough memory for the new element during the malloc operation,
* calls the DLL_Error() function.
*/
void DLL_InsertAfter( DLList *list, int data ) {
	DLLElementPtr newElem = (DLLElementPtr) malloc(sizeof(struct DLLElement));

	if(newElem == NULL){
		DLL_Error();
	}

	newElem->nextElement = list->activeElement->nextElement;
	newElem->previousElement = list->activeElement;
	newElem->data = data;
	
	if(list->activeElement->nextElement != NULL){
		list->activeElement->nextElement = newElem;
		newElem->nextElement->previousElement = newElem;
	}else{											
		list->lastElement = newElem;
		newElem->nextElement = NULL;
		list->activeElement->nextElement = newElem;
	}



}

/**
* Inserts an element before the active element of the list.
* If the list was not active, nothing happens.
* In case there is not enough memory for the new element during the malloc operation,
* calls the DLL_Error() function.
*/
void DLL_InsertBefore( DLList *list, int data ) {
	DLLElementPtr newElem = (DLLElementPtr) malloc(sizeof(struct DLLElement));

	if(newElem == NULL){
		DLL_Error();
	}

	newElem->nextElement = list->activeElement;
	newElem->previousElement = list->activeElement->previousElement;
	newElem->data = data;
	
	if(list->activeElement->previousElement != NULL){	
		list->activeElement->previousElement = newElem;
		list->activeElement->previousElement->nextElement = newElem;
	}else{										
		list->firstElement = newElem;
		newElem->previousElement = NULL;
		list->activeElement->previousElement = newElem;
	}
}

/**
* Returns the value of the active element of the list via the dataPtr parameter.
* If the list is not active, it calls the DLL_Error() function.
*/
void DLL_GetValue( DLList *list, int *dataPtr ) {
	if(list->activeElement == NULL){
		DLL_Error();
	}else{
		*dataPtr = list->activeElement->data;
	}
}

/**
* Overwrites the contents of the active element of the list.
* If list is not active, does nothing.
*/
void DLL_SetValue( DLList *list, int data ) {
	if(list->activeElement != NULL){
		list->activeElement->data = data;
	}
}

/**
* Moves the activity to the next element of the list.
* Does nothing if the list is not active.
* Note that the list becomes inactive when active on the last element.
*/
void DLL_Next( DLList *list ) {
	if(list->activeElement != NULL){
		DLLElementPtr moveAct;
		moveAct = list->activeElement->nextElement;
		list->activeElement = moveAct;
	}
}


/**
* Moves the activity to the previous element of the list.
* Does nothing if the list is not active.
* Note that the list becomes inactive when active on the last element.
*/
void DLL_Previous( DLList *list ) {
	if(list->activeElement != NULL){
		DLLElementPtr moveAct;
		moveAct = list->activeElement->previousElement;
		list->activeElement = moveAct;
	}
}

/**
* Returns a non-zero value if list is active, otherwise returns 0.
*/
int DLL_IsActive( DLList *list ) {
	return (list->activeElement) ? TRUE : FALSE;
}
