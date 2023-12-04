#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

void divide(char* str){
    printf("\n");
    if(strlen(str) == 1){ 
        printf("final = %s\n", str);
        return;
    }
    char strLeft[strlen(str) / 2]; memset(strLeft, '\0', sizeof(strLeft)+1);
    char strRight[strlen(str) / 2]; memset(strRight, '\0', sizeof(strRight)+1);
    for(int i = 0; i < strlen(str) / 2; i++){
        strLeft[i] = str[i];
        strRight[i] = str[i + strlen(str) / 2]; 
    }
    
    printf("sizeof left = %d ; left -> %s\n", sizeof(strLeft), strLeft);
    printf("sizeof right = %d ; right -> %s\n", sizeof(strRight), strRight);

    divide(strLeft); divide(strRight);
}

int main(){
    char* str1 = "12345678";
    divide(str1);

    return 0;
}
