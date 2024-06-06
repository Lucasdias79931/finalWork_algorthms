#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h>

#define rows 6
#define cols 6

char end  = ' '; //finalizar o jogo;
int jogadas;
char posicao[3];

int posiX; //coordenada X para percorrer a matriz
int posiY;//coordenada Y para percorrer a matriz
    

void clearScreen(); // limpla terminal
void initializeMatriz(int matriz[rows][cols]);// inicializa a matriz com números aleatórios
void menu(int matriz[rows][cols]); // mostra o jogo atualizado na tela
display(){
    printf("\n                              Digite a posição (entre 00 e 55) de acordo com o diagrama:");
}




int main(){
    
    //vetor com todas as posições possiveis da calculadora
    char posicoes[36][3] = {"00", "01", "02", "03", "04", "05",
                             "10", "11", "12", "13", "14", "15",
                             "20", "21", "22", "23", "24", "25",
                             "30", "31", "32", "33", "34", "35",
                             "40", "41", "42", "43", "44", "45",
                             "50", "51", "52", "53", "54", "55"};
    
    //cria e inicializa o jogo
    int game[rows][cols];
    initializeMatriz(game);

    //laço principal do jogo inteiro
    display();
    menu(game);

   

    return 0;
}

void menu(int matriz[rows][cols]){
    printf("\n                                                  Números");
    printf("\n                                               0 1 2 3 4 5");
    printf("\n\n                                          0    %d|%d|%d|%d|%d|%d",matriz[0][0],matriz[0][1],matriz[0][2],matriz[0][3],matriz[0][4],matriz[0][5]);
    printf("\n                                               -----------");
    printf("\n                                          1    %d|%d|%d|%d|%d|%d",matriz[1][0],matriz[1][1],matriz[1][2],matriz[1][3],matriz[1][4],matriz[1][5]);
    printf("\n                                               -----------");
    printf("\n                                          2    %d|%d|%d|%d|%d|%d",matriz[2][0],matriz[2][1],matriz[2][2],matriz[2][3],matriz[2][4],matriz[2][5]);
    printf("\n                                               -----------");
    printf("\n                                          3    %d|%d|%d|%d|%d|%d",matriz[3][0],matriz[3][1],matriz[3][2],matriz[3][3],matriz[3][4],matriz[3][5]);
    printf("\n                                               -----------");
    printf("\n                                          4    %d|%d|%d|%d|%d|%d",matriz[4][0],matriz[4][1],matriz[4][2],matriz[4][3],matriz[4][4],matriz[4][5]);
    printf("\n                                               -----------");
    printf("\n                                          5    %d|%d|%d|%d|%d|%d",matriz[5][0],matriz[5][1],matriz[5][2],matriz[5][3],matriz[5][4],matriz[5][5]);
    printf("\n                                               -----------\n\n");
}
void initializeMatriz(int matriz[rows][cols]){
    int i =0, j =0;
    srand(time(NULL)); 

    for(i = 0; i< rows; i++){
        for(j = 0; j< cols; j++){
            matriz[i][j] = 1 + rand() % 9; 
        }
    }
    
    
}
void clearScreen() {
    #ifdef _WIN32
        system("cls"); // Comando para limpar o terminal no Windows
    #else
        system("clear"); // Comando para limpar o terminal no Linux e macOS
    #endif
}