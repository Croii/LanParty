#include "../include/team.h"
#include "../include/player.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void showTeams(TeamNode *teams, char *outputPath) {
    FILE *outputFile = fopen(outputPath, "at");
    while (teams != NULL) {
        fprintf(outputFile, "%s", teams->teamName);
        teams = teams->nextTeam;
    }

    fclose(outputFile);
}

void readTeams(TeamNode **teams, char *filePath) {
    FILE *inputFile = fopen(filePath, "rt");
    int numberOfPlayers = 0;
    int numberOfTeams = 0;

    fscanf(inputFile, "%d", &numberOfTeams);
    TeamNode *currentTeam = NULL;
    addTeamAtBeginning(&currentTeam);
    *teams = currentTeam;
    fscanf(inputFile, "%d", &numberOfPlayers);

    char buffer[50];
    fgetc(inputFile);
    fgets(buffer, 50, inputFile);
    currentTeam->teamName = (char *)malloc(strlen(buffer) + 1);
    currentTeam->score = 0;
    strcpy(currentTeam->teamName, buffer);

    readPlayers(&currentTeam, numberOfPlayers, inputFile);

    for (int teamIndex = 1; teamIndex < numberOfTeams; teamIndex++) {

        fscanf(inputFile, "%d", &numberOfPlayers);
        fgetc(inputFile);
        fgets(buffer, 50, inputFile);
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
    TeamNode *newTeam = (TeamNode*)malloc(sizeof(TeamNode));
    if (*head == NULL)
        addTeamAtBeginning(head);
    else {
        while (aux->nextTeam != NULL)
            aux = aux->nextTeam;
        aux->nextTeam = newTeam;
        newTeam->nextTeam = NULL;
    }
}

//given the first team, it return the lowest score of all teams
int findLowestScore(TeamNode *head) {
    int lowestScore = 2147483647;
    while (head != NULL) {
        if (lowestScore > head->score)
            lowestScore = head->score;
        head = head->nextTeam;
    }
    return lowestScore;
}
void removeTeams(TeamNode **teams, char *teamsFilePath) {
    FILE *inputFile = fopen(teamsFilePath, "rt");
    int numberOfTeams = 0;
    fscanf(inputFile, "%d", &numberOfTeams);
    fclose(inputFile);

    //computing the number of teams knowing that there should be exactly a power of 2  
    int necessaryNumberOfTeams = (1 << (int)log2f((float)numberOfTeams));

    //removing teams till there are exactly a power of 2 number of teams
    for (int i = 0; i < numberOfTeams - necessaryNumberOfTeams; i++) {
        int lowestScore = findLowestScore(*teams);
        if ((*teams)->score == lowestScore) {
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
}
