/*
1．分别实现无向图的邻接矩阵和邻接表存储结构的建立算法，分析和比较各建
立算法的时间复杂度以及存储结构的空间占用情况；
2．实现无向图的邻接矩阵和邻接表两种存储结构的相互转换算法；
3．在上述两种存储结构上，分别实现无向图的深度优先搜索（递归和非递归)
和广度优先搜索算法。并以适当的方式存储和显示相应的搜索结果（深度优先或
广度优先生成森林（或生成树）、深度优先或广度优先序列和编号）；

4．分析搜索算法的时间复杂度和空间复杂度；
5．以文件形式输入图的顶点和边，并显示相应的结果。要求顶点不少于 10 个,边
数不少于 15 条；
6．软件功能结构安排合理，界面友好，便于使用。
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 10

typedef struct Node{//邻接表 
	char data;
	Node *next;
}Node;

typedef struct Stack{//栈 
	char data;
	Stack *next;
}Stack;

typedef struct celltype{//队列元素的型 
	char data;
	celltype *next;
}celltype;

typedef struct Queue{//队列 
	celltype *front;
	celltype *rear;
}Queue;

void s_Makenull(Stack *S);//栈置空 
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
void read_Matrix(char *v,char edge[][5],int n,int m,int c[][N]);//邻接矩阵 

Node *attach(char a,Node *p);//
void printList(Node *P[],int n);
void read_List(char *v,char edge[][5],int n,int m,Node *P[]);//邻接表
void freeall(Node *P[],int n);//释放邻接表 

void M_to_L(int c[][N],Node *P[],int n,char *v);//邻接矩阵 转 邻接表 
void L_to_M(int c[][N],Node *P[],int n,char *v);//邻接表 转 邻接矩阵 

int allflag(int *flag,int n);
void dfs_search_M(char ch,int c[][N],char *v,int n,int *flag);
void DFS_dg_Matrix(int c[][N],int n,char *v);//递归深搜-邻接矩阵 
void DFS_fdg_Matrix(int c[][N],int n,char *v);//非递归深搜-邻接矩阵
void BFS_Matrix(int c[][N],int n,char *v);// 广搜-邻接矩阵 

void dfs_search_L(char ch,Node *P[],char *v,int n,int *flag);
void DFS_dg_List(Node *P[],int n,char *v);//递归深搜-邻接表 
void DFS_fdg_List(Node *P[],int n,char *v);//非递归深搜-邻接表 
void BFS_List(Node *P[],int n,char *v);// 广搜-邻接表 

void menu();//菜单 

int main(){
	FILE *fp;
	char num[10],ch[5];
	int n,i,m,y;
	
	fp=fopen("D:\\DevC++\\lab3\\3.txt","r");
	fgets(num,9,fp);
	n=atoi(num);//点数 
	char v[n+1];//点集 
	for(i=0;i<n;i++)
		fscanf(fp,"%c",&v[i]);
	v[n]='\0';
	fgets(ch,3,fp);//读取其余半行 
	fgets(num,9,fp);
	m=atoi(num);//边数 
	char edge[m][5];//边集(带换行符) 
	for(i=0;i<m;i++)
		fgets(edge[i],4,fp);
	fclose(fp);
	
	while(1){
		/*********case语句中不要定义变量********/
		int c[N][N]={0};//邻接矩阵 ,只有初始化为全0才能这样使用 
		Node *head[n];//邻接表头 
		
		menu();
		printf("\t请输入你的选择：");
		scanf("%d",&y);
		switch(y){
			case 1:	read_Matrix(v,edge,n,m,c);
					printMatrix(v,c,n);//图的邻接矩阵
					break;
			case 2: read_List(v,edge,n,m,head);
					printList(head,n);//图的邻接表
					freeall(head,n);
					break;
					
			case 3: read_Matrix(v,edge,n,m,c);
					printMatrix(v,c,n);
					M_to_L(c,head,n,v);//邻接矩阵转邻接表
					printList(head,n);
					freeall(head,n);
					break;
			case 4: read_List(v,edge,n,m,head);
					printList(head,n);
					L_to_M(c,head,n,v);//邻接表转邻接矩阵
					printMatrix(v,c,n);
					freeall(head,n);
					break;
					
			case 5: read_Matrix(v,edge,n,m,c);
					DFS_dg_Matrix(c,n,v);//邻接矩阵--递归深搜
					break;
			case 6: read_Matrix(v,edge,n,m,c);
					DFS_fdg_Matrix(c,n,v);//邻接矩阵--非递归深搜
					break;
			case 7: read_Matrix(v,edge,n,m,c);
					BFS_Matrix(c,n,v);//邻接矩阵--广搜
					break;
					
			case 8: read_List(v,edge,n,m,head);
					DFS_dg_List(head,n,v);//邻接表--递归深搜
					freeall(head,n);
					break;
			case 9: read_List(v,edge,n,m,head);
					DFS_fdg_List(head,n,v);//邻接表--非递归深搜
					freeall(head,n);
					break;
			case 10:read_List(v,edge,n,m,head);
					BFS_List(head,n,v);//邻接表--广搜
					freeall(head,n);
					break;
					
			case 11:printf("已退出！！！");
					exit(0);
			default:printf("非法选择，请重新输入！！！");
					break;
		}
	}
	return 0;
}

void menu(){//菜单 
	printf("\t-----------------------------------\n");
	printf("\t|              菜单               |\n");
	printf("\t|1.图的邻接矩阵                   |\n");
	printf("\t|2.图的邻接表                     |\n");
	printf("\t|3.邻接矩阵转邻接表               |\n");
	printf("\t|4.邻接表转邻接矩阵               |\n");
	printf("\t|5.邻接矩阵--递归深搜             |\n");
	printf("\t|6.邻接矩阵--非递归深搜           |\n");
	printf("\t|7.邻接矩阵--广搜                 |\n");
	printf("\t|8.邻接表--递归深搜               |\n");
	printf("\t|9.邻接表--非递归深搜             |\n");
	printf("\t|10.邻接表--广搜                  |\n");
	printf("\t|11.退出！                        |\n");
	printf("\t-----------------------------------\n");
}

/************栈操作*************/
void s_Makenull(Stack *S){//栈置空 
	S=(Stack *)malloc(sizeof(Stack));
	S->next-NULL;
}

int s_isEmpty(Stack *S){//
	if(S->next!=NULL)
		return 0;//非空
	else
		return 1;//空 
}

char Top(Stack *S){//
	if(!s_isEmpty(S))
		return S->next->data;
	else
		printf("栈为空！！！");
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

/************队列操作************/
void q_Makenull(Queue Q){//
	celltype *head;
	head=(celltype *)malloc(sizeof(celltype));
	Q.front=head;
	Q.rear=Q.front;
}

int q_isEmpty(Queue Q){//
	if(Q.front==Q.rear)
		return 1;//空 
	else
		return 0;//非空 
}

char Front(Queue Q){//
	if(!q_isEmpty(Q))
		return Q.front->next->data; 
	else
		printf("队列为空！！！"); 
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
	if(Q.front->next==NULL)//这里很重要 
		Q.rear=Q.front;
	return Q;
}

/***********核心函数************/
int search(char *v,int n,char b){
	int i;
	for(i=0;i<n;i++)
		if(b==v[i])
			return i;
}

void printMatrix(char *v,int c[][N],int n){
	int i,j;
	printf("\n无向图的邻接矩阵为：\n");
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

void read_Matrix(char *v,char edge[][5],int n,int m,int c[][N]){//邻接矩阵 
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
	printf("\n无向图的邻接表为：");
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

void read_List(char *v,char edge[][5],int n,int m,Node *P[]){//邻接表
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

void M_to_L(int c[][N],Node *P[],int n,char *v){//邻接矩阵转邻接表 
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

void L_to_M(int c[][N],Node *P[],int n,char *v){//邻接表转邻接矩阵 
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
			return 0;//未全访问
		if(i==n-1) 
			return 1;//已全部访问 
	}
}

void dfs_search_M(char ch,int c[][N],char *v,int n,int *flag){
	int i,j;
	j=search(v,n,ch);
	printf("%c ",ch);
	flag[j]=1;//标记为已访问 
	for(i=0;i<n;i++){
		if(c[j][i]==1 && flag[i]==0)
			dfs_search_M(v[i],c,v,n,flag);//递归 
	}
}

void DFS_dg_Matrix(int c[][N],int n,char *v){//
	int flag[n]={0};//点全标记为未访问 
	printf("\n递归深搜序列：");
	while(!allflag(flag,n)){
		dfs_search_M(v[0],c,v,n,flag);
	}
	printf("\n");
}

void DFS_fdg_Matrix(int c[][N],int n,char *v){//
	int i,j;
	char ch;
	Stack *S;
	int flag[n]={0};//点全标记为未访问 
	printf("\n非递归深搜序列：");
	S=(Stack *)malloc(sizeof(Stack));//使用s_Makenull进行初始化会改变 v[n]的内容，原因未知！！ 
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
	int flag[n]={0};//点全标记为未访问 
	Queue Q;
	celltype *head;
	head=(celltype *)malloc(sizeof(celltype));
	Q.front=head;
	Q.rear=Q.front;
	Q=EnQueue(v[0],Q);
	flag[0]=1;
	printf("广搜序列：");
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
	flag[j]=1;//标记为已访问 
	t=P[j];
	while(t->next!=NULL){
		k=search(v,n,t->next->data);
		if(flag[k]==0)
			dfs_search_L(t->next->data,P,v,n,flag);//递归 
		else
			t=t->next;
	}
}

void DFS_dg_List(Node *P[],int n,char *v){//
	int flag[n]={0};//点全标记为未访问 
	printf("\n递归深搜序列：");
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
	int flag[n]={0};//点全标记为未访问 
	printf("\n非递归深搜序列：");
	S=(Stack *)malloc(sizeof(Stack));//使用s_Makenull进行初始化会改变 v[n]的内容，原因未知！！ 
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
	int flag[n]={0};//点全标记为未访问 
	Queue Q;
	celltype *head;
	head=(celltype *)malloc(sizeof(celltype));
	Q.front=head;
	Q.rear=Q.front;
	Q=EnQueue(v[0],Q);
	flag[0]=1;
	printf("广搜序列：");
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

