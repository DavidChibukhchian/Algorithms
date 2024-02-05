#ifndef _STACK_ARRAY_H
#define _STACK_ARRAY_H

//-------------------------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <malloc.h>
#include <string.h>

//-------------------------------------------------------------------------------------------------------------------
struct Stack
{
    void* buffer;
    size_t capacity;
    size_t size;
    size_t elem_size;
};

//-------------------------------------------------------------------------------------------------------------------

Stack* stack_ctr(size_t size, size_t elem_size);

int push(Stack* stack, void* elem);

int top(Stack* stack, void* elem);

int pop(Stack* stack);

Stack* stack_dtr(Stack* stack);

//-------------------------------------------------------------------------------------------------------------------

#endif // _STACK_ARRAY_H