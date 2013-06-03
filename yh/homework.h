#include <iostream>
#include <fstream>
#include <time.h>
#include <string.h>
using namespace std;

class Hamming{
public:
	void CreateFile();
	int Distance(string str1,string str2);
};

class Heap{
public:
	short int p;
	short int q;
	char distance;
public:
	void MinHeapify(Heap a[],int i);
	void BuildMinHeap(Heap a[],int size);
	void Heap::putin(Heap &heap,Heap heap1[],int dis,int a,short int p,short int q);
};


