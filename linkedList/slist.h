#ifndef SLIST_H
#define SLIST_H

/*
 * Singly Linked List
 *
 */


/* > Includes *****************************************************************/

#include <stdbool.h>


/* > Defines ******************************************************************/


/* > Type Declarations ********************************************************/


//
// Callback Functions used by the Linked List
//

typedef void (*DataDestroy_t)(void* const);

typedef void (*DataPrint_t)(const void* const);

typedef int (*DataCompare_t)(const void* const, const void* const);

typedef struct SLIST_Callbacks
{
  DataDestroy_t DataDestroy_fp;
  DataPrint_t DataPrint_fp;
  DataCompare_t DataCompare_fp;
} SLIST_Callbacks_t;


//
// Node Definition
//

typedef struct SLIST_Node
{
  void*              Data_p;
  struct SLIST_Node* Next_p;
} SLIST_Node_t;


//
// List Definition
//

typedef struct SLIST_List
{
  SLIST_Callbacks_t Callbacks;
  SLIST_Node_t*     Head_p;
  SLIST_Node_t*     Tail_p;// TODO: MAYBE ADD SOMETHING MORE HERE?!
} SLIST_List_t;


/* > Constant Declarations ****************************************************/


/* > Variable Declarations ****************************************************/


/* > Function Declarations ****************************************************/


/**
 * @brief Creates a new list
 *
 * Creates a singly-linked list.
 *
 * @param[in]     List_p  The list to be initialized.
 * @return        N/A
 *
 ******************************************************************************/
void
SLIST_Create(SLIST_List_t *const List_p);


/**
 * @brief Destroys a list
 *
 * Destroys a list created by SLIST_Create(), freeing the memory allocated
 * for the list structures. The data in the list is freed by the function
 * set by SLIST_SetDestroyFunction(). If no destroy function is set, the
 * data in the nodes is not freed.
 *
 * @param[in]     List_p  The list to be destroyed.
 * @return        N/A
 *
 ******************************************************************************/
void
SLIST_Destroy(SLIST_List_t *const List_p);


/**
 * @brief Checks if the list is empty
 *
 * Checks if the list pointed to by list_p contains any items. Returns true if
 * there are no items in the list.
 *
 * @param[in]     List_p Pointer to the list
 * @return        true/false
 *
 ******************************************************************************/
bool
SLIST_IsEmpty(const SLIST_List_t *const List_p);


/**
 * @brief Calculates the number of elements in the list
 *
 * Determines the number of elements in the linked list and returns that value.
 *
 * @param[in]     List_p Pointer to the list
 * @return        Number of elements
 *
 ******************************************************************************/
int
SLIST_Length(const SLIST_List_t *const List_p);


/**
 * @brief Inserts an item first in the list
 *
 * Inserts the data at the first position of the list.
 *
 * @param[in]     List_p  Pointer to the list pointer
 * @param[in]     Data_p  The data to insert
 * @return        N/A
 *
 ******************************************************************************/
void
SLIST_InsertFirst(SLIST_List_t *const List_p, const void *const Data_p);


/**
 * @brief Inserts an item last in the list
 *
 * Inserts the data at the last position of the list.
 *
 * @param[in]     List_p  Pointer to the list pointer
 * @param[in]     Data_p  The data to insert
 * @return        N/A
 *
 ******************************************************************************/
void
SLIST_InsertLast(SLIST_List_t *const List_p, const void *const Data_p);


/**
 * @brief Removes the first item in the list.
 *
 * Removes the first item in the list.
 * Does not de-allocate the data in the removed node; this data is returned and
 * should be de-allocated manually.
 *
 * @param[in]     List_p  Pointer to the list pointer
 * @return        Pointer to the removed data
 *
 ******************************************************************************/
void*
SLIST_RemoveFirst(SLIST_List_t *const List_p);


/**
 * @brief Removes the last item in the list.
 *
 * Removes the last item in the list.
 * Does not de-allocate the data in the removed node; this data is returned and
 * should be de-allocated manually.
 *
 * @param[in]     List_p  Pointer to the list pointer
 * @return        Pointer to the removed data
 *
 ******************************************************************************/
void*
SLIST_RemoveLast(SLIST_List_t *const List_p);


/**
 * @brief Removes a specific item from the list
 *
 * Removes the first item in the list that is equal to search_data, according
 * to the comparison function.
 * Does not de-allocate the data in the removed node; this data is returned and
 * should be de-allocated manually.
 *
 * @param[in]     List_p        Pointer to the list pointer
 * @param[in]     SearchData_p  The data to remove
 * @return        Pointer to the removed data
 *
 ******************************************************************************/
void*
SLIST_RemoveSpecific(SLIST_List_t *const List_p, const void* const SearchData_p);


/**
 * @brief Print the list
 *
 * Calls the print function for the list for every node in the list.
 * The print function must have been set with SLIST_SetPrintFunction() before
 * calling this function.
 *
 * @param[in]     List_p  Pointer to the list
 * @return        N/A
 *
 ******************************************************************************/
void
SLIST_Print(const SLIST_List_t *const List_p);


/**
 * @brief Sets destroy function for the list
 *
 * Sets a destroy function for the list. The function is used when the list
 * is destroyed by the SLIST_Destroy() function. Then the destroy function
 * is applied to every element in the list.
 *
 * @param[in]     List_p          Pointer to the list
 * @param[in]     DataDestroy_fp  Pointer to the destroy function
 * @return        N/A
 *
 ******************************************************************************/
void
SLIST_SetDestroyFunction(SLIST_List_t *const List_p, DataDestroy_t DataDestroy_fp);


/**
 * @brief Sets print function for the list
 *
 * Sets a print function for the list. The function is applied to every
 * element in the list when the SLIST_Print() function is called.
 *
 * @param[in]     List_p        Pointer to the list
 * @param[in]     DataPrint_fp  Pointer to the print function
 * @return        N/A
 *
 ******************************************************************************/
void
SLIST_SetPrintFunction(SLIST_List_t *const List_p, DataPrint_t DataPrint_fp);


/**
 * @brief Sets comparison function for the list
 *
 * Sets a comparison function for the list. The function is used for removing
 * specific elements in the list, with SLIST_RemoveSpecific().
 * The function shall return:
 *   1  if the first element is bigger than the second,
 *   0  if the elements are equal
 *   -1 if the second element is bigger than the first.
 *
 * @param[in]     List_p          Pointer to the list
 * @param[in]     DataCompare_fp  Pointer to the compare function
 * @return        N/A
 *
 ******************************************************************************/
void
SLIST_SetCompareFunction(SLIST_List_t *const List_p, DataCompare_t DataCompare_fp);


//
// Data Iterator
//

typedef struct Iterator
{
  SLIST_List_t*  List_p;
  SLIST_Node_t** Current_pp;
} Iterator_t;



/**
 * @brief Creates a new iterator
 *
 * Creates an iterator for a singly-linked list.
 *
 * @param[in]     List_p  The list to be iterated.
 * @return        A pointer to an iterator
 *
 ******************************************************************************/
Iterator_t*
ITERATOR_Create(const SLIST_List_t *const List_p);


/**
 * @brief Destroys an iterator
 *
 * Destroys an iterator created by ITERATOR_Create() and frees the memory used
 * by the iterator.
 *
 * @param[in]     Iterator_pp  Pointer to the iterator pointer for the iterator
 * @return        N/A
 *
 ******************************************************************************/
void
ITERATOR_Destroy(Iterator_t** Iterator_pp);


/**
 * @brief Checks if the iterator has more elements
 *
 * Returns true if the next call to ITERATOR_GetNext() would be successful
 * and return the data of a node.
 *
 * @param[in]     Iterator_p  Pointer to the iterator
 * @return        N/A
 *
 ******************************************************************************/
bool
ITERATOR_HasNext(const Iterator_t* const Iterator_p);


/**
 * @brief Returns the data of the next node in the list
 *
 * Returns the data of the current node in the list. Then, the iterator
 * advances in the list and the next node becomes the current one.
 *
 * @param[in]     Iterator_p  Pointer to the iterator
 * @return        A pointer to the data of the current node
 *
 ******************************************************************************/
void*
ITERATOR_GetNext(Iterator_t* const Iterator_p);


/**
 * @brief Resets the iterator
 *
 * Restores the current node in the iterator so it points to the head of
 * the list again.
 *
 * @param[in]     Iterator_p  Pointer to the iterator
 * @return        N/A
 *
 ******************************************************************************/
void
ITERATOR_Reset(Iterator_t* const Iterator_p);


#endif // SLIST_H
