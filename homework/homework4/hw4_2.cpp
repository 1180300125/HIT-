/*��ҵ��Ŀ 2�����ð�����ʵ�ֽ�������������ѡ������----��ѡ������ĸĽ����˷ѿռ�϶࣬-----�ٴθĽ�Ϊ������ 
������ʵ������һ����ȫ�����������Կ�����ʤ������һ�ֱ��塣������
�����ع������������ع�ֻ����ý��ĸ����ļ�¼�йأ���ʤ�������ع�
����ý����ֵܽ���йء���������Ϊһ����Ҫ�����ݽṹ����������ѡ����
����ⲿ���򡣱���ҵҪ����ư������Ĵ洢�ṹ����ʵ������ѡ�������㷨��
��ҵҪ��
1����ư������Ĵ洢�ṹ��
2�����ð�����ʵ�ֽ�����������Ҫ��������1���������ĳ�ʼ���㷨����2��
�������Ĺ����㷨����3�����������ع��㷨����4�����������㷨��
3�������������ļ���ʽ���棬���ݹ�ģ n �������κ����������� n ���� 2 ����
�����ݵ����Ҳ���Դ����Ҿ����ؽ�Լ�����洢�ռ俪����*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//#define N 20
#define MAX 10000 //���Ա�ʾ����� 

void create_failtree(int *num,int *failtree,int n);//����������
int renew_failtree(int *failtree,int n);//�������ع� 

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
	int failtree[2*n];//�����ڵ�����һ�����ڵ� 
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
	printf("ԭ����Ϊ��");
	for(i=0;i<N;i++)
		printf("%d ",num[i]);
	
	create_failtree(num,failtree,n);
	printf("\n\n���ð�����ʵ�ֽ���������");
	printf("\n�����Ϊ��");
	while(a!=MAX){
		a=renew_failtree(failtree,n);
		if(a!=MAX)
			printf("%d ",a);
	}
	return 0;
}

void create_failtree(int *num,int *failtree,int n){//�������������Ƚ���ʤ�������ڴ˻����ϸ�Ϊ������ 
	int i,j,k=n;
	for(i=n;i<2*n;i++)
		failtree[i]=num[i-n];
	while(k!=0){
		for(i=k;i<2*k;i=i+2){
			if(failtree[i]<=failtree[i+1])
				failtree[i/2]=failtree[i];//ʤ���� 
			else
				failtree[i/2]=failtree[i+1];
		}
		k=k/2;//ÿ����׽���±� 
	}
	for(i=1;i<n;i++){//���ϵ����޸����з�Ҷ���,�γɰ�����
		if(failtree[2*i]==failtree[i])
			failtree[i]=failtree[2*i+1];
		else
			failtree[i]=failtree[2*i];
	}
}

int renew_failtree(int *failtree,int n){//�������ع� 
	int i,min,a;
	for(i=n;;i++)
		if(failtree[i]==failtree[0])
			break;
	failtree[i]=MAX;
	min=failtree[i];
	while(i!=0){
		if(min>failtree[i/2]){//ֻ�븸���Ƚ� 
			a=failtree[i/2];
			failtree[i/2]=min;
			min=a;
		}
		i=i/2;
	}
	return min;
}

