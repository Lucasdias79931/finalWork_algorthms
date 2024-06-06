#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#define rows 6
#define cols 6

char game[rows][cols];
char operacao = ' '; // operação que o usuário vai escolher
char end = ' '; // finalizar o jogo;
int jogadas;
int erros;
int acertos;
char posicao[3];
int posiX; // coordenada X para percorrer a matriz
int posiY; // coordenada Y para percorrer a matriz
float numero1;
float numero2;

void clearScreen();       // limpa terminal
void initializeGame();    // inicializa a matriz com números aleatórios
void menu();              // mostra o jogo atualizado na tela
void display_coordenadas();           // declaração da função display_coordenadas
void display_calculo();
float calcular(float num1, float num2,char op);
bool verificaResultado(float resultado, float resultadoUs);

int main(){

    // vetor com todas as posições possiveis da calculadora
    char posicoes[36][3] = {"00", "01", "02", "03", "04", "05",
                             "10", "11", "12", "13", "14", "15",
                             "20", "21", "22", "23", "24", "25",
                             "30", "31", "32", "33", "34", "35",
                             "40", "41", "42", "43", "44", "45",
                             "50", "51", "52", "53", "54", "55"};

    // cria e inicializa o jogo
    initializeGame();

    
    
    while (end == ' '){
        
        
        
        
        // solicita as coordenadas ao usuário
        int numeros = 0; // para verificar se conseguiu selecionar os dois números
        while (numeros != 2){
            
            clearScreen();
            display_coordenadas();
            
            if(numeros == 0){
                printf("\n                              para o primerio número");
            }else{
                printf("\n                              para o segundo número\n");
            }

            menu();
            

            fgets(posicao, 3, stdin);
            getchar();

            // Verifica se todas as coordenadas são dígitos
            bool coordenadasNumericas = true;
            for (int i = 0; i < 2; i++){
                if(!isdigit(posicao[i])){
                    coordenadasNumericas = false;
                    break;
                }
            }

            if (!coordenadasNumericas){
                printf("\n                              As coordenadas devem ser numéricas!");
                getchar(); // Para evitar que a mensagem seja imediatamente sobrescrita
                continue;
            }

            bool posicaoExiste = false;

            for (int z = 0; z < rows * cols; z++){
                if (strcmp(posicao, posicoes[z]) == 0){
                    posicaoExiste = true;

                    posiX = posicao[0] - '0';
                    posiY = posicao[1] - '0';
                    break;
                }
            }

            if (!posicaoExiste){
                printf("\n                              Digito Errado! Favor digitar posição correspondente ao diagrama");
                continue;
            }

            char current = game[posiX][posiY];

            // verifica se o número está disponível e computa
            if (current == ' '){
                printf("\n                              Digito não está disponível! Favor digitar posição correspondente ao diagrama");
                continue;
            }else{
                if(numeros == 0){
                    numero1 = (float)(game[posiX][posiY] + '0');
                }else{
                    numero2 = (float)(game[posiX][posiY] + '0');
                }
                game[posiX][posiY] = ' ';
                numeros++;
            }

            if (numeros == 2)break;
               
            
        }
        
        //solicita a operação
        while(true){
            clearScreen();
            menu();
            display_calculo();
            operacao = getchar();
            getchar();

            if(operacao!='+' && operacao!='-' && operacao!='*' && operacao!='/' ){
                printf("\n                              Digito Errado! Escolha apenas uma das 4 operações");
                getchar(); // pausar antes de voltar
                continue;
            }

            break;
        }
   
        //solicita ao usuário qual resultado do calculo
       
        float resp = calcular(numero1,numero2,operacao);
        float resUser;
        
        printf("\n                              Qual Resultado da operação? ");
            
        while (true) {
            printf("\nDigite: ");
            char temp[5];
            fgets(temp, 5, stdin);
            char *end;
            resUser = strtof(temp,&end);

            if(*end == '\0' || *end== '\n')break;

        }

        if(verificaResultado(resp, resUser)){
            acertos++;
        }else{
            erros++;
        }
        jogadas++;
         
        
        printf("\n                              Digite 's' se quiser sair ");
        scanf(" %c",&end);
        if(end == 's' || end == "S" || jogadas >24 )break;    
        
   
    }
   

    return 0;
}


bool verificaResultado(float resultado, float resultadoUs){
    return resultado == resultadoUs;
}

float calcular(float num1, float num2, char op){
    switch (op){
    case '+':
        return num1 + num2;
        break;
    case '-':
        return num1 - num2;
        break;
    case '*':
        return num1 * num2;
        break;
    case '/':
        return num1 / num2;
        break;
    
    }
}

void display_calculo(){
    printf("\n                              (/) para dividir    (*) para multiplicar");
    printf("\n                              (+) para somar      (-) para subtrair\n");
}
void display_coordenadas()
{
    printf("\n                              Digite a posição (entre 00 e 55) de acordo com o diagrama:");
}

void menu()
{

    printf("\n                                                  Números");
    printf("\n                                               0 1 2 3 4 5");
    printf("\n\n                                          0    %c|%c|%c|%c|%c|%c", game[0][0], game[0][1], game[0][2], game[0][3], game[0][4], game[0][5]);
    printf("\n                                               -----------");
    printf("\n                                          1    %c|%c|%c|%c|%c|%c", game[1][0], game[1][1], game[1][2], game[1][3], game[1][4], game[1][5]);
    printf("\n                                               -----------");
    printf("\n                                          2    %c|%c|%c|%c|%c|%c", game[2][0], game[2][1], game[2][2], game[2][3], game[2][4], game[2][5]);
    printf("\n                                               -----------");
    printf("\n                                          3    %c|%c|%c|%c|%c|%c", game[3][0], game[3][1], game[3][2], game[3][3], game[3][4], game[3][5]);
    printf("\n                                               -----------");
    printf("\n                                          4    %c|%c|%c|%c|%c|%c", game[4][0], game[4][1], game[4][2], game[4][3], game[4][4], game[4][5]);
    printf("\n                                               -----------");
    printf("\n                                          5    %c|%c|%c|%c|%c|%c", game[5][0], game[5][1], game[5][2], game[5][3], game[5][4], game[5][5]);
    printf("\n                                               -----------\n\n");
}

void initializeGame()
{
    int i = 0, j = 0;
    srand(time(NULL));

    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            int temp = 1 + (rand() % 9); 
            game[i][j] = temp + '0'; 
        }
    }

    operacao = ' ';
    end = ' ';
    jogadas = 0;
    acertos =0;
    numero1 = 0;
    numero2 = 0;
    posiX = 0;
    posiY = 0;
    erros =0;
}

void clearScreen()
{
#ifdef _WIN32
    system("cls"); // Comando para limpar o terminal no Windows
#else
    system("clear"); // Comando para limpar o terminal no Linux e macOS
#endif
}

