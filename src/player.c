#include "../include/player.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//displays all players from a team
void showPlayers(Team *head) {
    while (head->players != NULL) {
        printf("%s ", head->players->infoPlayer.secondName);
        printf("%s ", head->players->infoPlayer.firstName);
        printf("%d ", head->players->infoPlayer.points);
        printf("\n");
        head->players = head->players->nextPlayer;
    }
}

//it reads players from input file
void readPlayers(TeamNode **team, int numberOfPlayers, FILE *inputFile) {
    PlayerNode *currentPlayer = NULL;
    addPlayerAtBeginning(&currentPlayer);

    char buffer[50];
    fscanf(inputFile, "%s", buffer);
    currentPlayer->infoPlayer.secondName = (char *)malloc(strlen(buffer) + 1);
    strcpy(currentPlayer->infoPlayer.secondName, buffer);

    fscanf(inputFile, "%s", buffer);
    currentPlayer->infoPlayer.firstName = (char *)malloc(strlen(buffer) + 1);
    strcpy(currentPlayer->infoPlayer.firstName, buffer);

    fscanf(inputFile, "%d", &currentPlayer->infoPlayer.points);
    (*team)->infoTeam.players = currentPlayer;
    for (int playerIndex = 1; playerIndex < numberOfPlayers; playerIndex++) {
        addPlayerAtEnd(&currentPlayer);
        currentPlayer = currentPlayer->nextPlayer;

        fscanf(inputFile, "%s", buffer);
        currentPlayer->infoPlayer.secondName = (char *)malloc(strlen(buffer) + 1);
        strcpy(currentPlayer->infoPlayer.secondName, buffer);

        fscanf(inputFile, "%s", buffer);
        currentPlayer->infoPlayer.firstName = (char *)malloc(strlen(buffer) + 1);
        strcpy(currentPlayer->infoPlayer.firstName, buffer);

        fscanf(inputFile, "%d", &currentPlayer->infoPlayer.points);
    }
}

void addPlayerAtBeginning(PlayerNode **head) {
    PlayerNode *newPlayer = (PlayerNode*)malloc(sizeof(PlayerNode));
    newPlayer->nextPlayer = *head;
    *head = newPlayer;
}


void addPlayerAtEnd(PlayerNode **head) {
    PlayerNode *aux = *head;
    PlayerNode *newPlayer = (PlayerNode *)malloc(sizeof(PlayerNode));
    if (*head == NULL)
        addPlayerAtBeginning(head);
    else {
        while (aux->nextPlayer != NULL)
            aux = aux->nextPlayer;
        aux->nextPlayer = newPlayer;
        newPlayer->nextPlayer = NULL;
    }
}


//emptying memory for a player struct
void freePlayers(PlayerNode **head) {
    PlayerNode *aux = *head;
    while (*head != NULL) {
        free((*head)->infoPlayer.secondName);
        free((*head)->infoPlayer.firstName);
        aux = (*head)->nextPlayer;
        free(*head);
        *head = aux;
    }
}