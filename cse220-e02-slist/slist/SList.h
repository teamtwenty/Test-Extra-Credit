/***************************************************************************************************************
 * FILE: SList.h
 *
 * DESCRIPTION
 * Declaration of a singly-linked list data structure. The data stored in each node is an int. See SListNode.h.
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
 * 29 Feb 2012 [KRB] Initial revision.
 **************************************************************************************************************/
#ifndef __SLIST_H__
#define __SLIST_H__

#include <stdio.h>      /* For FILE */
#include "SListNode.h"
#include "Types.h"

/*==============================================================================================================
 * Defines a type for the SList data structure.
 *============================================================================================================*/
typedef struct {
    SListNode *mHead;  /* Pointer to first node in the list. */
    SListNode *mTail;  /* Pointer to last node in the list.  */
    int        mSize;  /* Number of nodes in list.           */
} SList;

/*==============================================================================================================
 * Global function declarations. See function comments in SList.c
 *============================================================================================================*/
extern SList *SListAlloc
    (
    );

extern SList *SListAppend
    (
    SList *pList,
    int    pData
    );

extern void SListDebugPrint
    (
    FILE *stream,
    SList *pList
    );

extern SListNode *SListFind
    (
    SList *pList,
    int    pData
    );

extern SList *SListFree
    (
    SList *pList
    );

extern SListNode *SListGetHead
    (
    SList *pList
    );

extern int SListGetSize
    (
    SList *pList
    );

extern SListNode *SListGetTail
    (
    SList *pList
    );

extern SList *SListInsert
    (
    SList *pList,
    int    pIndex,
    int    pData
);

extern bool SListIsEmpty
    (
    SList *pList
);

extern SList *SListRemove
    (
    SList *pList,
    int    pData
    );

extern SList *SListSetHead
    (
    SList     *pList,
    SListNode *pHead
    );

extern SList *SListSetSize
    (
    SList *pList,
    int    pSize
    );

extern SList *SListSetTail
    (
    SList     *pList,
    SListNode *pTail
    );

#endif
