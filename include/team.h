#ifndef TEAM_H
#define TEAM_H

#include "..//include//player.h"

#include "structures//team_structure.h"

void addTeamAtBeginning(TeamNode **head);
void addTeamAtEnd(TeamNode **head);
void readTeams(TeamNode **teams, char *filePath, int *numberOfTeams);
void removeTeams(TeamNode **teams, char *teamsFilePath, int *numberOfTeams);
void printTeams(TeamNode *teams, char *outputPath);
void freeTeams(TeamNode **teams);

#endif
