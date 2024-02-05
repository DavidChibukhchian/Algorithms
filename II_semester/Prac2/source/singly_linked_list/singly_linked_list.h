#ifndef _LIST_H
#define _LIST_H

//-------------------------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <malloc.h>

//-------------------------------------------------------------------------------------------------------------------

typedef int Data;

//-------------------------------------------------------------------------------------------------------------------

enum Errors
{
    Done_Successfully     = 0,
    Failed_To_Create_Node = 1,
    List_Pointer_Is_Null  = 2,
    List_Is_Empty         = 3,
    Incorrect_Position    = 4
};

//-------------------------------------------------------------------------------------------------------------------

struct Node
{
    Data data;
    Node* next;
};

struct List
{
    size_t size;
    Node* head;
    Node* tail;
};

//-------------------------------------------------------------------------------------------------------------------

List* list_ctor(void);

int insert_front(List* list, Data data);

int insert_back(List* list, Data data);

int insert(List* list, size_t position, Data data);

int erase_front(List* list);

int erase_back(List* list);

int erase(List* list, size_t position);

int assign(List* list, size_t position, Data new_data);

bool search(List* list, Data key);

int list_dump(List* list);

int list_dtor(List* list);

//-------------------------------------------------------------------------------------------------------------------

#define CHECK_LIST_POINTER                                                                                          \
                                                                                                                    \
    if (list == nullptr)                                                                                            \
        return List_Pointer_Is_Null                                                                                 \

//-------------------------------------------------------------------------------------------------------------------

#endif // _LIST_H