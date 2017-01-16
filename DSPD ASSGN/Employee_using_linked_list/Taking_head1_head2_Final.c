#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>

typedef enum {FAILURE, SUCCESS, UPDATE} status_code;

int count=0;		//global variable to maintain the number of nodes in the list

typedef struct Employee_Tag{
	char employee_name[40];
	char project_name[25];
	unsigned int number_of_hours;
	char employee_address[100];
	unsigned int phone_number;
	unsigned int employee_salary;
	struct Employee_Tag *next;
}node;

//This function makes a node and sets its 'next' to NULL and returns the pointer pointing to the node
node * makeNode(char employee_name[], char project_name[], unsigned int number_of_hours, char employee_address[], unsigned int phone_number, unsigned int employee_salary){
	node * ptr;
	ptr=(node *)(malloc(sizeof(node)));
	if(ptr!=NULL){
		strcpy(ptr->employee_name, employee_name);
		strcpy(ptr->project_name, project_name);
		ptr->number_of_hours=number_of_hours;
		strcpy(ptr->employee_address, employee_address);
		ptr->phone_number=phone_number;
		ptr->employee_salary=employee_salary;
	}
	ptr->next=NULL;
	return ptr;
}

/*This function compares the the lists whose head pointers are passed as parameters and returns 1 if first list is smaller, 0 if second list is smaller and 
0 if both the lists are same when their keys are compared*/  
int compareNode(node * ptr1, node * ptr2){ 
	int flag, cmp1, cmp2;
	/*Return flag=1 if ptr1 is lesser than ptr2 else return flag=-1 & flag=0 if both keys are same*/
	cmp1=strcmp(ptr1->employee_name, ptr2->employee_name);
	cmp2=strcmp(ptr1->project_name, ptr2->project_name);

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
//This function inserts the node at the correct position and returns the head pointer
status_code insertNode(node **head, node * nptr){
	status_code status=SUCCESS;
	node *ptr;
	ptr=*head;
	int flag=compareNode(ptr, nptr), cmp;
	if(*head==NULL){		//checking for 0 nodes
		*head=nptr;		//set head if it is NULL
	}
	else if(ptr->next==NULL){		//checking for one nodes
		if(flag>0){			//ptr is smaller than nptr(node to be inserted)
			ptr->next=nptr;		
			nptr->next=NULL;
		}
		else if(flag<0){		//nptr(node to be inserted is smaller than ptr
			nptr->next=ptr;
			*head=nptr;	
		}
		else{		//update
			ptr->number_of_hours=nptr->number_of_hours;
			strcpy(ptr->employee_address,nptr->employee_address);
			ptr->phone_number=nptr->phone_number;
			ptr->employee_salary=nptr->employee_salary;

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
			ptr->number_of_hours=nptr->number_of_hours;
			strcpy(ptr->employee_address,nptr->employee_address);
			ptr->phone_number=nptr->phone_number;
			ptr->employee_salary=nptr->employee_salary;

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
status_code deleteNode(node **head, char employee_name[], char project_name[]){
	status_code status=SUCCESS;
	int cmp1, cmp2;
	node* ptr, *prev;
	if(*head==NULL)
		status=FAILURE;
	else{
		int flag=0;
		prev=ptr=*head;
		while(!flag && ptr!=NULL){			//flag will be set if the node with that particular employee name and project name is found
			cmp1=strcmp(ptr->employee_name, employee_name);
			cmp2=strcmp(ptr->project_name, project_name);
			//printf("%d\n", cmp);
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
status_code isEmpty(){
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
void getMaxNumHrs(node * head, char project_name[]){
	int maxHrs=0;
	node *ptr=head, *maxPtr;

	if(head!=NULL){
		while(ptr!=NULL){
			if(!strcmp(project_name, ptr->project_name)){
				if(ptr->number_of_hours>maxHrs){
					maxHrs=ptr->number_of_hours;
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
		if(!strcmp(project_name, ptr->project_name)){
			if(ptr->number_of_hours==maxHrs){
				puts(ptr->employee_name);
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
			ptr->next=makeNode(ptr1->employee_name, ptr1->project_name, ptr1->number_of_hours, ptr1->employee_address, ptr1->phone_number, ptr1->employee_salary);
			ptr=ptr->next;
			ptr1=ptr1->next;
			ptr2=ptr2->next;
		}
		else{
			if(cmp>0){		//if node in list1 is smaller,we copy the data in that node 
				ptr->next=makeNode(ptr1->employee_name, ptr1->project_name, ptr1->number_of_hours, ptr1->employee_address, ptr1->phone_number, ptr1->employee_salary);
				ptr=ptr->next;
				ptr1=ptr1->next;
			}
			else if(cmp<0){		//if node in list2 is smaller,we copy the data in that node
				ptr->next=makeNode(ptr2->employee_name, ptr2->project_name, ptr2->number_of_hours, ptr2->employee_address, ptr2->phone_number, ptr2->employee_salary);
				ptr=ptr->next;
				ptr2=ptr2->next;
			}
		}
	}

	while(ptr1!=NULL){		//if ptr2 has become NULL then we have to copy the nodes of ptr1
		ptr->next=makeNode(ptr1->employee_name, ptr1->project_name, ptr1->number_of_hours, ptr1->employee_address, ptr1->phone_number, ptr1->employee_salary);
		ptr=ptr->next;
		ptr1=ptr1->next;
	}
	
	while(ptr2!=NULL){		//if ptr1 has become NULL then we have to copy the nodes of ptr2
		ptr->next=makeNode(ptr2->employee_name, ptr2->project_name, ptr2->number_of_hours, ptr2->employee_address, ptr2->phone_number, ptr2->employee_salary);
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
				ptr->next=makeNode(ptr1->employee_name, ptr1->project_name, ptr1->number_of_hours, ptr1->employee_address, ptr1->phone_number, ptr1->employee_salary);
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
			ptr->next=makeNode(ptr1->employee_name, ptr1->project_name, ptr1->number_of_hours, ptr1->employee_address, ptr1->phone_number, ptr1->employee_salary);
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
		fprintf(fp,"%s\n", ptr->employee_name);
		fprintf(fp, "%s\n", ptr->project_name);
		fprintf(fp,"%u\n",ptr->number_of_hours);
		fprintf(fp,"%s\n", ptr->employee_address);
		fprintf(fp,"%u\n",ptr->phone_number);
		fprintf(fp, "%u\n",ptr->employee_salary);
		fprintf(fp,"\n");
		ptr=ptr->next;	
	}
}

//This function reads from the file being pointed to by the file pointer passed as parameter
node * FileInput(node *head1,FILE *fp){
	node *nptr;
	status_code status;
	
	char employee_name[40], project_name[20], employee_address[100];
	unsigned int number_of_hours, employee_salary; 
	unsigned int phone_number,c=0; 
	
	while(c=getc(fp)!=EOF){			//if it is not EOF, continue reading from the file   

			fscanf(fp, "%s", employee_name);
			
			fscanf(fp, "%s", project_name);	
			
			fscanf(fp,"%u",&number_of_hours);
			
			fscanf(fp, "%s", employee_address);
			
			fscanf(fp, "%u", &phone_number);
			
			fscanf(fp, "%u", &employee_salary);
			
			nptr=makeNode(employee_name, project_name, number_of_hours, employee_address, phone_number, employee_salary);
			status=insertNode(&head1, nptr);  //insertNode function inserts the node at the correct position ,so the list will be sorted
		
	}
	
	return head1;
}

//This function will print the list 
void printList(node *head){
	node *ptr=head->next;
	
	while(ptr!=NULL){
		printf("\nEmployee Name: %s\n", ptr->employee_name);
		printf("Project Name: %s\n", ptr->project_name);
		printf("Number of hours: %u\n", ptr->number_of_hours);
		printf("Employee Address: %s\n", ptr->employee_address);
		printf("Phone Number: %llu\n", ptr->phone_number);
		printf("Employee Salary: %u\n", ptr->employee_salary);

		ptr=ptr->next;
	}
}

int main(int argc, char const *argv[])
{
	node* head1=NULL, *head2=NULL, *head3=NULL, *nptr=NULL;
	int i, n1, n2, n3, opertn, max_hours;
	char employee_name[40], project_name[20], employee_address[100];
	unsigned int number_of_hours, employee_salary; 
	unsigned int phone_number; 
	status_code status;
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
				printf("Employee Name: ");
				gets(employee_name);
				printf("Project Name: ");
				gets(project_name);
				printf("Number of hours: ");
				scanf("%u", &number_of_hours);
				getchar();
				printf("Employee Address: ");
				gets(employee_address);
				printf("Phone Number: ");
				scanf("%u", &phone_number);
				printf("Employee Salary: ");
				scanf("%u", &employee_salary);

				nptr=makeNode(employee_name, project_name, number_of_hours, employee_address, phone_number, employee_salary);
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
					
				printList(head1);

				break;
			}
			case 2:
			{
				printf("\nEnter the record to be deleted: \n");
				printf("Employee Name: ");
				gets(employee_name);
				printf("Project Name: ");
				gets(project_name);
				getchar();

				status=deleteNode(&head1, employee_name, project_name);

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
				gets(project_name);
				getch();
				getMaxNumHrs(head1, project_name);
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
