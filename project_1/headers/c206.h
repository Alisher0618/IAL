#include<stdio.h>
#include<stdlib.h>

#define FALSE 0
#define TRUE 1

extern int error_flag;
extern int solved;

/** Prvek dvousměrně vázaného seznamu. */
typedef struct DLLElement {
	/** Užitečná data. */
	int data;
	/** Ukazatel na předcházející prvek seznamu. */
	struct DLLElement *previousElement;
	/** Ukazatel na následující prvek seznamu. */
	struct DLLElement *nextElement;
} *DLLElementPtr;

/** Dvousměrně vázaný seznam. */
typedef struct {
	/** Ukazatel na první prvek seznamu. */
	DLLElementPtr firstElement;
	/** Ukazatel na aktuální prvek seznamu. */
	DLLElementPtr activeElement;
	/** Ukazatel na posledni prvek seznamu. */
	DLLElementPtr lastElement;
} DLList;

void DLL_Init( DLList * );

void DLL_Dispose( DLList * );

void DLL_InsertFirst( DLList *, int );

void DLL_InsertLast( DLList *, int );

void DLL_First( DLList * );

void DLL_Last( DLList * );

void DLL_GetFirst( DLList *, int * );

void DLL_GetLast( DLList *, int * );

void DLL_DeleteFirst( DLList * );

void DLL_DeleteLast( DLList * );

void DLL_DeleteAfter( DLList * );

void DLL_DeleteBefore( DLList * );

void DLL_InsertAfter( DLList *, int );

void DLL_InsertBefore( DLList *, int );

void DLL_GetValue( DLList *, int * );

void DLL_SetValue( DLList *, int );

void DLL_Next( DLList * );

void DLL_Previous( DLList * );

int DLL_IsActive( DLList * );

/* Konec hlavičkového souboru c206.h */
