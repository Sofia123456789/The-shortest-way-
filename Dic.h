#include "List.h"

typedef struct {
    //Идентификатор станции
    int sid;
    //Название станции
    char* name;
    //Список перегонов, начинающихся на станции
    List* srtLids;
    //Список перегонов, заканчивающихся на станции
    List* endLids;
} Station;


typedef struct
{
    //Идентификатор перегона
    int lid;
    //Идентификатор станции начала перегона
    int sid1;
    //Идентификатор станции конца перегона
    int sid2;
    //Длина перегона
    double len;
} Link;

//Загрузка справочников
void loadDictionary(List** links, List** stations);
