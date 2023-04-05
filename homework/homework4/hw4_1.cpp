/*��ҵ��Ŀ 1��AVL ���������ʵ��
 AVL �� AVL ����Ϊһ�ֻ����Ĳ��ң��������ṹ����һ����ƽ��������
������ AVL �����κν������������ĸ߶�����Ϊ 1��������Ҳ����Ϊ�߶�
ƽ�����������ɾ������������Ҫͨ��һ�λ�����ת����������ƽ���������
AVL �����������ķ����� G. M. Adelson-Velsky �� E. M. Landis�������� 1962 ��
�����ġ�An algorithm for the organization of information���з���������
������ҵҪ����� AVL ���洢�ṹ����ʵ�� AVL �����������룩��ɾ���Ͳ����㷨��
����ӳ�����ɾ�������㷨�ĸ�����ת�仯��
��ҵҪ��
1����� AVL ���������洢�ṹ��
2��ʵ�� AVL �������洢�ṹ�ϵĲ��루��������ɾ�������Һ������㷨��
3�������������ļ���ʽ���棬�ܷ�ӳ�����ɾ��������������ת���������Ӧ�����*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct avltree{
	int bf;//ƽ�����ӣ��ý�����������������ĸ߶�֮�� ��-1,0,1 
	int data;
	struct avltree *lchild;
	struct avltree *rchild;
}AVL;

void AVLBuild(int *num,int n,AVL **T,int *unbalanced);//���� 
void AVLInsert(int d,AVL **T,int *unbalanced);//���� 
void deleteAVL(int d,AVL **T,int *unbalanced);//ɾ�� 
void AVLSearch(int d,AVL *T);//���� 
void In_order(AVL *T);//�������

void LeftRotation(AVL **T,int *unbalanced);//LL��ת��LR��ת 
void RightRotation(AVL **T,int *unbalanced);//RR��ת��RL��ת 

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
		printf("���������ѡ��");
		scanf("%d",&y);
		switch(y){
			case 1: AVLBuild(num,n,&T,&unbalanced);
					printf("AVL���ѽ�����");
					printf("\n�����������Ϊ��");
					In_order(T);
					while(1){
						int m;
						unbalanced=0;
						menu1();
						printf("���������ѡ��");
						scanf("%d",&x);
						switch(x){
							case 1: printf("������Ҫ��������ݣ�");
									scanf("%d",&m);
									AVLInsert(m,&T,&unbalanced);
									printf("\n�����������Ϊ��");
									In_order(T);
									break;
							case 2: printf("������Ҫɾ�������ݣ�");
									scanf("%d",&m);
									deleteAVL(m,&T,&unbalanced);
									printf("\n�����������Ϊ��");
									In_order(T);
									break;
							case 3: printf("������Ҫ���ҵ����ݣ�");
									scanf("%d",&m);
									AVLSearch(m,T);
									printf("\n�����������Ϊ��");
									In_order(T);
									break;
							case 4: printf("���˳���");
									break;
							default:printf("�Ƿ�ѡ�����������룡");
									break;
						}
						if(x==4)
							break;
					}
					break;
			case 2: printf("���˳���");
					//exit(0);
					break;
			default:printf("�Ƿ�ѡ�����������룡");
					break;
		}
		if(y==2)
			break;
	}
	return 0;
}

void menu(){
	printf("\n\t--------------------\n");
	printf("\t|       �˵�       |\n");
	printf("\t|1.����AVL��       |\n");
	printf("\t|2.�˳���          |\n");
	printf("\t--------------------\n");
}

void menu1(){
	printf("\n\t---------------\n");
	printf("\t|     �˵�    |\n");
	printf("\t|1.����       |\n");
	printf("\t|2.ɾ��       |\n");
	printf("\t|3.����       |\n");
	printf("\t|4.�˳���     |\n");
	printf("\t---------------\n");
}

void AVLBuild(int *num,int n,AVL **T,int *unbalanced){//���� 
	int i;
	for(i=0;i<n;i++){
		*unbalanced=0;
		AVLInsert(num[i],T,unbalanced);
	}
}
 
void AVLInsert(int d,AVL **T,int *unbalanced){//���� 
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
						*unbalanced=0;// ����/�߶Ȳ��� 
						break;
				case 0: (*T)->bf=1;// ����/�߶ȸı� 
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
		printf("�޴����ݣ�");
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
			while(p->lchild!=NULL)//�������������� 
				p=p->lchild;
			temp=p->data;
			deleteAVL(temp,T,unbalanced);//�൱��ɾ���������������㣬�ٰ�ԭ�ڵ㸳ֵΪɾ���ļ̳н��ֵ 
			(*T)->data=temp;
		}
	}
	else if(d<(*T)->data){
		deleteAVL(d,&((*T)->lchild),unbalanced);
		if(*unbalanced){
			switch((*T)->bf){
				case 1: (*T)->bf=0;//�����ı�--�߶ȸı䣬��ݹ鵽�ϲ�����޸� 
						break;
				case 0: (*T)->bf=-1;//����δ�ı� 
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

void AVLSearch(int d,AVL *T){//���� 
	if(T==NULL)
		printf("�޴����ݣ�");
	else if(d==T->data)
		printf("���ҳɹ���");
	else if(d<T->data)
		AVLSearch(d,T->lchild);
	else if(d>T->data)
		AVLSearch(d,T->rchild);
}
 
void In_order(AVL *T){//�������
	if(T!=NULL){
		In_order(T->lchild);
		printf("%d(%d) ",T->data,T->bf);
		In_order(T->rchild);
	}
}

void LeftRotation(AVL **T,int *unbalanced){//LL��ת��LR��ת 
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
 
void RightRotation(AVL **T,int *unbalanced){//RR��ת��RL��ת
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

