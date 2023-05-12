#include "..//include//match.h"
#include "..//include//player.h"
#include "..//include//team.h"
#include "..//include//trees.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TASKS 5





int main(int argc, char **argv) {

    // input from command line
    char *tasksFilePath = argv[1];
    char *teamsFilePath = argv[2];
    char *outputFilePath = argv[3];

    int tasks[TASKS];

    // reading tasks from file
    FILE *taskFile = fopen(tasksFilePath, "rt");

    for (int i = 0; i < TASKS; i++)
        fscanf(taskFile, "%d", &tasks[i]);
    fclose(taskFile);

    // clearing file input
    fclose(fopen(outputFilePath, "wt"));

    TeamNode *teams = NULL;
    int numberOfTeams = 0;

    readTeams(&teams, teamsFilePath, &numberOfTeams);
    if (tasks[0] && !tasks[1]) {
        printTeams(teams, outputFilePath);

    } else if (tasks[1]) {
        computeAllScores(teams);
        removeTeams(&teams, teamsFilePath, &numberOfTeams);
        printTeams(teams, outputFilePath);
    }

    TeamsQueue *teamsQueue = NULL;
    TeamNode *lastWinners = NULL;
    if (tasks[2]) {
        teamsQueue = createQueueTeam();
        int taskToExecute = 3;
        preparingMatches(teamsQueue, &teams);
        simulatingMatches(teamsQueue, &numberOfTeams, outputFilePath, tasks[3] || tasks[4], &lastWinners);
        free(teamsQueue);
    }

    TreeNode *rootBst = NULL;
    if (tasks[3]) {

        sortNodesByName(lastWinners);
        initBstTree(&rootBst, lastWinners);

        FILE *outputFile = fopen(outputFilePath, "at");
        fprintf(outputFile, "\nTOP 8 TEAMS:\n");
        fclose(outputFile);
        buildBstTree(rootBst, lastWinners->nextTeam);
        printDescending(rootBst, outputFilePath);
        customFreeForList(&lastWinners);
    }

    TreeNode *rootAvl = NULL;
    if (tasks[4]) {
        
        insertFromBstToAVL(rootBst, &rootAvl);

        FILE *outputFile = fopen(outputFilePath, "at");
        fprintf(outputFile, "\nTHE LEVEL 2 TEAMS ARE: \n");
        fclose(outputFile);
        printLevel(rootAvl, 3, outputFilePath);
    }


    if (teams != NULL) {
        freeTeams(&teams);
    }

    if (rootBst != NULL) {
        freeTree(&rootBst);
    }
    
    if (rootAvl != NULL) {
        freeTree(&rootAvl);
    }


}