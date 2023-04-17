#include "..//include//player.h"
#include "..//include//team.h"
#include "..//include//match.h"


#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define TASKS 5

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
    int taskToExecute = 0;
    int aux;
    FILE *taskFile = fopen(tasksFilePath, "rt");
<<<<<<< HEAD
    for (int i = 0; i < TASKS; i++) {
        fscanf(taskFile, "%d", &aux);
        taskToExecute += aux;

=======
    for (int i = 0; i < TASKS; i++)
        fscanf(taskFile, "%d", &tasks[i]);
    fclose(taskFile);

    //finding the right task to execute
    int TASK1 = tasks[0] == 1 && tasks[1] == 0 && tasks[2] == 0 && tasks[3] == 0 && tasks[4] == 0;
    int TASK2 = tasks[0] == 1 && tasks[1] == 1 && tasks[2] == 0 && tasks[3] == 0 && tasks[4] == 0;
    int TASK3 = tasks[0] == 1 && tasks[1] == 1 && tasks[2] == 1 && tasks[3] == 0 && tasks[4] == 0;
    int TASK4 = tasks[0] == 1 && tasks[1] == 1 && tasks[2] == 1 && tasks[3] == 1 && tasks[4] == 0;
    int TASK5 = tasks[0] == 1 && tasks[1] == 1 && tasks[2] == 1 && tasks[3] == 1 && tasks[4] == 1;

    // clearing file input
    fclose(fopen(outputFilePath, "wt"));
    TeamNode *teams = NULL;
    int numberOfTeams = 0;
    readTeams(&teams, teamsFilePath, &numberOfTeams);

     if (TASK1) {
        showTeams(teams, outputFilePath);
    }  

     if (TASK2) {
        computeAllScores(teams);
        removeTeams(&teams, teamsFilePath, &numberOfTeams);
        showTeams(teams, outputFilePath);
    }
    
    
    TeamsQueue *teamsQueue = NULL;
    if (TASK3) {
        computeAllScores(teams);
        removeTeams(&teams, teamsFilePath, &numberOfTeams);
        showTeams(teams, outputFilePath);
        teamsQueue = createQueueTeam();
        //showTeams(teams, outputFilePath);
        preparingMatches(teamsQueue, &teams);
        simulatingMatches(teamsQueue, &numberOfTeams, outputFilePath);
      
        
        //printQueue(*teamsQueue, outputFilePath);

    }

    if (TASK4) {
    }

    if (TASK5) {
>>>>>>> 82be213385d01fbf5c12cad2b6b0e3a9acd341a0
    }
    
    fclose(taskFile);

    
<<<<<<< HEAD
    
    
    // clearing file input
    fclose(fopen(outputFilePath, "wt"));


    TeamNode *teams = NULL;
    int numberOfTeams = 0;
    

    readTeams(&teams, teamsFilePath, &numberOfTeams);
    switch(taskToExecute) {
        case 1:
            showTeams(teams, outputFilePath);
            break;
        case 2:
            computeAllScores(teams);
            removeTeams(&teams, teamsFilePath, &numberOfTeams);
            showTeams(teams, outputFilePath);

            break;
        case 3:

            TeamsQueue *teamsQueue = NULL;
            computeAllScores(teams);
            removeTeams(&teams, teamsFilePath, &numberOfTeams);
            showTeams(teams, outputFilePath);
            teamsQueue = createQueueTeam();
            //showTeams(teams, outputFilePath);
            preparingMatches(teamsQueue, &teams);
            simulatingMatches(teamsQueue, &numberOfTeams, outputFilePath);
            break;
        case 4:
            break;
        case 5:
            break;
}
    
=======
>>>>>>> 82be213385d01fbf5c12cad2b6b0e3a9acd341a0

        //freeTeams(&teams);
        //free(*argv);
}