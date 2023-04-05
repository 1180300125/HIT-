/*1．实现单源最短路径的 Dijkstra 算法，输出源点及其到其他顶点的最短路径长
度和最短路径
2． 利用堆结构（实现的优先级队列），改进和优化 Dijkstra 算法的实现；
3． 实现全局最短路径的 Floyd-Warshall 算法。计算任意两个顶点间的最短距离
矩阵和最短路径矩阵，并输出任意两个顶点间的最短路径长度和最短路径。
4． 利用 Dijkstra 或 Floyd-Warshall 算法解决单目标最短路径问题：找出图中每
个顶点 v 到某个指定顶点 c 最短路径；
5． 利用 Dijkstra 或 Floyd-Warshall 算法解决单顶点对间最短路径问题：对于某
对顶点 u 和 v，找出 u 到 v 和 v 到 u 的一条最短路径 ；
6． （选做）利用 Floyd-Warshall 算法，计算有向图的可达矩阵，理解可达矩阵
的含义；
7． 以文件形式输入图的顶点和边，并显示相应的结果。要求顶点不少于 10 个，
边不少于 13 个；
8． 软件功能结构安排合理，界面友好，便于使用。*/  //有向图 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 10 //有向图顶点数 

typedef struct node{
	char point;
	int distance;
	struct node *next;
}Node;

typedef struct cell{//堆数组的元素的型 
	char point;
	int distance;
}celltype;

int search(char *v,int n,char b);
void printMatrix(char *v,int c[][N]);
void read_Matrix(char *v,char edge[][N],int n,int m,int c[][N]);//得到有向图带权邻接矩阵 

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
void Insert_Heap(celltype *num,int first,int last,celltype w);//堆(优先队列)插入--上涌 
celltype Delete_Heap(celltype *num,int first,int last);//堆(优先队列)删除--下推 
void PushDown(celltype *num,int first,int last);//整理堆，将 A[1]下推到合适位置，并把最小元素移到 A[1] 
void heap_Dijkstra(int c[][N],int D[N],int s,char *v,int P[][N]); 

void Path(int i,int j,int P[][N],char *v);
void Floyd_Warshall(int c[][N],int A[][N],int P[][N]);

void read_c(char *v,char edge[][N],int n,int m,int c[][N]);//得到无权的邻接矩阵 
void Accessibility_Matrix(int c[][N],int A[][N]);//利用 Floyd_Warshall算法计算可达矩阵 

void menu();

int main(){
	FILE *fp;
	char num[10],ch[5];
	int n,i,m,y,j;
	
	fp=fopen("D:\\DevC++\\homework3\\3_1.txt","r");
	fgets(num,9,fp);
	n=atoi(num);//点数 
	char v[n+1];//点集 
	for(i=0;i<n;i++)
		fscanf(fp,"%c",&v[i]);
	v[n]='\0';
	fgets(ch,3,fp);//读取其余半行 
	fgets(num,9,fp);
	m=atoi(num);//边数 
	char edge[m][N];//边集(带换行符) 
	for(i=0;i<m;i++)
		fgets(edge[i],8,fp);
	fclose(fp);
	
	while(1){
		int D[N],A[N][N],P[N][N];
		char s,t;
		int h,k;
		int c[N][N];//用10000代替无穷 
		for(i=0;i<N;i++)
			for(j=0;j<N;j++)
				c[i][j]=10000;
		
		read_Matrix(v,edge,n,m,c);
		//printMatrix(v,c);//图的邻接矩阵
		menu();
		printf("\t请输入你的选择：");
		scanf("%d",&y);
		switch(y){
			case 1:	Dijkstra(c,D,0,v,P);//Dijkstra算法
					printdistance_one(D,v,0);
					for(i=0;i<N;i++){
						if(D[i]<10000 && D[i]>0){//有最短路径 
							printf("\n最短路径%c%c：",v[0],v[i]);
							printf("%c->",v[0]);
							Path(0,i,P,v);
							printf("%c",v[i]);
						}
					}
					break;
			case 2:	heap_Dijkstra(c,D,0,v,P);//优先级队列优化的Dijstra算法
					printdistance_one(D,v,0);
					for(i=0;i<N;i++){
						if(D[i]<10000 && D[i]>0){//有最短路径 
							printf("\n最短路径%c%c：",v[0],v[i]);
							printf("%c->",v[0]);
							Path(0,i,P,v);
							printf("%c",v[i]);
						}
					}
					break;
			case 3: Floyd_Warshall(c,A,P);//
					printf("每对顶点之间的最短距离为：\n");
					printdistance_more(A,v);
					printpath(P,A,v);
					break;
			case 4:	Floyd_Warshall(c,A,P);
					printf("请输入目标顶点(大写字母)：");
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
							printf("∞  ");
					}
					for(i=0;i<N;i++){
						if(A[i][h]<10000 && A[i][h]>0){//有最短路径 
							printf("\n最短路径%c%c：",v[i],s);
							printf("%c->",v[i]);
							Path(i,h,P,v);
							printf("%c",s);
						}
					}
					break;
			case 5:	Floyd_Warshall(c,A,P);
					printf("请输入顶点对(大写字母)：");
					getchar();
					scanf("%c %c",&s,&t);
					h=search(v,N,s);
					k=search(v,N,t);
					if(A[h][k]<10000)
						printf("\n%c->%c的最短距离：%d",s,t,A[h][k]);
					else
						printf("\n%c无法到达%c",s,t);
					if(A[h][k]<10000 && A[h][k]>0){//有最短路径 
						printf("\n最短路径%c%c：",s,t);
						printf("%c->",s);
						Path(h,k,P,v);
						printf("%c",t);
					}
					if(A[k][h]<10000)
						printf("\n%c->%c的最短距离：%d",t,s,A[k][h]);
					else
						printf("\n%c无法到达%c",t,s);
					if(A[k][h]<10000 && A[k][h]>0){//有最短路径 
						printf("\n最短路径%c%c：",t,s);
						printf("%c->",t);
						Path(k,h,P,v);
						printf("%c",s);
					}
					break;
			case 6: read_c(v,edge,n,m,c);
					Accessibility_Matrix(c,A);
					printf("有向图的可达矩阵为：\n");
					printdistance_more(A,v);
					break;
			case 7: printf("已退出！！！");
					exit(0);
					break;
			default:printf("选择非法，请重新输入！！！");
					break;
		}
	}
	return 0;
}

void menu(){
	printf("\n\t------------------------------------------------\n");
	printf("\t|                      菜单                    |\n");
	printf("\t|1.Dijkstra算法--单源最短距离和路径            |\n");
	printf("\t|2.改进的Dijkstra算法--单源最短距离和路径      |\n");
	printf("\t|3.Floyd-Warshall算法--全局最短距离和路径      |\n");
	printf("\t|4.单目标最短距离和路径                        |\n");
	printf("\t|5.单顶点对最短距离和路径                      |\n");
	printf("\t|6.有向图的可达矩阵                            |\n");
	printf("\t|7.退出！                                      |\n");
	printf("\t------------------------------------------------\n");
}

int search(char *v,int n,char b){
	int i;
	for(i=0;i<n;i++)
		if(b==v[i])
			return i;
}

void read_Matrix(char *v,char edge[][N],int n,int m,int c[][N]){//邻接矩阵 
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
	create_S(&Shead,v,s,D);//初始化S集合 
	create_V_S(&V_Shead,v,s,D);//初始化V-S集合 
	for(i=0;i<N-1;i++){//N-1次循环 
		w=Findmin(V_Shead);
		a=w->next->point;//注意！此处需将点和距离记录下来，否则插入与删除操作会改变 w 对应的元素值 ，导致后续出错。！！！！ 
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
		PushDown(num,i,N-2);//初始化最小堆
}

void Insert_Heap(celltype *num,int first,int last,celltype w){//上涌 
	int i;
	i=last+1;
	num[i].distance=w.distance;
	num[i].point=w.point;
	while(i>0){
		if(i%2==0){//在右子树
			if(num[i].distance<num[(i-2)/2].distance){
				swap(&num[i],&num[(i-2)/2]);
				i=(i-2)/2;
			}
			else
				i=0;//结束循环 
		}
		else{//在左子树 
			if(num[i].distance<num[(i-1)/2].distance){
				swap(&num[i],&num[(i-1)/2]);
				i=(i-1)/2;
			}
			else
				i=0;//结束循环 
		}
	}
} 

celltype Delete_Heap(celltype *num,int first,int last){
	celltype temp;
	temp.distance=num[first].distance;
	temp.point=num[first].point;
	swap(&num[first],&num[last]);
	PushDown(num,first,last-1);//这句没有也不影响，因为还需要更新distance，在Renew的结束时会重新整理成堆结构 ！，但作为堆删除函数，这句必须存在！！！ 
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
		PushDown(num,i,last);//更新完距离后，要重新整理成堆！！！很重要！！！******************** 
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

void PushDown(celltype *num,int first,int last){//整理堆，将 A[0]下推到合适位置，并把最小(大)元素移到 A[0]-----此处选择使用最大堆，能使排序结果直接为升序 
	int k;
	k=first;
	while(2*k+1<=last){//每次循环进入下一层 
		if(2*k+1==last){//只有左子树 ,即最后一层 
			if(num[k].distance>num[2*k+1].distance)
				swap(&num[k],&num[2*k+1]);
			k=last;//使循环结束 
		}
		else if(num[k].distance>num[2*k+1].distance && num[2*k+1].distance<num[2*k+2].distance){//与子树中较大的一个交换 --最大堆 
			swap(&num[k],&num[2*k+1]);
			k=2*k+1;
		}
		else if(num[k].distance>num[2*k+2].distance && num[2*k+1].distance>=num[2*k+2].distance){
			swap(&num[k],&num[2*k+2]);
			k=2*k+2;
		}
		else//相等情况 
			k=last;//使循环结束 
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

void read_c(char *v,char edge[][N],int n,int m,int c[][N]){//得到无权的邻接矩阵 
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

void Accessibility_Matrix(int c[][N],int A[][N]){//利用 Floyd_Warshall算法计算可达矩阵
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
	printf("\n无向图的邻接矩阵为：\n");
	printf("  ");
	for(i=0;i<N;i++)
		printf("%c   ",v[i]);
	for(i=0;i<N;i++){
		printf("\n%c ",v[i]);
		for(j=0;j<N;j++){
			if(c[i][j]<10000)
				printf("%3d ",c[i][j]);
			else
				printf("∞  ");
		}
	}
	printf("\n\n");
}

void printdistance_one(int D[N],char *v,int s){
	int i;
	printf("源点：%c，单源最短路径为：\n",v[s]);
	for(i=0;i<N;i++)
		printf("%c   ",v[i]);
	printf("\n");
	for(i=0;i<N;i++){
		if(D[i]<10000)
			printf("%3d ",D[i]);
		else
			printf("∞  ");
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
				printf("∞  ");
		}
	}
	printf("\n\n");
}

void printpath(int P[][N],int A[][N],char *v){
	int i,j,k;
	for(i=0;i<N;i++)
		for(j=0;j<N;j++){
			if(A[i][j]<10000 && A[i][j]>0){//有最短路径 
				printf("\n最短路径%c%c：",v[i],v[j]);
				printf("%c->",v[i]);
				Path(i,j,P,v);
				printf("%c",v[j]);
			}
		}
}

