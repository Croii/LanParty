#include "..//include//team.h"
#include "..//include//player.h"

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EPS 1E-6

//function used to deallocate memory for one TeamNode element
void freeTeams(TeamNode **head) {
    TeamNode *aux;
    while (*head != NULL) {
        free((*head)->teamName);
        freePlayers(&(*head)->players);
        aux = (*head)->nextTeam;
        free(*head);
        *head = aux;
    }
    (*head) = NULL;
}

//function used to print all teams to the output file
void printTeams(TeamNode *teams, char *outputPath) {
    FILE *outputFile = fopen(outputPath, "at");

    while (teams != NULL) {
        fprintf(outputFile, "%s\n", teams->teamName);
        teams = teams->nextTeam;
    }
    //
    fclose(outputFile);
}

//function used to read all teams from input file
void readTeams(TeamNode **teams, char *filePath, int *numberOfTeams) {
    FILE *inputFile = fopen(filePath, "rt");
    int numberOfPlayers = 0;

    fscanf(inputFile, "%d", numberOfTeams);
    TeamNode *currentTeam = NULL;
    addTeamAtBeginning(&currentTeam);
    *teams = currentTeam;
    fscanf(inputFile, "%d", &numberOfPlayers);
    //reading first team name
    char buffer[50];
    fgetc(inputFile);
    fgets(buffer, 50, inputFile);
    //removing endline from buffer
    buffer[strlen(buffer) - 2] = 0;
    //removing additional spaces
    for (int i = strlen(buffer); !isalnum(buffer[i]); i--)
        if (buffer[i] == ' ')
            buffer[i] = 0;
    currentTeam->teamName = (char *)malloc(strlen(buffer) + 1);
    currentTeam->score = 0;
    strcpy(currentTeam->teamName, buffer);
    readPlayers(&currentTeam, numberOfPlayers, inputFile);
    //reading teams data
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

//function used to add an element at the beginning of an TEAMNODE list 
void addTeamAtBeginning(TeamNode **head) {
    TeamNode *newTeam = (TeamNode *)malloc(sizeof(TeamNode));
    newTeam->nextTeam = *head;
    *head = newTeam;
}

//function used to add a TeamNode element at the end of a list
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

//function used to determine the lowest score among all teams
float findLowestScore(TeamNode *head) {
    float lowestScore = __FLT_MAX__;
    while (head != NULL) {
        if (lowestScore > head->score)
            lowestScore = head->score;
        head = head->nextTeam;
    }
    return lowestScore;
}

//function to deallocate a list of type TeamNode
void removeTeams(TeamNode **teams, char *teamsFilePath, int *numberOfTeams) {

    //computing the number of teams knowing that there should be exactly a power of 2
    int necessaryNumberOfTeams = (1 << (int)log2f((float)(*numberOfTeams)));

    //removing teams till there are exactly a power of 2 number of teams
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

//function used to deallocate memory from a TeamNode without freeing it's contents
void customFreeForList(TeamNode **head) {
    TeamNode *aux;
    while (*head != NULL) {
        aux = (*head)->nextTeam;
        free(*head);
        *head = aux;
    }
}

//function used to compute scores for one team
void computeScores(TeamNode *head) {

    PlayerNode *player = head->players;
    float score = 0;
    int numberOfPlayers = 0;
    while (player != NULL) {
        score += player->points;
        player = player->nextPlayer;
        numberOfPlayers++;
    }
    head->score = score / numberOfPlayers;
}

//function used to compute scores for all teams in a list
void computeAllScores(TeamNode *head) {
    while (head != NULL) {
        computeScores(head);
        head = head->nextTeam;
    }
}