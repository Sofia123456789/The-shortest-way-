#include "Dic.h"

typedef struct
{
    //������ ������� ��������
    List* stations;
    //������ ��������� ��������
    List* links;
    //����� ��������
    double length;
} Route;

//���������� �������. ���������: �������������� ������� ������ � ����� ��������, ����������� ������� � ��������
Route* routeCalculate (int sid1, int sid2, List* stations, List* links);

//�������� ��������
void routeFree(Route** route);


