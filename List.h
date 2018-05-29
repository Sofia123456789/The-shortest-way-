//Реализация динамического массива
typedef struct
{
    //Данные
    void** data;
    //Количество элементов, под которые выделена память
    int capacity;
    //Колчиество добавленных элементов
    int count;
} List;

//Создать массив
List* listNew ();
//Добавить элемент в конец массива
void listAdd(List* list, void* item);
//Вставить элемент по указанному индексу
void listSet(List* list, void* item, int index);
//очистить массив
void listClear(List* list);
//удалить массив
void listFree(List* list);

