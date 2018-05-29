#include "List.h"

typedef struct {
    //������������� �������
    int sid;
    //�������� �������
    char* name;
    //������ ���������, ������������ �� �������
    List* srtLids;
    //������ ���������, ��������������� �� �������
    List* endLids;
} Station;


typedef struct
{
    //������������� ��������
    int lid;
    //������������� ������� ������ ��������
    int sid1;
    //������������� ������� ����� ��������
    int sid2;
    //����� ��������
    double len;
} Link;

//�������� ������������
void loadDictionary(List** links, List** stations);
