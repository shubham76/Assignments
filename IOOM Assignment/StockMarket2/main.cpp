#include <bits/stdc++.h>
#include "stockMarketClass.cpp"
using namespace std;

int main(int argc, char const *argv[])
{
	int choice;
	int i=0, companyId;
	string s;
	map<string, int> mp;
	stockMarketClass arr[100];

	int exit=0;

	while(!exit){
		cout<<"Select your choice : "<<endl;
		cout<<"1. Buy Share"<<endl;
		cout<<"2. Sell Share"<<endl;
		cout<<"3. Exit"<<endl;
		cout<<"Enter your choice : ";
		cin>>choice;
		switch(choice){
			case 1 :
				cout<<"Enter the name of company from which you want to buy shares : "<<endl;
				cin>>s;
				if(mp.find(s) == mp.end()){
					mp[s]=i++;
					companyId=i-1;
					arr[companyId].init(s);
				}
				else{
					companyId=mp[s];
				}
				arr[companyId].buyShare();
				
				break;
			
			case 2:
				cout<<"Enter the name of company from which you want to buy shares : "<<endl;
				cin>>s;
				if(mp.find(s) == mp.end()){
					cout<<"The company does not exist.\n";
				}
				else{
					companyId=mp[s];
					arr[companyId].sellShare();
				}

				break;		
			
			case 3:
				exit=1;

				break;
		}
	}
	return 0;
}
