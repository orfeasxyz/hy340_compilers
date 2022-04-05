#ifndef _FUNC_STACK_H_
#define _FUNC_STACK_H_

typedef struct func_stack* func_stack_T;

int func_stack_top();

void func_stack_push(int scope);

void func_stack_pop();

#endif // _FUNC_STACK_H_
