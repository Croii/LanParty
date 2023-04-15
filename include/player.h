#ifndef PLAYER_H
#define PLAYER_H

#include "structures/team_structure.h"

#include <stdio.h>

void addPlayerAtBeginning(PlayerNode **team);
void addPlayerAtEnd(PlayerNode **team);
void readPlayers(TeamNode **team, int numberOfPlayers, FILE *inputFile);
void showPlayers(Team *team);
void freePlayers(PlayerNode **player);

#endif
