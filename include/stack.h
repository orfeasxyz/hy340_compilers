#ifndef _STACK_H_
#define _STACK_H_

typedef struct stack* stack_T;

int stack_top(stack_T);

void stack_push(stack_T, int);

void stack_pop(stack_T);

extern stack_T scopeOffsetStack;
extern stack_T functionScopeStack;

#endif // _STACK_H_
