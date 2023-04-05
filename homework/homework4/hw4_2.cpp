/*作业题目 2：利用败者树实现锦标赛排序（树形选择排序）----简单选择排序的改进，浪费空间较多，-----再次改进为堆排序 
败者树实际上是一棵完全二叉树，可以看作是胜者树的一种变体。败者树
简化了重构，败者树的重构只是与该结点的父结点的记录有关，而胜者树的重构
还与该结点的兄弟结点有关。败者树作为一种重要的数据结构，用于树形选择排
序和外部排序。本作业要求设计败者树的存储结构，并实现树形选择排序算法。
作业要求：
1．设计败者树的存储结构；
2．利用败者树实现锦标赛排序，主要包括：（1）败者树的初始化算法；（2）
败者树的构建算法；（3）败者树的重构算法；（4）标赛排序算法。
3．测试数据以文件形式保存，数据规模 n 可以是任何整数，即对 n 不是 2 的整
数次幂的情况也可以处理，且尽量地节约辅助存储空间开销。*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//#define N 20
#define MAX 10000 //用以表示无穷大 

void create_failtree(int *num,int *failtree,int n);//构建败者树
int renew_failtree(int *failtree,int n);//败者树重构 

int main(){
	int i=0,k=0,c=0,j=0,n=1,N=0,a=0;
	//int temp;
	char list[500],s[10];
	FILE *fp;
	fp=fopen("D:\\DevC++\\homework4\\4_2.txt","r");
	fgets(list,490,fp);
	fclose(fp);
	while(list[i]!='\0'){
		while(list[i]!=' ' && list[i]!='\0')
			i++;
		N++;
		if(list[i]!='\0')
			i++;
	}
	while(n<N)
		n=n*2;
	int num[n];
	while(list[j]!='\0'){
		while(list[j]!=' ' && list[j]!='\0'){
			s[k]=list[j];
			k++;
			j++;
		}
		s[k]='\0';
		num[c]=atoi(s);
		k=0;
		c++;
		if(list[j]!='\0')
			j++;
	}
	int failtree[2*n];//给根节点增加一个父节点 
	/*for(i=0;i<N;i++)
		num[i]=2*i+1;
	for(i=0;i<N;i++){
		srand((unsigned)time(NULL));
		a=rand()%(N-i)+i;
		temp=num[a];
		num[a]=num[i];
		num[i]=temp;
	}*/
	for(i=N;i<n;i++)
		num[i]=MAX;
	printf("原序列为：");
	for(i=0;i<N;i++)
		printf("%d ",num[i]);
	
	create_failtree(num,failtree,n);
	printf("\n\n利用败者树实现锦标赛排序：");
	printf("\n排序后为：");
	while(a!=MAX){
		a=renew_failtree(failtree,n);
		if(a!=MAX)
			printf("%d ",a);
	}
	return 0;
}

void create_failtree(int *num,int *failtree,int n){//构建败者树，先建立胜者树，在此基础上改为败者树 
	int i,j,k=n;
	for(i=n;i<2*n;i++)
		failtree[i]=num[i-n];
	while(k!=0){
		for(i=k;i<2*k;i=i+2){
			if(failtree[i]<=failtree[i+1])
				failtree[i/2]=failtree[i];//胜者树 
			else
				failtree[i/2]=failtree[i+1];
		}
		k=k/2;//每层的首结点下标 
	}
	for(i=1;i<n;i++){//由上到下修改所有非叶结点,形成败者树
		if(failtree[2*i]==failtree[i])
			failtree[i]=failtree[2*i+1];
		else
			failtree[i]=failtree[2*i];
	}
}

int renew_failtree(int *failtree,int n){//败者树重构 
	int i,min,a;
	for(i=n;;i++)
		if(failtree[i]==failtree[0])
			break;
	failtree[i]=MAX;
	min=failtree[i];
	while(i!=0){
		if(min>failtree[i/2]){//只与父结点比较 
			a=failtree[i/2];
			failtree[i/2]=min;
			min=a;
		}
		i=i/2;
	}
	return min;
}

