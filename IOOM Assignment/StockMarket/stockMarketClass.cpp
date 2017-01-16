#include <bits/stdc++.h>
#include "stockMarketClass.h"
using namespace std;

void stockMarket :: initialise(string s){
	companyName=s;
}
void stockMarket :: buyShare(){
	int numShares, pricePerShare;
	ofstream outfile;
	outfile.open("b.txt",ios_base::app);
	cout<<"Enter the number of shares you want to buy: ";
	cin>>numShares;

	numberOfShares.push(numShares);

	cout<<"Enter the price at which you purchased each share: ";
	cin>>pricePerShare;

	price.push(pricePerShare);
	outfile<<"BUY"<<"\t";
	outfile<<companyName<<"\t";
	outfile<<numShares<<"\t";
	outfile<<pricePerShare<<endl;
	
}

void stockMarket :: buyShare(int share_quan,int pricePerShare){

	numberOfShares.push(share_quan);

	price.push(pricePerShare);

}

void stockMarket :: sellShare(){
	int numShares, pricePerShare;
	int net=0,sharesSold=0;;
	
	ofstream outfile;
	outfile.open("b.txt",ios_base::app);
	
	
	cout<<"Enter the number of shares you want to sell: ";
	cin>>numShares;
	
	cout<<"Enter the price at which you want to sell each share: ";
	cin>>pricePerShare;

	while(!price.empty() && numShares>0){
		int shares;
		shares=numberOfShares.top();
		numberOfShares.pop();
		int price1=price.top();
		price.pop();



		if(numShares>=shares){
			net+=(pricePerShare-price1)*shares;
			sharesSold+=shares;
		}
		else if(numShares<shares){
			net+=(pricePerShare-price1)*numShares;
			price.push(price1);
			numberOfShares.push(shares-numShares);
			sharesSold+=shares;
		}

		numShares-=shares;
	}
	if(price.empty() && numShares>0){
		cout<<"you do not have the number of shares you wanted\n";
	}

	if(net>0){
		cout<<"You're profit is "<<net<<endl;
	}
	else if(net<0){
		cout<<"Sorry. You had a loss of "<<-1*net<<endl;
	}
	else{
		cout<<"No Profit. No Loss.\n";
	}

	outfile<<"SELL"<<"\t";
	outfile<<companyName<<"\t";
	outfile<<sharesSold<<"\t";
	outfile<<pricePerShare<<endl;
}
