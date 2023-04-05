/*1．选择并建立加权连通图的存储结构，实现求解加权连通图的 Prim 算法，并输
出连接各顶点的最小生成树；
2．利用堆结构（实现的优先级队列）改进和优化 Prim 算法，降低时间复杂度，
实现改进和优化的 Prim 算法，并与原算法进行实验比较；
3．利用并查集，实现求解加权连通图的 Kruskal 算法，并输出连接各顶点的最
小生成树；
4．（选作）设计并实现其他最小生成树算法（如管梅谷破圈算法、Sollin(Boruvka)
算法）；
5．以文件形式输入图的顶点和边，并显示相应的结果。要求顶点不少于 10 个，
边不少于 13 个；无向图 
6．软件功能结构安排合理，界面友好，便于使用。*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 10 //无向图顶点数 

typedef struct node{
	char point;
	int distance;
	struct node *next;
}Node;

typedef struct cell{//堆数组的元素的型 
	int point;
	int distance;
}celltype;

typedef struct edge{//一条边 
	int s;//起点 
	int t;//终点 
	int distance;//边的权值 
}Edge;

int search(char *v,int n,char b);
void printMatrix(char *v,int c[][N]);
void read_Matrix(char *v,char edge[][N],int n,int m,int c[][N]);//得到有向图带权邻接矩阵 

void Prim(char *v,int c[][N]);

void Heap_Prim(char *v,int c[][N]);
void swap(celltype *a,celltype *b);
void create_V_UHeap(celltype *lowcost,int c[][N],int *closest);
void Renew_Heap(celltype *num,int first,int last,int c[][N],celltype w,int *closest);
void Insert_Heap(celltype *num,int first,int last,celltype w);//堆(优先队列)插入--上涌 
celltype Delete_Heap(celltype *num,int first,int last);//堆(优先队列)删除--下推 
void PushDown(celltype *num,int first,int last);//整理堆，将 A[1]下推到合适位置，并把最小元素移到 A[1] 

void swap1(Edge *a,Edge *b);
int Find(int *father,int a);//返回帮主(父父父...结点)(代表结点) 
void Union(int *father,int a,int b);//将两个集合合并成一个集合 
void Kruskal(int m,int c[][N],char *v);//利用并查集 

void menu();

int main(){
	FILE *fp;
	char num[10],ch[5];
	int n,i,m,y,j;
	
	fp=fopen("D:\\DevC++\\homework3\\3_2.txt","r");
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
		int c[N][N];//用10000代替无穷 
		for(i=0;i<N;i++)
			for(j=0;j<N;j++)
				c[i][j]=1000;//1000为大于任何权值，而小于无限大10000的常数 
		
		read_Matrix(v,edge,n,m,c);
		//printMatrix(v,c);//图的邻接矩阵
		menu();
		printf("\t请输入你的选择：");
		scanf("%d",&y);
		switch(y){
			case 1: Prim(v,c);
					break;
			case 2: Heap_Prim(v,c);
					break;
			case 3: Kruskal(m,c,v);
					break;
			case 4: printf("已退出！！！");
					exit(0);
					break;
			default:printf("非法选择，请重新输入！");
					break;
		}
	}
	return 0;
}

void menu(){
	printf("\n\t-----------------------------\n");
	printf("\t|           菜单            |\n");
	printf("\t|1.Prim算法                 |\n");
	printf("\t|2.Heap优化的Prim算法       |\n");
	printf("\t|3.并查集实现Kruskal算法    |\n");
	printf("\t|4.退出！                   |\n");
	printf("\t-----------------------------\n");
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
		c[j][i]=atoi(w);
	}
}

void Prim(char *v,int c[][N]){
	int lowcost[N];
	int closest[N];
	int min;
	int i,j,k;
	for(i=1;i<N;i++){//初始化 V-U ,从1开始循环意味着 0点(A点)加入集合U
		lowcost[i]=c[0][i];
		closest[i]=0;
	}
	for(i=1;i<N;i++){//N-1次循环 
		min=1000;
		for(j=1;j<N;j++)
			if(min>lowcost[j]){
				min=lowcost[j];
				k=j;
			}
		printf("\n树边：%c%c",v[closest[k]],v[k]);
		lowcost[k]=10000;//加入集合U 
		for(j=1;j<N;j++)
			if(c[k][j]<lowcost[j] && lowcost[j]!=10000){//更新 
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

void create_V_UHeap(celltype *lowcost,int c[][N],int *closest){//初始化集合 V-U 
	int i;
	for(i=0;i<N-1;i++){
		lowcost[i].distance=c[0][i+1];
		lowcost[i].point=i+1;
		closest[i]=0;
	}
	for(i=3;i>=0;i--)
		PushDown(lowcost,i,N-2);//初始化最小堆
}

void Insert_Heap(celltype *num,int first,int last,celltype w){//上涌 ，上涌时只与父节点比较即可 
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

void Renew_Heap(celltype *num,int first,int last,int c[][N],celltype w,int *closest){//更新 
	int i,k;
	k=w.point;
	for(i=first;i<=last;i++){
		if(c[k][num[i].point]<num[i].distance){
			num[i].distance=c[k][num[i].point];
			closest[num[i].point]=k;
		}
	}
	for(i=(last-1)/2;i>=0;i--)
		PushDown(num,i,last);//更新完距离后，要重新整理成堆！！！很重要！！！******************** 
}

void PushDown(celltype *num,int first,int last){//整理堆，将 A[first]下推到合适位置，并把最小(大)元素交换到 A[first]-----此处选择使用最大堆，能使排序结果直接为升序 
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

void Heap_Prim(char *v,int c[][N]){
	celltype lowcost[N],w;
	int closest[N],i;
	create_V_UHeap(lowcost,c,closest);
	for(i=0;i<N-1;i++){
		w=Delete_Heap(lowcost,0,N-2-i);//从V-U中删去就相当于加入到集合 U中 
		printf("\n树边：%c%c",v[closest[w.point]],v[w.point]);
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

int Find(int *father,int a){//返回帮主(父节点) 
	if(father[a]==a)
		return a;//帮主 
	else
		return(Find(father,father[a]));//递归 
}

void Union(int *father,int a,int b){//两个合并成一个 
	if(father[b]==b)
		father[b]=a;
	else
		father[a]=b;
}

void Kruskal(int m,int c[][N],char *v){//利用并查集
	Edge ed[m];
	int father[N];
	//int rank[N];//秩 ,此处用不到 
	int i,j,k=0;
	for(i=0;i<N;i++)
		for(j=i;j<N;j++)
			if(c[i][j]<1000){
				ed[k].distance=c[i][j];
				ed[k].s=i;
				ed[k].t=j;
				k++;
			}
	for(i=0;i<m;i++)//对边权值冒泡排序 。每次选择权最小的边，可使用堆进行优化 
		for(j=0;j<m-i-1;j++)
			if(ed[j].distance>ed[j+1].distance)
				swap1(&ed[j],&ed[j+1]);
	for(i=0;i<N;i++)
		father[i]=i;//初始化父节点(帮主)
		//rank[i]=1;//初始化秩 
	for(i=0;i<m;i++)
		if(Find(father,ed[i].s)!=Find(father,ed[i].t))//两顶点在同一集合，即形成环路 
			Union(father,ed[i].s,ed[i].t);
	for(i=0;i<N;i++)//打印 
		if(father[i]!=i)
			printf("\n树边：%c%c",v[father[i]],v[i]);
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
			if(c[i][j]<1000)
				printf("%3d ",c[i][j]);
			else
				printf("∞  ");
		}
		printf("\n");
	}
	printf("\n\n");
}

