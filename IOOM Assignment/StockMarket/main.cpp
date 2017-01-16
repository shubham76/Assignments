#include <iostream>
#include <fstream>
#include "stockMarketClass.cpp"
using namespace std;

int main()
{
	int choice;
	int i=0, j, comanyNo;
	string s;
	int share_quan, sharePrice;
	map<string, int> m;
	stockMarket arr[100];

	int exit=0;

	ifstream infile;
	ofstream outfile;
	infile.open("a.txt");
	outfile.open("b.txt",ios_base::app);

	for(j=0;j<6;j++){
		infile>>s;

		infile>>share_quan;
		infile>>sharePrice;
		if(m.find(s) == m.end()){
			m[s]=i++;
			comanyNo=i-1;
			arr[comanyNo].initialise(s);
		}
		else{
			comanyNo=m[s];
		}
		arr[comanyNo].buyShare(share_quan,sharePrice);
		outfile<<"BUY"<<"\t";
		outfile<<s<<"\t";
		outfile<<share_quan<<"\t";
		outfile<<sharePrice<<endl;
	}

	infile.close();

	
	while(!exit){
		cout<<"Select your choice : "<<endl;
		cout<<"1. Buy Share"<<endl;
		cout<<"2. Sell Share"<<endl;
		cout<<"3. Exit"<<endl;
		cout<<"Enter your choice : ";
		cin>>choice;
		switch(choice){
			case 1 :
				cout<<"Enter the name of comany from which you want to buy shares : "<<endl;
				cin>>s;
				if(m.find(s) == m.end()){
					m[s]=i++;
					comanyNo=i-1;
					arr[comanyNo].initialise(s);
				}
				else{
					comanyNo=m[s];
				}
				arr[comanyNo].buyShare();
				
				break;
			
			case 2:
				cout<<"Enter the name of comany from which you want to buy shares : "<<endl;
				cin>>s;
				if(m.find(s) == m.end()){
					cout<<"The comany does not exist.\n";
				}
				else{
					comanyNo=m[s];
					arr[comanyNo].sellShare();
				}

				break;		
			
			case 3:
				exit=1;

				break;
		}
	}
	outfile.close();
	return 0;
}
