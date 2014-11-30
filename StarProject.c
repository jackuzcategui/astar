//
//  StarProject.c
//  AStar
//
//  Created by Suiz Uzcategui on 21/11/14.
//  Copyright (c) 2014 ___JuanUzcategui___. All rights reserved.
//

#include <stdio.h>
#include <string.h>

/*************************************************************
 * Function to compare two elements (strings) : based on strcmp
 * @param s1 the first string to compare
 * @param s2 the second string to compare
 * @return <0 if s1 is less than s2
 * @return 0 if s1 equals s2
 * @return >0 otherwise
 *************************************************************/
static int compString (void * s1, void * s2) {
    return strcmp((char*)s1, (char*)s2);
}