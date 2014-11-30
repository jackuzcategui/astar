//
//  Map.h
//  AStar
//
//  Created by Suiz Uzcategui on 07/11/14.
//  Copyright (c) 2014 ___JuanUzcategui___. All rights reserved.
//

#ifndef __AStar__Map__
#define __AStar__Map__
#define CITYNAME 30

#include <stdio.h>
#include "List.h"

//City structure
typedef struct City {
    char name[CITYNAME + 1];
    List *neighbors;
    int longitude, latitude;
    int g, h;
    struct City *link;
}City ;

//Neighbor structure
typedef struct Neighbor {
    char name[CITYNAME + 1];
    int distance;
    City *cityNode;
}Neighbor;


/** Loads Map from the specified file
 * @param FILE* - The file object
 * returns the completed list with Cities, coordinates, neighbors, initial distances, etc...
 */

List *loadMap(FILE *);

/** Checks to city if string can be equated to a City in the list
 * @param char* - a string of characters that spells the name of the City
 * @return 2 if string is empty
 * @return 1 if it finds the City
 * @return 0 if it does not find the City
 */
int isCity(char*);

/** Prints City when required by displayMap
 * @param void* - the City Node to be printed
 */
void prCity (void *);

/** Prints Neighbor node when required by displayNeighbors
 * @param void* - the Neighbor node to be printed
 */
void prNeighbor (void *);

/** Prints a list of neighbors from the Neighbor list in City when required by displayMap
 * @param List* - the list of Neighbors inside the City Node
 */
void displayNeighbors (List *);

/** Prints the Map. Cities with their coords, list of neighbors, distances, etc.
 * @param List* - the list of nodes built on main which contains all cities and their neighbors
 */
void displayMap (List *);

/** Heuristic function that calculates the distance between two cities based on their coordinates
 * @param City* - City node 1
 * @param City* - City node 2
 * returns the distance between those cities rounded up
 */
int estimateDistance(City *, City *);

/** A* function that performs the main goal of the program
 * @param City* - START CITY for the calcuation
 * @param City* - END CITY for the calculation
 * @param List* - List of city and neighbors loaded from external file
 */
void aStar (City*, City*, List*);

/** Checks to see if a string of characters exists as a City in the map List. Returns the City node
 * @param List* - List of cities and neighbords loaded from external file
 * @param char* - String of characters to check if it represents a City in file
 * returns the City node if found
 * returns 0 if it is not present
 */
City *findCity (List *, char *);

/** Iterates through cities and sorts their list of Neighbors by their distance from the City
 * @param List* - List of cities and neighbors loaded from external file
 */
void sortNeighbors (List *);

/** Sorts the main Map list by their f(n) function which is calculated through g(n) + h(n)
 * @param List* - List of cities and neighbors loaded from external file
 * @param City* - END CITY to be able to calculate the heuristic function
 */
void sortMapByF (List *, City *);

/** Once the main Map list has been compiled, this function iterates through the Neighbor Nodes
 *  of each City in order to link their City *link pointer back to the corresponding City node
 * @param List* - List of cities and neighbors loaded from external file
 */
void linkNeighborsToCity (List*);

/** Formats and displays the resulting path list from A*. Uses City->g to print distance travelled.
 * @param City* - Current city where the A* algorithm stopped, also known as END CITY
 */
void displayPath (City*);

#endif /* defined(__AStar__Map__) */
