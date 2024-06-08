#include "hex.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

//effacer l'historique
void cls() {
    system("cls");
}
//L'affichage du titre
void title() {
    printf("                                                            ██╗  ██╗███████╗██╗  ██╗\n");
    printf("                                                            ██║  ██║██╔════╝╚██╗██╔╝\n");
    printf("                                                            ███████║█████╗   ╚███╔╝ \n");
    printf("                                                            ██╔══██║██╔══╝   ██╔██╗ \n");
    printf("                                                            ██║  ██║███████╗██╔╝ ██╗\n");
    printf("                                                            ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝\n");
}
//regles du jeu
void displayRules() {
    printf("\nWelcome to the HEX Game!\n\n");

    printf("Rules:\n");
    printf("1. The game starts with an empty hexagonal board.\n");
    printf("2. Players take turns placing their colored pieces on empty hexagons.\n");
    printf("3. The goal is to create a connected path of your color from one side to the opposite side.\n");
    printf("4. For example, if you are Blue, connect the sides marked with Blue to win.\n");
    printf("5. The connection can be horizontal, vertical, or diagonal.\n");
    printf("6. The first player to create a connecting path wins the game.\n\n");

    printf("Press Enter to return to the main menu...\n");
    while (getchar() != '\n');

    getchar();  // attenter que l'utilisateur entre une entrez
}
void afficherGrilleChar(char grille[LIGNES][COLONNES]) {
    int g_size = 9;

    // Affichage d'indexation hozizontal
    for (int col = 0; col <= g_size - 1; col++) {
        printf("    ");
        printf("%-4d", col);
    }
    printf("\n\n\n");

    for (int j = 0; j < g_size; j++) {
        printf("   / \\  ");
    }
    printf("\n");

    for (int j = 0; j < g_size; j++) {
        printf(" /     \\");
    }
    printf("\n");

    for (int j = 0; j < 10; j++) {
        printf("|   %c   ", grille[0][j]);
    }
    printf("0");
    printf("\n");

    for (int j = 0; j < 10; j++) {
        printf("|       ");
    }
    printf("\n");

    for (int j = 0; j < 9; j++) {
        printf(" \\     /");
    }
    printf(" \\      ");
    printf("\n");

    for (int j = 0; j < 9; j++) {
        printf("   \\ /  ");
    }
    printf("   \\    ");
    printf("\n");

    for (int i = 1; i < 9; i++) {
        for (int k = 0; k < i; k++) {
            printf("    ");
        }

        for (int j = 0; j < 10; j++) {
            printf("|   %c   ", grille[i][j]);
        }
        printf("%d", i);
        printf("\n");

        for (int k = 0; k < i; k++) {
            printf("    ");
        }

        for (int j = 0; j < 10; j++) {
            printf("|       ");
        }
        printf("\n");

        for (int k = 0; k < i; k++) {
            printf("    ");
        }

        for (int j = 0; j < 9; j++) {
            printf(" \\     /");
        }
        printf(" \\      \n");

        for (int k = 0; k < i; k++) {
            printf("    ");
        }

        for (int j = 0; j < 9; j++) {
            printf("   \\ /  ");
        }
        printf("   \\    \n");
    }
}
int visited[9][9] = {0};
//Vérification de ne pas sortir de la grille
int isValid(int row, int col) {
    return (row >= 0 && row < 9 && col >= 0 && col < 9);
}
//les voisins de 'x'
void findNeighbors(struct Position current, struct Position neighbors[], int *count, char grille[LIGNES][COLONNES]) {
    int directions[6][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {-1, 1}, {1, -1}};

    for (int k = 0; k < 6; ++k) {
        int ni = current.row + directions[k][0];
        int nj = current.col + directions[k][1];

        if (isValid(ni, nj) && grille[ni][nj] == 'X' && !visited[ni][nj]) {
            neighbors[*count].row = ni;
            neighbors[*count].col = nj;
            visited[ni][nj] = 1;
            ++(*count);
        }
    }
}
//les voisins de 'O'
void findNeighborso(struct Position current, struct Position neighbors[], int *count, char grille[LIGNES][COLONNES]) {
    int directions[6][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {-1, 1}, {1, -1}};

    for (int k = 0; k < 6; ++k) {
        int ni = current.row + directions[k][0];
        int nj = current.col + directions[k][1];

        if (isValid(ni, nj) && grille[ni][nj] == 'O' && !visited[ni][nj]) {
            neighbors[*count].row = ni;
            neighbors[*count].col = nj;
            visited[ni][nj] = 1;
            ++(*count);
        }
    }
}

//explorer les chemins possibles depuis start pour 'X'
 bool dfs(struct Position start, char grille[LIGNES][COLONNES]) {
    if (grille[start.row][start.col] != 'X') {
        return false;
    }

    struct Position queue[100];
    int front = 0, rear = 0;
    queue[rear++] = start;

    while (front < rear) {
        struct Position current = queue[front++];

        if (current.row == 8) {
            return true;
        }

        visited[current.row][current.col] = 1;

        struct Position neighbors[6];
        int count = 0;

        findNeighbors(current, neighbors, &count, grille);

        for (int k = 0; k < count; ++k) {
            queue[rear++] = neighbors[k];
        }
    }

    return false;
}

//loop sur toute les positions de premiere ligne
bool checkPaths(char grille[LIGNES][COLONNES]) {
    for (int i = 0; i < 9; ++i) {
        struct Position start = {0, i};
        visited[0][i] = 1; // Marquer la position de départ comme visitée
        if (dfs(start, grille)) {
            return true;
        }
        // Réinitialiser le tableau visited pour la prochaine itération
        for (int row = 0; row < LIGNES; ++row) {
            for (int col = 0; col < COLONNES; ++col) {
                visited[row][col] = 0;
            }
        }
    }
    return false;
}

//explorer les chemins possibles depuis start pour 'O'
bool dfso(struct Position start, char grille[LIGNES][COLONNES]) {
    if (grille[start.row][start.col] != 'O') {
        return false;
    }

    struct Position queue[100];
    int front = 0, rear = 0;
    queue[rear++] = start;

    while (front < rear) {
        struct Position current = queue[front++];

        if (current.col == 8) {
            return true;
        }

        visited[current.row][current.col] = 1;

        struct Position neighbors[6];
        int count = 0;

        findNeighborso(current, neighbors, &count, grille);

        for (int k = 0; k < count; ++k) {
            queue[rear++] = neighbors[k];
        }
    }

    return false;
}

//loop sur toute les positions de premiere colonne
bool checkPathso(char grille[LIGNES][COLONNES]) {
    for (int i = 0; i < 9; ++i) {
        struct Position start = {i, 0};
        visited[i][0] = 1; // Marquer la position de départ comme visitée
        if (dfso(start, grille)) {  // Utilisez dfso au lieu de dfs ici
            return true;
        }
        // Réinitialiser le tableau visited pour la prochaine itération
        for (int row = 0; row < LIGNES; ++row) {
            for (int col = 0; col < COLONNES; ++col) {
                visited[row][col] = 0;
            }
        }
    }
    return false;
}

void joueur_humain(char grille[LIGNES][COLONNES]) {
    int ligne, colonne;
    char symboleJoueur = 'X';

    // Obtient l'entrée de l'utilisateur pour la ligne et la colonne
    printf("Entrez la ligne (0-%d) et la colonne (0-%d) où vous voulez placer '%c': ", LIGNES - 1, COLONNES - 2, symboleJoueur);
    scanf("%d %d", &ligne, &colonne);

    // Vérifie si la cellule sélectionnée est valide et vide
    if (ligne >= 0 && ligne < LIGNES && colonne >= 0 && colonne < COLONNES-1 && grille[ligne][colonne] == ' ') {
        // Place le symbole dans la cellule sélectionnée
        grille[ligne][colonne] = symboleJoueur;
    } else {
        printf("Mouvement invalide. Réessayez.\n");
        joueur_humain(grille);  // Demande à nouveau à l'utilisateur de jouer
    }
}

// Implementation of random_entre_deux_int
int random_entre_deux_int(int min, int max) {
    return rand() % (max - min + 1) + min;
}

// Implémentation de la fonction joueur_ordinateur
void joueur_ordinateur(char grille[LIGNES][COLONNES], int niveau) {
    int ligne, colonne;
    char symboleJoueur = 'O';  // Le symbole pour l'ordinateur

    // Niveau facile (mouvements aléatoires)
    if (niveau == 1) {
        // Utilisation de la fonction random_entre_deux_int pour choisir une cellule vide de manière aléatoire
        do {
            ligne = random_entre_deux_int(0, LIGNES - 1);
            colonne = random_entre_deux_int(0, COLONNES - 2);
        } while (grille[ligne][colonne] != ' ');

        // Place le symbole dans la cellule sélectionnée
        grille[ligne][colonne] = symboleJoueur;
    }

    // Niveau supérieur //minmax j'ai pa pu l'implementer correctement

}
void playerVsPlayer(char grille[LIGNES][COLONNES]) {
    char vide = ' ';
    int ligne, colonne;
    char symboleJoueur = 'X';

    // Initialize la grille avec des espaces vides
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 10; j++)
            grille[i][j] = vide;

    do {
        // Affiche l'état actuel de la grille
        afficherGrilleChar(grille);

        // Obtient l'entrée de l'utilisateur pour la ligne et la colonne
        printf("Entrez la ligne (0-%d) et la colonne (0-%d) où vous voulez placer '%c': ", LIGNES - 1, COLONNES - 2, symboleJoueur);
        scanf("%d %d", &ligne, &colonne);

        // Vérifie si la cellule sélectionnée est valide et vide
        if (ligne >= 0 && ligne < LIGNES && colonne >= 0 && colonne < COLONNES-1 && grille[ligne][colonne] == ' ') {
            // Place le symbole dans la cellule sélectionnée
            grille[ligne][colonne] = symboleJoueur;

            // Vérifie la victoire après chaque mouvement
            if (checkPaths(grille)) {
                printf("Joueur '%c' a gagné !\n", symboleJoueur);
                break; // Fin du jeu
            }

            // Change de joueur
            symboleJoueur = (symboleJoueur == 'X') ? 'O' : 'X';
        } else {
            printf("Mouvement invalide. Réessayez.\n");
        }
        cls();
    } while (1);
}

void playerVsEasyAI(char grille[LIGNES][COLONNES]) {
    char vide = ' ';
    int ligne, colonne;
    char symboleJoueur = 'X';

    // Initialize la grille avec des espaces vides
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 10; j++)
            grille[i][j] = vide;

    do {
        // Affiche l'état actuel de la grille
        afficherGrilleChar(grille);

        // Tour du joueur humain
        joueur_humain(grille);

        // Vérifie la victoire après chaque mouvement
        if (checkPaths(grille)) {
            printf("Joueur 'X' a gagné !\n");
            break;
        }

        // Tour de l'ordinateur (easy AI)
        joueur_ordinateur(grille, 1);

        // Vérifie la victoire après chaque mouvement
        if (checkPathso(grille)) {
            printf("Joueur 'O' a gagné !\n");
            break;
        }
        cls();

    } while (1);
}
void jeu(){
char grille[LIGNES][COLONNES];
    int mainChoice;

    do {
        cls();
        title();
        printf("\n  Welcome to HEX Game!\n");
        printf("Please select an option:\n");
        printf("1. Start\n");
        printf("2. Rules\n");
        printf("3. Quit\n");

        printf("Enter your choice: ");
        scanf("%d", &mainChoice);

        switch (mainChoice) {
            case 1:
                cls();
                title();
                printf("1. Player vs Player\n");
                printf("2. Player vs Easy AI\n");
                printf("3. Player vs Hard AI\n");

                int gameChoice;
                printf("Enter your choice: ");
                scanf("%d", &gameChoice);

                switch (gameChoice) {
                    case 1:
                        cls();
                        printf("Starting Player vs Player game...\n");
                        playerVsPlayer(grille);
                        break;
                    case 2:
                        cls();
                        printf("Starting Player vs Easy AI game...\n");
                        playerVsEasyAI(grille);
                        break;
                    case 3:
                        cls();
                        printf("Starting Player vs Hard AI game...\n");
                        break;
                    default:
                        printf("Invalid choice\n");
                }
                break;
            case 2:
                title();
                cls();
                displayRules();
                break;
            case 3:
                cls();
                printf("Quitting...\n");
                break;
            default:
                printf("Invalid choice\n");
        }
    } while (mainChoice != 3);}
