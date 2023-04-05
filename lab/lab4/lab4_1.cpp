/*
本实验要求编写程序实现 BST 存储结构的建立（插入）、删除、查找和排
序算法；实现折半查找算法；比较 BST 查找结构与折半查找的时间性能。
实验要求：
1．设计 BST 的左右链存储结构，并实现 BST 插入（建立）、删除、查找和排序算法。
2．实现折半查找算法。
3．实验比较：设计并产生实验测试数据，考察比较两种查找方法的时间性能，
并与理论结果进行比较。以下具体做法可作为参考：
（1） 第 1 组测试数据： n=1024 个已排序的整数序列（如 0 至 2048 之间的奇数）；第 2 组测试数据：第 1 组测试数据的随机序列。
（2） 按上述两组序列的顺序作为输入顺序，分别建立 BST。 
（3） 编写程序计算所建的两棵BST的查找成功和查找失败的平均查找长度
（主要是改造 Search 算法，对“比较”进行计数），并与理论结果比较。
（4） 以上述 BST 的中序遍历序列作为折半查找的输入，编写程序分别计算
折半查找的查找成功和查找失败的平均查找长度，并与理论结果比较。
（5） 以上实验能否说明：就平均性能而言，BST 的查找与折半查找差不多，为什么？答：随机序列情况还好，若BST退化成单链，则其性能远不如折半查找 。 
*/
#include <stdio.h>      	/*****出错原因：(递归时)直接修改指针(T=T->lchld)，需要传入指针的地址 (例如：BST **T)--(*T)=(*T)->lchild ******/
#include <stdlib.h>
#include <time.h>

#define N 10  //1024太大，此处以10来测试 

typedef struct Tree{
	int data;
	struct Tree *lchild;
	struct Tree *rchild;
}BST;

typedef struct cell{//队列元素的型 
	float level;//层数
	BST *tree;
	struct cell *next;
}celltype;

typedef struct queue{//队列 
	celltype *front;
	celltype *rear;
}Queue;

void Makenull(Queue *Q);
int isEmpty(Queue Q);
celltype *Front(Queue Q);
void EnQueue(float l,BST *T,Queue *Q);
void DeQueue(Queue *Q);

void buildBST(int num[],BST **T);//BST建立
void insertBST(int key,BST **T);//BST插入                   //要改变指针，需传入指针的地址 
int deletemin(BST **T);//删除最小元素---右子树的最左结点 
void deleteBST(int key,BST **T);//BST删除
float searchBST(int key,BST *T,float count);//BST查找
float searchfail(BST *T);//计算查找失败的平均查找长度ASL
 
void in_order(BST *T);//中序遍历 
void buildhalfBT(int num[],int start,int end,BST **T);//折半查找判定树建立

void menu();//菜单 
void menu1();//

int main(){
	int i,j=1,a,temp,y,x,z;
	int num[N],numrand[N];//1024个奇数的已排序序列 
	for(i=0;i<N;i++){
		num[i]=j;
		numrand[i]=j;
		j+=2;
	}
	for(i=0;i<N;i++){
		srand((unsigned)time(NULL));
		a=rand()%(N-i)+i;
		temp=numrand[i];
		numrand[i]=numrand[a];
		numrand[a]=temp;
	}//1024个奇数的随机序列 (0-2048)
	while(1){
		BST *T;
		T=NULL;
		float count=0,sum=0;
		menu();
		printf("请输入你的选择："); 
		scanf("%d",&y);
		switch(y){
			case 1: buildBST(num,&T);//BST建立 
					printf("\nBST已建立！(顺序)");
					printf("\n中序序列为：");
					in_order(T);//中序遍历
					for(i=0;i<N;i++)
						sum=sum+searchBST(num[i],T,count);
					sum=sum/N;
					printf("\n顺序BST查找成功的平均查找长度ASL=%f",sum);
					printf("\n顺序BST查找失败的平均查找长度ASL=%f",searchfail(T));
					printf("\n");
					while(1){
						menu1();
						printf("请输入你的选择："); 
						scanf("%d",&z);
						switch(z){
							case 1: printf("请输入要插入的数据：");
									scanf("%d",&x);
									insertBST(x,&T);//BST插入 
									printf("\n中序序列为：");
									in_order(T);//中序遍历
									break;
							case 2: printf("请输入要删除的数据：");
									scanf("%d",&x);
									deleteBST(x,&T);//BST删除 
									printf("\n中序序列为：");
									in_order(T);//中序遍历
									break;
							case 3: printf("请输入要查找的数据：");
									scanf("%d",&x);
									if(searchBST(x,T,count)!=-1)//BST查找 
										printf("查找成功！");
									printf("\n中序序列为：");
									in_order(T);//中序遍历
									break;
							case 4: printf("退出此菜单！！");
									break;
							default:printf("非法选择，请重新输入！！！");
									break;
						}
						if(z==4)
							break;
					}
					break;
			case 2: buildBST(numrand,&T);//BST建立 
					printf("\nBST已建立！(随机)");
					printf("\n中序序列为：");
					in_order(T);//中序遍历
					for(i=0;i<N;i++)
						sum=sum+searchBST(numrand[i],T,count);
					sum=sum/N;
					printf("\n随机BST查找成功的平均查找长度ASL=%f",sum);
					printf("\n随机BST查找失败的平均查找长度ASL=%f",searchfail(T));
					printf("\n");
					while(1){
						menu1();
						printf("请输入你的选择："); 
						scanf("%d",&z);
						switch(z){
							case 1: printf("请输入要插入的数据：");
									scanf("%d",&x);
									insertBST(x,&T);//BST插入 
									printf("\n中序序列为：");
									in_order(T);//中序遍历
									break;
							case 2: printf("请输入要删除的数据：");
									scanf("%d",&x);
									deleteBST(x,&T);//BST删除 
									printf("\n中序序列为：");
									in_order(T);//中序遍历
									break;
							case 3: printf("请输入要查找的数据：");
									scanf("%d",&x);
									if(searchBST(x,T,count)!=-1)//BST查找 
										printf("查找成功！");
									printf("\n中序序列为：");
									in_order(T);//中序遍历
									break;
							case 4: printf("退出此菜单！！");
									break;
							default:printf("非法选择，请重新输入！！！");
									break;
						}
						if(z==4)
							break;
					}
					break;
			case 3: buildhalfBT(num,0,N-1,&T);//折半查找判定树 
					printf("\n折半查找判定树已建立！");
					printf("\n中序序列为：");
					in_order(T);//中序遍历
					for(i=0;i<N;i++)
						sum=sum+searchBST(num[i],T,count);
					sum=sum/N;
					printf("\n折半查找判定树查找成功的平均查找长度ASL=%f",sum);
					printf("\n折半查找判定树查找失败的平均查找长度ASL=%f",searchfail(T));
					printf("\n是否要查找数据？ 1.是   2.否 ");
					printf("\n请输入选择：");
					scanf("%d",&y);
					if(y==1){
						printf("\n请输入要查找的数据：");
						scanf("%d",&x);
						if(searchBST(x,T,count)!=-1)//BST查找 
							printf("查找成功！");
					}
					break;
			case 4: printf("已退出！！！");
					exit(0);
					break;
			default:printf("非法选择，请重新输入！！！");
					break;
		}
	}
	return 0;
}

void Makenull(Queue *Q){
	celltype *t;
	t=(celltype *)malloc(sizeof(celltype));
	t->next=NULL;
	(*Q).front=t;
	(*Q).rear=(*Q).front;
}

int isEmpty(Queue Q){
	if(Q.front==Q.rear)
		return 1;//空
	else
		return 0;//非空 
}

celltype *Front(Queue Q){
	if(!isEmpty(Q))
		return Q.front->next;
	else
		printf("队列为空！");
}

void EnQueue(float l,BST *T,Queue *Q){
	celltype *t;
	t=(celltype *)malloc(sizeof(celltype));
	t->level=l;
	t->tree=T;
	t->next=NULL;
	(*Q).rear->next=t;
	(*Q).rear=t;
}

void DeQueue(Queue *Q){
	celltype *t;
	t=(*Q).front->next;
	(*Q).front->next=t->next;
	free(t);
	if((*Q).front->next==NULL)
		(*Q).rear=(*Q).front;
}

void menu(){
	printf("\n\t-----------------------------\n");
	printf("\t|            菜单           |\n");
	printf("\t|1.建立BST--顺序序列        |\n");
	printf("\t|2.建立BST--随机序列        |\n");
	printf("\t|3.折半查找                 |\n");
	printf("\t|4.退出！！                 |\n");
	printf("\t-----------------------------\n");
}

void menu1(){
	printf("\n\t------------------\n");
	printf("\t|      菜单      |\n");
	printf("\t|1.插入BST       |\n");
	printf("\t|2.删除BST       |\n");
	printf("\t|3.查找BST       |\n");
	printf("\t|4.退出！！      |\n");
	printf("\t------------------\n");
}
												/*****出错原因：直接修改指针，需要传入指针的地址 (例如：BST **T)******/
void buildBST(int num[],BST **T){//BST建立
	int i;
	for(i=0;i<N;i++)
		insertBST(num[i],T);
}

void insertBST(int key,BST **T){//BST插入
	BST *k;
	if((*T)==NULL){
		(*T)=(BST *)malloc(sizeof(BST));
		(*T)->data=key;
		(*T)->lchild=NULL;
		(*T)->rchild=NULL;
	}
	else if(key<(*T)->data)
		insertBST(key,&((*T)->lchild));//切记要传入指针的地址 
	else if(key>(*T)->data)
		insertBST(key,&((*T)->rchild));
	else if(key==(*T)->data)
		printf("此结点已存在，无需插入！\n");
}

int deletemin(BST **T){//删除最小元素---右子树的最左结点  //按照教材程序，在左右链直接继承时出现错误，即 T=T->lchild ,T=T->rchild会出现错误！！！！ 
	int temp;
	BST *p;
	if((*T)->lchild==NULL){
		temp=(*T)->data;
		p=(*T);
		(*T)=(*T)->rchild;
		free(p);
		return temp;
	}
	else
		return deletemin(&((*T)->lchild));
}
 
void deleteBST(int key,BST **T){//BST删除     //按照教材程序，在左右链直接继承时出现错误，即 T=T->lchild ,T=T->rchild会出现错误！！！！
	if((*T)!=NULL){
		if(key==(*T)->data){
			if((*T)->lchild==NULL)//如果左子树为空，右链直接继承 
				(*T)=(*T)->rchild;
			else if((*T)->rchild==NULL)//如果右子树为空，左链直接继承 
				(*T)=(*T)->lchild;
			else//如果有两棵子树，选择右子树的最左结点为继承结点 
				(*T)->data=deletemin(&((*T)->rchild));
		}
		else if(key<(*T)->data)
			deleteBST(key,&((*T)->lchild));
		else if(key>(*T)->data)
			deleteBST(key,&((*T)->rchild));
	}
	else
		printf("无此结点！\n"); 
}

float searchBST(int key,BST *T,float count){//BST查找
	if(T==NULL){
		printf("无此结点！\n"); 
		return -1;//没有找到 
	}
	else if(key==T->data){
		count++;
		return count;
	}
	else if(key>T->data){
		count++;
		return (searchBST(key,T->rchild,count));
	}
	else if(key<T->data){
		count++;
		return (searchBST(key,T->lchild,count));
	}
}
 
void in_order(BST *T){//中序遍历 --左根右 
	if(T!=NULL){
		in_order(T->lchild);
		printf("%d ",T->data);
		in_order(T->rchild);
	}
}

void buildhalfBT(int num[],int start,int end,BST **T){//建立折半查找判定树
	int i,mid,low,high;
	low=start;
	high=end;
	mid=(low+high)/2;
	if(low<=high){
		insertBST(num[mid],T);
		buildhalfBT(num,low,mid-1,T);
		buildhalfBT(num,mid+1,high,T);
	}
}

float searchfail(BST *T){//计算查找失败的平均查找长度ASL，利用队列，计算(左/右)子树为空的结点的层数和 ,除以N+1即得到答案 
	Queue Q;
	float sum=0;
	Makenull(&Q);
	EnQueue(1,T,&Q);
	while(!isEmpty(Q)){
		if(Front(Q)->tree->lchild!=NULL)
			EnQueue(Front(Q)->level+1,Front(Q)->tree->lchild,&Q);
		else
			sum=sum+Front(Q)->level;
		if(Front(Q)->tree->rchild!=NULL)
			EnQueue(Front(Q)->level+1,Front(Q)->tree->rchild,&Q);
		else
			sum=sum+Front(Q)->level;
		DeQueue(&Q);
	}
	sum=sum/(N+1);
	return sum;
}

