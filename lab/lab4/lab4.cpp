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
��5�� ����ʵ���ܷ�˵������ƽ�����ܶ��ԣ�BST �Ĳ������۰���Ҳ�࣬Ϊʲô��
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10  //1024̫�󣬴˴���10������ 

typedef struct Tree{
	int data;
	struct Tree *lchild;
	struct Tree *rchild;
}BST;

void buildBST(int num[],BST *T);//BST����
void insertBST(int key,BST *T);//BST����
int deletemin(BST *T);//ɾ����СԪ��---�������������� 
void deleteBST(int key,BST *T);//BSTɾ��
BST *searchBST(int key,BST *T);//BST����
void in_order(BST *T);//������� 
void halfsearch(int key,int start,int end,int ordernum[]);//�۰����

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
		menu();
		printf("���������ѡ��"); 
		scanf("%d",&y);
		switch(y){
			case 1: T=(BST *)malloc(sizeof(BST));
					T->data=num[0];
					T->lchild=NULL;
					T->rchild=NULL;
					buildBST(num,T);//BST���� 
					printf("\nBST�ѽ�����(˳��)");
					printf("\n��������Ϊ��");
					in_order(T);//�������
					printf("\n");
					while(1){
						menu1();
						printf("���������ѡ��"); 
						scanf("%d",&z);
						switch(z){
							case 1: printf("������Ҫ��������ݣ�");
									scanf("%d",&x);
									insertBST(x,T);//BST���� 
									printf("\n��������Ϊ��");
									in_order(T);//�������
									break;
							case 2: printf("������Ҫɾ�������ݣ�");
									scanf("%d",&x);
									deleteBST(x,T);//BSTɾ�� 
									printf("\n��������Ϊ��");
									in_order(T);//�������
									break;
							case 3: printf("������Ҫ���ҵ����ݣ�");
									scanf("%d",&x);
									if(searchBST(x,T)!=NULL)//BST���� 
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
			case 2: T=(BST *)malloc(sizeof(BST));
					T->data=numrand[0];
					T->lchild=NULL;
					T->rchild=NULL;
					buildBST(numrand,T);//BST���� 
					printf("\nBST�ѽ�����(���)");
					printf("\n��������Ϊ��");
					in_order(T);//�������
					printf("\n");
					while(1){
						menu1();
						int ordernum[N]={0};
						printf("���������ѡ��"); 
						scanf("%d",&z);
						switch(z){
							case 1: printf("������Ҫ��������ݣ�");
									scanf("%d",&x);
									insertBST(x,T);//BST���� 
									printf("\n��������Ϊ��");
									in_order(T);//�������
									break;
							case 2: printf("������Ҫɾ�������ݣ�");
									scanf("%d",&x);
									deleteBST(x,T);//BSTɾ�� 
									printf("\n��������Ϊ��");
									in_order(T);//�������
									break;
							case 3: printf("������Ҫ���ҵ����ݣ�");
									scanf("%d",&x);
									if(searchBST(x,T)!=NULL)//BST���� 
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
			case 3: printf("������Ҫ���ҵ����ݣ�");
					scanf("%d",&x);
					halfsearch(x,0,N-1,num);//�۰���� 
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
void buildBST(int num[],BST *T){//BST����
	int i;
	for(i=1;i<N;i++)
		insertBST(num[i],T);
}

void insertBST(int key,BST *T){//BST����
	BST *k;
	if(T->data==0){
		T->data=key;
		T->lchild=NULL;
		T->rchild=NULL;
	}
	else if(key<T->data){					/*��Ҫ��Ҫ��Ҫ��������������������������������*/ 
		if(T->lchild==NULL){/********�ر�ע��˴���̲Ĳ�ͬ��ֱ�Ӵ�ֵΪNULL��ָ���ʧЧ���޷��γ������������ӣ�
							�˴�����ǰmalloc����ֵΪNULL��ָ�룬Ȼ��data������ֵ0��Ȼ����0ֵΪ�ж����ݣ����в������************/
			k=(BST *)malloc(sizeof(BST));
			k->data=0;
			T->lchild=k;
		}
		insertBST(key,T->lchild);
	}
	else if(key>T->data){					/*��Ҫ��Ҫ��Ҫ��������������������������������*/ 
		if(T->rchild==NULL){/********�ر�ע��˴���̲Ĳ�ͬ��ֱ�Ӵ�ֵΪNULL��ָ���ʧЧ���޷��γ������������ӣ�
							�˴�����ǰmalloc����ֵΪNULL��ָ�룬Ȼ��data������ֵ0��Ȼ����0ֵΪ�ж����ݣ����в������************/
			k=(BST *)malloc(sizeof(BST));
			k->data=0;
			T->rchild=k;
		}
		insertBST(key,T->rchild);
	}
	else if(key==T->data)
		printf("�˽���Ѵ��ڣ�������룡\n");
}

/*int deletemin(BST *T){//ɾ����СԪ��---��������������  //���ս̲ĳ�����������ֱ�Ӽ̳�ʱ���ִ��󣬼� T=T->lchild ,T=T->rchild����ִ��󣡣����� 
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
 
void deleteBST(int key,BST *T){//BSTɾ��     //���ս̲ĳ�����������ֱ�Ӽ̳�ʱ���ִ��󣬼� T=T->lchild ,T=T->rchild����ִ��󣡣�����
	if(T!=NULL){
		if(key==T->data){
			if(T->lchild==NULL)//���������Ϊ�գ�����ֱ�Ӽ̳� 
				T=T->rchild;
			else if(T->rchild==NULL)//���������Ϊ�գ�����ֱ�Ӽ̳� 
				T=T->lchild;
			else//���������������ѡ����������������Ϊ�̳н�� 
				T->data=deletemin(T->rchild);
		}
		else if(key<T->data)
			deleteBST(key,T->lchild);
		else if(key>T->data)
			deleteBST(key,T->rchild);
	}
	else
		printf("�޴˽�㣡\n"); 
}*/

int deletemin(BST *T){//ɾ����СԪ��---�������������� 
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
 
void deleteBST(int key,BST *T){//BSTɾ��
	BST *p;
	if(T!=NULL){
		if(key==T->data){
			if(T->lchild==NULL){//���������Ϊ�գ�����ֱ�Ӽ̳� 
				p=T;
				T=p->rchild;
				free(p);
			}
			else if(T->rchild==NULL){//���������Ϊ�գ�����ֱ�Ӽ̳� 
				p=T;
				T=p->lchild;
				free(p);
			}
			else{//���������������ѡ����������������Ϊ�̳н�� 
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
				if(T->lchild->lchild==NULL){//���������Ϊ�գ�����ֱ�Ӽ̳� 
					p=T->lchild;
					T->lchild=p->rchild;
					free(p);
				}
				else if(T->lchild->rchild==NULL){//���������Ϊ�գ�����ֱ�Ӽ̳� 
					p=T->lchild;
					T->lchild=p->lchild;
					free(p);
				}
				else{//���������������ѡ����������������Ϊ�̳н�� 
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
				if(T->rchild->lchild==NULL){//���������Ϊ�գ�����ֱ�Ӽ̳� 
					p=T->rchild;
					T->rchild=p->rchild;
					free(p);
				}
				else if(T->rchild->rchild==NULL){//���������Ϊ�գ�����ֱ�Ӽ̳� 
					p=T->rchild;
					T->rchild=p->lchild;
					free(p);
				}
				else{//���������������ѡ����������������Ϊ�̳н�� 
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
		printf("�޴˽�㣡\n"); 
}

BST *searchBST(int key,BST *T){//BST����
	if(T==NULL){
		printf("�޴˽�㣡\n"); 
		return NULL;//û���ҵ� 
	}
	else if(key==T->data)
		return T;
	else if(key>T->data)
		return (searchBST(key,T->rchild));
	else if(key<T->data)
		return (searchBST(key,T->lchild));
}
 
void in_order(BST *T){//������� --����� 
	if(T!=NULL){
		in_order(T->lchild);
		printf("%d ",T->data);
		in_order(T->rchild);
	}
}

void halfsearch(int key,int start,int end,int ordernum[]){//�۰����
	int low,high,mid;
	low=start;
	high=end;
	mid=(low+high)/2;
	if(start<end){
		if(key==ordernum[mid])
			printf("���ҳɹ���\n");
		else if(key<ordernum[mid])
			halfsearch(key,low,mid,ordernum);
		else
			halfsearch(key,mid+1,high,ordernum);
	}
	else
		printf("�޴�Ԫ�أ�\n");
}

