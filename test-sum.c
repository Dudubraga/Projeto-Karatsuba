#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAX_SIZE 65536 /* 2^16 */
#define MAX_INPUT 32768 /* 2^15 */

typedef unsigned long long ull;
typedef struct{
    char num[MAX_SIZE];
    ull size;
} string;

void FixSize(char* str1, char* str2, ull size){
    if(size == 1){ return; }
    int p = 1;
    while(size > pow(2, p)){ p++; }
    ull zeros = pow(2, p);
    char power1[zeros];
    char power2[zeros];
    memset(power1, '\0', sizeof(power1));
    memset(power2, '\0', sizeof(power2));
    memset(power1, '0', zeros - strlen(str1));
    memset(power2, '0', zeros - strlen(str2));
    
    strcat(power1, str1);
    strcat(power2, str2);
    strcpy(str1, power1);
    strcpy(str2, power2);
}

string Sum(string a, string b){
    ull carry = 0;
    string r; memset(r.num, '\0', sizeof(r));
    string result; memset(result.num, '\0', sizeof(result));
    for(int i = a.size-1; i >= 0; i--){
        ull sum = (a.num[i] - '0') + (b.num[i] - '0');
        r.num[i] = ((sum + carry) % 10) + '0';
        carry = (sum + carry) / 10;
    }
    if(carry != 0){
        result.num[0] = '1';
        strcat(result.num, r.num);
        result.size = strlen(result.num);
    }else{
        strcpy(result.num, r.num);
        result.size = strlen(result.num);
    }
    return result;
}

int main(){
    string number1; scanf("%s", number1.num); 
    string number2; scanf("%s", number2.num); 
    number1.size = strlen(number1.num);
    number2.size = strlen(number2.num);

    if(number1.size > MAX_INPUT || number2.size > MAX_INPUT){
        printf("Numero muito grande.\n");
        exit(1);
    }

    printf("number 1 -> %s\n", number1.num);
    printf("number 2 -> %s\n\n", number2.num);

    if(number1.size > number2.size){
        FixSize(number1.num, number2.num, number1.size);
    }else{
        FixSize(number1.num, number2.num, number2.size);
    }
    number1.size = strlen(number1.num);
    number2.size = strlen(number2.num);

    printf("number 1 fixed -> %s\n", number1.num); //printf("size1 = %u\n", number1.size);
    printf("number 2 fixed -> %s\n\n", number2.num); //printf("size2 = %u\n", number2.size);

    string result = Sum(number1, number2);
    printf("%s\n", result.num);

    return 0;
}
