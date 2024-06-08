#ifndef HEX_H_INCLUDED
#define HEX_H_INCLUDED
#include <stdbool.h>
#define LIGNES 9
#define COLONNES 10
struct Position {
    int row;
    int col;
};
extern int visited[9][9];
void cls();
void title();
void displayRules();
void joueur_humain(char grille[LIGNES][COLONNES]);
void joueur_ordinateur(char grille[LIGNES][COLONNES], int niveau);
void afficherGrilleChar(char grille[LIGNES][COLONNES]);
int isValid(int row, int col);

// Function prototype for random_entre_deux_int
int random_entre_deux_int(int min, int max);

void findNeighbors(struct Position current, struct Position neighbors[], int *count, char grille[LIGNES][COLONNES]);
void findNeighborso(struct Position current, struct Position neighbors[], int *count, char grille[LIGNES][COLONNES]);
bool dfs(struct Position start, char grille[LIGNES][COLONNES]);
bool checkPaths(char grille[LIGNES][COLONNES]);
bool dfso(struct Position start, char grille[LIGNES][COLONNES]);
bool checkPathso(char grille[LIGNES][COLONNES]);
void playerVsPlayer(char grille[LIGNES][COLONNES]);
void playerVsEasyAI(char grille[LIGNES][COLONNES]);
void jeu();



#endif // HEX_H_INCLUDED
