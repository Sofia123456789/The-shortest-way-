//���������� ������������� �������
typedef struct
{
    //������
    void** data;
    //���������� ���������, ��� ������� �������� ������
    int capacity;
    //���������� ����������� ���������
    int count;
} List;

//������� ������
List* listNew ();
//�������� ������� � ����� �������
void listAdd(List* list, void* item);
//�������� ������� �� ���������� �������
void listSet(List* list, void* item, int index);
//�������� ������
void listClear(List* list);
//������� ������
void listFree(List* list);

