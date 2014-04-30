/***************************************************************************************************************
 * FILE: ListTest.c
 *
 * DESCRIPTION
 * Test driver for the singly-linked list data structure.
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
#include <stdio.h>    /* For FILE, fprintf(), fscanf(), NULL */
#include <stdlib.h>   /* For exit() */
#include "ListMan.h"
#include "DList.h"
#include "String.h"

/*==============================================================================================================
 * Static function declarations.
 *============================================================================================================*/
static void ListTest
    (
    );

static void ListTestCmdAppend
    (
    );

/* Function declaration for ListTestCmdCopy() */
???

static void ListTestCmdCreate
    (
    );

static void ListTestCmdFind
    (
    );

/* Function declaration for ListTestCmdFindAt() */
???

static void ListTestCmdFree
    (
    );

/* Function declaration for ListTestInsert() */
???

/* Function declaration for ListTestInsertAt() */
???

static void ListTestCmdPrint
    (
    );

/* Function declaration for ListTestCmdPrintRev() */
???

/* Function declaration for ListTestRemove() */
???

/* Function declaration for ListTestCmdRemoveAt() */
???

static void ListTestFileClose
    (
    FILE *pStream
    );

static FILE *ListTestFileOpen
    (
    char *pFileName, 
    char *pMode, 
    char *pMsg
    );

static void ListTestPerform
    (
    char *pCmd
    );

/*==============================================================================================================
 * Global variable definitions.
 *============================================================================================================*/
static FILE *gFin;
static FILE *gFout;

/*==============================================================================================================
 * Function definitions.
 *============================================================================================================*/

/*--------------------------------------------------------------------------------------------------------------
 * FUNCT: main
 * DESCR: Starting point of execution. Opens the input and output files and calls ListTest() to perform the
 *        testing. On return, closes the input and output files and terminates.
 *------------------------------------------------------------------------------------------------------------*/
int main
    (
    int   pArgc, 
    char *pArgv[]
    )
{
    if (pArgc < 3) {
        fprintf(stderr, "Usage: ListTest inputfile outputfile\n");
        exit(-1);
    }
    gFin = ListTestFileOpen(pArgv[1], "rt", "reading");
    gFout = ListTestFileOpen(pArgv[2], "wt", "writing");
    ListTest();
    ListTestFileClose(gFin);
    ListTestFileClose(gFout);
    return 0;
}

/*--------------------------------------------------------------------------------------------------------------
 * FUNCT: ListTestCmdAppend
 * DESCR: Performs the "append list data" command. Prints the list after appending so it can be inspected to
 *        determine if the DListAppend() function worked correctly.
 * PCODE:
 * Read the listname and data value from gFin.
 * list <- ListManGetList(listname)
 * If DListAppend(list, data) succeeds Then
 *     Print "appended ..."
 * Else
 *     Print "failed ..."
 * End If
 *------------------------------------------------------------------------------------------------------------*/
static void ListTestCmdAppend
    (
    )
{
    char listname[8];
    int data;
    DList *list;
    fscanf(gFin, "%s%d", listname, &data);
    list = ListManGetList(listname);
    if (DListAppend(list, data)) fprintf(gFout, "appended %d to %s\n", data, listname);
    else fprintf(gFout, "failed to append %d to %s\n", data, listname);
}

/*--------------------------------------------------------------------------------------------------------------
 * FUNCT: ListTestCmdCopy
 * DESCR: Performs the "copy dst src" command. Prints the destination list after copying so it can be inspected
 *        to etermine if the dlist_copy() function worked correctly.
 * PCODE:
 * Read dstlistname and srclistname from gFin 
 * srclist <- ListManGetList(srclistname)
 * dstlist <- DListCopy(srclist)
 * Call ListManCreateList() to add the dstlist to the list manager database.
 * Print "copied ..."
 *------------------------------------------------------------------------------------------------------------*/
???

/*--------------------------------------------------------------------------------------------------------------
 * FUNCT: ListTestCmdCreate
 * DESCR: Performs the "create list" command.
 * PCODE:
 * Read the listname from gFin.
 * new_list <- DListAlloc()
 * If the new list was created Then
 *     Call ListManCreateList() to add new_list to the list manager database.
 *     Print listname " created"
 * Else
 *     Print "failed to create ..." listname.
 * EndIf
 *------------------------------------------------------------------------------------------------------------*/
static void ListTestCmdCreate
    (
    )
{
    char listname[8];
    fscanf(gFin, "%s", listname);
    DList *new_list = DListAlloc();
    if (new_list) {
        ListManCreateList(listname, new_list);
        fprintf(gFout, "%s created\n", listname);
    } else {
        fprintf(gFout, "failed to create %s\n", listname);
    }
}

/*--------------------------------------------------------------------------------------------------------------
 * FUNCT: ListTestCmdFind
 * DESCR: Performs the "find list data" command.
 * PCODE:
 * Read the listname and data from gFin
 * list <- ListManGetList(listname)
 * found_node <- DListFindData(list, data)
 * If found_node is not null Then
 *     Print "found ..."
 * Else
 *     Print *failed ..."
 * End If
 *------------------------------------------------------------------------------------------------------------*/
static void ListTestCmdFind
    (
    )
{
    char listname[8];
    int data;
    DList *list;
    DListNode *found_node;
    fscanf(gFin, "%s%d", listname, &data);
    list = ListManGetList(listname);
    found_node = DListFindData(list, data);
    if (found_node) fprintf(gFout, "found %d in %s\n", data, listname);
    else fprintf(gFout, "failed to find %d in %s\n", data, listname);
}

/*--------------------------------------------------------------------------------------------------------------
 * FUNCT: ListTestCmdFindAt
 * DESCR: Performs the "findat list index" command.
 * PCODE:
 * Read the listname and index from gFin
 * list <- ListManGetList(listname)
 * found_node <- DListFindIndex(list, index)
 * If found_node is not null Then
 *     Print "found ..."
 * Else
 *     Print "failed to findat ..."
 * End If
 *------------------------------------------------------------------------------------------------------------*/
???

/*--------------------------------------------------------------------------------------------------------------
 * FUNCT: ListTestCmdFree
 * DESCR: Performs the "free list" command.
 * PCODE:
 * Read the listname from gFin.
 * list <- ListManGetList(listname)
 * If list is not null Then
 *     list <- DListFree(list)
 *     ListManFreeList(listname)
 *     Print "freed ..."
 * Else
 *     Print "error ..."
 * EndIf
 *------------------------------------------------------------------------------------------------------------*/
static void ListTestCmdFree
    (
    )
{
    char listname[8];
    DList *list;
    fscanf(gFin, "%s", listname);
    list = ListManGetList(listname);
    if (list) {
        list = DListFree(list); /* Sanity check. list will be NULL. */
        ListManFreeList(listname);
        fprintf(gFout, "freed %s\n", listname);
    } else {
        fprintf(gFout, "error: %s does not exist\n", listname);
    }
}

/*--------------------------------------------------------------------------------------------------------------
 * FUNCT: ListTestCmdInsert
 * DESCR: Performs the "insert list data" command.
 * PCODE:
 * Read the listname, before, data from gFin.
 * list <- ListManGetList(listname)
 * If DListInsertBefore(list, before, data) succeeds Then
 *     Print "inserted ..."
 * Else
 *     Print "failed ..."
 * End If
 *------------------------------------------------------------------------------------------------------------*/
static void ListTestCmdInsert
    (
    )
{
    char listname[8];
    int before, data;
    fscanf(gFin, "%s%d%d", listname, &before, &data);
    DList *list = ListManGetList(listname);
    if (DListInsertBefore(list, before, data)) {
        fprintf(gFout, "inserted %d before %d in %s\n", data, before, listname);
    } else {
        fprintf(gFout, "failed to insert %d before %d in %s\n", data, before, listname);
    }
}

/*--------------------------------------------------------------------------------------------------------------
 * FUNCT: ListTestCmdInsertAt
 * DESCR: Performs the "insertat list index data" command.
 * PCODE:
 * Read the listname, index, data from gFin.
 * list <- ListManGetList(listname)
 * If DListInsertIndex(list, index, data) succeeds Then
 *     Print "inserted ..."
 * Else
 *     Print "failed ..."
 * End If
 *------------------------------------------------------------------------------------------------------------*/
???

/*--------------------------------------------------------------------------------------------------------------
 * FUNCT: ListTestCmdPrint
 * DESCR:Performs the "print list" command.
 * PCODE:
 * Read the listname from the input file
 * list <- ListManGetList(listname)
 * If list is not null Then
 *     Output the list
 * Else
 *     Print " ... does not exist"
 * End If
 *------------------------------------------------------------------------------------------------------------*/
static void ListTestCmdPrint
    (
    )
{
    char listname[8];
    fscanf(gFin, "%s", listname);
    DList *list = ListManGetList(listname);
    if (list) {
        fprintf(gFout, "%s = ", listname);
        DListDebugPrint(gFout, list);
        fprintf(gFout, "\n");
    } else {
        fprintf(gFout, "%s does not exist\n", listname);
    }
}

/*--------------------------------------------------------------------------------------------------------------
 * FUNCT: ListTestCmdPrintRev
 * DESCR:Performs the "printr list" command.
 * PCODE:
 * Read the listname from the input file
 * list <- ListManGetList(listname)
 * If list is not null Then
 *     Output the list in reverse order
 * Else
 *     Print " ... does not exist"
 * End If
 *------------------------------------------------------------------------------------------------------------*/
???

/*--------------------------------------------------------------------------------------------------------------
 * FUNCT: ListTestCmdRemove
 * DESCR Performs the "remove list data" command.
 * PCODE:
 * Read the listname and data from gFin.
 * list <- ListManGetList(listname)
 * If DListRemoveData(list, data) succeeds Then
 *     Print "removed ..."
 * Else
 *     Print "failed ..."
 * End If
 *------------------------------------------------------------------------------------------------------------*/
static void ListTestCmdRemove
    (
    )
{
    char listname[8];
    int data;
    DList *list;
    fscanf(gFin, "%s%d", listname, &data);
    list = ListManGetList(listname);
    if (DListRemoveData(list, data)) fprintf(gFout, "removed %d from %s\n", data, listname);
    else fprintf(gFout, "failed to remove %d from %s\n", data, listname);
}

/*--------------------------------------------------------------------------------------------------------------
 * FUNCT: ListTestCmdRemoveAt
 * DESCR Performs the "removeat list data" command.
 * PCODE:
 * Read the listname and index from gFin.
 * list <- ListManGetList(listname)
 * If DListRemoveIndex(list, index) succeeds Then
 *     Print "removed ..."
 * Else
 *     Print "failed ..."
 * End If
 *------------------------------------------------------------------------------------------------------------*/
???

/*--------------------------------------------------------------------------------------------------------------
 * FUNCT: ListTestFileClose
 * DESCR: Closes the file specified by pStream. You close a file the same way whether it was opened for reading
 *        or writing.
 *------------------------------------------------------------------------------------------------------------*/
static void ListTestFileClose
    (
    FILE *pStream
    )
{
    fclose(pStream);
}

/*--------------------------------------------------------------------------------------------------------------
 * FUNCT: ListTestFileOpen
 * DESCR: Opens the file with name specified by pFilename for reading (if mode is "rt") or writing (if mode is
 *        "wt"). Returns the file pointer. If the file open fails, displays an error message to stderr and
 *        terminates the program with a nonzero return code by calling exit().
 * PCODE:
 * Call fopen() passing pFileName and pMode.
 * If the file was opened successfully (return pointer is nonnull) then return the file pointer.
 * Else file could not be opened. Display an error message and terminate the program with exit(-1).
 *------------------------------------------------------------------------------------------------------------*/
static FILE *ListTestFileOpen
    (
    char *pFileName,
    char *pMode,
    char *pMsg
    )
{
    FILE *fstream = fopen(pFileName, pMode);
    if (fstream) return fstream;
    fprintf(stdout, "Cannot open '%s' for %s. Terminating.\n", pFileName, pMsg);
    exit(-1);
}

/*--------------------------------------------------------------------------------------------------------------
 * FUNCT: ListTestPerform
 * DESCR: Performs the specified command 'cmd' that was read from the test input file.
 *------------------------------------------------------------------------------------------------------------*/
static void ListTestPerform
    (
    char *pCmd
    )
{
    if      (streq(pCmd, "append"))    ListTestCmdAppend();
    else if (streq(pCmd, "copy"))      ListTestCmdCopy();
    else if (streq(pCmd, "create"))    ListTestCmdCreate();
    else if (streq(pCmd, "free"))      ListTestCmdFree();
    else if (streq(pCmd, "find"))      ListTestCmdFind();
    else if (streq(pCmd, "findat"))    ListTestCmdFindAt();
    else if (streq(pCmd, "insert"))    ListTestCmdInsert();
    else if (streq(pCmd, "insertat"))  ListTestCmdInsertAt();
    else if (streq(pCmd, "print"))     ListTestCmdPrint();
    else if (streq(pCmd, "printr"))    ListTestCmdPrintRev();
    else if (streq(pCmd, "remove"))    ListTestCmdRemove();
    else if (streq(pCmd, "removeat"))  ListTestCmdRemoveAt();
    else fprintf(stdout, "Unknown command '%s', ignoring.\n", pCmd);
}

/*--------------------------------------------------------------------------------------------------------------
 * FUNCT: ListTest
 * DESCR: Tests the linked list implementation by reading and performing various commands from a testing input
 *        file.
 *------------------------------------------------------------------------------------------------------------*/
static void ListTest
    (
    )
{
    char cmd[9];
    ListManInit();
    while (fscanf(gFin, "%s", cmd) != EOF) ListTestPerform(cmd);
}
