#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define ORDER 5
#define KMIN 2
#define KMAX 4
#define DMIN 2
#define DMAX 4
typedef enum {FALSE, TRUE} bool;

int count=0;

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
			struct BPlusTree *branch[ORDER];
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

void printRecord(Record rec){
	
	printf("\n****************************************************************************\n");

	printf("Employee Number  :%d\n", rec.employeeNumber);
	printf("Employee Name    :%s\n", rec.employeeName);
	printf("Employee Address :%s\n", rec.employeeAddress);
	printf("Designation      :%s\n", rec.designation);
	printf("Phone Number     :%d\n", rec.phoneNumber);
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
				printRecord(node->u.DNode.values[i]);
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

void InsertInKey(int value, Btree *root, Btree *rightSub, int pos){
	int i;

	for(i=root->u.KeyNode.numKeys; i>pos; i--){
		root->u.KeyNode.keys[i+1]=root->u.KeyNode.keys[i];
		root->u.KeyNode.branch[i+1]=root->u.KeyNode.branch[i];
	}
	root->u.KeyNode.keys[pos+1]=value;
	root->u.KeyNode.branch[pos+1]=rightSub;
	root->u.KeyNode.numKeys++;
}

void SplitKey(int medentry, Btree *medright, Btree *root, int pos, int *newmedian, Btree **newright)
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
		InsertInKey(medentry,root,medright,pos);
	}
	else
	{
		InsertInKey(medentry,*newright,medright, pos-median);
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
	
	if(medentry<(*newmedian)){
		InsertInDataNode(root, medentry, rec);
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

void SearchPosition(int value , Btree *root, int *pos){
	if(root->flag==0){
		if(value<root->u.KeyNode.keys[1]){
			*pos=0;
		}
		else{
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

		if(root->u.DNode.numValues<DMAX/*Maximum values in DNode*/){	
			InsertInDataNode(root, value,rec);
			return 0;
		}
		else{
			SplitLeaf(value, *rightSub, root, i, medNum, rightSub, rec);
			return 1;
		}
	}	
	else if(root->flag==0){
		SearchPosition(value, root, &pos);
		if (PushDown(value, root->u.KeyNode.branch[pos], medNum, rightSub, rec))
		{
			if(root->u.KeyNode.numKeys<ORDER){
				InsertInKey(*medNum, root, *rightSub, pos);
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
	root->u.KeyNode.keys[pos]=t->u.KeyNode.keys[1];
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
	Btree *lhs;
	Btree *rhs;
	int c;
	lhs=root->u.KeyNode.branch[pos-1];
	rhs=root->u.KeyNode.branch[pos];
	for(c=rhs->u.DNode.numValues-1;c>=0;c--)
	{
		rhs->u.DNode.values[c+1]=rhs->u.DNode.values[c];
	}
	rhs->u.DNode.numValues++;
	rhs->u.DNode.values[0]=lhs->u.DNode.values[lhs->u.DNode.numValues-1];
	root->u.KeyNode.keys[pos]=rhs->u.DNode.values[lhs->u.DNode.numValues-1].employeeNumber;	
	lhs->u.DNode.numValues--;	
}

void CombineLeaf(Btree *root,int pos)
{
	Btree *lhs,*rhs;
	int c;
	lhs=root->u.KeyNode.branch[pos-1];
	rhs=root->u.KeyNode.branch[pos];
	int elems=lhs->u.DNode.numValues;
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
}

void DeleteFromLeafDirect(int target,Btree *root)
{
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
			count--;
		}
	}
}

int RestoreLeaf(int target,Btree *root,int pos)
{
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

int RestoreKey(int target,Btree *root,int pos)
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



int Delete_rec(int target,Btree *root)
{
	int pos,k,check_count;
	if((root->u.KeyNode.branch[0])->flag)
	{
		SearchPosition(target,root,&pos);
		
		DeleteFromLeafDirect(target,root->u.KeyNode.branch[pos]);
		check_count=(root->u.KeyNode.branch[pos])->u.DNode.numValues;

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
		SearchPosition(target,root,&pos);
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


Btree * Delete(int target,Btree *root)
{
	Btree *oldroot;
	int k;
	if(root==NULL)
	{
		printf("Tree is empty.\n");
	}
	else if(root->flag)
	{
		DeleteFromLeafDirect(target,root);
	}
	else if (!root->flag)
	{
		Delete_rec(target,root);
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
	while(ptr!=NULL && ptr->u.DNode.values[i].employeeNumber<=end ){
		printRecord( ptr->u.DNode.values[i]);
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
		Btree *ptr=HeadDNode;
		while(ptr!=NULL){
			int n=ptr->u.DNode.numValues, i;
			for(i=0; i<n; i++){
				printRecord(ptr->u.DNode.values[i]);
			}
			ptr=ptr->u.DNode.next;
			printf("\n");
		}
	}
}

//This function writes into the file being pointed to by the file pointer passed as parameter
void FileWrite(Btree *root,FILE *fp){
	
	Btree *ptr=HeadDNode;
	while(ptr!=NULL){
		int n=ptr->u.DNode.numValues, i;
		for(i=0; i<n; i++){
			fprintf(fp,"%d\n", ptr->u.DNode.values[i].employeeNumber);
			fprintf(fp, "%s\n", ptr->u.DNode.values[i].employeeName);
			fprintf(fp,"%s\n", ptr->u.DNode.values[i].employeeAddress);
			fprintf(fp,"%s\n",ptr->u.DNode.values[i].designation);
			fprintf(fp, "%d\n",ptr->u.DNode.values[i].phoneNumber);
			fprintf(fp,"\n");
		}
		ptr=ptr->u.DNode.next;
		}
}

//This function reads from the file being pointed to by the file pointer passed as parameter
Btree * FileInput(Btree *root,FILE *fp){
	Record rec;
	
	char employeeName[40], designation[20], employeeAddress[100];
	int phoneNumber, employeeNumber, c=0; 
	
	while(c=getc(fp)!=EOF){			//if it is not EOF, continue reading from the file   

			fscanf(fp, "%d", &(rec.employeeNumber));
			
			fscanf(fp, "%s", rec.employeeName);	
			
			fscanf(fp, "%s", rec.employeeAddress);
			
			fscanf(fp, "%s", rec.designation);
			
			fscanf(fp, "%d", &(rec.phoneNumber));
			
			root=Insert(root, rec.employeeNumber, rec);  
		
	}
	
	return root;
}

bool checkValidity(Record rec){
	bool sc=TRUE;
	int flag, i;
	
	flag=0;
	for(i=0; rec.employeeName[i]!='\0' && !flag; i++){
		if(rec.employeeName[i]>=48 && rec.employeeName[i]<=57){
			sc=FALSE;
			flag=1;
			printf("\nSorry. Employee Name not valid!!!\n");
		}
	}
	
	flag=0;
	for(i=0; rec.designation!='\0' && !flag; i++){
		if(rec.designation[i]>=48 && rec.designation[i]<=57){
			sc=FALSE;
			flag=1;
			printf("\nSorry. Designation not valid!!!\n");
		}
	}
	
	return sc;
}


int main(int argc, char const *argv[])
{
	Btree *root=NULL;
	bool status;
	Record rec;
	int i, opertn, start, end;
	char employeeName[40], designation[20], employeeAddress[100];
	int phoneNumber, employeeNumber; 
	
	FILE *ip,*op;
	
	ip=fopen("input.txt", "r");
	root=FileInput(root,ip);
	fclose(ip);
	printTree();
	
	

	printf("\nSelect your operation from the following:\n\n\
0.To view contents of the database.\n\
1.Insert a record.\n\
2.Delete a record.\n\
3.To get number of active records.\n\
4.To get the height of the tree.\n\
5.To Search an element in Database.\n\
6.To get a range of records.\n\
7.To stop the process.\n");
	
	scanf("%d", &opertn);
	getchar();

	while(opertn!=7)
	{
		/*if the operation requires third list then we ask the user for
		the list first and then perform the operation.*/

		switch(opertn)
		{
			case 0:
				printTree();
				break;
			case 1:
			{
				printf("Enter the record to be inserted: \n");
				printf("Employee ID: ");
				scanf("%d", &rec.employeeNumber);
				printf("Employee Name: ");
				scanf("%s",rec.employeeName);
				
				printf("Employee Address: ");
				scanf("%s",rec.employeeAddress);
				printf("Designation:");
				scanf("%s",rec.designation);
				printf("Phone Number: ");
				scanf("%d", &rec.phoneNumber);	

				status=0;
				status=checkValidity(rec);
				if(status){
					root=Insert(root, rec.employeeNumber, rec);
					printTree();
				}
				break;
			}
			case 2:
			{
				printf("\nEnter the record to be deleted: \n");
				printf("Employee Number: ");
				scanf("%d", &employeeNumber);
				
				root=Delete(employeeNumber, root);

				printTree();	

				break;
			}
			case 3:
			{
				printf("The number of records are %d", getNumNodes());
				break;
			}
			case 4:
			{
				printf("The height of the tree is %d.\n", getHeight(root));
				break;
			}
			case 5:
			{
				printf("Enter the Employee ID to be searched: \n");
				scanf("%d", &employeeNumber);

				status=SearchTarget(root, employeeNumber);

				if(status==FALSE)
					printf("The Record is not present!");

				break;	
			}
			case 6:
			{
				printf("Enter the start & end ID for searching the range: ");
				scanf("%d", &start);
				scanf("%d", &end);
				RangeSearch(root,start,end);
				break;
			}
			default:
			{
				printf("\nWrong option is selected.\n");
				break;
			}
		}
		printf("\nEnter next operation: ");
		scanf("%d", &opertn);
		getchar();
	}
	op=fopen("output.txt","w");
	FileWrite(root,op);
	fclose(op);
	return 0;
}
