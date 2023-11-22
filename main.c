#include <stdio.h>
#include "stack.h"
#include <string.h>
#include <ctype.h>

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


int operand_priority(char symb){
    switch (symb) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case ')':
            return 3;
        case '(':
            return 4;
        default:
            return 0;
    }
}


char* ToPostfix(char *infix, int len){
    char *postfix = (char*)malloc(sizeof(char)*len*2);
    int postfix_num = 0, last_priority = 0;
    STACK *stack = create();
    for(int i = 0; i < len; i++){
        if(isdigit(infix[i]) != 0){
            postfix[postfix_num] = infix[i];
            postfix_num++;
        }
        else{
            postfix[postfix_num++] = ' ';
            if(empty(stack)){
                push(stack,infix[i]);
                last_priority = operand_priority(infix[i]);

            }
            else if(operand_priority(infix[i]) <= last_priority){
                postfix[postfix_num++] = pop(stack);
                push(stack,infix[i]);
                last_priority = operand_priority(infix[i]);
            }
            else{
                push(stack,infix[i]);
                last_priority = operand_priority(infix[i]);
            }
            postfix[postfix_num++] = ' ';
        }
    }
    while (!empty(stack)){
        postfix[postfix_num++] = ' ';
        postfix[postfix_num++] = pop(stack);
        postfix[postfix_num++] = ' ';
    }
    return postfix;
}

int main() {
    char infix[1000];
    gets(infix);
    SynErr(infix);
    divBy0(infix);
    char *postfix = ToPostfix(infix, strlen(infix));
    for(int i = 0; i < strlen(postfix); i++){
        printf("%c", postfix[i]);
    }
    return 0;
}
