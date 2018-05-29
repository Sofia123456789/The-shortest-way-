#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <ctype.h>
#include "Router.h"

//������ ������� ������������
char readCommand()
{
    char buf[100];
    fgets(buf, 100, stdin);

    char result = tolower(buf[0]);
    return result;
}

//����� �������
Station* selectStation(List* stations)
{
    Station** data = (Station**)stations->data;
    for (int i = 0; i < stations->count; i++)
    {
        if (data[i] == NULL) continue;

        printf("%d. %s\n",  i, data[i]->name);
    }

    if (stations->count > 0)
    {
        puts("������� ����� �������:");
        int s;
        if (scanf("%d", &s) > 0 && s >= 0 && s < stations->count)
        {
            return (Station*)stations->data[s];
        }
    }

    return NULL;
}


int main()
{
    setlocale(LC_CTYPE, "ru");
    
    List* links;
    List* stations;
    puts("�������� ������������...");
    loadDictionary(&links, &stations);
    puts("������");

    int exitFlag = 1;
    Station* s1 = NULL;
    Station* s2 = NULL;
    Route* route = NULL;
    while (exitFlag)
    {
        puts("��������� �������:");
        puts("������ ������� ������  : s");
        puts("������ ������� �����   : e");

        if (route == NULL)
        {
            puts("��������� �������      : r");
        }
        else
        {
            puts("���������� �� �������� : i");
        }

        puts("�����                  : q");

        puts("\n������� �������:");

        printf("%s - %s\n", s1 != NULL ? s1->name : "?", s2 != NULL ? s2->name : "?");

        puts("\n��������� �������:");
        if (route == NULL)
        {
            puts("<���>\n");
        }
        else
        {
            printf("�����: %f; �������:%d\n\n", route->length, route->stations->count);
        }



        switch (readCommand())
        {
            case 's':
            {
                s1 = selectStation(stations);
                routeFree(&route);
                break;
            }

            case 'e':
            {
                s2 = selectStation(stations);
                routeFree(&route);
                break;
            }

            case 'r':
            {
                if (s1 != NULL && s2 != NULL)
                {
                    route = routeCalculate(s1->sid, s2->sid, stations, links);
                }
                break;
            }
			
            case 'i': 
            {
                if (route != NULL) 
                {
                    for (int l = 0; l < route->stations->count; l++)
                    {
                        Station * s = (Station*)route->stations->data[l];
                        printf("%d. %s\n", l + 1, s->name);
                    }
                    puts("\n..������� <enter> ��� �����������...");
                    readCommand();
                }
                break;
            }

            case 'q':
            {
                exitFlag = 0;
                break;
            }
        }
        system("cls");
    }

   
    return 0;
}