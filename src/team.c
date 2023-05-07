#include "..//include//team.h"
#include "..//include//player.h"

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EPS 1E-6

void freeTeams(TeamNode **head) {
    TeamNode *aux = *head;
    while (*head != NULL) {
        free((*head)->teamName);
        freePlayers(&(*head)->players);
        aux = (*head)->nextTeam;
        free(*head);
        *head = aux;
    }
    (*head) = NULL;
}

void printTeams(TeamNode *teams, char *outputPath) {
    FILE *outputFile = fopen(outputPath, "at");

    while (teams != NULL) {
        fprintf(outputFile, "%s\n", teams->teamName);
        teams = teams->nextTeam;
    }
    //
    fclose(outputFile);
}

void readTeams(TeamNode **teams, char *filePath, int *numberOfTeams) {
    FILE *inputFile = fopen(filePath, "rt");
    int numberOfPlayers = 0;

    fscanf(inputFile, "%d", numberOfTeams);
    TeamNode *currentTeam = NULL;
    addTeamAtBeginning(&currentTeam);
    *teams = currentTeam;
    fscanf(inputFile, "%d", &numberOfPlayers);

    char buffer[50];
    fgetc(inputFile);
    fgets(buffer, 50, inputFile);
    buffer[strlen(buffer) - 2] = 0;

    for (int i = strlen(buffer); !isalnum(buffer[i]); i--)
        if (buffer[i] == ' ')
            buffer[i] == 0;

    currentTeam->teamName = (char *)malloc(strlen(buffer) + 1);
    currentTeam->score = 0;
    strcpy(currentTeam->teamName, buffer);

    readPlayers(&currentTeam, numberOfPlayers, inputFile);

    for (int teamIndex = 1; teamIndex < *numberOfTeams; teamIndex++) {

        fscanf(inputFile, "%d", &numberOfPlayers);
        fgetc(inputFile);
        fgets(buffer, 50, inputFile);
        removeEnding(buffer);
        // buffer[strlen(buffer) - 2] = 0;
        if (buffer[strlen(buffer) - 1] == ' ')
            buffer[strlen(buffer) - 1] = 0;

        addTeamAtBeginning(&currentTeam);
        currentTeam->teamName = (char *)malloc(strlen(buffer) + 1);
        strcpy(currentTeam->teamName, buffer);
        readPlayers(&currentTeam, numberOfPlayers, inputFile);
        fgetc(inputFile);
    }

    *teams = currentTeam;
    fclose(inputFile);
}

void addTeamAtBeginning(TeamNode **head) {
    TeamNode *newTeam = (TeamNode *)malloc(sizeof(TeamNode));
    newTeam->nextTeam = *head;
    *head = newTeam;
}

void addTeamAtEnd(TeamNode **head) {
    TeamNode *aux = *head;
    TeamNode *newTeam = (TeamNode *)malloc(sizeof(TeamNode));
    if (*head == NULL)
        addTeamAtBeginning(head);
    else {
        while (aux->nextTeam != NULL)
            aux = aux->nextTeam;
        aux->nextTeam = newTeam;
        newTeam->nextTeam = NULL;
    }
}

// given the first team, it return the lowest score of all teams
float findLowestScore(TeamNode *head) {
    float lowestScore = 2147483647;
    while (head != NULL) {
        if (lowestScore > head->score)
            lowestScore = head->score;
        head = head->nextTeam;
    }
    return lowestScore;
}
void removeTeams(TeamNode **teams, char *teamsFilePath, int *numberOfTeams) {

    // computing the number of teams knowing that there should be exactly a power of 2
    int necessaryNumberOfTeams = (1 << (int)log2f((float)(*numberOfTeams)));

    // removing teams till there are exactly a power of 2 number of teams
    for (int i = 0; i < *numberOfTeams - necessaryNumberOfTeams; i++) {
        float lowestScore = findLowestScore(*teams);
        if (((*teams)->score - lowestScore) < EPS) {
            TeamNode *aux = *teams;
            *teams = (*teams)->nextTeam;
            free(aux->teamName);
            freePlayers(&aux->players);
            free(aux);

        } else {
            TeamNode *teamsCopy = *teams;
            while (teamsCopy->nextTeam->score != lowestScore)
                teamsCopy = teamsCopy->nextTeam;

            free(teamsCopy->nextTeam->teamName);
            freePlayers(&teamsCopy->nextTeam->players);
            TeamNode *aux = teamsCopy->nextTeam;
            teamsCopy->nextTeam = aux->nextTeam;
            free(aux);
        }
    }
    (*numberOfTeams) = necessaryNumberOfTeams;
}
