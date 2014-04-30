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
 * 29 Feb 2012 [KRB] Initial revision.
 **************************************************************************************************************/
#include <stdio.h>    /* For FILE, fprintf(), fscanf(), NULL */
#include <stdlib.h>   /* For exit() */
#include "ListMan.h"
#include "SList.h"
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

static void ListTestCmdCreate
    (
    );

static void ListTestCmdFind
    (
    );

static void ListTestCmdFree
    (
    );

static void ListTestCmdInsert
    (
    );

static void ListTestCmdPrint
    (
    );

static void ListTestCmdRemove
    (
    );

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
 *        determine if the SListAppend() function worked correctly.
 * PCODE:
 * Read the 'listname' and 'data' value from gFin.
 * Call ListManGetList() to get the list ptr from the list manager database.
 * Call SListAppend() to append 'data' to the list.
 * If the append succeeded then print "appended " data " to " listname.
 *  Else print "failed to append " data " to " listname.
 *------------------------------------------------------------------------------------------------------------*/
static void ListTestCmdAppend
    (
    )
{
    char listname[8];
    int data;
      SList *list;
    fscanf(gFin, "%s%d", listname, &data);
    list = ListManGetList(listname);
    if (SListAppend(list, data)) fprintf(gFout, "appended %d to %s\n", data, listname);
    else fprintf(gFout, "failed to append %d to %s\n", data, listname);
}

/*--------------------------------------------------------------------------------------------------------------
 * FUNCT: ListTestCmdCreate
 * DESCR: Performs the "create list" command.
 * PCODE:
 * Read the 'listname' from gFin.
 * Call SListAlloc() to create the new list.
 * If the new list was created then
 *   Call ListManCreateList() to add the new list to the list manager database.
 *   Print listname " created".
 * Else
 *   Print "failed to create " listname.
 * EndIf
 *------------------------------------------------------------------------------------------------------------*/
static void ListTestCmdCreate
    (
    )
{
    char listname[8];
    fscanf(gFin, "%s", listname);
       SList *new_list = SListAlloc();
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
 * Read the 'listname' and 'data' value from gFin.
 * Call ListManGetList() to get the list ptr from the list manager database.
 * Call SListFind() to search for 'data'.
 * If 'data' was found then print "found " data " in " listname.
 * Else print "did not gFind " data " in " listname.
 *------------------------------------------------------------------------------------------------------------*/
static void ListTestCmdFind
    (
    )
{
    char listname[8];
    int data;
       SList *list;
    SListNode *found_node;
    fscanf(gFin, "%s%d", listname, &data);
    list = ListManGetList(listname);
    found_node = SListFind(list, data);
    if (found_node) fprintf(gFout, "found %d in %s\n", data, listname);
    else fprintf(gFout, "failed to find %d in %s\n", data, listname);
}

/*--------------------------------------------------------------------------------------------------------------
 * FUNCT: ListTestCmdFree
 * DESCR: Performs the "free list" command.
 * PCODE:
 * Read the 'listname' from gFin.
 * Call ListmanGetList() to get the list ptr from the list manager database.
 * If the list exists
 *   Call SListFree() to free the list.
 *   Call ListManFreeList() to remove the list from the list manager database.
 *   If list was successfully freed by SListFree() then print "freed " listname.
 *   Else print "failed to free %s" listname
 * Else
 *   Print "error " followed by listname followed by " does not exist".
 * EndIf
 *------------------------------------------------------------------------------------------------------------*/
static void ListTestCmdFree
    (
    )
{
    char listname[8];
       SList *list;
    fscanf(gFin, "%s", listname);
    list = ListManGetList(listname);
    if (list) {
        list = SListFree(list); /* Sanity check. list will be NULL. */
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
 * Read the 'listname', the 'index', and the 'data' value from gFin.
 * Call ListManGetList() to get the list ptr from the list manager database.
 * Call SListInsert() to insert a new node containing 'data' at 'index'.
 * If succeeded then print "inserted " data " at " index " of " listname.
 * Else print "could not insert " data " at " index " of " listname.
 *------------------------------------------------------------------------------------------------------------*/
static void ListTestCmdInsert
    (
    )
{
    char listname[8];
    int data, index;
       SList *list;
    fscanf(gFin, "%s%d%d", listname, &index, &data);
    list = ListManGetList(listname);
    if (SListInsert(list, index, data)) fprintf(gFout, "inserted %d at %d in %s\n", data, index, listname);
    else fprintf(gFout, "failed to insert %d  %d in %s\n", data, index, listname);
}

/*--------------------------------------------------------------------------------------------------------------
 * FUNCT: ListTestCmdPrint
 * DESCR:Performs the "print list" command.
 * PCODE:
 * Read the 'listname' from the input file
 * Call ListManGetList() to get the list ptr from the list manager database.
 * If the list exists, then call SListDebugPrint()
 * Else print listname " does not exist"
 *------------------------------------------------------------------------------------------------------------*/
static void ListTestCmdPrint
    (
    )
{
    char listname[8];
    fscanf(gFin, "%s", listname);
       SList *list = ListManGetList(listname);
    if (list) {
        fprintf(gFout, "%s = ", listname);
        SListDebugPrint(gFout, list);
        fprintf(gFout, "\n");
    } else {
        fprintf(gFout, "%s does not exist\n", listname);
    }
}

/*--------------------------------------------------------------------------------------------------------------
 * FUNCT: ListTestCmdRemove
 * DESCR Performs the "remove list data" command.
 * PCODE:
 * Read the 'listname' and 'data' value from gFin.
 * Call ListManGetList() to get the list ptr from the list manager database.
 * Call SListRemoveData()
 * If the remove succeeded then print "removed " data " from " listname.
 * Else print "failed to remove " data " from " listname.
 *------------------------------------------------------------------------------------------------------------*/
static void ListTestCmdRemove
    (
    )
{
    char listname[8];
    int data;
       SList *list;
    fscanf(gFin, "%s%d", listname, &data);
    list = ListManGetList(listname);
    if (SListRemove(list, data)) fprintf(gFout, "removed %d from %s\n", data, listname);
    else fprintf(gFout, "failed to remove %d from %s\n", data, listname);
}

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
    if      (streq(pCmd, "append")) ListTestCmdAppend();
    else if (streq(pCmd, "create")) ListTestCmdCreate();
    else if (streq(pCmd, "free"))   ListTestCmdFree();
    else if (streq(pCmd, "find"))  ListTestCmdFind();
    else if (streq(pCmd, "insert")) ListTestCmdInsert();
    else if (streq(pCmd, "print"))  ListTestCmdPrint();
    else if (streq(pCmd, "remove")) ListTestCmdRemove();
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
