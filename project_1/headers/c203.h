#ifndef C203_H
#define C203_H

#include <stdio.h>

#define FALSE 0
#define TRUE 1
#define MAX_QUEUE 50

extern int QUEUE_SIZE;

extern int error_flag;
extern int solved;

/** Celkový počet možných chyb. */
#define MAX_QERR    5
/** Chyba při Queue_Enqueue. */
#define QERR_ENQUEUE     1
/** Chyba při Queue_Front. */
#define QERR_FRONT  2
/** Chyba při Queue_Remove. */
#define QERR_REMOVE 3
/** Chyba při Queue_Dequeue. */
#define QERR_DEQUEUE    4
/** Chyba při malloc. */
#define QERR_INIT   5

/** ADT fronta implementovaná ve statickém poli. */
typedef struct {
	/** Pole pro uložení hodnot. */
	char array[MAX_QUEUE];
	/** Index prvního prvku. */
	int firstIndex;
	/** Index první volné pozice. */
	int freeIndex;
} Queue;

void Queue_Error( int error_code );

void Queue_Init( Queue *queue );

int Queue_IsEmpty( const Queue *queue );

int Queue_IsFull( const Queue *queue );

void Queue_Front( const Queue *queue, char *dataPtr );

void Queue_Remove( Queue *queue );

void Queue_Dequeue( Queue *queue, char *dataPtr );

void Queue_Enqueue( Queue *queue, char data );

#endif

/* Konec hlavičkového souboru c203.h */
