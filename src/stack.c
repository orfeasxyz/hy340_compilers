#include "../include/stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

stack_T scopeOffsetStack = NULL;
stack_T functionScopeStack = NULL;

struct stack{
    int data;
    struct stack* next;
};

stack_T stack_push(stack_T head, int data){
    stack_T temp = malloc(sizeof(struct stack));
    temp->data = data;
    temp->next = head;
    head = temp;
    return head;
}

int stack_top(stack_T head){
    if(!head) return 0;
    return head->data;
}

stack_T stack_pop(stack_T head){
    assert(head);
    stack_T temp = head;
    head = head->next;
    free(temp);
    return head;
}
