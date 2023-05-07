#include "..//include//player.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// displays all players from a team
void showPlayers(PlayerNode *head) {
    while (head != NULL) {
        printf("%s ", head->secondName);
        printf("%s ", head->firstName);
        printf("%d ", head->points);
        printf("\n");
        head = head->nextPlayer;
    }
}

// it reads players from input file
void readPlayers(TeamNode **team, int numberOfPlayers, FILE *inputFile) {
    PlayerNode *currentPlayer = NULL;
    addPlayerAtBeginning(&currentPlayer);

    char buffer[50];
    fscanf(inputFile, "%s", buffer);
    currentPlayer->secondName = (char *)malloc(strlen(buffer) + 1);
    strcpy(currentPlayer->secondName, buffer);

    fscanf(inputFile, "%s", buffer);
    currentPlayer->firstName = (char *)malloc(strlen(buffer) + 1);
    strcpy(currentPlayer->firstName, buffer);

    fscanf(inputFile, "%d", &currentPlayer->points);
    (*team)->players = currentPlayer;
    for (int playerIndex = 1; playerIndex < numberOfPlayers; playerIndex++) {
        addPlayerAtEnd(&currentPlayer);
        currentPlayer = currentPlayer->nextPlayer;

        fscanf(inputFile, "%s", buffer);
        currentPlayer->secondName = (char *)malloc(strlen(buffer) + 1);
        strcpy(currentPlayer->secondName, buffer);

        fscanf(inputFile, "%s", buffer);
        currentPlayer->firstName = (char *)malloc(strlen(buffer) + 1);
        strcpy(currentPlayer->firstName, buffer);

        fscanf(inputFile, "%d", &currentPlayer->points);
    }
}

void addPlayerAtBeginning(PlayerNode **head) {
    PlayerNode *newPlayer = (PlayerNode *)malloc(sizeof(PlayerNode));
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

// emptying memory for a player struct
void freePlayers(PlayerNode **head) {
    PlayerNode *aux = *head;
    while (*head != NULL) {
        free((*head)->secondName);
        free((*head)->firstName);
        aux = (*head)->nextPlayer;
        free(*head);
        *head = aux;
    }
}
void removeEnding(char *text) {
    while (*text != 0) {
        if (*text == (char)13 || *text == (char)10) {
            *text = 0;
            return;
        }
        text++;
    }
}
