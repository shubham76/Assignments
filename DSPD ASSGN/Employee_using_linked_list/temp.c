#include<stdio.h>
#include<conio.h>
#include<string.h>

main(){
	FILE *fp, *op;
	op=fopen("temp1.txt", "w");
	
	char employee_name[40], project_name[20], employee_address[100];
	unsigned int number_of_hours, employee_salary; 
	unsigned int phone_number,c=0; 
	fp=fopen("abc.txt", "r");
	
	while(c=getc(fp)!=EOF){

		fscanf(fp, "%s", employee_name);
			
		fscanf(fp, "%s", project_name);	
			
		fscanf(fp,"%u",&number_of_hours);
			
		fscanf(fp, "%s", employee_address);
			
		fscanf(fp, "%u", &phone_number);
			
		fscanf(fp, "%u", &employee_salary);
			
		fprintf(op,"%s\n", employee_name);
		fprintf(op, "%s\n", project_name);
		fprintf(op,"%u\n",number_of_hours);
		fprintf(op,"%s\n", employee_address);
		fprintf(op,"%u\n",phone_number);
		fprintf(op, "%u\n",employee_salary);
		fprintf(op,"\n");
		
	}
	
	fclose(fp);
	fclose(op);
}
