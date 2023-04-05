//数据结构homework1 
/*
表达式求值是实现程序设计语言的基本问题之一，也是栈的应用的一个典型
例子。一个算术表达式是由操作数(operand)、运算符(operator)和界限符
(delimiter)组成的。假设操作数是正整数，运算符只含加减乘除等四种二元运
算符，界限符有左右括号和表达式起始、结束符“#”，如：#（7+15）*（23-28/4）#。22*16=352
引入表达式起始、结束符是为了方便。设计一个程序，演示用算符优先法对
算术表达式求值的过程。 
要求：
1. 从文本文件输入任意一个语法正确的（中缀）表达式，显示并保存该表达式。
2. 利用栈结构，把上述（中缀）表达式转换成后缀表达式，并显示栈的状态变
化过程和所得到的后缀表达式。
3. 利用栈结构，对上述后缀表达式进行求值，并显示栈的状态变化过程和最终
结果。
4. 将操作数类型扩充到实数、扩充运算符集合，并引入变量操作数，来完成表
达式求值。
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct Stack{
	char c[10];//栈中存放字符串 
	Stack *next;
};

void Makenull(Stack *S);//
void Push(char *a,Stack *S);//
char *Top(Stack *S);//
void Pop(Stack *S);//
int isEmpty(Stack *S);//

void read(char *a,char *d);//读取中缀表达式文件 
int f(char *a);//运算符优先级定义 
int isnum(char *a);//判断是否为数字 
void run(char *n);//转后缀并进行运算 --核心函数 
int cal(int b,int a,char *c);//计算 
void printstack(Stack *S);//打印栈内容 
void freeall(Stack *S);//释放栈链表 

main(){
	char str[100];
	read("D:\\DevC++\\homework1\\1.txt",str);
	printf("中缀表达式为：%s\n",str);
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
		printf("栈为空！");
	}
	else{
		return S->next->c;
	}
}

void Pop(Stack *S){//
	Stack *p;
	if(isEmpty(S)){
		printf("栈为空！");
	}
	else{
		p=S->next;
		S->next=p->next;
		free(p);
	}
}

int isEmpty(Stack *S){//
	if(S->next==NULL)
		return 1;//是空的
	else
		return 0;//非空 
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

int cal(int b,int a,char *c){//计算 
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
	printf("\n栈顶      <-       栈底\n");
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
			printf("\n\n操作数栈S_sum：");
			printstack(S_num);
		}
		else{
			pp:
			if(isEmpty(S_ch) || Top(S_ch)[0]=='('){
				Push(a[i],S_ch);
				printf("\n\n字符栈S_ch："); 
				printstack(S_ch);
			}
			else if(a[i][0]=='('){
				Push(a[i],S_ch);
				printf("\n\n字符栈S_ch：");
				printstack(S_ch);
			}
			else if(a[i][0]==')'){
				while(Top(S_ch)[0]!='('){
					Push(Top(S_ch),S_num);
					Pop(S_ch);
					printf("\n\n操作数栈S_sum：");
					printstack(S_num);
					printf("\n\n字符栈S_ch：");
					printstack(S_ch);
				}
				Pop(S_ch);//删掉'(' 
				printf("\n\n字符栈S_ch：");
				printstack(S_ch);
			}
			else{
				if(f(a[i])>f(Top(S_ch))){
					Push(a[i],S_ch);
					printf("\n\n字符栈S_ch：");
					printstack(S_ch);
				}
				else{
					Push(Top(S_ch),S_num);
					Pop(S_ch);
					printf("\n\n操作数栈S_sum：");
					printstack(S_num);
					printf("\n\n字符栈S_ch：");
					printstack(S_ch);
					goto pp;//直到把a[i]处理后才结束goto函数 
				}
			}
		}
		i++;
	}
	while(!isEmpty(S_ch)){//直到表达式读完，将字符栈全部压入另一个栈 
		Push(Top(S_ch),S_num);
		Pop(S_ch);
		printf("\n\n操作数栈S_sum：");
		printstack(S_num);
		printf("\n\n字符栈S_ch：");
		printstack(S_ch);
	}
	while(!isEmpty(S_num)){
		strcpy(s[j],Top(S_num));
		j++;
		Pop(S_num);
	}
	while(j!=0){//栈中内容的倒序即为后缀表达式 
		strcpy(hou[k],s[j-1]);
		j--;
		k++;
	}
	hou[k][0]='\0';
	i=0;
	printf("\n后缀表达式为：");
	while(hou[i][0]!='\0'){
		printf("%s ",hou[i]);
		i++;
	}
	/***********计算后缀表达式**********/
	while(hou[j][0]!='\0'){
		if(isnum(hou[j])){
			Push(hou[j],S_calcu);
			printf("\n\n计算器栈S_calcu：");
			printstack(S_calcu);
		}
		else{
			if(!isEmpty(S_calcu)){
				b=atoi(Top(S_calcu));
				Pop(S_calcu);
				printf("\n\n计算器栈S_calcu：");
				printstack(S_calcu);
			}
			if(!isEmpty(S_calcu)){
				c=atoi(Top(S_calcu));
				Pop(S_calcu);
				printf("\n\n计算器栈S_calcu：");
				printstack(S_calcu);
			}
			Push(itoa(cal(b,c,hou[j]),buff,10),S_calcu);
			printf("\n\n计算器栈S_calcu：");
			printstack(S_calcu);
		}
		j++;
	}
	printf("\n计算结果为：%s",Top(S_calcu));
	Pop(S_calcu);
	printf("\n\n计算器栈S_calcu：");
	printstack(S_calcu);
	
	freeall(S_ch);
	freeall(S_num);
	freeall(S_calcu);
}

void freeall(Stack *S){//释放栈链表 
	Stack *p;
	while(S->next!=NULL){
		p=S->next;
		free(S);
		S=p;
	}
	free(S);
}

