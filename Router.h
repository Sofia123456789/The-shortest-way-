#include "Dic.h"

typedef struct
{
    //Список станций маршрута
    List* stations;
    //Список перегонов маршрута
    List* links;
    //Длина маршрута
    double length;
} Route;

//Рассчитать маршрут. Параметры: идентификаторы станций начала и конца маршрута, справочники станций и пергонов
Route* routeCalculate (int sid1, int sid2, List* stations, List* links);

//Удаление маршрута
void routeFree(Route** route);


