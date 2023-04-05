//数据结构实验一 lab1：多项式计算器 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct node{
	float coef;  //系数 
	int exp;     //指数 
	struct node *next;
}Node;

void menu();//菜单 
Node* readfile(char * filename);//从文件读多项式 
void printlink(Node *a);//根据链表打印多项式 
Node* sortlink(Node *a);//根据指数大小排序 
Node* attach(float c,int e,Node *a);//向链表结尾添加结点 
void qd();//求k阶导 
Node* add(Node *a,Node *b);//多项式相加
int Compare(int x,int y);//用于比较指数大小 
Node* sub(Node *a,Node *b);//多项式相减 
Node* mul(Node *a,Node *b);//多项式相乘 
void div(Node *a,Node *b);//多项式除法，得到商和余式 
void calculation();//计算x=x0时的值 
void freeall(Node *a);//释放整个链表 

int main(){
	int m;
	while(1){
		Node *e,*a,*b;
		menu();
		printf("\t请输入你的选择：");
		scanf("%d",&m);
		switch(m){
			case 1: qd();//求导 
					break;
			case 2: a=readfile("D:\\DevC++\\lab1\\a.txt");//加法 
					b=readfile("D:\\DevC++\\lab1\\b.txt");
					printf("\n多项式a：");
					printlink(a);
					printf("\n多项式b：");
					printlink(b);
					e=add(a,b);
					printf("\n多项式a+b：");
					printlink(e);
					freeall(a);
					freeall(b);
					freeall(e);
					break;
			case 3: a=readfile("D:\\DevC++\\lab1\\a.txt");//减法 
					b=readfile("D:\\DevC++\\lab1\\b.txt");
					printf("\n多项式a：");
					printlink(a);
					printf("\n多项式b：");
					printlink(b);
					e=sub(a,b);
					printf("\n多项式a-b：");
					printlink(e);
					freeall(a);
					freeall(e);
					break;
			case 4: a=readfile("D:\\DevC++\\lab1\\a.txt");//乘法  
					b=readfile("D:\\DevC++\\lab1\\b.txt");
					printf("\n多项式a：");
					printlink(a);
					printf("\n多项式b：");
					printlink(b);
					e=mul(a,b);
					printf("\n多项式a*b：");
					printlink(e);
					freeall(a);
					freeall(b); 
					freeall(e);
					break;
			case 5: a=readfile("D:\\DevC++\\lab1\\a.txt");//除法 
					b=readfile("D:\\DevC++\\lab1\\b.txt");
					printf("\n多项式a：");
					printlink(a);
					printf("\n多项式b：");
					printlink(b);
					div(a,b);
					break;
			case 6: calculation();//计算x0点函数值 
					break;
			case 7: printf("已退出！！");
					exit(0);
			default:printf("非法输入！！请重新输入！！");
					break;
		}
	}
	return 0;
}
void menu(){//菜单
	printf("\n\t-------------------------\n");
	printf("\t|请选择你的操作：       |\n");
	printf("\t|1.对多项式a求k阶导.    |\n");
	printf("\t|2.多项式相加.          |\n");
	printf("\t|3.多项式相减.          |\n");
	printf("\t|4.多项式相乘.          |\n");
	printf("\t|5.多项式a除以b.        |\n");
	printf("\t|6.多项式a在x=x0处的值. |\n");
	printf("\t|7.退出.                |\n");
	printf("\t-------------------------\n");
}

void freeall(Node *a){//释放整个链表
	Node *p;
	while(a->next!=NULL){
		p=a;
		a=a->next;
		free(p);
	}
	free(a);
}

Node* readfile(char * filename){//从文件读多项式
	Node *a,*head;
	char x,s;
	int e;
	float c;
	head=(Node *)malloc(sizeof(Node));
	a=head;
	FILE *fp=fopen(filename,"r");
	if(fp==NULL){
		printf("文件打开失败！！！\n");
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
	return sortlink(head);//按降幂进行排序
}
 
Node* attach(float c,int e,Node *a){//向链表结尾添加新结点p 
	Node *p;
	p=(Node *)malloc(sizeof(Node));
	p->coef=c;
	p->exp=e;
	a->next=p;
	return p;
} 

void printlink(Node *a){//根据链表打印多项式 
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

Node* sortlink(Node *a){//根据指数大小排序
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
	p->next=NULL;//不要忘记链表结束标志,很重要！！！ 
	freeall(a);
	return head;
}

void qd(){//求k阶导 
	Node *a,*head,*p,*ahead;
	int i,e,k;
	float c;
	a=readfile("D:\\DevC++\\lab1\\a.txt");
	ahead=a;
	head=(Node *)malloc(sizeof(Node));
	p=head;
	printf("\n请输入求导的阶数：");
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
	printf("\n多项式a：");
	printlink(ahead);
	printf("\n求k=%d阶导后式为：",k);
	printlink(head);
	freeall(ahead);
	freeall(head);
} 

Node* add(Node *a,Node *b){//多项式相加 
	Node *p,*head,*ahead,*bhead;
	head=(Node *)malloc(sizeof(Node));
	p=head;
	ahead=a;
	bhead=b;
	while(a->next!=NULL && b->next!=NULL){
		switch(Compare(a->next->exp,b->next->exp)){
			case 0 :if(a->next->coef+b->next->coef==0){//系数和为0 
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

int Compare(int x,int y){//用于比较指数大小 
	if(x==y)
		return 0;
	else if(x>y)
		return 1;
	else
		return 2;
}

Node* sub(Node *a,Node *b){//多项式相减 ,a+(-b)
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

Node* mul(Node *a,Node *b){//多项式相乘
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

void div(Node *a,Node *b){//多项式除法，得到商和余式 
	Node *s,*r,*shead,*ahead;
	int j=0;
	shead=(Node *)malloc(sizeof(Node));//商 
	s=shead;
	ahead=a;
	//要打印商和余式 
	while(1){
		if(a->next->exp >= b->next->exp){
			s=attach(a->next->coef/b->next->coef,a->next->exp-b->next->exp,s);
			s->next=NULL;
			if(j>0)
				freeall(a);
		}
		else{//计算结束，s为商，a为余式 
			printf("\n商为：");
			printlink(shead);
			printf("\n余式为：");
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

void calculation(){//计算x=x0时的值 
	Node *a;
	a=readfile("D:\\DevC++\\lab1\\a.txt");
	Node *c,*p;
	float x0,ans=0;
	p=a;
	printf("\n请输入x0的值：");
	scanf("%f",&x0);
	while(p->next!=NULL){
		ans=ans+pow(x0,p->next->exp)*p->next->coef;
		p=p->next;
	}
	printf("\n多项式a：");
	printlink(a);
	printf("\n结果：%f\n",ans); 
	freeall(a);
}

