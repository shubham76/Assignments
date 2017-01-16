#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>

typedef enum {FAILURE, SUCCESS, UPDATE} statusCode;

int count=0;		//global variable to maintain the number of nodes in the list

typedef struct employeeTag{
	char employeeName[40];
	char projectName[25];
	unsigned int numberOfHours;
	char employeeAddress[100];
	unsigned int phoneNumber;
	unsigned int employeeSalary;
	struct employeeTag *next;
}node;

//This function makes a node and sets its 'next' to NULL and returns the pointer pointing to the node
node * makeNode(char employeeName[], char projectName[], unsigned int numberOfHours, char employeeAddress[], unsigned int phoneNumber, unsigned int employeeSalary){
	node * ptr;
	ptr=(node *)(malloc(sizeof(node)));
	if(ptr!=NULL){
		strcpy(ptr->employeeName, employeeName);
		strcpy(ptr->projectName, projectName);
		ptr->numberOfHours=numberOfHours;
		strcpy(ptr->employeeAddress, employeeAddress);
		ptr->phoneNumber=phoneNumber;
		ptr->employeeSalary=employeeSalary;
	}
	ptr->next=NULL;
	return ptr;
}

/*This function compares the the lists whose head pointers are passed as parameters and returns 1 if first list is smaller, -1 if second list is smaller and 
0 if both the lists are same when their keys are compared*/  
int compareNode(node * ptr1, node * ptr2){ 
	int flag, cmp1, cmp2;
	/*Return flag=1 if ptr1 is lesser than ptr2 else return flag=-1 & flag=0 if both keys are same*/
	cmp1=strcmp(ptr1->employeeName, ptr2->employeeName);
	cmp2=strcmp(ptr1->projectName, ptr2->projectName);

	if(cmp1<0)
		flag=1;
	else if(cmp1>0)
		flag=-1;
	else if(cmp1==0 && cmp2<0)
		flag=1;
	else if(cmp1==0 && cmp2>0)
		flag=-1;
	else if(cmp1==0 && cmp2==0)
		flag=0;

	return flag;
}

statusCode insertNodeFromFile(node **head, node * nptr){
	statusCode status=SUCCESS;
	node *ptr;
	ptr=*head;
	int flag=compareNode(ptr, nptr), cmp;
	if(*head==NULL){		//checking for 0 nodes
		*head=nptr;		//set head if it is NULL
	}
	else if(ptr->next==NULL){		//checking for one nodes
		if(flag>0){					//ptr is smaller than nptr(node to be inserted)
			ptr->next=nptr;		
			nptr->next=NULL;
		}
		else if(flag<0){			//nptr(node to be inserted is smaller than ptr
			nptr->next=ptr;
			*head=nptr;	
		}
		else{
			ptr->next=nptr;
			nptr->next=NULL;
		}	
	}
	else{			//if number of nodes are more than one
		int flag1=0;
		
		while(!flag1 && ptr!=NULL){
			cmp=compareNode(ptr, nptr);
			if(cmp==0)
				flag1=1;
			else
				ptr=ptr->next;
		}

		if(flag1){
			nptr->next=ptr->next;
			ptr->next=nptr;
		}
		else{			//adding new node
			ptr=*head;
			node *prev;
			prev=ptr;
			flag=0;
			
			while(!flag && ptr!=NULL){
				cmp=compareNode(ptr, nptr);
				if(cmp<0){
					flag=1;
				}
				else{
					prev=ptr;
					ptr=ptr->next;
				}
			}

			if(ptr==prev){		//if prev and ptr are same it means they will be pointing to the same node,so we have to update the head pointer 
				nptr->next=ptr;
				*head=nptr;
			}
			else{
				prev->next=nptr;
				nptr->next=ptr;
			}
		}
	}

	if(status==1) 				//increments count if new node is added.
			count++;

	return status;
}



//This function inserts the node at the correct position and returns the head pointer
statusCode insertNode(node **head, node * nptr){
	statusCode status=SUCCESS;
	node *ptr;
	ptr=*head;
	int flag=compareNode(ptr, nptr), cmp;
	if(*head==NULL){		//checking for 0 nodes
		*head=nptr;		//set head if it is NULL
	}
	else if(ptr->next==NULL){		//checking for one nodes
		if(flag>0){					//ptr is smaller than nptr(node to be inserted)
			ptr->next=nptr;		
			nptr->next=NULL;
		}
		else if(flag<0){			//nptr(node to be inserted is smaller than ptr
			nptr->next=ptr;
			*head=nptr;	
		}
		else{						//update
			ptr->numberOfHours=nptr->numberOfHours;
			strcpy(ptr->employeeAddress,nptr->employeeAddress);
			ptr->phoneNumber=nptr->phoneNumber;
			ptr->employeeSalary=nptr->employeeSalary;

			status=UPDATE;
		}	
	}
	else{			//if number of nodes are more than one
		int flag1=0;
		//checking for updates.
		while(!flag1 && ptr!=NULL){
			cmp=compareNode(ptr, nptr);
			if(cmp==0)
				flag1=1;
			else
				ptr=ptr->next;
		}
		//updating node if flag1=1.
		if(flag1){
			ptr->numberOfHours=nptr->numberOfHours;
			strcpy(ptr->employeeAddress,nptr->employeeAddress);
			ptr->phoneNumber=nptr->phoneNumber;
			ptr->employeeSalary=nptr->employeeSalary;

			free(nptr);

			status=UPDATE;
		}
		else{			//adding new node
			ptr=*head;
			node *prev;
			prev=ptr;
			flag=0;
			
			while(!flag && ptr!=NULL){
				cmp=compareNode(ptr, nptr);
				if(cmp<0){
					flag=1;
				}
				else{
					prev=ptr;
					ptr=ptr->next;
				}
			}

			if(ptr==prev){		//if prev and ptr are same it means they will be pointing to the same node,so we have to update the head pointer 
				nptr->next=ptr;
				*head=nptr;
			}
			else{
				prev->next=nptr;
				nptr->next=ptr;
			}
		}
	}

	if(status==1) 				//increments count if new node is added.
			count++;

	return status;
}

//This function returns SUCCESS if the node with that particular node is found(deletes this node),else returns FAILURE
statusCode deleteNode(node **head, char employeeName[], char projectName[]){
	statusCode status=SUCCESS;
	int cmp1, cmp2;
	node* ptr, *prev;
	if(*head==NULL)
		status=FAILURE;
	else{
		int flag=0;
		ptr=*head;
		while(!flag && ptr!=NULL){			//flag will be set if the node with that particular employee name and project name is found
			cmp1=strcmp(ptr->employeeName, employeeName);
			cmp2=strcmp(ptr->projectName, projectName);
			if(cmp1==0 && cmp2==0)
				flag=1;
			else{
				prev=ptr;
				ptr=ptr->next;
			}
		}

		if(flag){
			if(ptr==prev){			//if prev and ptr are same it means they will be pointing to the same node,so we have to update the head pointer 
				*head=ptr->next;
			}
			else{
				prev->next=ptr->next;
			}
			free(ptr);
		}
		else{
			status=FAILURE;
		}
	}

	if(status==1)			//decrements count if node is deleted successfully!
		count--;

	return status;
}

// This function returns the number of nodes in the list 
int getNumRecords(){		
	return count;
}

//This function returns SUCCESS if list is empty else FAILURE
statusCode isEmpty(){
	if(count==0)
		return SUCCESS;  //If list is empty
	else
		return FAILURE; //If list is not empty
}

//This function removes the duplicates in the list
void listUnique(node * head){ 		//we need not return head pointer
	node *ptr, *prev, *temp;
	int cmp;

	//list will be sorted
	ptr=head;
	if(head!=NULL){			//we can skip the first node and check from the second node onwards
		prev=ptr;
		ptr=ptr->next;

		while(ptr!=NULL){
			cmp=compareNode(ptr, prev);		//we'll check ptr and prev and if they are same then we'll free ptr
			if(cmp==0){
				temp=ptr;
				prev->next=ptr->next;
				ptr=ptr->next;
				free(temp);
				count--;		//decrement counter if a duplicate is found(as we are freeing that node
			}
			else{
				prev=ptr;
				ptr=ptr->next;
			}
		}	
	}
}

//This function looks through and prints the employee names with the maximum number of hours for a given project name
void getMaxNumHrs(node * head, char projectName[]){
	int maxHrs=0;
	node *ptr=head, *maxPtr;

	if(head!=NULL){
		while(ptr!=NULL){
			if(!strcmp(projectName, ptr->projectName)){
				if(ptr->numberOfHours>maxHrs){
					maxHrs=ptr->numberOfHours;
					maxPtr=ptr;  		//maxPtr points to the first occurence of the maximum number of hours
				}
			}
			ptr=ptr->next;
		}
	}

	//to print the list of employee's

	printf("maximum number of hours for given project are %d\n", maxHrs);
	ptr=maxPtr;
	printf("The employee names for the maximum number of hours are: \n");
	while(ptr!=NULL){
		if(!strcmp(projectName, ptr->projectName)){
			if(ptr->numberOfHours==maxHrs){
				puts(ptr->employeeName);
			}
		}
		ptr=ptr->next;
	}
}

//This function returns the head pointer of the union of list1 and list2 
node * listUnion(node * head1, node * head2){
	int cmp;
	node *head, *ptr1, *ptr2, *ptr, *temp;
	ptr1=head1->next;
	ptr2=head2->next;

	head=makeNode("0","0", 0, "0", 0, 0); //temporary node.
	ptr=head;
	
	while(ptr1!=NULL && ptr2!=NULL){
		
		cmp=compareNode(ptr1, ptr2);
		if(!cmp){   //if the nodes in both the lists are same,then we copy the data in node of list1
			ptr->next=makeNode(ptr1->employeeName, ptr1->projectName, ptr1->numberOfHours, ptr1->employeeAddress, ptr1->phoneNumber, ptr1->employeeSalary);
			ptr=ptr->next;
			ptr1=ptr1->next;
			ptr2=ptr2->next;
		}
		else{
			if(cmp>0){		//if node in list1 is smaller,we copy the data in that node 
				ptr->next=makeNode(ptr1->employeeName, ptr1->projectName, ptr1->numberOfHours, ptr1->employeeAddress, ptr1->phoneNumber, ptr1->employeeSalary);
				ptr=ptr->next;
				ptr1=ptr1->next;
			}
			else if(cmp<0){		//if node in list2 is smaller,we copy the data in that node
				ptr->next=makeNode(ptr2->employeeName, ptr2->projectName, ptr2->numberOfHours, ptr2->employeeAddress, ptr2->phoneNumber, ptr2->employeeSalary);
				ptr=ptr->next;
				ptr2=ptr2->next;
			}
		}
	}

	while(ptr1!=NULL){		//if ptr2 has become NULL then we have to copy the nodes of ptr1
		ptr->next=makeNode(ptr1->employeeName, ptr1->projectName, ptr1->numberOfHours, ptr1->employeeAddress, ptr1->phoneNumber, ptr1->employeeSalary);
		ptr=ptr->next;
		ptr1=ptr1->next;
	}
	
	while(ptr2!=NULL){		//if ptr1 has become NULL then we have to copy the nodes of ptr2
		ptr->next=makeNode(ptr2->employeeName, ptr2->projectName, ptr2->numberOfHours, ptr2->employeeAddress, ptr2->phoneNumber, ptr2->employeeSalary);
		ptr=ptr->next;
		ptr2=ptr2->next;
	}

	temp=head; 			//deleting the temporary node
	head=head->next;
	free(temp);

	return head;
}

//This function returns the head pointer of the intersection of the two lists
node * listIntersection(node* head1, node* head2){
	int cmp, flag;
	node *head, *ptr, *ptr1, *ptr2, *temp;
	head=makeNode("0","0", 0, "0", 0, 0); //temporary node.

	//the lists are in sorted form, on the key

	ptr=head;
	ptr1=head1->next;
	ptr2=head2->next;

	for(;ptr1!=NULL;ptr1=ptr1->next){ 
		ptr2=head2;
		flag=0;
		for(;ptr2!=NULL &&!flag ;ptr2=ptr2->next){
			cmp=compareNode(ptr1, ptr2);
			if(!cmp){		//if both those nodes are same
				ptr->next=makeNode(ptr1->employeeName, ptr1->projectName, ptr1->numberOfHours, ptr1->employeeAddress, ptr1->phoneNumber, ptr1->employeeSalary);
				ptr=ptr->next;
				flag=1;				//to break the loop once found.
			}
		}
	}

	temp=head;
	head=head->next;
	free(temp);

	return head;
}

//This function returns the head pointer of list difference of list1 and list2
node * listDifference(node* head1, node* head2){
	int cmp, flag;
	node *head, *ptr, *ptr1, *ptr2, *temp;
	head=makeNode("0","0", 0, "0", 0, 0); //temporary node.

	//the lists are in sorted form, on the key

	ptr=head;
	ptr1=head1->next;
	ptr2=head2->next;

	for(;ptr1!=NULL;ptr1=ptr1->next){ 
		ptr2=head2;
		flag=0;
		for(;ptr2!=NULL &&!flag ;ptr2=ptr2->next){
			cmp=compareNode(ptr1, ptr2);
			if(!cmp){			//if both those nodes are same!
				flag=1;			//to break the loop once found.
			}
		}
		if (flag==0)		//if the data of that particular employee in list1 is not found 
		{
			ptr->next=makeNode(ptr1->employeeName, ptr1->projectName, ptr1->numberOfHours, ptr1->employeeAddress, ptr1->phoneNumber, ptr1->employeeSalary);
			ptr=ptr->next;
		}
	}

	temp=head;
	head=head->next;
	free(temp);

	return head;
}

//This function returns the head pointer of the symmetric difference of list1 and list2
node * symmetricDifference(node *head1, node* head2){
	node *head3, *head4, *head5;
	head3=makeNode("0","0",0,"0",0,0);
	head4=makeNode("0","0",0,"0",0,0);
	head3->next=listDifference(head1, head2);
	head4->next=listDifference(head2, head1);
	head5=listUnion(head3, head4);

	return head5; 
}

//This function writes into the file being pointed to by the file pointer passed as parameter
void FileWrite(node* head1,FILE *fp){
	
	node* ptr;
	ptr=head1->next;
	
	
	while(ptr!=NULL){
		fprintf(fp,"%s\n", ptr->employeeName);
		fprintf(fp, "%s\n", ptr->projectName);
		fprintf(fp,"%u\n",ptr->numberOfHours);
		fprintf(fp,"%s\n", ptr->employeeAddress);
		fprintf(fp,"%u\n",ptr->phoneNumber);
		fprintf(fp, "%u\n",ptr->employeeSalary);
		fprintf(fp,"\n");
		ptr=ptr->next;	
	}
}

//This function reads from the file being pointed to by the file pointer passed as parameter
node * FileInput(node *head1,FILE *fp){
	node *nptr;
	statusCode status;
	
	char employeeName[40], projectName[20], employeeAddress[100];
	unsigned int numberOfHours, employeeSalary; 
	unsigned int phoneNumber,c=0; 
	
	while(c=getc(fp)!=EOF){			//if it is not EOF, continue reading from the file   

			fscanf(fp, "%s", employeeName);
			
			fscanf(fp, "%s", projectName);	
			
			fscanf(fp,"%u",&numberOfHours);
			
			fscanf(fp, "%s", employeeAddress);
			
			fscanf(fp, "%u", &phoneNumber);
			
			fscanf(fp, "%u", &employeeSalary);
			
			nptr=makeNode(employeeName, projectName, numberOfHours, employeeAddress, phoneNumber, employeeSalary);
			status=insertNodeFromFile(&head1, nptr);  //insertNode function inserts the node at the correct position ,so the list will be sorted
		
	}
	
	return head1;
}

statusCode checkValidity(char employeeName[], char projectName[], unsigned int numberOfHours, char employeeAddress[], unsigned int phoneNumber, unsigned int employeeSalary){
	statusCode sc=SUCCESS;
	int flag, i;
	
	flag=0;
	for(i=0; employeeName[i]!='\0' && !flag; i++){
		if(employeeName[i]>=48 && employeeName[i]<=57){
			sc=FAILURE;
			flag=1;
			printf("\nSorry. Employee Name not valid.\n");
		}
	}
	
	flag=0;
	for(i=0; projectName[i]!='\0' && !flag; i++){
		if(projectName[i]>=48 && projectName[i]<=57){
			sc=FAILURE;
			flag=1;
			printf("\nSorry. Project Name not valid.\n");
		}
	}
	
	return sc;
	
}

//This function will print the list 
void printList(node *head){
	node *ptr=head->next;
	
	printf("\n****************************************************************************\n");
	
	while(ptr!=NULL){
		printf("\nEmployee Name    : %s\n", ptr->employeeName);
		printf("Project Name     : %s\n", ptr->projectName);
		printf("Number of hours  : %u\n", ptr->numberOfHours);
		printf("Employee Address : %s\n", ptr->employeeAddress);
		printf("Phone Number     : %llu\n", ptr->phoneNumber);
		printf("Employee Salary  : %u\n", ptr->employeeSalary);

		ptr=ptr->next;
	}
	
	printf("\n****************************************************************************\n");

}

int main(int argc, char const *argv[])
{
	node* head1=NULL, *head2=NULL, *head3=NULL, *nptr=NULL;
	int i, n1, n2, n3, opertn, max_hours, flag;
	char employeeName[40], projectName[20], employeeAddress[100];
	unsigned int numberOfHours, employeeSalary; 
	unsigned int phoneNumber; 
	statusCode status;
	FILE *ip1,*ip2,*op1,*op3;
	
	head1=makeNode("0", "0", 0, "0", 0, 0);
	head2=makeNode("0", "0", 0, "0", 0, 0);
	head3=makeNode("0", "0", 0, "0", 0, 0);
	ip1=fopen("head1_input.txt", "r");
	head1=FileInput(head1,ip1);
	fclose(ip1);
	printList(head1);
	
	

	printf("\nSelect your operation from the following:\n\n\
0.To view contents of the first record.\n\
1.Insert a record.\n\
2.Delete a record.\n\
3.To get number of active records.\n\
4.To check if a record is empty or not.\n\
5.To get maximum number of hours spent on a particular project.\n\
6.To remove duplicates from a list.\n\
7.To get the union of two lists.\n\
8.To get the intersection of the two lists.\n\
9.To get the difference between two lists.\n\
10.To get the symmentric difference between the two lists.\n\
11.To stop the process.\n");
	
	scanf("%d", &opertn);
	getchar();

	while(opertn!=11)
	{
		/*if the operation requires third list then we ask the user for
		the list first and then perform the operation.*/

		switch(opertn)
		{
			case 7:
			case 8:
			case 9:
			case 10:
			{
				ip2=fopen("head2_input.txt", "r");
				head2=FileInput(head2,ip2);
				fclose(ip2);
				printList(head2);
				
			}
		}

		switch(opertn)
		{
			case 0:
				printList(head1);
				break;
			case 1:
			{
				printf("Enter the record to be inserted: \n");
				flag=0;
				printf("Employee Name: ");
				gets(employeeName);
				
				printf("Project Name: ");
				gets(projectName);
				printf("Number of hours: ");
				scanf("%u", &numberOfHours);
				getchar();
				printf("Employee Address: ");
				gets(employeeAddress);
				printf("Phone Number: ");
				scanf("%u", &phoneNumber);
				printf("Employee Salary: ");
				scanf("%u", &employeeSalary);
				
				status=checkValidity(employeeName, projectName, numberOfHours, employeeAddress, phoneNumber, employeeSalary);
				
				if(status==1){
					
					nptr=makeNode(employeeName, projectName, numberOfHours, employeeAddress, phoneNumber, employeeSalary);
					
					if(nptr==NULL){
						status=FAILURE;
					}
					else{
						status=insertNode(&head1, nptr);	
					}
					
	
					if(status==2)
					{
						printf("\nInsertion was successful.\n");
					}
					else if(status)
					{
						printf("\nInsertion is successful.\n");					
					}
					else
					{
						printf("\nInsertion failed. The heap is full.\n");
					}
				}
				
				printList(head1);

				break;
			}
			case 2:
			{
				printf("\nEnter the record to be deleted: \n");
				printf("Employee Name: ");
				gets(employeeName);
				printf("Project Name: ");
				gets(projectName);

				status=deleteNode(&head1, employeeName, projectName);

				if (!status)
				{
					printf("\nThe record was not found.\n"); //sending messege of failure.
				}
				else
				{
					printf("\nThe record was successfully deleted.\n");
				}

				printList(head1);

				break;
			}
			case 3:
			{
				printf("The number of records are %d", count);
				break;
			}
			case 4:
			{
				status=isEmpty();
				if(status){
					printf("The record is empty.");
				}
				else{
					printf("The record is not empty.");
				}
				break;
			}
			case 5:
			{
				printf("\nEnter the project name for which maximum hours are required: ");
				gets(projectName);
				getch();
				getMaxNumHrs(head1, projectName);
				break;	
			}
			case 6:
			{
				listUnique(head1);
				printList(head1);
				break;
			}
			case 7:
			{
				head3->next=listUnion(head1,head2);
				printf("\nUnion of both the lists is obtained.\n");
				printList(head3);
				break;
			}
			case 8:
			{
				head3->next=listIntersection(head1,head2);
				printf("\nIntersection is obtained.\n");
				printList(head3);
				break;
			}
			case 9:
			{
				head3->next=listDifference(head1, head2);
				printf("\nList difference is obtained.\n");
				printList(head3);
				break;
			}
			case 10:
			{
				head3->next=symmetricDifference(head1,head2);
				printf("The symmentric difference is obtained: \n");
				printList(head3);
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
	op1=fopen("head1_output.txt","w");
	FileWrite(head1,op1);
	fclose(op1);
	op3=fopen("head3_output.txt","w");
	FileWrite(head3,op3);
	fclose(op3);
	return 0;

}
