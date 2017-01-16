#include <bits/stdc++.h>
#include "stockMarketClass.h"
using namespace std;

void stockMarketClass :: init(string s){
	companyName=s;
}
void stockMarketClass :: buyShare(){
	int numShares, pricePerShare;

	cout<<"Enter the number of shares you want to buy: ";
	cin>>numShares;

	numberOfShares.push(numShares);

	cout<<"Enter the price at which you purchased each share: ";
	cin>>pricePerShare;

	price.push(pricePerShare);

}

void stockMarketClass :: sellShare(){
	int numShares, pricePerShare;
	int net=0;
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
		
		
		
		if(numShares>shares){
			net+=(pricePerShare-price1)*shares;
		}
		else{
			net+=(pricePerShare-price1)*numShares;
			price.push(price1);
			numberOfShares.push(shares-numShares);
			cout<<"remaining shares: "<<numberOfShares.top()<<endl;
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

	
}
