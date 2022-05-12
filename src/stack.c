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

void func_stack_push(stack_T head, int data){
    stack_T temp = malloc(sizeof(struct stack));
    temp->data = data;
    temp->next = head;
    head = temp;
}

int func_stack_top(stack_T head){
    if(!head) return 0;
    return head->data;
}

void func_stack_pop(stack_T head){
    assert(head);
    stack_T temp = head;
    head = head->next;
    free(temp);
}