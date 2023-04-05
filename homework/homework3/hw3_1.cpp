/*1��ʵ�ֵ�Դ���·���� Dijkstra �㷨�����Դ�㼰�䵽������������·����
�Ⱥ����·��
2�� ���öѽṹ��ʵ�ֵ����ȼ����У����Ľ����Ż� Dijkstra �㷨��ʵ�֣�
3�� ʵ��ȫ�����·���� Floyd-Warshall �㷨����������������������̾���
��������·�����󣬲���������������������·�����Ⱥ����·����
4�� ���� Dijkstra �� Floyd-Warshall �㷨�����Ŀ�����·�����⣺�ҳ�ͼ��ÿ
������ v ��ĳ��ָ������ c ���·����
5�� ���� Dijkstra �� Floyd-Warshall �㷨���������Լ����·�����⣺����ĳ
�Զ��� u �� v���ҳ� u �� v �� v �� u ��һ�����·�� ��
6�� ��ѡ�������� Floyd-Warshall �㷨����������ͼ�Ŀɴ�������ɴ����
�ĺ��壻
7�� ���ļ���ʽ����ͼ�Ķ���ͱߣ�����ʾ��Ӧ�Ľ����Ҫ�󶥵㲻���� 10 ����
�߲����� 13 ����
8�� ������ܽṹ���ź��������Ѻã�����ʹ�á�*/  //����ͼ 
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
	char point;
	int distance;
}celltype;

int search(char *v,int n,char b);
void printMatrix(char *v,int c[][N]);
void read_Matrix(char *v,char edge[][N],int n,int m,int c[][N]);//�õ�����ͼ��Ȩ�ڽӾ��� 

void printdistance_one(int D[N],char *v,int s);
void printdistance_more(int D[][N],char *v);
void printpath(int P[][N],int A[][N],char *v);

Node *Findmin(Node *t);
void Insert(Node *t,char a,int d);
void Delete(Node *t,char a);
void Renew(Node *t,int c[][N],char a,int d,char *v,int s,int P[][N]);
Node *attach(char a,int d,Node *t);
void create_V_S(Node **t,char *v,int s,int D[N]);
void create_S(Node **t,char *v,int s,int D[N]);
void Dijkstra(int c[][N],int D[N],int s,char *v,int P[][N]);

void swap(celltype *a,celltype *b);
void create_V_SHeap(celltype *num,int D[N],char *v,int s);
void Renew_Heap(celltype *num,int first,int last,int c[][N],celltype w,char *v,int s,int P[][N]);
void Insert_Heap(celltype *num,int first,int last,celltype w);//��(���ȶ���)����--��ӿ 
celltype Delete_Heap(celltype *num,int first,int last);//��(���ȶ���)ɾ��--���� 
void PushDown(celltype *num,int first,int last);//����ѣ��� A[1]���Ƶ�����λ�ã�������СԪ���Ƶ� A[1] 
void heap_Dijkstra(int c[][N],int D[N],int s,char *v,int P[][N]); 

void Path(int i,int j,int P[][N],char *v);
void Floyd_Warshall(int c[][N],int A[][N],int P[][N]);

void read_c(char *v,char edge[][N],int n,int m,int c[][N]);//�õ���Ȩ���ڽӾ��� 
void Accessibility_Matrix(int c[][N],int A[][N]);//���� Floyd_Warshall�㷨����ɴ���� 

void menu();

int main(){
	FILE *fp;
	char num[10],ch[5];
	int n,i,m,y,j;
	
	fp=fopen("D:\\DevC++\\homework3\\3_1.txt","r");
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
		int D[N],A[N][N],P[N][N];
		char s,t;
		int h,k;
		int c[N][N];//��10000�������� 
		for(i=0;i<N;i++)
			for(j=0;j<N;j++)
				c[i][j]=10000;
		
		read_Matrix(v,edge,n,m,c);
		//printMatrix(v,c);//ͼ���ڽӾ���
		menu();
		printf("\t���������ѡ��");
		scanf("%d",&y);
		switch(y){
			case 1:	Dijkstra(c,D,0,v,P);//Dijkstra�㷨
					printdistance_one(D,v,0);
					for(i=0;i<N;i++){
						if(D[i]<10000 && D[i]>0){//�����·�� 
							printf("\n���·��%c%c��",v[0],v[i]);
							printf("%c->",v[0]);
							Path(0,i,P,v);
							printf("%c",v[i]);
						}
					}
					break;
			case 2:	heap_Dijkstra(c,D,0,v,P);//���ȼ������Ż���Dijstra�㷨
					printdistance_one(D,v,0);
					for(i=0;i<N;i++){
						if(D[i]<10000 && D[i]>0){//�����·�� 
							printf("\n���·��%c%c��",v[0],v[i]);
							printf("%c->",v[0]);
							Path(0,i,P,v);
							printf("%c",v[i]);
						}
					}
					break;
			case 3: Floyd_Warshall(c,A,P);//
					printf("ÿ�Զ���֮�����̾���Ϊ��\n");
					printdistance_more(A,v);
					printpath(P,A,v);
					break;
			case 4:	Floyd_Warshall(c,A,P);
					printf("������Ŀ�궥��(��д��ĸ)��");
					getchar();
					scanf("%c",&s);
					h=search(v,N,s);
					for(i=0;i<N;i++)
						printf("%c   ",v[i]);
					printf("\n");
					for(i=0;i<N;i++){
						if(A[i][h]<10000)
							printf("%3d ",A[i][h]);
						else
							printf("��  ");
					}
					for(i=0;i<N;i++){
						if(A[i][h]<10000 && A[i][h]>0){//�����·�� 
							printf("\n���·��%c%c��",v[i],s);
							printf("%c->",v[i]);
							Path(i,h,P,v);
							printf("%c",s);
						}
					}
					break;
			case 5:	Floyd_Warshall(c,A,P);
					printf("�����붥���(��д��ĸ)��");
					getchar();
					scanf("%c %c",&s,&t);
					h=search(v,N,s);
					k=search(v,N,t);
					if(A[h][k]<10000)
						printf("\n%c->%c����̾��룺%d",s,t,A[h][k]);
					else
						printf("\n%c�޷�����%c",s,t);
					if(A[h][k]<10000 && A[h][k]>0){//�����·�� 
						printf("\n���·��%c%c��",s,t);
						printf("%c->",s);
						Path(h,k,P,v);
						printf("%c",t);
					}
					if(A[k][h]<10000)
						printf("\n%c->%c����̾��룺%d",t,s,A[k][h]);
					else
						printf("\n%c�޷�����%c",t,s);
					if(A[k][h]<10000 && A[k][h]>0){//�����·�� 
						printf("\n���·��%c%c��",t,s);
						printf("%c->",t);
						Path(k,h,P,v);
						printf("%c",s);
					}
					break;
			case 6: read_c(v,edge,n,m,c);
					Accessibility_Matrix(c,A);
					printf("����ͼ�Ŀɴ����Ϊ��\n");
					printdistance_more(A,v);
					break;
			case 7: printf("���˳�������");
					exit(0);
					break;
			default:printf("ѡ��Ƿ������������룡����");
					break;
		}
	}
	return 0;
}

void menu(){
	printf("\n\t------------------------------------------------\n");
	printf("\t|                      �˵�                    |\n");
	printf("\t|1.Dijkstra�㷨--��Դ��̾����·��            |\n");
	printf("\t|2.�Ľ���Dijkstra�㷨--��Դ��̾����·��      |\n");
	printf("\t|3.Floyd-Warshall�㷨--ȫ����̾����·��      |\n");
	printf("\t|4.��Ŀ����̾����·��                        |\n");
	printf("\t|5.���������̾����·��                      |\n");
	printf("\t|6.����ͼ�Ŀɴ����                            |\n");
	printf("\t|7.�˳���                                      |\n");
	printf("\t------------------------------------------------\n");
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
	}
	for(l=0;l<n;l++)
		c[l][l]=0;
}

Node *Findmin(Node *t){
	Node *p,*temp;
	p=t;
	int min;
	min=t->next->distance;
	temp=p;
	while(p->next!=NULL){
		if(min > p->next->distance){
			min=p->next->distance;
			temp=p;
		}
		p=p->next;
	}
	return temp;
}

void Insert(Node *t,char a,int d){
	Node *p;
	p=(Node *)malloc(sizeof(Node));
	p->distance=d;
	p->point=a;
	p->next=t->next;
	t->next=p;
}

void Delete(Node *t,char a){
	Node *p,*temp;
	p=t;
	while(p->next!=NULL){
		if(p->next->point==a){
			temp=p->next;
			p->next=temp->next;
			free(temp);
			break;
		}
		else
			p=p->next;
	}
}

void Renew(Node *t,int c[][N],char a,int d,char *v,int s,int P[][N]){
	Node *p;
	int i,j;
	p=t;
	i=search(v,N,a);
	while(p->next!=NULL){
		j=search(v,N,p->next->point);
		if(p->next->distance > (d+c[i][j])){
			p->next->distance = d+c[i][j];
			P[s][j]=i; 
		}
		p=p->next;
	}
}

Node *attach(char a,int d,Node *t){
	Node *p;
	p=(Node *)malloc(sizeof(Node));
	p->point=a;
	p->distance=d;
	t->next=p;
	p->next=NULL;
	return p;
}

void create_V_S(Node **t,char *v,int s,int D[N]){
	Node *p;
	int i;
	p=(Node *)malloc(sizeof(Node));
	(*t)=p;
	for(i=0;i<N;i++)
		if(i!=s)
			p=attach(v[i],D[i],p);
}

void create_S(Node **t,char *v,int s,int D[N]){
	Node *p;
	int i;
	p=(Node *)malloc(sizeof(Node));
	(*t)=p;
	p=attach(v[s],D[s],p);
}

void Dijkstra(int c[][N],int D[N],int s,char *v,int P[][N]){
	int i,d,j;
	char a;
	for(i=0;i<N;i++)
		for(j=0;j<N;j++)
			P[i][j]=0;
	for(i=0;i<N;i++)
		D[i]=c[s][i];
	Node *Shead,*V_Shead,*w;
	create_S(&Shead,v,s,D);//��ʼ��S���� 
	create_V_S(&V_Shead,v,s,D);//��ʼ��V-S���� 
	for(i=0;i<N-1;i++){//N-1��ѭ�� 
		w=Findmin(V_Shead);
		a=w->next->point;//ע�⣡�˴��轫��;����¼���������������ɾ��������ı� w ��Ӧ��Ԫ��ֵ �����º��������������� 
		d=w->next->distance;
		Insert(Shead,a,d);
		Delete(V_Shead,a);
		Renew(V_Shead,c,a,d,v,s,P);
	}
	w=Shead;
	while(w->next!=NULL){
		i=search(v,N,w->next->point);
		D[i]=w->next->distance;
		w=w->next;
	}
}

void swap(celltype *a,celltype *b){
	int temp;
	char ch;
	temp=(*a).distance;
	(*a).distance=(*b).distance;
	(*b).distance=temp;
	ch=(*a).point;
	(*a).point=(*b).point;
	(*b).point=ch;
}

void create_V_SHeap(celltype *num,int D[N],char *v,int s){
	int i,j=0;
	for(i=0;i<N;i++)
		if(i!=s){
			num[j].distance=D[i];
			num[j].point=v[i];
			j++;
		}
	for(i=3;i>=0;i--)
		PushDown(num,i,N-2);//��ʼ����С��
}

void Insert_Heap(celltype *num,int first,int last,celltype w){//��ӿ 
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

void Renew_Heap(celltype *num,int first,int last,int c[][N],celltype w,char *v,int s,int P[][N]){
	int i,j,k;
	k=search(v,N,w.point);
	for(i=first;i<=last;i++){
		j=search(v,N,num[i].point);
		if(num[i].distance > (w.distance+c[k][j])){
			num[i].distance = w.distance+c[k][j];
			P[s][j]=k;
		}
	}
	for(i=(last-1)/2;i>=0;i--)
		PushDown(num,i,last);//����������Ҫ��������ɶѣ���������Ҫ������******************** 
}

void heap_Dijkstra(int c[][N],int D[N],int s,char *v,int P[][N]){
	int i,j;
	for(i=0;i<N;i++)
		for(j=0;j<N;j++)
			P[i][j]=0;
	for(i=0;i<N;i++)
		D[i]=c[s][i];
	celltype w;
	celltype S[N],V_S[N];
	S[0].distance=D[s];
	S[0].point=v[s];
	create_V_SHeap(V_S,D,v,s);
	for(i=0;i<N-1;i++){
		w=Delete_Heap(V_S,0,N-2-i);
		Insert_Heap(S,0,i,w);
		Renew_Heap(V_S,0,N-3-i,c,w,v,s,P);
	}
	for(i=0;i<N;i++){
		j=search(v,N,S[i].point);
		D[j]=S[i].distance;
	}
}

void PushDown(celltype *num,int first,int last){//����ѣ��� A[0]���Ƶ�����λ�ã�������С(��)Ԫ���Ƶ� A[0]-----�˴�ѡ��ʹ�����ѣ���ʹ������ֱ��Ϊ���� 
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

void Path(int i,int j,int P[][N],char *v){
	int k;
	k=P[i][j];
	if(k!=0){
		Path(i,k,P,v);
		printf("%c->",v[k]);
		Path(k,j,P,v);
	}
}

void Floyd_Warshall(int c[][N],int A[][N],int P[][N]){
	int i,j,k;
	for(i=0;i<N;i++)
		for(j=0;j<N;j++){
			A[i][j]=c[i][j];
			P[i][j]=0;
		}
	for(k=0;k<N;k++)
		for(i=0;i<N;i++)
			for(j=0;j<N;j++)
				if(A[i][j]>A[i][k]+A[k][j]){
					A[i][j]=A[i][k]+A[k][j];
					P[i][j]=k;
				}	
}

void read_c(char *v,char edge[][N],int n,int m,int c[][N]){//�õ���Ȩ���ڽӾ��� 
	int k,i,j,t,l;
	char w[5];
	for(k=0;k<n;k++)
		for(l=0;l<n;l++)
			c[k][l]=0;
	for(k=0;k<m;k++){
		i=search(v,n,edge[k][0]);
		j=search(v,n,edge[k][1]);
		c[i][j]=1;
	}
	for(l=0;l<n;l++)
		c[l][l]=1;
}

void Accessibility_Matrix(int c[][N],int A[][N]){//���� Floyd_Warshall�㷨����ɴ����
	int i,j,k;
	for(i=0;i<N;i++)
		for(j=0;j<N;j++)
			A[i][j]=c[i][j];
	for(k=0;k<N;k++)
		for(i=0;i<N;i++)
			for(j=0;j<N;j++)
				A[i][j]=A[i][j]|(A[i][k]&A[k][j]);
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
			if(c[i][j]<10000)
				printf("%3d ",c[i][j]);
			else
				printf("��  ");
		}
	}
	printf("\n\n");
}

void printdistance_one(int D[N],char *v,int s){
	int i;
	printf("Դ�㣺%c����Դ���·��Ϊ��\n",v[s]);
	for(i=0;i<N;i++)
		printf("%c   ",v[i]);
	printf("\n");
	for(i=0;i<N;i++){
		if(D[i]<10000)
			printf("%3d ",D[i]);
		else
			printf("��  ");
	}
	printf("\n\n");
}

void printdistance_more(int D[][N],char *v){
	int i,j;
	printf("  ");
	for(i=0;i<N;i++)
		printf("%c   ",v[i]);
	for(i=0;i<N;i++){
		printf("\n%c ",v[i]);
		for(j=0;j<N;j++){
			if(D[i][j]<10000)
				printf("%3d ",D[i][j]);
			else
				printf("��  ");
		}
	}
	printf("\n\n");
}

void printpath(int P[][N],int A[][N],char *v){
	int i,j,k;
	for(i=0;i<N;i++)
		for(j=0;j<N;j++){
			if(A[i][j]<10000 && A[i][j]>0){//�����·�� 
				printf("\n���·��%c%c��",v[i],v[j]);
				printf("%c->",v[i]);
				Path(i,j,P,v);
				printf("%c",v[j]);
			}
		}
}

