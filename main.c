#include <stdio.h>
#include "stack.h"
#include <string.h>
#include <ctype.h>
#include <math.h>


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

void SynErr(char *str){
    int cnt_l = 0, cnt_r = 0;
    if(strlen(str)==0) {
        printf("syntax error");
        exit(0);
    }
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
        if(str[i] == '(' && str[i+1] == ')' ||(str[i] == '('&& isoper(str[i+1])==1)){
            printf("syntax error");
            exit(0);
        }else if(str[i] == '(')
            cnt_l++;
        else if(str[i] == ')' && str[i+1] == '(' ){
            printf("syntax error");
            exit(0);
        }else if(str[i] == ')')
            cnt_r++;
        if( cnt_r>cnt_l){
            printf("syntax error");
            exit(0);
        }
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

    if(isoper(str[strlen(str)-1])==1 ){
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

char *split(char *str, int ind){
    int i = ind + 1;
    int resSize = 1,resInd = 0;
    char *res = (char*)malloc(sizeof(char));

    while (str[i] != ' ' && str[i] != '\0'){
        res[resInd++] = str[i];
        resSize++;
        res = (char*) realloc(res,resSize*sizeof(char));
        i++;
    }
    res[resSize-1] ='\0';
    return res;
}

int splitInd(char *str, int ind){
    int i = ind;
    while (str[i] != ' ' && str[i] != '\0'){
        i++;
    }
    return i;
}

char* ToPostfix(char *infix){
    char *postfix;
    postfix = (char*)malloc(1*sizeof(char));
    int postfix_num = 0;
    int postSize = 1;
    postfix[postfix_num++] = ' ';
    postSize++;
    postfix = (char*)realloc(postfix,postSize*sizeof(char));
    STACK *stack = create();
    for(int i = 0; i < strlen(infix); i++) {
        if(isoper(infix[i])==1){
            postfix[postfix_num++] = ' ';
            postSize++;
            postfix = (char*)realloc(postfix,postSize*sizeof(char));
        }
        if(infix[i] == '(')
            push(stack,(int)infix[i]);
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
            push(stack,(int)infix[i]);
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

        postfix[postfix_num++] = ' ';
        postSize++;
        postfix = (char*)realloc(postfix,postSize*sizeof(char));
    }



    postfix = (char*)realloc(postfix,(postfix_num-1)*sizeof(char));
    if(postfix[strlen(postfix)-1] == ' ' && !isoper(postfix[strlen(postfix)-2] ))
        postfix_num--;
    postfix[postfix_num-1] = '\0';
    return postfix;
}

int ToInt(char *str) {
    int res = 0;
    int length = strlen(str);
    for (int i = length - 1; i >= 0; i--) {
        int digit = str[i] - '0';
        res += digit * pow(10, length - 1 - i);
    }

    return res;
}
void calculations(char *postfix){
    long long int result = 0;
    STACK *stack = create();
    for(int i = 0; i < strlen(postfix);i++){
        if (postfix[i] == ' ' && !isoper(postfix[i+1])&& i!= strlen(postfix)){
            char *s=split(postfix,i);
            int chis = ToInt(s);
            push(stack, chis);
            i = splitInd(postfix,i);
            print(stack);
        }
        else if(i != strlen(postfix)){

            if(postfix[i]=='+'){
                result = pop(stack) + pop(stack);
                push(stack,result);
            }
            else if(postfix[i]=='-'){
                int last = pop(stack);
                int first = pop(stack);
                result =  first - last;
                push(stack,result);
            }
            else if(postfix[i]=='*'){
                result = pop(stack) * pop(stack);
                push(stack,result);
            }
            else if(postfix[i]=='/'){
                int last = pop(stack);
                int first = pop(stack);
                if(last == 0){
                    printf("division by zero");
                    exit(0);
                }
                else{
                    result =  first / last;
                    push(stack,result);
                }

            }
        }
    }
    printf("%d", pop(stack));
}

int main() {
    char infix[1001];
    gets(infix);
    SynErr(infix);
    divBy0(infix);
    char *postfix = ToPostfix(infix);
    //printf("%s\n", postfix);
    calculations(postfix);
    return 0;
}