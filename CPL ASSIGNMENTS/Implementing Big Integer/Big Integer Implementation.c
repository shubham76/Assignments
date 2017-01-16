#include<stdio.h>
#include<math.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>

#define N 1000

int add1(int num1[], int num2[], int ans[], int n1, int n2){
	
	int i, j, k, temp, carry, add;
	
	carry=0;
	k=0;
	i=0;
	while(i<n1 || i<n2){
		add=num1[i]+num2[i]+carry;
		if(add>=10){
			ans[k++]=add-10;
			carry=1;
		}
		else{
			ans[k++]=add;
			carry=0;
		}
		i++;
	}
	if(carry==1)
		ans[k++]=carry;

	return k;	
}

int sub(int num1[], int num2[], int ans[], int n1, int n2){
	int i, j, k, temp, carry, diff;
	
	carry=0;
	k=0;
	i=0;
	while(i<n1 || i<n2){
		if(num1[i]>=num2[i]){
			diff=num1[i]-num2[i]-carry;
			ans[k++]=diff;
		}
		else{
			diff=10+num1[i]-num2[i]-carry;
			ans[k++]=diff;
			carry=1;
		}
		i++;
	}
	
	return k;
}

int mul(int num1[], int num2[], int ans[], int n1, int n2){
	
	int i, j, k, temp1, carry, diff;
	
	j=0;
	k=0;
	int y=-1;

	while(j<n2){
		carry=0;
		int carry1=0;
		y++;
		k=y;
		for(i=0; i<n1; i++){
			int sum=(num2[j]*num1[i]+carry)%10;
			carry=(num2[j]*num1[i]+carry)/10;
			
			if(ans[k]+sum>=10){
				ans[k]=ans[k]+sum-10+carry1;
				carry1=1;
			}
			else{
				ans[k]=ans[k]+sum+carry1;
				carry1=0;
			}
			k++;
		}
		if(ans[k]+carry>=10){
			ans[k]=ans[k]+carry-10+carry1;
			carry1=1;
			k++;
		}
		else{
			ans[k]=ans[k]+carry+carry1;
			carry1=0;
			k++;
		}		
		if(carry1==1){
			ans[k]=carry1;
			k++;
		}
		j++;
	}
	
	return k;
}

int div1(int num1[], int num2[], int n1, int n2){
	int ans[2*N]={0}, mod[N]={0}, i, j, k, temp, carry, add, div, flag1;
	
	int n=n2;
	int flag=0;
	div=0;
	while(!flag){
		div++;
		
		n=add1(num2, ans, ans,  n, n);
		
		if(n>n1){
			div--;
			flag=1;
		}
		else if(n<n1){
			continue;
		}
		else{
			for(i=n-1; i>=0; i--){
				if(ans[i]>num1[i]){
					flag=1;
				}
				else if(ans[i]<num1[i]){
					break;
				}
				else{
					continue;
				}
			}
			if(flag)
				div--;
		}	
	}
	/*To check the modulus!*/
	n=sub(ans, num1, ans, n, n1);
	n=sub(num2, ans, ans, n2, n);
	printf("\nThe modulus is\n");
	for(i=n-1; i>=0; i--){
		printf("%d", ans[i]);
	}
	return div;
}

int main(){
	
	
	char numStr1[N], numStr2[N];
	int num1[N]={0}, num2[N]={0}, ans[2*N]={0}, i, k, temp, n;
	
	gets(numStr1);
	gets(numStr2);
	
	int n1=strlen(numStr1);
	int n2=strlen(numStr2);
	
	/*We store the digits in revrse order so as to help during operations.*/
	k=0;
	for(i=n1-1; i>=0; i--){
		temp=numStr1[i]-48;
		num1[k++]=temp;
	}
	k=0;
	for(i=n2-1; i>=0; i--){
		temp=numStr2[i]-48;
		num2[k++]=temp;
	}
	
	//add();
	//sub();
	n=div1(num1, num2, n1, n2);
	
	printf("\n%d", n);
	
	return 0;
}


