#include <iostream>
#include <fstream>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include "homework.h"
using namespace std;
#define T 20
#define L 15
#define N 500
#define Range (N-L+1)*(N-L+1)/5
#define INFINITY 20

void Hamming::CreateFile(){
	cout << "���ڴ������DNA�ַ����С���" << endl;
	srand((unsigned)time(NULL));
	ofstream fout;
	fout.open("data.txt");
	for (int i=0;i<T;i++){
		for (int j=0;j<N;j++){
			int a=rand()%4;
			if (a==0)
				fout << "A" ;
			else if (a==1)
				fout << "C" ;
			else if (a==2)
				fout << "G" ;
			else if (a==3)
				fout << "T" ;
		}
		fout << endl;
	}
	fout.close();
	cout << "�ַ����ļ��������!" << endl;
}

int Hamming::Distance(string str1,string str2){
	int dis=0;
	for (int i=0;i<L;i++){
		if (str1[i]!=str2[i])
			dis++;
	}
	return dis;
}

void Heap::MinHeapify(Heap a[],int k){
	short left=INFINITY,right=INFINITY;
	int lowest=0;
	if ((k*2+1<=Range)&&((short)a[k*2+1].distance!=INFINITY))
		left=(short)a[k*2+1].distance;//K��������
	if ((k*2+1<=Range)&&((short)a[k*2+2].distance!=INFINITY))
		right=(short)a[k*2+2].distance;//K�����Һ���
	if ((k*2+1<=Range)&&(a[k*2+1].distance<a[k].distance))
		lowest=k*2+1;
	else lowest=k;
	if ((k*2+2<=Range)&&(a[k*2+2].distance<a[lowest].distance))
		lowest=k*2+2;//�ҵ�ֵ��С�Ľ��
	if (lowest!=k){//�������ڵ����С����ֵ
		char temp;//��������
		temp=a[k].distance;
		a[k].distance=a[lowest].distance;
		a[lowest].distance=temp;
		short int temp1;//����p
		temp1=a[k].p;
		a[k].p=a[lowest].p;
		a[lowest].p=temp1;
		short int temp2;//����q
		temp2=a[k].q;
		a[k].q=a[lowest].q;
		a[lowest].q=temp2;	
		this->MinHeapify(a,lowest);//�ݹ�
	}
}

void Heap::BuildMinHeap(Heap a[],int size){
	for (int i=(size-1)/2;i>=0;i--)
		this->MinHeapify(a,i);
}

void Heap::putin(Heap &heap,Heap heap1[],int dis,int a,short int p,short int q){
	heap.distance=dis;//�õ�ǰ�ĺ������븲�ǵ����������һ����ֵ��
	heap.p=p;
	heap.q=q;
	heap.BuildMinHeap(heap1,a);//���½���
}

int main(){
	Hamming h;
	Heap heap[Range];
	for (int i=0;i<Range;i++){
		heap[i].distance=(char)INFINITY;
		heap[i].p=-1;
		heap[i].q=-1;
	}
	h.CreateFile();
	ofstream fout;
	ifstream fin;
	fin.open("data.txt");
	string str1="",str2="";
	int row[N-L+1];
	int distance[N-L+1];
	for (i=0;i<T;i++){
		for (int j=i+1;j<T;j++){
			cout << "���ڱȽϵ�" << i << "�͵�" << j << "���ַ���" << endl;
			int up_left=0,up_right=0,down_left=0,down_right=0,pointer=0;
			char n;

			//����һ���ļ�������Ƚϵ��ǵ�һ���͵ڶ�ʮ���ַ������������ļ�1-20.txt
			char left1[2],right1[2];
			_itoa(i+1,left1,10);
			_itoa(j+1,right1,10);
		
			string filename="",left="",right="";
			//�����ļ���
			int p=0;
			while (left1[p]!='\0'){
				left+=left1[p];
				p++;
			}
			p=0;
			while (right1[p]!='\0'){
				right+=right1[p];
				p++;
			}
			string dian("-");
			string extd(".txt");
			filename+=left;			
			filename+=dian;
			filename+=right;
			filename+=extd;

			fout.open(filename.c_str());
					
			for (int m=0;m<N-L+1;m++){//�����������ĵ�һ�С���һ��Ҫ��������
				
				//���ɾ���ĵ�һ��
				fin.seekg(i*N+i*2,ios::beg);
				for (int k=0;k<L;k++){
					fin >> n;
					str1+=n;
				}
				fin.seekg(j*N+m+j*2,ios::beg);
				
				for (k=0;k<L;k++){
					fin >> n;
					str2+=n;
				}
				distance[m]=h.Distance(str1,str2);					
				str1="";
				str2="";
				if (distance[m]<=10){
					heap[pointer].putin(heap[pointer],heap,distance[m],pointer,0,(short)m);
					if (pointer<Range) pointer++;
				}
				//���ɾ���ĵ�һ��
				fin.seekg(i*N+m+i*2,ios::beg);
				for (k=0;k<L;k++){
					fin >> n;
					str1+=n;
				}
				fin.seekg(j*N+j*2,ios::beg);
				for (k=0;k<L;k++){
					fin >> n;
					str2+=n;
				}
				row[m]=h.Distance(str1,str2);
				if ((m!=0)&&(row[m]<=10)){
					heap[pointer].putin(heap[pointer],heap,row[m],pointer,(short)m,0);
					if (pointer<Range) pointer++;
				}
				str1="";
				str2="";
				//fout << distance[m] << " ";
			}
			fout << endl;
			int temp,temp2;
			//�Ծ����ʣ�ಿ�ְ��ձ��ʽ�ֱ���Ⲣ����һ����
			for (up_left=1;up_left<N-L+1;up_left++){
				//fout << row[up_left] << " ";
				for (down_left=1;down_left<N-L+1;down_left++){
					//up_left������ʾ��i���ַ����ĵ�һ��λ�ã�up_right��ʾ���һ��λ��
					//down_left������ʾ��j���ַ����ĵ�һ��λ�ã�down_right��ʾ���һ��λ��
					char m,n,u,w;
					m=n=u=w='0';
					temp=distance[down_left];
					fin.seekg(i*N+up_left-1+i*2,ios::beg);
					fin >> m;//i�ַ�����һλǰ�����ĸ
					fin.seekg(j*N+down_left-1+j*2,ios::beg);
					fin >> n;//j�ַ�����һλǰ�����ĸ
					fin.seekg(i*N+up_left+L-1+i*2,ios::beg);
					fin >> u;//i�ַ������һλ
					fin.seekg(j*N+down_left+L-1+j*2,ios::beg);
					fin >> w;//j�ַ������һλ
					if (down_left==1){
						if (((m==n)&&(u==w))||((m!=n)&&(u!=w)))
							distance[down_left]=row[up_left-1];
						else if ((m!=n)&&(u==w))
							distance[down_left]=row[up_left-1]-1;
						else if ((m==n)&&(u!=w))
							distance[down_left]=row[up_left-1]+1;						
						//fout << distance[down_left] ;
						//fout << " ";
					}
					else {
						if (((m==n)&&(u==w))||((m!=n)&&(u!=w)))
							distance[down_left]=temp2;
						else if ((m!=n)&&(u==w))
							distance[down_left]=temp2-1;
						else if ((m==n)&&(u!=w))
							distance[down_left]=temp2+1;
						//fout << distance[down_left] ;
						//fout << endl;
						//fout << down_left ;
						//fout << endl;
					}
					if (distance[down_left]<=10){
						heap[pointer].putin(heap[pointer],heap,distance[down_left],pointer,(short)up_left,(short)down_left);
						if (pointer<Range) pointer++;
					}
					temp2=temp;
				}
				//fout << endl;
			}
			for (int a=0;a<Range;a++)
				fout << (short)heap[a].distance << " ";
			fout << endl;
			for (a=0;a<Range;a++)
				fout << heap[a].p << " ";
			fout << endl;
			for (a=0;a<Range;a++)
				fout << heap[a].q << " ";
			fout << endl;
			fout.close();
			cout << "��" << i << "�͵�" << j << "���ַ����Ƚ����" << endl;
		}
	}
	fin.close();
	return 0;
}