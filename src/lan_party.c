#include "../include/player.h"
#include "../include/team.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define TASKS 5

void computeScores(TeamNode *head) {

    PlayerNode *player = head->players;
    int score = 0;
    while (player != NULL) {
        score += player->points;
        player = player->nextPlayer;
    }
    head->score = score;
}

void computeAllScores(TeamNode *head) {
    while (head != NULL) {
        computeScores(head);
        head = head->nextTeam;
    }
}

int main(int argc, char **argv) {

    //input from command line
    char *tasksFilePath = argv[1];
    char *teamsFilePath = argv[2];
    char *outputFilePath = argv[3];

    //reading tasks from file
    int tasks[TASKS];
    FILE *taskFile = fopen(tasksFilePath, "rt");
    for (int i = 0; i < TASKS; i++)
        fscanf(taskFile, "%d", &tasks[i]);

    //finding the right task to execute
    int TASK1 = tasks[0] == 1 && tasks[1] == 0 && tasks[2] == 0 && tasks[3] == 0 && tasks[4] == 0;
    int TASK2 = tasks[0] == 1 && tasks[1] == 1 && tasks[2] == 0 && tasks[3] == 0 && tasks[4] == 0;
    int TASK3 = tasks[0] == 1 && tasks[1] == 1 && tasks[2] == 1 && tasks[3] == 0 && tasks[4] == 0;
    int TASK4 = tasks[0] == 1 && tasks[1] == 1 && tasks[2] == 1 && tasks[3] == 1 && tasks[4] == 0;
    int TASK5 = tasks[0] == 1 && tasks[1] == 1 && tasks[2] == 1 && tasks[3] == 1 && tasks[4] == 1;

    // clearing file input
    fclose(fopen(outputFilePath, "wt"));
    TeamNode *teams = NULL;
    readTeams(&teams, teamsFilePath);

     if (TASK1) {
        showTeams(teams, outputFilePath);
    }  

     if (TASK2) {
        computeAllScores(teams);
        removeTeams(&teams, teamsFilePath);
        showTeams(teams, outputFilePath);
    }

    if (TASK3) {
    }

    if (TASK4) {
    }

    if (TASK5) {
    }

    
        computeAllScores(teams);
        removeTeams(&teams, teamsFilePath);
       // showTeams(teams, 1);
        //free(*argv);
        printf("1"); 
}