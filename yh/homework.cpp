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
	cout << "正在创建随机DNA字符序列……" << endl;
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
	cout << "字符串文件创建完毕!" << endl;
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
		left=(short)a[k*2+1].distance;//K结点的左孩子
	if ((k*2+1<=Range)&&((short)a[k*2+2].distance!=INFINITY))
		right=(short)a[k*2+2].distance;//K结点的右孩子
	if ((k*2+1<=Range)&&(a[k*2+1].distance<a[k].distance))
		lowest=k*2+1;
	else lowest=k;
	if ((k*2+2<=Range)&&(a[k*2+2].distance<a[lowest].distance))
		lowest=k*2+2;//找到值最小的结点
	if (lowest!=k){//交换根节点和最小结点的值
		char temp;//交换距离
		temp=a[k].distance;
		a[k].distance=a[lowest].distance;
		a[lowest].distance=temp;
		short int temp1;//交换p
		temp1=a[k].p;
		a[k].p=a[lowest].p;
		a[lowest].p=temp1;
		short int temp2;//交换q
		temp2=a[k].q;
		a[k].q=a[lowest].q;
		a[lowest].q=temp2;	
		this->MinHeapify(a,lowest);//递归
	}
}

void Heap::BuildMinHeap(Heap a[],int size){
	for (int i=(size-1)/2;i>=0;i--)
		this->MinHeapify(a,i);
}

void Heap::putin(Heap &heap,Heap heap1[],int dis,int a,short int p,short int q){
	heap.distance=dis;//用当前的海明距离覆盖掉堆数组最后一个数值。
	heap.p=p;
	heap.q=q;
	heap.BuildMinHeap(heap1,a);//重新建堆
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
			cout << "正在比较第" << i << "和第" << j << "条字符串" << endl;
			int up_left=0,up_right=0,down_left=0,down_right=0,pointer=0;
			char n;

			//生成一个文件，例如比较的是第一条和第二十条字符串，则生成文件1-20.txt
			char left1[2],right1[2];
			_itoa(i+1,left1,10);
			_itoa(j+1,right1,10);
		
			string filename="",left="",right="";
			//生成文件名
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
					
			for (int m=0;m<N-L+1;m++){//海明距离矩阵的第一行、第一列要单独计算
				
				//生成矩阵的第一行
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
				//生成矩阵的第一列
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
			//对矩阵的剩余部分按照表达式分别求解并建立一个堆
			for (up_left=1;up_left<N-L+1;up_left++){
				//fout << row[up_left] << " ";
				for (down_left=1;down_left<N-L+1;down_left++){
					//up_left变量表示第i条字符串的第一个位置，up_right表示最后一个位置
					//down_left变量表示第j条字符串的第一个位置，down_right表示最后一个位置
					char m,n,u,w;
					m=n=u=w='0';
					temp=distance[down_left];
					fin.seekg(i*N+up_left-1+i*2,ios::beg);
					fin >> m;//i字符串第一位前面的字母
					fin.seekg(j*N+down_left-1+j*2,ios::beg);
					fin >> n;//j字符串第一位前面的字母
					fin.seekg(i*N+up_left+L-1+i*2,ios::beg);
					fin >> u;//i字符串最后一位
					fin.seekg(j*N+down_left+L-1+j*2,ios::beg);
					fin >> w;//j字符串最后一位
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
			cout << "第" << i << "和第" << j << "条字符串比较完毕" << endl;
		}
	}
	fin.close();
	return 0;
}