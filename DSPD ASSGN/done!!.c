#include<stdio.h>
#include<conio.h>
#include<string.h>
#define SIZE 50

struct record{
	int r_no;
	char stu_name[50];
	char sub_code[6];
	unsigned int marks;
};
enum status_code{FAILURE , SUCCESS, UPDATE};

int isBlank(struct record stu_rec);
void print_list(struct record stu_record[],int n);
void initialize(struct record stu_record[],int n);
enum status_code insert(struct record stu_record[],int n);
enum status_code delete(struct record stu_record[],int p);
void isEmpty(struct record stu_record[], int n);
void isFull( struct record stu_record[], int n);
int getNumRecords( struct record stu_record[],int n);
void getMaxMarks(struct record stu_record[],int n);
int list_unique(struct record stu_record[],int p);
void mergeSort(struct record stu_record[],int low,int high,struct record temp[]);
void selfMerge(struct record stu_record[],struct record temp[],int l,int m,int n);
void sort(struct record stu_record[],int n);
void list_intersection(struct record stu_record1[],struct record stu_record2[],int n,int b);
void list_difference(struct record stu_record1[],struct record stu_record2[],int n,int b);
void list_symmetricdifference(struct record stu_record1[],struct record stu_record2[],int n,int b);
void list_union(struct record stu_record1[],struct record stu_record2[],int n,int b);


int main()
{   
    enum status_code s,t,q;
    
	struct record stu_record[SIZE],stu_record2[SIZE];
	int i,choice,flag=1,b,g,n,x;
	
	printf("Initialising the records:\n");
	initialize(stu_record,SIZE);
	
	printf("Enter the size of first list\n");
	scanf("%d",&n);
	
	if(n!=0)
		printf("Enter the data\n");
	
	for(i=0;i<n;i++)
	{   printf("Enter roll no.: ");
	    scanf("%d",&stu_record[i].r_no);
	    printf("Enter student name: ");
	    getchar();
		gets(stu_record[i].stu_name);
		printf("Enter subject code: ");
		scanf("%s",stu_record[i].sub_code);
		printf("Enter marks: ");
		scanf("%d",&stu_record[i].marks);
		if(i!=n-1)
			  printf("\nEnter Next Record\n");	
	}
	printf("select function to be executed:\n\n");
	printf("*****************************************************************************\n");
	printf("1 . to  INSERT a record\n");
	printf("2 . to DELETE a record\n");
	printf("3 . to GET_NUM_RECORDS\n");
	printf("4 . to check if the list of records is EMPTY\n");
	printf("5 . to check if the list of records is FULL\n");
	printf("6 . to GET_MAX_MARKS\n");
	printf("7 . to find number of UNIQUE records\n");
	printf("8 . to get UNION of the lists\n");
	printf("9 . to get INTERSECTION of the lists\n");
	printf("10 . to get DIFFERENCE of the lists\n");
	printf("11 . to get SYMMETRIC_DIFFERENCE of the lists\n");
	printf("12 . to VIEW the contents of the list\n");
	printf("13 . to EXIT the series of operations\n");
	printf("*****************************************************************************\n");
	
	while(flag==1)
	{   
	    printf("\nEnter your operation \n");
		scanf("%d",&choice);
		
		switch(choice){
		
		case 8:
		case 9:
		case 10:
		case 11:
			
				initialize(stu_record2,SIZE);
				printf("Enter the size of second list\n");
				scanf("%d",&b);
	
				printf("Enter data in the records\n");
	
				for(i=0;i<b;i++)
				{
				    printf("Enter roll no.: ");
					scanf("%d",&stu_record2[i].r_no);
					printf("Enter student name: ");
					getchar();
					gets(stu_record2[i].stu_name);
					printf("Enter subject code: ");
					scanf("%s",stu_record2[i].sub_code);
					printf("Enter marks: ");
					scanf("%d",&stu_record2[i].marks);
					
					if(i!=b-1)
						printf("\nEnter Next Record\n");	
				}
				break;
			
		}
		switch(choice){
		
		case 1:
				s=insert(stu_record,SIZE);   //number of records increments if record gets added and not just updated
				if(s==SUCCESS)
					n++;	
		        break;		          
	    case 2:
				q=delete(stu_record,n);     
				if(q==SUCCESS)                //number of records decrements if a record gets deleted
					n--;
	            break;     	
	    case 3:
	            g=getNumRecords(stu_record,n);
	            printf("Number of active records is %d",g);
	            break;     
	    case 4: 
	    		isEmpty(stu_record,SIZE);
		        break;        
	    case 5:
				isFull(stu_record,SIZE);
		        break;           
	    case 6:
		        getMaxMarks(stu_record,n);
			    break;
		case 7:
				x=list_unique(stu_record,n);
				n=x;
			    break;
	    case 8:
				list_union(stu_record,stu_record2,n,b);
		        break;	   
	    case 9:
		        list_intersection(stu_record,stu_record2,n,b);
		        break;
		case 10:
		        list_difference(stu_record,stu_record2,n,b);
		        break;
		case 11:
		        list_symmetricdifference(stu_record,stu_record2,n,b);
				break;
		case 12:
		        print_list(stu_record,n);
				break;
	    case 13:
				flag=0;
				break;
		default:
		        printf("\ninvaid choice of operation\n");
				break;				   
	    }
	}
    
    printf("\n THANK YOU!! \n");
    
	getch();	
	return 0;
}

void initialize(struct record stu_record[],int n)
{
	int i;
	for(i=0;i<n;i++)                //initialising all the records
	{
		stu_record[i].r_no=0;
		stu_record[i].stu_name[0]='\0';
		stu_record[i].sub_code[0]='\0';
		stu_record[i].marks=0;
	}
	printf("The records have been initialised\n");
}


enum status_code insert(struct record stu_record[],int n)
{
	int i=0,found=0,p,free_index,j,l,roll;
	enum status_code status=SUCCESS;
	unsigned int mks;
	char name[50], code[6];
	
	printf("enter record to be inserted in the order roll no, name, subject code,marks\n");
	printf("Enter roll number: ");
	scanf("%d",&roll);
	printf("Enter student name: ");
	getchar();
	gets(name);
	printf("Enter subject code: ");
	scanf("%s",code);
	printf("Enter marks in that subject: ");
	scanf("%d",&mks);
	
	while(i<n&&found==0)
	{
		if(stu_record[i].r_no==roll)                     //checks if roll no. is same
		{
			p=strcmp(stu_record[i].sub_code,code);      //then checks if subject code is same
			if(p==0)
				found=1;	
		}
		else
			i++;
				
    }
	
	
	if(found==1)
	{
		strcpy(stu_record[i].stu_name,name);            //updating the record
		stu_record[i].marks=mks;
		status=UPDATE;
		printf("Insertion Successful!\n");
	}
	else
	{
		free_index=0;
		j=0;
		
		while((j<n)&&(free_index==0))
		{
			if((stu_record[j].r_no==0)&&(stu_record[j].sub_code[0]=='\0'))   //finding a free index
				free_index=1;
			else
				j++;	
		}
		
		if(free_index==1)
		{                                                                     //filling an empty index
			stu_record[j].r_no=roll;
			strcpy(stu_record[j].stu_name,name);
			strcpy(stu_record[j].sub_code,code);
			stu_record[j].marks=mks;
			
			printf("\nInsertion Successful!\n");
			
		}
		else
		{
			status=FAILURE;
			printf("\nArray full\n");	
		}		
	}	
	
	return status;
}


//delete the first occurance of a particular record: 
enum status_code delete(struct record stu_record[],int p)
{
	int i,found,roll;
	i=0;
	found=0;
	char code[6];
	enum status_code status=SUCCESS;
	
	printf("\nenter record to be deleted in the order roll no, subject code\n");
	printf("Enter roll number: ");
	scanf("%d",&roll);
	printf("\nEnter subject code: ");
	scanf("%s",code);
	
	while(i<p && found==0)
	{
		//finding record with matching roll no and subject code
		if(stu_record[i].r_no==roll && strcmp(stu_record[i].sub_code,code)==0) 
		{
				found=1;	
		}
		else
			i++;
					
	}
	
	if(found==1)
	{   //initialising the matching record
		stu_record[i].r_no=0;
		stu_record[i].stu_name[0]='\0';
		stu_record[i].sub_code[0]='\0';
		stu_record[i].marks=0;
		
    //	shifting the created initialised record to the end of array:	
		i++;
		while(i<p)
		{
			stu_record[i-1]=stu_record[i];
			i++;
		}
		
		i=i-1;
		stu_record[i].r_no=0;
		stu_record[i].stu_name[0]='\0';
		stu_record[i].sub_code[0]='\0';
		stu_record[i].marks=0;
		
		printf("\nDeletion Successful!\n");		
	}
	else
	{
		printf("\nNo matching record found. Deletion unsuccessful\n");
		status=FAILURE;	
	}
	
	return status;		
}


void print_list(struct record stu_record[],int n)
{
   int i;
   //printing the list until blank record is encountered	
  for(i=0;i<n && stu_record[i].r_no!=0 && stu_record[i].sub_code[0]!='\0';i++)
	{
		printf("\nRoll no : %d\n",stu_record[i].r_no);
		printf("Student Name : %s\n",stu_record[i].stu_name);
		printf("Subject Code : %s\n",stu_record[i].sub_code);
		printf("Marks : %d\n\n",stu_record[i].marks);		
	}		
}


void isEmpty(struct record stu_record[], int n)
{
	int i,stop=0;
	for(i=0;i<n&&stop==0;i++)
	{
		if(stu_record[i].r_no!=0 || stu_record[i].sub_code[0]!='\0')
		{
			stop=1;
		}
				
	}
	//list is not empty if atleast one record is filled
	if (stop==1)
	{
	  printf("\nThe list is not empty\n");
    }
    else
    {
    	printf("\nThe list is empty\n");
	}
}


void isFull( struct record stu_record[], int n)
{
	int i,stop=0;
	for(i=0;i<n&&stop==0;i++)
	{
		if(stu_record[i].r_no==0 && stu_record[i].sub_code[0]=='\0')
		{
			stop=1;
		}
				
	}
	//the list is not full if atleast one record is totally empty
	if (stop==1)
	{
	  printf("\nThe record is not full\n");
    }
    else
    {
    	printf("\nThe record is full\n");
	}
}

int getNumRecords( struct record stu_record[],int n)
{
	int i,count=0;
	for(i=0;i<n;i++)
	{
		if(stu_record[i].r_no!=0 && stu_record[i].sub_code[0]!='\0')
		{
			count++;
		}
				
	}
	
	return count;
}


void getMaxMarks(struct record stu_record[],int n)
{
	int i,max=0,h=0,p;
	struct record max_record[100];
	char code[6];
	
	printf("\nEnter subject code of which toppers have to be found\n");
	scanf("%s",code);
	
	for(i=0;i<n && (stu_record[i].r_no!=0 && stu_record[i].sub_code[0]!='\0') ;i++)
	{
		if(strcmp(stu_record[i].sub_code,code)==0)
		{
			if(stu_record[i].marks>max)
			{
				max=stu_record[i].marks;
			}
		}
	}
	//storing all records having that 'maximum' marks and printing them:
	printf("\ndetails of students receiving maximum marks are as follows:\n");
	for(i=0;i<n && (stu_record[i].r_no!=0 && stu_record[i].sub_code[0]!='\0') ;i++)
	{
		p=strcmp(stu_record[i].sub_code,code);
		if(p==0 && stu_record[i].marks==max)
		{
			max_record[h]=stu_record[i];
			printf("Roll number : %d\n",stu_record[i].r_no);
			printf("Student Name : %s\n",stu_record[i].stu_name);
			printf("Subject Code : %s\n",stu_record[i].sub_code);
			printf("Marks : %d\n\n",stu_record[i].marks);
			h++;	
		}	
	}	
}


int list_unique(struct record stu_record[],int n)
{
	int i,j,q;
	i=1;
	
	q=strcmp(stu_record[i-1].sub_code,stu_record[i].sub_code);
	sort(stu_record,n);
	
	//in the sorted array, checking with the previous record and moving ahead till you find distinct pair, while keeping 
	//count of number of unique records encountered till that point.
	while((stu_record[i-1].r_no!=stu_record[i].r_no || (stu_record[i-1].r_no==stu_record[i].r_no && q!=0 )) && i<n-1)
		{
			i++;
			q=strcmp(stu_record[i-1].sub_code,stu_record[i].sub_code);
		}
		
	if(stu_record[i-1].r_no!=stu_record[i].r_no)
		{
			i++;
			q=strcmp(stu_record[i-1].sub_code,stu_record[i].sub_code);
		}
		
	j=i-1;
	q=strcmp(stu_record[i-1].sub_code,stu_record[i].sub_code);
	while(i<n-1)
	{
		i=i+1;
		q=strcmp(stu_record[i-1].sub_code,stu_record[i].sub_code);
		if((stu_record[i-1].r_no!=stu_record[i].r_no )|| (stu_record[i-1].r_no==stu_record[i].r_no && q!=0 ))
		{
			j++;
			stu_record[j]=stu_record[i];
		}
	}
	j++;
	printf("\nNumber of unique records is %d\n",j);
	while(j<n && stu_record[j].r_no!=0)
	{
		stu_record[j].r_no=0;
		stu_record[j].stu_name[0]='\0';
		stu_record[j].sub_code[0]='\0';
		stu_record[j].marks=0;	
	}
	return j;
}

void mergeSort(struct record stu_record[],int low,int high,struct record temp[])
{
	int mid;
	if(low<high)
	{
		mid=(low+high)/2;
		mergeSort(stu_record,low,mid,temp);
		mergeSort(stu_record,mid+1,high,temp);
		selfMerge(stu_record,temp,low,mid,high);
		
	}
	
}


void selfMerge(struct record stu_record[],struct record temp[],int l,int m,int n)
{
	int i,j,k,p;
	i=l;
	j=m+1;
	k=l;
	//comparing roll numbers and subject codes of records of the pair:
	while(i<=m && j<=n)
	{
		p=strcmp(stu_record[i].sub_code,stu_record[j].sub_code);
		if((stu_record[i].r_no<stu_record[j].r_no) || (stu_record[i].r_no==stu_record[j].r_no && p<0))
		{
			temp[k]=stu_record[i];
			k++;
			i++;
		}
		else 
		{
			temp[k]=stu_record[j];
			k++;
			j++;
		}
	}
	
	if(i<=m)
	{
		while(i<=m)
			temp[k++]=stu_record[i++];
	}
	else 
	{
		while(j<=n)
			temp[k++]=stu_record[j++];
	}
	
	i=l;
	
	while(i<=n)
	{
		stu_record[i]=temp[i];
		i++;
	}
	
}


void sort(struct record stu_record[],int n)
{
	struct record temp[n];
	//assuming all records are continuously stored without space between them,
	mergeSort(stu_record,0,n-1,temp);
	
}

void list_intersection(struct record stu_record1[],struct record stu_record2[],int n,int b)
{
	int i,j,k,l,p,q;
	struct record stu_record3[n];
	
	i=0;
	j=0;
	k=0;
	//sorting both the lists
	sort(stu_record1,n);
	p=n;
	sort(stu_record2,b);
	q=b;
	
	//keeping pointers i and j for two lists respectively and incrementing them accordingly till we find a similar pair
	while(i<p && j<q )
	{
    	while(i<p&&j<q&&((stu_record1[i].r_no<stu_record2[j].r_no) || (stu_record1[i].r_no==stu_record2[j].r_no && strcmp(stu_record1[i].sub_code,stu_record2[j].sub_code)<0)))
			i++;
			   
		if(i<p&&j<q&&(stu_record1[i].r_no==stu_record2[j].r_no) && (strcmp(stu_record1[i].sub_code,stu_record2[j].sub_code)==0))
		{
			stu_record3[k++]=stu_record1[i++];
			j++;
		}
		
		while(i<p&&j<q&&((stu_record1[i].r_no>stu_record2[j].r_no) || (stu_record1[i].r_no==stu_record2[j].r_no && strcmp(stu_record1[i].sub_code,stu_record2[j].sub_code)>0)))
			j++;
			   
		if(i<p&&j<q&&(stu_record1[i].r_no==stu_record2[j].r_no) && strcmp(stu_record1[i].sub_code,stu_record2[j].sub_code)==0)
		{
			stu_record3[k++]=stu_record2[j++];
			i++;
		}
		
	}
	
	printf("The records common to two lists are:\n");
	for(l=0;l<k;l++)
	{
		printf("Roll no : %d\n",stu_record3[l].r_no);
		printf("Student name : %s\n",stu_record3[l].stu_name);
		printf("Subject Code : %s\n",stu_record3[l].sub_code);
		printf("Marks : %d\n",stu_record3[l].marks);
	}
	
}



void list_difference(struct record stu_record1[],struct record stu_record2[],int n,int b)
{
	int i,j,k,l,p,q;
	struct record stu_record3[n];
	i=0;
	j=0;
	k=0;
	//sorting the lists
	sort(stu_record1,n);
	p=n;
	sort(stu_record2,b);
	q=b;
	
	//following the logic similar to that in intersection
	//just printing records of first list only if they do not occur in second list
	while(i<p && j<q )
	{
		
		
    	while(i<p&&j<q&&((stu_record1[i].r_no<stu_record2[j].r_no) || (stu_record1[i].r_no==stu_record2[j].r_no && strcmp(stu_record1[i].sub_code,stu_record2[j].sub_code)<0)))
	   {
	   		stu_record3[k++]=stu_record1[i++];		  	
	   } 
	   
		if(i<p && j<q && (stu_record1[i].r_no==stu_record2[j].r_no) && strcmp(stu_record1[i].sub_code,stu_record2[j].sub_code)==0)
		{
			i++;
			j++;
		}
		
		while(j<q&&i<p&&((stu_record1[i].r_no>stu_record2[j].r_no) || (stu_record1[i].r_no==stu_record2[j].r_no && strcmp(stu_record1[i].sub_code,stu_record2[j].sub_code)>0)))
			j++;
			   
		if(i<p && j<q &&(stu_record1[i].r_no==stu_record2[j].r_no) && strcmp(stu_record1[i].sub_code,stu_record2[j].sub_code)==0)
		{
			i++;
			j++;
		}
		
	}
	
	while(i<p)
		stu_record3[k++]=stu_record1[i++];
	
	printf("The records in first list other than those in second are:\n");
	for(l=0;l<k;l++)
	{
		printf("Roll no : %d\n",stu_record3[l].r_no);
		printf("Student name : %s\n",stu_record3[l].stu_name);
		printf("Subject Code : %s\n",stu_record3[l].sub_code);
		printf("Marks : %d\n",stu_record3[l].marks);
	}
}


void list_symmetricdifference(struct record stu_record1[],struct record stu_record2[],int n,int b)
{
	int i,j,k,l,p,q;
	struct record stu_record3[2*n];
	i=0;
	j=0;
	k=0;
	//sorting the two lists
	sort(stu_record1,n);
	p=n;
	sort(stu_record2,b);
	q=b;
	//following the logic of intersection operation 
	// printing i^th and j^th records respectively till they are not same
	while(i<p && j<q )
	{
    	while(i<p && j<q && ((stu_record1[i].r_no<stu_record2[j].r_no) || (stu_record1[i].r_no==stu_record2[j].r_no && strcmp(stu_record1[i].sub_code,stu_record2[j].sub_code)<0)))
			stu_record3[k++]=stu_record1[i++];
		
		if(i<p&j<q&&(stu_record1[i].r_no==stu_record2[j].r_no) && strcmp(stu_record1[i].sub_code,stu_record2[j].sub_code)==0)
		{
			i++;
			j++;
		}
		
		while(j<q && i<p &&((stu_record1[i].r_no>stu_record2[j].r_no) || (stu_record1[i].r_no==stu_record2[j].r_no && strcmp(stu_record1[i].sub_code,stu_record2[j].sub_code)>0)))
			stu_record3[k++]=stu_record2[j++];
			   
		if(i<p&j<q&&(stu_record1[i].r_no==stu_record2[j].r_no) && strcmp(stu_record1[i].sub_code,stu_record2[j].sub_code)==0)
		{
			i++;
			j++;
		}
		
	}
	
	while(i<p)
		stu_record3[k++]=stu_record1[i++];
	while(j<q)	
		stu_record3[k++]=stu_record2[j++];
			
	printf("The symmetric difference of lists is:\n");
	for(l=0;l<k;l++)
	{
		printf("Roll no : %d\n",stu_record3[l].r_no);
		printf("Student name : %s\n",stu_record3[l].stu_name);
		printf("Subject Code : %s\n",stu_record3[l].sub_code);
		printf("Marks : %d\n",stu_record3[l].marks);
	}
}

void list_union(struct record stu_record1[],struct record stu_record2[],int n,int b)
{
	int i,j,k,l,p,q;
	struct record stu_record3[2*n];
	i=0;
	j=0;
	k=0;
	//sorting the lists
	sort(stu_record1,n);
	p=n;
	sort(stu_record2,b);
	q=b;
	
	//following logic similar to that in intersection
	// just printing record in all cases and incrementing i and j both when matching records are found
	
	while(i<p && j<q )
	{
    	while(i<p && j<q && ((stu_record1[i].r_no<stu_record2[j].r_no) || (stu_record1[i].r_no==stu_record2[j].r_no && strcmp(stu_record1[i].sub_code,stu_record2[j].sub_code)<0)))
			stu_record3[k++]=stu_record1[i++];	   
			   
		if(i<p&j<q&&(stu_record1[i].r_no==stu_record2[j].r_no) && strcmp(stu_record1[i].sub_code,stu_record2[j].sub_code)==0)
		{
			stu_record3[k++]=stu_record1[i++];
			j++;
		}
		
		while(j<q && i<p &&((stu_record1[i].r_no>stu_record2[j].r_no) || (stu_record1[i].r_no==stu_record2[j].r_no && strcmp(stu_record1[i].sub_code,stu_record2[j].sub_code)>0)))
			stu_record3[k++]=stu_record2[j++];
			   
		if(i<p&j<q&&(stu_record1[i].r_no==stu_record2[j].r_no) && strcmp(stu_record1[i].sub_code,stu_record2[j].sub_code)==0)
		{
			stu_record3[k++]=stu_record1[i++];
			j++;
		}
		
	}
	
	while(i<p)
		stu_record3[k++]=stu_record1[i++];
	while(j<q)	
		stu_record3[k++]=stu_record2[j++];
			
	printf("The union of lists is:\n");
	for(l=0;l<k;l++)
	{
		printf("Roll no : %d\n",stu_record3[l].r_no);
		printf("Student name : %s\n",stu_record3[l].stu_name);
		printf("Subject Code : %s\n",stu_record3[l].sub_code);
		printf("Marks : %d\n",stu_record3[l].marks);
	}
}



