#ifndef TEAM_H
#define TEAM_H

#include "..//include//player.h"

#include "structures//team_structure.h"

void addTeamAtBeginning(TeamNode **head);
void addTeamAtEnd(TeamNode **head);
void readTeams(TeamNode **teams, char *filePath);
void removeTeams(TeamNode **teams, char *teamsFilePath);
void showTeams(TeamNode *teams, char *outputPath);
void freeTeams(TeamNode **teams);

#endif
