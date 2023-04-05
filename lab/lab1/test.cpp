#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Tree{
	int data;
	struct Tree *lchild;
	struct Tree *rchild;
}BST;
int deletemin(BST *T);//删除最小元素---右子树的最左结点 
void deleteBST(int key,BST *T);//BST删除
void in_order(BST *T);//中序遍历
main(){
	BST *p,*t,*r,*o;
	p=(BST *)malloc(sizeof(BST));
	p->data=3;
	p->lchild=NULL;
	p->rchild=NULL;
	
	t=(BST *)malloc(sizeof(BST));
	t->data=4;
	t->lchild=NULL;
	t->rchild=NULL;
	
	r=(BST *)malloc(sizeof(BST));
	r->data=1;
	r->lchild=NULL;
	r->rchild=NULL;
	
	o=(BST *)malloc(sizeof(BST));
	o->data=2;
	o->lchild=NULL;
	o->rchild=NULL;
	
	p->rchild=t;
	p->lchild=r;
	r->rchild=o;
	
	deleteBST(4,p);
	in_order(p);
	printf("end");
}
void in_order(BST *T){//中序遍历 --左根右 
	if(T!=NULL){
		in_order(T->lchild);
		printf("%d ",T->data);
		in_order(T->rchild);
	}
}
int deletemin(BST *T){//删除最小元素---右子树的最左结点 
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
 
void deleteBST(int key,BST *T){//BST删除
	BST *p;
	if(T!=NULL){
		if(key==T->data){
			if(T->lchild==NULL){//如果左子树为空，右链直接继承 
				p=T;
				T=p->rchild;
				free(p);
			}
			else if(T->rchild==NULL){//如果右子树为空，左链直接继承 
				p=T;
				T=p->lchild;
				free(p);
			}
			else{//如果有两棵子树，选择右子树的最左结点为继承结点 
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
				if(T->lchild->lchild==NULL){//如果左子树为空，右链直接继承 
					p=T->lchild;
					T->lchild=p->rchild;
					free(p);
				}
				else if(T->lchild->rchild==NULL){//如果右子树为空，左链直接继承 
					p=T->lchild;
					T->lchild=p->lchild;
					free(p);
				}
				else{//如果有两棵子树，选择右子树的最左结点为继承结点 
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
				if(T->rchild->lchild==NULL){//如果左子树为空，右链直接继承 
					p=T->rchild;
					T->rchild=p->rchild;
					free(p);
				}
				else if(T->rchild->rchild==NULL){//如果右子树为空，左链直接继承 
					p=T->rchild;
					T->rchild=p->lchild;
					free(p);
				}
				else{//如果有两棵子树，选择右子树的最左结点为继承结点 
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
		printf("无此结点！\n"); 
}
