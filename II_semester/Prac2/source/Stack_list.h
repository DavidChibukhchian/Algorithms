#ifndef _STACK_LIST_H
#define _STACK_LIST_H

//-------------------------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <malloc.h>
#include <string.h>

//-------------------------------------------------------------------------------------------------------------------

struct Stack
{
    struct Node* top;
    size_t size;
    size_t elem_size;
};

struct Node
{
    void* value;
    struct Node* next;
};

//-------------------------------------------------------------------------------------------------------------------

Stack* stack_ctr(size_t elem_size);

int push(Stack* stack, void* elem);

int top(Stack* stack, void* elem);

int pop(Stack* stack);

Stack* stack_dtr(Stack* stack);

//-------------------------------------------------------------------------------------------------------------------

#endif // _STACK_LIST_H