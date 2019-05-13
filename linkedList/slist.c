/* > Includes *****************************************************************/
#include "slist.h"
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>


/* > Defines ******************************************************************/


/* > Type Declarations  *******************************************************/


/* > Global Constant Definitions **********************************************/


/* > Global Variable Definitions **********************************************/


/* > Local Constant Definitions ***********************************************/


/* > Local Variable Definitions ***********************************************/


/* > Local Function Declarations **********************************************/


/* > Global Function Definitions **********************************************/

void
SLIST_Create(SLIST_List_t *const List_p)

{
  List_p->Head_p = NULL;
  List_p->Tail_p = NULL;
  memset(&List_p->Callbacks, 0, sizeof(SLIST_Callbacks_t));
}

void
SLIST_Destroy(SLIST_List_t *const List_p)
{
  if (List_p->Callbacks.DataDestroy_fp != NULL)
  {
	SLIST_Node_t* destroy_p = List_p->Head_p;
	while (destroy_p != NULL)
	{
	  List_p->Callbacks.DataDestroy_fp(destroy_p->Data_p);
	  destroy_p = destroy_p->Next_p;
	}
  }
  List_p->Head_p = NULL;
  List_p->Tail_p = NULL;
}

bool
SLIST_IsEmpty(const SLIST_List_t *const List_p)
{
  return (List_p->Head_p == NULL);
}

int
SLIST_Length(const SLIST_List_t *const List_p)
{
  int listLength = 0;
  SLIST_Node_t* listIterator_p = List_p->Head_p;

  while (listIterator_p != NULL)
  {
	listIterator_p = listIterator_p->Next_p;
	listLength++;
  }
  return listLength;
}

void
SLIST_InsertFirst(SLIST_List_t *const List_p, const void *const Data_p)
{
  SLIST_Node_t* newNode = malloc(sizeof(SLIST_Node_t));
  newNode->Data_p = (void*)Data_p;

  if (List_p->Head_p == NULL)
  {
   List_p->Head_p = newNode;
   List_p->Tail_p = newNode;
   newNode->Next_p = NULL;
  }
  else
  {
   newNode -> Next_p = List_p -> Head_p;
   List_p -> Head_p = newNode;
  }
}

void
SLIST_InsertLast(SLIST_List_t *const List_p, const void *const Data_p)
{
  SLIST_Node_t* newNode = malloc(sizeof(SLIST_Node_t));
  newNode->Data_p = (void*)Data_p;
  newNode->Next_p = NULL;

  if (List_p->Head_p == NULL)
  {
	List_p->Head_p = newNode;
	List_p->Tail_p = newNode;
  }
  else
  {
    List_p -> Tail_p -> Next_p = newNode;
	List_p -> Tail_p = newNode;
  }
}

void*
SLIST_RemoveFirst(SLIST_List_t *const List_p)
{
  SLIST_Node_t* Remove_p = NULL;

  if (List_p->Head_p->Next_p == NULL)
  {
	Remove_p = List_p->Head_p;
	List_p->Head_p = Remove_p->Next_p;
	List_p->Tail_p = Remove_p->Next_p;
	}
  else
  {
	Remove_p = List_p->Head_p;
	List_p -> Head_p = Remove_p->Next_p;
  }
  void* Data_p = Remove_p->Data_p;
  free(Remove_p);
  return Data_p;
}

void*
SLIST_RemoveLast(SLIST_List_t *const List_p)
{
  void* Data_p = NULL;
  SLIST_Node_t* nodePointer_p = NULL;
  if (List_p->Head_p->Next_p == NULL)
  {
	nodePointer_p = List_p->Head_p;
	List_p->Head_p = NULL;
	List_p->Tail_p = NULL;
  }
  else
  {
    nodePointer_p = List_p->Head_p;
	while (nodePointer_p -> Next_p != List_p -> Tail_p)
	{
	  nodePointer_p = nodePointer_p -> Next_p;
	}
	List_p -> Tail_p = nodePointer_p;
	nodePointer_p = nodePointer_p -> Next_p;
	List_p->Tail_p->Next_p = NULL;
  }
  Data_p = nodePointer_p->Data_p;
  free(nodePointer_p);
  return Data_p;
}

void*
SLIST_RemoveSpecific(SLIST_List_t *const List_p, const void* const SearchData_p)
{
  SLIST_Node_t* currentNode_p = List_p->Head_p;
  SLIST_Node_t* previousNode_p = NULL;

  // Traversing the list to find the node to be deleted
  while (currentNode_p != NULL &&
		 List_p->Callbacks.DataCompare_fp(currentNode_p->Data_p, SearchData_p) != 0)
  {
	previousNode_p = currentNode_p;
	currentNode_p = currentNode_p->Next_p;
  }

  // Check if the node is in the list otherwise return
  if (currentNode_p == NULL)
  {
	return NULL;
  }
  else if (currentNode_p == List_p->Head_p)
  {
	previousNode_p = currentNode_p;
	currentNode_p = currentNode_p->Next_p;
	List_p->Head_p = currentNode_p;
	previousNode_p->Next_p = NULL;
	free(previousNode_p);
  }
  else if (currentNode_p == List_p->Tail_p)
  {
	List_p->Tail_p = previousNode_p;
	previousNode_p->Next_p = NULL;
	free(currentNode_p);
  }
  else
  {
    previousNode_p->Next_p = NULL;
    previousNode_p->Next_p = currentNode_p->Next_p;
    currentNode_p->Next_p = NULL;
    free(currentNode_p);
  }
  return (void*)SearchData_p;
}

void
SLIST_Print(const SLIST_List_t *const List_p)
{
  SLIST_Node_t* print_p = List_p->Head_p;
  while (print_p != NULL)
  {
	List_p->Callbacks.DataPrint_fp(print_p->Data_p);
	print_p = print_p->Next_p;
  }
}

void
SLIST_SetDestroyFunction(SLIST_List_t *const List_p, DataDestroy_t DataDestroy_fp)
{
  List_p->Callbacks.DataDestroy_fp = DataDestroy_fp;
}

void
SLIST_SetPrintFunction(SLIST_List_t *const List_p, DataPrint_t DataPrint_fp)
{
  List_p->Callbacks.DataPrint_fp = DataPrint_fp;
}

void
SLIST_SetCompareFunction(SLIST_List_t *const List_p, DataCompare_t DataCompare_fp)
{
  List_p->Callbacks.DataCompare_fp = DataCompare_fp;
}

//
// ITERATOR
//

Iterator_t*
ITERATOR_Create(const SLIST_List_t *const List_p)
{
  Iterator_t* It_p = malloc(sizeof(Iterator_t));
  It_p->List_p = (SLIST_List_t*)List_p;
  It_p->Current_pp = &It_p->List_p->Head_p;
  return It_p;
}

void
ITERATOR_Destroy(Iterator_t** Iterator_pp)
{
  free(*Iterator_pp);
  *Iterator_pp = NULL;
}

bool
ITERATOR_HasNext(const Iterator_t* const Iterator_p)
{
  return ((*Iterator_p->Current_pp) != NULL);
}

void*
ITERATOR_GetNext(Iterator_t* const Iterator_p)
{
  void* Data_p = (*Iterator_p->Current_pp)->Data_p;
  *Iterator_p->Current_pp = (*Iterator_p->Current_pp)->Next_p;
  return Data_p;
}

void
ITERATOR_Reset(Iterator_t* const Iterator_p)
{
  *Iterator_p->Current_pp = Iterator_p->List_p->Head_p;
}

/* > Local Function Definitions ***********************************************/
