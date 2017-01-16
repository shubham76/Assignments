#include<bits/stdc++.h>
#include "BankAccount.cpp"

using namespace std;

int main(){
	int choice1, choice2, exit1=0, exit2=0, cntSav=0, cntCurr=0, tmp;
	string accNum;
	SavingsAccount sav[100];
	CurrentAccount curr[100];
	map<string, int> mpSav, mpCurr;


	while(!exit1){
		cout<<"******************************\n";
		cout<<"Select your choice : "<<endl;
		cout<<"1. Savings Account"<<endl;
		cout<<"2. Current Account"<<endl;
		cout<<"3. Exit"<<endl;
		cout<<"Enter your choice : ";
		cin>>choice1;
		exit2=0;
		switch(choice1){
			case 1:
				while(!exit2){
					cout<<"******************************\n";
					cout<<"Select your choice : "<<endl;
					cout<<"1. Create New Savings Account."<<endl;
					cout<<"2. Deposit money in your Savings Account."<<endl;
					cout<<"3. Withdraw money from your Savings Account."<<endl;
					cout<<"4. Display the balance."<<endl;
					cout<<"5. Return to the main menu."<<endl;
					cout<<"Enter your choice : ";
					cin>>choice2;
	
					if(choice2<4 && choice2!=1){
						cout<<"Enter the Account Number:";
						cin>>accNum;
	
						if(mpSav.find(accNum)==mpSav.end()){
							cout<<"The given Account does not exist!\n";
							exit2=1;
							break;
						}
						else{
							tmp=mpSav[accNum];
						}
					}
					switch(choice2){
					case 1:
						cout<<"enter the Account Number for new Account"<<endl;
						cin>>accNum;
						if(mpSav.find(accNum)==mpSav.end()){
							mpSav[accNum]=cntSav;
							tmp=cntSav++;
							sav[tmp].init(accNum);
						}
						else{
							cout<<"The given Account Number already exists.\n";
						}
						break;
					case 2:
						if(!exit2)
							sav[tmp].deposit();
						break;
					case 3:
						if(!exit2)
							sav[tmp].withdraw();
						break;
					case 4:
						if(!exit2)
							sav[tmp].display();
						break;
					case 5:
						exit2=1;
						break;
					}

				}
				break;

			case 2:
				while(!exit2){
					cout<<"******************************\n";
					cout<<"Select your choice : "<<endl;
					cout<<"1. Create New Savings Account."<<endl;
					cout<<"2. Deposit money in your Current Account."<<endl;
					cout<<"3. Withdraw money from your Current Account."<<endl;
					cout<<"4. Display the balance."<<endl;
					cout<<"5. Return to the main menu."<<endl;
					cout<<"Enter your choice : ";
					cin>>choice2;
	
					if(choice2<4 && choice2!=1){
						cout<<"Enter the Account Number:";
						cin>>accNum;
	
						if(mpCurr.find(accNum)==mpCurr.end()){
							cout<<"The given Account does not exist!\n";
							exit2=1;
							break;
						}
						else{
							tmp=mpCurr[accNum];
						}
					}
					switch(choice2){
					case 1:
						cout<<"enter he Account Number for new Account"<<endl;
						cin>>accNum;
						if(mpCurr.find(accNum)==mpCurr.end()){
							mpCurr[accNum]=cntCurr;
							tmp=cntCurr++;
							curr[tmp].init(accNum);
						}
						else{
							cout<<"The given Account Number already exists.\n";
						}
						break;
					case 2:
						if(!exit2)
							curr[tmp].deposit();
						break;
					case 3:
						if(!exit2)
							curr[tmp].withdraw();
						break;
					case 4:
						if(!exit2)
							curr[tmp].display();
						break;
					case 5:
						exit2=1;
						break;
					}
				}
				break;

			case 3:
				exit1=1;
				break;
		}
	}

}
