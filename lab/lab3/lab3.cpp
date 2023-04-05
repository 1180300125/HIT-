/*
1���ֱ�ʵ������ͼ���ڽӾ�����ڽӱ�洢�ṹ�Ľ����㷨�������ͱȽϸ���
���㷨��ʱ�临�Ӷ��Լ��洢�ṹ�Ŀռ�ռ�������
2��ʵ������ͼ���ڽӾ�����ڽӱ����ִ洢�ṹ���໥ת���㷨��
3�����������ִ洢�ṹ�ϣ��ֱ�ʵ������ͼ����������������ݹ�ͷǵݹ�)
�͹�����������㷨�������ʵ��ķ�ʽ�洢����ʾ��Ӧ�����������������Ȼ�
�����������ɭ�֣�������������������Ȼ����������кͱ�ţ���

4�����������㷨��ʱ�临�ӶȺͿռ临�Ӷȣ�
5�����ļ���ʽ����ͼ�Ķ���ͱߣ�����ʾ��Ӧ�Ľ����Ҫ�󶥵㲻���� 10 ��,��
�������� 15 ����
6��������ܽṹ���ź��������Ѻã�����ʹ�á�
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 10

typedef struct Node{//�ڽӱ� 
	char data;
	Node *next;
}Node;

typedef struct Stack{//ջ 
	char data;
	Stack *next;
}Stack;

typedef struct celltype{//����Ԫ�ص��� 
	char data;
	celltype *next;
}celltype;

typedef struct Queue{//���� 
	celltype *front;
	celltype *rear;
}Queue;

void s_Makenull(Stack *S);//ջ�ÿ� 
int  s_isEmpty(Stack *S);//
char Top(Stack *S);//
void Push(char a,Stack *S);//
void Pop(Stack *S);//

void q_Makenull(Queue Q);//
int  q_isEmpty(Queue Q);//
char Front(Queue Q);//
Queue EnQueue(char a,Queue Q);//
Queue DeQueue(Queue Q);//

int search(char *v,int n,char b);
void printMatrix(char *v,int c[][N],int n);
void read_Matrix(char *v,char edge[][5],int n,int m,int c[][N]);//�ڽӾ��� 

Node *attach(char a,Node *p);//
void printList(Node *P[],int n);
void read_List(char *v,char edge[][5],int n,int m,Node *P[]);//�ڽӱ�
void freeall(Node *P[],int n);//�ͷ��ڽӱ� 

void M_to_L(int c[][N],Node *P[],int n,char *v);//�ڽӾ��� ת �ڽӱ� 
void L_to_M(int c[][N],Node *P[],int n,char *v);//�ڽӱ� ת �ڽӾ��� 

int allflag(int *flag,int n);
void dfs_search_M(char ch,int c[][N],char *v,int n,int *flag);
void DFS_dg_Matrix(int c[][N],int n,char *v);//�ݹ�����-�ڽӾ��� 
void DFS_fdg_Matrix(int c[][N],int n,char *v);//�ǵݹ�����-�ڽӾ���
void BFS_Matrix(int c[][N],int n,char *v);// ����-�ڽӾ��� 

void dfs_search_L(char ch,Node *P[],char *v,int n,int *flag);
void DFS_dg_List(Node *P[],int n,char *v);//�ݹ�����-�ڽӱ� 
void DFS_fdg_List(Node *P[],int n,char *v);//�ǵݹ�����-�ڽӱ� 
void BFS_List(Node *P[],int n,char *v);// ����-�ڽӱ� 

void menu();//�˵� 

int main(){
	FILE *fp;
	char num[10],ch[5];
	int n,i,m,y;
	
	fp=fopen("D:\\DevC++\\lab3\\3.txt","r");
	fgets(num,9,fp);
	n=atoi(num);//���� 
	char v[n+1];//�㼯 
	for(i=0;i<n;i++)
		fscanf(fp,"%c",&v[i]);
	v[n]='\0';
	fgets(ch,3,fp);//��ȡ������� 
	fgets(num,9,fp);
	m=atoi(num);//���� 
	char edge[m][5];//�߼�(�����з�) 
	for(i=0;i<m;i++)
		fgets(edge[i],4,fp);
	fclose(fp);
	
	while(1){
		/*********case����в�Ҫ�������********/
		int c[N][N]={0};//�ڽӾ��� ,ֻ�г�ʼ��Ϊȫ0��������ʹ�� 
		Node *head[n];//�ڽӱ�ͷ 
		
		menu();
		printf("\t���������ѡ��");
		scanf("%d",&y);
		switch(y){
			case 1:	read_Matrix(v,edge,n,m,c);
					printMatrix(v,c,n);//ͼ���ڽӾ���
					break;
			case 2: read_List(v,edge,n,m,head);
					printList(head,n);//ͼ���ڽӱ�
					freeall(head,n);
					break;
					
			case 3: read_Matrix(v,edge,n,m,c);
					printMatrix(v,c,n);
					M_to_L(c,head,n,v);//�ڽӾ���ת�ڽӱ�
					printList(head,n);
					freeall(head,n);
					break;
			case 4: read_List(v,edge,n,m,head);
					printList(head,n);
					L_to_M(c,head,n,v);//�ڽӱ�ת�ڽӾ���
					printMatrix(v,c,n);
					freeall(head,n);
					break;
					
			case 5: read_Matrix(v,edge,n,m,c);
					DFS_dg_Matrix(c,n,v);//�ڽӾ���--�ݹ�����
					break;
			case 6: read_Matrix(v,edge,n,m,c);
					DFS_fdg_Matrix(c,n,v);//�ڽӾ���--�ǵݹ�����
					break;
			case 7: read_Matrix(v,edge,n,m,c);
					BFS_Matrix(c,n,v);//�ڽӾ���--����
					break;
					
			case 8: read_List(v,edge,n,m,head);
					DFS_dg_List(head,n,v);//�ڽӱ�--�ݹ�����
					freeall(head,n);
					break;
			case 9: read_List(v,edge,n,m,head);
					DFS_fdg_List(head,n,v);//�ڽӱ�--�ǵݹ�����
					freeall(head,n);
					break;
			case 10:read_List(v,edge,n,m,head);
					BFS_List(head,n,v);//�ڽӱ�--����
					freeall(head,n);
					break;
					
			case 11:printf("���˳�������");
					exit(0);
			default:printf("�Ƿ�ѡ�����������룡����");
					break;
		}
	}
	return 0;
}

void menu(){//�˵� 
	printf("\t-----------------------------------\n");
	printf("\t|              �˵�               |\n");
	printf("\t|1.ͼ���ڽӾ���                   |\n");
	printf("\t|2.ͼ���ڽӱ�                     |\n");
	printf("\t|3.�ڽӾ���ת�ڽӱ�               |\n");
	printf("\t|4.�ڽӱ�ת�ڽӾ���               |\n");
	printf("\t|5.�ڽӾ���--�ݹ�����             |\n");
	printf("\t|6.�ڽӾ���--�ǵݹ�����           |\n");
	printf("\t|7.�ڽӾ���--����                 |\n");
	printf("\t|8.�ڽӱ�--�ݹ�����               |\n");
	printf("\t|9.�ڽӱ�--�ǵݹ�����             |\n");
	printf("\t|10.�ڽӱ�--����                  |\n");
	printf("\t|11.�˳���                        |\n");
	printf("\t-----------------------------------\n");
}

/************ջ����*************/
void s_Makenull(Stack *S){//ջ�ÿ� 
	S=(Stack *)malloc(sizeof(Stack));
	S->next-NULL;
}

int s_isEmpty(Stack *S){//
	if(S->next!=NULL)
		return 0;//�ǿ�
	else
		return 1;//�� 
}

char Top(Stack *S){//
	if(!s_isEmpty(S))
		return S->next->data;
	else
		printf("ջΪ�գ�����");
}

void Push(char a,Stack *S){//
	Stack *p;
	p=(Stack *)malloc(sizeof(Stack));
	p->next=S->next;
	S->next=p;
	p->data=a;
}

void Pop(Stack *S){//
	Stack *p;
	p=S->next;
	S->next=p->next;
	free(p);
}

/************���в���************/
void q_Makenull(Queue Q){//
	celltype *head;
	head=(celltype *)malloc(sizeof(celltype));
	Q.front=head;
	Q.rear=Q.front;
}

int q_isEmpty(Queue Q){//
	if(Q.front==Q.rear)
		return 1;//�� 
	else
		return 0;//�ǿ� 
}

char Front(Queue Q){//
	if(!q_isEmpty(Q))
		return Q.front->next->data; 
	else
		printf("����Ϊ�գ�����"); 
}

Queue EnQueue(char a,Queue Q){//
	celltype *p;
	p=(celltype *)malloc(sizeof(celltype));
	p->data=a;
	p->next=NULL;
	Q.rear->next=p;
	Q.rear=p;
	return Q;
}

Queue DeQueue(Queue Q){//
	celltype *p;
	p=Q.front->next;
	Q.front->next=p->next;
	free(p);
	if(Q.front->next==NULL)//�������Ҫ 
		Q.rear=Q.front;
	return Q;
}

/***********���ĺ���************/
int search(char *v,int n,char b){
	int i;
	for(i=0;i<n;i++)
		if(b==v[i])
			return i;
}

void printMatrix(char *v,int c[][N],int n){
	int i,j;
	printf("\n����ͼ���ڽӾ���Ϊ��\n");
	printf("  ");
	for(i=0;i<n;i++)
		printf("%c ",v[i]);
	for(i=0;i<n;i++){
		printf("\n%c ",v[i]);
		for(j=0;j<n;j++)
			printf("%d ",c[i][j]);
	}
	printf("\n\n");
}

void read_Matrix(char *v,char edge[][5],int n,int m,int c[][N]){//�ڽӾ��� 
	int k,i,j;
	for(k=0;k<m;k++){
		i=search(v,n,edge[k][0]);
		j=search(v,n,edge[k][1]);
		c[i][j]=1;
		c[j][i]=1;
	}
}

void printList(Node *P[],int n){
	int i;
	Node *t;
	printf("\n����ͼ���ڽӱ�Ϊ��");
	for(i=0;i<n;i++){
		t=P[i];
		if(t->next!=NULL)
			printf("\n%c:",t->data);
		else
			printf("%c.",t->data); 
		while(t->next!=NULL){
			printf("->%c",t->next->data);
			t=t->next;
		}
	}
	printf("\n\n");
}

void read_List(char *v,char edge[][5],int n,int m,Node *P[]){//�ڽӱ�
	int i,j;
	Node *t;
	for(i=0;i<n;i++)
		P[i]=(Node *)malloc(sizeof(Node));
	for(i=0;i<n;i++){
		t=P[i];
		t->data=v[i];
		for(j=0;j<m;j++){
			if(edge[j][0]==v[i])
				t=attach(edge[j][1],t);
			if(edge[j][1]==v[i])
				t=attach(edge[j][0],t);
		}
		t->next=NULL;
	}
}

Node *attach(char a,Node *p){//
	Node *t;
	t=(Node *)malloc(sizeof(Node));
	t->data=a;
	p->next=t;
	return t;
}

void freeall(Node *P[],int n){
	int i;
	Node *t,*l;
	for(i=0;i<n;i++){
		l=P[i];
		while(l->next!=NULL){
			t=l->next;
			free(l);
			l=t;
		}
		free(l);
	}
}

void M_to_L(int c[][N],Node *P[],int n,char *v){//�ڽӾ���ת�ڽӱ� 
	int i,j;
	Node *t;
	for(i=0;i<n;i++){
		P[i]=(Node *)malloc(sizeof(Node));
		P[i]->data=v[i];
	}
	for(i=0;i<n;i++){
		t=P[i];
		for(j=0;j<n;j++)
			if(c[i][j]==1)
				t=attach(v[j],t);
		t->next=NULL;
	}
}

void L_to_M(int c[][N],Node *P[],int n,char *v){//�ڽӱ�ת�ڽӾ��� 
	int i,j;
	Node *t;
	for(i=0;i<n;i++){
		t=P[i];
		while(t->next!=NULL){
			j=search(v,n,t->next->data);
			c[i][j]=1;
			t=t->next;
		}
	}
}

int allflag(int *flag,int n){
	int i;
	for(i=0;i<n;i++){
		if(flag[i]==0)
			return 0;//δȫ����
		if(i==n-1) 
			return 1;//��ȫ������ 
	}
}

void dfs_search_M(char ch,int c[][N],char *v,int n,int *flag){
	int i,j;
	j=search(v,n,ch);
	printf("%c ",ch);
	flag[j]=1;//���Ϊ�ѷ��� 
	for(i=0;i<n;i++){
		if(c[j][i]==1 && flag[i]==0)
			dfs_search_M(v[i],c,v,n,flag);//�ݹ� 
	}
}

void DFS_dg_Matrix(int c[][N],int n,char *v){//
	int flag[n]={0};//��ȫ���Ϊδ���� 
	printf("\n�ݹ��������У�");
	while(!allflag(flag,n)){
		dfs_search_M(v[0],c,v,n,flag);
	}
	printf("\n");
}

void DFS_fdg_Matrix(int c[][N],int n,char *v){//
	int i,j;
	char ch;
	Stack *S;
	int flag[n]={0};//��ȫ���Ϊδ���� 
	printf("\n�ǵݹ��������У�");
	S=(Stack *)malloc(sizeof(Stack));//ʹ��s_Makenull���г�ʼ����ı� v[n]�����ݣ�ԭ��δ֪���� 
	S->next=NULL;
	Push(v[0],S);
	printf("%c ",v[0]);
	while(!s_isEmpty(S)){
		ch=Top(S);
		j=search(v,n,ch);
		flag[j]=1;
		for(i=0;i<n;i++){
			if(c[j][i]==1 && flag[i]==0){
				Push(v[i],S);
				printf("%c ",v[i]);
				break;
			}
			if(i==n-1)
				Pop(S);
		}
	}
	printf("\n");
}

void BFS_Matrix(int c[][N],int n,char *v){// 
	int i,j;
	char ch;
	int flag[n]={0};//��ȫ���Ϊδ���� 
	Queue Q;
	celltype *head;
	head=(celltype *)malloc(sizeof(celltype));
	Q.front=head;
	Q.rear=Q.front;
	Q=EnQueue(v[0],Q);
	flag[0]=1;
	printf("�������У�");
	while(!q_isEmpty(Q)){
		ch=Front(Q);
		j=search(v,n,ch);
		printf("%c ",ch);
		Q=DeQueue(Q);
		for(i=0;i<n;i++){
			if(c[j][i]==1 && flag[i]==0){
				Q=EnQueue(v[i],Q);
				flag[i]=1;
			}
		}
	}
	printf("\n");
}

void dfs_search_L(char ch,Node *P[],char *v,int n,int *flag){
	int j,k;
	Node *t;
	j=search(v,n,ch);
	printf("%c ",ch);
	flag[j]=1;//���Ϊ�ѷ��� 
	t=P[j];
	while(t->next!=NULL){
		k=search(v,n,t->next->data);
		if(flag[k]==0)
			dfs_search_L(t->next->data,P,v,n,flag);//�ݹ� 
		else
			t=t->next;
	}
}

void DFS_dg_List(Node *P[],int n,char *v){//
	int flag[n]={0};//��ȫ���Ϊδ���� 
	printf("\n�ݹ��������У�");
	while(!allflag(flag,n)){
		dfs_search_L(v[0],P,v,n,flag);
	}
	printf("\n");
}

void DFS_fdg_List(Node *P[],int n,char *v){//
	int j,k;
	char ch;
	Stack *S;
	Node *t;
	int flag[n]={0};//��ȫ���Ϊδ���� 
	printf("\n�ǵݹ��������У�");
	S=(Stack *)malloc(sizeof(Stack));//ʹ��s_Makenull���г�ʼ����ı� v[n]�����ݣ�ԭ��δ֪���� 
	S->next=NULL;
	Push(v[0],S);
	printf("%c ",v[0]);
	while(!s_isEmpty(S)){
		ch=Top(S);
		j=search(v,n,ch);
		flag[j]=1;
		t=P[j];
		while(t->next!=NULL){
			k=search(v,n,t->next->data);
			if(flag[k]==0){
				Push(t->next->data,S);
				printf("%c ",t->next->data);
				break;
			}
			else
				t=t->next;
			if(t->next==NULL)
				Pop(S);
		}
	}
	printf("\n");
}

void BFS_List(Node *P[],int n,char *v){// 
	int j,k;
	char ch;
	Node *t;
	int flag[n]={0};//��ȫ���Ϊδ���� 
	Queue Q;
	celltype *head;
	head=(celltype *)malloc(sizeof(celltype));
	Q.front=head;
	Q.rear=Q.front;
	Q=EnQueue(v[0],Q);
	flag[0]=1;
	printf("�������У�");
	while(!q_isEmpty(Q)){
		ch=Front(Q);
		j=search(v,n,ch);
		printf("%c ",ch);
		Q=DeQueue(Q);
		t=P[j];
		while(t->next!=NULL){
			k=search(v,n,t->next->data);
			if(flag[k]==0){
				Q=EnQueue(t->next->data,Q);
				flag[k]=1;
			}
			else
				t=t->next;
		}
	}
	printf("\n");
}

