#include "Stack_list.h"

//-------------------------------------------------------------------------------------------------------------------

Stack* stack_ctr(size_t elem_size)
{
    Stack* stack = (Stack*)calloc (1, sizeof(Stack));
    if (stack == nullptr)
        return nullptr;

    stack->top       = nullptr;
    stack->size      = 0;
    stack->elem_size = elem_size;

    return stack;
}

//-------------------------------------------------------------------------------------------------------------------

int push(Stack* stack, void* elem)
{
    if ((stack == nullptr) || (elem == nullptr))
        return 0;
    
    Node* new_node = (Node*)calloc (1, sizeof(Node));
    if (new_node == nullptr)
        return 0;

    new_node->value = (void*)calloc (1, stack->elem_size);

    new_node->next = stack->top;
    stack->top = new_node;
    stack->size++;

    memcpy(new_node->value, elem, stack->elem_size);

    return 1;
}

//-------------------------------------------------------------------------------------------------------------------

int top(Stack* stack, void* elem)
{
    if ((stack == nullptr) || (elem == nullptr) || (stack->top == nullptr))
        return 0;

    memcpy(elem, stack->top->value, stack->elem_size);
    
    return 1;
}

//-------------------------------------------------------------------------------------------------------------------

int pop(Stack* stack)
{
    if ((stack == nullptr) || (stack->top == nullptr))
        return 0;

    Node* old_top = stack->top;
    stack->top = stack->top->next;

    free(old_top->value);
    free(old_top);

    stack->size--;

    return 1;
}

//-------------------------------------------------------------------------------------------------------------------

Stack* stack_dtr(Stack* stack)
{
    Node* old_top = nullptr;

    while(stack->top != nullptr)
    {
        old_top = stack->top;
        stack->top = stack->top->next;

        free(old_top->value);
        free(old_top);
    }

    stack->size      = 0;
    stack->elem_size = 0;


    return nullptr;
}

//-------------------------------------------------------------------------------------------------------------------