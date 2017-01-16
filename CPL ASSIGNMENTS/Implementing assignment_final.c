#include <stdio.h>
#include <stdlib.h>
#define N 101

typedef enum {FAILURE, SUCCESS} statusCode;

typedef struct Node
{
	int value;
	struct Node *next;
}node;

typedef struct Set
{
	node *arr[N];
}Set;

int getHashValue(int value){

	return value%(N);
}


statusCode Insert(Set *SetArray, int value){
	node *ptr, *nptr, *prev;
	statusCode status=FAILURE;
	int hashValue = getHashValue(value);
//	printf("hs: %d\n",hashValue);

	ptr=SetArray->arr[hashValue];
	prev=ptr;

	if(ptr==NULL){
		//printf("ptr is null\n");
		SetArray->arr[hashValue]=(node *)malloc(sizeof(node));
		SetArray->arr[hashValue]->value=value;
		SetArray->arr[hashValue]->next=NULL;
		status=SUCCESS;
	}
	else
	{
		int flag=0;
		prev=ptr;

		while(ptr!=NULL && ptr->value<value)
		{
			prev=ptr;
			ptr=ptr->next;	
		}
		
		if(ptr!=NULL && ptr->value==value)
		{
			printf("The entry is already present.\n");
			return status;
		}
		
		//if(ptr->value=value)
		//{
		if(ptr==prev)
		{
			nptr=(node *)malloc(sizeof(node));
			nptr->value=value;
			nptr->next=ptr;
			status=SUCCESS;
			SetArray->arr[hashValue]=nptr;
		}
		else
		{
			nptr=(node *)malloc(sizeof(node));
			nptr->value=value;
			nptr->next=prev->next;
			prev->next=nptr;
			status=SUCCESS;
		}
		//}
		//else{
		//	printf("The Entry is already present.\n");
		//}
	}
	return status;
}

statusCode Delete(Set *SetArray, int value)
{
	node *ptr, *temp, *prev;
	int hashValue=getHashValue(value);
	statusCode status=FAILURE;
	ptr=SetArray->arr[hashValue];
	
	if(ptr==NULL)
	{
		printf("The value is not present.\n");
	}
	else
	{
		
		prev=ptr;
		int flag=0;
		while(!flag && ptr!=NULL)
		{
			if(ptr->value==value)
			{
				flag=1;
			}
			else
			{
				if(ptr->value>value)
				{
					break;
				}
				else
				{
					prev=ptr;
					ptr=ptr->next;
				}

			}
		}

		if(ptr!=NULL && flag)
		{									/*To make sure that root is not NULL.*/
			if(ptr->value==prev->value)
			{								/*To handle the root case*/
				temp=ptr;
				SetArray->arr[hashValue]=ptr->next;
				free(temp);
				status=SUCCESS;
			}
			else
			{
				prev->next=ptr->next;
				temp=ptr;
				free(temp);
				status=SUCCESS;
			}
		}
		else{
			printf("The entry is not present.\n");
		}
	}
	return status;
}

statusCode Search(Set *SetArray, int value)
{
	node *ptr;
	int hashValue=getHashValue(value);
	statusCode status=FAILURE;

	ptr=SetArray->arr[hashValue];

	if(ptr==NULL)
	{
		printf("Entry is not available!\n");
		return status;
	}
	else
	{
		int flag=0;
		while(ptr!=NULL && !flag)
		{
			if(ptr->value==value)
			{
				flag=1;
				status=SUCCESS;
				return status;
			}
			ptr=ptr->next;
		}
		return status;
	}
}

Set *intersection(Set *S1, Set *S2){
	node *ptr, *nptr, *ptr1, *ptr2, *temp, *dummy;
	int value, flag;
	Set *ans;
	ans=(Set *)malloc(sizeof(Set));
	
	int i=0;
	while(i<N){
		ptr1=S1->arr[i];
		ptr2=S2->arr[i];
		
		dummy=(node *)malloc(sizeof(node));
		dummy->next=NULL;
		ptr=dummy;
		while(ptr1!=NULL && ptr2!=NULL)
		{
			if(ptr1->value==ptr2->value)
			{
				nptr=(node *)malloc(sizeof(node));
				nptr->value=ptr1->value;
				nptr->next=NULL;

				ptr->next=nptr;
				ptr=nptr;
				
				ptr2=ptr2->next;
				ptr1=ptr1->next;
			}
			else if(ptr1->value>ptr2->value)
			{
				ptr2=ptr2->next;
			}
			else
			{
				ptr1=ptr1->next;
			}
		}
		temp=dummy;
		ans->arr[i]=dummy->next;
		free(temp);
		
		i++;
	}
	return ans;
}

Set *Union(Set *S1, Set *S2){
	node *ptr, *nptr, *ptr1, *ptr2, *temp, *dummy;
	int value, flag, i;

	Set *ans;
	ans=(Set*)malloc(sizeof(Set));
	
	i=0;

	while(i<N){
		ptr1=S1->arr[i];
		ptr2=S2->arr[i];
		
		dummy=(node *)malloc(sizeof(node));
		dummy->next=NULL;

		ptr=dummy;
		
		while(ptr1!=NULL && ptr2!=NULL)
		{
			if(ptr1->value==ptr2->value)
			{
				nptr=(node *)malloc(sizeof(node));
				nptr->value=ptr1->value;
				nptr->next=NULL;
				
				ptr1=ptr1->next;
				ptr2=ptr2->next;
			}
			else if(ptr1->value<ptr2->value){
				nptr=(node *)malloc(sizeof(node));
				nptr->value=ptr1->value;
				nptr->next=NULL;
				
				ptr1=ptr1->next;
			}
			else{
				nptr=(node *)malloc(sizeof(node));
				nptr->value=ptr2->value;
				nptr->next=NULL;

				ptr2=ptr2->next;
			}
			ptr->next=nptr;
			ptr=nptr;
		}

		for(;ptr1!=NULL;ptr1=ptr1->next){
			nptr=(node *)malloc(sizeof(node));
			nptr->value=ptr1->value;
			nptr->next=NULL;

			ptr->next=nptr;
			ptr=nptr;
		}

		for(;ptr2!=NULL;ptr2=ptr2->next){
			nptr=(node *)malloc(sizeof(node));
			nptr->value=ptr2->value;
			nptr->next=NULL;

			ptr->next=nptr;
			ptr=nptr;
		}

		temp=dummy;
		ans->arr[i]=dummy->next;
		free(temp);

		i++;
	}
	return ans;
}

void printSet(Set *SetArray){
	node *ptr;
	int i=0,flag=0;
	
	if(SetArray!=NULL){
		printf("The elements of required set are:\n");
		while(i<N)
		{
			ptr=SetArray->arr[i];
			while(ptr!=NULL)
			{
				printf("%d\t", ptr->value);
				ptr=ptr->next;
				flag=1;
			}
			i++;
		}
		if(flag==0)
			printf("The set is empty.\n");
	}
	else{
		printf("The set is empty.\n");
	}

}

Set *getNewSet()
{
	Set *SetArray;
	int n, value, i;
	statusCode status;
	SetArray=(Set *)malloc(sizeof(Set));
	
	for(i=0; i<N; i++){
		SetArray->arr[i]=NULL;
	}
	printf("Enter the number of values in new the set: \n");
	scanf("%d", &n);
	printf("Enter the values\n");
	
	for(i=0; i<n; i++){
		scanf("%d", &value);
		status=Insert(SetArray, value);
	}
	
	return SetArray;
}
int main(){
	Set *SetArray, *NewSet, *ans;
	int option=-1, i, value, n,stop=0;
	statusCode status;
	
	SetArray=(Set*)malloc(sizeof(Set));
	NewSet=(Set*)malloc(sizeof(Set));
	ans=(Set*)malloc(sizeof(Set));
	for(i=0; i<N; i++){
		SetArray->arr[i]=NULL;
		NewSet->arr[i]=NULL;
		ans->arr[i]=NULL;
	}
	
	while(!stop){
		printf("\n------------------------------------------------------------------------------\n");
		printf("Select your operation from the following:\n\n\
0.To view contents of the Set.\n\
1.Insert values in the Set.\n\
2.Delete a value in the Set.\n\
3.Search a value in Set.\n\
4.Intersection of two sets.\n\
5.Union of two sets.\n\
6..To stop the process.\n");
		printf("------------------------------------------------------------------------------\n");

		scanf("%d", &option);

		switch(option){
			case 0:{
				printSet(SetArray);
				break;
			}
			case 1:{
				printf("How many values do you want to insert?\n");
				scanf("%d", &n);
				printf("Enter the values:\n");
				for (i = 0; i < n; ++i){
					scanf("%d", &value);
					status=Insert(SetArray, value);
				}
				printf("Values inserted successfully!\n");
				break;
			}
			case 2:{
				printf("Enter the value to be deleted: \n");
				scanf("%d", &value);

				status=Delete(SetArray, value);

				if(status){
					printf("The value deleted successfully.\n");
				}

				break;
			}
			case 3:{
				printf("Enter the value to be searched:\n");
				scanf("%d", &value);

				status=Search(SetArray, value);

				if(status){
					printf("The value is present.\n");
				}
				break;
			}
			case 4:{
				NewSet=getNewSet();
				ans=intersection(SetArray, NewSet);
				printSet(ans);
				break;
			}
			case 5:{
				NewSet=getNewSet();
				ans=Union(SetArray, NewSet);
				printSet(ans);
				break;
			}
			case 6:{
				stop=1;
				break;
			}	
			default:
				printf("Invalid option.\n");
				break;
		}	
	}



}
