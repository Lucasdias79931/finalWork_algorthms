#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>


int main() {
    
    char a = '2', b = '4';
    float num1 = (float)(a - '0');
    float num2 = (float)(b - '0');

    float rest = num1 / num2;
    

    printf("\nresu:%.2f", rest);
    float res;
   while (true)
   {
        printf("\nDigite:");
        char temp[5];
        
        fgets(temp,5,stdin);
        getchar();
        
        char *end;
        res = strtof(temp,&end);

        
        if(*end == '\0'){
            printf("\n digito corrento");
            getchar();
            
        }else{
            continue;
        }
        break;
        
   }
   

   
    if(res == rest){
        printf("\nCerto");
    }else{
        printf("\nerrado");
    }
    return 0;
}
