#include <iostream>
using namespace std;
/*
class BankAccount{
	public:
		virtual void init(string)=0;
		virtual void deposit()=0;
		virtual void withdraw()=0;
		virtual void display()=0;
};
*/
class SavingsAccount{
	string name;
	string acc_num;
	
	long int balance;

	public:
		void init(string);
		void deposit();
		void withdraw();
		void display();
};

class CurrentAccount{
	string name;
	string acc_num;
	
	long int balance;

	public:
		void init(string);
		void deposit();
		void withdraw();
		void display();
	
};
