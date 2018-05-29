
#include <stdlib.h>
#include <string.h>
#include "List.h"
#define initialCapacity 4;

//Выделение дополнительной памяти
void _listExtend (List* list, int by)
{
    int desired = list->count + by;
    int newCapacity = list->capacity * 2;
    if (newCapacity < desired) newCapacity = desired;    

    list->data = (void**)realloc(list->data, sizeof(void*) * newCapacity);
    memset(list->data + list->capacity, 0, (newCapacity - list->capacity) * sizeof(void*));
    list->capacity = newCapacity;
}

List* listNew()
{
    List* result = (List*)malloc(sizeof(List));

    result->capacity = initialCapacity;
    result->count = 0;
    result->data = (void**)calloc(result->capacity, sizeof(void*));
    return result;
}

void listSet(List* list, void* item, int index)
{
    if (index >= list->capacity)
    {
        _listExtend(list, list->capacity - index + 1);
    }

    list->data[index] = item;

    list->count = list->count > index ? list->count : index + 1;
}

void listAdd(List* list, void* item)
{
    if (list->count >= list->capacity)
    {
        _listExtend(list, 1);
    }

    list->data[list->count] = item;

    list->count ++;
}

void listClear (List* list)
{
    list->count = 0;
}

void listFree(List* list)
{
    if (list != NULL)
    {
        free(list->data);
        free(list);
    }
}