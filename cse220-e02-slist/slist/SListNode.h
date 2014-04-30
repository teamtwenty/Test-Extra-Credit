/***************************************************************************************************************
 * FILE: SListNode.h
 *
 * DESCRIPTION
 * Declaration of a node in a singly-linked list. The data stored in each node is an int.
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
#ifndef __SLISTNODE_H__
#define __SLISTNODE_H__

#include <stdio.h>  /* For FILE */

/*==============================================================================================================
 * Typedefs.
 *
 * Remember, the syntax of a typedef statement is: typedef existing-data-type new-name-for-existing-data-type ;
 * In the typedef below, the existing data type is the struct starting with the word "struct" continuing to the
 * closing right brace. The new name is "SListNode". Recall, there are basically three different ways you can
 * define a struct variable. Let's suppose we want to define a struct variable named 'p' which represents a
 * Point located at an (x, y) coordinate.
 *
 * Method 1.
 *
 *      struct {
 *          int x;
 *          int y;
 *      } p;
 *
 * Advantage: Simplest way to define a struct variable.
 *
 * Disadvantage: The struct data type does not have a name. Cannot create another variable of this struct type
 * without writing something like,
 *
 *      struct {
 *          int x;
 *          int y;
 *      } q;
 *
 * Furthermore, since the struct does not have a name, you cannot pass p and q as parameters to functions,
 * because there is no data type that can be listed in the function header, e.g.,
 *
 *     void SomeFunction(what-do-you-put-here-to-specify-the-data-type-of-p p) { ... }
 *
 * Summary: This method is really only useful if you intend to only create one instance (variable) of the struct
 * and if you do not intend to pass that variable as a function parameter.
 *
 * Method 2. Use a structure "tag".
 *
 *     struct point {
 *         int x;
 *         int y;
 *     };
 *
 * Here, "point" is a structure tag, essentially a name associated with the struct. This code does not define
 * any variables, but now that we have a name for the struct, we can define variables and use the struct type
 * in a parameter list,
 *
 *     void SomeFunction(struct Point P) { ... }
 *
 *     int main()
 *         struct Point p;
 *         struct Point q;
 *         p.x = 100; p. y = 200;
 *         SomeFunction(q);
 *     }
 *
 * Advantage: No more work than method 1 AND you now have a name for the struct data type.
 *
 * Disadvantage: When using the struct data type you have to remember to write "struct point p" to define p
 * as a variable of this data type. Writing "point p" is not sufficient, and if you are me (you're not, be
 * glad) then you will find yourself constantly omitting the word "struct" and then wondering why you're code
 * does not compile.
 *
 * Method 3. Use a typedef to give a name to the struct data type.
 *
 *     typedef struct {
 *         int x;
 *         int y;
 *     } Point;
 *
 * Here, "Point" is just another name (an alias) for the struct type.
 *
 *     void SomeFunction(Point P) { ... }
 *
 *     int main()
 *         Point p;
 *         Point q;
 *         p.x = 100; p. y = 200;
 *         SomeFunction(q);
 *     }
 *
 * Advantage: You do not have to remember to write "struct Point blah-blah-blah". "Point" looks like a data
 * type (e.g., like int and double).
 *
 * Disadvantage: Some people, including Linus Torvalds the original author of the Linux kernel, argue that
 * using typedefs obscures the code [3]. When writing "struct Point p" or "struct Point *p" it's obvious to
 * the reader that p is a struct or a pointer to a struct. In "Point p" or "Point *p" it's not exactly clear
 * that Point is a struct. The readof the code has to go look somewhere else to find the definition of "Point"
 * to understand the code. That is, I believe, a powerful argument. But, somehow I cannot find myself breaking
 * old habits, and many, many years ago, I acquired the habit of using typedefs. And since this is my code,
 * I'm gonna do it my way. Hmmph.
 *
 * By the way, this struct is called a "self-referential" structure, see [1, p. 384], because it contains a
 * pointer data member, mNext, which is a pointer to the same structure type. To define a self-referential
 * structure, you MUST specify a tag, e.g., this structure type can be defined without using typedef this way,
 *
 *     struct SListNode {
 *         int               mData;
 *         struct SListNode *mNext;
 *     }
 *
 *     struct SListNode node1;
 *     struct SListNode *node2;
 *
 * References:
 * 1. C How to Program (the course text book). Chapter 10.
 * 2. http://ee.hawaii.edu/~tep/EE160/Book/chap12/chapter2.1.html
 * 3. http://yarchive.net/comp/linux/typedefs.html
 *============================================================================================================*/
typedef struct SListNode_ {
    int                mData;  /* Each node stores a simple int. */
    struct SListNode_ *mNext;  /* Pointer to the next node in the list. NULL if this is the last node. */
} SListNode;

/*==============================================================================================================
 * Global function declarations. See function comments in SListNode.c
 *============================================================================================================*/
extern SListNode *SListNodeAlloc
    (
    int        pData,
    SListNode *pNext
    );

extern void SListNodeDebugPrint
    (
    FILE      *pStream,
    SListNode *pNode
    );

extern SListNode *SListNodeFree
    (
    SListNode *pNode
    );

extern int SListNodeGetData
    (
    SListNode *pNode
    );

extern SListNode *SListNodeGetNext
    (
    SListNode *pNode
    );

extern void SListNodeSetData
    (
    SListNode *pNode,
    int        pData
    );

extern void SListNodeSetNext
    (
    SListNode *pNode,
    SListNode *pNext
    );

#endif
