#ifndef TEAM_STRUCTURE_H
#define TEAM_STRUCTURE_H

/* typedef struct Player {
    char *firstName;
    char *secondName;
    int points;
} Player; */

typedef struct PlayerNode {
    char *firstName;
    char *secondName;
    int points;
    struct PlayerNode *nextPlayer;
} PlayerNode;

/* typedef struct Team {
    PlayerNode *players;
    char *teamName;
    int score;
} Team; */

typedef struct TeamNode {
    PlayerNode *players;
    char *teamName;
    float score;
    struct TeamNode *nextTeam;
} TeamNode;

#endif
