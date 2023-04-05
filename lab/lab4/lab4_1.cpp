/*
��ʵ��Ҫ���д����ʵ�� BST �洢�ṹ�Ľ��������룩��ɾ�������Һ���
���㷨��ʵ���۰�����㷨���Ƚ� BST ���ҽṹ���۰���ҵ�ʱ�����ܡ�
ʵ��Ҫ��
1����� BST ���������洢�ṹ����ʵ�� BST ���루��������ɾ�������Һ������㷨��
2��ʵ���۰�����㷨��
3��ʵ��Ƚϣ���Ʋ�����ʵ��������ݣ�����Ƚ����ֲ��ҷ�����ʱ�����ܣ�
�������۽�����бȽϡ����¾�����������Ϊ�ο���
��1�� �� 1 ��������ݣ� n=1024 ����������������У��� 0 �� 2048 ֮������������� 2 ��������ݣ��� 1 ��������ݵ�������С�
��2�� �������������е�˳����Ϊ����˳�򣬷ֱ��� BST�� 
��3�� ��д�����������������BST�Ĳ��ҳɹ��Ͳ���ʧ�ܵ�ƽ�����ҳ���
����Ҫ�Ǹ��� Search �㷨���ԡ��Ƚϡ����м��������������۽���Ƚϡ�
��4�� ������ BST ���������������Ϊ�۰���ҵ����룬��д����ֱ����
�۰���ҵĲ��ҳɹ��Ͳ���ʧ�ܵ�ƽ�����ҳ��ȣ��������۽���Ƚϡ�
��5�� ����ʵ���ܷ�˵������ƽ�����ܶ��ԣ�BST �Ĳ������۰���Ҳ�࣬Ϊʲô�����������������ã���BST�˻��ɵ�������������Զ�����۰���� �� 
*/
#include <stdio.h>      	/*****����ԭ��(�ݹ�ʱ)ֱ���޸�ָ��(T=T->lchld)����Ҫ����ָ��ĵ�ַ (���磺BST **T)--(*T)=(*T)->lchild ******/
#include <stdlib.h>
#include <time.h>

#define N 10  //1024̫�󣬴˴���10������ 

typedef struct Tree{
	int data;
	struct Tree *lchild;
	struct Tree *rchild;
}BST;

typedef struct cell{//����Ԫ�ص��� 
	float level;//����
	BST *tree;
	struct cell *next;
}celltype;

typedef struct queue{//���� 
	celltype *front;
	celltype *rear;
}Queue;

void Makenull(Queue *Q);
int isEmpty(Queue Q);
celltype *Front(Queue Q);
void EnQueue(float l,BST *T,Queue *Q);
void DeQueue(Queue *Q);

void buildBST(int num[],BST **T);//BST����
void insertBST(int key,BST **T);//BST����                   //Ҫ�ı�ָ�룬�贫��ָ��ĵ�ַ 
int deletemin(BST **T);//ɾ����СԪ��---�������������� 
void deleteBST(int key,BST **T);//BSTɾ��
float searchBST(int key,BST *T,float count);//BST����
float searchfail(BST *T);//�������ʧ�ܵ�ƽ�����ҳ���ASL
 
void in_order(BST *T);//������� 
void buildhalfBT(int num[],int start,int end,BST **T);//�۰�����ж�������

void menu();//�˵� 
void menu1();//

int main(){
	int i,j=1,a,temp,y,x,z;
	int num[N],numrand[N];//1024������������������ 
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
	}//1024��������������� (0-2048)
	while(1){
		BST *T;
		T=NULL;
		float count=0,sum=0;
		menu();
		printf("���������ѡ��"); 
		scanf("%d",&y);
		switch(y){
			case 1: buildBST(num,&T);//BST���� 
					printf("\nBST�ѽ�����(˳��)");
					printf("\n��������Ϊ��");
					in_order(T);//�������
					for(i=0;i<N;i++)
						sum=sum+searchBST(num[i],T,count);
					sum=sum/N;
					printf("\n˳��BST���ҳɹ���ƽ�����ҳ���ASL=%f",sum);
					printf("\n˳��BST����ʧ�ܵ�ƽ�����ҳ���ASL=%f",searchfail(T));
					printf("\n");
					while(1){
						menu1();
						printf("���������ѡ��"); 
						scanf("%d",&z);
						switch(z){
							case 1: printf("������Ҫ��������ݣ�");
									scanf("%d",&x);
									insertBST(x,&T);//BST���� 
									printf("\n��������Ϊ��");
									in_order(T);//�������
									break;
							case 2: printf("������Ҫɾ�������ݣ�");
									scanf("%d",&x);
									deleteBST(x,&T);//BSTɾ�� 
									printf("\n��������Ϊ��");
									in_order(T);//�������
									break;
							case 3: printf("������Ҫ���ҵ����ݣ�");
									scanf("%d",&x);
									if(searchBST(x,T,count)!=-1)//BST���� 
										printf("���ҳɹ���");
									printf("\n��������Ϊ��");
									in_order(T);//�������
									break;
							case 4: printf("�˳��˲˵�����");
									break;
							default:printf("�Ƿ�ѡ�����������룡����");
									break;
						}
						if(z==4)
							break;
					}
					break;
			case 2: buildBST(numrand,&T);//BST���� 
					printf("\nBST�ѽ�����(���)");
					printf("\n��������Ϊ��");
					in_order(T);//�������
					for(i=0;i<N;i++)
						sum=sum+searchBST(numrand[i],T,count);
					sum=sum/N;
					printf("\n���BST���ҳɹ���ƽ�����ҳ���ASL=%f",sum);
					printf("\n���BST����ʧ�ܵ�ƽ�����ҳ���ASL=%f",searchfail(T));
					printf("\n");
					while(1){
						menu1();
						printf("���������ѡ��"); 
						scanf("%d",&z);
						switch(z){
							case 1: printf("������Ҫ��������ݣ�");
									scanf("%d",&x);
									insertBST(x,&T);//BST���� 
									printf("\n��������Ϊ��");
									in_order(T);//�������
									break;
							case 2: printf("������Ҫɾ�������ݣ�");
									scanf("%d",&x);
									deleteBST(x,&T);//BSTɾ�� 
									printf("\n��������Ϊ��");
									in_order(T);//�������
									break;
							case 3: printf("������Ҫ���ҵ����ݣ�");
									scanf("%d",&x);
									if(searchBST(x,T,count)!=-1)//BST���� 
										printf("���ҳɹ���");
									printf("\n��������Ϊ��");
									in_order(T);//�������
									break;
							case 4: printf("�˳��˲˵�����");
									break;
							default:printf("�Ƿ�ѡ�����������룡����");
									break;
						}
						if(z==4)
							break;
					}
					break;
			case 3: buildhalfBT(num,0,N-1,&T);//�۰�����ж��� 
					printf("\n�۰�����ж����ѽ�����");
					printf("\n��������Ϊ��");
					in_order(T);//�������
					for(i=0;i<N;i++)
						sum=sum+searchBST(num[i],T,count);
					sum=sum/N;
					printf("\n�۰�����ж������ҳɹ���ƽ�����ҳ���ASL=%f",sum);
					printf("\n�۰�����ж�������ʧ�ܵ�ƽ�����ҳ���ASL=%f",searchfail(T));
					printf("\n�Ƿ�Ҫ�������ݣ� 1.��   2.�� ");
					printf("\n������ѡ��");
					scanf("%d",&y);
					if(y==1){
						printf("\n������Ҫ���ҵ����ݣ�");
						scanf("%d",&x);
						if(searchBST(x,T,count)!=-1)//BST���� 
							printf("���ҳɹ���");
					}
					break;
			case 4: printf("���˳�������");
					exit(0);
					break;
			default:printf("�Ƿ�ѡ�����������룡����");
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
		return 1;//��
	else
		return 0;//�ǿ� 
}

celltype *Front(Queue Q){
	if(!isEmpty(Q))
		return Q.front->next;
	else
		printf("����Ϊ�գ�");
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
	printf("\t|            �˵�           |\n");
	printf("\t|1.����BST--˳������        |\n");
	printf("\t|2.����BST--�������        |\n");
	printf("\t|3.�۰����                 |\n");
	printf("\t|4.�˳�����                 |\n");
	printf("\t-----------------------------\n");
}

void menu1(){
	printf("\n\t------------------\n");
	printf("\t|      �˵�      |\n");
	printf("\t|1.����BST       |\n");
	printf("\t|2.ɾ��BST       |\n");
	printf("\t|3.����BST       |\n");
	printf("\t|4.�˳�����      |\n");
	printf("\t------------------\n");
}
												/*****����ԭ��ֱ���޸�ָ�룬��Ҫ����ָ��ĵ�ַ (���磺BST **T)******/
void buildBST(int num[],BST **T){//BST����
	int i;
	for(i=0;i<N;i++)
		insertBST(num[i],T);
}

void insertBST(int key,BST **T){//BST����
	BST *k;
	if((*T)==NULL){
		(*T)=(BST *)malloc(sizeof(BST));
		(*T)->data=key;
		(*T)->lchild=NULL;
		(*T)->rchild=NULL;
	}
	else if(key<(*T)->data)
		insertBST(key,&((*T)->lchild));//�м�Ҫ����ָ��ĵ�ַ 
	else if(key>(*T)->data)
		insertBST(key,&((*T)->rchild));
	else if(key==(*T)->data)
		printf("�˽���Ѵ��ڣ�������룡\n");
}

int deletemin(BST **T){//ɾ����СԪ��---��������������  //���ս̲ĳ�����������ֱ�Ӽ̳�ʱ���ִ��󣬼� T=T->lchild ,T=T->rchild����ִ��󣡣����� 
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
 
void deleteBST(int key,BST **T){//BSTɾ��     //���ս̲ĳ�����������ֱ�Ӽ̳�ʱ���ִ��󣬼� T=T->lchild ,T=T->rchild����ִ��󣡣�����
	if((*T)!=NULL){
		if(key==(*T)->data){
			if((*T)->lchild==NULL)//���������Ϊ�գ�����ֱ�Ӽ̳� 
				(*T)=(*T)->rchild;
			else if((*T)->rchild==NULL)//���������Ϊ�գ�����ֱ�Ӽ̳� 
				(*T)=(*T)->lchild;
			else//���������������ѡ����������������Ϊ�̳н�� 
				(*T)->data=deletemin(&((*T)->rchild));
		}
		else if(key<(*T)->data)
			deleteBST(key,&((*T)->lchild));
		else if(key>(*T)->data)
			deleteBST(key,&((*T)->rchild));
	}
	else
		printf("�޴˽�㣡\n"); 
}

float searchBST(int key,BST *T,float count){//BST����
	if(T==NULL){
		printf("�޴˽�㣡\n"); 
		return -1;//û���ҵ� 
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
 
void in_order(BST *T){//������� --����� 
	if(T!=NULL){
		in_order(T->lchild);
		printf("%d ",T->data);
		in_order(T->rchild);
	}
}

void buildhalfBT(int num[],int start,int end,BST **T){//�����۰�����ж���
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

float searchfail(BST *T){//�������ʧ�ܵ�ƽ�����ҳ���ASL�����ö��У�����(��/��)����Ϊ�յĽ��Ĳ����� ,����N+1���õ��� 
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

