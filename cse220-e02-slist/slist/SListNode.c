/***************************************************************************************************************
 * FILE: SListNode.c
 *
 * DESCRIPTION
 * Implements the functions for a singly linked list node.
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
/*#define NDEBUG*/      /* Comment out to enable assertions. */
#include <assert.h>     /* For assert() */
#include <stdio.h>      /* For FILE, fprintf() */
#include <stdlib.h>     /* For free(), malloc(), NULL */
#include "SListNode.h"

/*==============================================================================================================
 * Function definitions.
 *============================================================================================================*/

/*--------------------------------------------------------------------------------------------------------------
 * Allocates a new node with mData member set to pData and mNext pointer set to pNext. Returns a pointer to the
 * new node, or NULL if malloc() fails.
 *------------------------------------------------------------------------------------------------------------*/
SListNode *SListNodeAlloc
    (
    int        pData,
    SListNode *pNext
    )
{
    SListNode *new_node = (SListNode*)malloc(sizeof(SListNode));
    if (new_node) {
        SListNodeSetData(new_node, pData);
        SListNodeSetNext(new_node, pNext);
    }
    return new_node;
}

/*--------------------------------------------------------------------------------------------------------------
 * FUNCT: SListNodeDebugPrint
 * DESCR: Prints the data member stored at pNode. This is primarily intended to be a debugging function.
 *        Assertion error if pNode is NULL.
 *------------------------------------------------------------------------------------------------------------*/
void SListNodeDebugPrint
    (
    FILE      *pStream,
    SListNode *pNode
    )
{
    assert(pNode);
    fprintf(pStream, "%d", SListNodeGetData(pNode));
}

/*--------------------------------------------------------------------------------------------------------------
 * Deallocates a node that was allocated by calling SListNodeAlloc(). Note: after a node is deallocated, you
 * should not dereference it. For example,
 *
 * SListNode *node = SListNodeAlloc(10, NULL);
 * ...
 * SListNodeFree(node);
 * int x = SListNodeGetData(node);  BUG!
 * int y = node->mData;             BUG!
 *
 * These sorts of bugs can be very hard to find because they generally do not cause a segmentation fault and
 * your program generally does not crash right away. Why not? Because even though 'node' now points to a block
 * of memory which has been deallocated, the data is still there, and you can still read from those memory
 * locations. For this reason, we will make this function return a NULL pointer, and then call it this way,
 *
 * SListNode *node = SListNodeAlloc(10, NULL);
 * ...
 * node = SListNodeFree(node);      On return, node points to NULL.
 * int x = SListNodeGetData(node);  Segmentation fault
 * int y = node->mData;             Segmentation fault
 *
 * As we discussed in the lecture, seg faults are pretty easy to find. Just load the program into gdb, run it
 * and wait for it to blow up. gdb will tell you where the code failed. Fix your bug, rebuild, and you're on
 * your way. Slick.
 *------------------------------------------------------------------------------------------------------------*/
SListNode *SListNodeFree
    (
    SListNode *pNode
    )
{
    free(pNode);
    return NULL;
}

/*--------------------------------------------------------------------------------------------------------------
 * Accessor function for the mData data member. Assertion error if pNode is NULL.
 *------------------------------------------------------------------------------------------------------------*/
int SListNodeGetData
    (
    SListNode *pNode
    )
{
    assert(pNode);
    return pNode->mData;
}

/*--------------------------------------------------------------------------------------------------------------
 * Accessor function for the mNext data member. Assertion error if pNode is NULL.
 *------------------------------------------------------------------------------------------------------------*/
SListNode *SListNodeGetNext
    (
    SListNode *pNode
    )
{
    assert(pNode);
    return pNode->mNext;
}

/*--------------------------------------------------------------------------------------------------------------
 * Mutator function for the mData data member. Assertion error if pNode is NULL.
 *------------------------------------------------------------------------------------------------------------*/
void SListNodeSetData
    (
    SListNode *pNode,
    int        pData
    )
{
    assert(pNode);
    pNode->mData = pData;
}

/*--------------------------------------------------------------------------------------------------------------
 * Mutator function for the mNext data member. Assertion error if pNode is NULL.
 *------------------------------------------------------------------------------------------------------------*/
void SListNodeSetNext
    (
    SListNode *pNode,
    SListNode *pNext
    )
{
    assert(pNode);
    pNode->mNext = pNext;
}
