#include <stdio.h>
#include "stack.h"
#include <string.h>


void SynErr(char *str){
    int cnt_l = 0, cnt_r = 0;

    if(str[0] == '+' ||str[0] == '*' || str[0] == '/') {
        printf("syntax error");
        exit(0);
    }

    for (int i = 0; i < strlen(str); i++){
        if((str[i]>='0' && str[i]<='9')||
           (str[i]>='(' && str[i]<='+')||(str[i]=='-')||(str[i]=='/')){
        }
        else{
            printf("syntax error");
            exit(0);
        }
        if(str[i] == '(' && str[i+1] == ')'){
            printf("syntax error");
            exit(0);
        }else if(str[i] == '(')
            cnt_l++;
        else if(str[i] == ')' && str[i+1] == '('){
            printf("syntax error");
            exit(0);
        }else if(str[i] == ')')
            cnt_r++;
        if((str[i] == '+' ||str[i] == '-' ||str[i] == '*' ||str[i] == '/') &&
        (str[i+1] == '+' ||str[i+1] == '-' ||str[i+1] == '*' ||str[i+1] == '/')) {
            printf("syntax error");
            exit(0);
        }
    }

     if(cnt_l != cnt_r) {
         printf("syntax error");
         exit(0);
     }

}

void divBy0(char *str){
    for (int i = 0; i < strlen(str); i++){
        if(str[i]=='/' && str[i+1]=='0'){
            printf("division by zero");
            exit(0);
        }
    }
}


int main() {
    STACK *cur_stack = create();
    char str[1000];
    gets(str);
    SynErr(str);
    divBy0(str);
    for(int i = 0; i < 5; i++)
        push(cur_stack,'2');
    print(cur_stack);
    return 0;
}
