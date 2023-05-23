#include "..//include//match.h"
#include "..//include//player.h"
#include "..//include//team.h"


#include <stdlib.h>
#include <string.h>
#include <math.h>

#define EPS 10E-5

//function used to create a queue of teams
TeamsQueue *createQueueTeam() {
    TeamsQueue *queue = (TeamsQueue *)malloc(sizeof(TeamsQueue));

    if (queue == NULL)
        return (TeamsQueue *)NULL;
    queue->front = queue->rear = NULL;

    return queue;
}

//function used to check if a queue is empty
int isQueueEmpty(TeamsQueue *queue) {
    return (queue->front == NULL);
}

//function used to dequeue a team from a queue and return it
TeamNode *deQueueTeam(TeamsQueue *queue) {
    if (isQueueEmpty(queue))
        return (TeamNode *)NULL;

    if (queue->front == queue->rear) 
        queue->rear = NULL;
    
    TeamNode *team;
    team = queue->front;
    queue->front = (queue->front)->nextTeam;
    team->nextTeam = NULL;

    return team;
}

//function used to enqueue a team in a queue
void enQueueTeam(TeamsQueue *queue, TeamNode **value) {
    TeamNode *newNode = *value;

    // copy data from a given team node
    newNode->nextTeam = NULL;
    if (queue->rear == NULL) {
        queue->rear = newNode;
        queue->rear->nextTeam = NULL;

    } else {
        (queue->rear)->nextTeam = newNode;
        (queue->rear) = newNode;
    }

    if (queue->front == NULL) 
        queue->front = queue->rear;
}

//function used to check if a stack is empty
int isStackEmpty(TeamNode *top) {
    return (top == NULL);
}

//function used to pop a team from a stack and return it
TeamNode *pop(TeamNode **top) {
    if (isStackEmpty(*top))
        return (TeamNode *)NULL;

    TeamNode *team = (*top);
    *top = (*top)->nextTeam;
    team->nextTeam = NULL;
    return team;
}

//function used to push a team in a stack
void push(TeamNode **top, TeamNode **value) {
    TeamNode *newNode = *value;
    newNode->nextTeam = *top;
    *top = newNode;
}

//function used to push a team in a stack with deep copy
//ignoring the players field
void pushWithDuplicate(TeamNode **top, TeamNode *value) {
    TeamNode *newNode = (TeamNode *)malloc(sizeof(TeamNode));
    // copy data from a given team node
    newNode->teamName = (char *)malloc(sizeof(char) * (strlen(value->teamName) + 1));
    strcpy(newNode->teamName, value->teamName);
    newNode->score = value->score;
    newNode->players = NULL;
    newNode->nextTeam = *top;
    *top = newNode;
}

//function used to enqueue all teams from list in a queue
void preparingMatches(TeamsQueue *teamQueue, TeamNode **head) {
    TeamNode *aux = NULL;
    while (*head != NULL) {
        aux = *head;
        *head = (*head)->nextTeam;
        enQueueTeam(teamQueue, &aux);
    }
}

//function used to deallocate memory for a stack
void freeStack(TeamNode **stackTop) {
    TeamNode *aux = NULL;
    while (!isStackEmpty(*stackTop)) {
        aux = *stackTop;
        (*stackTop) = (*stackTop)->nextTeam;
        free(aux->teamName);
        freePlayers(&(aux->players));
        free(aux);
    }
}

//function used to print the winners of a particular round
void printRound(TeamsQueue *teamsQueue, int round, char *outputFilePath) {
    FILE *outputFile = fopen(outputFilePath, "at");
    fprintf(outputFile, "--- ROUND NO:%d\n", round);
    TeamNode *teams = teamsQueue->front;
    while (teams != NULL) {
        fprintf(outputFile, "%-32s - %32s\n", teams->teamName, teams->nextTeam->teamName);

        teams = teams->nextTeam->nextTeam;
    }
    fprintf(outputFile, "\n");
    fclose(outputFile);
}

//function used to simulate the matches and print the winners
void simulatingMatches(TeamsQueue *teamsQueue, int *numberOfTeams, char *outputFilePath, int task, TeamNode **lastWinners) {
    FILE *outputFile = fopen(outputFilePath, "at");
    fprintf(outputFile, "\n");
    fclose(outputFile);
    TeamNode *losersStack = NULL;
    TeamNode *winnersStack = NULL;
    int round = 1;
    while (*numberOfTeams > 1) {
        printRound(teamsQueue, round, outputFilePath);
        for (int i = 0; i < *numberOfTeams / 2; i++) {
            TeamNode *firstTeam = deQueueTeam(teamsQueue);
            TeamNode *secondTeam = deQueueTeam(teamsQueue);
            if ((firstTeam->score - secondTeam->score) >= EPS) {
                firstTeam->score = firstTeam->score + 1;
                push(&winnersStack, &firstTeam);
                push(&losersStack, &secondTeam);
            } else {
                secondTeam->score = secondTeam->score + 1;
                push(&winnersStack, &secondTeam);
                push(&losersStack, &firstTeam);
            }
        }
        printWinners(winnersStack, outputFilePath, round, *numberOfTeams);
        if (*numberOfTeams == 16 && task) {
            TeamNode *aux = winnersStack;
            while (aux != NULL) {
                pushWithDuplicate(lastWinners, aux);
                aux = aux->nextTeam;
            }
        }
        while (!isStackEmpty(winnersStack)) {
            TeamNode *aux = pop(&winnersStack);
            enQueueTeam(teamsQueue, &aux);
        }
        freeStack(&losersStack);
        losersStack = NULL;
        *numberOfTeams /= 2;
        round++;
    }
    freePlayers(&teamsQueue->front->players);
    free(teamsQueue->front->teamName);
    free(teamsQueue->front);
}


//function used to print the queue
void printQueue(TeamsQueue *queue, char *outputFilePath) {
    FILE *outputFile = fopen(outputFilePath, "at");
    TeamNode *teams = queue->front;
    fprintf(outputFile, "%c", '\n');
    while (teams != NULL) {
        fprintf(stdout, "%s", teams->teamName);
        teams = teams->nextTeam;
    }
    fclose(outputFile);
}


//function used to print the winners of a round from a stack 
void printWinners(TeamNode *stackTop, char *outputFilePath, int round, int numberOfPlayers) {
    FILE *outputFile = fopen(outputFilePath, "at");
    fprintf(outputFile, "WINNERS OF ROUND NO:%d\n", round);
    while (stackTop != NULL) {
        fprintf(outputFile, "%-32s  -  %.2f\n", stackTop->teamName, stackTop->score);
        stackTop = stackTop->nextTeam;
    }

    if (numberOfPlayers != 2)
        fprintf(outputFile, "\n");
    fclose(outputFile);
}
