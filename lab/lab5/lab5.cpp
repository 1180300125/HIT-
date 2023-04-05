/*ʵ�����ݣ�
 ʵ��һ�龭��������㷨��ͨ��ʵ�����ݵ���ƣ����첻ͬ��ģ�ͷֲ�����
�����С��������к�������У������ݶ������㷨����ʱ��Ӱ��Ĺ��ɣ���֤��
�۷����������ȷ�ԡ�
ʵ��Ҫ��
1�� ʵ�������������򷽷��е�һ�������㷨�� 
��1�� ð������Ϳ�������
��2�� ���������ϣ������
��3�� ѡ������Ͷ�����
��4�� �ݹ�ͷǵݹ�Ĺ鲢����
2�� ������ͬ��ģ�ͷֲ������ݣ��� Excel �����㷨ִ��ʱ�� T(n)���������ģ
n �����ߵ���ʽ�����������ģ�ͷֲ������򷽷�����ʱ��仯���Ƶ�Ӱ�죬
�������۷�������Ƚϡ�*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define N 21

typedef struct cell{//����Ԫ�ص��� 
	int data;
	struct cell *next;
}celltype;

typedef struct queue{//���� 
	celltype *front;
	celltype *rear;
}Queue;

void Makenull(Queue *Q);//Ҫ�޸�ָ�룬����ָ��ĵ�ַ
int isEmpty(Queue Q);
int Front(Queue Q);
void EnQueue(int data,Queue *Q);//Ҫ�޸�ָ�룬�贫��ָ��ĵ�ַ 
void DeQueue(Queue *Q);//�ı�ָ�룬�贫��ָ��ĵ�ַ 

void swap(int *a,int *b);//���� 
/*****ð������Ϳ���*****/ 
void maopao_Sort(int num[]);
int FindPivot(int num[],int start,int end);//���ţ�ѡ��׼
int Partition(int pivot,int num[],int start,int end);//���ţ��ֳ����飬���С�ڻ�׼���ұߴ��ڵ��ڻ�׼ 
void QuickSort(int num[],int start,int end);

/*****���������ϣ������*****/
void insert_Sort(int num[],int d,int k);
void xier_Sort(int num[]);

/*****ѡ������Ͷ�����*****/
void choose_Sort(int num[]);
void PushDown(int num[],int first,int last);//����ѣ��� A[1]���Ƶ�����λ�ã�������СԪ���Ƶ� A[1] 
void heap_Sort(int num[]);

/*****�ݹ�ͷǵݹ�Ĺ鲢����*****/
void gb_Sort_dg(int num[],int len);
void Merge(int left,int mid,int right,int num[],int temp[]);
void Mpass(int len,int num[],int temp[]);
void gb_Sort_fdg(int num[]);

/*****��������(Ҳ��Ͱ����)*****/  //--һ�ֲ����ڱȽϵ����� 
int Radix(int key,int pass);//��ֵkey��������passλ���� 
void RadixSort(int num[],int figure);//��figureλ 

void printsort(int num[]);
void menu();

int main(){
	int num1[N];//�������� 
	int num2[N];//�������� 
	int num3[N];//������� 
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
		printf("ԭ�������Ϊ��");
		printsort(num3);
		printf("\n���������ѡ��");
		scanf("%d",&y);
		switch(y){
			case 1: maopao_Sort(num3);
					printf("\nð�����������Ϊ��");
					printsort(num3);
					break;
			case 2: QuickSort(num3,0,N-1);
					printf("\n�������������Ϊ��");
					printsort(num3);
					break;
			case 3: insert_Sort(num3,1,0);
					printf("\n�������������Ϊ��");
					printsort(num3);
					break;
			case 4: xier_Sort(num3);
					printf("\nϣ�����������Ϊ��");
					printsort(num3);
					break;
			case 5: choose_Sort(num3);
					printf("\nѡ�����������Ϊ��");
					printsort(num3);
					break;
			case 6: heap_Sort(num3);
					printf("\n�����������Ϊ��");
					printsort(num3);
					break;
			case 7: gb_Sort_dg(num3,1);//��ʼ�鲢����Ϊ 1 
					printf("\n�鲢����(�ݹ�)������Ϊ��");
					printsort(num3);
					break;
			case 8: gb_Sort_fdg(num3);
					printf("\n�鲢����(�ǵݹ�)������Ϊ��");
					printsort(num3);
					break;
			case 9: RadixSort(num3,2);//2λ�� 
					printf("\n�������������Ϊ��");
					printsort(num3);
					break;
			case 10:printf("���˳�������");
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

int Front(Queue Q){
	if(!isEmpty(Q))
		return Q.front->next->data;
	else
		printf("����Ϊ�գ�");
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
	printf("\t|           �˵�          |\n");
	printf("\t|1.ð������               |\n");
	printf("\t|2.��������               |\n");
	printf("\t|3.��������               |\n");
	printf("\t|4.ϣ������               |\n");
	printf("\t|5.ѡ������               |\n");
	printf("\t|6.������                 |\n");
	printf("\t|7.�鲢����--�ݹ�         |\n");
	printf("\t|8.�鲢����--�ǵݹ�       |\n");
	printf("\t|9.��������               |\n");
	printf("\t|10.�˳���                |\n");
	printf("\t---------------------------\n");
}

void swap(int *a,int *b){
	int temp;
	temp=*a;
	*a=*b;
	*b=temp;
}

/*****ð������Ϳ���*****/ 
void maopao_Sort(int num[]){
	int i,j;
	for(i=0;i<N;i++)
		for(j=0;j<N-i-1;j++)
			if(num[j]>num[j+1])
				swap(&num[j],&num[j+1]);
}

int FindPivot(int num[],int start,int end){//���ţ�ѡ��׼
	int i;
	for(i=start;i<end;i++){
		if(num[i+1]>num[i])
			return num[i+1];
		else if(num[i+1]<num[i])
			return num[i];
	}
	return 0;//ȫ��� ,�������� ---��Ϊ�ݹ���ֹ���������� 
}

int Partition(int pivot,int num[],int start,int end){//���ţ��ֳ����飬���С�ڻ�׼���ұߴ��ڵ��ڻ�׼
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
	return l;//��ʱl=r+1��l���ұߣ�r����� 
}

void QuickSort(int num[],int start,int end){
	int pivot,k;
	pivot=FindPivot(num,start,end);
	if(pivot!=0){ //�ݹ���ֹ���� 
		k=Partition(pivot,num,start,end);
		QuickSort(num,start,k-1);
		QuickSort(num,k,end);
	}
}

/*****���������ϣ������*****/
void insert_Sort(int num[],int d,int k){//���ڲ�������d=1��k=0�����������������Ϊ�˷���ϣ������ĵ��� 
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

void xier_Sort(int num[]){//�Ľ��Ĳ������� ,�ɽ��п���뽻����������swapִ�д��� 
	int d=N/2;//���,Ҳ�Ƿ����� 
	int i;
	while(d!=0){//d=1Ϊ���һ������ 
		for(i=0;i<d;i++)
			insert_Sort(num,d,i);//���ڵ��ò������� 
		d=d/2;
	}
}

/*****ѡ������Ͷ�����*****/
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

void PushDown(int num[],int first,int last){//����ѣ��� A[0]���Ƶ�����λ�ã�������С(��)Ԫ���Ƶ� A[0]-----�˴�ѡ��ʹ�����ѣ���ʹ������ֱ��Ϊ���� 
	int k;
	k=first;
	while(2*k+1<=last){//ÿ��ѭ��������һ�� 
		if(2*k+1==last){//ֻ�������� ,�����һ�� 
			if(num[k]<num[2*k+1])
				swap(&num[k],&num[2*k+1]);
			k=last;//ʹѭ������ 
		}
		else if(num[k]<num[2*k+1] && num[2*k+1]>num[2*k+2]){//�������нϴ��һ������ --���� 
			swap(&num[k],&num[2*k+1]);
			k=2*k+1;
		}
		else if(num[k]<num[2*k+2] && num[2*k+1]<=num[2*k+2]){
			swap(&num[k],&num[2*k+2]);
			k=2*k+2;
		}
		else//������ 
			k=last;//ʹѭ������ 
	}
}

void heap_Sort(int num[]){
	int i;
	for(i=(N/2)-1;i>=0;i--)
		PushDown(num,i,N-1);//��ʼ������
	for(i=0;i<N-1;i++){
		swap(&num[0],&num[N-1-i]);//�����Ԫ�ط���ĩβ��ĩβԪ�ط��ڿ�ͷ���ж����� 
		PushDown(num,0,N-2-i);
	}
}

/*****�ݹ�ͷǵݹ�Ĺ鲢����*****/
void gb_Sort_dg(int num[],int len){
	int temp[N];
	if(len<N){//�ݹ���ֹ���� ,���鲢���� len >= N ʱ��ֹ 
		Mpass(len,num,temp);
		len=2*len;
		Mpass(len,temp,num);
		len=2*len;
		gb_Sort_dg(num,len);//�ݹ� 
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
	while(len<N){//�鲢��ֹ���� 
		Mpass(len,num,temp);
		len=2*len;
		Mpass(len,temp,num);
		len=2*len;
	}
}

/*****��������(Ҳ��Ͱ����)*****/  //--һ�ֲ����ڱȽϵ����� 
int Radix(int key,int pass){//��ֵkey��������passλ����
	int i,t=1;
	for(i=0;i<pass;i++)
		t=t*10;
	return key%t/(t/10);
}

void RadixSort(int num[],int figure){//��figureλ ����ʹ�ö��� A�洢ԭ����ʱ����ÿ��ѭ���� Makenull10��Ͱ��Ȼ���ռ�ʱֱ�ӰѸ���Ͱ����һ�𣬸��� A�� 
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

void printsort(int num[]){//��ӡ���� 
	int i;
	for(i=0;i<N;i++)
		printf("%d ",num[i]);
}

