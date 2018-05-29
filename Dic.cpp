
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Dic.h"

#define stationsFileName "stations.csv"
#define linksFileName "links.csv"


List* _loadLinks()
{
    char* pos;
    char* str;
    char buff[255];
    FILE* file = fopen(linksFileName, "r");

    fgets(buff, 255, file);

    List* result = listNew();

    while ((str = fgets(buff, 255, file)) != NULL)
    {
        if ((pos = strchr(str, '\n')) != NULL) *pos = '\0';

        Link* link = (Link*)malloc(sizeof(Link));

        str = strtok(str, ";");
        link->lid = strtol(str, NULL, 10);

        str = strtok(NULL, ";");
        link->sid1 = strtol(str, NULL, 10);

        str = strtok(NULL, ";");
        link->sid2 = strtol(str, NULL, 10);

        str = strtok(NULL, ";");
        link->len = strtod(str, NULL);

        listSet(result, link, link->lid);
    }

    fclose(file);
    return result;
}

List* _loadStations(List* links)
{
    char* pos;
    char* str;
    char buff[255];
    FILE* file = fopen(stationsFileName, "r");
    
    fgets(buff, 255, file);

    List* result = listNew();

    while ((str = fgets(buff, 255, file)) != NULL)
    {
        if ((pos = strchr(str, '\n')) != NULL) *pos = '\0';

        Station* station = (Station*)malloc(sizeof(Station));

        str = strtok(str, ";");
        station->sid = strtol(str, NULL, 10);
        station->name = strdup(strtok(NULL, ";"));
        station->srtLids = listNew();
        station->endLids = listNew();

        listSet(result, station, station->sid);
    }

    fclose(file);
    return result;
}

void loadDictionary(List** links, List** stations)
{
    *links = _loadLinks();
    *stations = _loadStations(*links);
    for (int i = 0; i < (*links)->count; i++) 
    {
        Link* l = (Link*)(*links)->data[i];
        if (l == NULL) continue;

        Station* s1 = (Station*)(*stations)->data[l->sid1];
        if (s1 != NULL) listAdd(s1->srtLids, l);

        Station* s2 = (Station*)(*stations)->data[l->sid2];
        if (s2 != NULL) listAdd(s2->endLids, l);
    }
}