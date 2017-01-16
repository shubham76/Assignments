#include <bits/stdc++.h>
#include "RailwayReservation.h"
using namespace std;

void Train::trainInfo(){
	cout<<"Train name: "<<trainName<<endl;
	cout<<"Train Number: "<<trainNum<<endl;
	cout<<"Available Tickets: "<<availableTkts<<endl;
	cout<<"Cost of each ticket: "<<price<<endl;
}

Train trn[100];
TicketClerk clerk;
map<long int,int> mp;

bool Train::availability(long int numTkt){
	if(numTkt<=availableTkts)
		return true;	
	else
		return false;
}

void Passenger::searchTrain(long int num){
	if(mp.find(num)!=mp.end()){
		int index=mp[num];
		trn[index].trainInfo();
		
		long int numTkt, totalCost;
		string strt,end;
		cout<<"Enter the number of tickets you want to book: ";
		cin>>numTkt;
		cout<<"Enter start location : ";
		cin>>strt;
		cout<<"Enter dest: ";
		cin>>end;
		totalCost=trn[index].price*numTkt;
		if(trn[index].availability(numTkt)){
			cout<<"The total cost is "<<trn[index].price*numTkt<<".\n";
			cout<<"Are you sure you want to book tickets and make payment? (y/n)"<<endl;
			char ans;
			cin>>ans;
			
			if(ans=='y' || ans=='Y'){
				if(makePay(totalCost)){
					cout<<"Your tickets have been booked.\n\n";
					reserveTkt(num,numTkt,strt,end);
				}
				else{
					cout<<"Your wallet doesn't have enough credit balance.\n";
					cout<<"Payment unsuccessful. Tickets could not be booked.\n\n";
				}
				
			}			
		}	
		else{
			cout<<"The requested number of tickets are not availble.\n\n";
		}
	}
	else{
		cout<<"This train does not exist.\n\n";
	}
}

void Passenger::viewSch(){	//to view booked history
	for(int i=0; i<index; i++){
		if(hist[i].isValid!=false)
			hist[i].printTkt();
	}
}

void Passenger::reserveTkt(long trnNum, long numOfTkt,string strt,string end){
	srand(time(NULL));
	hist[index].numOfPass=numOfTkt;
	hist[index].ticketNum=rand()%10000;
	hist[index].trainNum=trnNum;
	hist[index].isValid=true;
	hist[index].startLoc=strt;
	hist[index].destLoc=end;
	index++;
	
	int i=mp[trnNum];
	trn[i].availableTkts-=numOfTkt; 
	
	hist[index-1].printTkt();
}

bool Passenger::makePay(long totalCost){
	if(amntInWallet>=totalCost){
		amntInWallet-=totalCost;
		clerk.receivePay(totalCost);
		return true;
	}
	else{
		return false;
	}
}

void Passenger::cancelTkt(int tktNum, long trainNum){
	for(int i=0; i<index; i++){
//		cout<<"Hello  outside                l\n";
		if(hist[i].ticketNum==tktNum){
			hist[i].isValid=false;
			clerk.cancelTkt(trainNum, hist[i].numOfPass);
			amntInWallet+=hist[i].numOfPass*trn[mp[trainNum]].price;
//			cout<<"Hello                 l\n";
		}
	}
}

long int Passenger::viewBalance(){
	cout<<"Amount in your wallet is "<<amntInWallet<<endl;
}

void Ticket::printTkt(){
	cout<<"\n**************************\n";
	cout<<"Your ticket number is "<<ticketNum<<endl;
	cout<<"Your train is "<<trainNum<<endl;
	cout<<"Total number of passengers is "<<numOfPass<<endl;
	cout<<"Start location is "<<startLoc<<endl;
	cout<<"Dest is "<<destLoc<<endl;
	cout<<"Dep time from "<<startLoc<<" is "<<trn[mp[trainNum]].time<<endl;
	cout<<"**************************\n\n";
}

TicketClerk::TicketClerk(){
	balance=0;
}

void TicketClerk::cancelTkt(long trainNum, long numOfTkt){
	int index=mp[trainNum];
	trn[index].availableTkts+=numOfTkt;
	balance-=numOfTkt*trn[index].price;	 
	cout<<"Ticket cancellation successful\n\n";
}

void TicketClerk::receivePay(long amnt){
	balance+=amnt;
}

