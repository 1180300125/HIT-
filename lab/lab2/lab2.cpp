//数据结构实验二---二叉树
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct BTree{//二叉树 
	char data;
	BTree *lchild;
	BTree *rchild;
}BTree;

typedef struct Stack{//栈 
	BTree *addr;
	Stack *next;
}Stack;

typedef struct celltype{//队列中每个结点的类型 
	BTree *addr;
	celltype *next;
}celltype;

typedef struct Queue{//队列的型 
	celltype *front;
	celltype *rear;
}Queue;

void sMakenull();			//将栈置空 
int s_isEmpty(Stack *S);	//判断栈是否为空 
void Push(BTree *T,Stack *S);//压入栈 
BTree *Top(Stack *S);		//返回栈顶元素 
void Pop(Stack *S);			//删除栈顶 

void qMakenull(Queue Q);	//将队列置空 
int q_isEmpty(Queue Q);		//判断队列是否为空 
BTree *Front(Queue Q);		//返回队首元素 
Queue EnQueue(BTree *T,Queue Q);//在队尾插入元素 
Queue DeQueue(Queue Q);		//删除队首元素 

void btEmpty();				//建立空二叉树 
int btIsEmpty(BTree *T);	//判断二叉树是否为空  
BTree *create(BTree *T,char c);//建立新二叉树
char Data(BTree *T);		//返回二叉树根结点的数据域 

int z=0;//全局变量 
BTree *build_dg(BTree *T,char *a);//递归函数 
BTree *creatbt_dg(char *a);		//创建二叉树--递归 ,文件读取 
BTree *creatbt_fdg(char *a);	//创建二叉树--非递归 ，文件读取 
void printBTree(BTree *a);		//显示二叉树 
void pre_order_dg(BTree *a);	//先序遍历--递归 
void pre_order_fdg(BTree *T);	//先序遍历--非递归--    利用栈实现 
void in_order_dg(BTree *a);		//中序遍历--递归 
void in_order_fdg(BTree *T);	//中序遍历--非递归 
void post_order_dg(BTree *a);	//后序遍历--递归 
void post_order_fdg(BTree *T);	//后序遍历--非递归 
void c_order(BTree *a);			//层序遍历--            利用队列实现**** 
void is_completeBTree(BTree *T);	//判断是否为完全二叉树 
void calculation_BT_width(BTree *T);//计算二叉树的宽度 

void menu();//菜单
void freeallS(Stack *S);	//free栈链表 
void freeallQ(Queue Q);		//free队列链表 
void freeallBT(BTree *T);	//free二叉树链表 

int main(){
	int m;
	while(1){
		BTree *t;
		char filename[50];
		strcpy(filename,"D:\\DevC++\\lab2\\bt3.txt");//bt1，bt2，bt3共三个测试文件 
		menu();
		printf("请输入你的选择：");
		scanf("%d",&m);
		switch(m){
			case 1: t=creatbt_dg(filename); //*-*
					printBTree(t);
					break;
			case 2: t=creatbt_fdg(filename);//*-*
					printBTree(t);
					break;
			case 3: t=creatbt_fdg(filename);//*-*
					printf("先序遍历序列(递归)为：");
					pre_order_dg(t);
					break;
			case 4: t=creatbt_fdg(filename);//*-*
					printf("先序遍历序列(非递归)为：");
					pre_order_fdg(t);
					break;
			case 5: t=creatbt_fdg(filename);//*-*
					printf("中序遍历序列(递归)为：");
					in_order_dg(t);
					break;
			case 6: t=creatbt_fdg(filename);//*-*
					printf("中序遍历序列(非递归)为：");//修改了原二叉树 
					in_order_fdg(t);
					break;
			case 7: t=creatbt_fdg(filename);//*-*
					printf("后序遍历序列(递归)为：");
					post_order_dg(t);
					break;
			case 8: t=creatbt_fdg(filename);//*-*
					printf("后序遍历序列(非递归)为：");//修改了原二叉树 
					post_order_fdg(t);
					break;
			case 9: t=creatbt_fdg(filename);//*-*
					c_order(t);
					break;
			case 10:t=creatbt_fdg(filename);//*-*
					is_completeBTree(t);
					break;
			case 11:t=creatbt_fdg(filename);//*-*
					calculation_BT_width(t);
					break;
			case 12:printf("已退出！！！");//*-*
					exit(0);
			default:printf("非法输入！！请重新输入！！");//*-*
					break;
		} 
	}
	return 0;
} 

void menu(){//菜单
	printf("\n\t-------------------------------\n");
	printf("\t|1.递归--建立二叉树           |\n");
	printf("\t|2.非递归--建立二叉树         |\n");
	printf("\t|3.递归--先序遍历             |\n");
	printf("\t|4.非递归--先序遍历           |\n");
	printf("\t|5.递归--中序遍历             |\n");
	printf("\t|6.非递归--中序遍历           |\n");
	printf("\t|7.递归--后序遍历             |\n");
	printf("\t|8.非递归--后序遍历           |\n");
	printf("\t|9.层序遍历                   |\n");
	printf("\t|10.判断是否为完全二叉树      |\n");
	printf("\t|11.计算二叉树的宽度          |\n");
	printf("\t|12.退出                      |\n");
	printf("\t-------------------------------\n");
}

/**************栈操作**************/
void sMakenull(){//将栈置空 ,(初始化栈)
	Stack *S;
	S=(Stack *)malloc(sizeof(Stack));
	S->next=NULL;
}

int s_isEmpty(Stack *S){//判断栈是否为空 
	if(S->next==NULL)
		return 1;//空 
	else
		return 0;//非空 
}

void Push(BTree *T,Stack *S){//压入栈 
	Stack *p;
	p=(Stack *)malloc(sizeof(Stack));
	p->addr=T;
	p->next = S->next;
	S->next=p;
}

BTree *Top(Stack *S){//返回栈顶元素 
	if(S->next!=NULL)
		return S->next->addr;
	else
		return NULL;
}

void Pop(Stack *S){//删除栈顶 
	Stack *p;
	if(S->next!=NULL){
		p=S->next;
		S->next=p->next;
		free(p);
	}
}

/**************队列操作***************/
void qMakenull(Queue Q){//将队列置空 
	Q.front=(celltype *)malloc(sizeof(celltype));//表头 
	Q.front->next=NULL;//结点的next域为空
	Q.rear=Q.front; 
}

int q_isEmpty(Queue Q){//判断队列是否为空 
	if(Q.front==Q.rear)
		return 1;//空 
	else
		return 0;//非空 
}

BTree *Front(Queue Q){//返回队首元素 
	if(q_isEmpty(Q))
		return NULL;
	else
		return Q.front->next->addr;
}

Queue EnQueue(BTree *T,Queue Q){//在队尾插入元素 
	celltype *p;
	p=(celltype *)malloc(sizeof(celltype));
	p->addr=T;
	Q.rear->next=p;
	Q.rear=p;
	Q.rear->next=NULL;
	return Q;
}

Queue DeQueue(Queue Q){//删除队首元素
	celltype *p;
	if(q_isEmpty(Q))
		printf("队列为空！");
	else{
		p=Q.front->next;
		Q.front->next=p->next;
		free(p);
		if(Q.front->next==NULL)
			Q.rear=Q.front;
	}
	return Q;
}

/************二叉树操作************/
void btEmpty(){//建立空二叉树 
	BTree *T;
	T=(BTree *)malloc(sizeof(BTree));
	T->data=NULL;
	T->lchild=NULL;
	T->rchild=NULL;
}

int btIsEmpty(BTree *T){//判断二叉树是否为空 
	if(T->data=='@')
		return 1;
	else
		return 0;
}

BTree *create(BTree *T,char c){
	BTree *ltree,*rtree;
	ltree=(BTree *)malloc(sizeof(BTree));
	rtree=(BTree *)malloc(sizeof(BTree));
	T->data=c;
	T->lchild=ltree;
	T->rchild=rtree;
	return T;
}

char Data(BTree *T){//返回二叉树根结点的数据域
	if(T->data!=NULL)
		return T->data;
	else
		return NULL;
}

/**************核心实现函数***************/
BTree *build_dg(BTree *T,char *a){
	BTree *p;
	if(a[z]!='\0'){
		if(a[z]=='#'){
			T->data='@';
			T->lchild=NULL;
			T->rchild=NULL;
			return T;
		}
		T=create(T,a[z]);
		z++;
		p=build_dg(T->lchild,a);
		z++;
		p=build_dg(T->rchild,a);
	}
	return T;
}

BTree *creatbt_dg(char *a){//创建二叉树--递归 
	FILE *fp;
	BTree *T,*head;
	head=(BTree *)malloc(sizeof(BTree));
	T=head;
	char c,d[100];
	fp=fopen(a,"r");
	fscanf(fp,"%s",d);
	fclose(fp);
	
	T=build_dg(T,d);
	return head;
}

BTree *creatbt_fdg(char *a){//创建二叉树--非递归 ,此方法比较浪费空间 
	FILE *fp;
	BTree *p,*T,*head,*ltree,*rtree,*q;
	Stack *S;
	char c;
	fp=fopen(a,"r");
	T=(BTree *)malloc(sizeof(BTree));
	head=T;
	fscanf(fp,"%c",&c);
	S=(Stack *)malloc(sizeof(Stack));
	S->next=NULL;
	while(!feof(fp)){
		if(c=='#'){//无分支 
			T->data='@';
			T->lchild=NULL;
			T->rchild=NULL;
			if(!s_isEmpty(S)){
				T=Top(S);
				Pop(S);
			}
		}
		else{
			T=create(T,c);
			Push(T->rchild,S);
			Push(T->lchild,S);
			p=T;
			if(!s_isEmpty(S)){
				T=Top(S);
				Pop(S);
			}
		}
		fscanf(fp,"%c",&c);
	}
	fclose(fp);
	return head;
}

void printBTree(BTree *a){//显示二叉树 ,为了美观，限定二叉树不超过4层，且最后一层叶结点最好不大于2个且靠左 
	Queue Q;
	int i=0,lflag=0,rflag=0,ceng[50];
	//qMakenull(Q);
	Q.front=(celltype *)malloc(sizeof(celltype));//表头 
	Q.front->next=NULL;//结点的next域为空
	Q.rear=Q.front; 
	if(a!=NULL){
		Q=EnQueue(a,Q);
	}
	printf("二叉树详细结构如下：\n");
	while(!q_isEmpty(Q)){
		if(i==0){
			printf("\n		      ");
			printf("%c",Data(Front(Q)));
		}
		if(i==1){
			if(lflag==1 && rflag==1){
				printf("\n		    ");printf("/");printf("   ");printf("\\");
				printf("\n		   ");printf("%c",Data(Front(Q)));
				lflag=0;rflag=0;ceng[0]=11;//0的左右子树都有 
			}
			else if(lflag==1 && rflag==0){
				printf("\n		    ");printf("/");
				printf("\n		   ");printf("%c",Data(Front(Q)));
				lflag=0;ceng[0]=10;//0只有左子树 
			}
			else if(lflag==0 && rflag==1){
			}
			else{	
			}
		}
		if(i==2){
			if(ceng[0]==11){
				printf("     ");printf("%c",Data(Front(Q)));
			}
			if(lflag==1 && rflag==1){
				printf("\n		  ");printf("/");printf(" ");printf("\\");
				lflag=0;rflag=0;ceng[1]=11;//1的左右子树都有 
			}
			else if(lflag==1 && rflag==0){
			}
			else if(lflag==0 && rflag==1){
			}
			else{
			}
			if(ceng[0]==10){
				printf("\n		 ");printf("%c",Data(Front(Q)));
			}
		}
		if(i==3){
			if(lflag==1 && rflag==1){
			}
			else if(lflag==1 && rflag==0){//2只有左子树 
				printf("   ");printf("/");
				lflag=0;ceng[2]=10;
			}
			else if(lflag==0 && rflag==1){//第2个数据只有右子树 
				ceng[2]=1;rflag=0; 
			}
			else{//2没有左右子树 
				ceng[2]=0;
			}
			if(ceng[0]!=10){
				printf("\n		 ");printf("%c",Data(Front(Q)));
			}
			if(ceng[0]==10){
				printf("   ");printf("%c",Data(Front(Q)));
			}
		}
		if(i==4){
			if(lflag==1 && rflag==1){
			}
			else if(lflag==1 && rflag==0){//3只有左子树 
				lflag=0;ceng[3]=10; 
			}
			else if(lflag==0 && rflag==1){
			}
			else{//3没有子树 
				ceng[3]=0;
			}
			if(ceng[0]==11){
				printf("   ");printf("%c",Data(Front(Q)));
			}
			else{
				if(ceng[2]==1){
					printf("\n		 ");printf(" ");printf("\\");
					printf("\n	        ");printf("   ");printf("%c",Data(Front(Q)));
				}
				if(ceng[2]==10){
				}
				if(ceng[2]==11){
				}
			}
		}
		if(i==5){
			if(lflag==1 && rflag==1){
			}
			else if(lflag==1 && rflag==0){
			}
			else if(lflag==0 && rflag==1){
			}
			else{//4没有子树 
				ceng[4]=0;
			}
			if(ceng[2]==11 || ceng[2]==10){
				printf(" ");printf("%c",Data(Front(Q)));
			}
			if(ceng[2]==1){
				printf("  ");printf("   ");printf("%c",Data(Front(Q)));
			}
			if(ceng[2]==0){
				if(ceng[3]==10){
					printf("\n		");printf("/");
					printf("\n	       ");printf("%c",Data(Front(Q)));
				}
				if(ceng[3]==11){
					printf("\n		");printf("/");printf(" ");printf("\\");
					printf("\n	       ");printf("%c",Data(Front(Q)));
				}
			}
		}
		if(Q.front->next->addr->lchild->data!='@'){//如果有左子树 
			Q=EnQueue(Q.front->next->addr->lchild,Q);
			lflag=1;
		}
		if(Q.front->next->addr->rchild->data!='@'){//如果有右子树 
			Q=EnQueue(Q.front->next->addr->rchild,Q);
			rflag=1;
		}
		Q=DeQueue(Q);
		i++;
	}
}

void pre_order_dg(BTree *a){//先序遍历--递归 
	if(a->data!='@'){
		printf("%c ",Data(a));
		pre_order_dg(a->lchild);
		pre_order_dg(a->rchild);
	}
}

void pre_order_fdg(BTree *T){//先序遍历--非递归 
	Stack *S;
	S=(Stack *)malloc(sizeof(Stack));
	S->next=NULL;
	if(!btIsEmpty(T)){
		Push(T,S);
		T=Top(S);
		Pop(S);
		printf("%c ",Data(T));
	}
	while(1){
		if(T->rchild->data!='@'){
			Push(T->rchild,S);
		}
		if(T->lchild->data!='@'){
			Push(T->lchild,S);
		}
		if(!s_isEmpty(S)){
			T=Top(S);
			Pop(S);
		}
		else
			break;
		printf("%c ",Data(T));
	}
}

void in_order_dg(BTree *a){//中序遍历--递归 
	if(a->data!='@'){
		in_order_dg(a->lchild);
		printf("%c ",Data(a));
		in_order_dg(a->rchild);
	}
}

void in_order_fdg(BTree *T){//中序遍历--非递归 
	Stack *S;
	S=(Stack *)malloc(sizeof(Stack));
	S->next=NULL;
	if(!btIsEmpty(T)){
		Push(T,S);
	}
	while(1){
		if(T->lchild->data!='@'){
			Push(T->lchild,S);
			T=T->lchild;
		}
		else{
			if(T->lchild->data=='@' && T->rchild->data=='@'){
				T=Top(S);Pop(S);printf("%c ",Data(T));
				T->data='@';
				if(!s_isEmpty(S))
					T=Top(S);
			}
			if(T->lchild->data=='@' && T->rchild->data!='@'){
				T=Top(S);Pop(S);printf("%c ",Data(T));
				T->data='@';
				Push(T->rchild,S);
				T=Top(S);
			}
			if(s_isEmpty(S))
				break;
		}
	}
}

void post_order_dg(BTree *a){//后序遍历--递归 
	if(a->data!='@'){
		post_order_dg(a->lchild);
		post_order_dg(a->rchild);
		printf("%c ",Data(a));
	}
}

void post_order_fdg(BTree *T){//后序遍历--非递归 
	Stack *S;
	S=(Stack *)malloc(sizeof(Stack));
	S->next=NULL;
	if(!btIsEmpty(T)){
		Push(T,S);
	}
	while(1){
		if(T->lchild->data!='@'){
			Push(T->lchild,S);
			T=T->lchild;
		}
		else if(T->rchild->data!='@' && T->lchild->data=='@'){
			Push(T->rchild,S);
			T=T->rchild;
		}
		else if(T->lchild->data=='@' && T->rchild->data=='@'){
			if(!s_isEmpty(S)){
				T=Top(S);Pop(S);
				printf("%c ",Data(T));
				T->data='@';
			}
			if(!s_isEmpty(S)){
				T=Top(S);
			}
			else
				break;
		}
	}
}

void c_order(BTree *a){//层序遍历--使用队列 
	Queue Q;
	Q.front=(celltype *)malloc(sizeof(celltype));//表头 
	Q.front->next=NULL;//结点的next域为空
	Q.rear=Q.front; 
	if(a!=NULL){
		Q=EnQueue(a,Q);
	}
	printf("层序遍历的序列为：");
	while(!q_isEmpty(Q)){
		printf("%c ",Data(Front(Q)));
		if(Q.front->next->addr->lchild->data!='@'){
			Q=EnQueue(Q.front->next->addr->lchild,Q);
		}
		if(Q.front->next->addr->rchild->data!='@'){
			Q=EnQueue(Q.front->next->addr->rchild,Q);
		}
		Q=DeQueue(Q);
	}
}

void is_completeBTree(BTree *T){//判断是否为完全二叉树 
	Queue Q;
	celltype *p;
	char m[100];
	int i=0;
	p=(celltype *)malloc(sizeof(celltype));
	p->next=NULL;
	Q.front=p;
	Q.rear=Q.front;
	Q=EnQueue(T,Q);
	/*while(!q_isEmpty(Q)){
		m[i]=Front(Q)->data;
		i++;
		if(Front(Q)->lchild!=NULL)//有左子树 
			Q=EnQueue(Front(Q)->lchild,Q);
		if(Front(Q)->rchild!=NULL)//有右子树
			Q=EnQueue(Front(Q)->rchild,Q);
		Q=DeQueue(Q);
	}*/
	while(!q_isEmpty(Q)){
		m[i]=Data(Front(Q));
		i++;
		if(Q.front->next->addr->lchild!=NULL)
			Q=EnQueue(Q.front->next->addr->lchild,Q);
		if(Q.front->next->addr->rchild!=NULL)
			Q=EnQueue(Q.front->next->addr->rchild,Q);
		Q=DeQueue(Q);
	}
	m[i]='\0';
	for(i=0;;i++){
		if(m[i]=='@')
			break;
	}
	while(m[i]!='\0'){
		if(m[i]!='@'){
			printf("此二叉树不是完全二叉树！！！");
			i=0;
			break;
		}
		i++;
	}
	if(i!=0){
		printf("此二叉树是完全二叉树！！！");
	}
}

void calculation_BT_width(BTree *T){//计算二叉树的宽度 
	Queue Q[20];
	int i=0,count=0,max;
	Q[i].front=(celltype *)malloc(sizeof(celltype));
	Q[i].front->next=NULL;
	Q[i].rear=Q[i].front;
	Q[i]=EnQueue(T,Q[i]);
	max=1;
	while(1){
		Q[i+1].front=(celltype *)malloc(sizeof(celltype));
		Q[i+1].front->next=NULL;
		Q[i+1].rear=Q[i+1].front;
		while(!q_isEmpty(Q[i])){
			if(Front(Q[i])->lchild->data!='@'){//有左子树 
				Q[i+1]=EnQueue(Front(Q[i])->lchild,Q[i+1]);
				count++;
			}
			if(Front(Q[i])->rchild->data!='@'){//有右子树
				Q[i+1]=EnQueue(Front(Q[i])->rchild,Q[i+1]);
				count++;
			}
			Q[i]=DeQueue(Q[i]);
		}
		i++;
		if(max<count)
			max=count;
		count=0;
		if(q_isEmpty(Q[i+1]))
			break;
	}
	printf("二叉树的宽度为：%d",max);
}

void freeallS(Stack *S){//free栈链表 
	Stack *p;
	while(S->next!=NULL){
		p=S->next;
		free(S);
		S=p;
	}
	free(S);
}

void freeallQ(Queue Q){//free队列链表 
	
}
 
void freeallBT(BTree *T){//free二叉树链表

}

