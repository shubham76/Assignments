#include <stdio.h>
#include <conio.h>
#include <string.h>

int size=10;

enum status_code {FAILURE, SUCCESS};



struct Employee_Record_System
{
	char employee_name[40];
	char project_name[25];
	unsigned int number_of_hours;
	char employee_address[100];
	unsigned long long int phone_number;
	unsigned int employee_salary;	
};

void SortRecord(struct Employee_Record_System Employee_Record1[], int n1)
{
	int i, j, min, flag=0;
	struct Employee_Record_System temp;

	for(i=0; i<n1 && !flag; i++)
	{
		if(Employee_Record1[i+1].employee_name[0]=='\0') //Sorting stops when it encounter blank record.
			flag=1;
		else
			min=i;
		for(j=i+1; j<n1 && !flag; j++)
		{
			if(strcmp(Employee_Record1[min].employee_name, Employee_Record1[j].employee_name)>=0)
			{
				if(strcmp(Employee_Record1[min].employee_name, Employee_Record1[j].employee_name)>0)
					min=j;
				else
				{
					if(strcmp(Employee_Record1[min].project_name, Employee_Record1[j].project_name)>0)
						min=j;
				}
			}
		}
		temp=Employee_Record1[i];
		Employee_Record1[i]=Employee_Record1[min];
		Employee_Record1[min]=temp;
	}
}

void Initialize(struct Employee_Record_System Employee_Record1[], int size)
{
	int i;

	for (i = 0; i < size; ++i)
	{
		Employee_Record1[i].employee_name[0]='\0';
		Employee_Record1[i].project_name[0]='\0';
		Employee_Record1[i].number_of_hours=0;
		Employee_Record1[i].employee_address[0]='\0';
		Employee_Record1[i].phone_number=0;
		Employee_Record1[i].employee_salary=0;
	}
}

enum status_code Insert(struct Employee_Record_System Employee_Record1[], char employee_name[], char project_name[], unsigned int number_of_hours, char employee_address[], unsigned int phone_number, unsigned int employee_salary, int n1)
{
	int i;
	enum status_code status=FAILURE;
		
	//updating the list
	for (i = 0; i < n1 && !status; ++i)
	{
		if(strcmp(Employee_Record1[i].employee_name,employee_name)==0) //checks if name is same or not
			if(strcmp(Employee_Record1[i].project_name,project_name)==0) //if name is same then only checks project name
			{
				Employee_Record1[i].number_of_hours=number_of_hours;
				strcpy(Employee_Record1[i].employee_address, employee_address);
				Employee_Record1[i].phone_number=phone_number;
				Employee_Record1[i].employee_salary=employee_salary;
				
				status=SUCCESS; //confirms the updation
			}
	}

	//inserting new employee information
	if(status==0)
	{
		for (i = 0; i < size && !status; ++i)
		{
			if(Employee_Record1[i].employee_name[0]=='\0')
			{
				strcpy(Employee_Record1[i].employee_name,employee_name);
				strcpy(Employee_Record1[i].project_name,project_name);
				Employee_Record1[i].number_of_hours=number_of_hours;
				strcpy(Employee_Record1[i].employee_address,employee_address);
				Employee_Record1[i].phone_number=phone_number;
				Employee_Record1[i].employee_salary=employee_salary;

				status=SUCCESS; //confirms the insertion
			}
		}
	}

	return status;
}

enum status_code Delete(struct Employee_Record_System Employee_Record1[], char employee_name[], char project_name[], int n1)
{
	int i;
	enum status_code status=FAILURE;

	for (i = 0; i < n1 && !status; ++i)
	{
		if(strcmp(Employee_Record1[i].employee_name,employee_name)==0)
		{
			if(strcmp(Employee_Record1[i].project_name,project_name)==0)
			{
				//deleting element only if it's name and project neme is same.
				Employee_Record1[i].employee_name[0]='\0';
				Employee_Record1[i].project_name[0]='\0';
				Employee_Record1[i].number_of_hours=0;
				Employee_Record1[i].employee_address[0]='\0';
				Employee_Record1[i].phone_number=0;
				Employee_Record1[i].employee_salary=0;

				status=SUCCESS;
			}
		}
	}
	//to shift the empty records at the end.
	

	if(status)
	{
		while(i<n1)
		{
			Employee_Record1[i-1]=Employee_Record1[i];
			i++;
		}
	}

	return status;
}

void getNumRecords(struct Employee_Record_System Employee_Record1[], int size)
{
	int count=0, i;

	for (i = 0; i < size; ++i)
	{
		if(Employee_Record1[i].employee_name[0]!='\0')
			count++;
	}

	printf("The number of active records are %d\n", count);
}

void isEmpty(struct Employee_Record_System Employee_Record1[], int size)
{
	int i, empty=FAILURE;

	for (i = 0; i < size && !empty; ++i)
	{
		if (Employee_Record1[i].employee_name[0]!='\0')
		{
			empty=SUCCESS;
		}
	}

	//printing if the records are empty or not.
	if (empty)
	{
		printf("The list is not empty.\n");
	}
	else
	{
		printf("The list is empty.\n");
	}
}

void IsFull(struct Employee_Record_System Employee_Record1[], int size)
{
	int i, full=SUCCESS;

	for (i = 0; i < size && full; ++i)
	{
		if (Employee_Record1[i].employee_name[0]=='\0')
		{
			full=FAILURE;
		}
	}

	//printing if the records are full or not.
	if (full)
	{
		printf("The list is full.\n");
	}
	else
	{
		printf("The list is not full.\n");
	}
}

//getting maximum number of hours spend i=on an prject
int getMaxNumHrs(struct Employee_Record_System Employee_Record1[], char project_name[], int n1)
{
	int i, max_hours=0, max_position;

	for (i = 0; i < n1; ++i)
	{
		if(strcmp(Employee_Record1[i].project_name,project_name)==0)
		{
			if(max_hours<Employee_Record1[i].number_of_hours)
			{
				max_hours=Employee_Record1[i].number_of_hours; //getting maximum no. of hours.
				max_position=i; //storing the location where we find the max.
			}
		}					
	}

	for (i = 0; i < n1; ++i)
	{
		if(strcmp(Employee_Record1[i].project_name,project_name)==0)
		{
			if(Employee_Record1[i].number_of_hours==max_hours)
			{
				puts(Employee_Record1[i].employee_name);		//printing the emplyee names
				printf("\n");
			}
		}
	}

	return max_hours; //eturning maximum number of hours pend on that project.
}

//to remove duplicates from the given records

int isUnique(struct Employee_Record_System Employee_Record1[], int n1)
{
	int i, j, n=-1;//here n counts the number of elements in final list.

	SortRecord(Employee_Record1, n1);
	//we'll apply the following algorithm on sorted list

	j=0;

	for (i = 0; i < n1; ++i)
	{
		if(strcmp(Employee_Record1[i].employee_name, Employee_Record1[i+1].employee_name)!=0)
		{
			Employee_Record1[j++]=Employee_Record1[i];
			n++;
		}
		else if(strcmp(Employee_Record1[i].employee_name, Employee_Record1[i+1].employee_name)==0)
		{
			if(strcmp(Employee_Record1[i].project_name, Employee_Record1[i+1].employee_name)!=0)
			{
				Employee_Record1[j++]=Employee_Record1[i];
				n++;
			}
		}
	}	

	printf("The dupicates are removed.\n");

	return n;
}

int list_Union(struct Employee_Record_System Employee_Record1[], struct Employee_Record_System Employee_Record2[], int n1, int n2, int size, struct Employee_Record_System Employee_Record3[])
{
	int i=0, j=0, k=0;

	SortRecord(Employee_Record1, n1);
	SortRecord(Employee_Record2, n2);

	Initialize(Employee_Record3, 2*size); //initialising all elements to default value

	while(i<n1&&j<n2)
	{
		if(strcmp(Employee_Record1[i].employee_name,Employee_Record2[j].employee_name)!=0)
		{
			if(strcmp(Employee_Record1[i].employee_name,Employee_Record2[j].employee_name)<0)
			{
			
				Employee_Record3[k]=Employee_Record1[i];
				i++;
				k++;
			}
			else
			{
				Employee_Record3[k]=Employee_Record2[j];
				j++;
				k++;
			}	
		}
	    else
		{
			if(strcmp(Employee_Record1[i].project_name,Employee_Record2[j].project_name)==0)
			{
				Employee_Record3[k]=Employee_Record1[i];
				i++;
				j++;
				k++;
			}
			else if(strcmp(Employee_Record1[i].project_name,Employee_Record2[j].project_name)<0)
			{
				Employee_Record3[k]=Employee_Record1[i];
				i++;
				k++;
			}
			else
			{
				Employee_Record3[k]=Employee_Record2[j];
				j++;
				k++;
			}
		}	
	}
	while(i<n1)
	{
		Employee_Record3[k]=Employee_Record1[i];
		i++;
		k++;
	}
	while(j<n2)
	{
		Employee_Record3[k]=Employee_Record2[j];
		j++;
		k++;
	}

	return k;
}

int list_intersection(struct Employee_Record_System Employee_Record1[], struct Employee_Record_System Employee_Record2[], int n1, int n2, int size, struct Employee_Record_System Employee_Record3[])
{
	int i=0, j=0, k=0;

	SortRecord(Employee_Record1, n1);
	SortRecord(Employee_Record2, n2);

	Initialize(Employee_Record3, 2*size); //initialising all elements to default value

	for (i = 0; i < n1; ++i)
	{
		for (j = 0; j < n2; ++j)
		{
			if(strcmp(Employee_Record1[i].employee_name, Employee_Record2[j].employee_name)==0 && strcmp(Employee_Record1[i].project_name, Employee_Record2[j].project_name)==0)
			{
				if(Employee_Record1[i].employee_salary>Employee_Record2[j].employee_salary)
				{
					Employee_Record3[k]=Employee_Record1[i];
					k++;
				}
				else
				{
					Employee_Record3[k]=Employee_Record2[j];	
					k++;
				}
			}	
		}		
	}
	//the obtained list will be sorted.

	return k;

}

int list_difference(struct Employee_Record_System Employee_Record1[], struct Employee_Record_System Employee_Record2[], int n1, int n2, int size, struct Employee_Record_System Employee_Record3[])
{
	int i, j, k=0, flag;

	for(i=0; i<n1; i++)
	{
		flag=0;

		for(j=0; j<n2; j++)
		{
			if(strcmp(Employee_Record1[i].employee_name, Employee_Record2[j].employee_name)!=0 && strcmp(Employee_Record1[i].project_name, Employee_Record2[j].project_name)!=0)
			{
				flag=1;
			}
		}

		if (!flag)
		{
			Employee_Record3[k]=Employee_Record1[i];
			k++;
		}
	}
	//The output is sorted.
	printf("List difference is obtained.\n");

	return k;
}

int list_symmetric_difference(struct Employee_Record_System Employee_Record1[], struct Employee_Record_System Employee_Record2[],int n1, int n2, int size, struct Employee_Record_System Employee_Record3[])
{
	int i=0, j=0, k=0, flag;
	struct Employee_Record_System temp1[2*size], temp2[2*size];
	int n3, n4, n5;	

	Initialize(Employee_Record3, 2*size);

	n4=list_difference(Employee_Record1, Employee_Record2, n1, n2, size, temp1);
	n5=list_difference(Employee_Record2, Employee_Record2, n2, n1, size, temp2);
	n3=list_Union(temp1, temp2, n4, n5, size, Employee_Record3);

	printf("The symmetric difference is obtained.\n");

	return n3;
}

void printList(struct Employee_Record_System Employee_Record[], int n)
{
	int i;
	
	for(i=0; i<n; i++)
	{
		printf("\nEmployee Name: %s\n", Employee_Record[i].employee_name);
		printf("Project Name: %s\n", Employee_Record[i].project_name);
		printf("Number of hours: %u\n", Employee_Record[i].number_of_hours);
		printf("Employee Address: %s\n", Employee_Record[i].employee_address);
		printf("Phone Number: %llu\n", Employee_Record[i].phone_number);
		printf("Employee Salary: %u\n", Employee_Record[i].employee_salary);
	}
}

int main(int argc, char const *argv[])
{
	struct Employee_Record_System Employee_Record1[size], Employee_Record2[size], Employee_Record3[2*size];
	int n1, n2, n3, opertn, i, status, max_hours;
	char employee_name[40], project_name[20], employee_address[100];
	unsigned int number_of_hours, phone_number, employee_salary; 
	
	Initialize(Employee_Record1, size);
	
	printf("Enter the size of the first record: ");
	scanf("%d", &n1);
	printf("Enter the data in record: \n");
	getchar();
	for (i = 0; i < n1; ++i)
	{
		printf("Employee Name: ");
		gets(Employee_Record1[i].employee_name);
		printf("Project Name: ");
		gets(Employee_Record1[i].project_name);
		printf("Number of hours: ");
		scanf("%u", &Employee_Record1[i].number_of_hours);
		getchar();
		printf("Employee Address: ");
		gets(Employee_Record1[i].employee_address);
		printf("Phone Number: ");
		scanf("%llu", &Employee_Record1[i].phone_number);
		getchar();
		printf("Employee Salary: ");
		scanf("%d", &Employee_Record1[i].employee_salary);
		
		if(i<n1-1)
			printf("\nEnter the next record.\n");
		getchar();
	}
	
	printList(Employee_Record1, n1);

	printf("\nSelect your operation from the following:\n\n\
1.Insert a record.\n\
2.Delete a record.\n\
3.To get number of active records.\n\
4.To check if a record is empty or not.\n\
5.To check if the list is full or not.\n\
6.To get maximum number of hours spent on a particular project.\n\
7.To remove duplicates from a list.\n\
8.To get the union of two lists.\n\
9.To get the intersection of the two lists.\n\
10.To get the difference between two lists.\n\
11.To get the symmentric difference between the two lists.\n");
	
	scanf("%d", &opertn);
	getchar();

	switch(opertn)
	{
		case 8:
		case 9:
		case 10:
		case 11:
		{
			Initialize(Employee_Record2, size);

			printf("\nEnter the size of the second record: ");
			scanf("%d", &n2);
			printf("Enter the data for the second record: \n");
			getchar();

			for (i = 0; i < n2; ++i)
			{
				printf("\nEnter the record to be inserted: \n");
				printf("Employee Name: ");
				gets(Employee_Record2[i].employee_name);
				printf("Project Name: ");
				gets(Employee_Record2[i].project_name);
				printf("Number of hours: ");
				scanf("%u", &Employee_Record2[i].number_of_hours);
				getchar();
				printf("Employee Address: ");
				gets(Employee_Record2[i].employee_address);
				printf("Phone Number: ");
				scanf("%llu", &Employee_Record2[i].phone_number);
				getchar();
				printf("Employee Salary: ");
				scanf("%u", &Employee_Record2[i].employee_salary);
				
				if(i<n2-1)
					printf("\nEnter the next record.\n");
					
				getchar();
			}
			
		}
	}

	switch(opertn)
	{
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
			scanf("%llu", &phone_number);
			printf("Employee Salary: ");
			scanf("%u", &employee_salary);

			status=Insert(Employee_Record1,employee_name,project_name,number_of_hours,employee_address,phone_number,employee_salary, n1);

			if(status)
			{
			
				printf("\nInsertion was successful.\n");
				n1++;
			}
			else
				printf("\nInsrtion failed. The list is full.\n");
				

			

			printList(Employee_Record1, n1);

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

			status=Delete(Employee_Record1, employee_name, project_name, n1);

			if (!status)
			{
				printf("\nThe record was not found.\n"); //sending messege of failure.
			}
			else
			{
				printf("\nThe record was successfully deleted.\n");
				n1--;
			}
			

			printList(Employee_Record1, n1);

			break;
		}
		case 3:
		{
			getNumRecords(Employee_Record1, size);
			break;
		}
		case 4:
		{
			isEmpty(Employee_Record1, size);
			break;
		}
		case 5:
		{
			IsFull(Employee_Record1, size);
			break;
		}
		case 6:
		{
			printf("\nEnter the project name for which maximum hours are required: ");
			gets(project_name);
			getch();
			max_hours=getMaxNumHrs(Employee_Record1, project_name, n1);
			printf("\nMaximum number of hours for project %s is %d\n", project_name, max_hours);
			break;	
		}
		case 7:
		{
			n1=isUnique(Employee_Record1, size);
			printList(Employee_Record1, n1);
			break;
		}
		case 8:
		{
			n3=list_Union(Employee_Record1, Employee_Record2, n1, n2, size, Employee_Record3);
			printf("\nUnion of both the lists is obtained.\n");
			printList(Employee_Record3, n3);
			break;
		}
		case 9:
		{
			n3=list_intersection(Employee_Record1, Employee_Record2, n1, n2, size, Employee_Record3);
			printf("\nIntersection is obtained.\n");
			printList(Employee_Record3, n3);
			break;
		}
		case 10:
		{
			n3=list_difference(Employee_Record1, Employee_Record2, n1, n2, size, Employee_Record3);
			printList(Employee_Record3, n3);
			break;
		}
		case 11:
		{
			n3=list_symmetric_difference(Employee_Record1, Employee_Record2, n1, n2, size, Employee_Record3);
			printList(Employee_Record3, n3);
			break;
		}
		default:
		{
			printf("\nWrong option is selected.\n");
			break;
		}
	}

	return 0;
}

