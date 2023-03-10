#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "booleanEvaluation.h"
#include "booleanWithError.h"
#include "stack.h"

/* TODO
 * printName
 * input: none
 * output: none
 *
 * Prints name of the student who worked on this solution
 */
void printName()
{
    /* TODO : Fill in your name */
    printf("This solution was completed by:\n");
    printf("<Ryan Reddoch>\n");
}

/* TODO
 * evaluatePostfix
 * input: a postfix expression (calls tokenizeString to get the tokens from the
 * string) output: T, F, or E
 *
 * Uses a stack to evaluates the postfix expression and returns the result as a
 * string where "T" denotes true and "F" denotes false. If the postfix
 * expression is invalid it returns "E" to denote an error has occurred.  Be
 * sure to use the helpful functions in booleanEvaluation.
 *
 * Hints:
 * - DO NOT free the parameter str.  It is freed by the calling function.
 * - Be sure to use the helpful functions in booleanEvaluation.
 * - Test your code often!  Get it working correctly for the first couple test
 * cases instead of trying to solve all of them at once.
 */
char *evaluatePostfix(char *str)
{

    Stack *s = createStack();

    char *op1;   // holds 1st operand
    char *op2;   // holds 2nd operand
    char *x[10]; // holds operator;
    char *testArray[] = {"NOT", "AND", "NAND", "OR",
                         "NOR", "XOR", "COND", "BICOND"};

    int i = 0;
    int j = 0;
    int count = 0; /* counts T and F*/
    boolean res;
    boolean bool;
    boolean bool2;
    int tokenCount; /*# of Tokens*/
    char **arrTokens = tokenizeString(str, &tokenCount);

    op1 = (char *)malloc(sizeof(char) * count);
    op2 = (char *)malloc(sizeof(char) * count);
    /* Your variable Declarations: */

    /* Currently commented out to prevent a memory leak.  Uncomment to get the
     * tokens from str. */

    for (i = 0; i < tokenCount; i++)
    {
        /* PARSE THROUGH ARRTOKENS FOR T AND F and Push EM' */
        if (strequals(arrTokens[i], "T") || strequals(arrTokens[i], "F"))
        {
            /* count counts the number of T and F */
            count++;
            push(s, arrTokens[i]);
        }
        /* NOT START */

        if (strequals(arrTokens[i], "NOT") && tokenCount <= 2)
        {
            op1 = pop(s);
            if (strequals(op1, "T"))
            {

                op1 = "F";
                res = stringToBoolean(op1);
            }

            else if (strequals(op1, "F"))
            {
                op1 = "T";
                res = stringToBoolean(op1);
            }
        }
        /*NOT END */

        /*AND START*/
        if (strequals(arrTokens[i], "AND") && tokenCount <= 3)
        {
            op2 = pop(s);
            op1 = pop(s);

            if (strequals(op1, "T") && strequals(op2, "T"))
            {
                res = stringToBoolean(op1);
            }
            else
            {
                res = stringToBoolean("F");
            }
        }
        /*AND END*/

        /*NAND START*/

        if (strequals(arrTokens[i], "NAND") && tokenCount <= 3)
        {
            op2 = pop(s);
            op1 = pop(s);

            if (strequals(op1, "T") && strequals(op2, "T"))
            {
                res = stringToBoolean("F");
            }
            else
            {
                res = stringToBoolean("T");
            }
        }
        /*END NAND*/

        /*START OR*/
        if (strequals(arrTokens[i], "OR") && tokenCount <= 3)
        {
            op2 = pop(s);
            op1 = pop(s);

            if (strequals(op1, "T") || strequals(op2, "T"))
            {
                res = stringToBoolean("T");
            }
            else
            {
                res = stringToBoolean("F");
            }
        }
        /*END OR*/

        /*START XOR*/
        if (strequals(arrTokens[i], "XOR") && tokenCount <= 3)
        {
            op2 = pop(s);
            op1 = pop(s);

            if (strequals(op1, "T") && strequals(op2, "F") ||
                strequals(op1, "F") && strequals(op2, "T"))
            {
                res = stringToBoolean("T");
            }
            else
            {
                res = stringToBoolean("F");
            }
        }
        /*END XOR*/

        /*START NOR*/
        if (strequals(arrTokens[i], "NOR") && tokenCount <= 3)
        {
            op2 = pop(s);
            op1 = pop(s);

            if (strequals(op1, "F") && strequals(op2, "F"))
            {
                res = stringToBoolean("T");
            }
            else
            {
                res = stringToBoolean("F");
            }
        }
        /*END NOR*/

        /*START COND*/
        if (strequals(arrTokens[i], "COND") && tokenCount <= 3)
        {
            op2 = pop(s);
            op1 = pop(s);

            if (strequals(op1, "T") && strequals(op2, "F"))
            {
                res = stringToBoolean("F");
            }
            else
            {
                res = stringToBoolean("T");
            }
        }
        /*END COND*/

        /*BICOND START */
        if (strequals(arrTokens[i], "BICOND") && tokenCount <= 3)
        {
            op2 = pop(s);
            op1 = pop(s);

            if (strequals(op1, "T") && strequals(op2, "T") ||
                strequals(op1, "F") && strequals(op2, "F"))
            {
                res = stringToBoolean("T");
            }
            else
            {
                res = stringToBoolean("F");
            }
        }
        /*BICOND END*/

        /*MULTI BOOLOEAN START*/
        if (tokenCount > 3)
        {
            /*MULTI NOT START*/
            if (strequals(arrTokens[i], "NOT"))
            {
                op2 = pop(s);
                if (strequals(op2, "T"))
                {
                    push(s, "F");
                }
                else
                {
                    push(s, "T");
                }
            }
            /*MULTI NOT END*/

            /*MULTI AND START*/
            if (strequals(arrTokens[i], "AND"))
            {
                op2 = pop(s);
                op1 = pop(s);
                if (strequals(op1, op2))
                {
                    push(s, "T");
                }
                else
                {
                    push(s, "F");
                }
            }
            /*MULT AND END*/

            /*MULTI NAND START*/
            if (strequals(arrTokens[i], "NAND"))
            {
                op2 = pop(s);
                op1 = pop(s);
                if (strequals(op1, "T") && strequals(op2, "T"))
                {
                    push(s, "F");
                }
                else
                {

                    push(s, "T");
                }
            }
            /*MULTI NAND END*/

            /*MULTI OR START*/
            if (strequals(arrTokens[i], "OR"))
            {
                op2 = pop(s);
                op1 = pop(s);
                if (strequals(op1, "T") || strequals(op2, "T"))
                {
                    push(s, "T");
                }
                else
                {

                    push(s, "F");
                }
            }
            /*MULTI OR END*/

            /*MULTI NOR START*/
            if (strequals(arrTokens[i], "NOR"))
            {
                op2 = pop(s);
                op1 = pop(s);

                if (strequals(op1, "F") && strequals(op2, "F"))
                {
                    push(s, "T");
                }
                else
                {
                    push(s, "F");
                }
            }
            /*MULTI NOR END*/

            /*MULTI XOR START*/
            if (strequals(arrTokens[i], "XOR"))
            {
                op2 = pop(s);
                op1 = pop(s);

                if (strequals(op1, "F") && strequals(op2, "F") ||
                    strequals(op1, "T") && strequals(op2, "T"))
                {

                    push(s, "T");
                }
                else
                {
                    push(s, "F");
                }
            }

            /*MULTI XOR END*/

            /*MULTI COND START*/
            if (strequals(arrTokens[i], "COND"))
            {
                op2 = pop(s);
                op1 = pop(s);

                if (strequals(op1, "T") && strequals(op2, "F"))
                {
                    push(s, "F");
                }
                else
                {
                    push(s, "T");
                }
            }
            /*MULTI COND END*/

            /*MULTI BICOND START*/
            if (strequals(arrTokens[i], "BICOND"))
            {
                op2 = pop(s);
                op1 = pop(s);
                if (strequals(op1, "T") && strequals(op2, "T") ||
                    strequals(op1, "F") && strequals(op2, "F"))
                {

                    push(s, "T");
                }
                else
                {

                    push(s, "F");
                }
            }
            /*MULTI BICOND END*/
            res = stringToBoolean(pop(s));
        }
    }

    // print("FREE TEST \n");
    freeStackElements(s);
    freeStack(s);

    return booleanToString(res);
    /* Replace this with your actual solution to return */
}

//}

/* TODO
 * postfixToInfix
 * input: a postfix expression (calls tokenizeString to get the tokens from the
 * string) output: the equivalent infix expression
 *
 * Uses a stack to convert str to its equivalent expression in infix.
 * You can assume that the postfix expression is valid
 *
 * Hints:
 * - DO NOT free the parameter str.  It is freed by the calling function.
 * - Be sure to use the helpful functions in booleanEvaluation.
 * - Test your code often!  Get it working correctly for the first couple test
 * cases instead of trying to solve all of them at once.
 */

//////////////////////////////////
///////////////////////////////

char *postfixToInfix(char *str)
{
    Stack *s = createStack();
    Stack *s2 = createStack();

    // char *op1; // holds 1st operand
    // char *op2; // holds 2nd operand
    // char *x;   // holds operator;

    int i = 0;
    // int j = 0;

    // int count = 0; /* counts T and F*/

    int tokenCount; /*# of Tokens*/
    char **arrTokens = tokenizeString(str, &tokenCount);

    // int index;

    // char buffer[100];

    char* str1;
    char* str2;
    char* str3;
    char* str4;
    

    // op1 = (char *)malloc(sizeof(char) * count);
    // op2 = (char *)malloc(sizeof(char) * count);
    // x = (char *)malloc(sizeof(char) * count);
    str1 = (char *)malloc(sizeof(char) * 1024);
    str3 = (char *)malloc(sizeof(char) * 1024);
    str4 = (char *)malloc(sizeof(char) * 1024);

    memset(str1, '\0', 1024);
    memset(str3, '\0', 1024);
    memset(str4, '\0', 1024);
    //  result = (char *)malloc(sizeof(char) * index);

    for (i = 0; i < tokenCount; ++i)
    {
        if (strequals(arrTokens[i], "T") || strequals(arrTokens[i], "F"))
        {
            /* count counts the number of T and F */
            push(s, arrTokens[i]);
            //printf("S1: %s\n", arrTokens[i]);
        }
        else
        {
            push(s2, arrTokens[i]);
            //printf("S2: %s\n", arrTokens[i]);
        }
    }

    char* first_op = pop(s2);

    if (strequals(first_op, "NOT"))
    {
        sprintf(str1, "( NOT %s )", "%s");
    }
    else
    {
        sprintf(str1, "( %s %s %s )", "%s", first_op, pop(s));
    }

    printf("%s\n", str1);

    boolean loop_entered = FALSE;

    while (!isEmpty(s2))
    {
        loop_entered = TRUE;
        char* cur_op = pop(s2);

        if (strequals(cur_op, "NOT"))
        {
            sprintf(str4, str1, "( NOT %s )");
        }
        else if (strequals(cur_op, "OR"))
        {
            str2 = pop(s);
           // memset(str3, '\0', 1024);
            sprintf(str3, "( %s %s %s )", str2, cur_op, "%s");
            sprintf(str4, str1, str3);
            strcpy(str1, str4);
            free(str2);
        }
        else
        {
            str2 = pop(s);
           // memset(str3, '\0', 1024);
            sprintf(str3, "( %s %s %s )", "%s", cur_op, str2);
            sprintf(str4, str1, str3);
            strcpy(str1, str4);
            free(str2);
        }

        free(cur_op);
    }
    
    printf("%s\n", str1);

    if (loop_entered)
        sprintf(str1, str4, pop(s));
    else
        sprintf(str1, str1, pop(s));
    
    printf("%s\n", str1);
    
    
    freeStack(s2);
    freeStack(s);

    return str1;
}

/* You may want to create some helper functions down here! */

// return booleanToString(
//     ERROR); /* Replace this with your actual solution to return */

/* You may want to create some helper functions down here! */
