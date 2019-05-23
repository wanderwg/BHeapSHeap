#pragma once
typedef int HPDatatype;
typedef int (*PCOM)(HPDatatype, HPDatatype);
int Less(HPDatatype left, HPDatatype right);
int Greater(HPDatatype left, HPDatatype right);

typedef struct Heap
{
	HPDatatype* _array;
	int _capacity;
	int _size;
	PCOM Compare;
}Heap;

//�������ʼ����
void InitHeap(Heap* hp, HPDatatype* array, int size,PCOM compare);

//��ʼ��һ���ն�
void InitEmptyHeap(Heap* hp, int capacity, PCOM compare);

//�ڶ��в���ֵΪdata��Ԫ��
void InsertHeap(Heap* hp, HPDatatype data);

//ɾ���Ѷ�Ԫ��
void EraseHeap(Heap* hp);

//��ȡ������ЧԪ�ظ���
int HeapSize(Heap* hp);

//�����Ƿ�Ϊ�ն�
int HeapEmpty(Heap* hp);

//��ȡ�Ѷ�Ԫ��
HPDatatype HeapTop(Heap* hp);

//���ٶ�
void DestoryHeap(Heap* hp);