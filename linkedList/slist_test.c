/* > Includes *****************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "CuTest.h"
#include "slist.h"
#include "slist_test.h"


/* > Defines ******************************************************************/


/* > Type Declarations  *******************************************************/


/* > Global Constant Definitions **********************************************/


/* > Global Variable Definitions **********************************************/


/* > Local Constant Definitions ***********************************************/


/* > Local Variable Definitions ***********************************************/


/* > Local Function Declarations **********************************************/

static void
TestCreateDestroyEmptyList(CuTest* Test_p);

static void
TestInsertFirst(CuTest* Test_p);

static void
TestInsertLast(CuTest* Test_p);

static void
TestRemoveFirst(CuTest* Test_p);

static void
TestRemoveLast(CuTest* Test_p);

static void
TestRemoveSpecific(CuTest* Test_p);

static void
TestIterator(CuTest* Test_p);

static CuSuite*
Get_SLIST_Suite(void);


/* > Global Function Definitions **********************************************/
static int DestroyCount = 0;
static int PrintCount = 0;

static void ResetDestroyAndPrintCount()
{
  DestroyCount = 0;
  PrintCount = 0;
}

static void
DataDestroy(void* const Data_p)
{
  DestroyCount++;
  free(Data_p);
}

static void
DataPrint(const void* const Data_p)
{
  char* String_p = (char*)Data_p;
  printf("Data: '%s'\n", String_p);
  PrintCount++;
}

void
Run_SLIST_Tests(void)
{
  CuString* OutputText_p = CuStringNew();
  CuSuite* TestSuite_p = CuSuiteNew();

  CuSuiteAddSuite(TestSuite_p, Get_SLIST_Suite());

  CuSuiteRun(TestSuite_p);
  CuSuiteSummary(TestSuite_p, OutputText_p);
  CuSuiteDetails(TestSuite_p, OutputText_p);

  printf("%s\n", OutputText_p->buffer);

  CuSuiteDelete(TestSuite_p);
  CuStringDelete(OutputText_p);
}


/* > Local Function Definitions ***********************************************/


static void
TestCreateDestroyEmptyList(CuTest* Test_p)
{
  SLIST_List_t List;

  SLIST_Create(&List);

  CuAssertTrue(Test_p, SLIST_IsEmpty(&List) == true);
  CuAssertTrue(Test_p, SLIST_Length(&List) == 0);

  SLIST_Destroy(&List);

  CuAssertTrue(Test_p, SLIST_IsEmpty(&List) == true);
  CuAssertTrue(Test_p, SLIST_Length(&List) == 0);
}


static void
TestInsertFirst(CuTest* Test_p)
{
  SLIST_List_t List;
  char* Strings[] = { "One", "Two", "Three" };

  SLIST_Create(&List);
  SLIST_SetDestroyFunction(&List, DataDestroy);

  for (int i = 0; i < 3; i++)
  {
	int Length = strlen(Strings[i]);
	char* Data_p = malloc(Length + 1);
	strcpy(Data_p, Strings[i]);
	SLIST_InsertFirst(&List, Data_p);
  }

  CuAssertTrue(Test_p, SLIST_IsEmpty(&List) == false);
  CuAssertTrue(Test_p, SLIST_Length(&List) == 3);

  ResetDestroyAndPrintCount();
  SLIST_Destroy(&List);

  CuAssertTrue(Test_p, SLIST_IsEmpty(&List) == true);
  CuAssertTrue(Test_p, SLIST_Length(&List) == 0);
}


static void
TestInsertLast(CuTest* Test_p)
{
  SLIST_List_t List;
  char* Strings[] = { "One", "Two", "Three" };

  SLIST_Create(&List);
  SLIST_SetDestroyFunction(&List, DataDestroy);

  for (int i = 0; i < 3; i++)
  {
	int Length = strlen(Strings[i]);
	char* Data_p = malloc(Length + 1);
	strcpy(Data_p, Strings[i]);
	SLIST_InsertLast(&List, Data_p);
  }

  CuAssertTrue(Test_p, SLIST_IsEmpty(&List) == false);
  CuAssertTrue(Test_p, SLIST_Length(&List) == 3);

  ResetDestroyAndPrintCount();
  SLIST_Destroy(&List);

  CuAssertTrue(Test_p, SLIST_IsEmpty(&List) == true);
  CuAssertTrue(Test_p, SLIST_Length(&List) == 0);
}


static void
TestRemoveFirst(CuTest* Test_p)
{
  SLIST_List_t List;
  int Data[] = { 1, 2, 3};
  void* RemovedData_p;

  SLIST_Create(&List);

  SLIST_InsertFirst(&List, &Data[0]);
  SLIST_InsertFirst(&List, &Data[1]);
  SLIST_InsertFirst(&List, &Data[2]);

  RemovedData_p = SLIST_RemoveFirst(&List);
  CuAssertIntEquals(Test_p, 3, *(int*)RemovedData_p);
  CuAssertTrue(Test_p, SLIST_IsEmpty(&List) == false);
  CuAssertTrue(Test_p, SLIST_Length(&List) == 2);

  RemovedData_p = SLIST_RemoveFirst(&List);
  CuAssertIntEquals(Test_p, 2, *(int*)RemovedData_p);
  CuAssertTrue(Test_p, SLIST_IsEmpty(&List) == false);
  CuAssertTrue(Test_p, SLIST_Length(&List) == 1);

  RemovedData_p = SLIST_RemoveFirst(&List);
  CuAssertIntEquals(Test_p, 1, *(int*)RemovedData_p);
  CuAssertTrue(Test_p, SLIST_IsEmpty(&List) == true);
  CuAssertTrue(Test_p, SLIST_Length(&List) == 0);

  SLIST_Destroy(&List);
}


static void
TestRemoveLast(CuTest* Test_p)
{
  SLIST_List_t List;
  int Data[] = { 1, 2, 3};
  void* RemovedData_p;

  SLIST_Create(&List);

  SLIST_InsertFirst(&List, &Data[0]);
  SLIST_InsertFirst(&List, &Data[1]);
  SLIST_InsertFirst(&List, &Data[2]);

  RemovedData_p = SLIST_RemoveLast(&List);
  CuAssertIntEquals(Test_p, 1, *(int*)RemovedData_p);
  CuAssertTrue(Test_p, SLIST_IsEmpty(&List) == false);
  CuAssertTrue(Test_p, SLIST_Length(&List) == 2);

  RemovedData_p = SLIST_RemoveLast(&List);
  CuAssertIntEquals(Test_p, 2, *(int*)RemovedData_p);
  CuAssertTrue(Test_p, SLIST_IsEmpty(&List) == false);
  CuAssertTrue(Test_p, SLIST_Length(&List) == 1);

  RemovedData_p = SLIST_RemoveLast(&List);
  CuAssertIntEquals(Test_p, 3, *(int*)RemovedData_p);
  CuAssertTrue(Test_p, SLIST_IsEmpty(&List) == true);
  CuAssertTrue(Test_p, SLIST_Length(&List) == 0);

  SLIST_Destroy(&List);
}

static void
TestInsertMalloc(CuTest* Test_p)
{
  SLIST_List_t List;
  char* Strings[] = { "One", "Two", "Three" };

  SLIST_Create(&List);
  SLIST_SetDestroyFunction(&List, DataDestroy);
  SLIST_SetPrintFunction(&List, DataPrint);

  for (int i = 0; i < 3; i++)
  {
    int Length = strlen(Strings[i]);
    char* Data_p = malloc(Length + 1);
    strcpy(Data_p, Strings[i]);

    SLIST_InsertLast(&List, Data_p);
  }
  CuAssertTrue(Test_p, SLIST_IsEmpty(&List) == false);
  CuAssertTrue(Test_p, SLIST_Length(&List) == 3);

  SLIST_Print(&List);
  CuAssertIntEquals(Test_p, 3, PrintCount);
  ResetDestroyAndPrintCount();
  SLIST_Destroy(&List);
  CuAssertIntEquals(Test_p, 3, DestroyCount);
}


static int
DataCompare(const void* const Data1_p, const void* const Data2_p)
{
  return strcmp(Data1_p, Data2_p);
}


static void
TestRemoveSpecific(CuTest* Test_p)
{
  SLIST_List_t List;
  char* Strings[] = { "One", "Two", "Three" };

  SLIST_Create(&List);
  SLIST_SetDestroyFunction(&List, DataDestroy);
  SLIST_SetCompareFunction(&List, DataCompare);

  for (int i = 0; i < 3; i++)
  {
    int Length = strlen(Strings[i]);
    char* Data_p = malloc(Length + 1);
    strcpy(Data_p, Strings[i]);

    SLIST_InsertLast(&List, Data_p);
  }
  CuAssertTrue(Test_p, SLIST_IsEmpty(&List) == false);
  CuAssertTrue(Test_p, SLIST_Length(&List) == 3);

  // Item not in list
  char* Ten_p = SLIST_RemoveSpecific(&List, "Ten");
  CuAssertStrEquals(Test_p, NULL, Ten_p);
  CuAssertTrue(Test_p, SLIST_Length(&List) == 3);

  // Item in the middle
  char* Two_p = SLIST_RemoveSpecific(&List, "Two");
  CuAssertStrEquals(Test_p, "Two", Two_p);
  CuAssertTrue(Test_p, SLIST_Length(&List) == 2);

  // Last item
  char* Three_p = SLIST_RemoveSpecific(&List, "Three");
  CuAssertStrEquals(Test_p, "Three", Three_p);
  CuAssertTrue(Test_p, SLIST_Length(&List) == 1);

  // First item
  char* One_p = SLIST_RemoveSpecific(&List, "One");
  CuAssertStrEquals(Test_p, "One", One_p);
  CuAssertTrue(Test_p, SLIST_Length(&List) == 0);

  SLIST_Destroy(&List);
}


static void
TestIterator(CuTest* Test_p)
{
  SLIST_List_t List;
  int Data[] = { 1, 2, 3};

  SLIST_Create(&List);

  SLIST_InsertFirst(&List, &Data[0]);
  SLIST_InsertFirst(&List, &Data[1]);
  SLIST_InsertFirst(&List, &Data[2]);

  Iterator_t* It_p = ITERATOR_Create(&List);
  int Expected = 3;
  while (ITERATOR_HasNext(It_p))
  {
    int Number = *(int*)ITERATOR_GetNext(It_p);
    CuAssertIntEquals(Test_p, Expected, Number);
    Expected--;
  }

  ITERATOR_Reset(It_p);
  Expected = 3;
  while (ITERATOR_HasNext(It_p))
  {
    int Number = *(int*)ITERATOR_GetNext(It_p);
    CuAssertIntEquals(Test_p, Expected, Number);
    Expected--;
  }

  ITERATOR_Destroy(&It_p);
  SLIST_Destroy(&List);
}


static CuSuite*
Get_SLIST_Suite(void)
{
  CuSuite* Suite_p = CuSuiteNew();

  SUITE_ADD_TEST(Suite_p, TestCreateDestroyEmptyList);
  SUITE_ADD_TEST(Suite_p, TestInsertFirst);
  SUITE_ADD_TEST(Suite_p, TestInsertLast);
  SUITE_ADD_TEST(Suite_p, TestRemoveFirst);
  SUITE_ADD_TEST(Suite_p, TestRemoveLast);
  SUITE_ADD_TEST(Suite_p, TestInsertMalloc);
  SUITE_ADD_TEST(Suite_p, TestRemoveSpecific);
  SUITE_ADD_TEST(Suite_p, TestIterator);

  return Suite_p;
}

