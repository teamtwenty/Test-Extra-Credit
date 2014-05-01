/***************************************************************************************************************
 * FILE: DList.h
 *
 * DESCRIPTION
 * Declaration of a doubly-linked list data structure. The data stored in each node is an int. See DListNode.h.
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
#ifndef __DLIST_H__
#define __DLIST_H__

#include <stdio.h>      /* For FILE */
#include "DListNode.h"  /* For DListNode structure */
#include "Types.h"      /* For bool */

/*==============================================================================================================
 * Defines a type for the DList data structure.
 *============================================================================================================*/
typedef struct {
    DListNode *mHead;  /* Pointer to first node in the list. */
    DListNode *mTail;  /* Pointer to last node in the list.  */
    int        mSize;  /* Number of nodes in list.           */
} DList;

/*==============================================================================================================
 * Global function declarations. See function comments in DList.c
 *============================================================================================================*/
extern DList *DListAlloc
    (
    );

extern DList *DListAppend
    (
    DList *pList,
    int    pData
    );

/* Function declaration for DListCopy() */
extern DList *DListCopy
    (
    DList *pSrcList
    );

extern void DListDebugPrint
    (
    FILE *stream,
    DList *pList
    );

/* Function declaration for DListDebugPrintRev() */
extern void DListDebugPrintRev
    (
    FILE *stream,
    DList *pList
    );

/* Function declaration for DListFindData() */
extern DNode *DListFindData
    (
    DList *pList,
    int    pData
    );

/* Function declaration for DListFindIndx() */
extern DNode *DListFindIndex
    (
    DList *pList,
    int    pIndex
    );

extern DList *DListFree
    (
    DList *pList
    );

extern DListNode *DListGetHead
    (
    DList *pList
    );

/* Function declaration for DListGetIndex() */
extern DListNode *DListGetIndex
    (
    DList *pList,
    int    pData
    );

extern int DListGetSize
    (
    DList *pList
    );

extern DListNode *DListGetTail
    (
    DList *pList
    );

/* Function declaration for DListInsertBefore() */
extern DList *DListInsertBefore
    (
    DList *pList,
    int    pBefore,
    int    pData
    );

/* Function declaration for DListInsertIndex() */
extern DList *DListInsertIndex
    (
    DList *pList,
    int    pIndex,
    int    pData
    );

extern bool DListIsEmpty
    (
    DList *pList
    );

/* Function declaration for DListRemoveData() */
extern DList *DListRemoveData
    (
    DList *pList,
    int    pData
    );

/* Function declaration for DListRemoveIndex() */
extern DList *DListRemoveIndex
    (
    DList *pList,
    int    pIndex
    );

extern DList *DListSetHead
    (
    DList     *pList,
    DListNode *pHead
    );

extern DList *DListSetSize
    (
    DList *pList,
    int    pSize
    );

extern DList *DListSetTail
    (
    DList     *pList,
    DListNode *pTail
    );

#endif
