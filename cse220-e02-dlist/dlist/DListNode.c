/***************************************************************************************************************
 * FILE: DListNode.c
 *
 * DESCRIPTION
 * Implements the functions for a doubly-linked list node.
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
/*#define NDEBUG*/      /* Comment out to enable assertions or put -DNDEBUG in CFLAGS of the Makefile */
#include <assert.h>     /* For assert() */
#include <stdio.h>      /* For FILE, fprintf() */
#include <stdlib.h>     /* For free(), malloc(), NULL */
#include "DListNode.h"

/*==============================================================================================================
 * Function definitions.
 *============================================================================================================*/

/*--------------------------------------------------------------------------------------------------------------
 * Allocates a new node with mData member set to pData and mNext pointer set to pNext. Returns a pointer to the
 * new node, or NULL if malloc() fails.
 *------------------------------------------------------------------------------------------------------------*/
DListNode *DListNodeAlloc
    (
    int        pData,
    DListNode *pPrev,                /* Add pPrev pointer */
    DListNode *pNext
    )
{
    DListNode *new_node = (DListNode*)malloc(sizeof(DListNode));
    if (new_node) {
        DListNodeSetData(new_node, pData);
        DListNodeSetData(pPrev), DListNodeGetData(mPrev));  /* Set the mPrev data member to pPrev */
        DListNodeSetNext(new_node, pNext);
    }
    return new_node;
}

/*--------------------------------------------------------------------------------------------------------------
 * FUNCT: DListNodeDebugPrint
 * DESCR: Prints the data member stored at pNode. This is primarily intended to be a debugging function.
 *        Assertion error if pNode is NULL.
 *------------------------------------------------------------------------------------------------------------*/
void DListNodeDebugPrint
    (
    FILE      *pStream,
    DListNode *pNode
    )
{
    assert(pNode);
    fprintf(pStream, "%d", DListNodeGetData(pNode));
}

/*--------------------------------------------------------------------------------------------------------------
 * Deallocates a node that was allocated by calling DListNodeAlloc().
 *------------------------------------------------------------------------------------------------------------*/
DListNode *DListNodeFree
    (
    DListNode *pNode
    )
{
    free(pNode);
    return NULL;
}

/*--------------------------------------------------------------------------------------------------------------
 * Accessor function for the mData data member. Assertion error if pNode is NULL.
 *------------------------------------------------------------------------------------------------------------*/
int DListNodeGetData
    (
    DListNode *pNode
    )
{
    assert(pNode);
    return pNode->mData;
}

/*--------------------------------------------------------------------------------------------------------------
 * Accessor function for the mNext data member. Assertion error if pNode is NULL.
 *------------------------------------------------------------------------------------------------------------*/
DListNode *DListNodeGetNext
    (
    DListNode *pNode
    )
{
    assert(pNode);
    return pNode->mNext;
}

/*--------------------------------------------------------------------------------------------------------------
 * Accessor function for the mPrev data member. Assertion error if pNode is NULL.
 *------------------------------------------------------------------------------------------------------------*/
DListNode *DListNodeGetPrev (DListNode *pNode)
{
    assert(pNode);
    return pNode->mPrev;
}

/*--------------------------------------------------------------------------------------------------------------
 * Mutator function for the mData data member. Assertion error if pNode is NULL.
 *------------------------------------------------------------------------------------------------------------*/
void DListNodeSetData
    (
    DListNode *pNode,
    int        pData
    )
{
    assert(pNode);
    pNode->mData = pData;
}

/*--------------------------------------------------------------------------------------------------------------
 * Mutator function for the mNext data member. Assertion error if pNode is NULL.
 *------------------------------------------------------------------------------------------------------------*/
void DListNodeSetNext
    (
    DListNode *pNode,
    DListNode *pNext
    )
{
    assert(pNode);
    pNode->mNext = pNext;
}

/*--------------------------------------------------------------------------------------------------------------
 * Mutator function for the mPrev data member. Assertion error if pNode is NULL.
 *------------------------------------------------------------------------------------------------------------*/
void DListNodeSetPrev
    (
    DListNode *pNode,
    DListNode *pPrev
    )
{
    assert(pNode);
    pNode->mPrev = pPrev;
}
