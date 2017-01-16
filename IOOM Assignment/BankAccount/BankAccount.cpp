#include <iostream>
#include "BankAccount.h"
using namespace std;

int interest=5, minBalance=500, penalty=250;

void SavingsAccount::init(string accNum){
	string s;
	long int initialBalance;

	cout<<"Enter the name: ";
	cin>>s;
	name=s;

	acc_num=accNum;

	cout<<"Enter the initial money to be deposited: ";
	cin>>initialBalance;
	balance=initialBalance;

	cout<<"New Savings Account has been created!\n";
}

void SavingsAccount::deposit(){
	long int amnt;
	
	cout<<"enter the amount to be deposited: ";
	cin>>amnt;

	balance=(int)(balance*(100+interest)/100)+amnt;

	cout<<"New amount has been deposited & your current balance is "<<balance<<".\n";
}

void SavingsAccount::withdraw(){
	long int amnt;

	cout<<"Enter the amount to be withdraw: ";
	cin>>amnt;

	if(balance<minBalance)
		cout<<"Balance is less than "<<minBalance<<". Money can't be withdrawn.\n";
	else{
		balance=balance-amnt;
		if(balance<minBalance){
			balance=balance-penalty;
			cout<<"As the remaining balance is less than "<<minBalance<<" you have been imposed penalty of "<<penalty;	
		}
		cout<<"Amount withdrawn successfully. Current balance is "<<balance<<".";
	}	
}	

void SavingsAccount::display(){
	cout<<"Current balance left is "<<balance<<endl;
}

void CurrentAccount::init(string accNum){
	string s;
	long int initialBalance;

	cout<<"Enter the name: ";
	cin>>s;
	name=s;

	acc_num=accNum;

	cout<<"Enter the initial money to be deposited: ";
	cin>>initialBalance;
	balance=initialBalance;

	cout<<"New Current Account has been created!\n";
}

void CurrentAccount::deposit(){
	long int amnt;
	
	cout<<"enter the amount to be deposited: ";
	cin>>amnt;

	balance+=amnt;

	cout<<"New amount has been deposited & your current balance is "<<balance<<".\n";
}

void CurrentAccount::withdraw(){
	long int amnt;

	cout<<"Enter the amount to be withdraw: ";
	cin>>amnt;

	if(balance<minBalance)
		cout<<"Balance is less than "<<minBalance<<". Money can't be withdrawn.\n";
	else{
		balance=balance-amnt;
		if(balance<minBalance){
			balance=balance-penalty;
			cout<<"As the remaining balance is less than "<<minBalance<<" you have been imposed penalty of "<<penalty;	
		}
		cout<<"Amount withdrawn successfully. Current balance is "<<balance<<".";
	}
}

void CurrentAccount::display(){
	cout<<"Current balance left is "<<balance<<endl;
}
