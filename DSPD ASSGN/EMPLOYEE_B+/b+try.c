#include <stdio.h>
#include <stdlib.h>
#define ORDER 5
#define KMIN 2
#define KMAX 4
#define DMIN 2
#define DMAX 4
typedef enum {FALSE, TRUE} bool;

typedef struct employeeRecord
{
	int employeeNumber;
	char employeeName[20];
	char employeeAddress[20];
	char designation[20];
	int phoneNumber;
}Record;


typedef struct BPlusTree{
	union{
		struct KeyNodes
		{
			int keys[ORDER];
			struct BPlusTree *branch[ORDER+1];
			int numKeys;
		}KeyNode;

		struct DNodes{
			Record values[DMAX+1];
			int numValues;
			struct BPlusTree *next, *prev;
		}DNode;
	}u;
	int flag;
}Btree;

Btree * HeadDNode=NULL;


Btree * SearchNode(Btree *root, int target){

	if(!(root->flag)){
		int i=1;
		while(i<=root->u.KeyNode.numKeys && root->u.KeyNode.keys[i]<=target){
			i++;
		}
		root=SearchNode(root->u.KeyNode.branch[i-1], target);
	}

	return root;
}

bool SearchInNode(Btree *node, int target){

	if(!node){
		return FALSE;
	}
	else{
		int n=node->u.DNode.numValues, i, temp;
		for(i=0; i<n; i++){
			temp=node->u.DNode.values[i].employeeNumber;
			if(temp==target){
				return TRUE;
			}
		}
		return FALSE;
	}
}

bool SearchTarget(Btree *root, int target){
	Btree *ptr=root;
	ptr=SearchNode(ptr, target);
	return SearchInNode(ptr, target);

}



void InsertInDataNode(Btree *root, int employeeNumber, char employeeName[], char employeeAddress[], char designation[], int phoneNumber ){
	int i=root->u.DNode.numValues-1;

	while(employeeNumber<root->u.DNode.values[i].employeeNumber && i>=0){
		root->u.DNode.values[i+1]=root->u.DNode.values[i];
		i--;
	}
	root->u.DNode.values[i+1].employeeNumber=employeeNumber;
	strcpy(root->u.DNode.values[i+1].employeeName, employeeName);
	strcpy(root->u.DNode.values[i+1].employeeAddress, employeeAddress);
	strcpy(root->u.DNode.values[i+1].designation, designation);
	root->u.DNode.values[i+1].phoneNumber=phoneNumber;
	root->u.DNode.numValues++;
}

void InsertInKey(int value, Btree *root, Btree *rightSub, int pos, Record rec){
	int i;

	for(i=root->u.KeyNode.numKeys; i>pos; i--){
		root->u.KeyNode.keys[i+1]=root->u.KeyNode.keys[i];
		root->u.KeyNode.branch[i+1]=root->u.KeyNode.branch[i];
	}
	root->u.KeyNode.keys[pos+1]=value;
	root->u.KeyNode.branch[pos+1]=rightSub;
	root->u.KeyNode.numKeys++;
}

void SplitKey(int medentry, Btree *medright, Btree *root, int pos, int *newmedian, Btree **newright, Record rec)
{
	int i;
	int median;
	if(pos<=KMIN)
	{
		median=KMIN;
	}
	else
	{
		median=KMIN+1;
	}
	*newright=(Btree *)malloc(sizeof(Btree));
	(*newright)->flag=0;
	for(i=median+1;i<=KMAX;i++)
	{
		(*newright)->u.KeyNode.keys[i-median]=root->u.KeyNode.keys[i];
		(*newright)->u.KeyNode.branch[i-median]=root->u.KeyNode.branch[i];
	}
	(*newright)->u.KeyNode.numKeys=KMAX-median;
	root->u.KeyNode.numKeys=median;
	if(pos<=KMIN)
	{
		InsertInKey(medentry,root,medright,pos, Record rec);
	}
	else
	{
		InsertInKey(medentry,root,*newright,pos-median);
	}
	*newmedian=root->u.KeyNode.keys[root->u.KeyNode.numKeys];
	(*newright)->u.KeyNode.branch[0]=root->u.KeyNode.branch[root->u.KeyNode.numKeys];
	root->u.KeyNode.numKeys--;
}

void SplitLeaf(int medentry, Btree *medright, Btree *root, int pos, int *newmedian, Btree **newright, Record rec){
	int i,median;
	if(pos<=DMIN-1)
	{
		median=DMIN-1;
	}
	else
	{
		median=DMIN;
	}
	*newright=(Btree *)malloc(sizeof(Btree));
	(*newright)->flag=1;
	for(i=median;i<DMAX;i++){
		(*newright)->u.DNode.values[i-median]=root->u.DNode.values[i];
	}
	(*newright)->u.DNode.numValues=DMAX-median;
	root->u.DNode.numValues=median;
	*newmedian=(*newright)->u.DNode.values[0].employeeNumber;
	//printf("ok2\n");
	if(medentry<(*newmedian)){
		InsertInDataNode(root, medentry);
	}
	else{
		InsertInDataNode((*newright), medentry);
	}
	(*newright)->u.DNode.next=root->u.DNode.next;
	Btree *ptr=(root->u.DNode.next);
	if(ptr!=NULL){
		ptr->u.DNode.prev=(*newright);
	}
	(*newright)->u.DNode.prev=root;
	root->u.DNode.next=(*newright);
}

void SearchPosition(int value , Btree *root, int *pos, Record rec)
{
	printf("keys:%d\n", root->u.KeyNode.numKeys);
	if(root->flag==0)
	{
		if(value<root->u.KeyNode.keys[1])
		{
			*pos=0;
		}
		else
		{
			for(*pos=root->u.KeyNode.numKeys; value<root->u.KeyNode.keys[*pos]; *pos=*pos-1)
			;	
		}
	}
}

int PushDown(int value, Btree *root, int *medNum, Btree **rightSub, Record rec){
	int pos;
	//printf("adsadada\n");
	if(root->flag){
		int i=0;
		while(i<root->u.DNode.numValues && value>root->u.DNode.values[i].employeeNumber){
			i++;
		}

		if(root->u.DNode.numValues<DMAX/*Maximum values in DNode*/){
			InsertInDataNode(root, value);
			return 0;
		}
		else{
			SplitLeaf(value, *rightSub, root, i, medNum, rightSub);
			return 1;
		}
	}	
	else if(root->flag==0){
		SearchPosition(value, root, &pos);
		if (PushDown(value, root->u.KeyNode.branch[pos], medNum, rightSub))
		{
			if(root->u.KeyNode.numKeys<ORDER){
				InsertInKey(value, root, *rightSub, pos);
				return 0;
			}
			else{
				SplitKey(value, *rightSub, root, pos, medNum, rightSub);
				return 1;
			}
		}
		return 0;
	}
}

Btree * Insert(Btree *root, int employeeNumber, char[] employeeName, char[] employeeAddress, char[] designation, int phoneNumber, Record rec){
	int medNum;
	Btree *rightSub, *newRoot;

	if(!root){
		Btree *nptr=(Btree *)malloc(sizeof(Btree));

		nptr->u.DNode.values[0].employeeNumber=employeeNumber;
		strcpy(nptr->u.DNode.values[i+1].employeeName, employeeName);
		strcpy(nptr->u.DNode.values[i+1].employeeAddress, employeeAddress);
		nptr->u.DNode.values[0].designation=designation;
		nptr->u.DNode.values[0].phoneNumber=phoneNumber;
		nptr->u.DNode.numValues=1;
		nptr->u.DNode.next=nptr->u.DNode.prev=NULL;
		nptr->flag=1;
		root=nptr;
		HeadDNode=nptr;
	}
	else if(PushDown(employeeNumber, root, &medNum, &rightSub)){
		newRoot = (Btree *)malloc(sizeof(Btree));

		newRoot->flag=0;
		newRoot->u.KeyNode.keys[1]=medNum;
		newRoot->u.KeyNode.numKeys=1;
		newRoot->u.KeyNode.branch[0]=root;
		newRoot->u.KeyNode.branch[1]=rightSub;
		printf("newkey%d\n",newRoot->u.KeyNode.keys[1]);
		return newRoot;
	}
	return root;
}



void printTree(){
	if(!HeadDNode){
		printf("Tree is empty;\n");
	}
	else{
		Btree *ptr=HeadDNode;
		while(ptr!=NULL){
			int n=ptr->u.DNode.numValues, i;
			for(i=0; i<n; i++){
				printf("%d\t", ptr->u.DNode.values[i].employeeNumber);
			}
			ptr=ptr->u.DNode.next;
			printf("\n");
		}
	}
}

int main(int argc, char const *argv[])
{

	int i=0, n;
	Btree *root=NULL;
	while(i<11){
		scanf("%d", &n);
		root=Insert(root, n);
		i++;
	}

	printTree();
	
	printf("%d\n", SearchTarget(root, 4));
	printf("%d\n", SearchTarget(root, 411));
	
	return 0;
}
