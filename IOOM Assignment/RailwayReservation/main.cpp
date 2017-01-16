#include <bits/stdc++.h>
#include "RailwayReservation.cpp"
using namespace std;

int main(){
	ifstream fp("trainInput.txt");
	int idx=0;
	string s;
	long num;
	long amnt;
	string time;
	while(fp>>s>>num>>amnt>>time){
		trn[idx].trainName=s;
		trn[idx].trainNum=num;
		trn[idx].price=amnt;
		trn[idx].availableTkts=100;
		trn[idx].time=time;
		idx++;
		mp[num]=idx-1; 
	}
	
	idx=0;
	Passenger psg[100];
	map<string,int> mpPsg;
	int exit1=0, exit2=0;
	char ans;
	while(!exit1){
		cout<<"Welcome!\n";
		cout<<"Are you a new user?(y/n) ";
		cin>>ans;
		string name;
		if(ans=='Y' || ans=='y'){
			string addr;
			int age;
			long amnt;		
			cout<<"Enter your name: ";
			cin>>name;
			cout<<"Enter your address: ";
			cin>>addr;
			cout<<"Enter your age: ";
			cin>>age;
			cout<<"Enter the amount you want to add to your wallet: ";
			cin>>amnt;
			
			psg[idx].name=name;
			psg[idx].age=age;
			psg[idx].address=addr;
			psg[idx].amntInWallet=amnt;
			
			mpPsg[name]=idx;
			
			idx++;
		}
		else{
			cout<<"Enter your name: ";
			cin>>name;
			
			if(mpPsg.find(name)==mpPsg.end()){
				cout<<"This user does not exist.\n";
				continue;
			}
		}
		while(!exit2){
			int index=mpPsg[name];
			cout<<"Enter what you want to do\n";
			cout<<"1.Book a Ticket\n";
			cout<<"2.View Booked History\n";
			cout<<"3.Cancel a Ticket\n";
			cout<<"4.Check amount in your wallet\n";
			cout<<"5.Exit\n";
			int choice;
			cin>>choice;
			
			switch(choice){
				case 1:
					long num;
					cout<<"Enter the train number: ";
					cin>>num;
					psg[index].searchTrain(num);
					break;
				case 2:
					psg[index].viewSch();
					break;
				case 3:
					long tktNum, trnNum;
					cout<<"Enter your ticket number: ";
					cin>>tktNum;
					cout<<"Enter your train number: ";
					cin>>trnNum;
					psg[index].cancelTkt(tktNum,trnNum);
					break;
				case 5:
					exit2=0;
					cout<<"Logging out!\n";
					break;
				case 4:
					psg[index].viewBalance();
			}
			cout<<"You want to continue? (y/n) ";
			cin>>ans;
			if(ans=='n' || ans=='N')
				exit1=1;
		}
	}
	
	return 0;
}
