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

void push(STACK *S, STACK *elem){
    STACK *first = S->next;
    elem->next = first;
    S->next = elem;
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


#endif //CALCULATOR_STACK_H
