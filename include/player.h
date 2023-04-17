#ifndef PLAYER_H
#define PLAYER_H

#include "structures//team_structure.h"

#include <stdio.h>

void addPlayerAtBeginning(PlayerNode **head);
void addPlayerAtEnd(PlayerNode **head);
void readPlayers(TeamNode **head, int numberOfPlayers, FILE *inputFile);
void showPlayers(PlayerNode *head);
void freePlayers(PlayerNode **head);
void removeEnding(char *text);

#endif
