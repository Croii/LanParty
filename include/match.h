#ifndef MATCH_H
#define MATCH_H

#include "structures//match_structure.h"
#include "structures//team_structure.h"

TeamsQueue *createQueueTeam();
void enQueueTeam(TeamsQueue *queue, TeamNode **teams);
TeamNode *deQueueTeam(TeamsQueue *queue);
void simulatingMatches(TeamsQueue *teamsQueue, int *numberOfTeams, char *outputFilePath, int task, TeamNode **lastWinners);
void preparingMatches(TeamsQueue *teamQueue, TeamNode **head);
void push(TeamNode **top, TeamNode **value);
void freeStack(TeamNode **stackTop);
TeamNode *pop(TeamNode **top);
int isStackEmpty(TeamNode *top);
int isQueueEmpty(TeamsQueue *queue);
void printQueue(TeamsQueue *queue, char *outputFilePath);
void printRound(TeamsQueue *teamsQueue, int round, char *outputFilePath);
void printWinners(TeamNode *stackTop, char *outputFilePath, int round, int numberOfPlayers);
void pushWithDuplicate(TeamNode **top, TeamNode *value);
void customFreeForList(TeamNode **head);
#endif
