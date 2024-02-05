#include "Stack_array.h"

//-------------------------------------------------------------------------------------------------------------------

static const size_t MULTIPLIER = 2;

//-------------------------------------------------------------------------------------------------------------------

static void* recalloc(void* mem_pointer, size_t new_size)
{
    if (new_size == 0)
    {
        free(mem_pointer);
        return nullptr;
    }

    void* new_pointer = nullptr;

    if (mem_pointer == nullptr)
    {
        new_pointer = (void*)calloc (new_size, sizeof(char));
        if (new_pointer == nullptr)
            return nullptr;

        return new_pointer;
    }

    size_t old_size = _msize(mem_pointer);

    new_pointer = (void*)realloc (mem_pointer, new_size);
    if (new_pointer == nullptr)
        return nullptr;

    if (new_size > old_size)
    {
        for (size_t i = old_size; i < new_size; i++)
            ((char*)new_pointer)[i] = 0;
    }

    return new_pointer;
}

//-------------------------------------------------------------------------------------------------------------------

static int stack_expand(Stack* stack)
{
    stack->buffer = recalloc(stack->buffer, stack->capacity*MULTIPLIER);
    if (stack->buffer == nullptr)
        return 0;

    stack->capacity *= MULTIPLIER;

    return 1;
}

//-------------------------------------------------------------------------------------------------------------------

Stack* stack_ctr(size_t size, size_t elem_size)
{
    Stack* stack = (Stack*)calloc (1, sizeof(Stack));
    if (stack == nullptr)
    {
        return nullptr;
    }

    stack->buffer = (void*)calloc (size, sizeof(elem_size));
    if (stack->buffer == nullptr)
    {
        free(stack);
        return nullptr;
    }

    stack->capacity  = size;
    stack->size      = 0;
    stack->elem_size = elem_size;

    return stack;
}

//-------------------------------------------------------------------------------------------------------------------

int push(Stack* stack, void* elem)
{
    if ((stack == nullptr) || (stack->buffer == nullptr) || (elem == nullptr))
        return 0;

    if (stack->size == stack->capacity)
    {
        if (!stack_expand(stack))
        {
            free(stack->buffer);
            return 0;
        }
    }

    char* top = (char*)(stack->buffer) + (stack->size)*(stack->elem_size);
    memcpy(top, elem, stack->elem_size);
    stack->size++;

    return 1;
}

//-------------------------------------------------------------------------------------------------------------------

int top(Stack* stack, void* elem)
{
    if ((stack == nullptr) || (stack->buffer == nullptr) || (elem == nullptr))
        return 0;

    if (stack->size == 0)
        return 0;
    
    char* top = (char*)(stack->buffer) + (stack->size - 1)*(stack->elem_size);
    memcpy(elem, top, stack->elem_size);

    return 1;
}

//-------------------------------------------------------------------------------------------------------------------

int pop(Stack* stack)
{
    if ((stack == nullptr) || (stack->buffer == nullptr))
        return 0;

    if (stack->size == 0)
        return 0;

    char* top = (char*)(stack->buffer) + (stack->size - 1)*(stack->elem_size);
    memset(top, 0, stack->elem_size);
    stack->size--;

    return 1;
}

//-------------------------------------------------------------------------------------------------------------------

Stack* stack_dtr(Stack* stack)
{
    if (stack == nullptr)
        return nullptr;
    
    free(stack->buffer);

    stack->capacity  = 0;
    stack->size      = 0;
    stack->elem_size = 0;

    free(stack);

    return nullptr;
}

//-------------------------------------------------------------------------------------------------------------------