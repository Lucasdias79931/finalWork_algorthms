#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define RESET "\033[0m"
#define MAGENTA "\033[35m"
#define RED "\033[31m"
#define CYAN "\033[36m"
#define YELLOW "\033[33m"

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
    char operacoes[18];
    int k = 0;
    int i = 0;

    for(i = 0; i < 18; i++){
        operacoes[k] = ' ';
    }

    initializeGame();

    while (true){


        int numeros = 0;
        while (numeros != 2){
            clearScreen();
            display_coordenadas();

            if(numeros == 0){
                printf(MAGENTA"\n                              para o primerio número",RESET);
            } else {
                printf(MAGENTA"\n                              para o segundo número\n",RESET);
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
                printf(MAGENTA"\n                              As coordenadas devem ser numéricas!"RESET);
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
                printf(MAGENTA"\n                              Digito Errado! Favor digitar posição correspondente ao diagrama",RESET);
                getchar();
                continue;
            }

            char current = game[posiX][posiY];

            if (current == ' '){
                printf(MAGENTA"\n                              Digito não está disponível! Favor digitar posição correspondente ao diagrama",RESET);
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
                printf(MAGENTA"\n                              Digito Errado! Escolha apenas uma das 4 operações",RESET);
                getchar();
                continue;
            }

            int cont = 0;
            int w = 0;
            for(w = 0; w < 18; w++){
                if(operacao == operacoes[w])cont++;
            }

            if(cont == 5){
                printf(MAGENTA"\n                     A operação já foi usada muitas vezes! Escolha outra das 4 operações",RESET);
                
            }else{
                operacoes[k++] = operacao;

                printf(MAGENTA"\n                     Você escolheu a operação '%c' %d Vezes",operacao,cont + 1,RESET);
                break;
            }
            
        }
       
        float resp = calcular(numero1, numero2, operacao);
        float resUser;

        int tentativas = 0;
        while (true) {
        
            printf(MAGENTA"\n                              Qual Resultado da operação? ",RESET);
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
                    printf(MAGENTA"\n                              Resposta Errada! TENTE NOVAMENTE! ",RESET);
                    jogadas++;
                    erros++;
                }
            }

            if(tentativas >= 3){
                clearScreen();
                printf(MAGENTA"\n                              's' para pedir a resposta",RESET);
                char op = getchar();
                getchar();
                if(op == 's' || op == 'S'){
                    printf(MAGENTA"\n                              Resposta correta: %.2f", resp,RESET);
                    getchar();
                    acertos++;
                    
                    break;
                }else{
                    break;
                }
            }
        }
       
       
        

        clearScreen();
        printf(MAGENTA"\n                              Digite 's' se quiser sair ",RESET);
        end = getchar();
        getchar();
        if(end == 's' || end == 'S' || jogadas == 24) break;
    }

    clearScreen();

    if(acertos == 18){

        printf(MAGENTA"\n                              Vitória ",RESET);
        printf(MAGENTA"\n                              Jogadas:%d",jogadas,RESET);
        printf(MAGENTA"\n                              Erros:%d",erros,RESET);
    }else{

        printf(MAGENTA"\n                              Derrota",RESET);
        printf(MAGENTA"\n                              Jogadas:%d",jogadas,RESET);
        printf(MAGENTA"\n                              Acertos:%d",acertos,RESET);
    }

    printf("\n\n");


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
    printf(MAGENTA"\n                              (/) para dividir    (*) para multiplicar",RESET);
    printf(MAGENTA"\n                              (+) para somar      (-) para subtrair\n",RESET);
}

void display_coordenadas(){
    printf(MAGENTA"\n                              Digite a posição (entre 00 e 55) de acordo com o diagrama:",RESET);
}

void menu(){
    printf(YELLOW"\n                                                  Números",RESET);
    printf(YELLOW"\n                                               0 1 2 3 4 5",RESET);
    for (int i = 0; i < ROWS; i++) {
        printf(YELLOW"\n                                           %d",i,RESET);
        printf(MAGENTA"   %c|%c|%c|%c|%c|%c", game[i][0], game[i][1], game[i][2], game[i][3], game[i][4], game[i][5],RESET);
        if (i < ROWS - 1) printf(CYAN"\n                                               -----------"RESET);
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