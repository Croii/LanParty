#include "..//include//match.h"
#include "..//include//player.h"
#include "..//include//team.h"
#include "..//include//trees.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TASKS 5

//function used to deallocate all the memory left
void freeAll(TeamNode **teams, TreeNode **rootBst, TreeNode **rootAvl) {
    if (*teams != NULL) {
        freeTeams(teams);
    }

    if (*rootBst != NULL) {
        freeTree(rootBst);
    }
    
    if (*rootAvl != NULL) {
        freeTree(rootAvl);
    }

}

//Function used to run all the tasks
void runTasks(int tasks[], char *outputFilePath, TeamNode **teams, int *numberOfTeams, TeamsQueue **teamsQueue, TeamNode **lastWinners, TreeNode **rootBst, TreeNode **rootAvl) {
    if (tasks[0] && !tasks[1]) {
        printTeams(*teams, outputFilePath);

    } 
    if (tasks[1]) {
        computeAllScores(*teams);
        removeTeams(teams, outputFilePath, numberOfTeams);
        printTeams(*teams, outputFilePath);
    }
    if (tasks[2]) {
        *teamsQueue = createQueueTeam();
        int taskToExecute = 3;
        preparingMatches(*teamsQueue, teams);
        simulatingMatches(*teamsQueue, numberOfTeams, outputFilePath, tasks[3] || tasks[4], lastWinners);
        free(*teamsQueue);
    }
    if (tasks[3]) {

        sortNodesByName(*lastWinners);
        initBstTree(rootBst, *lastWinners);

        FILE *outputFile = fopen(outputFilePath, "at");
        fprintf(outputFile, "\nTOP 8 TEAMS:\n");
        fclose(outputFile);
        buildBstTree(*rootBst, (*lastWinners)->nextTeam);
        printDescending(*rootBst, outputFilePath);
        customFreeForList(lastWinners);
    }
    if (tasks[4]) {
        
        insertFromBstToAVL(*rootBst, rootAvl);

        FILE *outputFile = fopen(outputFilePath, "at");
        fprintf(outputFile, "\nTHE LEVEL 2 TEAMS ARE: \n");
        fclose(outputFile);
        printLevel(*rootAvl, 3, outputFilePath);
    }
}




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

    TeamsQueue *teamsQueue = NULL;
    TeamNode *lastWinners = NULL;
    TreeNode *rootBst = NULL;
    TreeNode *rootAvl = NULL;

    runTasks(tasks, outputFilePath, &teams, &numberOfTeams, &teamsQueue, &lastWinners, &rootBst, &rootAvl);

    freeAll(&teams, &rootBst, &rootAvl);
}
