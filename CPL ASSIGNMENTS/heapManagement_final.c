#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define N 10
#define gran 5

typedef struct nodeTagAloc{
	/*This defines the allocated list structure.*/
	char name[5];
	int startIndex;
	int fragSpace;
	int totalSpace;
	struct nodeTagAloc *next;
}nodeAloc;

typedef struct nodeTagFree{
	/*this defines free list structure*/
	int startIndex;
	int freeSpace;//freeSpace is according to blocks of 5
	struct nodeTagFree *next;
}nodeFree;

void printFreelist(nodeFree * headFree){
	nodeFree * ptr=headFree;
	printf("Free list:\n");
	while(ptr!=NULL){
		printf("Starting index: ");
		printf("%d\n",ptr->startIndex);
		printf("Free space is: ");
		printf("%d\n",ptr->freeSpace);
		printf("********************************************************\n");
		ptr=ptr->next;
    }
}

void printAloclist(nodeAloc * headAloc){
	nodeAloc * ptr= headAloc;
	printf("Allocated list:\n");
	while(ptr!=NULL){
		printf("Name: ");
		puts(ptr->name);
		printf("Starting index of block: ");
		printf("%d\n",ptr->startIndex);
		printf("Amount of fragmented space: ");
		printf("%d\n",ptr->fragSpace);
		printf("Total space taken: ");
		printf("%d\n",ptr->totalSpace);
		printf("********************************************************\n");
		ptr=ptr->next;
	}
}

/*It deletes the complete free list.*/
void deleteList(nodeFree *headFree){
	nodeFree *temp;
	nodeFree *ptrFree;
	ptrFree=headFree;
	while(ptrFree!=NULL){
		temp=ptrFree;
		ptrFree=ptrFree->next;
		free(temp);
	}
}
/*Helper function to sort allocated linked list.*/
nodeAloc * Divide(nodeAloc *p){
    nodeAloc *q,*r;
    q=p;
    r=(p->next)->next;
    while(r!=NULL){
        q=q->next;
        r=r->next;
        if(r!=NULL){
            r=r->next;
        }
    }
    r=q;
    q=q->next;
    r->next=NULL;
    return q;
}
/*helper function to sort linked list.*/
nodeAloc * Merge(nodeAloc *p, nodeAloc *q){
    nodeAloc * head, *r;
    if(p==NULL || q==NULL){
        printf("SOMETHING IS WRONG!\n");
    }
    else{
        if(p->startIndex<q->startIndex){
            head=p;
            p=p->next;
        }
        else{
            head=q;
            q=q->next;
        }
       
    }
    r=head;
    while(p!=NULL && q!=NULL){
        if(p->startIndex<q->startIndex){
            r=r->next=p;
            p=p->next;
        }
        else{
            r=r->next=q;
            q=q->next;
        }
    }
    if(p!=NULL){
        r->next=p;
    }
    if(q!=NULL){
        r->next=q;

    }
    return head;
}
/*sorts allocated list*/
nodeAloc * Sort(nodeAloc *p){
    nodeAloc *q, *newhead;
    newhead=p;
    if(p!=NULL && (p->next!=NULL)){
        q=Divide(p);
        p=Sort(p);
        q=Sort(q);
        newhead=Merge(p,q);
    }
    return newhead;
}

/*
Does the compaction of allocated list.
We make a new linked list of allocated list and delete the previously allocated list completely.
*/
nodeAloc *compact(nodeAloc *headAloc,nodeFree **headFree){
	nodeAloc *ptrAloc=headAloc, *ptr, *temp1;
	nodeAloc *temp, *newhead;
	nodeFree *nptr;
	newhead=(nodeAloc *)malloc(sizeof(nodeAloc));
	newhead->next=NULL;
	ptr=newhead;
    int startIndex=1;
	while(ptrAloc!=NULL){
		temp=(nodeAloc *)malloc(sizeof(nodeAloc));
		temp->startIndex=startIndex;
		strcpy(temp->name, ptrAloc->name);
		temp->fragSpace=ptrAloc->fragSpace;
		temp->totalSpace=ptrAloc->totalSpace;
		temp->next=NULL;
		startIndex+=(temp->totalSpace+temp->fragSpace)/5;
		temp1=ptrAloc;
		ptrAloc=ptrAloc->next;
		free(temp1);
		ptr->next=temp;
		ptr=ptr->next;
	}
	temp=newhead; 
	newhead=newhead->next;
	//deleting the dummy node.
	free(temp);  
	/*
	deleting the free list completely and creating new head with single node.
	because after compaction only single node will be left inside free list.
	*/
	deleteList(*headFree);
	nptr=(nodeFree *)malloc(sizeof(nodeFree));
	nptr->startIndex=startIndex;
	nptr->freeSpace=N-startIndex+1;
	nptr->next=NULL;
	*headFree=nptr;
	return newhead;
}



nodeAloc *mallocNew(nodeAloc *headAloc, nodeFree **headFree, int size, char string[]){
	nodeFree *ptrFree,*temp,*nptr;
	nodeAloc *ptrAloc, *ptr;
	ptrFree=*headFree;
	ptrAloc=headAloc;
	int startIndex;
	int flag=1;
	while(ptrFree!=NULL && ptrFree->freeSpace<(int)ceil((double)size/5)){
		ptrFree=ptrFree->next; 
	}
	if(ptrAloc!=NULL){
		while(ptrAloc->next!=NULL){
			ptrAloc=ptrAloc->next;
		}
    }
	if(ptrFree==NULL){
		flag=0;
	}
	else{
		startIndex=ptrFree->startIndex;
	}
	if(flag==0){
		headAloc=compact(headAloc,headFree);
		/*
		We call compact function if free list is empty.
		*/
		nptr=*headFree;
		startIndex=nptr->startIndex;
		ptrFree=*headFree;
		ptrAloc=headAloc;
		if(ptrAloc!=NULL){
			while(ptrAloc->next!=NULL){
				ptrAloc=ptrAloc->next;
			}
	    }
	}
	if((int)ceil((double)size/5)+startIndex<=N+1){

		ptr=(nodeAloc *)malloc(sizeof(nodeAloc));
		ptr->startIndex=startIndex;
		strcpy(ptr->name, string);
		ptr->fragSpace=(5-(size%5))%5; //if size%5==0 the we have to put fragmented space as 0.
		ptr->totalSpace=size;
		ptr->next=NULL;

		if(ptrAloc!=NULL){
			ptrAloc->next=ptr;
		}
		else{
			headAloc=ptr;
		}

		if(ptrFree->freeSpace>((int)ceil((double)size/5))){
			ptrFree->freeSpace=ptrFree->freeSpace-(int)ceil((double)size/5);
			ptrFree->startIndex+=(int)ceil((double)size/5);
		}
		else if(ptrFree->freeSpace==((int)ceil((double)size/5))){
			temp=ptrFree;
			ptrFree=ptrFree->next;
			free(temp);
		}	
	}
	else{
		printf("THE HEAP IS FULL\n");
	}

	headAloc=Sort(headAloc);
	*headFree=ptrFree;

	return headAloc;
}

void mergeFreeList(nodeFree * headFree){
	nodeFree *temp,*prev,*ptr;
	
	if(headFree!=NULL)
	{
		ptr=headFree->next;
		prev=headFree;
		while(ptr!=NULL)
		{
			while(prev!=NULL && ptr!=NULL && prev->startIndex+prev->freeSpace==ptr->startIndex)
			{
				temp=ptr;
				prev->freeSpace+=ptr->freeSpace;
				ptr=ptr->next;
				prev->next=ptr;
				free(temp);
			}
			if(ptr!=NULL)
			{
			
				prev=ptr;
				ptr=ptr->next;
			}
		}
	}
	
}

void freeNew(nodeAloc **headAloc, nodeFree **headFree, char string[]){
	int flag=0;
	nodeAloc *ptrAloc, *prev;
	nodeFree *ptrFree, *prevFree, *temp;
	ptrFree=prevFree=*headFree;
	ptrAloc=*headAloc;
	int startIndex,totalSpace;
	if(ptrAloc!=NULL){
		if(strcmp(ptrAloc->name, string)==0){
			*headAloc=ptrAloc->next;
			startIndex=ptrAloc->startIndex;
			totalSpace=ptrAloc->totalSpace;
			free(ptrAloc);
			flag=1;
		}
		else{
			while(ptrAloc!=NULL && !flag){
				if(strcmp(ptrAloc->name, string)==0){
					flag=1;
				}
				else{
					prev=ptrAloc;
					ptrAloc=ptrAloc->next;
				}
			}
			if(flag==1){
				prev->next=ptrAloc->next;
				startIndex=ptrAloc->startIndex;
				totalSpace=ptrAloc->totalSpace;
				free(ptrAloc);
			}
			else{
				printf("THE GIVEN ADDRESS DOES NOT EXIST!\n");
			}
		}
	}

	if(flag==1){
		temp=(nodeFree *)malloc(sizeof(nodeFree));
		temp->startIndex=startIndex;
		temp->freeSpace=(int)ceil((double)totalSpace/5);
		temp->next=NULL;
		if(ptrFree==NULL){
			*headFree=temp;
		}
		else{
			while(ptrFree!=NULL && ptrFree->startIndex<startIndex){
				prevFree=ptrFree;
				ptrFree=ptrFree->next;
			}
			if(prevFree==ptrFree){
				*headFree=temp;
				temp->next=prevFree;
			}
			else{
				
				temp->next=ptrFree;
				prevFree->next=temp;
			}
			mergeFreeList(*headFree);
		}
	}
}

int main(int argc, char const *argv[]){
	nodeFree *headFree=NULL;
	nodeAloc *headAloc=NULL;
	int flag=1,n,x,s,size;
	char stringname[100];
	headFree=(nodeFree *)malloc(sizeof(nodeFree));
	headFree->startIndex=1;
	headFree->freeSpace=N;
	headFree->next=NULL;
	

    while(flag==1){
    	printf("********************************************************\n");
    	printf("1. Insertion\n");
    	printf("2. Deletion\n");
    	printf("3. Print\n");
    	printf("4. Quit\n");
    	printf("********************************************************\n");
    	printf("Enter your choice\n");
    	scanf("%d",&n);
    	switch(n){
    		case 1:printf("1. insert an integer\n");
    			   printf("2. insert an character\n");
    			   printf("3. insert an float\n");
    			   printf("4. insert an double\n");
    			   printf("5. insert an array of integers\n");
    			   printf("6. insert an array of character\n");
    			   printf("7. insert an array of float\n");
    			   printf("8. insert an array of double\n");
    			   printf("9. insert user defined structure\n");
    		       
    		       printf("Enter your choice\n");
    		       scanf("%d",&x);
    		       switch(x){
    		       	  case 1: printf("Enter the name of the pointer\n");
    		       	  		  scanf("%s",stringname);
    		       	  	      s=sizeof(int);
    		       	  	      break;
    		       	  case 2: printf("enter the name of the pointer\n");
    		       	  		  scanf("%s",stringname);
    		       	  	      s=sizeof(char);
    		       	  	      break;
    		       	  case 3: printf("enter the name of the pointer\n");
    		       	  		  scanf("%s",stringname);
    		       	  	      s=sizeof(float);
    		       	  	      break;
    		       	  case 4: printf("enter the name of the pointer\n");
    		       	  		  scanf("%s",stringname);
    		       	  	      s=sizeof(double);
    		       	  	      break;
    		       	  case 5: printf("enter the name of the pointer\n");
    		       	  		  scanf("%s",stringname);
							  printf("enter size of array: ");
    		       	  		  scanf("%d",&size);
    		       	  		  s=sizeof(int)*size;
    		       	  		  break;
    		       	  case 6: printf("enter the name of the pointer\n");
    		       	  		  scanf("%s",stringname);
						      printf("enter size of array: ");
    		       	  		  scanf("%d",&size);
    		       	  		  s=sizeof(char)*size;
    		       	  		  break;
    		       	  case 7: printf("enter the name of the pointer\n");
    		       	  		 scanf("%s",stringname);
						      printf("enter size of array: ");
    		       	  		  scanf("%d",&size);
    		       	  		  s=sizeof(float)*size;
    		       	  		  break;
    		       	  case 8: printf("enter the name of the pointer\n: ");
    		       	  		 scanf("%s",stringname);
						      printf("enter size of array: ");
    		       	  		  scanf("%d",&size);
    		       	  		  s=sizeof(double)*size;
    		       	  		  break;
    		       	  case 9: printf("enter the name of the pointer\n");
    		       	  		  scanf("%s",stringname);
						      scanf("%d",&s);
						      break;
    		       	  
    		       	  default: printf("Not a valid choice!\n");
    		       	  		   flag=0;
						 	   break; 
    		       	  		  
				   }
				   headAloc=mallocNew(headAloc, &headFree, s, stringname);
				   break;
				   
			case 2: printf("Name of the pointer to be freed:\n ");
					scanf("%s",stringname);
					freeNew(&headAloc,&headFree,stringname);
					break;
					
					
			case 3: printAloclist(headAloc);
			        printFreelist(headFree);
			        break;
			        
			case 4: printf("EXIT");
			        flag=0;
					break;        
			        
			default: printf("Not a valid choice!");
					 flag=0;
					 break;        
		}
	}
    
return 0;
}
