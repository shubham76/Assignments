#include <iostream>
#include <stack>
using namespace std;

class stockMarket
{
private:
	string companyName;
	stack<int> numberOfShares;
	stack<int> price;
public:
	void initialise(string s);
	void buyShare(int share_quan,int price);
	void buyShare();
	void sellShare();	
};
