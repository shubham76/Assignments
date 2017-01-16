#include <bits/stdc++.h>
using namespace std;

class Train{
	public:
		string trainName;
		long int trainNum;
		long int availableTkts;
		int price;
		string time;
		void trainInfo();
		bool availability(long int numTkt);
};

class Ticket{
	public:
		int ticketNum;
		bool isValid;
		long int trainNum;
		string startLoc;
		string destLoc;
		int numOfPass;
		void printTkt();
};

class TicketClerk{
	long balance;
	public:
		//void reserveTkt();
		TicketClerk();
		void cancelTkt(long, long);
		void receivePay(long);
		//void refundMoney();
};

class Passenger{
	public:
		string name;
		int age;
		string address;
		long int amntInWallet;
		Ticket hist[10];
		int index;
		void searchTrain(long int);//trin no,# of tickets
		void viewSch();
		void reserveTkt(long trnNum, long numOfTkt,string,string);
		//void availability(long int);//# of tickets from searchTrain()
		void cancelTkt(int, long);//ticket #
		bool makePay(long int);	
		long int viewBalance();		
};

