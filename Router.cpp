#include <stdlib.h>
#include <string.h>
#include "Router.h"


void _stepBack(Station* current, Link* link, int nextSid, int targetSid, double* map, Station** stationsArray, List* nextStations, int* step, int* found)
{
    if (current->sid != targetSid && (map[nextSid] == -1 || map[nextSid] > link->len + map[current->sid]))
    {
        *step = true;
        map[nextSid] = link->len + map[current->sid];
        listAdd(nextStations, stationsArray[nextSid]);

        if (nextSid == targetSid)
        {
            *found = true;
        }
    }
}

int _stepForward(Station* current, Link* link, int nextSid, int targetSid, double* map, Station** stationsArray, Station** nextStation, Link** nextLink, double* minval, int* step, int* found)
{
    if (map[nextSid] != -1 && map[nextSid] + link->len <= *minval)
    {

        if (nextSid == targetSid)
        {
            *found = true;
        }
        else
        {
            if (stationsArray[nextSid]->srtLids->count + stationsArray[nextSid]->endLids->count < 2) return 0;
        }

        *minval = map[nextSid];
        *nextLink = link;
        *nextStation = stationsArray[nextSid];
        *step = true;

        map[current->sid]++;
    }

    return 1;
}

Route* _routeNew(void* firstStation)
{
    Route* result = (Route*)calloc(1, sizeof(Route));
    result->links = listNew();
    result->stations = listNew();
    listAdd(result->stations, firstStation);
    return result;
}

Route* routeCalculate(int sid1, int sid2, List* stations, List* links)
{
    Station** stationsArray = (Station**)stations->data;
    double* map = (double*)calloc(stations->count, sizeof(double));

    for (int i = 0; i < stations->count; i++) 
    {
        map[i] = -1;
    }

    int found = false;
    int step = false;
    List* currentStations = listNew();
    List* nextStations = listNew();
    listAdd(currentStations, stationsArray[sid2]);
    map[sid2] = 0;


    while (true)
    {
        listClear(nextStations);
        step = false;
        for (int j = 0; j < currentStations->count; j++)
        {
            Station* current = (Station*)currentStations->data[j];

            for (int l = 0; l < current->srtLids->count; l++)
            {
                Link* link = (Link*)current->srtLids->data[l];
                _stepBack(current, link, link->sid2, sid1, map, stationsArray, nextStations, &step, &found);
            }

            for (int l = 0; l < current->endLids->count; l++)
            {
                Link* link = (Link*)current->endLids->data[l];
                _stepBack(current, link, link->sid1, sid1, map, stationsArray, nextStations, &step, &found);
            }
        }
        if (!found && !step) break;

        if (found && nextStations->count == 0) break;
        listClear(currentStations);
        for (int l = 0; l < nextStations->count; l++)
        {
            listAdd(currentStations, nextStations->data[l]);
        }
    }

    listFree(currentStations);
    listFree(nextStations);

    Route* result = NULL;

    if (found)
    {
        found = false;
        Link* nextLink = NULL;
        Station* nextStation = stationsArray[sid1];
        double minval = map[sid1];

        while (!found)
        {
            Station* cursid = nextStation;
            step = false;

            for (int l = 0; l < cursid->srtLids->count; l++)
            {
                Link* link = (Link*)cursid->srtLids->data[l];
                _stepForward(cursid, link, link->sid2, sid2, map, stationsArray, &nextStation, &nextLink, &minval, &step, &found);
            }

            for (int l = 0; l < cursid->endLids->count; l++)
            {
                Link* link = (Link*)cursid->endLids->data[l];
                _stepForward(cursid, link, link->sid1, sid2, map, stationsArray, &nextStation, &nextLink, &minval, &step, &found);
            }

            if (!found && !step) return NULL;

            if (result == NULL)
            { 
                result = _routeNew(stationsArray[sid1]);
            }
            
            result->length += nextLink->len;
            listAdd(result->stations, nextStation);
            listAdd(result->links, nextLink);

            if (found) return result;
        }
    
    }

    routeFree(&result);
    free(map);

    return NULL;
}

void routeFree(Route** route)
{
    if (route != NULL && *route != NULL)
    {
        listFree((*route)->links);
        listFree((*route)->stations);
        free(*route);
        *route = NULL;
    }
}