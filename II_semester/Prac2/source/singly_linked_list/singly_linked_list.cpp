#include "singly_linked_list.h"

//-------------------------------------------------------------------------------------------------------------------

static Node* create_node(Data data)
{
    Node* new_node = (Node*)calloc (1, sizeof(Node));
    if (new_node == nullptr)
        return nullptr;

    new_node->data = data;

    return new_node;
}

//-------------------------------------------------------------------------------------------------------------------

List* list_ctor(void)
{
    List* list = (List*)calloc (1, sizeof(List));
    if (list == nullptr)
        return nullptr;

    list->size = 0;
    list->head = nullptr;
    list->tail = nullptr;

    return list;
}

//-------------------------------------------------------------------------------------------------------------------

int insert_front(List* list, Data data)
{
    CHECK_LIST_POINTER;

    Node* new_node = create_node(data);
    if (new_node == nullptr)
        return Failed_To_Create_Node;

    if (list->size == 0)
    {
        list->head = new_node;
        list->tail = new_node;

        new_node->next = nullptr;
        list->size++;

        return Done_Successfully;
    }

    list->size++;
    new_node->next = list->head;
    list->head = new_node;

    return Done_Successfully;
}

//-------------------------------------------------------------------------------------------------------------------

int insert_back(List* list, Data data)
{
    CHECK_LIST_POINTER;

    if (list->size == 0)
        return insert_front(list, data);

    Node* new_node = create_node(data);
    if (new_node == nullptr)
        return Failed_To_Create_Node;

    list->size++;

    if (list->tail == nullptr)
        return Done_Successfully;

    new_node->next = nullptr;
    list->tail->next = new_node;
    list->tail = new_node;

    return Done_Successfully;
}

//-------------------------------------------------------------------------------------------------------------------

int insert(List* list, size_t position, Data data)
{
    CHECK_LIST_POINTER;

    if (position == 0)
        return insert_front(list, data);
    
    if (list->size == 0)
        return List_Is_Empty;

    if (position > list->size)
        return Incorrect_Position;

    Node* previous_node = nullptr;
    Node* current_node  = list->head;

    size_t counter = 0;
    while (current_node != nullptr)
    {
        previous_node = current_node;
        current_node  = current_node->next;
        counter++;

        if (counter == position)
            break;
    }

    Node* new_node = create_node(data);
    if (new_node == nullptr)
        return Failed_To_Create_Node;

    list->size++;

    previous_node->next = new_node;
    new_node->next = current_node;

    if (new_node->next == nullptr)
        list->tail = new_node;

    return Done_Successfully;
}

//-------------------------------------------------------------------------------------------------------------------

int erase_front(List* list)
{
    CHECK_LIST_POINTER;

    if (list->size == 0)
        return List_Is_Empty;

    if (list->size == 1)
    {
        free(list->head);
        list->head = nullptr;
        list->tail = nullptr;
        list->size--;

        return Done_Successfully;
    }

    Node* new_head = list->head->next;
    free(list->head);
    list->head = new_head;
    list->size--;

    return Done_Successfully;
}

//-------------------------------------------------------------------------------------------------------------------

int erase_back(List* list)
{
    CHECK_LIST_POINTER;

    if (list->size <= 1)
        return erase_front(list);

    Node* previous_node = nullptr;
    Node* current_node  = list->head;
    while (current_node->next != nullptr)
    {
        previous_node = current_node;
        current_node  = current_node->next;
    }

    free(list->tail);

    list->tail = previous_node;
    list->tail->next = nullptr;
    list->size--;

    return Done_Successfully;
}

//-------------------------------------------------------------------------------------------------------------------

int erase(List* list, size_t position)
{
    CHECK_LIST_POINTER;

    if (list->size == 0)
        return List_Is_Empty;

    if (position == 0)
        return erase_front(list);

    if (position + 1 > list->size)
        return Incorrect_Position;

    Node* previous_node = nullptr;
    Node* current_node = list->head;

    size_t counter = 0;
    while (current_node != nullptr)
    {
        previous_node = current_node;
        current_node = current_node->next;
        counter++;

        if (counter == position)
            break;
    }

    previous_node->next = current_node->next;

    if (current_node->next == nullptr)
        list->tail = previous_node;

    free(current_node);

    list->size--;

    return Done_Successfully;
}

//-------------------------------------------------------------------------------------------------------------------

int assign(List* list, size_t position, Data new_data)
{
    CHECK_LIST_POINTER;

    if (list->size == 0)
        return List_Is_Empty;

    if (position == 0)
    {
        list->head->data = new_data;

        return 0;
    }

    if (position + 1 > list->size)
        return Incorrect_Position;

    Node* previous_node = nullptr;
    Node* current_node  = list->head;

    size_t counter = 0;
    while (current_node != nullptr)
    {
        previous_node = current_node;
        current_node  = current_node->next;
        counter++;

        if (counter == position)
            break;
    }

    current_node->data = new_data;

    return Done_Successfully;
}

//-------------------------------------------------------------------------------------------------------------------

bool search(List* list, Data key)
{
    if ((list == nullptr) || (list->size == 0))
        return false;

    Node* current_node = list->head;

    while (current_node != nullptr)
    {
        if (current_node->data == key)
            return true;

        current_node = current_node->next;
    }

    return false;
}

//-------------------------------------------------------------------------------------------------------------------

int list_dump(List* list)
{
    CHECK_LIST_POINTER;

    if (list->size == 0)
        return List_Is_Empty;

    Node* current_node = list->head;
    while (current_node != nullptr)
    {
        printf("%d ", current_node->data);
        current_node = current_node->next;
    }

    return Done_Successfully;
}

//-------------------------------------------------------------------------------------------------------------------

int list_dtor(List* list)
{
    CHECK_LIST_POINTER;

    if (list->size == 0)
    {
        free(list);
        return Done_Successfully;
    }

    Node* current_node = list->head;
    Node* next_node    = list->head->next;

    free(list->head);

    while (next_node != nullptr)
    {
        current_node = next_node;
        next_node = next_node->next;

        free(current_node);
    }

    free(list);

    return Done_Successfully;
}

//-------------------------------------------------------------------------------------------------------------------