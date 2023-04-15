#ifndef TEAM_STRUCTURE_H
#define TEAM_STRUCTURE_H

typedef struct Player {
    char *firstName;
    char *secondName;
    int points;
} Player;

typedef struct PlayerNode {
    Player infoPlayer;
    struct PlayerNode *nextPlayer;
} PlayerNode;

typedef struct Team {
    PlayerNode *players;
    char *teamName;
    int score;
} Team;

typedef struct TeamNode {
    Team infoTeam;
    struct TeamNode *nextTeam;
} TeamNode;

#endif
