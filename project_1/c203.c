/*                              
* TASK - A queue of characters in an array                                         
*/

#include "c203.h"

int QUEUE_SIZE = MAX_QUEUE;
int error_flag;
int solved;

/*
* Prints a notification that an error has occurred.
* This function will be called from some further implemented operations.
*/
void Queue_Error( int error_code ) {
	static const char *QERR_STRINGS[MAX_QERR + 1] = {
			"Unknown error",
			"Queue error: ENQUEUE",
			"Queue error: FRONT",
			"Queue error: REMOVE",
			"Queue error: DEQUEUE",
			"Queue error: INIT"
	};

	if (error_code <= 0 || error_code > MAX_QERR)
	{
		error_code = 0;
	}
	printf("%s\n", QERR_STRINGS[error_code]);
	error_flag = 1;
}

/*
* Initialize the queue as follows:
* - set all values in queue->array to '*',
* - set the index to the beginning of the queue to 0,
* - set the index of the first free space to 0 as well.
*/
void Queue_Init( Queue *queue ) {
	if(queue == NULL){
		Queue_Error(QERR_INIT);
	}
	queue->firstIndex = 0;
	queue->freeIndex = 0;

	for(int i = 0; i < QUEUE_SIZE; i++){
		queue->array[i] = '*';
	}
}

/*
* Helper function that returns the index of the next element in the array.
*/
int nextIndex( int index ) {
	return (index + 1) % QUEUE_SIZE; 
}

/*
* Returns non-zero if queue is empty, otherwise returns 0.
*/
int Queue_IsEmpty( const Queue *queue ) {
	return (queue->firstIndex == queue->freeIndex) ? TRUE : FALSE;
}

/*
* Returns a non-zero value if the queue is full, otherwise returns 0.
*/
int Queue_IsFull( const Queue *queue ) {
	return (nextIndex(queue->freeIndex) == queue->firstIndex) ? TRUE : FALSE;
}

/*
* Returns the character from the beginning of the queue via the dataPtr parameter.
* If the queue is empty, handle it by calling Queue_Error(QERR_FRONT).
*/
void Queue_Front( const Queue *queue, char *dataPtr ) {
	if(Queue_IsEmpty(queue)){
		Queue_Error(QERR_FRONT);
	}else{
		*dataPtr = queue->array[queue->firstIndex];	
	}
	

}

/*
* Removes a character from the beginning of the queue. 
* If the queue is empty, handle it by calling Queue_Error(QERR_DEQUEUE).
*/
void Queue_Remove( Queue *queue ) {
	if(Queue_IsEmpty(queue)){
		Queue_Error(QERR_REMOVE);
	}else{
		queue->firstIndex++;
		if(queue->firstIndex == QUEUE_SIZE){
			queue->firstIndex = 0;
		}
	}
}

/*
* Removes a character from the beginning of the queue and returns it via the dataPtr parameter.
* If the queue is empty, handle it by calling Queue_Error(QERR_DEQUEUE).
*/
void Queue_Dequeue( Queue *queue, char *dataPtr ) {
	if(Queue_IsEmpty(queue)){
		Queue_Error(QERR_DEQUEUE);
	}else{	
		Queue_Front(queue, dataPtr);
		Queue_Remove(queue);
	}

}

/*
* Inserts a date character into the queue. 
* If the queue is full, handle it by calling Queue_Error(QERR_DEQUEUE).
*/
void Queue_Enqueue( Queue *queue, char data ) {
	int elem = queue->freeIndex;
	if(Queue_IsFull(queue)){
		Queue_Error(QERR_ENQUEUE);
	}else{	
		queue->array[elem] = data;
		queue->freeIndex = nextIndex(elem);			
	}

}
