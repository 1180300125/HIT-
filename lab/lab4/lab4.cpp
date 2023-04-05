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
（5） 以上实验能否说明：就平均性能而言，BST 的查找与折半查找差不多，为什么？
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10  //1024太大，此处以10来测试 

typedef struct Tree{
	int data;
	struct Tree *lchild;
	struct Tree *rchild;
}BST;

void buildBST(int num[],BST *T);//BST建立
void insertBST(int key,BST *T);//BST插入
int deletemin(BST *T);//删除最小元素---右子树的最左结点 
void deleteBST(int key,BST *T);//BST删除
BST *searchBST(int key,BST *T);//BST查找
void in_order(BST *T);//中序遍历 
void halfsearch(int key,int start,int end,int ordernum[]);//折半查找

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
		menu();
		printf("请输入你的选择："); 
		scanf("%d",&y);
		switch(y){
			case 1: T=(BST *)malloc(sizeof(BST));
					T->data=num[0];
					T->lchild=NULL;
					T->rchild=NULL;
					buildBST(num,T);//BST建立 
					printf("\nBST已建立！(顺序)");
					printf("\n中序序列为：");
					in_order(T);//中序遍历
					printf("\n");
					while(1){
						menu1();
						printf("请输入你的选择："); 
						scanf("%d",&z);
						switch(z){
							case 1: printf("请输入要插入的数据：");
									scanf("%d",&x);
									insertBST(x,T);//BST插入 
									printf("\n中序序列为：");
									in_order(T);//中序遍历
									break;
							case 2: printf("请输入要删除的数据：");
									scanf("%d",&x);
									deleteBST(x,T);//BST删除 
									printf("\n中序序列为：");
									in_order(T);//中序遍历
									break;
							case 3: printf("请输入要查找的数据：");
									scanf("%d",&x);
									if(searchBST(x,T)!=NULL)//BST查找 
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
			case 2: T=(BST *)malloc(sizeof(BST));
					T->data=numrand[0];
					T->lchild=NULL;
					T->rchild=NULL;
					buildBST(numrand,T);//BST建立 
					printf("\nBST已建立！(随机)");
					printf("\n中序序列为：");
					in_order(T);//中序遍历
					printf("\n");
					while(1){
						menu1();
						int ordernum[N]={0};
						printf("请输入你的选择："); 
						scanf("%d",&z);
						switch(z){
							case 1: printf("请输入要插入的数据：");
									scanf("%d",&x);
									insertBST(x,T);//BST插入 
									printf("\n中序序列为：");
									in_order(T);//中序遍历
									break;
							case 2: printf("请输入要删除的数据：");
									scanf("%d",&x);
									deleteBST(x,T);//BST删除 
									printf("\n中序序列为：");
									in_order(T);//中序遍历
									break;
							case 3: printf("请输入要查找的数据：");
									scanf("%d",&x);
									if(searchBST(x,T)!=NULL)//BST查找 
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
			case 3: printf("请输入要查找的数据：");
					scanf("%d",&x);
					halfsearch(x,0,N-1,num);//折半查找 
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
void buildBST(int num[],BST *T){//BST建立
	int i;
	for(i=1;i<N;i++)
		insertBST(num[i],T);
}

void insertBST(int key,BST *T){//BST插入
	BST *k;
	if(T->data==0){
		T->data=key;
		T->lchild=NULL;
		T->rchild=NULL;
	}
	else if(key<T->data){					/*重要重要重要！！！！！！！！！！！！！！！！*/ 
		if(T->lchild==NULL){/********特别注意此处与教材不同，直接传值为NULL的指针会失效，无法形成左右链的链接，
							此处需提前malloc，给值为NULL的指针，然后data域赋特殊值0，然后以0值为判断依据，进行插入操作************/
			k=(BST *)malloc(sizeof(BST));
			k->data=0;
			T->lchild=k;
		}
		insertBST(key,T->lchild);
	}
	else if(key>T->data){					/*重要重要重要！！！！！！！！！！！！！！！！*/ 
		if(T->rchild==NULL){/********特别注意此处与教材不同，直接传值为NULL的指针会失效，无法形成左右链的链接，
							此处需提前malloc，给值为NULL的指针，然后data域赋特殊值0，然后以0值为判断依据，进行插入操作************/
			k=(BST *)malloc(sizeof(BST));
			k->data=0;
			T->rchild=k;
		}
		insertBST(key,T->rchild);
	}
	else if(key==T->data)
		printf("此结点已存在，无需插入！\n");
}

/*int deletemin(BST *T){//删除最小元素---右子树的最左结点  //按照教材程序，在左右链直接继承时出现错误，即 T=T->lchild ,T=T->rchild会出现错误！！！！ 
	int temp;
	BST *p;
	if(T->lchild==NULL){
		temp=T->data;
		p=T;
		T=T->rchild;
		free(p);
		return temp;
	}
	else
		return deletemin(T->lchild);
}
 
void deleteBST(int key,BST *T){//BST删除     //按照教材程序，在左右链直接继承时出现错误，即 T=T->lchild ,T=T->rchild会出现错误！！！！
	if(T!=NULL){
		if(key==T->data){
			if(T->lchild==NULL)//如果左子树为空，右链直接继承 
				T=T->rchild;
			else if(T->rchild==NULL)//如果右子树为空，左链直接继承 
				T=T->lchild;
			else//如果有两棵子树，选择右子树的最左结点为继承结点 
				T->data=deletemin(T->rchild);
		}
		else if(key<T->data)
			deleteBST(key,T->lchild);
		else if(key>T->data)
			deleteBST(key,T->rchild);
	}
	else
		printf("无此结点！\n"); 
}*/

int deletemin(BST *T){//删除最小元素---右子树的最左结点 
	int temp;
	BST *p;
	if(T->lchild->lchild==NULL){
		temp=T->lchild->data;
		p=T->lchild;
		T->lchild=p->rchild;
		free(p);
		return temp;
	}
	else
		return deletemin(T->lchild);
}
 
void deleteBST(int key,BST *T){//BST删除
	BST *p;
	if(T!=NULL){
		if(key==T->data){
			if(T->lchild==NULL){//如果左子树为空，右链直接继承 
				p=T;
				T=p->rchild;
				free(p);
			}
			else if(T->rchild==NULL){//如果右子树为空，左链直接继承 
				p=T;
				T=p->lchild;
				free(p);
			}
			else{//如果有两棵子树，选择右子树的最左结点为继承结点 
				if(T->rchild->lchild==NULL){
					p=T->rchild;
					T->data=p->data;
					T->rchild=p->rchild;
					free(p);
				}
				else
					T->data=deletemin(T->rchild);
			}
		}
		else if(key<T->data){
			if(key==T->lchild->data){
				if(T->lchild->lchild==NULL){//如果左子树为空，右链直接继承 
					p=T->lchild;
					T->lchild=p->rchild;
					free(p);
				}
				else if(T->lchild->rchild==NULL){//如果右子树为空，左链直接继承 
					p=T->lchild;
					T->lchild=p->lchild;
					free(p);
				}
				else{//如果有两棵子树，选择右子树的最左结点为继承结点 
					if(T->lchild->rchild->lchild==NULL){
						p=T->lchild->rchild;
						T->lchild->data=p->data;
						T->lchild->rchild=p->rchild;
						free(p);
					}
					else
						T->lchild->data=deletemin(T->lchild->rchild);
				}
			}
			else
				deleteBST(key,T->lchild);
		}
		else if(key>T->data){
			if(key==T->rchild->data){
				if(T->rchild->lchild==NULL){//如果左子树为空，右链直接继承 
					p=T->rchild;
					T->rchild=p->rchild;
					free(p);
				}
				else if(T->rchild->rchild==NULL){//如果右子树为空，左链直接继承 
					p=T->rchild;
					T->rchild=p->lchild;
					free(p);
				}
				else{//如果有两棵子树，选择右子树的最左结点为继承结点 
					if(T->rchild->rchild->lchild==NULL){
						p=T->rchild->rchild;
						T->rchild->data=p->data;
						T->rchild->rchild=p->rchild;
						free(p);
					}
					else
						T->rchild->data=deletemin(T->rchild->rchild);
				}
			}
			else
				deleteBST(key,T->rchild);
		}
	}
	else
		printf("无此结点！\n"); 
}

BST *searchBST(int key,BST *T){//BST查找
	if(T==NULL){
		printf("无此结点！\n"); 
		return NULL;//没有找到 
	}
	else if(key==T->data)
		return T;
	else if(key>T->data)
		return (searchBST(key,T->rchild));
	else if(key<T->data)
		return (searchBST(key,T->lchild));
}
 
void in_order(BST *T){//中序遍历 --左根右 
	if(T!=NULL){
		in_order(T->lchild);
		printf("%d ",T->data);
		in_order(T->rchild);
	}
}

void halfsearch(int key,int start,int end,int ordernum[]){//折半查找
	int low,high,mid;
	low=start;
	high=end;
	mid=(low+high)/2;
	if(start<end){
		if(key==ordernum[mid])
			printf("查找成功！\n");
		else if(key<ordernum[mid])
			halfsearch(key,low,mid,ordernum);
		else
			halfsearch(key,mid+1,high,ordernum);
	}
	else
		printf("无此元素！\n");
}

