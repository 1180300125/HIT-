//���ݽṹhomework1 
/*
���ʽ��ֵ��ʵ�ֳ���������ԵĻ�������֮һ��Ҳ��ջ��Ӧ�õ�һ������
���ӡ�һ���������ʽ���ɲ�����(operand)�������(operator)�ͽ��޷�
(delimiter)��ɵġ�������������������������ֻ���Ӽ��˳������ֶ�Ԫ��
��������޷����������źͱ��ʽ��ʼ����������#�����磺#��7+15��*��23-28/4��#��22*16=352
������ʽ��ʼ����������Ϊ�˷��㡣���һ��������ʾ��������ȷ���
�������ʽ��ֵ�Ĺ��̡� 
Ҫ��
1. ���ı��ļ���������һ���﷨��ȷ�ģ���׺�����ʽ����ʾ������ñ��ʽ��
2. ����ջ�ṹ������������׺�����ʽת���ɺ�׺���ʽ������ʾջ��״̬��
�����̺����õ��ĺ�׺���ʽ��
3. ����ջ�ṹ����������׺���ʽ������ֵ������ʾջ��״̬�仯���̺�����
�����
4. ���������������䵽ʵ����������������ϣ����������������������ɱ�
��ʽ��ֵ��
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct Stack{
	char c[10];//ջ�д���ַ��� 
	Stack *next;
};

void Makenull(Stack *S);//
void Push(char *a,Stack *S);//
char *Top(Stack *S);//
void Pop(Stack *S);//
int isEmpty(Stack *S);//

void read(char *a,char *d);//��ȡ��׺���ʽ�ļ� 
int f(char *a);//��������ȼ����� 
int isnum(char *a);//�ж��Ƿ�Ϊ���� 
void run(char *n);//ת��׺���������� --���ĺ��� 
int cal(int b,int a,char *c);//���� 
void printstack(Stack *S);//��ӡջ���� 
void freeall(Stack *S);//�ͷ�ջ���� 

main(){
	char str[100];
	read("D:\\DevC++\\homework1\\1.txt",str);
	printf("��׺���ʽΪ��%s\n",str);
	run(str);
}

void Makenull(Stack *S){//
	S->next=NULL;
}

void Push(char *a,Stack *S){//
	Stack *p;
	p=(Stack *)malloc(sizeof(Stack));
	p->next=S->next;
	S->next=p;
	//S->next->c=a;
	strcpy(S->next->c,a);
}

char *Top(Stack *S){//
	if(isEmpty(S)){
		printf("ջΪ�գ�");
	}
	else{
		return S->next->c;
	}
}

void Pop(Stack *S){//
	Stack *p;
	if(isEmpty(S)){
		printf("ջΪ�գ�");
	}
	else{
		p=S->next;
		S->next=p->next;
		free(p);
	}
}

int isEmpty(Stack *S){//
	if(S->next==NULL)
		return 1;//�ǿյ�
	else
		return 0;//�ǿ� 
}

void read(char *a,char *d){//
	FILE *fp;
	char c;
	int i=0;
	fp=fopen(a,"r");
	fscanf(fp,"%c",&c);
	if(c=='#'){
		fscanf(fp,"%c",&c);
		while(c!='#'){
			d[i]=c;
			i++;
			fscanf(fp,"%c",&c);
		}
	}
	d[i]='\0';
	fclose(fp);
}

int f(char *a){
	if(a[0]=='+')
		return 1;
	else if(a[0]=='-')
		return 1;
	else if(a[0]=='*')
		return 2;
	else if(a[0]=='/')
		return 2;
	else if(a[0]=='^')
		return 3;
	else 
		return 0;
}

int isnum(char *a){
	if(strlen(a)==1 && a[0]>='0' && a[0]<='9')
		return 1;
	else if(strlen(a)>1)
		return 1;
	else
		return 0;
}

int cal(int b,int a,char *c){//���� 
	if(c[0]=='+')
		return b+a;
	else if(c[0]=='-')
		return a-b;
	else if(c[0]=='*')
		return a*b;
	else if(c[0]=='/')
		return a/b;
	else if(c[0]=='^')
		return pow(a,b);
	else 
		return 0;
}

void printstack(Stack *S){
	Stack *p;
	p=S;
	printf("\nջ��      <-       ջ��\n");
	while(p->next!=NULL){
		printf("%s ",p->next->c);
		p=p->next;
	}
}

void run(char *n){
	Stack *S_ch,*S_num,*S_calcu;
	int i=0,j=0,k=0,b,c,m=0,l=0,h=0;
	char s[100][5],hou[100][5],a[100][5],buff[10];
	S_ch=(Stack *)malloc(sizeof(Stack));
	S_ch->next=NULL;
	S_num=(Stack *)malloc(sizeof(Stack));
	S_num->next=NULL;
	S_calcu=(Stack *)malloc(sizeof(Stack));
	S_calcu->next=NULL;
	while(n[m]!='\0'){
		if(n[m]>=48 && n[m]<=57){
			while(n[m]>=48 && n[m]<=57){
				a[l][h]=n[m];
				m++;
				h++;
			}
			a[l][h]='\0';
			l++;
			h=0;
		}
		else{
			a[l][0]=n[m];
			a[l][1]='\0';
			l++;
			m++;
		}
	}
	a[l][0]='\0';
	while(a[i][0]!='\0'){
		if(isnum(a[i])){
			Push(a[i],S_num);
			printf("\n\n������ջS_sum��");
			printstack(S_num);
		}
		else{
			pp:
			if(isEmpty(S_ch) || Top(S_ch)[0]=='('){
				Push(a[i],S_ch);
				printf("\n\n�ַ�ջS_ch��"); 
				printstack(S_ch);
			}
			else if(a[i][0]=='('){
				Push(a[i],S_ch);
				printf("\n\n�ַ�ջS_ch��");
				printstack(S_ch);
			}
			else if(a[i][0]==')'){
				while(Top(S_ch)[0]!='('){
					Push(Top(S_ch),S_num);
					Pop(S_ch);
					printf("\n\n������ջS_sum��");
					printstack(S_num);
					printf("\n\n�ַ�ջS_ch��");
					printstack(S_ch);
				}
				Pop(S_ch);//ɾ��'(' 
				printf("\n\n�ַ�ջS_ch��");
				printstack(S_ch);
			}
			else{
				if(f(a[i])>f(Top(S_ch))){
					Push(a[i],S_ch);
					printf("\n\n�ַ�ջS_ch��");
					printstack(S_ch);
				}
				else{
					Push(Top(S_ch),S_num);
					Pop(S_ch);
					printf("\n\n������ջS_sum��");
					printstack(S_num);
					printf("\n\n�ַ�ջS_ch��");
					printstack(S_ch);
					goto pp;//ֱ����a[i]�����Ž���goto���� 
				}
			}
		}
		i++;
	}
	while(!isEmpty(S_ch)){//ֱ�����ʽ���꣬���ַ�ջȫ��ѹ����һ��ջ 
		Push(Top(S_ch),S_num);
		Pop(S_ch);
		printf("\n\n������ջS_sum��");
		printstack(S_num);
		printf("\n\n�ַ�ջS_ch��");
		printstack(S_ch);
	}
	while(!isEmpty(S_num)){
		strcpy(s[j],Top(S_num));
		j++;
		Pop(S_num);
	}
	while(j!=0){//ջ�����ݵĵ���Ϊ��׺���ʽ 
		strcpy(hou[k],s[j-1]);
		j--;
		k++;
	}
	hou[k][0]='\0';
	i=0;
	printf("\n��׺���ʽΪ��");
	while(hou[i][0]!='\0'){
		printf("%s ",hou[i]);
		i++;
	}
	/***********�����׺���ʽ**********/
	while(hou[j][0]!='\0'){
		if(isnum(hou[j])){
			Push(hou[j],S_calcu);
			printf("\n\n������ջS_calcu��");
			printstack(S_calcu);
		}
		else{
			if(!isEmpty(S_calcu)){
				b=atoi(Top(S_calcu));
				Pop(S_calcu);
				printf("\n\n������ջS_calcu��");
				printstack(S_calcu);
			}
			if(!isEmpty(S_calcu)){
				c=atoi(Top(S_calcu));
				Pop(S_calcu);
				printf("\n\n������ջS_calcu��");
				printstack(S_calcu);
			}
			Push(itoa(cal(b,c,hou[j]),buff,10),S_calcu);
			printf("\n\n������ջS_calcu��");
			printstack(S_calcu);
		}
		j++;
	}
	printf("\n������Ϊ��%s",Top(S_calcu));
	Pop(S_calcu);
	printf("\n\n������ջS_calcu��");
	printstack(S_calcu);
	
	freeall(S_ch);
	freeall(S_num);
	freeall(S_calcu);
}

void freeall(Stack *S){//�ͷ�ջ���� 
	Stack *p;
	while(S->next!=NULL){
		p=S->next;
		free(S);
		S=p;
	}
	free(S);
}

