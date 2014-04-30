/***************************************************************************************************************
 * FILE: ListMan.h
 *
 * DESCRIPTION
 * The "list manager" can be used to manage the lists that are being created, modified, and destroyed during
 * testing. See the comments in ListMan.c for more information.
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
#ifndef __LISTMAN_H__
#define __LISTMAN_H__

#include "DList.h"

/*==============================================================================================================
 * Global function declarations. See function comments in ListMan.c
 *============================================================================================================*/
extern void ListManCreateList
    (
    char  *pListName,
    DList *pNewList
    );

extern void ListManFreeList
    (
    char *pListname
    );

extern DList *ListManGetList
    (
    char *pListName
    );

extern void ListManInit
    (
    );

#endif
