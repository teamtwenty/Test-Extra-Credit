/***************************************************************************************************************
 * FILE: DListNode.h
 *
 * DESCRIPTION
 * Declaration of a node in a doubly-linked list. The data stored in each node is an int.
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
#ifndef __DLISTNODE_H__
#define __DLISTNODE_H__

#include <stdio.h>  /* For FILE */

/*==============================================================================================================
 * Typedefs.
 *============================================================================================================*/
typedef struct DListNode_ {
    int                mData;  /* Each node stores a simple int. */
    struct DListNode_ *mNext;  /* Pointer to the next node in the list. NULL if this is the last node. */
    ???                        /* Pointer to the prev node in the list. NULL if this is the last node. */
} DListNode;

/*==============================================================================================================
 * Global function declarations. See function comments in DListNode.c
 *============================================================================================================*/
extern DListNode *DListNodeAlloc
    (
    int        pData,
    DListNode *pPrev,
    DListNode *pNext
    );

extern void DListNodeDebugPrint
    (
    FILE      *pStream,
    DListNode *pNode
    );

extern DListNode *DListNodeFree
    (
    DListNode *pNode
    );

extern int DListNodeGetData
    (
    DListNode *pNode
    );

extern DListNode *DListNodeGetNext
    (
    DListNode *pNode
    );

/* Function declaration for DListNodeGetPrev() */
???

extern void DListNodeSetData
    (
    DListNode *pNode,
    int        pData	
    );

extern void DListNodeSetNext
    (
    DListNode *pNode,
    DListNode *pNext
    );

/* Function declaration for DListNodeSetPrev()
???

#endif
