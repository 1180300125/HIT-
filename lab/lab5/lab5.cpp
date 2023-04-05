/*实验内容：
 实现一组经典的排序算法，通过实验数据的设计，考察不同规模和分布（正
序序列、反序序列和随机序列）的数据对排序算法运行时间影响的规律，验证理
论分析结果的正确性。
实验要求：
1． 实现以下三组排序方法中的一组排序算法： 
（1） 冒泡排序和快速排序；
（2） 插入排序和希尔排序；
（3） 选择排序和堆排序；
（4） 递归和非递归的归并排序。
2． 产生不同规模和分布的数据，以 Excel 生成算法执行时间 T(n)关于输入规模
n 的曲线的形式，给出输入规模和分布对排序方法运行时间变化趋势的影响，
并与理论分析结果比较。*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define N 21

typedef struct cell{//队列元素的型 
	int data;
	struct cell *next;
}celltype;

typedef struct queue{//队列 
	celltype *front;
	celltype *rear;
}Queue;

void Makenull(Queue *Q);//要修改指针，传入指针的地址
int isEmpty(Queue Q);
int Front(Queue Q);
void EnQueue(int data,Queue *Q);//要修改指针，需传入指针的地址 
void DeQueue(Queue *Q);//改变指针，需传入指针的地址 

void swap(int *a,int *b);//交换 
/*****冒泡排序和快排*****/ 
void maopao_Sort(int num[]);
int FindPivot(int num[],int start,int end);//快排，选基准
int Partition(int pivot,int num[],int start,int end);//快排，分成两块，左边小于基准，右边大于等于基准 
void QuickSort(int num[],int start,int end);

/*****插入排序和希尔排序*****/
void insert_Sort(int num[],int d,int k);
void xier_Sort(int num[]);

/*****选择排序和堆排序*****/
void choose_Sort(int num[]);
void PushDown(int num[],int first,int last);//整理堆，将 A[1]下推到合适位置，并把最小元素移到 A[1] 
void heap_Sort(int num[]);

/*****递归和非递归的归并排序*****/
void gb_Sort_dg(int num[],int len);
void Merge(int left,int mid,int right,int num[],int temp[]);
void Mpass(int len,int num[],int temp[]);
void gb_Sort_fdg(int num[]);

/*****基数排序(也叫桶排序)*****/  //--一种不基于比较的排序 
int Radix(int key,int pass);//求值key的右数第pass位数字 
void RadixSort(int num[],int figure);//有figure位 

void printsort(int num[]);
void menu();

int main(){
	int num1[N];//升序序列 
	int num2[N];//降序序列 
	int num3[N];//随机序列 
	int i,j=1,temp,a,y;
	for(i=0;i<N;i++){
		num1[i]=j;
		num3[i]=j;
		j+=2;
	}
	j=1;
	for(i=N-1;i>=0;i--){
		num2[i]=j;
		j+=2;
	}
	while(1){
		menu();
		for(i=0;i<N;i++){
			srand((unsigned)time(NULL));
			a=rand()%(N-i)+i;
			temp=num3[a];
			num3[a]=num3[i];
			num3[i]=temp;
		}
		printf("原随机序列为：");
		printsort(num3);
		printf("\n请输入你的选择：");
		scanf("%d",&y);
		switch(y){
			case 1: maopao_Sort(num3);
					printf("\n冒泡排序后序列为：");
					printsort(num3);
					break;
			case 2: QuickSort(num3,0,N-1);
					printf("\n快速排序后序列为：");
					printsort(num3);
					break;
			case 3: insert_Sort(num3,1,0);
					printf("\n插入排序后序列为：");
					printsort(num3);
					break;
			case 4: xier_Sort(num3);
					printf("\n希尔排序后序列为：");
					printsort(num3);
					break;
			case 5: choose_Sort(num3);
					printf("\n选择排序后序列为：");
					printsort(num3);
					break;
			case 6: heap_Sort(num3);
					printf("\n堆排序后序列为：");
					printsort(num3);
					break;
			case 7: gb_Sort_dg(num3,1);//初始归并长度为 1 
					printf("\n归并排序(递归)后序列为：");
					printsort(num3);
					break;
			case 8: gb_Sort_fdg(num3);
					printf("\n归并排序(非递归)后序列为：");
					printsort(num3);
					break;
			case 9: RadixSort(num3,2);//2位数 
					printf("\n基数排序后序列为：");
					printsort(num3);
					break;
			case 10:printf("已退出！！！");
					exit(0);
					break;
			default:printf("非法选择，请重新输入！！！");
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
		return 1;//空
	else
		return 0;//非空 
}

int Front(Queue Q){
	if(!isEmpty(Q))
		return Q.front->next->data;
	else
		printf("队列为空！");
}

void EnQueue(int data,Queue *Q){
	celltype *t;
	t=(celltype *)malloc(sizeof(celltype));
	t->data=data;
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
	printf("\n\t---------------------------\n");
	printf("\t|           菜单          |\n");
	printf("\t|1.冒泡排序               |\n");
	printf("\t|2.快速排序               |\n");
	printf("\t|3.插入排序               |\n");
	printf("\t|4.希尔排序               |\n");
	printf("\t|5.选择排序               |\n");
	printf("\t|6.堆排序                 |\n");
	printf("\t|7.归并排序--递归         |\n");
	printf("\t|8.归并排序--非递归       |\n");
	printf("\t|9.基数排序               |\n");
	printf("\t|10.退出！                |\n");
	printf("\t---------------------------\n");
}

void swap(int *a,int *b){
	int temp;
	temp=*a;
	*a=*b;
	*b=temp;
}

/*****冒泡排序和快排*****/ 
void maopao_Sort(int num[]){
	int i,j;
	for(i=0;i<N;i++)
		for(j=0;j<N-i-1;j++)
			if(num[j]>num[j+1])
				swap(&num[j],&num[j+1]);
}

int FindPivot(int num[],int start,int end){//快排，选基准
	int i;
	for(i=start;i<end;i++){
		if(num[i+1]>num[i])
			return num[i+1];
		else if(num[i+1]<num[i])
			return num[i];
	}
	return 0;//全相等 ,无需排序 ---此为递归终止的条件！！ 
}

int Partition(int pivot,int num[],int start,int end){//快排，分成两块，左边小于基准，右边大于等于基准
	int l,r;
	l=start;
	r=end;
	while(l<r){
		if(num[l]>=pivot && num[r]<pivot)
			swap(&num[l],&num[r]);
		while(num[l]<pivot)
			l++;
		while(num[r]>=pivot)
			r--;
	}
	return l;//此时l=r+1，l在右边，r在左边 
}

void QuickSort(int num[],int start,int end){
	int pivot,k;
	pivot=FindPivot(num,start,end);
	if(pivot!=0){ //递归终止条件 
		k=Partition(pivot,num,start,end);
		QuickSort(num,start,k-1);
		QuickSort(num,k,end);
	}
}

/*****插入排序和希尔排序*****/
void insert_Sort(int num[],int d,int k){//对于插入排序，d=1，k=0。加入这两项参数是为了方便希尔排序的调用 
	int i,j;
	for(i=1;i<=((N-k-1)/d);i++){
		j=i;
		while(num[k+j*d]<num[k+(j-1)*d]){
			swap(&num[k+j*d],&num[k+(j-1)*d]);
			j--;
			if(j==0)
				break;
		}
	}
}

void xier_Sort(int num[]){//改进的插入排序 ,可进行跨距离交换，减少了swap执行次数 
	int d=N/2;//间隔,也是分组数 
	int i;
	while(d!=0){//d=1为最后一趟排序 
		for(i=0;i<d;i++)
			insert_Sort(num,d,i);//组内调用插入排序 
		d=d/2;
	}
}

/*****选择排序和堆排序*****/
void choose_Sort(int num[]){
	int i,j,k,min;
	for(i=0;i<N;i++){
		min=num[i];
		k=i;
		for(j=i+1;j<N;j++){
			if(min>num[j]){
				k=j;
				min=num[j];
			}
		}
		swap(&num[i],&num[k]);
	}
}

void PushDown(int num[],int first,int last){//整理堆，将 A[0]下推到合适位置，并把最小(大)元素移到 A[0]-----此处选择使用最大堆，能使排序结果直接为升序 
	int k;
	k=first;
	while(2*k+1<=last){//每次循环进入下一层 
		if(2*k+1==last){//只有左子树 ,即最后一层 
			if(num[k]<num[2*k+1])
				swap(&num[k],&num[2*k+1]);
			k=last;//使循环结束 
		}
		else if(num[k]<num[2*k+1] && num[2*k+1]>num[2*k+2]){//与子树中较大的一个交换 --最大堆 
			swap(&num[k],&num[2*k+1]);
			k=2*k+1;
		}
		else if(num[k]<num[2*k+2] && num[2*k+1]<=num[2*k+2]){
			swap(&num[k],&num[2*k+2]);
			k=2*k+2;
		}
		else//相等情况 
			k=last;//使循环结束 
	}
}

void heap_Sort(int num[]){
	int i;
	for(i=(N/2)-1;i>=0;i--)
		PushDown(num,i,N-1);//初始化最大堆
	for(i=0;i<N-1;i++){
		swap(&num[0],&num[N-1-i]);//将最大元素放在末尾，末尾元素放在开头进行堆整理 
		PushDown(num,0,N-2-i);
	}
}

/*****递归和非递归的归并排序*****/
void gb_Sort_dg(int num[],int len){
	int temp[N];
	if(len<N){//递归终止条件 ,当归并长度 len >= N 时终止 
		Mpass(len,num,temp);
		len=2*len;
		Mpass(len,temp,num);
		len=2*len;
		gb_Sort_dg(num,len);//递归 
	}
}

void Merge(int left,int mid,int right,int num[],int temp[]){//left--mid, mid+1--right
	int i,j,k;
	k=left;
	i=left;
	j=mid+1;
	while(i<=mid && j<=right){
		if(num[i]<num[j]){
			temp[k]=num[i];
			i++;
			k++;
		}
		else{
			temp[k]=num[j];
			j++;
			k++;
		}
	}
	while(i<=mid){
		temp[k]=num[i];
		i++;
		k++;
	}
	while(j<=right){
		temp[k]=num[j];
		j++;
		k++;
	}
}

void Mpass(int len,int num[],int temp[]){
	int i,j=0,k;
	k=N/(2*len);
	for(i=0;i<k;i++){
		Merge(j,j+len-1,j+2*len-1,num,temp);
		j=j+2*len;
	}
	if(N-j>len && N-j<2*len)
		Merge(j,j+len-1,N-1,num,temp);
	else{
		while(j<N){
			temp[j]=num[j];
			j++;
		}
	}
}

void gb_Sort_fdg(int num[]){
	int len=1,temp[N];
	while(len<N){//归并终止条件 
		Mpass(len,num,temp);
		len=2*len;
		Mpass(len,temp,num);
		len=2*len;
	}
}

/*****基数排序(也叫桶排序)*****/  //--一种不基于比较的排序 
int Radix(int key,int pass){//求值key的右数第pass位数字
	int i,t=1;
	for(i=0;i<pass;i++)
		t=t*10;
	return key%t/(t/10);
}

void RadixSort(int num[],int figure){//有figure位 。当使用队列 A存储原序列时，可每次循环都 Makenull10个桶，然后收集时直接把各个桶链在一起，赋给 A。 
	int i,j,k,m;
	Queue Q[10];
	for(i=0;i<10;i++)
		Makenull(&Q[i]);
	for(i=0;i<figure;i++){
		for(j=0;j<N;j++){
			k=Radix(num[j],i+1);
			EnQueue(num[j],&Q[k]);
		}
		m=0;
		for(j=0;j<10;j++){
			while(!isEmpty(Q[j])){
				num[m]=Front(Q[j]);
				DeQueue(&Q[j]);
				m++;
			}
		}
	}
}

void printsort(int num[]){//打印序列 
	int i;
	for(i=0;i<N;i++)
		printf("%d ",num[i]);
}

