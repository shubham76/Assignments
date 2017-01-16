#include <bits/stdc++.h>
#include <string>
#include <fstream>
#include <iostream>
#include <stdexcept>
using namespace std;

int main(){	

	map<string,int> wCnt;
	
	int n,i;
	cout<<"Enter the number of words you want to search: ";
	cin>>n;
	
	string s;
	cout<<"Enter the words you want to search : \n";
	for(i=0;i<n;i++){
		cin>>s;
		wCnt[s]=0;
	}
	
	try{
		ifstream f1;
		f1.open ("input.txt");
		string word;
		
		if(!f1.good()){
			throw runtime_error("Could not open file as the file doesn't exist");
		}
		else{
			try{
				while(1){
					f1>>word;
					if(wCnt.find(word)!=wCnt.end()){
							wCnt[word]++;
						}
					if(f1.eof())
						throw "File Read Complete.";
					else{
						continue;
					}
				}
			}
			catch(const char* s){
				cout<<s<<endl;
			}
			
		}
	}
	catch (exception &ex){
        cout << "Ouch! That hurts, because: "<< ex.what() << "!\n";
	}
	
	try{
		try{
			ofstream f2;
			f2.open("output.txt");
			
			if(f2==NULL){
				throw "IO Error.";
			}
			if(!f2.good()){
				throw runtime_error("Could not open file");
			}
			else{
				f2<<"Word"<<"\t"<<"Count"<<endl;
				for(map<string,int>::iterator it=wCnt.begin(); it!=wCnt.end(); it++){
					f2<<it->first<<"\t"<<it->second<<endl;
				}
			}
		}
		catch(const char *s){
			cout<<s<<endl;
		}
	}
	catch (exception &ex){
        cout << "Ouch! That hurts, because: "<< ex.what() << "!\n";
	}
	
}
