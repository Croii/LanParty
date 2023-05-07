#include "..//include//match.h"
#include "..//include//player.h"
#include "../include//team.h"

#include <stdlib.h>
#include <string.h>

#define EPS 10E-5

// create a queue
TeamsQueue *createQueueTeam() {
    TeamsQueue *q = (TeamsQueue *)malloc(sizeof(TeamsQueue));

    if (q == NULL)
        return (TeamsQueue *)NULL;
    q->front = q->rear = NULL;

    return q;
}

int isQueueEmpty(TeamsQueue *q) {
    return (q->front == NULL);
}

TeamNode *deQueueTeam(TeamsQueue *q) {
    if (isQueueEmpty(q))
        return (TeamNode *)NULL;

    if (q->front == q->rear) {
        q->rear = NULL;
    }

    TeamNode *team;
    team = q->front;
    q->front = (q->front)->nextTeam;
    team->nextTeam = NULL;
    return team;
}
void enQueueTeam(TeamsQueue *q, TeamNode **data) {
    TeamNode *newNode = *data;

    // copy data from a given team node
    /*  newNode->players = data->players;
     newNode->score = data->score;
     newNode->teamName = data->teamName; */
    newNode->nextTeam = NULL;
    if (q->rear == NULL) {
        q->rear = newNode;
        q->rear->nextTeam = NULL;

    } else {
        (q->rear)->nextTeam = newNode;
        (q->rear) = newNode;
    }

    if (q->front == NULL) {
        q->front = q->rear;
    }
}

int isStackEmpty(TeamNode *top) {
    return (top == NULL);
}

TeamNode *pop(TeamNode **top) {
    if (isStackEmpty(*top))
        return (TeamNode *)NULL;

    TeamNode *team = (*top);
    *top = (*top)->nextTeam;
    team->nextTeam = NULL;
    return team;
}

void push(TeamNode **top, TeamNode **data) {
    TeamNode *newNode = *data;
    // copy data from a given team node
    /*     newNode->players = data->players;
        newNode->score = data->score;
        newNode->teamName = data->teamName; */

    newNode->nextTeam = *top;
    *top = newNode;
}

void pushWithDuplicate(TeamNode **top, TeamNode *data) {
    TeamNode *newNode = (TeamNode *)malloc(sizeof(TeamNode));
    // copy data from a given team node
    newNode->teamName = (char *)malloc(sizeof(char) * (strlen(data->teamName) + 1));
    strcpy(newNode->teamName, data->teamName);
    newNode->score = data->score;
    newNode->players = NULL;
    newNode->nextTeam = *top;
    *top = newNode;
}

void preparingMatches(TeamsQueue *teamQueue, TeamNode **head) {
    TeamNode *aux = NULL;
    while (*head != NULL) {
        aux = *head;
        *head = (*head)->nextTeam;
        enQueueTeam(teamQueue, &aux);
    }
}

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

void printRound(TeamsQueue *teamsQueue, int round, char *outputFilePath) {
    FILE *outputFile = fopen(outputFilePath, "at");
    fprintf(outputFile, "--- ROUND NO:%d\n", round);
    char buffer[100];
    TeamNode *teams = teamsQueue->front;
    while (teams != NULL) {
        // removeEnding(teams->teamName);
        fprintf(outputFile, "%-33s-%33s\n", teams->teamName, teams->nextTeam->teamName);

        teams = teams->nextTeam->nextTeam;
    }
    fprintf(outputFile, "\n");
    fclose(outputFile);
}

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
}

void printQueue(TeamsQueue *q, char *outputFilePath) {
    FILE *outputFile = fopen(outputFilePath, "at");
    TeamNode *teams = q->front;
    fprintf(outputFile, "%c", '\n');
    while (teams != NULL) {
        fprintf(stdout, "%s", teams->teamName);
        teams = teams->nextTeam;
    }
    fclose(outputFile);
}

void printWinners(TeamNode *stackTop, char *outputFilePath, int round, int numberOfPlayers) {
    FILE *outputFile = fopen(outputFilePath, "at");
    fprintf(outputFile, "WINNERS OF ROUND NO:%d\n", round);
    while (stackTop != NULL) {
        fprintf(outputFile, "%-34s-  %0.2f\n", stackTop->teamName, stackTop->score);
        stackTop = stackTop->nextTeam;
    }

    if (numberOfPlayers != 2)
        fprintf(outputFile, "\n");
    fclose(outputFile);
}
