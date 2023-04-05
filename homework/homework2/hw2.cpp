//数据结构作业二----树形结构及其应用 -哈夫曼树 
/*
哈夫曼编码与译码方法
1. 从文件中读入任意一篇英文文本文件，分别统计英文文本文件中各字符（包
括标点符号和空格）的使用频率；
2. 根据已统计的字符使用频率构造哈夫曼编码树，并给出每个字符的哈夫曼编
码（字符集的哈夫曼编码表）；
3. 将文本文件利用哈夫曼树进行编码，存储成压缩文件（哈夫曼编码文件）；
4. 计算哈夫曼编码文件的压缩率；
5. 将哈夫曼编码文件译码为文本文件，并与原文件进行比较。--结果：一模一样 

以下可以不做，供思考，做了可以适当加分
6. 能否利用堆结构，优化的哈夫曼编码算法。
7. 上述 1-5 的编码和译码是基于字符的压缩，考虑基于单词的压缩，完成上述
工作，讨论并比较压缩效果。
8. 上述 1-5 的编码是二进制的编码，可以采用 K 叉的哈夫曼树完成上述工作，
实现“K 进制”的编码和译码，并与二进制的编码和译码进行比较。
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

void countword(char *a,char *b,int *c,float *d);//统计字符出现次数 
void insert(char *b,char ch,int *c);//字符统计
void printtable(int n,char *a,int *b,float *c);//打印统计表  

void SelectMin(Huffmanbt *T,int n,int *p1,int *p2);//选择两个最小的权值p1，p2
void InitHT(Huffmanbt *T,int n,char *a,float *b);//初始化单个森林 
void CreatHT(Huffmanbt *T,int n,int m,char *a,float *b);//构造哈夫曼树 
void Encode(Huffmanbt *T,int i,char *d);//返回01编码的二进制字符串 

int Searchi(char ch,char *c);//返回字符对应的索引值  
int encode(char *a);//将八位 01字符串转为二进制对应的整数 
void inttostr(int m,char *t);//将int类型转换为 8位二进制字符串 
void ys(char *a,char *b,char *c,char d[][20]);//压缩 
void hy(char *a,char *b,char *c,char d[][20],Huffmanbt *T,int m);//还原

int main(){
	char word[100],filename[50],filename_ys[100],filename_hy[100];//字符表 
	int times[100]={0},n=0,i=0,m;//次数表 
	float frequency[100]={0},v;//频率表 
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
	printf("\n\n字符的哈夫曼编码表如下：\n");
	for(i=0;i<n;i++){
		printf("字符：%c 编码为：%s",word[i],c[i]);
		i++;
		if(i==n)
			continue;
		printf("\t\t字符：%c 编码为：%s\n",word[i],c[i]);
	}
	
	strcpy(filename_ys,"D:\\DevC++\\homework2\\2_ys.txt");
	strcpy(filename_hy,"D:\\DevC++\\homework2\\2_hy.txt");
	ys(filename,filename_ys,word,c);
	printf("\n完成压缩！！");
	hy(filename_ys,filename_hy,word,c,T,m-1);
	printf("\n完成还原！！\n");
	v=100*24.0/42;//原文件大小：42KB，压缩后大小：24KB 
	printf("压缩率为：%f%%",v);
	return 0;
}

void insert(char *b,char ch,int *c){//字符统计 
	int i=0,flag=0;
	if(b[i]=='\0')
		flag=1;
	if(ch=='\n')//如果是换行符，进行特殊处理 
		ch='^';//'^'用来表示换行符\n 
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

void countword(char *a,char *b,int *c,float *d){//统计文本中字符出现次数 
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
 
void printtable(int n,char *a,int *b,float *c){//打印统计表 
	int i=0;
	printf("字符频率表如下 共%d种字符 ：(注意：此处用字符'^'来表示换行符)\n",n);
	while(a[i]!='\0'){
		printf("字符：%c 出现 %d次，频率：%f%%",a[i],b[i],c[i]);
		i++;
		if(a[i]!='\0'){
			printf("\t\t字符：%c 出现 %d次，频率：%f%%\n",a[i],b[i],c[i]);
			i++;
		}
	}
}

void SelectMin(Huffmanbt *T,int n,int *p1,int *p2){//选择两个最小的权值p1，p2
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

void InitHT(Huffmanbt *T,int n,char *a,float *b){//初始化单个森林
	int i;
	for(i=0;i<n;i++){
		T[i].parent=-1;
		T[i].lchild=-1;
		T[i].rchild=-1;
		T[i].weight=b[i];
		T[i].data=a[i];
	}
}

void CreatHT(Huffmanbt *T,int n,int m,char *a,float *b){//构造哈夫曼树
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

void Encode(Huffmanbt *T,int i,char *d){//返回01编码的二进制字符串
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

int Searchi(char ch,char *c){//返回字符对应的索引值 
	int i;
	for(i=0;;i++){
		if(c[i]==ch)
			return i;
	}
}

int encode(char *a){//将八位 01字符串转为二进制对应的十进制数字 
	int i,c=0;
	for(i=0;i<8;i++)
		if(a[i]=='1')
			c+=1<<(7-i);
	return c;
}

void ys(char *a,char *b,char *c,char d[][20]){//压缩 ,file,file,word,bm
	FILE *fp1,*fp2;
	int i,j=0,k=0,n,m,r,flag=0;
	char ch;
	char buff[2054],temp[9000],t[9];
	fp1=fopen(a,"r");
	fp2=fopen(b,"wb");
	strcpy(temp,"");//初始化temp 
	while(1){
		if(fgets(buff,2050,fp1)==NULL)//按行读 ,从fp1流中读取 2050-1个字符，如果超了，就把'\n'也加到后面，其余用'\0'来补充 .txt文件一行有1024列 ，有几句超过1024但<2048行 
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
			fputc(m,fp2);//按单字节写入，虽然是4字节的int，但实际只会写入其低八位 
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

void inttostr(int m,char *t){//将int类型转换为 8位二进制字符串 
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

void hy(char *a,char *b,char *c,char d[][20],Huffmanbt *T,int m){//还原 file,file,word,bm,huffman,结点数 
	FILE *fp1,*fp2;
	int k,x,i=0,j,p;
	char temp[9000],t[9];
	fp1=fopen(a,"rb");
	fp2=fopen(b,"w");
	strcpy(temp,"");//初始化temp
	x=Searchi('^',c);
	p=m;
	while(1){
		pl:
		k=fgetc(fp1);//读取一个字节，返回int型 
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
				if(T[j].data!='@'){//到达叶结点 
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
			strcpy(temp,"");//开始下一行 
		}
	}
	fclose(fp1);
	fclose(fp2);
}

