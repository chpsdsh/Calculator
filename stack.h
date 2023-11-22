#ifndef CALCULATOR_STACK_H
#define CALCULATOR_STACK_H
#define STACK struct stack
#include <stdio.h>
#include <malloc.h>

STACK{
    char value;
    STACK *next;
};

STACK* create(){
    STACK *Telem;
    Telem = (STACK*)malloc(sizeof(STACK));
    Telem->value = 0;
    Telem->next = NULL;
    return Telem;
}

void push(STACK *S, char value){
    STACK *first = S->next;
    STACK *elem;
    elem = (STACK*)malloc(sizeof(STACK));
    elem->value = value;
    elem->next = first;
    S->next = elem;
}

void print(STACK *S){
    STACK *ptr = S-> next;
    while (ptr != NULL){
        printf("%d\n",ptr->value);
        ptr = ptr->next;
    }
}

void delete(STACK *pre){
    STACK *d = pre->next;
    if(d){
        pre->next = d->next;
        free(d);
    }
}

int empty(STACK*S){//проверка на пустоту
    if(S->next)
        return 0;
    else
        return 1;
}
char pop(STACK *S){
    STACK *first = S->next;
    char val = first->value;
    if(!empty(S)){
        S->next = first->next;
        free(first);
        return val;
    }
}

#endif //CALCULATOR_STACK_H
