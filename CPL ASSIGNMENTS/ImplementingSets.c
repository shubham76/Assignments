/*
Basically, what we do is we get the hash value of the required set entry to be inserted. 
Then we put it in the array according to the hash value. If some node is already present in
that place then we create another node and add it to it keeping it in sorted manner.
We need this sorted manner as our Insertion & Union function become very optimised.

Hash value is always in between 0-100. So our insertion or deletion becomes order of (1).
*/

#include <stdio.h>
#include <stdlib.h>
#define N 101 //maximum size of the set array.

//status code for functions.
typedef enum {FAILURE, SUCCESS} statusCode;

//structure of linked list.
typedef struct Node
{
	int value;
	struct Node *next;
}node;

//Structure for set.
typedef struct Set
{
	node *arr[N]; //we take array of pointers of range 0-100.
}Set;

//function to get hash value. returns mod 101 as answer because that is the nearest prime.
int getHashValue(int value){
	return value%(101);
}

/*Insertion function. Grabs hash value and insert it in appropriate postion.*/
statusCode Insert(Set *SetArray, int value){
	node *ptr, *nptr, *prev;
	statusCode status=FAILURE;
	int hashValue = getHashValue(value);

	ptr=SetArray->arr[hashValue];
	prev=ptr;

	if(ptr==NULL){
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
	}
	return status;
}


/*Deletion Function.*/
statusCode Delete(Set *SetArray, int value){
	node *ptr, *temp, *prev;
	int hashValue=getHashValue(value);
	statusCode status=FAILURE;
	ptr=SetArray->arr[hashValue];
	if(ptr==NULL){
		printf("The value is not present.\n");
	}
	else{
		
		prev=ptr;
		int flag=0;
		while(!flag && ptr!=NULL){
			if(ptr->value==value){
				flag=1;
			}
			else{
				if(ptr->value>value){
					break;
				}
				else{
					prev=ptr;
					ptr=ptr->next;
				}

			}
		}

		if(ptr!=NULL && flag){/*To make sure that root is not NULL.*/
			if(ptr->value==prev->value){/*To handle the root case*/
				temp=ptr;
				SetArray->arr[hashValue]=ptr->next;
				free(temp);
				status=SUCCESS;
			}
			else{
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

/*Search becomes highly optimised because of the use of hash table.*/
statusCode Search(Set *SetArray, int value){
	node *ptr;
	int hashValue=getHashValue(value);
	statusCode status=FAILURE;

	ptr=SetArray->arr[hashValue];

	if(ptr==NULL){
		printf("Entry is not available!\n");
		return status;
	}
	else{
		int flag=0;
		while(ptr!=NULL && !flag){
			if(ptr->value==value){
				flag=1;
				status=SUCCESS;
				return status;
			}
		}
		return status;
	}
}

/*
	Algorithm used for is=nsertion is highly optimsed as we do it in order of (n).
	We make use of the fact that we have put entries in sorted manner in the linked list at hashed value index at array.
	Remember that our set is not sorted only entries at indices are sorted.
*/
Set *intersection(Set *S1, Set *S2){
	node *ptr, *nptr, *ptr1, *ptr2, *temp, *dummy;
	int value, flag;
	Set *ans;
	
	ans=(Set*)malloc(sizeof(Set));
	
	
	int i=0;
	while(i<N){
		ptr1=S1->arr[i];
		ptr2=S2->arr[i];
		
		dummy=(node *)malloc(sizeof(node));
		dummy->next=NULL;
		ptr=dummy;
		while(ptr1!=NULL && ptr2!=NULL){
			if(ptr1->value==ptr2->value){
				nptr=(node *)malloc(sizeof(node));
				nptr->value=ptr1->value;
				nptr->next=NULL;

				ptr->next=nptr;
				ptr=nptr;
				
				ptr2=ptr2->next;
				ptr1=ptr1->next;
			}
			else if(ptr1->value>ptr2->value){
				ptr2=ptr2->next;
			}
			else{
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

/*Function for union.*/
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
		
		while(ptr1!=NULL && ptr2!=NULL){
			if(ptr1->value==ptr2->value){
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

/*Prints Set.*/
void printSet(Set *SetArray){
	node *ptr;
	int i=0;
	
	if(SetArray!=NULL){
		printf("The elements of the set are:\n");
		while(i<N){
			ptr=SetArray->arr[i];
			while(ptr!=NULL){
				printf("key:%d value:%d\t", i,ptr->value);
				ptr=ptr->next;
			}
			i++;
		}
	}
	else{
		printf("The set is empty.\n");
	}

}

/*returns new set properly allocating size and making internal pointers NULL.*/
Set *getNewSet(){
	Set *SetArray;
	int n, value, i;
	statusCode status;
	SetArray=(Set *)malloc(sizeof(Set));
	
	for(i=0; i<N; i++){
		SetArray->arr[i]=NULL;
	}
	printf("Enter the number of values in the set: \n");
	scanf("%d", &n);

	for(i=0; i<n; i++){
		scanf("%d", &value);
		status=Insert(SetArray, value);
	}
	
	return SetArray;
}


int main(){
	Set *SetArray, *NewSet, *ans;
	int option=-1, i, value, n;
	statusCode status;
	
	SetArray=(Set*)malloc(sizeof(Set));
	NewSet=(Set*)malloc(sizeof(Set));
	ans=(Set*)malloc(sizeof(Set));
	for(i=0; i<N; i++){
		SetArray->arr[i]=NULL;
		NewSet->arr[i]=NULL;
		ans->arr[i]=NULL;
	}
	
	while(option!=6){
		printf("\nSelect your operation from the following:\n\n\
0.To view contents of the Set.\n\
1.Insert values in the Set.\n\
2.Delete a value in the Set.\n\
3.Search a value in Set.\n\
4.Intersection of two sets.\n\
5.Union of two sets.\n\
6..To stop the process.\n");

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
			default:
				printf("Invalid option.\n");
				break;
		}	
	}



}
