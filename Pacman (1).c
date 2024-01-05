#include <stdio.h>
#include <conio.h>
#include <unistd.h>
#include <stdbool.h>

// Constants

#define sizeM 23
#define pacman (char)1
#define coin (char)3
#define maxScore 28

// Lines : 95 | 179 | 186 | 187 | 188 | 200 | 201 | 205 | 254

#define hL (char)95
#define doubleHL (char)205
#define vL (char)179
#define DoubleVL (char)186
#define upRightL (char)187
#define downRightL (char)188
#define downLeftL (char)200
#define upLeftL (char)201
#define square (char)207

// Global variables :

int iPac = 0;
int jPac = 0;
int score = 0;

// -----------------------------------


void initialiser(char M[sizeM][sizeM]) {
    int i, j;

    // Filling matrix and borders
    for ( i = 0; i < 12; ++i) {
        for ( j = 0; j < 12; ++j) {
            M[i][j] = '.';
        }
    }
    M[0][0] =upLeftL;
    M[0][22]=upRightL;
    M[22][0]=downLeftL;
    M[22][22]=downRightL;
    for (i = 1; i < 22; i++)
    {
        M[0][i]=doubleHL;
    }
    for (i = 1; i < 22; i++)
    {
        M[22][i]=doubleHL;
    }
    for ( i = 1; i < 22; i++)
    {
        M[i][0]=DoubleVL;
    }
    for ( i = 1; i < 22; i++)
    {
        M[i][22]=DoubleVL;
    }
    // Filling 1st quarter of the map
    M[3][3]= coin;
    M[3][1]= coin;
    M[5][1]= coin;
    M[7][2]= coin;
    M[1][6]= coin;
    M[3][7]= coin;
    M[6][5]= coin;
	M[2][2] = square;
    M[5][11]=square;
    M[5][10] =square;
	M[6][2] = square;
    M[6][10] = square;
    M[4][10] = square;
    M[4][11] = square;
	M[6][11] = square;
    M[1][4] = vL;
	M[2][4] = vL;
    M[3][8] = vL;
    M[4][4] = vL;
	M[4][6] = vL;
	M[4][8] = vL;
    M[5][4] = vL;
	M[5][6] = vL;
	M[5][8] = vL;
    M[6][4] = vL;
	M[6][6] = vL;
	M[6][8] = vL;
    M[7][4] = vL;
	M[7][6] = vL;
    M[8][6] = vL;
    M[9][6] = vL;
    M[10][6] = vL;
	M[10][8] = hL;
    M[11][8] = vL;
	M[2][6] = hL;
	M[2][7] = hL;
	M[2][8] = hL;
	M[2][9] = hL;
	M[2][10] = hL;
	M[4][1] = hL;
	M[4][2] = hL;
	M[8][1] = hL;
	M[8][2] = hL;
	M[8][3] = hL;
	M[8][4] = hL;
	M[8][8] = hL;
	M[8][9] = hL;
	M[8][10] = hL;
	M[10][2] = hL;
	M[10][3] = hL;
	M[10][4] = hL;
	M[10][5] = hL;
	M[10][9] = hL;
	M[10][10] = hL;
	M[8][11] = hL;
   
	//Horizontal Symmetry
	for (i = 1; i <12; i++){
        for (j = 1; j < 13; j++){
            M[i][22-j] = M[i][j];
        }
    }
	//Vertical Symmetry

    for (j = 1; j <22; j++)
    {
        for (i = 1; i < 12; i++)
        {
            M[22-i][j]=M[i][j];
        }

    }
    M[1][1] = pacman;
    M[12][11]=hL;
    

}

void afficher(char M[sizeM][sizeM]){
    int i, j;
    system("cls");
    printf("Votre score est %d \n\n", score );

    for(i=0; i<sizeM; i++) {
        for(j=0;j<sizeM;j++) {
            printf("%c ", M[i][j]);
        }
        printf("\n");
    }

    printf("\n\n");


    if (score == maxScore){
        printf("Vous avez gagn%c !\n", (char)130);
        sleep(50);
    }
}

void chercherPacman(char M[sizeM][sizeM], int *iPac, int *jPac) {
    int i, j;

    for (i = 0; i < sizeM; ++i) {
        for (j = 0; j < sizeM; ++j) {
            if (M[i][j] == pacman) {
                *iPac = i;
                *jPac = j;
                return;
            }
        }
    }
}

bool estObstacle(char M[sizeM][sizeM], int i, int j){

    if (M[i][j] == hL || M[i][j] == vL || M[i][j] == DoubleVL || M[i][j] == upRightL || M[i][j] == downRightL || M[i][j] == downLeftL || M[i][j] == upLeftL || M[i][j] == doubleHL || M[i][j] == square) {
        return true ;
    }
    return false;
}

void deplacer (char M[sizeM][sizeM]){
    int ch, i, j;

    for(i=0; i<sizeM; i++) {
        for (j = 0; j < sizeM; j++) {
            while ((ch = _getch()) != 27) /* 27 = Esc key */{
                if (ch == 0 || ch == 224){
                    chercherPacman(M, &iPac, &jPac);
                    switch (_getch ()) {
                        case 72:
                            printf("\nButton cliqu%c : Haut\n", (char)130);
                            if(!estObstacle(M, iPac-1, jPac) ){
                                M[iPac][jPac] = '.';
                                if (M[iPac-1][jPac] == coin) {
                                    score += 1;
                                    }
                                M[iPac-1][jPac] = pacman;
                            }
                            break;

                        case 80:
                            printf("\nButton cliqu%c : Bas\n", (char)130);
                            if(!estObstacle(M, iPac+1, jPac)){
                                M[iPac][jPac] = '.';
                                if (M[iPac+1][jPac] == coin) {
                                    score += 1;
                                    }
                                M[iPac+1][jPac] = pacman;
                            }
                            break;

                        case 75:
                            printf("\nButton cliqu%c : Gauche\n", (char)130);
                            if(!estObstacle(M, iPac, jPac-1)){
                                M[iPac][jPac] = '.';
                                if (M[iPac][jPac-1] == coin) {
                                    score += 1;
                                    }
                                M[iPac][jPac-1] = pacman;
                            }
                            break;

                        case 77:
                            printf("\nButton cliqu%c : Droite\n", (char)130);
                            if(!estObstacle(M, iPac, jPac+1)){
                                M[iPac][jPac] = '.';
                                if (M[iPac][jPac+1] == coin) {
                                    score += 1;
                                    }
                                M[iPac][jPac+1] = pacman;
                            }
                            break;
                    }
                    printf("\n");
                    afficher(M);
                    
                }
            }
        }
    }
}



// ------------------------------------------------------------------------



int main(){


	char M[sizeM][sizeM];
    initialiser(M);
    afficher(M);
    deplacer(M);
    sleep(10);
    return 0;
}
