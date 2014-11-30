//
//  Map.c
//  AStar
//
//  Created by Suiz Uzcategui on 07/11/14.
//  Copyright (c) 2014 ___JuanUzcategui___. All rights reserved.
//

#include "Map.h"
#include <string.h>
#include <math.h>
#include "ListTest.c"

#define distanceRatio 0.3

List *loadMap (FILE *f) {
    
    List *l = newList(compString, prString);
    
    List *neighborList = newList(compString, prString);
    
    char line[100];
    char * token;
    char insertArray[189][100];
    
    int tokenIteration = 0;
    
    while(!feof(f)) {
        
        if (fgets(line,100,f)) {
            
            long len = strlen(line);
            
            if (strlen(line) > 1) {
                if( line[len-1] == '\n' ) {
                    line[len-1] = 0;
                }
            }
            else {
                
                City *city = (City*)malloc(sizeof(City));
                
                for (int i = 0; i < tokenIteration; i++) {
                    
                    if (i == 0) {
                        strcpy(city->name, insertArray[i]);
                    }
                    if (i == 1) {
                        city->latitude = atoi(insertArray[i]);
                    }
                    if (i == 2) {
                        city->longitude = atoi(insertArray[i]);
                        
                        city->g = 0;
                        
                        addList(l, city);
                        neighborList = newList(compString, prString);
                    }
                    if (i > 2) {
                        if (i % 2 != 0) {
                            Neighbor *neighbor = (Neighbor*)malloc(sizeof(Neighbor));
                            
                            strcpy(neighbor->name, insertArray[i]);
                            neighbor->distance = atoi(insertArray[i + 1]);
                            
                            addList(neighborList, neighbor);
                        }
                    }
                    
                }
                
                city->neighbors = neighborList;
                
                tokenIteration = 0;
                neighborList = newList(compString, prString);
                
            }
            
            token = strtok (line,"\t");
            
            while (token != NULL)
            {
                if (strlen(line) > 1) {
                    if( line[len-1] != '\n' ) {
                        //printf("[%s]\n", token);
                        strcpy (insertArray[tokenIteration], token);
                        tokenIteration++;
                    }
                }
                
                token = strtok (NULL, "\t");
            }
        }
    }
    
    return l;
}

int isCity(char*token) {
    
    long len = strlen(token);
    
    if (compString(token, "BREAK") == 0) {
        return 2;
    }
    
    for (int i = 0; i < len; i++) {
        if (token[i] > '9' || token[i] < '0') {
            if (token[i] != '-') {
                return 1;
            }
        }
    }
    
    return 0;
}

void prCity(void *s)
{
    City *city = malloc(sizeof(City));
    
    city = s;
    
    printf("[%s: (%i, %i)]\n\t[Backpath to: %s]\n\t[Distance to Goal: %ikm]\n", city->name, city->latitude, city->longitude, city->link->name, city->h);
    printf("\t[Distance from Start: %ikm]\n", city->g);
    displayNeighbors(city->neighbors);
    
}

void prNeighbor(void *s)
{
    Neighbor *city = malloc(sizeof(Neighbor));
    
    city = s;
    
    printf("\t[Distance to %s: %ikm ]\n", city->name, city->distance);
    
}

void displayNeighbors(List *s) {
    
    Node *forEachNode= (Node*)malloc(sizeof(Node));
    forEachNode = s->head;
    
    for (int i = 1; i <= s->nelts; i++) {
        prNeighbor(forEachNode->val);
        
        forEachNode = forEachNode->next;
    }
    
}

void displayMap (List *s) {
    
    Node *forEachNode= (Node*)malloc(sizeof(Node));
    forEachNode = s->head;
    
    for (int i = 1; i <= s->nelts; i++) {
        prCity(forEachNode->val);
        
        forEachNode = forEachNode->next;
    }
    
}

int estimateDistance(City *startCity, City *endCity) {
    
    int distance;
    
    double x1 = startCity->latitude;
    double y1 = startCity->longitude;
    double x2 = endCity->latitude;
    double y2 = endCity->longitude;
    
    distance = distanceRatio * sqrt(pow(abs((x2 - x1)), 2) + pow(abs(y2 - y1), 2));
    
    return distance;
}

void aStar (City *startCity, City *endCity, List *s) {
    
    List* closed = newList(compString, prString);
    List* open = newList(compString, prString);
    
    City *newCity = (City*)malloc(sizeof(City));
    newCity = startCity;
    
    startCity->g = 0;
    
    addList(open, newCity);
    
    while (lengthList(open) != 0) {
        
        sortMapByF(open, endCity);
        
        Node *n = open->head;
        
        City *currentCity = n->val;
        
        remFromList(open, currentCity);
        
        addList(closed, currentCity);
        
        if (compString(currentCity->name, endCity->name) == 0) {
            
            displayPath(currentCity);
            
            return;
        }
        
        List *si = currentCity->neighbors;
        Node *currentNeighbor = si->head;
        
        for (int i = 0; i < si->nelts; i++) {
            
            Neighbor *currentNeighborData = currentNeighbor->val;
            
            int gofncsi = currentCity->g + currentNeighborData->distance;
            
            City* gofsi = currentNeighborData->cityNode;
            
            if (isInList(open, currentNeighborData->name) != 0 || isInList(closed, currentNeighborData->name) !=0) {
            
                if (gofncsi < gofsi->g) {
                    
                    gofsi->g = gofncsi;
                
                    if (isInList(open, currentNeighborData->name) != 0) {
                        remFromList(open, currentNeighborData->cityNode);
                    }
                    
                    if (isInList(closed, currentNeighborData->name) != 0) {
                        remFromList(closed, currentNeighborData->cityNode);
                    }
                    
                }
                
            }
            else {
                
                currentNeighborData->cityNode->g = gofncsi;
                gofsi->link = currentCity;
                addList(open, gofsi);
            }
            
            currentNeighbor = currentNeighbor->next;
        }
        
    }
    
    printf("\nA route between %s and %s could not be found...\n", startCity->name, endCity->name);
}

City *findCity (List *s, char  *e) {
    if(isInList(s, e) != 0) {
        Node *foundNode = (Node *)malloc(sizeof(Node));
        City *foundCity = (City *)malloc(sizeof(City));
        
        foundNode = isInList(s, e);
        
        foundCity = foundNode->val;
        
        return foundCity;
    }
    
    return 0;

}

void sortNeighbors(List *s) {
    
    Node *tmpPtr = s->head;
    Node *tmpNxt = s->head->next;
    
    Neighbor* thisNeighbor = (Neighbor*)malloc(sizeof(Neighbor));
    Neighbor* nextNeighbor = (Neighbor*)malloc(sizeof(Neighbor));
    
    Node *tmp;
    
    while(tmpNxt != NULL) {
        
        while(tmpNxt != tmpPtr) {
            
            thisNeighbor = tmpNxt->val;
            nextNeighbor = tmpPtr->val;
            
            if(thisNeighbor->distance < nextNeighbor->distance){
                tmp = tmpPtr->val;
                tmpPtr->val = tmpNxt->val;
                tmpNxt->val = tmp;
            }
            
            tmpPtr = tmpPtr->next;
        }
        
        tmpPtr = s->head;
        tmpNxt = tmpNxt->next;
    }
    
}

void sortMapByF (List *s, City *e) {
    
    Node *tmpPtr = s->head;
    Node *tmpNxt = s->head->next;
    
    City* thisNeighbor = (City*)malloc(sizeof(City));
    City* nextNeighbor = (City*)malloc(sizeof(City));
    
    Node *tmp;
    
    int thisF;
    int nextF;
    
    while(tmpNxt != NULL) {
        
        while(tmpNxt != tmpPtr) {
            
            thisNeighbor = tmpNxt->val;
            nextNeighbor = tmpPtr->val;
            
            thisNeighbor->h = estimateDistance(thisNeighbor, e);
            nextNeighbor->h = estimateDistance(nextNeighbor, e);
            
            thisF = thisNeighbor->g + thisNeighbor->h;
            nextF = nextNeighbor->g + nextNeighbor->h;
            
            if(thisF < nextF){
                tmp = tmpPtr->val;
                tmpPtr->val = tmpNxt->val;
                tmpNxt->val = tmp;
            }
            
            tmpPtr = tmpPtr->next;
        }
        
        tmpPtr = s->head;
        tmpNxt = tmpNxt->next;
    }
    
    tmpPtr = s->head;
    
}

void linkNeighborsToCity (List *l) {
    
    Node *city = (Node*)malloc(sizeof(Node));
    Node *cityPtr = (Node*)malloc(sizeof(Node));
    Node *neighbor = (Node*)malloc(sizeof(Node));
    
    city = l->head;
    
    for (int i = 1; i <= l->nelts; i++) {
        
        City *cityNeighborNode = (City*)malloc(sizeof(City));
        
        cityNeighborNode = city->val;
        
        neighbor = cityNeighborNode->neighbors->head;
        
        for (int j = 1; j <= cityNeighborNode->neighbors->nelts; j++) {
            
            Neighbor *neighborCityNode = (Neighbor*)malloc(sizeof(neighbor));
            
            neighborCityNode = neighbor->val;
            
            cityPtr = l->head;
            
            if (neighborCityNode->cityNode == NULL) {
            
                for (int k = 1; k <= l->nelts; k++) {
                    
                    City *cityName = (City*)malloc(sizeof(City));
                    
                    cityName = cityPtr->val;
                    
                    if (compString(neighborCityNode->name, cityName->name) == 0) {
                        
                        neighborCityNode->cityNode = cityName;
                    }
                    
                    cityPtr = cityPtr ->next;
                }

            }
            
            
            neighbor = neighbor->next;
        }
        
        city = city->next;
    }
    
    return;
    
}

void displayPath (City *currentCity) {
    
    int totalDistance = currentCity->g;
    List *path = newList(compString, prString);
    
    addList(path, currentCity);
    currentCity = currentCity->link;
    
    int actualPosition = 1;
    
    while (currentCity != NULL) {
        addListAt(path, actualPosition, currentCity);
        currentCity = currentCity->link;
        actualPosition++;
    }
    
    Node *prev   = NULL;
    Node * current = path->head;
    Node * next;
    
    while (current != NULL)
    {
        next  = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    path->head = prev;
    
    printf("\n>> TRAVEL PATH: [ ");
    
    Node *printNode= (Node*)malloc(sizeof(Node));
    printNode = path->head;
    
    for (int i = 1; i <= path->nelts; i++) {
        printf("%s ", printNode->val);
        
        if (i != path->nelts) {
            printf("-> ");
        }
        
        printNode = printNode->next;
    }
    
    printf("]\n>> Distance Travelled: %ikm\n", totalDistance);
    
    return;
}