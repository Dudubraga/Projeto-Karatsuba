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

string number1; 
string number2; 

void PrintS(string str){
    ull i = 0;
    while(str.num[i] == '0'){ i++; }
    if(i == str.size){ 
        printf("0\n"); return;
    }
    for(i; i < str.size; i++){
        printf("%c", str.num[i]);
    } printf("\n");
}

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
        printf("\t\t ajeitando str1 : %s\n", str1);
        printf("\t\t ajeitando str2 : %s\n", str2);
        printf("\t\t add esses zeros em str1 : %s\n", power1);
        printf("\t\t add esses zeros em str2 : %s\n", power2);
    strcat(power1, str1);
    strcat(power2, str2);
        printf("\t\t\t strcat(zeros1, str1) : %s\n", power1);
        printf("\t\t\t strcat(zeros2, str2) : %s\n", power2);
    strcpy(str1, power1);
    strcpy(str2, power2);
        printf("\t\t\t copia do strcat pra str1 : %s\n", str1);
        printf("\t\t\t copia do strcat pra str2 : %s\n", str2);
}

string Zeros(string str, ull size, int n){
    printf("\tentrou no zero\n");
    printf("\tnumero de zeros : %lld\n", size / n);
    printf("%s --> ", str.num);
    for(int i = 0; i < size / n ; i++){
        str.num[i+str.size] = '0';
    }
    str.size += number1.size / n;
    printf("%s\n", str.num);
    return str;
}

string Substring(string str, ull pos){
    string s; memset(s.num, '\0', sizeof(s.num));
    s.size = str.size / 2;
    if(pos == 0){
        for(int i = 0; i < s.size; i++){
            s.num[i] = str.num[i];
        }
    }else{
        for(int i = 0; i < s.size; i++){
            s.num[i] = str.num[i + s.size];
        }
    }
    return s;
}

string Sum(string a, string b){
    printf("\tSOMANDO %s + %s\n", a.num, b.num);
    printf("\t DE TAMANHOS %lld e %lld\n", a.size, b.size);
    if(a.size > b.size){
        FixSize(a.num, b.num, a.size);
        a.size = strlen(a.num);
        b.size = strlen(b.num); 
        printf("\t DE TAMANHOS fixed %lld e %lld\n", a.size, b.size);
        printf("\tSOMANDO fixed %s + %s\n", a.num, b.num);
    }
    else if(a.size < b.size){
        FixSize(a.num, b.num, b.size);
        a.size = strlen(a.num);
        b.size = strlen(b.num); 
        printf("\t DE TAMANHOS fixed %lld e %lld\n", a.size, b.size);
        printf("\tSOMANDO fixed %s + %s\n", a.num, b.num);
    }
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

string Multiply(string x, string y){
    printf("ENTROU NA MULTIPLICACAO\n");
        string product; memset(product.num, '\0', sizeof(product.num));
        int r = (x.num[0] - '0') * (y.num[0] - '0');
        if(r >= 10){
            product.num[0] = r / 10 + '0';
            product.num[1] = r % 10 + '0';
        }else{
            product.num[0] = '0';
            product.num[1] = r + '0';
        }
        product.size = 2;
        printf("product.num -> %s\n", product.num);
        printf("product.size -> %lld\n", product.size);
        return product;
}

string Karatsuba(string x, string y){
    printf("\nx -> %s ; x.size = %lld\n", x.num, x.size);
    printf("y -> %s ; y.size = %lld\n\n", y.num, y.size);
    if(x.size == 1){
        string result = Multiply(x, y);
        return result;
    }
    string a, b, c, d;
    a = Substring(x, 0); b = Substring(x, 1);
    c = Substring(y, 0); d = Substring(y, 1);
    printf("a -> %s ; ", a.num); printf("a.size -> %lld\n", a.size); 
    printf("b -> %s ; ", b.num); printf("b.size -> %lld\n", b.size);
    printf("c -> %s ; ", c.num); printf("c.size -> %lld\n", c.size); 
    printf("d -> %s ; ", d.num); printf("d.size -> %lld\n", d.size);
    string ac = Karatsuba(a, c); printf("ac -> %s\n", ac.num);
    string ad = Karatsuba(a, d); printf("ad -> %s\n", ad.num);
    string bc = Karatsuba(b, c); printf("bc -> %s\n", bc.num);
    string bd = Karatsuba(b, d); printf("bd -> %s\n", bd.num);
    printf("\nCHEGOU AQUI\n");

    string adbc = Zeros(Sum(ad, bc), x.size, 2); /* 10^n/2 */ printf("adbc -> %s\n", adbc.num);
    string r1 = Zeros(ac, x.size, 1); /* 10^n */ printf("r1 -> %s\n", r1.num);
    string r2 = Sum(r1, adbc); printf("r2 -> %s\n", r2.num);
    string r3 = Sum(r2, bd); printf("r3 -> %s\n", r3.num);
    return r3;
}

int main(){
    scanf("%s", number1.num); 
    scanf("%s", number2.num); 
    number1.size = strlen(number1.num);
    number2.size = strlen(number2.num);

    if(number1.size > MAX_INPUT || number2.size > MAX_INPUT){
        printf("Numero muito grande.\n");
        exit(1);
    }

    printf("number 1 -> %s\n", number1.num);
    printf("number 2 -> %s\n", number2.num);

    if(number1.size > number2.size){
        FixSize(number1.num, number2.num, number1.size);
    }else{
        FixSize(number1.num, number2.num, number2.size);
    }
    number1.size = strlen(number1.num);
    number2.size = strlen(number2.num);

    printf("number 1 fixed -> %s\n", number1.num); //printf("size1 = %u\n", number1.size);
    printf("number 2 fixed -> %s\n", number2.num); //printf("size2 = %u\n", number2.size);

    string SOMA = Sum(number1, number2);
    printf("\nsoma = ");PrintS(SOMA); printf("\n");
    string result = Karatsuba(number1, number2);
    printf("\nmultiplicacao = "); PrintS(result); printf("\n");

    return 0;
}
