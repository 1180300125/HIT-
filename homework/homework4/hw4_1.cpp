/*作业题目 1：AVL 树的设计与实现
 AVL 树 AVL 树作为一种基本的查找（搜索）结构，是一种自平衡二叉查找
树。在 AVL 树中任何结点的两个子树的高度最大差为 1，所以它也被称为高度
平衡树。插入和删除操作可能需要通过一次或多次旋转操作来重新平衡这棵树。
AVL 树得名于它的发明者 G. M. Adelson-Velsky 和 E. M. Landis，他们在 1962 年
的论文《An algorithm for the organization of information》中发表了它。
本次作业要求设计 AVL 树存储结构，并实现 AVL 树建立（插入）、删除和查找算法，
并反映插入和删除操作算法的各种旋转变化。
作业要求：
1．设计 AVL 的左右链存储结构；
2．实现 AVL 左右链存储结构上的插入（建立）、删除、查找和排序算法。
3．测试数据以文件形式保存，能反映插入和删除操作的四种旋转，并输出相应结果。*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct avltree{
	int bf;//平衡因子，该结点左子树与右子树的高度之差 ，-1,0,1 
	int data;
	struct avltree *lchild;
	struct avltree *rchild;
}AVL;

void AVLBuild(int *num,int n,AVL **T,int *unbalanced);//建立 
void AVLInsert(int d,AVL **T,int *unbalanced);//插入 
void deleteAVL(int d,AVL **T,int *unbalanced);//删除 
void AVLSearch(int d,AVL *T);//查找 
void In_order(AVL *T);//中序遍历

void LeftRotation(AVL **T,int *unbalanced);//LL旋转，LR旋转 
void RightRotation(AVL **T,int *unbalanced);//RR旋转，RL旋转 

void menu();
void menu1();

int main(){
	FILE *fp;
	int i=0,n=0,j=0,k=0,c=0,y;
	char list[500],s[10];
	fp=fopen("D:\\DevC++\\homework4\\4_1.txt","r");
	fgets(list,490,fp);
	fclose(fp);
	while(list[i]!='\0'){
		while(list[i]!=' ' && list[i]!='\0')
			i++;
		n++;
		if(list[i]!='\0')
			i++;
	}
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
	while(1){
		int x,unbalanced=0;
		AVL *T;
		T=NULL;
		menu();
		printf("请输入你的选择：");
		scanf("%d",&y);
		switch(y){
			case 1: AVLBuild(num,n,&T,&unbalanced);
					printf("AVL树已建立！");
					printf("\n中序遍历序列为：");
					In_order(T);
					while(1){
						int m;
						unbalanced=0;
						menu1();
						printf("请输入你的选择：");
						scanf("%d",&x);
						switch(x){
							case 1: printf("请输入要插入的数据：");
									scanf("%d",&m);
									AVLInsert(m,&T,&unbalanced);
									printf("\n中序遍历序列为：");
									In_order(T);
									break;
							case 2: printf("请输入要删除的数据：");
									scanf("%d",&m);
									deleteAVL(m,&T,&unbalanced);
									printf("\n中序遍历序列为：");
									In_order(T);
									break;
							case 3: printf("请输入要查找的数据：");
									scanf("%d",&m);
									AVLSearch(m,T);
									printf("\n中序遍历序列为：");
									In_order(T);
									break;
							case 4: printf("已退出！");
									break;
							default:printf("非法选择，请重新输入！");
									break;
						}
						if(x==4)
							break;
					}
					break;
			case 2: printf("已退出！");
					//exit(0);
					break;
			default:printf("非法选择，请重新输入！");
					break;
		}
		if(y==2)
			break;
	}
	return 0;
}

void menu(){
	printf("\n\t--------------------\n");
	printf("\t|       菜单       |\n");
	printf("\t|1.建立AVL树       |\n");
	printf("\t|2.退出！          |\n");
	printf("\t--------------------\n");
}

void menu1(){
	printf("\n\t---------------\n");
	printf("\t|     菜单    |\n");
	printf("\t|1.插入       |\n");
	printf("\t|2.删除       |\n");
	printf("\t|3.查找       |\n");
	printf("\t|4.退出！     |\n");
	printf("\t---------------\n");
}

void AVLBuild(int *num,int n,AVL **T,int *unbalanced){//建立 
	int i;
	for(i=0;i<n;i++){
		*unbalanced=0;
		AVLInsert(num[i],T,unbalanced);
	}
}
 
void AVLInsert(int d,AVL **T,int *unbalanced){//插入 
	if((*T)==NULL){
		(*T)=(AVL *)malloc(sizeof(AVL));
		*unbalanced=1;
		(*T)->bf=0;
		(*T)->data=d;
		(*T)->lchild=NULL;
		(*T)->rchild=NULL;
	}
	else if(d>(*T)->data){
		AVLInsert(d,&((*T)->rchild),unbalanced);
		if(*unbalanced){
			switch((*T)->bf){
				case 1: (*T)->bf=0;
						*unbalanced=0;
						break;
				case 0: (*T)->bf=-1;
						break;
				case -1:RightRotation(T,unbalanced);
						break;
			}
		}
	}
	else if(d<(*T)->data){
		AVLInsert(d,&((*T)->lchild),unbalanced);
		if(*unbalanced){
			switch((*T)->bf){
				case -1:(*T)->bf=0; 
						*unbalanced=0;// 层数/高度不变 
						break;
				case 0: (*T)->bf=1;// 层数/高度改变 
						break;
				case 1: LeftRotation(T,unbalanced);
						break;
			}
		}
	}
}

void deleteAVL(int d,AVL **T,int *unbalanced){
	AVL *p;
	int temp;
	if((*T)==NULL)
		printf("无此数据！");
	else if(d==(*T)->data){
		if((*T)->rchild==NULL){
			p=(*T);
			(*T)=(*T)->lchild;
			free(p);
			*unbalanced=1;
		}
		else if((*T)->lchild==NULL){
			p=(*T);
			(*T)=(*T)->rchild;
			free(p);
			*unbalanced=1;
		}
		else{
			p=(*T)->rchild;
			while(p->lchild!=NULL)//右子树的最左结点 
				p=p->lchild;
			temp=p->data;
			deleteAVL(temp,T,unbalanced);//相当于删除右子树的最左结点，再把原节点赋值为删除的继承结点值 
			(*T)->data=temp;
		}
	}
	else if(d<(*T)->data){
		deleteAVL(d,&((*T)->lchild),unbalanced);
		if(*unbalanced){
			switch((*T)->bf){
				case 1: (*T)->bf=0;//层数改变--高度改变，需递归到上层进行修改 
						break;
				case 0: (*T)->bf=-1;//层数未改变 
						*unbalanced=0;
						break;
				case -1:LeftRotation(T,unbalanced);
						break;
			}
		}
	}
	else if(d>(*T)->data){
		deleteAVL(d,&((*T)->rchild),unbalanced);
		if(*unbalanced){
			switch((*T)->bf){
				case -1:(*T)->bf=0;
						break;
				case 0: (*T)->bf=1;
						*unbalanced=0;
						break;
				case 1: RightRotation(T,unbalanced);
						break;
			}
		}
	}
}

void AVLSearch(int d,AVL *T){//查找 
	if(T==NULL)
		printf("无此数据！");
	else if(d==T->data)
		printf("查找成功！");
	else if(d<T->data)
		AVLSearch(d,T->lchild);
	else if(d>T->data)
		AVLSearch(d,T->rchild);
}
 
void In_order(AVL *T){//中序遍历
	if(T!=NULL){
		In_order(T->lchild);
		printf("%d(%d) ",T->data,T->bf);
		In_order(T->rchild);
	}
}

void LeftRotation(AVL **T,int *unbalanced){//LL旋转，LR旋转 
	AVL *lc,*gc;
	lc=(*T)->lchild;
	if(lc->bf==1){//LL
		(*T)->lchild=lc->rchild;
		lc->rchild=(*T);
		(*T)->bf=0;
		lc->bf=0;//++
		(*T)=lc; 
	}
	else{//LR
		gc=lc->rchild;
		lc->rchild=gc->lchild;
		(*T)->lchild=gc->rchild;
		gc->lchild=lc;
		gc->rchild=(*T);
		switch(gc->bf){
			case 1: lc->bf=0;
					(*T)->bf=-1;
					break;
			case 0: lc->bf=0;
					(*T)->bf=0;
					break;
			case -1:lc->bf=1;
					(*T)->bf=0;
					break;		
		}
		gc->bf=0;
		(*T)=gc;
	}
	*unbalanced=0;
}
 
void RightRotation(AVL **T,int *unbalanced){//RR旋转，RL旋转
	AVL *rc,*gc;
	rc=(*T)->rchild;
	if(rc->bf==-1){//RR
		(*T)->rchild=rc->lchild;
		rc->lchild=(*T);
		(*T)->bf=0;
		rc->bf=0;//++
		(*T)=rc; 
	}
	else{//RL
		gc=rc->lchild;
		rc->lchild=gc->rchild;
		(*T)->rchild=gc->lchild;
		gc->lchild=(*T);
		gc->rchild=rc;
		switch(gc->bf){
			case 1: rc->bf=-1;
					(*T)->bf=0;
					break;
			case 0: rc->bf=0;
					(*T)->bf=0;
					break;
			case -1:rc->bf=0;
					(*T)->bf=1;
					break;		
		}
		gc->bf=0;
		(*T)=gc;
	}
	*unbalanced=0;
} 

