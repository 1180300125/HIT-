//���ݽṹʵ��һ lab1������ʽ������ 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct node{
	float coef;  //ϵ�� 
	int exp;     //ָ�� 
	struct node *next;
}Node;

void menu();//�˵� 
Node* readfile(char * filename);//���ļ�������ʽ 
void printlink(Node *a);//���������ӡ����ʽ 
Node* sortlink(Node *a);//����ָ����С���� 
Node* attach(float c,int e,Node *a);//�������β��ӽ�� 
void qd();//��k�׵� 
Node* add(Node *a,Node *b);//����ʽ���
int Compare(int x,int y);//���ڱȽ�ָ����С 
Node* sub(Node *a,Node *b);//����ʽ��� 
Node* mul(Node *a,Node *b);//����ʽ��� 
void div(Node *a,Node *b);//����ʽ�������õ��̺���ʽ 
void calculation();//����x=x0ʱ��ֵ 
void freeall(Node *a);//�ͷ��������� 

int main(){
	int m;
	while(1){
		Node *e,*a,*b;
		menu();
		printf("\t���������ѡ��");
		scanf("%d",&m);
		switch(m){
			case 1: qd();//�� 
					break;
			case 2: a=readfile("D:\\DevC++\\lab1\\a.txt");//�ӷ� 
					b=readfile("D:\\DevC++\\lab1\\b.txt");
					printf("\n����ʽa��");
					printlink(a);
					printf("\n����ʽb��");
					printlink(b);
					e=add(a,b);
					printf("\n����ʽa+b��");
					printlink(e);
					freeall(a);
					freeall(b);
					freeall(e);
					break;
			case 3: a=readfile("D:\\DevC++\\lab1\\a.txt");//���� 
					b=readfile("D:\\DevC++\\lab1\\b.txt");
					printf("\n����ʽa��");
					printlink(a);
					printf("\n����ʽb��");
					printlink(b);
					e=sub(a,b);
					printf("\n����ʽa-b��");
					printlink(e);
					freeall(a);
					freeall(e);
					break;
			case 4: a=readfile("D:\\DevC++\\lab1\\a.txt");//�˷�  
					b=readfile("D:\\DevC++\\lab1\\b.txt");
					printf("\n����ʽa��");
					printlink(a);
					printf("\n����ʽb��");
					printlink(b);
					e=mul(a,b);
					printf("\n����ʽa*b��");
					printlink(e);
					freeall(a);
					freeall(b); 
					freeall(e);
					break;
			case 5: a=readfile("D:\\DevC++\\lab1\\a.txt");//���� 
					b=readfile("D:\\DevC++\\lab1\\b.txt");
					printf("\n����ʽa��");
					printlink(a);
					printf("\n����ʽb��");
					printlink(b);
					div(a,b);
					break;
			case 6: calculation();//����x0�㺯��ֵ 
					break;
			case 7: printf("���˳�����");
					exit(0);
			default:printf("�Ƿ����룡�����������룡��");
					break;
		}
	}
	return 0;
}
void menu(){//�˵�
	printf("\n\t-------------------------\n");
	printf("\t|��ѡ����Ĳ�����       |\n");
	printf("\t|1.�Զ���ʽa��k�׵�.    |\n");
	printf("\t|2.����ʽ���.          |\n");
	printf("\t|3.����ʽ���.          |\n");
	printf("\t|4.����ʽ���.          |\n");
	printf("\t|5.����ʽa����b.        |\n");
	printf("\t|6.����ʽa��x=x0����ֵ. |\n");
	printf("\t|7.�˳�.                |\n");
	printf("\t-------------------------\n");
}

void freeall(Node *a){//�ͷ���������
	Node *p;
	while(a->next!=NULL){
		p=a;
		a=a->next;
		free(p);
	}
	free(a);
}

Node* readfile(char * filename){//���ļ�������ʽ
	Node *a,*head;
	char x,s;
	int e;
	float c;
	head=(Node *)malloc(sizeof(Node));
	a=head;
	FILE *fp=fopen(filename,"r");
	if(fp==NULL){
		printf("�ļ���ʧ�ܣ�����\n");
		exit(0);
	}
	fscanf(fp,"%f%c%d",&c,&x,&e);
	a=attach(c,e,a);
	s=fgetc(fp);
	while(s!=EOF){
		fscanf(fp,"%f%c%d",&c,&x,&e);
		if(s=='-'){
			a=attach(-c,e,a);
		}
		else{
			a=attach(c,e,a);
		}
		s=fgetc(fp);
	}
	fclose(fp);
	a->next=NULL; 
	return sortlink(head);//�����ݽ�������
}
 
Node* attach(float c,int e,Node *a){//�������β����½��p 
	Node *p;
	p=(Node *)malloc(sizeof(Node));
	p->coef=c;
	p->exp=e;
	a->next=p;
	return p;
} 

void printlink(Node *a){//���������ӡ����ʽ 
	Node *p;
	p=a;
	while(p->next!=NULL){
		if(p->next->coef<0){
			printf("-");
		}
		if(fabs(p->next->coef)==1 && p->next->exp!=0){
			;
		}
		else
			printf("%f",fabs(p->next->coef));
		if(p->next->exp==0){
			;
		}
		else if(p->next->exp!=1){
			printf("x^");
			printf("%d",p->next->exp);
		}
		else{
			printf("x");
		}
		p=p->next;
		if(p->next!=NULL && p->next->coef>0){
			printf("+");
		}
	}
}

Node* sortlink(Node *a){//����ָ����С����
	Node *p,*q,*head;
	int maxexp=0;
	float matchcoef;
	head=(Node *)malloc(sizeof(Node));
	p=head;
	while(a->next!=NULL){
		q=a;
		while(q->next!=NULL){
			if(maxexp<=q->next->exp){
				maxexp=q->next->exp;
				matchcoef=q->next->coef;
			}
			q=q->next;
		}
		p=attach(matchcoef,maxexp,p);
		q=a;
		while(q->next!=NULL){
			if(maxexp==q->next->exp ){
				q->next=q->next->next;
				break;
			}
			q=q->next;
		}
		maxexp=0;
	}
	p->next=NULL;//��Ҫ�������������־,����Ҫ������ 
	freeall(a);
	return head;
}

void qd(){//��k�׵� 
	Node *a,*head,*p,*ahead;
	int i,e,k;
	float c;
	a=readfile("D:\\DevC++\\lab1\\a.txt");
	ahead=a;
	head=(Node *)malloc(sizeof(Node));
	p=head;
	printf("\n�������󵼵Ľ�����");
	scanf("%d",&k);
	while(a->next!=NULL){
		if(a->next->exp<k){
			;
		}
		else{
			c=a->next->coef;
			e=a->next->exp;
			for(i=0;i<k;i++){
				c=c*e;
				e=e-1;
			}
			p=attach(c,e,p);
		} 
		a=a->next;
	}
	p->next=NULL;
	printf("\n����ʽa��");
	printlink(ahead);
	printf("\n��k=%d�׵���ʽΪ��",k);
	printlink(head);
	freeall(ahead);
	freeall(head);
} 

Node* add(Node *a,Node *b){//����ʽ��� 
	Node *p,*head,*ahead,*bhead;
	head=(Node *)malloc(sizeof(Node));
	p=head;
	ahead=a;
	bhead=b;
	while(a->next!=NULL && b->next!=NULL){
		switch(Compare(a->next->exp,b->next->exp)){
			case 0 :if(a->next->coef+b->next->coef==0){//ϵ����Ϊ0 
						a=a->next;
						b=b->next;
						break;
					}
					else{
						p=attach(a->next->coef+b->next->coef,a->next->exp,p);// =
						a=a->next;
						b=b->next;
						break;
					}
			case 1 :p=attach(a->next->coef,a->next->exp,p);// >
					a=a->next;
					break;
			case 2 :p=attach(b->next->coef,b->next->exp,p);// <
					b=b->next;
					break;
		}
	}
	if(a->next==NULL && b->next!=NULL){
		while(b->next!=NULL){
			p=attach(b->next->coef,b->next->exp,p);
			b=b->next;
		}
		p->next=NULL;
	}
	if(b->next==NULL && a->next!=NULL){
		while(a->next!=NULL){
			p=attach(a->next->coef,a->next->exp,p);
			a=a->next;
		}
		p->next=NULL;
	}
	if(b->next==NULL && a->next==NULL){
		p->next=NULL;
	}
	if(head->next==NULL){
		p=head;
		p=attach(0,0,p);
		p->next=NULL;
	}
	a=ahead;
	b=bhead;
	return head;
}

int Compare(int x,int y){//���ڱȽ�ָ����С 
	if(x==y)
		return 0;
	else if(x>y)
		return 1;
	else
		return 2;
}

Node* sub(Node *a,Node *b){//����ʽ��� ,a+(-b)
	Node *p,*head,*c,*bhead;
	bhead=b;
	head=(Node *)malloc(sizeof(Node));
	p=head;
	while(b->next!=NULL){
		p=attach(-b->next->coef,b->next->exp,p);
		b=b->next;
	}
	p->next=NULL;
	c=add(a,head);
	freeall(head);
	freeall(bhead);
	return c;
}

Node* mul(Node *a,Node *b){//����ʽ���
	Node *bhead,*c,*h[1000],*p,*m,*ahead;
	bhead=b;
	ahead=a;
	int i=0;
	while(a->next!=NULL){
		h[i]=(Node *)malloc(sizeof(Node));
		p=h[i];
		while(b->next!=NULL){
			p=attach(a->next->coef*b->next->coef,a->next->exp+b->next->exp,p);
			b=b->next;
		}
		p->next=NULL;
		if(i==0){
			c=h[i];
		}
		if(i>0){
			m=add(c,h[i]);
			freeall(c);
			freeall(h[i]); 
			c=m;
		}
		i++;
		b=bhead;
		a=a->next;
	}
	a=ahead;
	b=bhead;
	return c;
}

void div(Node *a,Node *b){//����ʽ�������õ��̺���ʽ 
	Node *s,*r,*shead,*ahead;
	int j=0;
	shead=(Node *)malloc(sizeof(Node));//�� 
	s=shead;
	ahead=a;
	//Ҫ��ӡ�̺���ʽ 
	while(1){
		if(a->next->exp >= b->next->exp){
			s=attach(a->next->coef/b->next->coef,a->next->exp-b->next->exp,s);
			s->next=NULL;
			if(j>0)
				freeall(a);
		}
		else{//���������sΪ�̣�aΪ��ʽ 
			printf("\n��Ϊ��");
			printlink(shead);
			printf("\n��ʽΪ��");
			printlink(a);
			freeall(shead);
			freeall(a);
			break;
		}
		j++;
		r=mul(b,shead);
		a=sub(ahead,r);
	}
	freeall(ahead);
	freeall(b);
}

void calculation(){//����x=x0ʱ��ֵ 
	Node *a;
	a=readfile("D:\\DevC++\\lab1\\a.txt");
	Node *c,*p;
	float x0,ans=0;
	p=a;
	printf("\n������x0��ֵ��");
	scanf("%f",&x0);
	while(p->next!=NULL){
		ans=ans+pow(x0,p->next->exp)*p->next->coef;
		p=p->next;
	}
	printf("\n����ʽa��");
	printlink(a);
	printf("\n�����%f\n",ans); 
	freeall(a);
}

