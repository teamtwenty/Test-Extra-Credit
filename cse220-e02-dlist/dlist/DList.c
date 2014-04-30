/***************************************************************************************************************
 * FILE: DList.c
 *
 * DESCRIPTION
 * Implementation of the doubly-linked list data structure. The data stored in each node is an int.
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
#include <assert.h>     /* For assert() */
#include <stdio.h>      /* For FILE, fprintf(), NULL */
#include <stdlib.h>     /* For free(), malloc() */
#include "DList.h"      /* For DList struct and function declarations */
#include "DListNode.h"  /* For DListNode struct and function declarations */

/*==============================================================================================================
 * Static function declarations.
 *============================================================================================================*/
static DList *DListNodeRemove
    (
    DList     *pList,
    DListNode *pNode
    );

/*==============================================================================================================
 * Function definitions.
 *============================================================================================================*/

/*--------------------------------------------------------------------------------------------------------------
 * FUNCT: DListAlloc
 * DESCR: Allocate a new linked list. Returns a pointer to the allocated list or NULL on failure.
 * PCODE:
 * Define new_list as DList *
 * new_list <- malloc(sizeof(DList))
 * If new_list is not null Then
 *     Set head pointer of new_list to null
 *     Set tail pointer of new_list to null
 *     Set size of new_list to 0
 * End If
 * Return new_list
 *------------------------------------------------------------------------------------------------------------*/
DList *DListAlloc
    (
    )
{
    DList *new_list = (DList *)malloc(sizeof(DList));
    if (new_list) {
        DListSetHead(new_list, NULL);
        DListSetTail(new_list, NULL);
        DListSetSize(new_list, 0);
    }
    return new_list;
}

/*--------------------------------------------------------------------------------------------------------------
 * FUNCT: DListAppend
 * DESCR: Appends a new node containing data member set to pData to the list pList. Returns a pointer to pList
 *        or NULL on failure, i.e., if pList is NULL.
 * PCODE:
 * Assert pList is not null
 * Define new_node as DListNode * <- DListNodeAlloc(pData, DListGetTail(pList), null)
 * If pList is empty Then
 *     Set head pointer of pList to point to new_node
 * Else
 *     Get tail pointer of pList
 *     Set next pointer of tail pointer to point to new_node
 * End If
 * Set tail pointer of pList to point to new_node
 * Increment size of pList
 * Return pList
 *------------------------------------------------------------------------------------------------------------*/
DList *DListAppend
    (
    DList *pList,
    int    pData
    )
{
    assert(pList);
    DListNode *new_node = DListNodeAlloc(pData, DListGetTail(pList), NULL);
    if (DListIsEmpty(pList)) {
        DListSetHead(pList, new_node);
    } else {
        DListNodeSetNext(DListGetTail(pList), new_node);
    }
    DListSetTail(pList, new_node);
    DListSetSize(pList, DListGetSize(pList) + 1);
    return pList;
}

/*--------------------------------------------------------------------------------------------------------------
 * FUNCT: DListCopy
 * DESCR: Makes an identical copy of list pSrcList and returns a pointer to the new list.
 * PCODE:
 * Assert pSrcList is not null
 * Define copy_list as DList * <- DListAlloc()
 * Define traverse as DListNode * <- head pointer of pSrcList
 * While traverse is not null Do
 *     Get data value from traverse node             -- hint: call DListNodeGetData()
 *     Append data value to copy_list                -- hint: call DListAppend()
 *     Make traverse point to next node of pSrcList  -- Hint: Call DListNodeGetnext()
 * End While
 * Return copy_list
 *------------------------------------------------------------------------------------------------------------*/
???

/*--------------------------------------------------------------------------------------------------------------
 * FUNCT: DListDebugPrint
 * DESCR: Prints the contents of the list pList to the stream pStream. Prints "List is NULL" if L is NULL. This
 *        is primarily a testing and debugging function.
 *------------------------------------------------------------------------------------------------------------*/
void DListDebugPrint
    (
    FILE  *pStream,
    DList *pList
)
{
    DListNode *traverse;
    if (!pList) {
        fprintf(pStream, "List is NULL.\n");
        return;
    }
    fprintf(pStream, "[ ");
    traverse = DListGetHead(pList);
    while (traverse) {
        DListNodeDebugPrint(pStream, traverse);
        fprintf(pStream, " ");
        traverse = DListNodeGetNext(traverse);
    }
    fprintf(pStream, "]");
}

/*--------------------------------------------------------------------------------------------------------------
 * FUNCT: DListDebugPrintRev
 * DESCR: Prints the contents of the list pList in reverse order to the stream pStream. Prints "List is NULL"
 *        if L is NULL. This is primarily a debugging function.
 * PCODE:
 * This is a pretty easy function to write. Just study DListDebugPrint().
 *------------------------------------------------------------------------------------------------------------*/
???

/*--------------------------------------------------------------------------------------------------------------
 * FUNCT: DListFindData
 * DESCR: Returns a pointer to the first node containing a data member matching pData. Returns NULL if pData is
 *        not in pList. Assertion error if pList is NULL.
 * PCODE:
 * Assert pList is not null
 * Define traverse as DListNode * <- head pointer of pList
 * While traverse is not null AND data member of traverse node != pData Do  -- Hint: Call DListNodeGetData()
 *     Make traverse point to next node of pList                            -- Hint: Call DListGetNext()
 * End While
 * Return traverse
 *------------------------------------------------------------------------------------------------------------*/
DListNode *DListFindData
    (
    DList *pList,
    int    pData
    )
{
    assert(pList);
    DListNode *traverse = DListGetHead(pList);
    while (traverse && DListNodeGetData(traverse) != pData) {
         traverse = DListNodeGetNext(traverse);
    }
    return traverse;
}

/*--------------------------------------------------------------------------------------------------------------
 * FUNCT: DListFindIndex
 * DESCR: Returns a pointer the node in pList at index pIndex. Fails if pIndex < 0 or pIndex >= pList->mSize
 *        and returns NULL. Assertion error if pList is NULL.
 * PCODE:
 * Assert pList is not null
 * If pIndex < 0 OR pIndex >= size of pList Then Return null  -- Hint: Call DListGetSize()
 * Define traverse as DListNode * <- head pointer of pList    -- Hint: Call DListGetHead()
 * While traverse is not null AND --pIndex >= 0 Do
 *     Make traverse point to next node of pList              -- Hint: Call DListNodeGetNext()
 * End While
 * Return traverse
 *------------------------------------------------------------------------------------------------------------*/
???

/*--------------------------------------------------------------------------------------------------------------
 * FUNCT: DListFree
 * DESCR: Deallocates the linked list pList. This function should be called as soon as the list is no longer
  *        needed. Returns NULL. Does nothing and returns NULL if pList is NULL.
 * PCODE:
 * If pList is null Then Return null
 * Define traverse as DListNode * <- head pointer of pList
 * While traverse is not null Do
 *     Define next_node as DListNode * <- pointer to next node following traverse
 *     Deallocate traverse
 *     traverse <- next_node
 * End While
 * Deallocate pList
 * Return null
 *------------------------------------------------------------------------------------------------------------*/
DList *DListFree
    (
    DList *pList
    )
{
    if (!pList) return NULL;
    DListNode *traverse = DListGetHead(pList);
    while (traverse) {
        DListNode *next_node = DListNodeGetNext(traverse);
        free(traverse);
        traverse = next_node;
    }
    free(pList);
    return NULL;
}

/*--------------------------------------------------------------------------------------------------------------
 * FUNCT: DListGetHead
 * DESCR: Accessor function for the pList->mHead data member. Assertion error if pList is NULL.
 *------------------------------------------------------------------------------------------------------------*/
DListNode *DListGetHead
    (
    DList *pList
    )
{
    assert(pList);
    return pList->mHead;
}

/*--------------------------------------------------------------------------------------------------------------
 * FUNCT: DListGetIndex
 * DESCR: Searches pList for a node containing data member set to pData. Returns the index if the node if it is
 *        found, or -1 if pData is not in pList. Assertion error if pList is NULL.
 * PCODE:
 * Assert pList is not null.
 * Define index as int <- 0
 * Define traverse as DListNode * <- head pointer of pList            -- Hint: Call DListGetHead()
 * While traverse is not null Do
 *     If the data member of traverse equals pData Then Return index  -- HInt: Call DListNodeGetData()
 *     Increment index
 *     Make traverse point to the next node in pList                  -- Hint: Call DListNodeGetNext()
 * End If
 * Return -1
 *------------------------------------------------------------------------------------------------------------*/
???

/*--------------------------------------------------------------------------------------------------------------
 * FUNCT: DListGetSize
 * DESCR: Accessor function for the pList->mSize data member. Assertion error if pList is NULL.
 *------------------------------------------------------------------------------------------------------------*/
int DListGetSize
    (
    DList *pList
    )
{
    assert(pList);
    return pList->mSize;
}

/*--------------------------------------------------------------------------------------------------------------
 * FUNCT: DListGetTail
 * DESCR: Accessor function for the pList->tail data member. Assertion error if pList is NULL.
 *------------------------------------------------------------------------------------------------------------*/
DListNode *DListGetTail
    (
    DList *pList
    )
{
    assert(pList);
    return pList->mTail;
}

/*--------------------------------------------------------------------------------------------------------------
 * FUNCT: DListInsertBefore
 * DESCR: Inserts a new node containing data member set to mData into list pList before the first occurrence of
 *        the node with data member set to pBefore. On success, returns the list pList. Fails if a node contain-
 *        ing data member pBefore is not found and returns NULL. Assertion error if pList is NULL.
 * PCODE:
 * Assert pList is not null.
 * Define index as int <- DListFindData(pList, pBefore)
 * If index < 0 Then Return null
 * Else Return DListInsertIndex(pList, index, pData)
 *------------------------------------------------------------------------------------------------------------*/
???

/*--------------------------------------------------------------------------------------------------------------
 * FUNCT: DListInsertIndex
 * DESCR: Inserts a new node containing pData into the list pList at index pIndex. The nodes in the list are
 *        numbered starting at 0. Fails and returns NULL if: (1) pList is empty; or (2) pIndex < 0; or (3)
 *        pIndex >= pList->mSize. Note: if you want to insert a new node at the end of the list then you should
 *        call the DListAppend() function. Assertion error if pList is NULL.
 * PCODE:
 * Assert pList is not null.
 * Define index_node, new_node as DListNode *
 * If pList is empty OR pIndex < 0 OR pIndex >= size of pList Then Return null.
 * index_node <- DListFindIndex(pList, pIndex)
 * If index_node is null Then Return null.
 * new_node <- DListNodeAlloc(pData, DListNodeGetPrev(index_node), index_node)
 * If the prev pointer of index_node is not null Then
 *     prev_index <- Get the prev pointer of index_node
 *     Set the next pointer of prev_index to point to new_node
 * Else
 *     Set the head pointer of pList to point to new_node
 * End If
 * Set the prev pointer of index_node to point to new_node
 * Increment the size of pList
 * Return pList
 *------------------------------------------------------------------------------------------------------------*/
???

/*--------------------------------------------------------------------------------------------------------------
 * FUNCT: DListIsEmpty
 * DESCR: Returns true if the pList is empty, false otherwise. Assertion error if pList is NULL.
 *------------------------------------------------------------------------------------------------------------*/
bool DListIsEmpty
    (
    DList *pList
    )
{
    assert(pList);
    return pList->mSize == 0;
}

/*--------------------------------------------------------------------------------------------------------------
 * FUNCT: DListRemoveData
 * DESCR: Finds and removes the first occurrence of a node containing data member set to pData in pList. On
 *        success returns the list pList. Fails if a node containing data member set to pData is not found and
 *        returns NULL. Assertion error if pList is NULL.
 * PCODE:
 * Assert pList is not null.
 * Define index as int <- DListGetIndex(pList, pData)
 * Return DListRemoveIndex(pList, pIndex)
 *------------------------------------------------------------------------------------------------------------*/
DList *DListRemoveData
    (
    DList *pList,
    int    pData
    )
{
    assert(pList);
    int index = DListGetIndex(pList, pData);
    return DListRemoveIndex(pList, index);
}

/*--------------------------------------------------------------------------------------------------------------
 * FUNCT: DListRemoveIndex
 * DESCR: Finds and removes the node at index pIndex in list pList. On success, returns the list pList. Fails
 *        if pIndex < 0 or pIndex >= pList->mSize and returns NULL. Assertion error if pList is NULL.
 * PCODE:
 * Assert pList is not null.
 * Define index_node as DListNode * <- DlistFindIndex(pList, pIndex)
 * Return DListNodeRemove(pList, index_node);
 *------------------------------------------------------------------------------------------------------------*/
???

/*--------------------------------------------------------------------------------------------------------------
 * FUNCT: DListNodeRemove
 * DESCR: Removes the node pNode from the list pList. Returns the list pList on success. Fails if pNode is NULL
 *        and returns NULL. Assertion error if pList is NULL.
 * PCODE:
 * Assert pList is not null.
 * If pNode is null Then Return null.
 * If pNode is the head node of pList Then
 *     Set the head pointer of pList to point to the next node following pNode
 *     If the head pointer of pList is not null Then
 *         Set the prev pointer of the head node to NULL
 *     End If
 * Else if pNode is the tail node of pList Then
 *     If the tail pointer of pList is not null Then
 *         tail_prev <- Get the prev pointer of the tail node of pList
 *         Set the next pointer of tail_prev to NULL
 *     End If
 * Else
 *     node_prev <- prev pointer of pNode
 *     If node_prev is not null Then
 *         Set the next pointer of node_prev to the next pointer of pNode
 *         If the next pointer of pNode is not null Then
 *             node_next <- Get the next pointer of pNode
 *             b <- Get the prev pointer of node_next
 *             Set the prev pointer of b to node_prev
 *         End If
 *     End If
 * End If
 * Call DListNodeFree(pNode) to deallocate pNode
 * Decrement the size of pList
 * Return pList
 *------------------------------------------------------------------------------------------------------------*/
???

/*--------------------------------------------------------------------------------------------------------------
 * FUNCT: DListSetHead
 * DESCR: Mutator function for the pList->mHead data member. Assertion error if pList is NULL.
 *------------------------------------------------------------------------------------------------------------*/
DList *DListSetHead
    (
    DList     *pList,
    DListNode *pHead
    )
{
    assert(pList);
    pList->mHead = pHead;
    return pList;
}

/*--------------------------------------------------------------------------------------------------------------
 * FUNCT: DListSetSize
 * DESCR: Mutator function for the pList->mSize data member. Assertion error if pList is NULL.
 *------------------------------------------------------------------------------------------------------------*/
DList *DListSetSize
    (
    DList *pList,
    int    pSize
    )
{
    assert(pList);
    pList->mSize = pSize;
    return pList;
}

/*--------------------------------------------------------------------------------------------------------------
 * FUNCT: DListSetTail
 * DESCR: Mutator function for the pList->mTail data member. Assertion error if pList is NULL.
 *------------------------------------------------------------------------------------------------------------*/
DList *DListSetTail
    (
    DList     *pList,
    DListNode *pTail
    )
{
    assert(pList);
    pList->mTail = pTail;
    return pList;
}
