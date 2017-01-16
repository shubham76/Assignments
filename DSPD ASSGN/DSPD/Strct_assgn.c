#include "stdio.h"
#include "conio.h"
#include "string.h"

int size=100;
enum status_code {FAILURE, SUCCESS};

struct Employee_Record_System
{
	char employee_name[40];
	char project_name[25];
	unsigned int number_of_hours;
	char employee_address[100];
	unsigned int phone_number;
	unsigned int employee_salary;	
};

void Initialize(struct Employee_Record_System Employee_Record[], int size)
{
	int i;

	for (i = 0; i < size; ++i)
	{
		Employee_Record[i].employee_name[0]='\0';
		Employee_Record[i].project_name[0]='\0';
		Employee_Record[i].number_of_hours=0;
		Employee_Record[i].employee_address[0]='\0';
		Employee_Record[i].phone_number=0;
	}
}

enum status_code Insert(struct Employee_Record_System Employee_Record[], char employee_name[], char project_name[], int number_of_hours, char employee_address[], unsigned int phone_number, int employee_salary, int size)
{
	int i, status=FAILURE;
		
	//updating the list
	for (i = 0; i < size && !status; ++i)
	{
		if(strcmp(Employee_Record[i].employee_name,employee_name)==0) //checks if name is same or not
			if(strcmp(Employee_Record[i].project_name,project_name)==0) //if name is same then only checks project name
			{
				Employee_Record[i].number_of_hours=number_of_hours;
				strcpy(Employee_Record[i].employee_address, employee_address);
				Employee_Record[i].phone_number=phone_number;
				status=SUCCESS; //confirms the updation
			}
	}

	//inserting new employee information
	if(status==0)
	{
		for (i = 0; i < size && !status; ++i)
		{
			if(Employee_Record[i].employee_name[0]=='\0')
			{
				strcpy(Employee_Record[i].employee_name,employee_name);
				strcpy(Employee_Record[i].project_name,project_name);
				Employee_Record[i].number_of_hours=number_of_hours;
				strcpy(Employee_Record[i].employee_address,employee_address);
				Employee_Record[i].phone_number=phone_number;

				status=SUCCESS; //confirms the insertion
			}
		}
	}

	return status;
}

enum status_code Delete(struct Employee_Record_System Employee_Record[], char employee_name[], char project_name[], int size)
{
	int i, status=FAILURE;

	for (i = 0; i < size && !status; ++i)
	{
		if(strcmp(Employee_Record[i].employee_name,employee_name)==0)
		{
			if(strcmp(Employee_Record[i].project_name,project_name)==0)
			{
				//deleting element only if it's name and project neme is same.
				Employee_Record[i].employee_name[0]='\0';
				Employee_Record[i].project_name[0]='\0';
				Employee_Record[i].number_of_hours=0;
				Employee_Record[i].employee_address[0]='\0';
				Employee_Record[i].phone_number=0;

				status=SUCCESS;
			}
		}
	}
	//to shift the empty records at the end.

	if(status)
	{
		while(Employee_Record[i].employee_name!='\0')
		{
			Employee_Record[i-1]=Employee_Record[i];
		}
	}

	if (!status)
	{
		printf("The element was not found.\n"); //sending messege of failure.
	}

	return status;
}

void getNumRecords(struct Employee_Record_System Employee_Record[], int size)
{
	int count=0, i;

	for (i = 0; i < size; ++i)
	{
		if(Employee_Record[i].employee_name[0]!='\0')
			count++;
	}

	printf("The number of active records are %d\n", count);
}

void isEmpty(struct Employee_Record_System Employee_Record[], int size)
{
	int i, empty=FAILURE;

	for (i = 0; i < size && !empty; ++i)
	{
		if (Employee_Record[i].employee_name[0]!='\0')
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

void IsFull(struct Employee_Record_System Employee_Record[], int size)
{
	int i, full=SUCCESS;

	for (i = 0; i < size && full; ++i)
	{
		if (Employee_Record[i].employee_name[0]=='\0')
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
int getMaxNumHrs(struct Employee_Record_System Employee_Record[], char project_name[], int size)
{
	int i, max_hours=0, max_position;

	for (i = 0; i < size; ++i)
	{
		if(strcmp(Employee_Record[i].project_name,project_name)==0)
		{
			if(max_hours<Employee_Record[i].number_of_hours)
			{
				max_hours=Employee_Record[i].number_of_hours; //getting maximum no. of hours.
				max_position=i; //storing the location where we find the max.
			}
		}					
	}

	for (i = 0; i < size; ++i)
	{
		if(strcmp(Employee_Record[i].project_name,project_name)==0)
		{
			if(Employee_Record[i].number_of_hours==max_hours)
			{
				puts(Employee_Record[i].employee_name);		//printing the emplyee names
				printf("\n");
			}
		}
	}

	return max_hours; //eturning maximum number of hours pend on that project.
}

//to remove duplicates from the given records

void isUnique(struct Employee_Record_System Employee_Record[], int size)
{
	int status=FAILURE, i;

	SortRecord(Employee_Record, size);
	//we'll apply the following algorithm on sorted list

	for (i = 1; i < size; ++i)
	{
		if(strcmp(Employee_Record[i].employee_name, Employee_Record[i-1].employee_name)==0)
		{
			if(strcmp(Employee_Record[i].project_name, Employee_Record[i-1].project_name)==0)
			{
				//if project name and emplyee name is duplicated then we initialise
				Employee_Record[i].employee_name[0]='\0';
				Employee_Record[i].project_name[0]='\0';
				Employee_Record[i].number_of_hours=0;
				Employee_Record[i].employee_address[0]='\0';
				Employee_Record[i].phone_number=0;
			}
		}
	}

	SortRecord(Employee_Record, size);	

	printf("The dupicates are removed.\n");
}

void list_Union(struct Employee_Record_System Employee_Record1[], struct Employee_Record_System Employee_Record2[], int size)
{
	int i=0, j=0, k=0;
	struct Employee_Record_System Employee_Record3[2*size];

	//assuming both lists are sorted.

	Initialize(Employee_Record3, 2*size); //initialising all elements to default value

	while(i<size && j<size)
	{
		if(strcmp(Employee_Record1[i].employee_name, Employee_Record2[j].employee_name)>0)
		{
			Employee_Record3[k]=Employee_Record2[j];
			j++, k++;
		}
		else if(strcmp(Employee_Record1[i].employee_name, Employee_Record2[j].employee_name)<0)
		{
			Employee_Record3[k]=Employee_Record1[i];
			i++, k++;
		}
		else if((strcmp(Employee_Record1[i].employee_name, Employee_Record2[j].employee_name)==0) && (strcmp(Employee_Record1[i].project_name, Employee_Record2[j].project_name)>0))
		{
			Employee_Record3[k]=Employee_Record2[j];
			j++, k++;
		}
		else if((strcmp(Employee_Record1[i].employee_name, Employee_Record2[j].employee_name)==0) && (strcmp(Employee_Record1[i].project_name, Employee_Record2[j].project_name)<0))
		{			
	        Employee_Record3[k]=Employee_Record1[i];
			i++, k++;
		}
		//if both have same key then we copy record of first list
		else if((strcmp(Employee_Record1[i].employee_name, Employee_Record2[j].employee_name)==0) && (strcmp(Employee_Record1[i].project_name, Employee_Record2[j].project_name)==0))
		{
			Employee_Record3[k]=Employee_Record1[i];
			i++, k++;
		}		
	}	
	if(i<size)
	{
		while(j<size)
		{
			Employee_Record3[k]=Employee_Record2[j];
			j++, k++;
		}
	}
	else
	{
		while(i<size)
		{
			Employee_Record3[k]=Employee_Record1[i];
			i++, k++;
		}
	}
	
	SortRecord(Employee_Record3, size);

	printf("Union of both the lists is obtained.\n");
}

void list_intersection(struct Employee_Record_System Employee_Record1[], struct Employee_Record_System Employee_Record2[], int size)
{
	int i=0, j=0, k=0;
	struct Employee_Record_System Employee_Record3[size];

	//assuming both lists are sorted.

	for (i = 0; i < size; ++i)
	{
		for (j = 0; j < size; ++j)
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

	printf("Intersection is obtained.\n");

}

void list_difference(struct Employee_Record_System Employee_Record1[], struct Employee_Record_System Employee_Record2[], int size)
{
	int i, j, k=0, flag;
	struct Employee_Record_System Employee_Record3[size];

	for(i=0; i<size; i++)
	{
		flag=0;

		for(j=0; j<size; j++)
		{
			if(strcmp(Employee_Record1[i].employee_name, Employee_Record2[j].employee_name)==0 && strcmp(Employee_Record1[i].project_name, Employee_Record2[j].project_name)==0)
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
}

void list_symmetric_difference(struct Employee_Record_System Employee_Record1[], struct Employee_Record_System Employee_Record2[], int size)
{
	int i=0, j=0, k=0, flag;
	struct Employee_Record_System Employee_Record3[size];

	//assuming the two lists are sorted.

	for(i=0; i<size; i++)
	{
		flag=0;

		for(j=0; j<size; j++)
		{
			if(strcmp(Employee_Record1[i].employee_name, Employee_Record2[j].employee_name)==0 && strcmp(Employee_Record1[i].project_name, Employee_Record2[j].project_name)==0)
			{
				flag=1;
			}
		}

		if (!flag)
		{
			Employee_Record3[k]=Employee_Record1[j];				
			k++;
		}
	}

	for(i=0; i<size; i++)
	{
		flag=0;

		for(j=0; j<size; j++)
		{
			if(strcmp(Employee_Record2[i].employee_name, Employee_Record1[j].employee_name)==0 && strcmp(Employee_Record2[i].project_name, Employee_Record1[j].project_name)==0)
			{
				flag=1;
			}
		}

		if (!flag)
		{
			Employee_Record3[k]=Employee_Record2[i];			
			k++;
		}
	}

	SortRecord(Employee_Record3, size);

	printf("The symmetric difference is obtained.\n");
}


void SortRecord(struct Employee_Record_System Employee_Record[], int size)
{
	int i, j, min;
	struct Employee_Record_System temp;

	for(i=0; i<size; i++)
	{
		min=i;
		for(j=i+1; j<size; j++)
		{
			if(strcmp(Employee_Record[min].employee_name, Employee_Record[j].employee_name)>=0)
			{
				if(strcmp(Employee_Record[min].employee_name, Employee_Record[j].employee_name)>0)
					min=j;
				else
				{
					if(strcmp(Employee_Record[min].project_name, Employee_Record[j].project_name)>0)
						min=j;
				}
			}
		}
		temp=Employee_Record[i];
		Employee_Record[i]=Employee_Record[min];
		Employee_Record[min]=temp;
	}

	printf("The list is sorted!\n");
}

int main(int argc, char const *argv[])
{
	struct Employee_Record_System Employee_Record[size];
	int i, n, x;
	unsigned int c, e, f;
	char a[size], b[size], d[size];

	scanf("%s %s %d %s %d %d", a, b, &c, d, &e, &f);
	
	x=Insert(Employee_Record, a,b,c,d,e,f, size);
	
	printf("%d\n", x);

	printf("%s %s %d %s %d", Employee_Record[0].employee_name, Employee_Record[0].project_name, Employee_Record[0].number_of_hours, Employee_Record[0].employee_address, Employee_Record[0].phone_number);

	return 0;
}
