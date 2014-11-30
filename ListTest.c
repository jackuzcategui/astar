/*************************************************************
 *
 * $Id: ListTest.c 1957 2014-06-12 06:21:22Z phil $
 * 
 *************************************************************
 */
/**
 * Sample test program for generic Lists : application to strings.
 *
 *************************************************************/

static char rcsId[] = "@(#) $Id: ListTest.c 1957 2014-06-12 06:21:22Z phil $";

#include <stdio.h>
#include <string.h>
#include "List.h"


/*************************************************************
 * Function to compare two elements (strings) : based on strcmp
 * @param s1 the first string to compare
 * @param s2 the second string to compare
 * @return <0 if s1 is less than s2
 * @return 0 if s1 equals s2
 * @return >0 otherwise
 *************************************************************/
static int compString (void * s1, void * s2) {
    if (s1 == NULL || s2 == NULL) {
        return 1;
    }
    
    return strcmp((char*)s1, (char*)s2);
}

/*************************************************************
 * Function to display an element of the list
 * @param s the string to display
 *************************************************************
 */
static void prString(void * s) {
  printf("%s",(char*)s);
}

/*************************************************************
 * another display function, just to test "forEach"
 * @param s the string to display
 *************************************************************/
static void prString2 (void * s) {
  printf("%s\n",(char*)s);
}
