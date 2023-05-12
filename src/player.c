#include "..//include//player.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//function used to print all players in a list
void showPlayers(PlayerNode *head) {
    while (head != NULL) {
        printf("%s ", head->secondName);
        printf("%s ", head->firstName);
        printf("%d ", head->points);
        printf("\n");
        head = head->nextPlayer;
    }
}

//function used to read all players of a team from input file
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

//function used to add a player at the beginning of a list
void addPlayerAtBeginning(PlayerNode **head) {
    PlayerNode *newPlayer = (PlayerNode *)malloc(sizeof(PlayerNode));
    newPlayer->nextPlayer = *head;
    *head = newPlayer;
}

//function used to add a player at the end of a list
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

//function used to free all players from a list
void freePlayers(PlayerNode **head) {
    PlayerNode *aux;
    while (*head != NULL) {
        free((*head)->secondName);
        free((*head)->firstName);
        aux = (*head)->nextPlayer;
        free(*head);
        *head = aux;
    }
}

//function used to remove the endline from a string
void removeEnding(char *text) {
    while (*text != 0) {
        if (*text == (char)13 || *text == (char)10) {
            *text = 0;
            return;
        }
        text++;
    }
}
