/*1��ѡ�񲢽�����Ȩ��ͨͼ�Ĵ洢�ṹ��ʵ������Ȩ��ͨͼ�� Prim �㷨������
�����Ӹ��������С��������
2�����öѽṹ��ʵ�ֵ����ȼ����У��Ľ����Ż� Prim �㷨������ʱ�临�Ӷȣ�
ʵ�ָĽ����Ż��� Prim �㷨������ԭ�㷨����ʵ��Ƚϣ�
3�����ò��鼯��ʵ������Ȩ��ͨͼ�� Kruskal �㷨����������Ӹ��������
С��������
4����ѡ������Ʋ�ʵ��������С�������㷨�����÷����Ȧ�㷨��Sollin(Boruvka)
�㷨����
5�����ļ���ʽ����ͼ�Ķ���ͱߣ�����ʾ��Ӧ�Ľ����Ҫ�󶥵㲻���� 10 ����
�߲����� 13 ��������ͼ 
6��������ܽṹ���ź��������Ѻã�����ʹ�á�*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 10 //����ͼ������ 

typedef struct node{
	char point;
	int distance;
	struct node *next;
}Node;

typedef struct cell{//�������Ԫ�ص��� 
	int point;
	int distance;
}celltype;

typedef struct edge{//һ���� 
	int s;//��� 
	int t;//�յ� 
	int distance;//�ߵ�Ȩֵ 
}Edge;

int search(char *v,int n,char b);
void printMatrix(char *v,int c[][N]);
void read_Matrix(char *v,char edge[][N],int n,int m,int c[][N]);//�õ�����ͼ��Ȩ�ڽӾ��� 

void Prim(char *v,int c[][N]);

void Heap_Prim(char *v,int c[][N]);
void swap(celltype *a,celltype *b);
void create_V_UHeap(celltype *lowcost,int c[][N],int *closest);
void Renew_Heap(celltype *num,int first,int last,int c[][N],celltype w,int *closest);
void Insert_Heap(celltype *num,int first,int last,celltype w);//��(���ȶ���)����--��ӿ 
celltype Delete_Heap(celltype *num,int first,int last);//��(���ȶ���)ɾ��--���� 
void PushDown(celltype *num,int first,int last);//����ѣ��� A[1]���Ƶ�����λ�ã�������СԪ���Ƶ� A[1] 

void swap1(Edge *a,Edge *b);
int Find(int *father,int a);//���ذ���(������...���)(������) 
void Union(int *father,int a,int b);//���������Ϻϲ���һ������ 
void Kruskal(int m,int c[][N],char *v);//���ò��鼯 

void menu();

int main(){
	FILE *fp;
	char num[10],ch[5];
	int n,i,m,y,j;
	
	fp=fopen("D:\\DevC++\\homework3\\3_2.txt","r");
	fgets(num,9,fp);
	n=atoi(num);//���� 
	char v[n+1];//�㼯 
	for(i=0;i<n;i++)
		fscanf(fp,"%c",&v[i]);
	v[n]='\0';
	fgets(ch,3,fp);//��ȡ������� 
	fgets(num,9,fp);
	m=atoi(num);//���� 
	char edge[m][N];//�߼�(�����з�) 
	for(i=0;i<m;i++)
		fgets(edge[i],8,fp);
	fclose(fp);
	
	while(1){
		int c[N][N];//��10000�������� 
		for(i=0;i<N;i++)
			for(j=0;j<N;j++)
				c[i][j]=1000;//1000Ϊ�����κ�Ȩֵ����С�����޴�10000�ĳ��� 
		
		read_Matrix(v,edge,n,m,c);
		//printMatrix(v,c);//ͼ���ڽӾ���
		menu();
		printf("\t���������ѡ��");
		scanf("%d",&y);
		switch(y){
			case 1: Prim(v,c);
					break;
			case 2: Heap_Prim(v,c);
					break;
			case 3: Kruskal(m,c,v);
					break;
			case 4: printf("���˳�������");
					exit(0);
					break;
			default:printf("�Ƿ�ѡ�����������룡");
					break;
		}
	}
	return 0;
}

void menu(){
	printf("\n\t-----------------------------\n");
	printf("\t|           �˵�            |\n");
	printf("\t|1.Prim�㷨                 |\n");
	printf("\t|2.Heap�Ż���Prim�㷨       |\n");
	printf("\t|3.���鼯ʵ��Kruskal�㷨    |\n");
	printf("\t|4.�˳���                   |\n");
	printf("\t-----------------------------\n");
}

int search(char *v,int n,char b){
	int i;
	for(i=0;i<n;i++)
		if(b==v[i])
			return i;
}

void read_Matrix(char *v,char edge[][N],int n,int m,int c[][N]){//�ڽӾ��� 
	int k,i,j,t,l;
	char w[5];
	for(k=0;k<m;k++){
		i=search(v,n,edge[k][0]);
		j=search(v,n,edge[k][1]);
		for(t=3,l=0;v[t]!='\0';t++,l++)
			w[l]=edge[k][t];
		c[i][j]=atoi(w);
		c[j][i]=atoi(w);
	}
}

void Prim(char *v,int c[][N]){
	int lowcost[N];
	int closest[N];
	int min;
	int i,j,k;
	for(i=1;i<N;i++){//��ʼ�� V-U ,��1��ʼѭ����ζ�� 0��(A��)���뼯��U
		lowcost[i]=c[0][i];
		closest[i]=0;
	}
	for(i=1;i<N;i++){//N-1��ѭ�� 
		min=1000;
		for(j=1;j<N;j++)
			if(min>lowcost[j]){
				min=lowcost[j];
				k=j;
			}
		printf("\n���ߣ�%c%c",v[closest[k]],v[k]);
		lowcost[k]=10000;//���뼯��U 
		for(j=1;j<N;j++)
			if(c[k][j]<lowcost[j] && lowcost[j]!=10000){//���� 
				lowcost[j]=c[k][j];
				closest[j]=k;
			}
	}
}

void swap(celltype *a,celltype *b){
	int temp,ch;
	temp=(*a).distance;
	(*a).distance=(*b).distance;
	(*b).distance=temp;
	ch=(*a).point;
	(*a).point=(*b).point;
	(*b).point=ch;
}

void create_V_UHeap(celltype *lowcost,int c[][N],int *closest){//��ʼ������ V-U 
	int i;
	for(i=0;i<N-1;i++){
		lowcost[i].distance=c[0][i+1];
		lowcost[i].point=i+1;
		closest[i]=0;
	}
	for(i=3;i>=0;i--)
		PushDown(lowcost,i,N-2);//��ʼ����С��
}

void Insert_Heap(celltype *num,int first,int last,celltype w){//��ӿ ����ӿʱֻ�븸�ڵ�Ƚϼ��� 
	int i;
	i=last+1;
	num[i].distance=w.distance;
	num[i].point=w.point;
	while(i>0){
		if(i%2==0){//��������
			if(num[i].distance<num[(i-2)/2].distance){
				swap(&num[i],&num[(i-2)/2]);
				i=(i-2)/2;
			}
			else
				i=0;//����ѭ�� 
		}
		else{//�������� 
			if(num[i].distance<num[(i-1)/2].distance){
				swap(&num[i],&num[(i-1)/2]);
				i=(i-1)/2;
			}
			else
				i=0;//����ѭ�� 
		}
	}
} 

celltype Delete_Heap(celltype *num,int first,int last){
	celltype temp;
	temp.distance=num[first].distance;
	temp.point=num[first].point;
	swap(&num[first],&num[last]);
	PushDown(num,first,last-1);//���û��Ҳ��Ӱ�죬��Ϊ����Ҫ����distance����Renew�Ľ���ʱ����������ɶѽṹ ��������Ϊ��ɾ����������������ڣ����� 
	return temp;
}

void Renew_Heap(celltype *num,int first,int last,int c[][N],celltype w,int *closest){//���� 
	int i,k;
	k=w.point;
	for(i=first;i<=last;i++){
		if(c[k][num[i].point]<num[i].distance){
			num[i].distance=c[k][num[i].point];
			closest[num[i].point]=k;
		}
	}
	for(i=(last-1)/2;i>=0;i--)
		PushDown(num,i,last);//����������Ҫ��������ɶѣ���������Ҫ������******************** 
}

void PushDown(celltype *num,int first,int last){//����ѣ��� A[first]���Ƶ�����λ�ã�������С(��)Ԫ�ؽ����� A[first]-----�˴�ѡ��ʹ�����ѣ���ʹ������ֱ��Ϊ���� 
	int k;
	k=first;
	while(2*k+1<=last){//ÿ��ѭ��������һ�� 
		if(2*k+1==last){//ֻ�������� ,�����һ�� 
			if(num[k].distance>num[2*k+1].distance)
				swap(&num[k],&num[2*k+1]);
			k=last;//ʹѭ������ 
		}
		else if(num[k].distance>num[2*k+1].distance && num[2*k+1].distance<num[2*k+2].distance){//�������нϴ��һ������ --���� 
			swap(&num[k],&num[2*k+1]);
			k=2*k+1;
		}
		else if(num[k].distance>num[2*k+2].distance && num[2*k+1].distance>=num[2*k+2].distance){
			swap(&num[k],&num[2*k+2]);
			k=2*k+2;
		}
		else//������ 
			k=last;//ʹѭ������ 
	}
}

void Heap_Prim(char *v,int c[][N]){
	celltype lowcost[N],w;
	int closest[N],i;
	create_V_UHeap(lowcost,c,closest);
	for(i=0;i<N-1;i++){
		w=Delete_Heap(lowcost,0,N-2-i);//��V-U��ɾȥ���൱�ڼ��뵽���� U�� 
		printf("\n���ߣ�%c%c",v[closest[w.point]],v[w.point]);
		Renew_Heap(lowcost,0,N-3-i,c,w,closest);
	}
}

void swap1(Edge *a,Edge *b){
	int temp;
	temp=(*a).distance;
	(*a).distance=(*b).distance;
	(*b).distance=temp;
	temp=(*a).s;
	(*a).s=(*b).s;
	(*b).s=temp;
	temp=(*a).t;
	(*a).t=(*b).t;
	(*b).t=temp;
}

int Find(int *father,int a){//���ذ���(���ڵ�) 
	if(father[a]==a)
		return a;//���� 
	else
		return(Find(father,father[a]));//�ݹ� 
}

void Union(int *father,int a,int b){//�����ϲ���һ�� 
	if(father[b]==b)
		father[b]=a;
	else
		father[a]=b;
}

void Kruskal(int m,int c[][N],char *v){//���ò��鼯
	Edge ed[m];
	int father[N];
	//int rank[N];//�� ,�˴��ò��� 
	int i,j,k=0;
	for(i=0;i<N;i++)
		for(j=i;j<N;j++)
			if(c[i][j]<1000){
				ed[k].distance=c[i][j];
				ed[k].s=i;
				ed[k].t=j;
				k++;
			}
	for(i=0;i<m;i++)//�Ա�Ȩֵð������ ��ÿ��ѡ��Ȩ��С�ıߣ���ʹ�öѽ����Ż� 
		for(j=0;j<m-i-1;j++)
			if(ed[j].distance>ed[j+1].distance)
				swap1(&ed[j],&ed[j+1]);
	for(i=0;i<N;i++)
		father[i]=i;//��ʼ�����ڵ�(����)
		//rank[i]=1;//��ʼ���� 
	for(i=0;i<m;i++)
		if(Find(father,ed[i].s)!=Find(father,ed[i].t))//��������ͬһ���ϣ����γɻ�· 
			Union(father,ed[i].s,ed[i].t);
	for(i=0;i<N;i++)//��ӡ 
		if(father[i]!=i)
			printf("\n���ߣ�%c%c",v[father[i]],v[i]);
}

void printMatrix(char *v,int c[][N]){
	int i,j;
	printf("\n����ͼ���ڽӾ���Ϊ��\n");
	printf("  ");
	for(i=0;i<N;i++)
		printf("%c   ",v[i]);
	for(i=0;i<N;i++){
		printf("\n%c ",v[i]);
		for(j=0;j<N;j++){
			if(c[i][j]<1000)
				printf("%3d ",c[i][j]);
			else
				printf("��  ");
		}
		printf("\n");
	}
	printf("\n\n");
}

