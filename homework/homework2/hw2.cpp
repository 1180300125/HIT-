//���ݽṹ��ҵ��----���νṹ����Ӧ�� -�������� 
/*
���������������뷽��
1. ���ļ��ж�������һƪӢ���ı��ļ����ֱ�ͳ��Ӣ���ı��ļ��и��ַ�����
�������źͿո񣩵�ʹ��Ƶ�ʣ�
2. ������ͳ�Ƶ��ַ�ʹ��Ƶ�ʹ����������������������ÿ���ַ��Ĺ�������
�루�ַ����Ĺ������������
3. ���ı��ļ����ù����������б��룬�洢��ѹ���ļ��������������ļ�����
4. ��������������ļ���ѹ���ʣ�
5. �������������ļ�����Ϊ�ı��ļ�������ԭ�ļ����бȽϡ�--�����һģһ�� 

���¿��Բ�������˼�������˿����ʵ��ӷ�
6. �ܷ����öѽṹ���Ż��Ĺ����������㷨��
7. ���� 1-5 �ı���������ǻ����ַ���ѹ�������ǻ��ڵ��ʵ�ѹ�����������
���������۲��Ƚ�ѹ��Ч����
8. ���� 1-5 �ı����Ƕ����Ƶı��룬���Բ��� K ��Ĺ��������������������
ʵ�֡�K ���ơ��ı�������룬��������Ƶı����������бȽϡ�
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

typedef struct Huffmanbt{
	float weight;
	int lchild;
	int rchild;
	int parent;
	char data;
}Huffmanbt;

void countword(char *a,char *b,int *c,float *d);//ͳ���ַ����ִ��� 
void insert(char *b,char ch,int *c);//�ַ�ͳ��
void printtable(int n,char *a,int *b,float *c);//��ӡͳ�Ʊ�  

void SelectMin(Huffmanbt *T,int n,int *p1,int *p2);//ѡ��������С��Ȩֵp1��p2
void InitHT(Huffmanbt *T,int n,char *a,float *b);//��ʼ������ɭ�� 
void CreatHT(Huffmanbt *T,int n,int m,char *a,float *b);//����������� 
void Encode(Huffmanbt *T,int i,char *d);//����01����Ķ������ַ��� 

int Searchi(char ch,char *c);//�����ַ���Ӧ������ֵ  
int encode(char *a);//����λ 01�ַ���תΪ�����ƶ�Ӧ������ 
void inttostr(int m,char *t);//��int����ת��Ϊ 8λ�������ַ��� 
void ys(char *a,char *b,char *c,char d[][20]);//ѹ�� 
void hy(char *a,char *b,char *c,char d[][20],Huffmanbt *T,int m);//��ԭ

int main(){
	char word[100],filename[50],filename_ys[100],filename_hy[100];//�ַ��� 
	int times[100]={0},n=0,i=0,m;//������ 
	float frequency[100]={0},v;//Ƶ�ʱ� 
	strcpy(filename,"D:\\DevC++\\homework2\\2.txt");
	countword(filename,word,times,frequency);
	while(word[i]!='\0')
		i++;
	n=i;
	m=2*n-1;
	printtable(n,word,times,frequency);
	
	Huffmanbt T[m];
	CreatHT(T,n,m,word,frequency);
	
	char c[n][20];
	for(i=0;i<n;i++)
		Encode(T,i,c[i]);
	printf("\n\n�ַ��Ĺ�������������£�\n");
	for(i=0;i<n;i++){
		printf("�ַ���%c ����Ϊ��%s",word[i],c[i]);
		i++;
		if(i==n)
			continue;
		printf("\t\t�ַ���%c ����Ϊ��%s\n",word[i],c[i]);
	}
	
	strcpy(filename_ys,"D:\\DevC++\\homework2\\2_ys.txt");
	strcpy(filename_hy,"D:\\DevC++\\homework2\\2_hy.txt");
	ys(filename,filename_ys,word,c);
	printf("\n���ѹ������");
	hy(filename_ys,filename_hy,word,c,T,m-1);
	printf("\n��ɻ�ԭ����\n");
	v=100*24.0/42;//ԭ�ļ���С��42KB��ѹ�����С��24KB 
	printf("ѹ����Ϊ��%f%%",v);
	return 0;
}

void insert(char *b,char ch,int *c){//�ַ�ͳ�� 
	int i=0,flag=0;
	if(b[i]=='\0')
		flag=1;
	if(ch=='\n')//����ǻ��з����������⴦�� 
		ch='^';//'^'������ʾ���з�\n 
	while(b[i]!='\0'){
		if(b[i]==ch){
			c[i]++;
			flag=2;
			break;
		}
		i++;
		if(b[i]=='\0')
			flag=1;
	}
	if(flag==1){
		b[i]=ch;
		c[i]++;
		b[i+1]='\0';
	}
}

void countword(char *a,char *b,int *c,float *d){//ͳ���ı����ַ����ִ��� 
	FILE *fp;
	int i=0,j;
	float sum=0;
	char ch;
	fp=fopen(a,"r");
	b[0]='\0';
	while(!feof(fp)){
		fscanf(fp,"%c",&ch);
		insert(b,ch,c);
	}
	while(c[i]!=0){
		sum+=c[i];
		i++;
	}
	for(j=0;j<i;j++){
		d[j]=100.0*c[j]/sum;
	}
}
 
void printtable(int n,char *a,int *b,float *c){//��ӡͳ�Ʊ� 
	int i=0;
	printf("�ַ�Ƶ�ʱ����� ��%d���ַ� ��(ע�⣺�˴����ַ�'^'����ʾ���з�)\n",n);
	while(a[i]!='\0'){
		printf("�ַ���%c ���� %d�Σ�Ƶ�ʣ�%f%%",a[i],b[i],c[i]);
		i++;
		if(a[i]!='\0'){
			printf("\t\t�ַ���%c ���� %d�Σ�Ƶ�ʣ�%f%%\n",a[i],b[i],c[i]);
			i++;
		}
	}
}

void SelectMin(Huffmanbt *T,int n,int *p1,int *p2){//ѡ��������С��Ȩֵp1��p2
	int i,j;
	for(i=0;i<n;i++)
		if(T[i].parent==-1){
			*p1=i;
			break;
		}
	for(j=i+1;j<n;j++)
		if(T[j].parent==-1){
			*p2=j;
			break;
		}
	for(i=0;i<n;i++)
		if(T[i].weight<T[*p1].weight && T[i].parent==-1 && *p2!=i)
			*p1=i;
	for(j=0;j<n;j++)
		if(T[j].weight<T[*p2].weight && T[j].parent==-1 && *p1!=j)
			*p2=j;
}

void InitHT(Huffmanbt *T,int n,char *a,float *b){//��ʼ������ɭ��
	int i;
	for(i=0;i<n;i++){
		T[i].parent=-1;
		T[i].lchild=-1;
		T[i].rchild=-1;
		T[i].weight=b[i];
		T[i].data=a[i];
	}
}

void CreatHT(Huffmanbt *T,int n,int m,char *a,float *b){//�����������
	int i,p1,p2;
	InitHT(T,n,a,b);
	for(i=n;i<m;i++){
		SelectMin(T,i,&p1,&p2);
		T[p1].parent=i;
		T[p2].parent=i;
		T[i].lchild=p1;
		T[i].rchild=p2;
		T[i].weight=T[p1].weight+T[p2].weight;
		T[i].parent=-1;
		T[i].data='@';
	}
} 

void Encode(Huffmanbt *T,int i,char *d){//����01����Ķ������ַ���
	char c[100];
	int j,k=0,n=0;
	while(T[i].parent!=(-1)){
		j=T[i].parent;
		if(T[j].lchild==i)
			c[k]='0';
		if(T[j].rchild==i)
			c[k]='1';
		k++;
		i=j;
	}
	while(k!=0){
		d[n]=c[k-1];
		k--;
		n++;
	}
	d[n]='\0';
}

int Searchi(char ch,char *c){//�����ַ���Ӧ������ֵ 
	int i;
	for(i=0;;i++){
		if(c[i]==ch)
			return i;
	}
}

int encode(char *a){//����λ 01�ַ���תΪ�����ƶ�Ӧ��ʮ�������� 
	int i,c=0;
	for(i=0;i<8;i++)
		if(a[i]=='1')
			c+=1<<(7-i);
	return c;
}

void ys(char *a,char *b,char *c,char d[][20]){//ѹ�� ,file,file,word,bm
	FILE *fp1,*fp2;
	int i,j=0,k=0,n,m,r,flag=0;
	char ch;
	char buff[2054],temp[9000],t[9];
	fp1=fopen(a,"r");
	fp2=fopen(b,"wb");
	strcpy(temp,"");//��ʼ��temp 
	while(1){
		if(fgets(buff,2050,fp1)==NULL)//���ж� ,��fp1���ж�ȡ 2050-1���ַ���������ˣ��Ͱ�'\n'Ҳ�ӵ����棬������'\0'������ .txt�ļ�һ����1024�� ���м��䳬��1024��<2048�� 
			break;
		while(buff[j]!='\0'){
			if(buff[j]=='\n')
				buff[j]='^';
			i=Searchi(buff[j],c);
			strcat(temp,d[i]);
			j++;
		}
		n=strlen(temp)/8;
		for(j=0;j<n;j++){
			for(k=0;k<8;k++)
				t[k]=temp[j*8+k];
			t[8]='\0';
			m=encode(t);
			fputc(m,fp2);//�����ֽ�д�룬��Ȼ��4�ֽڵ�int����ʵ��ֻ��д����Ͱ�λ 
		}
		r=strlen(temp)%8;
		if(r>0){
			for(k=0;k<8;k++){
				if(k<r)
					t[k]=temp[8*n+k];
				else
					t[k]='0';
			}
			t[8]='\0';
			m=encode(t);
			fputc(m,fp2);
		}
		j=0;
		strcpy(temp,"");
	}
	fclose(fp1);
	fclose(fp2);
}

void inttostr(int m,char *t){//��int����ת��Ϊ 8λ�������ַ��� 
	int i,j=0;
	char c[9];
	if(m==1){
		strcpy(t,"00000001");
	}
	else if(m==0){
		strcpy(t,"00000000");
	}
	else{
		for(i=0;;i++){
			if(m%2==1)
				c[i]='1';
			else if(m%2==0)
				c[i]='0';
			m=m/2;
			if(m==1){
				c[i+1]='1';
				break;
			}
		}
		c[i+2]='\0';
		for(j=0;j<6-i;j++){
			t[j]='0';
		}
		while(1){
			t[j]=c[i+1];
			i--;
			j++;
			if(i< -1)
				break;
		}
		t[j]='\0';
	}
}

void hy(char *a,char *b,char *c,char d[][20],Huffmanbt *T,int m){//��ԭ file,file,word,bm,huffman,����� 
	FILE *fp1,*fp2;
	int k,x,i=0,j,p;
	char temp[9000],t[9];
	fp1=fopen(a,"rb");
	fp2=fopen(b,"w");
	strcpy(temp,"");//��ʼ��temp
	x=Searchi('^',c);
	p=m;
	while(1){
		pl:
		k=fgetc(fp1);//��ȡһ���ֽڣ�����int�� 
		if(k!= -1){
			inttostr(k,t);
			strcat(temp,t);
		}
		else
			break;
		if(strstr(temp,d[x])!=NULL){
			while(1){
				if(temp[i]=='0')
					j=T[p].lchild;
				if(temp[i]=='1')
					j=T[p].rchild;
				if(T[j].data!='@'){//����Ҷ��� 
					if(T[j].data!='^'){
						fprintf(fp2,"%c",T[j].data);
						p=m;
						i++;
						if(strlen(temp)==i)
							goto pl;
					}
					else{
						fprintf(fp2,"%c",'\n');
						i=0;
						p=m;
						break;
					}
				}
				else{
					p=j;
					i++;
				}
				if(T[j].data=='@' && strlen(temp)==i){
					goto pl;
				}
			}
			strcpy(temp,"");//��ʼ��һ�� 
		}
	}
	fclose(fp1);
	fclose(fp2);
}

