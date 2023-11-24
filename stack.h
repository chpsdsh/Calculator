#ifndef CALCULATOR_STACK_H
#define CALCULATOR_STACK_H
#define STACK struct stack
#include <stdio.h>
#include <malloc.h>

STACK{
    int value;
    STACK *next;
};

STACK* create(){
    STACK *Telem;
    Telem = (STACK*)malloc(sizeof(STACK));
    Telem->value = 0;
    Telem->next = NULL;
    return Telem;
}

void push(STACK *S, int value){
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



int empty(STACK*S){//проверка на пустоту
    if(S->next)
        return 0;
    else
        return 1;
}

int getval(STACK *S){
    STACK *frst = S->next;
    return frst->value;
}

void del(STACK *S){
    STACK *first = S->next;
    if(!empty(S)) {
        S->next = first->next;
        free(first);
    }
}

int pop(STACK *S){
    STACK *first = S->next;
    int val = first->value;
    if(!empty(S)){
        S->next = first->next;
        free(first);
        return val;
    }
}

#endif //CALCULATOR_STACK_H