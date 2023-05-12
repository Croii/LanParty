#ifndef TEAM_STRUCTURE_H
#define TEAM_STRUCTURE_H

typedef struct PlayerNode {
    char *firstName;
    char *secondName;
    int points;
    struct PlayerNode *nextPlayer;
} PlayerNode;

typedef struct TeamNode {
    PlayerNode *players;
    char *teamName;
    float score;
    struct TeamNode *nextTeam;
} TeamNode;

#endif
