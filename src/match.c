#include "../include/match.h"

#include <stdlib.h>
//create a queue
TeamQueue* createQueue(){
    TeamQueue *q;
    q = (TeamQueue*)malloc(sizeof(TeamQueue));
    if (q==NULL) return NULL;
        q->front = q->rear = NULL;
return q;
}


void enQueueTeam(TeamQueue *q, TeamNode *v) {
    TeamNode *newNode =(TeamNode*)malloc(sizeof(TeamNode));
    newNode = v;
    if (q->rear == NULL) 
        q->rear = newNode;
    else {
        (q->rear)->nextTeam = newNode;
        (q->rear) = newNode;
    }
    
    if (q->front == NULL)
        q->front = q->rear;
}