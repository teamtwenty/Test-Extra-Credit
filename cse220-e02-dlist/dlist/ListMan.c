/***************************************************************************************************************
 * FILE: ListMan.c
 *
 * DESCRIPTION
 * See comments in ListMan.h
 *
 * AUTHOR INFORMATION
 * Kevin R. Burger [KRB]
 *
 * Mailing Address:
 * Computer Science & Engineering
 * School of Computing, Informatics, and Decision Systems Engineering
 * Arizona State University
 * Tempe, AZ 85287-8809
 *
 * Email: burgerk@asu
 * Web:   http://kevin.floorsoup.com
 *
 * MODIFICATION HISTORY:
 * -------------------------------------------------------------------------------------------------------------
 * 10 Mar 2012 [KRB] Initial revision.
 **************************************************************************************************************/
#include <stdio.h>    /* For fprintf(), fscanf() */
#include <stdlib.h>   /* For exit() */
#include <string.h>   /* For strcmp(), strcpy() */
#include "ListMan.h"
#include "String.h"   /* For streq() */

/*==============================================================================================================
 * Preprocess macro definitions.
 *============================================================================================================*/
#define MAX_LISTS 32

/*==============================================================================================================
 * Typedefs.
 *============================================================================================================*/
/*--------------------------------------------------------------------------------------------------------------
 * This structured data type provides a mapping from linked list name to the linked list pointer. Each name
 * in the testing input file will be seven characters or fewer.
 *------------------------------------------------------------------------------------------------------------*/
typedef struct {
    char   mListName[8];
    DList *mList;
} ListId;

/*
 * The list database is an array of ListID objects. The data member mSize keeps track of how many lists are in
 * the database. It is initialized to 0. Everytime a new list is added to the database (either because of a
 * "create" command or a "copy" command), then mSize is incremented. Everytime a list is destroyed (by a
 * "destroy" command) then mSize is decremented. We allot room for way more lists than we need to (see
 * MAX_LISTS).
 */
typedef struct {
    ListId mLists[MAX_LISTS];
    int    mSize;
} ListDb;

/*==============================================================================================================
 * Static global variable definitions.
 *============================================================================================================*/
static ListDb gListDb;

/*==============================================================================================================
 * Static function declarations (prototypes).
 *============================================================================================================*/
static void ListManCheckSize
    (
    );

/*==============================================================================================================
 * Function definitions.
 *============================================================================================================*/
/*--------------------------------------------------------------------------------------------------------------
 * FUNCT: ListManCheckSize
 * DESCR: Checks to make sure there is room in the list database for a new list. Called from ListManCreateList()
 *------------------------------------------------------------------------------------------------------------*/
static void ListManCheckSize
    (
    )
{
    if (gListDb.mSize < MAX_LISTS) return;
    fprintf(stderr, "Error, number of lists exceeds maximum (%d)\n", MAX_LISTS);
    exit(-1);
}

/*--------------------------------------------------------------------------------------------------------------
 * FUNCT: ListManCreateList
 * DESCR: Called when a new list is being created (either by "create" or "copy").
 *------------------------------------------------------------------------------------------------------------*/
void ListManCreateList
    (
    char  *pListName,
    DList *pNewList
    )
{
    ListManCheckSize();
    int index = gListDb.mSize;
    strcpy(gListDb.mLists[index].mListName, pListName);
    gListDb.mLists[index].mList = pNewList;
    gListDb.mSize++;
}

/*--------------------------------------------------------------------------------------------------------------
 * FUNCT: ListManFreeList
 * DESCR: Called when an existing list is being freed (by the "free" command). Note: This code is very sleazy,
 *        but since the array is small, the time it takes to move each element is minimal.
 *------------------------------------------------------------------------------------------------------------*/
void ListManFreeList
    (
    char *pListName
    )
{
    int i;
    for (i = 0; i < gListDb.mSize; i++) {
        if (streq(gListDb.mLists[i].mListName, pListName)) {
           int j;
           for (j = i; j < gListDb.mSize-1; j++) {
               strcpy(gListDb.mLists[j].mListName, gListDb.mLists[j+1].mListName);
               gListDb.mLists[j].mList = gListDb.mLists[j+1].mList;
           }
           gListDb.mSize--;
           break;
        }
    }
}

/*--------------------------------------------------------------------------------------------------------------
 * FUNCT: ListManGetList
 * DESCR: Given the name of a list in pListName this function finds the list pointer in the database and returns
 *        the list pointer.
 *------------------------------------------------------------------------------------------------------------*/
DList *ListManGetList
    (
    char *pListName
    )
{
    int i;
    for (i = 0; i < gListDb.mSize; i++) {
        if (streq(gListDb.mLists[i].mListName, pListName)) return gListDb.mLists[i].mList;
    }
    return NULL;
}
/*--------------------------------------------------------------------------------------------------------------
 * FUNCT: ListManInit()
 * DESCR: The list database is initialized by setting the mSize data member to 0.
 *------------------------------------------------------------------------------------------------------------*/
void ListManInit
    (
    )
{
    gListDb.mSize = 0;
}
