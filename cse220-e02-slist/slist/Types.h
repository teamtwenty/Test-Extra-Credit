/***************************************************************************************************************
 * FILE: Types.h
 *
 * DESCRIPTION
 * Useful defined types.
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
 * 24 Jan 2012 [KRB] Initial revision.
 **************************************************************************************************************/
#ifndef __TYPES_H__  /* Preprocessor guard to prevent Types.h from being included more than once */
#define __TYPES_H__  /* See comments in Main.h. */

/*==============================================================================================================
 * Global type definitions.
 *
 * Study the preprocessor macros for false and true that are defined below before reading the rest of this
 * comment.
 *
 * A "preprocessor macro" is defined with the #define directive. The basic syntax is,
 *
 *     #define  something  to-be-equiv-to-something-else
 *
 * So, we are defining "false" to be equivalent to (0). And we are defining "true" to be equivalent to
 * (!(false)). But remember, false is now equivalent to (0), so this says that "true" is equivalent to (!(0)).
 *
 * In ANSI (Standard) C there is not a boolean data type. Historically, booleans were represented by some
 * signed integeral type (e.g., int, or signed char) and a zero value was equivalent to false and a nonzero
 * value was equivalent to true. Therefore, the typedef below defines "bool" to be equivalent to "signed char".
 * Note that typedef does not really define a new type from scratch; it merely states that a new name is being
 * used for an existing type. We can say that "bool" is an alias for "signed char", so a typedef simply
 * creates an alias for an existing data type. Why would you want to do this? Because it makes your code more
 * readable, e.g.,
 *
 * Old way of doing boolean variables          New way of doing boolean variables
 * ----------------------------------          ----------------------------------
 * int found = 0;                              bool found;
 * while (!found) {                            while (!found) {
 *     ...                                         ...
 *     found = 1;  -- Found it!                    found = true;  -- Found it!
 * }                                           }
 *
 * Note, I used "signed char" because in most C compilers a char is 1-byte versus either 4- or 8-bytes for
 * an int. And, chars can be signed (store positive and negative integer values) or unsigned (store only
 * positive integer values). Whether chars are signed or unsigned by default is usually a compiler option
 * that can be flipped one way or the other way. If you don't know whether your compiler treats "char" as
 * "signed char" or "unsigned char" by default, then it is safest to be explicit about it. Either way, it
 * is important that bool be a signed data type because any nonzero value (including -1, -7, and -131) are
 * all considered to be true.
 *
 * In closing, the syntax for a typedef statement is,
 *
 *     typedef  existing-data-type  alias-for-existing-data-type ;
 *
 * and remember, that alias-for-existing-data-type is not really a new type but rather (get ready for this)
 * just an alias for an existing data type.
 *============================================================================================================*/
typedef signed char bool;

/*==============================================================================================================
 * Global preprocessor macros.
 *
 * Preprocessor Define Rule #1: It's good to parenthesize the hell out of these things.
 *
 * Why? Well, one reason is that preprocessor macro functions can also be defined using the syntax,
 *
 *     #define something-which-looks-like-a-function(with-paramters) to-be-equiv-to-something-else
 *
 * For example,
 *
 *     #define ToRadians(angle_in_degs)  angle_in_degs * M_PI / 180.0
 *
 *     ...
 *
 *     double SomeTrigLikeFunction(double angle1_in_degs, double angle2_in_degs)
 *     {
 *         ...
 *         double s = sin(ToRadians(angle1_in_degs + angle2_in_degs));
 *         ...
 *     }
 *
 * Now, consider the code generate by the preprocessor for this ToRadians macro (which ain't a function
 * but it suuuuurre looks like a function). The preprocessor simply performs "textual substitutation", so
 * the output from the preprocessor looks like this,
 *
 *     double SomeTrigLikeFunction(double angle1_in_degs, double angle2_in_degs)
 *     {
 *         ...
 *         double s = sin(angle1_in_degs + angle2_in_degs * M_PI / 180.0);
 *         ...
 *     }
 *
 * Now if you look at the original nonpreprocessed code, it appears that the programmer intends to add the
 * two angles and then convert the sum into an angle in radians. But, if you look at the preprocessed code
 * it appears that angle2_in_degs will be converted into an angle in radians which will then be added to
 * angle1_in_degs (which is in degrees). Why? Because * and / have higher precedence than +. How to fix this?
 * Parenthesize the hell out of the parameters to the ToRadians macro function, viz.,
 *
 *     #define ToRadians(angle_in_degs)  (((angle_in_degs) * M_PI) / 180.0)
 *
 * Now the "preprocessor macro function call in SomeTrigLikeFunction() will be converted to,
 *
 *         double s = sin((((angle1_in_degs + angle2_in_degs) * M_PI) / 180.0));
 *
 * which IS CORRECT.
 *============================================================================================================*/
#define false (0)
#define true  (!(false))

#endif /* __TYPES_H__ */
