/***************************************************************************************************************
 * FILE: SList.c
 *
 * DESCRIPTION
 * Implementation of the singly-linked list data structure. The data stored in each node is an int.
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
#include <assert.h>     /* For assert() */
#include <stdio.h>      /* For FILE, fprintf(), NULL */
#include <stdlib.h>     /* For free(), malloc() */
#include "SList.h"
#include "SListNode.h"

/*==============================================================================================================
 * Function definitions.
 *============================================================================================================*/

/*--------------------------------------------------------------------------------------------------------------
 * FUNCT: SListAlloc
 * DESCR: Allocate a new linked list. Returns a pointer to the allocated list or NULL on failure.
 *------------------------------------------------------------------------------------------------------------*/
SList *SListAlloc
    (
    )
{
    SList *new_list = (SList *)malloc(sizeof(SList));
    if (new_list) {
        SListSetHead(new_list, NULL);
        SListSetTail(new_list, NULL);
        SListSetSize(new_list, 0);
    }
    return new_list;
}

/*--------------------------------------------------------------------------------------------------------------
 * FUNCT: SListAppend
 * DESCR: Appends a new node containing data member set to pData to the list pList. Returns a pointer to pList
 *        or NULL on failure, i.e., if pList is NULL.
 *------------------------------------------------------------------------------------------------------------*/
SList *SListAppend
    (
    SList *pList,
    int    pData
)
{
    SListNode *new_node;
    if (!pList) return NULL;
    new_node = SListNodeAlloc(pData, NULL);
    if (SListIsEmpty(pList)) {
        SListSetHead(pList, new_node);
    } else {
        SListNodeSetNext(SListGetTail(pList), new_node);
    }
    SListSetTail(pList, new_node);
    SListSetSize(pList, SListGetSize(pList) + 1);
    return pList;
}

/*--------------------------------------------------------------------------------------------------------------
 * FUNCT: SListDebugPrint
 * DESCR: Prints the contents of the list pList to the stream pStream. Prints "List is NULL" if L is NULL. This
 *        is primarily a debugging function.
 *------------------------------------------------------------------------------------------------------------*/
void SListDebugPrint
    (
    FILE  *pStream,
    SList *pList
)
{
    SListNode *traverse;
    if (!pList) {
        fprintf(pStream, "List is NULL.\n");
        return;
    }
    fprintf(pStream, "[ ");
    traverse = SListGetHead(pList);
    while (traverse) {
        SListNodeDebugPrint(pStream, traverse);
        fprintf(pStream, " ");
        traverse = SListNodeGetNext(traverse);
    }
    fprintf(pStream, "]");
}

/*--------------------------------------------------------------------------------------------------------------
 * FUNCT: SListFind
 * DESCR: Returns a pointer to the first node containing a data member matching pData. Returns NULL if pData is
 *        not in pList or if pList is NULL.
 *------------------------------------------------------------------------------------------------------------*/
SListNode *SListFind
    (
    SList *pList,
    int    pData
    )
{
    if (!pList) return NULL;
    SListNode *traverse = SListGetHead(pList);
    while (traverse && SListNodeGetData(traverse) != pData) {
         traverse = SListNodeGetNext(traverse);
    }
    return traverse;
}

/*--------------------------------------------------------------------------------------------------------------
 * FUNCT: SListFree
 * DESCR: Deallocates the linked list pList. This function should be called as soon as the list is no longer
 *        needed. Returns NULL.
 *------------------------------------------------------------------------------------------------------------*/
SList *SListFree
    (
    SList *pList
    )
{
    if (!pList) return NULL;
    SListNode *traverse = SListGetHead(pList);
    while (traverse) {
        SListNode *next_node = SListNodeGetNext(traverse);
        free(traverse);
        traverse = next_node;
    }
    free(pList);
    return NULL;
}

/*--------------------------------------------------------------------------------------------------------------
 * FUNCT: SListGetHead
 * DESCR: Accessor function for the pList->mHead data member. Assertion error if pList is NULL.
 *------------------------------------------------------------------------------------------------------------*/
SListNode *SListGetHead
    (
    SList *pList
    )
{
    assert(pList);
    return pList->mHead;
}

/*--------------------------------------------------------------------------------------------------------------
 * FUNCT: SListGetNodeAtIndex
 * DESCR: Returns a pointer to the node at index pIndex of list pList. Returns NULL if pList is empty or pIndex
 *        is out of bounds.
 *------------------------------------------------------------------------------------------------------------*/
SListNode *SListGetNodeAtIndex
    (
    SList *pList,
    int    pIndex
    )
{
    SListNode *traverse;
    if (pIndex < 0) return NULL;
    traverse = SListGetHead(pList);
    while (traverse && --pIndex >= 0) {
        traverse = SListNodeGetNext(traverse);
    }
    return traverse;
}

/*--------------------------------------------------------------------------------------------------------------
 * FUNCT: SListGetPrev
 * DESCR: Returns a pointer to the node in pList that is the previous node of pNode. Assertion error if pList
 *        or pNode is NULL.
 *------------------------------------------------------------------------------------------------------------*/
SListNode *SListGetPrev
    (
    SList     *pList,
    SListNode *pNode
    )
{
    assert(pList && pNode);
    SListNode *traverse;
    if (pNode == SListGetHead(pList)) return NULL;
    traverse = SListGetHead(pList);
    while (traverse && SListNodeGetNext(traverse) != pNode) {
        traverse = SListNodeGetNext(traverse);
    }
    return traverse;
}

/*--------------------------------------------------------------------------------------------------------------
 * FUNCT: SListGetSize
 * DESCR: Accessor function for the pList->mSize data member. Assertion error if pList is NULL.
 *------------------------------------------------------------------------------------------------------------*/
int SListGetSize
    (
    SList *pList
    )
{
    assert(pList);
    return pList->mSize;
}

/*--------------------------------------------------------------------------------------------------------------
 * FUNCT: SListGetTail
 * DESCR: Accessor function for the pList->tail data member. Assertion error if pList is NULL.
 *------------------------------------------------------------------------------------------------------------*/
SListNode *SListGetTail
    (
    SList *pList
    )
{
    assert(pList);
    return pList->mTail;
}

/*--------------------------------------------------------------------------------------------------------------
 * FUNCT: SListInsert
 * DESCR: Inserts a new node containing pData into the list pList at index pIndex. The nodes in the list are
 *        numbered starting at 0. Fails and returns NULL if: (1) pList is NULL; or (2) pList->mSize <= 0; or
 *        (3) pIndex < 0; or (4) pIndex >= pList->mSize. Note: if you want to insert a new node at the end of
 *        the list then you should call the SListAppend() function.
 *------------------------------------------------------------------------------------------------------------*/
SList *SListInsert
    (
    SList *pList,
    int    pIndex,
    int    pData
)
{
    SListNode *new_node, *prev_node;
    if (!pList || SListIsEmpty(pList) || pIndex < 0 || pIndex >= pList->mSize) return NULL;
    new_node = SListNodeAlloc(pData, NULL);
    prev_node = SListGetNodeAtIndex(pList, pIndex-1);
    if (prev_node) {
        SListNode *next_node = SListNodeGetNext(prev_node);
        SListNodeSetNext(prev_node, new_node);
        SListNodeSetNext(new_node, next_node);
    } else {
        SListNodeSetNext(new_node, SListGetHead(pList));
        SListSetHead(pList, new_node);
    }
    SListSetSize(pList, SListGetSize(pList) + 1);
    return pList;
}

/*--------------------------------------------------------------------------------------------------------------
 * FUNCT: SListIsEmpty
 * DESCR: Returns true if the pList is empty. Assertion error if pList is NULL.
 *------------------------------------------------------------------------------------------------------------*/
bool SListIsEmpty
    (
    SList *pList
    )
{
    assert(pList);
    return pList->mSize == 0;
}

/*--------------------------------------------------------------------------------------------------------------
 * FUNCT: SListRemove
 * DESCR: Removes the first occurrence of a node with data member set to pData. If pList is NULL or pData is
 *        not in pList then returns NULL. On success, returns a pointer to pList.
 *------------------------------------------------------------------------------------------------------------*/
SList *SListRemove
    (
    SList *pList,
    int    pData
    )
{
    SListNode *data_node, *prev_node;
    if (!pList) return NULL;
    data_node = SListFind(pList, pData);
    if (!data_node) return NULL;
    prev_node = SListGetPrev(pList, data_node);
    if (prev_node) {
        SListNodeSetNext(prev_node,
        SListNodeGetNext(data_node));
    } else {
        SListSetHead(pList, SListNodeGetNext(data_node));
    }
    SListNodeFree(data_node);
    SListSetSize(pList, SListGetSize(pList)-1);
    return pList;
}

/*--------------------------------------------------------------------------------------------------------------
 * FUNCT: SListSetHead
 * DESCR: Mutator function for the pList->mHead data member. Assertion error if pList is NULL.
 *------------------------------------------------------------------------------------------------------------*/
SList *SListSetHead
    (
    SList     *pList,
    SListNode *pHead
    )
{
    assert(pList);
    pList->mHead = pHead;
    return pList;
}

/*--------------------------------------------------------------------------------------------------------------
 * FUNCT: SListSetSize
 * DESCR: Mutator function for the pList->mSize data member. Assertion error if pList is NULL.
 *------------------------------------------------------------------------------------------------------------*/
SList *SListSetSize
    (
    SList *pList,
    int    pSize
    )
{
    assert(pList);
    pList->mSize = pSize;
    return pList;
}

/*--------------------------------------------------------------------------------------------------------------
 * FUNCT: SListSetTail
 * DESCR: Mutator function for the pList->mTail data member. Assertion error if pList is NULL.
 *------------------------------------------------------------------------------------------------------------*/
SList *SListSetTail
    (
    SList     *pList,
    SListNode *pTail
    )
{
    assert(pList);
    pList->mTail = pTail;
    return pList;
}
