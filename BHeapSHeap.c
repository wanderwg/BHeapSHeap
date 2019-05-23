#include "BHeapSHeap.h"
#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include <stdlib.h>

void Swap(HPDatatype* pLeft, HPDatatype* pRight) {
	HPDatatype tmp = *pLeft;
	*pLeft = *pRight;
	*pRight = tmp;
}

void AdjustDown(HPDatatype* array, int size, int parent, PCOM Compare) {
	int child = parent * 2 + 1;//child标记了左孩子

	while (child < size) {
		//找双亲中较小的孩子
		if (child + 1 < size && Compare(array[child + 1],array[child])) {
			child = child + 1;
		}

		if (Compare(array[child],array[parent])) {
			Swap(&array[child], &array[parent]);
			parent = child;
			child = parent * 2 + 1;
		}
		else
			return;
	}
}

int Less(HPDatatype left, HPDatatype right) {
	return left < right;
}
int Greater(HPDatatype left, HPDatatype right) {
	return left > right;
}

void InitHeap(Heap* hp, HPDatatype* array, int size, PCOM compare) {
	assert(hp);
	hp->_array = (HPDatatype*)malloc(sizeof(HPDatatype)*size);
	if (hp->_array == NULL) {
		assert(0);
		return;
	}
	hp->_capacity = size;
	for (int i = 0; i < size; ++i)
		hp->_array[i] = array[i];
	hp->_size = size;
	hp->Compare = compare;

	//将该完全二叉树进行调整使其满足堆的性质

	//找完全二叉树中倒数第一个非叶子节点
	int root = ((size - 2) >> 1);
	for (; root >= 0; --root)
		AdjustDown(hp->_array, size, root,hp->Compare);
}

void InitEmptyHeap(Heap* hp, int capacity, PCOM compare) {
	assert(hp);
	hp->_array = (HPDatatype*)malloc(sizeof(HPDatatype)*capacity);
	if (hp->_array == NULL) {
		assert(0);
		return;
	}
	hp->Compare = compare;
	hp->_capacity = capacity;
	hp->_size = 0;
}

void AdjustUp(HPDatatype* array, int size, int child,PCOM Compare) {
	int parent = ((child - 1) >> 1);

	while (child) {
		if (Compare(array[child],array[parent])) {
			Swap(&array[child], &array[parent]);
			child = parent;
			parent = ((child - 1) >> 1);
		}
		else
			return;
	}

}

void CheckCapacity(Heap* hp) {
	assert(hp);
	if (hp->_size == hp->_capacity) {
		int newCapacity = hp->_capacity * 2;
		HPDatatype* pTemp = (HPDatatype*)malloc(sizeof(HPDatatype)*newCapacity);
		if (pTemp == NULL) {
			assert(0);
			return;
		}
		for (int i = 0; i < hp->_size; ++i)
			pTemp[i] = hp->_array[i];
		free(hp->_array);
		hp->_array = pTemp;
		hp->_capacity = newCapacity;
	}
}

void InsertHeap(Heap* hp, HPDatatype data) {
	CheckCapacity(hp);
	hp->_array[hp->_size] = data;
	hp->_size++;
	AdjustUp(hp->_array, hp->_size, hp->_size - 1,hp->Compare);
}

void EraseHeap(Heap* hp) {
	if (HeapEmpty(hp))
		return;
	Swap(&hp->_array[0], &hp->_array[hp->_size - 1]);
	hp->_size--;
	AdjustDown(hp->_array, hp->_size, 0,hp->Compare);
}

int HeapSize(Heap* hp) {
	assert(hp);
	return hp->_size;
}

int HeapEmpty(Heap* hp) {
	assert(hp);
	return 0 == hp->_size;
}

HPDatatype HeapTop(Heap* hp) {
	assert(hp);
	return hp->_array[0];
}

void DestoryHeap(Heap* hp) {
	assert(hp);
	if (hp->_array) {
		free(hp->_array);
		hp->_capacity = 0;
		hp->_size = 0;
	}
}


int main() {
	Heap hp;
	int array[] = { 2,6,7,3,9,1,4,0,5,8 };
	InitHeap(&hp, array, sizeof(array) / sizeof(array[0]),Greater);
	printf("%d\n", HeapSize(&hp));
	printf("%d\n", HeapTop(&hp));

	EraseHeap(&hp);
	printf("%d\n", HeapSize(&hp));
	printf("%d\n", HeapTop(&hp));

	InsertHeap(&hp, 0);
	printf("%d\n", HeapSize(&hp));
	printf("%d\n", HeapTop(&hp));

	InsertHeap(&hp, 12);
	printf("%d\n", HeapSize(&hp));
	printf("%d\n", HeapTop(&hp));

	DestoryHeap(&hp);

}