#include <stdio.h>

#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define YELLOW "\033[33m"
#define WHITE "\033[37m"
#define BLACK "\033[30m"
#define RESET "\033[0m"

int main() {
    printf(MAGENTA "Este texto é magenta\n" RESET);
    printf(CYAN "Este texto é ciano\n" RESET);
    printf(YELLOW "Este texto é amarelo\n" RESET);
    printf(WHITE "Este texto é branco\n" RESET);
    printf(BLACK "Este texto é preto\n" RESET);

    return 0;
}
