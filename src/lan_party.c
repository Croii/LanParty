#include "..//include//player.h"
#include "..//include//team.h"
#include "..//include//match.h"
#include "..//include//trees.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define TASKS 5

void reverse(TeamNode** head_ref)
{
     TeamNode* prev = NULL;
     TeamNode* current = *head_ref;
     TeamNode* next = NULL;
    while (current != NULL) {
        // Store next
        next = current->nextTeam;
 
        // Reverse current node's pointer
        current->nextTeam = prev;
 
        // Move pointers one position ahead.
        prev = current;
        current = next;
    }
    *head_ref = prev;
}


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
    char *tasksFilePath  = argv[1];
    char *teamsFilePath  = argv[2];
    char *outputFilePath = argv[3];

    //reading tasks from file
    int tasks[TASKS];

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
        showTeams(teams, outputFilePath);
        
    } else if (tasks[1]) {
        computeAllScores(teams);
        removeTeams(&teams, teamsFilePath, &numberOfTeams);
        showTeams(teams, outputFilePath);
    }

    TeamsQueue *teamsQueue = NULL;
    TeamNode *lastWinners = NULL;
    if (tasks[2]) {
        teamsQueue = createQueueTeam();
        int taskToExecute = 3;
        preparingMatches(teamsQueue, &teams);
        simulatingMatches(teamsQueue, &numberOfTeams, outputFilePath, tasks[3] || tasks[4], &lastWinners);
    }

    TreeNode *root = NULL;
    if (tasks[3]) {
            
            sortNodesByName(lastWinners);
            
            initTree(&root, lastWinners);
           
            FILE *outputFile = fopen(outputFilePath, "at");
            fprintf(outputFile, "\nTOP 8 TEAMS:\n");
            fclose(outputFile);

            buildTree(root, lastWinners->nextTeam);
            printDescending(root, outputFilePath);
    }




  /*   switch(taskToExecute) {
        case 1:
            showTeams(teams, outputFilePath);
            break;
        case 2:
            computeAllScores(teams);
            removeTeams(&teams, teamsFilePath, &numberOfTeams);
            showTeams(teams, outputFilePath);

            break;
        case 3:

            computeAllScores(teams);
            removeTeams(&teams, teamsFilePath, &numberOfTeams);
            showTeams(teams, outputFilePath);
            
            TeamsQueue *teamsQueue = createQueueTeam();
            preparingMatches(teamsQueue, &teams);
            simulatingMatches(teamsQueue, &numberOfTeams, outputFilePath, taskToExecute, NULL);

            break;
        case 4:
            computeAllScores(teams);
            removeTeams(&teams, teamsFilePath, &numberOfTeams);
            showTeams(teams, outputFilePath);
            
            teamsQueue = createQueueTeam();
            preparingMatches(teamsQueue, &teams);
            TeamNode *lastWinners = NULL;
            simulatingMatches(teamsQueue, &numberOfTeams, outputFilePath, taskToExecute, &lastWinners);
            
            TreeNode *root = NULL;
            sortNodesByName(lastWinners);
            initTree(&root, lastWinners);
            // /lastWinners = lastWinners->nextTeam;
            

            //showTeams(lastWinners, outputFilePath);
            FILE *outputFile = fopen(outputFilePath, "at");
            fprintf(outputFile, "\nTOP 8 TEAMS:\n");
            fclose(outputFile);

            buildTree(root, lastWinners->nextTeam);
            printDescending(root, outputFilePath);


            break;
        case 5:
            computeAllScores(teams);
            removeTeams(&teams, teamsFilePath, &numberOfTeams);
            showTeams(teams, outputFilePath);
            
            teamsQueue = createQueueTeam();
            preparingMatches(teamsQueue, &teams);
            lastWinners = NULL;
            simulatingMatches(teamsQueue, &numberOfTeams, outputFilePath, taskToExecute, &lastWinners);
            
            root = NULL;
            
            sortNodesByName(lastWinners);
            initTree(&root, lastWinners);
            // /lastWinners = lastWinners->nextTeam;
            

            //showTeams(lastWinners, outputFilePath);
            outputFile = fopen(outputFilePath, "at");
            fprintf(outputFile, "\nTOP 8 TEAMS:\n");
            fclose(outputFile);

            buildTree(root, lastWinners->nextTeam);
            printDescending(root, outputFilePath);

            
            TeamNode *listForAvl = NULL;
            extractFromBstToList(root, &listForAvl);
            
            sortNodesByName(listForAvl);
            TreeNode *rootAvl = NULL;
            //reverse(&listForAvl);
            
            insertFromListToAvl(&rootAvl, &listForAvl);

            //WinsertFromBstToAVL(root, &rootAvl);

            //printPostOrder(rootAvl, outputFilePath);
            outputFile = fopen(outputFilePath, "at");
            fprintf(outputFile, "\nTHE LEVEL 2 TEAMS ARE: \n");
            fclose(outputFile);
            printLevel(rootAvl,  3, outputFilePath);
            freeTree(&root);
            freeTree(&rootAvl);

            printLevel(rootAvl, 3, outputFilePath);


            break;
}
 */
}