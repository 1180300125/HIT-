//���ݽṹʵ���---������
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct BTree{//������ 
	char data;
	BTree *lchild;
	BTree *rchild;
}BTree;

typedef struct Stack{//ջ 
	BTree *addr;
	Stack *next;
}Stack;

typedef struct celltype{//������ÿ���������� 
	BTree *addr;
	celltype *next;
}celltype;

typedef struct Queue{//���е��� 
	celltype *front;
	celltype *rear;
}Queue;

void sMakenull();			//��ջ�ÿ� 
int s_isEmpty(Stack *S);	//�ж�ջ�Ƿ�Ϊ�� 
void Push(BTree *T,Stack *S);//ѹ��ջ 
BTree *Top(Stack *S);		//����ջ��Ԫ�� 
void Pop(Stack *S);			//ɾ��ջ�� 

void qMakenull(Queue Q);	//�������ÿ� 
int q_isEmpty(Queue Q);		//�ж϶����Ƿ�Ϊ�� 
BTree *Front(Queue Q);		//���ض���Ԫ�� 
Queue EnQueue(BTree *T,Queue Q);//�ڶ�β����Ԫ�� 
Queue DeQueue(Queue Q);		//ɾ������Ԫ�� 

void btEmpty();				//�����ն����� 
int btIsEmpty(BTree *T);	//�ж϶������Ƿ�Ϊ��  
BTree *create(BTree *T,char c);//�����¶�����
char Data(BTree *T);		//���ض����������������� 

int z=0;//ȫ�ֱ��� 
BTree *build_dg(BTree *T,char *a);//�ݹ麯�� 
BTree *creatbt_dg(char *a);		//����������--�ݹ� ,�ļ���ȡ 
BTree *creatbt_fdg(char *a);	//����������--�ǵݹ� ���ļ���ȡ 
void printBTree(BTree *a);		//��ʾ������ 
void pre_order_dg(BTree *a);	//�������--�ݹ� 
void pre_order_fdg(BTree *T);	//�������--�ǵݹ�--    ����ջʵ�� 
void in_order_dg(BTree *a);		//�������--�ݹ� 
void in_order_fdg(BTree *T);	//�������--�ǵݹ� 
void post_order_dg(BTree *a);	//�������--�ݹ� 
void post_order_fdg(BTree *T);	//�������--�ǵݹ� 
void c_order(BTree *a);			//�������--            ���ö���ʵ��**** 
void is_completeBTree(BTree *T);	//�ж��Ƿ�Ϊ��ȫ������ 
void calculation_BT_width(BTree *T);//����������Ŀ�� 

void menu();//�˵�
void freeallS(Stack *S);	//freeջ���� 
void freeallQ(Queue Q);		//free�������� 
void freeallBT(BTree *T);	//free���������� 

int main(){
	int m;
	while(1){
		BTree *t;
		char filename[50];
		strcpy(filename,"D:\\DevC++\\lab2\\bt3.txt");//bt1��bt2��bt3�����������ļ� 
		menu();
		printf("���������ѡ��");
		scanf("%d",&m);
		switch(m){
			case 1: t=creatbt_dg(filename); //*-*
					printBTree(t);
					break;
			case 2: t=creatbt_fdg(filename);//*-*
					printBTree(t);
					break;
			case 3: t=creatbt_fdg(filename);//*-*
					printf("�����������(�ݹ�)Ϊ��");
					pre_order_dg(t);
					break;
			case 4: t=creatbt_fdg(filename);//*-*
					printf("�����������(�ǵݹ�)Ϊ��");
					pre_order_fdg(t);
					break;
			case 5: t=creatbt_fdg(filename);//*-*
					printf("�����������(�ݹ�)Ϊ��");
					in_order_dg(t);
					break;
			case 6: t=creatbt_fdg(filename);//*-*
					printf("�����������(�ǵݹ�)Ϊ��");//�޸���ԭ������ 
					in_order_fdg(t);
					break;
			case 7: t=creatbt_fdg(filename);//*-*
					printf("�����������(�ݹ�)Ϊ��");
					post_order_dg(t);
					break;
			case 8: t=creatbt_fdg(filename);//*-*
					printf("�����������(�ǵݹ�)Ϊ��");//�޸���ԭ������ 
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
			case 12:printf("���˳�������");//*-*
					exit(0);
			default:printf("�Ƿ����룡�����������룡��");//*-*
					break;
		} 
	}
	return 0;
} 

void menu(){//�˵�
	printf("\n\t-------------------------------\n");
	printf("\t|1.�ݹ�--����������           |\n");
	printf("\t|2.�ǵݹ�--����������         |\n");
	printf("\t|3.�ݹ�--�������             |\n");
	printf("\t|4.�ǵݹ�--�������           |\n");
	printf("\t|5.�ݹ�--�������             |\n");
	printf("\t|6.�ǵݹ�--�������           |\n");
	printf("\t|7.�ݹ�--�������             |\n");
	printf("\t|8.�ǵݹ�--�������           |\n");
	printf("\t|9.�������                   |\n");
	printf("\t|10.�ж��Ƿ�Ϊ��ȫ������      |\n");
	printf("\t|11.����������Ŀ��          |\n");
	printf("\t|12.�˳�                      |\n");
	printf("\t-------------------------------\n");
}

/**************ջ����**************/
void sMakenull(){//��ջ�ÿ� ,(��ʼ��ջ)
	Stack *S;
	S=(Stack *)malloc(sizeof(Stack));
	S->next=NULL;
}

int s_isEmpty(Stack *S){//�ж�ջ�Ƿ�Ϊ�� 
	if(S->next==NULL)
		return 1;//�� 
	else
		return 0;//�ǿ� 
}

void Push(BTree *T,Stack *S){//ѹ��ջ 
	Stack *p;
	p=(Stack *)malloc(sizeof(Stack));
	p->addr=T;
	p->next = S->next;
	S->next=p;
}

BTree *Top(Stack *S){//����ջ��Ԫ�� 
	if(S->next!=NULL)
		return S->next->addr;
	else
		return NULL;
}

void Pop(Stack *S){//ɾ��ջ�� 
	Stack *p;
	if(S->next!=NULL){
		p=S->next;
		S->next=p->next;
		free(p);
	}
}

/**************���в���***************/
void qMakenull(Queue Q){//�������ÿ� 
	Q.front=(celltype *)malloc(sizeof(celltype));//��ͷ 
	Q.front->next=NULL;//����next��Ϊ��
	Q.rear=Q.front; 
}

int q_isEmpty(Queue Q){//�ж϶����Ƿ�Ϊ�� 
	if(Q.front==Q.rear)
		return 1;//�� 
	else
		return 0;//�ǿ� 
}

BTree *Front(Queue Q){//���ض���Ԫ�� 
	if(q_isEmpty(Q))
		return NULL;
	else
		return Q.front->next->addr;
}

Queue EnQueue(BTree *T,Queue Q){//�ڶ�β����Ԫ�� 
	celltype *p;
	p=(celltype *)malloc(sizeof(celltype));
	p->addr=T;
	Q.rear->next=p;
	Q.rear=p;
	Q.rear->next=NULL;
	return Q;
}

Queue DeQueue(Queue Q){//ɾ������Ԫ��
	celltype *p;
	if(q_isEmpty(Q))
		printf("����Ϊ�գ�");
	else{
		p=Q.front->next;
		Q.front->next=p->next;
		free(p);
		if(Q.front->next==NULL)
			Q.rear=Q.front;
	}
	return Q;
}

/************����������************/
void btEmpty(){//�����ն����� 
	BTree *T;
	T=(BTree *)malloc(sizeof(BTree));
	T->data=NULL;
	T->lchild=NULL;
	T->rchild=NULL;
}

int btIsEmpty(BTree *T){//�ж϶������Ƿ�Ϊ�� 
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

char Data(BTree *T){//���ض�����������������
	if(T->data!=NULL)
		return T->data;
	else
		return NULL;
}

/**************����ʵ�ֺ���***************/
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

BTree *creatbt_dg(char *a){//����������--�ݹ� 
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

BTree *creatbt_fdg(char *a){//����������--�ǵݹ� ,�˷����Ƚ��˷ѿռ� 
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
		if(c=='#'){//�޷�֧ 
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

void printBTree(BTree *a){//��ʾ������ ,Ϊ�����ۣ��޶�������������4�㣬�����һ��Ҷ�����ò�����2���ҿ��� 
	Queue Q;
	int i=0,lflag=0,rflag=0,ceng[50];
	//qMakenull(Q);
	Q.front=(celltype *)malloc(sizeof(celltype));//��ͷ 
	Q.front->next=NULL;//����next��Ϊ��
	Q.rear=Q.front; 
	if(a!=NULL){
		Q=EnQueue(a,Q);
	}
	printf("��������ϸ�ṹ���£�\n");
	while(!q_isEmpty(Q)){
		if(i==0){
			printf("\n		      ");
			printf("%c",Data(Front(Q)));
		}
		if(i==1){
			if(lflag==1 && rflag==1){
				printf("\n		    ");printf("/");printf("   ");printf("\\");
				printf("\n		   ");printf("%c",Data(Front(Q)));
				lflag=0;rflag=0;ceng[0]=11;//0�������������� 
			}
			else if(lflag==1 && rflag==0){
				printf("\n		    ");printf("/");
				printf("\n		   ");printf("%c",Data(Front(Q)));
				lflag=0;ceng[0]=10;//0ֻ�������� 
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
				lflag=0;rflag=0;ceng[1]=11;//1�������������� 
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
			else if(lflag==1 && rflag==0){//2ֻ�������� 
				printf("   ");printf("/");
				lflag=0;ceng[2]=10;
			}
			else if(lflag==0 && rflag==1){//��2������ֻ�������� 
				ceng[2]=1;rflag=0; 
			}
			else{//2û���������� 
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
			else if(lflag==1 && rflag==0){//3ֻ�������� 
				lflag=0;ceng[3]=10; 
			}
			else if(lflag==0 && rflag==1){
			}
			else{//3û������ 
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
			else{//4û������ 
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
		if(Q.front->next->addr->lchild->data!='@'){//����������� 
			Q=EnQueue(Q.front->next->addr->lchild,Q);
			lflag=1;
		}
		if(Q.front->next->addr->rchild->data!='@'){//����������� 
			Q=EnQueue(Q.front->next->addr->rchild,Q);
			rflag=1;
		}
		Q=DeQueue(Q);
		i++;
	}
}

void pre_order_dg(BTree *a){//�������--�ݹ� 
	if(a->data!='@'){
		printf("%c ",Data(a));
		pre_order_dg(a->lchild);
		pre_order_dg(a->rchild);
	}
}

void pre_order_fdg(BTree *T){//�������--�ǵݹ� 
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

void in_order_dg(BTree *a){//�������--�ݹ� 
	if(a->data!='@'){
		in_order_dg(a->lchild);
		printf("%c ",Data(a));
		in_order_dg(a->rchild);
	}
}

void in_order_fdg(BTree *T){//�������--�ǵݹ� 
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

void post_order_dg(BTree *a){//�������--�ݹ� 
	if(a->data!='@'){
		post_order_dg(a->lchild);
		post_order_dg(a->rchild);
		printf("%c ",Data(a));
	}
}

void post_order_fdg(BTree *T){//�������--�ǵݹ� 
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

void c_order(BTree *a){//�������--ʹ�ö��� 
	Queue Q;
	Q.front=(celltype *)malloc(sizeof(celltype));//��ͷ 
	Q.front->next=NULL;//����next��Ϊ��
	Q.rear=Q.front; 
	if(a!=NULL){
		Q=EnQueue(a,Q);
	}
	printf("�������������Ϊ��");
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

void is_completeBTree(BTree *T){//�ж��Ƿ�Ϊ��ȫ������ 
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
		if(Front(Q)->lchild!=NULL)//�������� 
			Q=EnQueue(Front(Q)->lchild,Q);
		if(Front(Q)->rchild!=NULL)//��������
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
			printf("�˶�����������ȫ������������");
			i=0;
			break;
		}
		i++;
	}
	if(i!=0){
		printf("�˶���������ȫ������������");
	}
}

void calculation_BT_width(BTree *T){//����������Ŀ�� 
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
			if(Front(Q[i])->lchild->data!='@'){//�������� 
				Q[i+1]=EnQueue(Front(Q[i])->lchild,Q[i+1]);
				count++;
			}
			if(Front(Q[i])->rchild->data!='@'){//��������
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
	printf("�������Ŀ��Ϊ��%d",max);
}

void freeallS(Stack *S){//freeջ���� 
	Stack *p;
	while(S->next!=NULL){
		p=S->next;
		free(S);
		S=p;
	}
	free(S);
}

void freeallQ(Queue Q){//free�������� 
	
}
 
void freeallBT(BTree *T){//free����������

}

