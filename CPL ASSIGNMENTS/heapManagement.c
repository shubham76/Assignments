#include <stdio.h>
#include <string.h>
#define N 1000
#define gran 5

typedef struct nodeTagAloc{
	char name[5];
	int startIndex;
	int endIndex;
	int fragSpace;
	int totalSpace;
	struct nodeTagAloc *next;
}nodeAloc;

typedef struct nodeTagFree{
	int startIndex;
	int freeSpace;
	struct nodeTagFree *next;
}nodeFree;

void deleteList(nodeFree *headFree){
	nodeFree *temp;
	nodeFree *ptrFree;
	while(ptrFree!=NULL){
		temp=ptrFree;
		ptrFree=ptrFree->next;
		free(temp);
	}
}

nodeAloc *compact(nodeAloc *headAloc,nodeFree *headFree)
{
	nodeAloc* ptrAloc=headAloc, *ptr, *temp1;
	nodeAloc* temp, *newhead;
	nodeFree *
	newhead=(*nodeAloc)malloc(sizeof(nodeAloc));
	newhead->next=NULL;
	ptr=newhead;
    int startIndex=1;
	while(ptrAloc!=NULL)
	{
		temp=(*nodeAloc)malloc(sizeof(nodeAloc));
		temp->startIndex=startIndex;
		temp->endIndex=ptrAloc->totalSpace+startIndex-1;
		strcpy(temp->name, ptrAloc->name);
		temp->fragSpace=ptrAloc->fragSpace;
		temp->totalSpace=ptrAloc->totalSpace;
		temp->next=NULL;

		startIndex+=temp->endIndex+1;

		temp1=ptrAloc;
		ptrAloc=ptrAloc->next;
		free(temp1);

		ptr->next=temp;
		ptr=ptr->next;
	}

	temp=newhead;
	newhead=newhead->next;
	free(temp);

	deleteList(headFree);

	headFree=(*nodeFree)malloc(sizeof(nodeFree));
	headFree->startIndex=startIndex;
	headFree->freeSpace=N-startIndex;
	headFree->next=NULL;

	return newhead;
}



nodeAloc *mallocNew(nodeAloc *headAloc, nodeFree *headFree, int size, char string[]){

	nodeFree *ptrFree;
	nodeAloc *ptrAloc, *ptr;

	ptrFree=headFree;

	int startIndex;

	while(ptrFree->next!=NULL){
		ptrFree=ptrFree->next;
	}

	startIdx=ptrFree->startIndex;

	while(ptrAloc->next!=NULL){
		ptrAloc=ptrAloc->next;
	}

	if(size+startIndex>N){
		headAloc=compact(headAloc, headFree);
	}

	if(size+startIndex<N){
		ptr=ptrAloc->next=(*nodeAloc)malloc(sizeof(nodeAloc));

		ptr->startIndex=startIndex;
		ptr->endIndex=startIndex+size-1;
		strcpy(ptr->name, string);
		ptr->fragSpace=5-(size%5);
		ptr->totalSpace=size;
		ptr->next=NULL;
	}
	else{
		printf("The heap is full.\n");
	}

	return headAloc;
}

void mergeFreeList(nodeFree *headFree){
	nodeFree *ptrFree;
	ptrFree=headFree;

	while(ptrFree->next!=NULL){
		temp=ptrFree->next;
		while(ptrFree->startIndex+ptrFree->freeSpace==temp->startIndex){
			ptrFree->next=temp->next;
			ptrFree->freeSpace+=temp->freeSpace;
			temp1=temp;
			temp=temp->next;
			free(temp1);
		}
		ptrFree=ptrFree->next;
	}
}

void freeNew(nodeAloc **headAloc, nodeFree **headFree, char string[]){
	int flag=0;
	nodeAloc *ptrAloc, *prev;
	nodeFree *ptrFree, *prevFree, *temp;

	ptrFree=prevFree=*headFree;
	ptrAloc=*headAloc;

	if(ptrAloc!=NULL){
		if(strcmp(ptrAloc->name, string)==0){
			*headAloc=ptrAloc->next;
			startIndex=ptrAloc->startIndex;
			totalSpace=ptrAloc->totalSpace;
			free(ptrAloc);
		}
		else{
			while(ptrAloc->next!=NULL && !flag){
				if(strcmp(ptrAloc->name, string)==0){
					flag=1;
				}
				else{
					prev=ptrAloc;
					ptrAloc=ptrAloc->next;
				}
			}
			if(flag){
				prev->next=ptrAloc->next;
				startIndex=ptrAloc->startIndex;
				totalSpace=ptrAloc->totalSpace;
				free(ptrAloc);
			}
			else{
				printf("The given address does not exist!\n");
			}
		}
	}

	if(flag){
		temp=(*nodeFree)malloc(sizeof(nodeFree));
		temp->startIndex=startIndex;
		temp->freeSpace=totalSpace;
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

			mergeFreeList(headFree);
		}
	}
}

int main(int argc, char const *argv[])
{
	nodeFree *headFree, *headAloc=NULL;

	headFree=(*nodeFree)malloc(sizeof(nodeFree));
	headFree->startIndex=1;
	headFree->freeSpace=1000
	headFree->next=NULL;


	
	headAloc=mallocNew(headAloc, &headFree, size, str);






	


	return 0;
}
