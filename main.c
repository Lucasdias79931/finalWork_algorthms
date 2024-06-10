#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

//linhas e colunas da matriz 
#define ROWS 6
#define COLS 6

//inicialização das variaveis globais
char posicoes[36][3] = {
    "00", "01", "02", "03", "04", "05",
    "10", "11", "12", "13", "14", "15",
    "20", "21", "22", "23", "24", "25",
    "30", "31", "32", "33", "34", "35",
    "40", "41", "42", "43", "44", "45",
    "50", "51", "52", "53", "54", "55"
};
char game[ROWS][COLS];
char operacao = ' '; 
char end = ' ';
int jogadas;
int erros;
int acertos;
char posicao[3];
int posiX;
int posiY;
float numero1;
float numero2;


void clearScreen();       
void initializeGame();    
void menu();              
void display_coordenadas();           
void display_calculo();
float calcular(float num1, float num2, char op);
bool verificaResultado(float resultado, float resultadoUs);


int main(){
    char operacoes[25];
    int k = 0;
    int i = 0;

    for(i = 0; i < 24; i++){
        operacoes[k] = ' ';
    }

    initializeGame();

    while (true){


        int numeros = 0;
        while (numeros != 2){
            clearScreen();
            display_coordenadas();

            if(numeros == 0){
                printf("\n                              para o primerio número");
            } else {
                printf("\n                              para o segundo número\n");
            }

            menu();

            fgets(posicao, 3, stdin);
            getchar();

            bool coordenadasNumericas = true;
            for (int i = 0; i < 2; i++){
                if(!isdigit(posicao[i])){
                    coordenadasNumericas = false;
                    break;
                }
            }

            if (!coordenadasNumericas){
                printf("\n                              As coordenadas devem ser numéricas!");
                getchar();
                continue;
            }

            bool posicaoExiste = false;
            for (int z = 0; z < ROWS * COLS; z++){
                if (strcmp(posicao, posicoes[z]) == 0){
                    posicaoExiste = true;
                    posiX = posicao[0] - '0';
                    posiY = posicao[1] - '0';
                    break;
                }
            }

            if (!posicaoExiste){
                printf("\n                              Digito Errado! Favor digitar posição correspondente ao diagrama");
                getchar();
                continue;
            }

            char current = game[posiX][posiY];

            if (current == ' '){
                printf("\n                              Digito não está disponível! Favor digitar posição correspondente ao diagrama");
                getchar();
                continue;
            } else {
                if(numeros == 0){
                    numero1 = (float)(current - '0');
                } else {
                    numero2 = (float)(current - '0');
                }
                game[posiX][posiY] = ' ';
                numeros++;
            }
        }

        while (true){
            clearScreen();
            menu();
            display_calculo();
            operacao = getchar();
            getchar();

            if(operacao != '+' && operacao != '-' && operacao != '*' && operacao != '/'){
                clearScreen();
                printf("\n                              Digito Errado! Escolha apenas uma das 4 operações");
                getchar();
                continue;
            }

            int cont = 0;
            int w = 0;
            for(w = 0; w < 24; w++){
                if(operacao == operacoes[w])cont++;
            }

            if(cont == 6){
                printf("\n                     A operação já foi usada muitas vezes! Escolha outra das 4 operações");
                
            }else{
                break;
            }
            
        }
       
        float resp = calcular(numero1, numero2, operacao);
        float resUser;

        int tentativas = 0;
        while (true) {
        
            printf("\n                              Qual Resultado da operação? ");
            char temp[10]; 
            fgets(temp, 10, stdin);
            getchar();
            char *endPtr;
            resUser = strtof(temp, &endPtr);
            tentativas++;

            if(endPtr != temp){
                clearScreen();
                if(verificaResultado(resp, resUser)){
                    acertos++;
                    jogadas++;
                    break;
                } else {
                    clearScreen();    
                    printf("\n                              Resposta Errada! ");
                    jogadas++;
                    erros++;
                }
            }

            if(tentativas >= 3){
                clearScreen();
                printf("\n                              's' para pedir a resposta");
                char op = getchar();
                getchar();
                if(op == 's' || op == 'S'){
                    printf("\n                              Resposta correta: %2f", resp);
                    getchar();
                    acertos++;
                    
                    break;
                }else{
                    break;
                }
            }
        }
       
       
        

       
        printf("\n                              Digite 's' se quiser sair ");
        end = getchar();
        getchar();
        if(end == 's' || end == 'S' || jogadas == 24) break;
    }


    if(acertos == 18){

        printf("\n                              Vitória ");
        printf("\n                              Jogadas:%d",jogadas);
        printf("\n                              Erros:%d",erros);
    }else{

        printf("\n                              Derrota");
        printf("\n                              Jogadas:%d",jogadas);
        printf("\n                              Acertos:%d",acertos);
    }


    return 0;
}

void initializeGame(){
    srand(time(NULL));

    for (int i = 0; i < ROWS; i++){
        for (int j = 0; j < COLS; j++){
            int temp = 1 + (rand() % 9); 
            game[i][j] = temp + '0';
        }
    }

    operacao = ' ';
    end = ' ';
    jogadas = 0;
    acertos = 0;
    numero1 = 0;
    numero2 = 0;
    posiX = 0;
    posiY = 0;
    erros = 0;
}



bool verificaResultado(float resultado, float resultadoUs){
    const float epsilon = 0.0001;
    return fabs(resultado - resultadoUs) < epsilon;
}

float calcular(float num1, float num2, char op){
    switch (op){
        case '+': return num1 + num2;
        case '-': return num1 - num2;
        case '*': return num1 * num2;
        case '/': return num1 / num2;
        default: return 0; 
    }
}

void display_calculo(){
    printf("\n                              (/) para dividir    (*) para multiplicar");
    printf("\n                              (+) para somar      (-) para subtrair\n");
}

void display_coordenadas(){
    printf("\n                              Digite a posição (entre 00 e 55) de acordo com o diagrama:");
}

void menu(){
    printf("\n                                                  Números");
    printf("\n                                               0 1 2 3 4 5");
    for (int i = 0; i < ROWS; i++) {
        printf("\n                                          %d    %c|%c|%c|%c|%c|%c", i, game[i][0], game[i][1], game[i][2], game[i][3], game[i][4], game[i][5]);
        if (i < ROWS - 1) printf("\n                                               -----------");
    }
    printf("\n\n");
}


void clearScreen(){
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}