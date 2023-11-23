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
int isoper(char symb){
    switch (symb) {
        case '+':
        case '-':
        case '*':
        case '/':
            return 1;
        case ')':
        case '(':
            return 2;
        default:
            return 0;
    }
}

char* ToPostfix(char *infix, int len){
    char *postfix;
    postfix = (char*)malloc(1*sizeof(char));
    int postfix_num = 0;
    int postSize = 1;
    STACK *stack = create();
    for(int i = 0; i < strlen(infix); i++) {
        if(isoper(infix[i])==1){
            postfix[postfix_num++] = ' ';
            postSize++;
            postfix = (char*)realloc(postfix,postSize*sizeof(char));
        }
        if(infix[i] == '(')
            push(stack,infix[i]);
        else if ((infix[i]=='+')||(infix[i]=='-')||(infix[i]=='/')||(infix[i]=='*')){
            while(!empty(stack) && operand_priority(getval(stack))
            >= operand_priority(infix[i]) && getval(stack)!='('){
                postfix[postfix_num++] = pop(stack);
                postSize++;
                postfix = (char*)realloc(postfix,postSize*sizeof(char));
                postfix[postfix_num++] = ' ';
                postSize++;
                postfix = (char*)realloc(postfix,postSize*sizeof(char));
            }
            push(stack,infix[i]);
        }
        else if(infix[i] == ')'){
            postfix[postfix_num++] = ' ';
            postSize++;
            postfix = (char*)realloc(postfix,postSize*sizeof(char));
            while(!empty(stack) && getval(stack) != '('){
                postfix[postfix_num++] = pop(stack);
                postSize++;
                postfix = (char*)realloc(postfix,postSize*sizeof(char));

            }
            del(stack);

        }
        else{
            postfix[postfix_num++] = infix[i];
            postSize++;
            postfix = (char*)realloc(postfix,postSize*sizeof(char));
        }

    }
    postfix = (char*)realloc(postfix,postSize*sizeof(char));
    postfix[postfix_num++] = ' ';
    postSize++;

    while(!empty(stack)){
        postfix[postfix_num++] = pop(stack);
        postSize++;
        postfix = (char*)realloc(postfix,postSize*sizeof(char));

    }
    postfix[postSize-1]='\0';
    return postfix;
}

int main() {
    char infix[1000];
    gets(infix);
    SynErr(infix);
    divBy0(infix);
    char *postfix = ToPostfix(infix, strlen(infix));
    printf("%s\n", postfix);
    return 0;
}
