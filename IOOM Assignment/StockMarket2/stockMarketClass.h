#include <iostream>
#include <stack>
using namespace std;

class stockMarketClass
{
private:
	string companyName;
	stack<int> numberOfShares;
	stack<int> price;
public:
	void init(string s);

	void buyShare();
	void sellShare();	
};