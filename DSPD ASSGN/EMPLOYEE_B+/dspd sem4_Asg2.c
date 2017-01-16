#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#define m 5
#define DATA_SIZE 3
#define MIN_DATASIZE 2
#define MAX 4
#define MIN 2

int Num_rec=0;

typedef struct info_tag{
	char student_name[100];
	unsigned int roll_number;
	char address[1000];
	unsigned int semester_number;
	char department_name[10];
}info;
typedef struct union_tag{
	union btree{
		struct key_nodes{
			unsigned int r_no[m+1];
			struct union_tag * ptr[m+1];
			int count;
		}key;
		struct data_nodes{
			info arr[DATA_SIZE+1];
			struct union_tag * next;
			struct union_tag * prev;
			int dataCount;
		}data;

	}u;
	char flag;
}record;

record * searchNode(record *root, unsigned int no)
{
	if(root->flag=='k')
	{
		int i=1;
		while(root->u.key.r_no[i]<=no && i<=root->u.key.count)
		{
			i++;
		}
		root=searchNode(root->u.key.ptr[i-1],no);

	}
	return root;
}

void searchValueInDataNode(record *dptr, unsigned int val)
{
	int i;
	if(dptr==NULL)
	{
		printf("Error\n");
	}
	else if(dptr->flag=='d')
	{
		int found=0;
		for(i=0;i<DATA_SIZE && found==0;i++)
		{
			if(dptr->u.data.arr[i].roll_number==val)
			{
				found=1;
			}
		}
		if(found==0)
		{
			printf("KEY NOT FOUND\n");
		}
		else
		{
			printf("The details of record are: \n");
			//printf("Name: %s\n",dptr->arr[i-1].account_holder_name);
			printf("Account number: %lu\n",dptr->u.data.arr[i-1].roll_number);
			//printf("Address: %s\n",dptr->arr[i-1].address);
			//printf("PAN number: %u\n",dptr->arr[i].PAN_number);
			//printf("Phone number is: %s\n",dptr->arr[i].phone_number);
			printf("************************************************************");
		}
	}

}

void searchFunction(record *root,unsigned int val)
{
	record *result;
	result=searchNode(root,val);
	searchValueInDataNode(result,val);

}


record * insert(record *root, info details, unsigned int no)
{
	unsigned int medno;
	record * right_subtree;
	record * newroot;
	if(root==NULL)
	{
		record *nptr;
		nptr=(record *)malloc(sizeof(record));
		nptr->flag='d';
		nptr->u.data.arr[0]=details;
		nptr->u.data.dataCount=1;
		nptr->u.data.next=NULL;
		nptr->u.data.prev=NULL;
		root=nptr;
	}
	else if(PushDown(no,root,&medno,&right_subtree,details))
	{
		newroot=(record *)malloc(sizeof(record));
		newroot->flag='k';
		newroot->u.key.count=1;
		newroot->u.key.r_no[1]=medno;
		newroot->u.key.ptr[0]=root;
		newroot->u.key.ptr[1]=right_subtree;
		return newroot;

	}
	return root;

}


void insertInDataNode(info details,record *root)
{
	int i=root->u.data.dataCount-1;
	if(root->flag=='d')
	{
		while(root->u.data.arr[i].roll_number>=details.roll_number && i>=0)
		{
			root->u.data.arr[i+1]=root->u.data.arr[i];
			i--;
		}
		root->u.data.arr[i+1]=details;
	}
	root->u.data.dataCount++;
	printf("\nINSERTION SUCCESSFUL\n");
	Num_rec++;
		
}

void insertInKey(unsigned int no,record *root,record *right_subtree,int pos)
{
	int i;
	for(i=root->u.key.count;i>pos;i--)
	{
		root->u.key.r_no[i+1]=root->u.key.r_no[i];
		root->u.key.ptr[i+1]=root->u.key.ptr[i];
	}
	root->u.key.r_no[pos+1]=no;
	root->u.key.ptr[pos+1]=right_subtree;
	root->u.key.count++;
}

void searchPosition(unsigned no,record *root,int *pos)
{
	if(root->flag=='k')
	{
		if(no<root->u.key.r_no[1])
		{
			*pos=0;
		}
		else
		{
			for(*pos=root->u.key.count;no<root->u.key.r_no[*pos];*pos=*pos-1);
		}

	}
}

void splitKey(unsigned int medentry,record *medright,record *root,int pos, unsigned int *newmedian,record **newright)
{
	int i;
	int median;
	if(pos<=MIN)
	{
		median=MIN;
	}
	else
	{
		median=MIN+1;
	}
	*newright=(record *)malloc(sizeof(record));

	for(i=median+1;i<=MAX;i++)
	{
		(*newright)->u.key.r_no[i-median]=root->u.key.r_no[i];
		(*newright)->u.key.ptr[i-median]=root->u.key.ptr[i];
	}
	(*newright)->flag='k';
	(*newright)->u.key.count=MAX-median;
	root->u.key.count=median;
	if(pos<=MIN)
	{
		insertInKey(medentry,root,medright,pos);
	}
	else
	{
		insertInKey(medentry,*newright,medright,pos-median);
	}
	*newmedian=root->u.key.r_no[root->u.key.count];
	(*newright)->u.key.ptr[0]=root->u.key.ptr[root->u.key.count];
	root->u.key.count--;

}


void splitLeaf(info details,record *root,record **right_subtree,unsigned int *no)
{
     info temp_arr[m+1];
     record *leaf_right;
     int i=0,j,k=0;
     while(details.roll_number>root->u.data.arr[i].roll_number && i<root->u.data.dataCount)
     {
        temp_arr[i]=root->u.data.arr[i];
        i++;
     }
     temp_arr[i]=details;
     while(i<=root->u.data.dataCount)
     {
        temp_arr[i+1]=root->u.data.arr[i];
        i++;
     }
     *no=temp_arr[i/2].roll_number;
     root->u.data.dataCount=(int)ceil((double)root->u.data.dataCount/2);
     
     leaf_right=(record *)malloc(sizeof(record));
     leaf_right->flag='d';
     leaf_right->u.data.dataCount=i-root->u.data.dataCount;
     
     for(j=0;j<i/2;j++)
     {
         root->u.data.arr[j]=temp_arr[j];

     }
     for(j=i/2;j<i;j++)
     {
        leaf_right->u.data.arr[k]=temp_arr[j];
        k++;
     }
     
     if(root->u.data.next!=NULL)
     {
     	(root->u.data.next)->u.data.prev=leaf_right;
	 }
     leaf_right->u.data.next=root->u.data.next;
     root->u.data.next=leaf_right;
     leaf_right->u.data.prev=root;
     *right_subtree=leaf_right;
     
     Num_rec++;
     printf("\nINSERTION SUCCESSFUL\n");

}

void update(record * root, info details, unsigned int i)
{
	if(root->u.data.arr[i].roll_number==details.roll_number)
	{
		root->u.data.arr[i]=details;
		printf("\nUPDATION SUCCESSFUL\n");	
	}
	else
	{
		printf("Error in updation\n");
	}
}


int PushDown(unsigned int no, record *root, unsigned int *medno, record **right_subtree,info details)
{
	int pos,i=0;
	int found=0;
	if(root->flag=='d')
	{
		while(root->u.data.arr[i].roll_number<no && i<root->u.data.dataCount)
		{
			i++;
		}
		if(root->u.data.arr[i].roll_number==no)
		{
			update(root,details,i);
		}
		else
		{
			if(root->u.data.dataCount<DATA_SIZE)
			{
				insertInDataNode(details,root);
				return 0;
			}

			else
			{
				splitLeaf(details,root,right_subtree,medno);
				return 1;
			}
		}
	}
	else if(root->flag=='k')
	{
		searchPosition(no,root,&pos);
		if(PushDown(no,root->u.key.ptr[pos], medno,right_subtree,details))
		{
		    no=*medno;
			if(root->u.key.count<MAX)
			{
				insertInKey(no,root,*right_subtree,pos);
				return 0;
			}
			else
			{
				splitKey(no,*right_subtree,root,pos,medno,right_subtree);
				return 1;
			}
		}
		return 0;
	}
}




void MoveLeftKey(record *root,int pos)
{
	int c;
	record *t;
	
	t=root->u.key.ptr[pos-1];
	t->u.key.count++;
	t->u.key.r_no[t->u.key.count]=root->u.key.r_no[pos];
	t->u.key.ptr[t->u.key.count]=(root->u.key.ptr[pos])->u.key.ptr[0];
	
	t=root->u.key.ptr[pos];
	root->u.key.r_no[pos]=t->u.key.r_no[1];
	t->u.key.ptr[0]=t->u.key.ptr[1];
	t->u.key.count--;
	
	for(c=1;c<=t->u.key.count;c++)
	{
		t->u.key.r_no[c]=t->u.key.r_no[c+1];
		t->u.key.ptr[c]=t->u.key.ptr[c+1];
	}
}


void MoveRightKey(record *root,int pos)
{
	int c;
	record *t;
	
	t=root->u.key.ptr[pos];
	for(c=t->u.key.count;c>0;c--)
	{
		t->u.key.r_no[c+1]=t->u.key.r_no[c];
		t->u.key.ptr[c+1]=t->u.key.ptr[c];
	}
	
	t->u.key.ptr[1]=t->u.key.ptr[0];
	t->u.key.count++;
	t->u.key.r_no[1]=root->u.key.r_no[pos];
	
	t=root->u.key.ptr[pos-1];
	root->u.key.r_no[pos]=t->u.key.r_no[t->u.key.count];
	(root->u.key.ptr[pos])->u.key.ptr[0]=t->u.key.ptr[t->u.key.count];
	t->u.key.count--;
}


void CombineKey(record *root,int pos)
{
	int c;
	record * right, * left;
	right=root->u.key.ptr[pos];
	left=root->u.key.ptr[pos-1];
	left->u.key.count++;
	
	left->u.key.r_no[left->u.key.count]=root->u.key.r_no[pos];
	left->u.key.ptr[left->u.key.count]=right->u.key.ptr[0];
	
	for(c=1;c<=right->u.key.count;c++)
	{
		left->u.key.count++;
		left->u.key.r_no[left->u.key.count]=right->u.key.r_no[c];
		left->u.key.ptr[left->u.key.count]=right->u.key.ptr[c];
	}
	
	for(c=pos;c<root->u.key.count;c++)
	{
		root->u.key.r_no[c]=root->u.key.r_no[c+1];
		root->u.key.ptr[c]=root->u.key.ptr[c+1];
	}
	
	root->u.key.count--;
	free(right);		
}



void MoveLeftLeaf(record *root,int pos)
{
	record *lhs;
	record *rhs;
	int c;
	
	lhs=root->u.key.ptr[pos-1];
	rhs=root->u.key.ptr[pos];
	
	lhs->u.data.arr[lhs->u.data.dataCount]=rhs->u.data.arr[0];
	lhs->u.data.dataCount++;
	root->u.key.r_no[pos]=rhs->u.data.arr[1].roll_number;
	for(c=1;c<rhs->u.data.dataCount;c++)
	{
		rhs->u.data.arr[c-1]=rhs->u.data.arr[c];
		
	}
	rhs->u.data.dataCount--;
}

void MoveRightLeaf(record *root,int pos)
{
	record *lhs;
	record *rhs;
	int c;
	lhs=root->u.key.ptr[pos-1];
	rhs=root->u.key.ptr[pos];
	
	for(c=rhs->u.data.dataCount-1;c>=0;c--)
	{
		rhs->u.data.arr[c+1]=rhs->u.data.arr[c];
	}
	
	rhs->u.data.dataCount++;
	rhs->u.data.arr[0]=lhs->u.data.arr[lhs->u.data.dataCount-1];
	root->u.key.r_no[pos]=rhs->u.data.arr[lhs->u.data.dataCount-1].roll_number;
	lhs->u.data.dataCount--;	
}

void CombineLeaf(record *root,int pos)
{
	record *lhs,*rhs;
	int c;
	
	lhs=root->u.key.ptr[pos-1];
	rhs=root->u.key.ptr[pos];
	int elems=lhs->u.data.dataCount;

	for(c=0;c<rhs->u.data.dataCount;c++)
	{
	
		lhs->u.data.arr[elems]=rhs->u.data.arr[c];
		elems++;
	}
	for(c=pos+1;c<=root->u.key.count;c++)
	{
		root->u.key.r_no[c-1]=root->u.key.r_no[c];
		root->u.key.ptr[c-1]=root->u.key.ptr[c];
	}
	lhs->u.data.next=rhs->u.data.next;
	if(rhs->u.data.next!=NULL)
	{
		(rhs->u.data.next)->u.data.prev=lhs;
	}
	lhs->u.data.dataCount=elems;
	root->u.key.count--;
	free(rhs);
	
}

void DeleteFromLeafDirect(unsigned int target,record *root)
{
	int pos,i=0;
	if(root->flag=='d')
	{
		while(root->u.data.arr[i].roll_number<target)
		{
			i++;
		}
		if(root->u.data.arr[i].roll_number>target)
		{
			printf("ENTRY TO BE DELETED IS ABSENT\n");
		}
		else if(root->u.data.arr[i].roll_number==target)
		{
			i++;
			for(i;i<root->u.data.dataCount;i++)
			{
				root->u.data.arr[i-1]=root->u.data.arr[i];
			}
			root->u.data.dataCount--;
			Num_rec--;
			printf("DELETION SUCCESSFUL");
		}
		
	}
}

//Pos is always the right node
int RestoreLeaf(unsigned int target,record *root,int pos)
{
	int k=0;
	int retval=0;
	if(pos==0)
	{
		if((root->u.key.ptr[1])->u.data.dataCount>MIN_DATASIZE)
		{
			MoveLeftLeaf(root,1);
		}
		else
		{
			CombineLeaf(root,1);
			retval=1;
		}
	}
	else if(pos==root->u.key.count)
	{
		if((root->u.key.ptr[pos-1])->u.data.dataCount>MIN_DATASIZE)
		{
			MoveRightLeaf(root,pos);
		}
		else
		{
			CombineLeaf(root,pos);
			retval=1;
		}
	}
	else if((root->u.key.ptr[pos-1])->u.data.dataCount>MIN_DATASIZE)
	{
		MoveRightLeaf(root,pos);
	}
	else if((root->u.key.ptr[pos+1])->u.data.dataCount>MIN_DATASIZE)
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

int RestoreKey(unsigned int target,record *root,int pos)
{
	int k=0;
	int retval=0;
	if(pos==0)
	{
		if((root->u.key.ptr[1])->u.key.count>MIN)
		{
			MoveLeftKey(root,1);
		}
		else
		{
			CombineKey(root,1);
			retval=1;
		}
	}
	else if(pos==root->u.key.count)
	{
		if((root->u.key.ptr[pos-1])->u.key.count>MIN)
		{
			MoveRightKey(root,pos);
		}
		else
		{
			CombineKey(root,pos);
			retval=1;
		}
	}
	else if((root->u.key.ptr[pos-1])->u.key.count>MIN)
	{
		MoveRightKey(root,pos);
	}
	else if((root->u.key.ptr[pos+1])->u.key.count>MIN)
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

int Delete_rec(unsigned int target,record *root)
{
	int pos,k,check_count;
	
	if((root->u.key.ptr[0])->flag=='d')
	{
		searchPosition(target,root,&pos);
		DeleteFromLeafDirect(target,root->u.key.ptr[pos]);
		check_count=(root->u.key.ptr[pos])->u.data.dataCount;
		
		if(check_count>=MIN_DATASIZE)
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
		searchPosition(target,root,&pos);
		if(Delete_rec(target,root->u.key.ptr[pos]))
		{
			check_count=(root->u.key.ptr[pos])->u.key.count;
			if(check_count>=MIN)
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

record * Delete(unsigned int target,record *root)
{
	record *oldroot;
	int k;
	if(root==NULL)
	{
		printf("Tree is empty\n");
	}
	else if(root->flag=='d')
	{
		DeleteFromLeafDirect(target,root);
		if(root->u.data.dataCount==0)
			root=NULL;
	}
	else if (root->flag=='k')
	{
		Delete_rec(target,root);
		if(root->u.key.count==0)
		{
			oldroot=root;
			root=root->u.key.ptr[0];
			free(oldroot);
		}
	}
	
	return root;
}

int GetNumRecords(record * root)
{
	printf("The number of records in the list is %d\n",Num_rec);
	return Num_rec;
}

int GetHeight(record * root)
{
	if(root==NULL)
		return -1;
	else if(root->flag=='d')
		return 0;
	else if(root->flag=='k')
	{
		return 1+GetHeight(root->u.key.ptr[0]);
	}
}


void printInfo(record * root, int i)
{
	printf("----------\n");
	printf("Roll Number : %d\n",root->u.data.arr[i].roll_number);
	printf("Student Name : %s\n",root->u.data.arr[i].student_name);
	printf("Department Name : %s\n",root->u.data.arr[i].department_name);
	printf("Semester Number : %d\n",root->u.data.arr[i].semester_number);
	printf("Address : %s\n",root->u.data.arr[i].address);
	printf("----------\n");	
}

void printTree(record *root)
{
	int i;
	if(root==NULL)
	{
		printf("No records in the tree\n");
	}
	else if(root->flag=='d')
	{
		record *iptr;
		iptr=root;
		while(iptr!=NULL)
		{
			for(i=0;i<iptr->u.data.dataCount;i++)
				printInfo(root,i);
			printf("\n*****node ends*****\n");
			iptr=iptr->u.data.next;
		}
	}
	else
	{
		printTree(root->u.key.ptr[0]);
	}
	
}


void Range_Search(record * root, unsigned int num1, unsigned int num2)
{
	int i=0;
	record * data_ptr;
	if(root==NULL)
	{
		printf("Tree is Empty\n");	
	}
	else 
	{
		data_ptr=searchNode(root,num1);
		if(data_ptr->flag=='d')
		{
			while(data_ptr->u.data.arr[i].roll_number < num1)
			{
				i++;	
			}
			
			while(data_ptr!=NULL)
			{
				while(i<data_ptr->u.data.dataCount && data_ptr->u.data.arr[i].roll_number<=num2)
				{
					printInfo(data_ptr,i);
					i++;	
				}
				data_ptr=data_ptr->u.data.next;
				i=0;	
			}	
		}
	}
}


info MakeInfo(unsigned int roll, char stu_name[], char dept_name[], unsigned int sem_no, char addr[])
{
	info details;
	
	details.roll_number=roll;
	strcpy(details.student_name,stu_name);
	strcpy(details.department_name,dept_name);
	details.semester_number=sem_no;
	strcpy(details.address,addr);
	
	return details;
}

/*record * CreateList()
{
	status sc;
	FILE * fp;
	unsigned int roll,n=0, sem_no;
	char stu_name[50],dept_name[10];
	char addr[50];
	node * root=NULL;
	fp=fopen("data.txt","r");
	
	while(n!=EOF)
	{
		n=fscanf(fp,"%d",&roll);
		if(n!=EOF)
		{
			fscanf(fp,"%s",stu_name);
			fscanf(fp,"%s",dept_name);
			fscanf(fp,"%d",&sem_no);
			fscanf(fp,"%s",addr);
			
			//printf("%d\n%s\n%s\n%d\n",roll,stu_name,sub_code,marks);
			detils=MakeInfo(roll,stu_name,dept_name,sem_no,addr);
			insert(root,details,details.roll_number);
					
		}		
	}
	
	fclose(fp);
	return head;				
}*/


int main()
{
	record * root=NULL;
	info details;
	unsigned int r_no,sem;
	char stu_name[50],dept[10],addr[10];
	int lower_bound, upper_bound, k;
	//root=CreateList();
	int stop=0,choice;
	
	printf("**************** Welcome User! *******************\n");
	while(stop==0)
	{
		printf("------------------------------------------------------------------------------\n");
		printf("Choose your operation:\n");	
		printf("1. Insert into the tree\n");
		printf("2. Delete from the tree\n");
		printf("3. Search in the tree\n");
		printf("4. Get Number of Records\n");
		printf("5. Get height of tree\n");
		printf("6. Make a Range Search\n");
		printf("7. Print Database\n");
		printf("------------------------------------------------------------------------------\n");
		
		scanf("%d",&choice);
		
		switch(choice)
		{
			case 1:
				printf("\nEnter details to insert:");
				printf("\nRoll number: ");
				scanf("%d",&r_no);
				printf("Student Name: ");
				scanf("%s",&stu_name);
				printf("Department Name: ");
				scanf("%s",dept);
				printf("Semester Number: ");
				scanf("%d",&sem);
				printf("Address:");
				scanf("%s",addr);
				details=MakeInfo(r_no,stu_name,dept,sem,addr);
				root=insert(root,details,details.roll_number);
				break;
			
			case 2:
				printf("\nEnter Roll Number of record to be deleted: \n");
				scanf("%d",&r_no);
				root=Delete(r_no,root);
				break;
				
			case 3:
				printf("\nEnter roll number of record of which details are desired: ");
				scanf("%d",&r_no);
				searchFunction(root,r_no);
				break;
				
			case 4:
				k=GetNumRecords(root);	
				break;
				
			case 5:
				k=GetHeight(root);
				printf("\nHeight of tree is %d",k);
				break;
				
			case 6:
				printf("\nEnter Lower Bound of range");
				scanf("%d",lower_bound);
				printf("\nEnter Upper Bound of range");
				scanf("%d",upper_bound);
				printf("\nElements in given range are\n");
				Range_Search(root,lower_bound,upper_bound);
				break;
				
			case 7:
				printTree(root);
				break;
				
			case 8:
				printf("\nSaving the database...");
				printf("\nExited successfully.");
				//WriteBack()
				stop=1;
				break;
				
			default:
				printf("\nInvalid choice of operation");
		}	
	}
		

}
