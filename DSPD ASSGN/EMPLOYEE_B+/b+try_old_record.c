#include "stdio.h"
#include "stdlib.h"
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
int count=0;

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

int ifExist(Btree *root, int value, int *position){
	int i,flag=0;

	for(i=0; i<root->u.DNode.numValues && !flag; i++){
		if(value==root->u.DNode.values[i].employeeNumber){
			flag=1;
			*position=i;
		}
	}
	return flag;
}


void InsertInDataNode(Btree *root, int value, Record rec){
	int i=root->u.DNode.numValues-1;
	int position;
	if(ifExist(root, value, &position)){
		root->u.DNode.values[position]=rec;
	}
	else{
		while(value<root->u.DNode.values[i].employeeNumber && i>=0){
		root->u.DNode.values[i+1]=root->u.DNode.values[i];
		i--;
		}

		root->u.DNode.values[i+1]=rec;
		root->u.DNode.numValues++;

		count++;
	}
	
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
		InsertInKey(medentry,root,medright,pos,rec);
	}
	else
	{
		InsertInKey(medentry,root,*newright,pos-median,rec);
	}
	*newmedian=root->u.KeyNode.keys[root->u.KeyNode.numKeys];
	(*newright)->u.KeyNode.branch[0]=root->u.KeyNode.branch[root->u.KeyNode.numKeys];
	root->u.KeyNode.numKeys--;
}

void SplitLeaf(int medentry, Btree *medright, Btree *root, int pos, int *newmedian, Btree **newright, Record rec){
	int i,median;
	if(pos<=DMIN-1){
		median=DMIN-1;
	}
	else{
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

	if(medentry<(*newmedian)){
		InsertInDataNode(root, medentry,rec);
	}
	else{
		InsertInDataNode((*newright), medentry, rec);
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
	if(root->flag){
		int i=0;
		while(i<root->u.DNode.numValues && value>root->u.DNode.values[i].employeeNumber){
			i++;
		}

		if(root->u.DNode.numValues<DMAX){
			InsertInDataNode(root, value,rec);
			return 0;
		}
		else{
			SplitLeaf(value, *rightSub, root, i, medNum, rightSub, rec);
			return 1;
		}
	}	
	else if(root->flag==0){
		SearchPosition(value, root, &pos,rec);
		if (PushDown(value, root->u.KeyNode.branch[pos], medNum, rightSub,rec))
		{
			if(root->u.KeyNode.numKeys<ORDER){
				InsertInKey(value, root, *rightSub, pos, rec);
				return 0;
			}
			else{
				SplitKey(value, *rightSub, root, pos, medNum, rightSub,rec);
				return 1;
			}
		}

		return 0;
	}
}

Btree * Insert(Btree *root, int value, Record rec){
	int medNum;
	Btree *rightSub, *newRoot;

	if(!root){
		Btree *nptr=(Btree *)malloc(sizeof(Btree));

		nptr->u.DNode.values[0]=rec;
		nptr->u.DNode.numValues=1;
		nptr->u.DNode.next=nptr->u.DNode.prev=NULL;
		nptr->flag=1;
		root=nptr;
		HeadDNode=nptr;

		count++;
	}
	else if(PushDown(value, root, &medNum, &rightSub, rec)){
		newRoot = (Btree *)malloc(sizeof(Btree));

		newRoot->flag=0;
		newRoot->u.KeyNode.keys[1]=medNum;
		newRoot->u.KeyNode.numKeys=1;
		newRoot->u.KeyNode.branch[0]=root;
		newRoot->u.KeyNode.branch[1]=rightSub;
		return newRoot;
	}

	return root;
}


void MoveLeftKey(Btree *root,int pos)
{
	int c;
	Btree *t;
	t=root->u.KeyNode.branch[pos-1];
	t->u.KeyNode.numKeys++;
	t->u.KeyNode.keys[t->u.KeyNode.numKeys]=root->u.KeyNode.keys[pos];
	t->u.KeyNode.branch[t->u.KeyNode.numKeys]=(root->u.KeyNode.branch[pos])->u.KeyNode.branch[0];
	t=root->u.KeyNode.branch[pos];
	root->u.KeyNode.keys[pos]=t->u.key.keys[1];
	t->u.KeyNode.branch[0]=t->u.KeyNode.branch[1];
	t->u.KeyNode.numKeys--;
	for(c=1;c<=t->u.KeyNode.numKeys;c++)
	{
		t->u.KeyNode.keys[c]=t->u.KeyNode.keys[c+1];
		t->u.KeyNode.branch[c]=t->u.KeyNode.branch[c+1];
	}
}


void MoveRightKey(Btree *root,int pos)
{
	int c;
	Btree *t;
	t=root->u.KeyNode.branch[pos];
	for(c=t->u.KeyNode.numKeys;c>0;c--)
	{
		t->u.KeyNode.keys[c+1]=t->u.KeyNode.keys[c];
		t->u.KeyNode.branch[c+1]=t->u.KeyNode.branch[c];
	}
	t->u.KeyNode.branch[1]=t->u.KeyNode.branch[0];
	t->u.KeyNode.numKeys++;
	t->u.KeyNode.keys[1]=root->u.KeyNode.keys[pos];
	t=root->u.KeyNode.branch[pos-1];
	root->u.KeyNode.keys[pos]=t->u.KeyNode.keys[t->u.KeyNode.numKeys];
	(root->u.KeyNode.branch[pos])->u.KeyNode.branch[0]=t->u.KeyNode.branch[t->u.KeyNode.numKeys];
	t->u.KeyNode.numKeys--;
}

void CombineKey(Btree *root, int pos)
{
	int c;
	Btree * right, * left;

	right=root->u.KeyNode.branch[pos];
	left=root->u.KeyNode.branch[pos-1];
	left->u.KeyNode.numKeys++;
	
	left->u.KeyNode.keys[left->u.KeyNode.numKeys]=root->u.KeyNode.keys[pos];
	left->u.KeyNode.branch[left->u.KeyNode.numKeys]=right->u.KeyNode.branch[0];
	
	for(c=1;c<=right->u.KeyNode.numKeys;c++)
	{
		left->u.KeyNode.numKeys++;
		left->u.KeyNode.keys[left->u.KeyNode.numKeys]=right->u.KeyNode.keys[c];
		left->u.KeyNode.branch[left->u.KeyNode.numKeys]=right->u.KeyNode.branch[c];
	}
	
	for(c=pos;c<root->u.KeyNode.numKeys;c++)
	{
		root->u.KeyNode.keys[c]=root->u.KeyNode.keys[c+1];
		root->u.KeyNode.branch[c]=root->u.KeyNode.branch[c+1];
	}
	
	root->u.KeyNode.numKeys--;
	free(right);		
}


void MoveLeftLeaf(Btree *root,int pos)
{
	Btree *lhs;
	Btree *rhs;
	int c;
	lhs=root->u.KeyNode.branch[pos-1];
	rhs=root->u.KeyNode.branch[pos];
	lhs->u.DNode.values[lhs->u.DNode.numValues]=rhs->u.DNode.values[0];
	lhs->u.DNode.numValues++;
	root->u.KeyNode.keys[pos]=rhs->u.DNode.values[1].employeeNumber;
	for(c=1;c<rhs->u.DNode.numValues;c++)
	{
		rhs->u.DNode.values[c-1]=rhs->u.DNode.values[c];
		
	}
	rhs->u.DNode.numValues--;
}

void MoveRightLeaf(Btree *root,int pos)
{
	record *lhs;
	record *rhs;
	int c;
	lhs=root->u.KeyNode.branch[pos-1];
	rhs=root->u.KeyNode.branch[pos];
	for(c=rhs->u.DNode.numValues-1;c>=0;c--)
	{
		rhs->u.DNode.values[c+1]=rhs->u.DNode.values[c];
	}
	rhs->u.DNode.numValues++;
	rhs->u.DNode.values[0]=lhs->u.DNode.values[lhs->u.DNode.numValues-1];
	root->u.KeyNode.keys[pos]=rhs->u.DNode.values[lhs->u.DNode.numValues-1].employeeNumber;	//should be rhs->u.data.arr[0].account_no
	lhs->u.DNode.numValues--;	
}

void CombineLeaf(Btree *root,int pos)
{
	printf("In combine leaf\n");
	record *lhs,*rhs;
	int c;
	printf("Pos is %d\n",pos);
	lhs=root->u.KeyNode.branch[pos-1];
	rhs=root->u.KeyNode.branch[pos];
	int elems=lhs->u.data.dataCount;
	printf("count in left tree is %d and right is %d\n",elems,rhs->u.data.dataCount);
	/*for(c=1;c<=root->u.KeyNode.numKeys;c++)
	{
		printf("Acc no:%d\n",root->u.key.acc_no[c]);
	}*/
	for(c=0;c<rhs->u.DNode.numValues;c++)
	{
		lhs->u.DNode.values[elems]=rhs->u.DNode.values[c];
		elems++;
	}
	for(c=pos+1;c<=root->u.KeyNode.numKeys;c++)
	{
		root->u.KeyNode.keys[c-1]=root->u.KeyNode.keys[c];
		root->u.KeyNode.branch[c-1]=root->u.KeyNode.branch[c];
	}
	lhs->u.DNode.next=rhs->u.DNode.next;
	if(rhs->u.DNode.next!=NULL)
	{
		(rhs->u.DNode.next)->u.DNode.prev=lhs;
	}
	lhs->u.DNode.numValues=elems;
	root->u.KeyNode.numKeys--;
	free(rhs);
	printf("*************Root in cobine\n");
	/*for(c=1;c<=root->u.KeyNode.numKeys;c++)
	{
		printf("Acc no:%d\n",root->u.key.acc_no[c]);
	}
	printf("#################################Tree after combine\n");
	printTree(root);*/
	
}

void DeleteFromLeafDirect(int target,Btree *root)
{
	printf("in delete from leaf direct\n");
	int pos,i=0;
	if(root->flag)
	{
		while(root->u.DNode.values[i].employeeNumber<target)
		{
			i++;
		}
		if(root->u.DNode.values[i].employeeNumber>target)
		{
			printf("ENTRY TO BE DELETED IS ABSENT\n");
		}
		else if(root->u.DNode.values[i].employeeNumber==target)
		{
			i++;
			for(i;i<root->u.DNode.numValues;i++)
			{
				root->u.DNode.values[i-1]=root->u.DNode.values[i];
			}
			root->u.DNode.numValues--;
		}
		printf("$$$$$$$$$$$");
		printTree(root);
	}
}

//Pos is always the right node
int RestoreLeaf(int target,Btree *root,int pos)
{
	printf("In restore leaf\n");
	int k=0;
	int retval=0;
	if(pos==0)
	{
		if((root->u.KeyNode.branch[1])->u.DNode.numValues>DMIN)
		{
			MoveLeftLeaf(root,1);
		}
		else
		{
			printf("Going to combine leaf\n");
			CombineLeaf(root,1);
			retval=1;
		}
	}
	else if(pos==root->u.KeyNode.numKeys)
	{
		if((root->u.KeyNode.branch[pos-1])->u.DNode.numValues>DMIN)
		{
			MoveRightLeaf(root,pos);
		}
		else
		{
			CombineLeaf(root,pos);
			retval=1;
		}
	}
	else if((root->u.KeyNode.branch[pos-1])->u.DNode.numValues>DMIN)
	{
		MoveRightLeaf(root,pos);
	}
	else if((root->u.KeyNode.branch[pos+1])->u.DNode.numValues>DMIN)
	{
		MoveLeftLeaf(root,pos+1);
	}
	else
	{
		CombineLeaf(root,pos);
		retval=1;
	}
	return retval;
	
}

int RestoreKey(int target,record *root,int pos)
{
	int k=0;
	int retval=0;
	if(pos==0)
	{
		if((root->u.KeyNode.branch[1])->u.KeyNode.numKeys>KMIN)
		{
			MoveLeftKey(root,1);
		}
		else
		{
			CombineKey(root,1);
			retval=1;
		}
	}
	else if(pos==root->u.KeyNode.numKeys)
	{
		if((root->u.KeyNode.branch[pos-1])->u.KeyNode.numKeys>KMIN)
		{
			MoveRightKey(root,pos);
		}
		else
		{
			CombineKey(root,pos);
			retval=1;
		}
	}
	else if((root->u.KeyNode.branch[pos-1])->u.KeyNode.numKeys>KMIN)
	{
		MoveRightKey(root,pos);
	}
	else if((root->u.KeyNode.branch[pos+1])->u.KeyNode.numKeys>KMIN)
	{
		MoveLeftKey(root,pos+1);
	}
	else
	{
		CombineKey(root,pos);
		retval=1;
	}
	return retval;
}



int Delete_rec(int target,Btree *root,Record rec)
{
	printf("in delete-rec\n");
	int pos,k,check_count;
	if((root->u.KeyNode.branch[0])->flag)
	{
		searchPosition(target,root,&pos, rec);
		printf("pos is %d\n",pos);
		DeleteFromLeafDirect(target,root->u.KeyNode.branch[pos]);
		check_count=(root->u.KeyNode.branch[pos])->u.DNode.numValues;
		printf("\n datacount aft deletn is %d\n",check_count);
		if(check_count>=DMIN)
		{
			return 0;
		}
		else
		{
			k=RestoreLeaf(target,root,pos);		//returns 1 if merge else 0
			return k;
			
		}
	}
	else
	{
		searchPosition(target,root,&pos,rec);
		if(Delete_rec(target,root->u.KeyNode.branch[pos]))
		{
			check_count=(root->u.KeyNode.branch[pos])->u.KeyNode.numKeys;
			if(check_count>=KMIN)
			{
				return 0;
			}
			else
			{
				k=RestoreKey(target,root,pos);
				return k;
			}
			
		}
		
		
	}
	return 0;
}


Btree * Delete(int target,Btree *root, Record rec)
{
	Btree *oldroot;
	int k;
	if(root==NULL)
	{
		printf("Tree is empty\n");
	}
	else if(root->flag)
	{
		DeleteFromLeafDirect(target,root);
	}
	else if (!root->flag)
	{
		printf("in delete- flag k\n");
		Delete_rec(target,root,rec);						//returns some value
		if(root->u.KeyNode.numKeys==0)
		{
			oldroot=root;
			root=root->u.KeyNode.branch[0];
			free(oldroot);
		}
	}
	
	return root;
}

int getNumNodes(){
	return count;
}

int getHeight(Btree *root){
	Btree *ptr=root;
	int ht=0;
	if(root==NULL){
		return ht;
	}
	else{
		while(!ptr->flag){
		ht++;
		ptr=ptr->u.KeyNode.branch[0];
		}
		return ht;
	}
	
}

void RangeSearch(Btree *root, int start, int end){
	Btree *ptr;
	int i;

	ptr=SearchNode(root, start);

	for(i=0; i<ptr->u.DNode.numValues; i++){
		if(ptr->u.DNode.values[i].employeeNumber==start)
			break;
	}

	while(ptr->u.DNode.values[i].employeeNumber<=end){
		printRecord(ptr->u.DNode.values[i]);
		i++;
		if(i>=ptr->u.DNode.numValues){
			ptr=ptr->u.DNode.next;
			i=0;
		}
	}

}

void printTree(){
	if(!HeadDNode){
		printf("Tree is empty;\n");
	}
	else{
		//printf("asadasd");
		Btree *ptr=HeadDNode;
		while(ptr!=NULL){
		//	printf("dkasa");
			int n=ptr->u.DNode.numValues, i;
			for(i=0; i<n; i++){
				printRecord(ptr->u.DNode.values[i]);
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
	
	printf("%d\n", getNumNodes());
	printf("%d\n", getHeight(root));

	RangeSearch(root, 3, 10);
	return 0;
}
