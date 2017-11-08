#include<iostream>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<sstream>
#include<cstring>
#include<map>
#include<list>
#include<queue>
#include<ctime>

using namespace std;
typedef struct {
	string arrangement;
	int cost;
}chromosome;

typedef vector<chromosome*> population;

population p;
int size=0;
int n=8;

int fitnessValue(string arrangement)
{
    int fitness=(n*(n-1))/2;        
    for(int i=0; i<n; i++)
        for(int j=i+1; j<n; j++)
            if((arrangement[i] == arrangement[j]) ||  (i-arrangement[i] == j-arrangement[j]) || (i+arrangement[i] == j+arrangement[j]))
                fitness--;
    return fitness;
} 
chromosome* createNode(){
	chromosome *newNode  = new chromosome;
    return newNode;
}
void generatePopulation()
{
    string sampleArrangement="";
    chromosome *temp;
    for(int i=1; i<=n; i++)
    {
        ostringstream ostr;
        ostr<<i;
        sampleArrangement += ostr.str();
    }
    //cout<<"sampleArrangement="<<sampleArrangement<<endl;
    for(int i=0; i<size; i++)
    {
        random_shuffle(sampleArrangement.begin(), sampleArrangement.end());
        temp   = createNode();
        temp->arrangement = sampleArrangement;
        temp->cost = fitnessValue(sampleArrangement);
        p.push_back(temp);
    }
}
chromosome* reproduce(chromosome *x,chromosome *y){
	chromosome* c1=createNode();
	int c=rand()%n;
	c1->arrangement = (x->arrangement).substr(0,c) + (y->arrangement).substr(c,n-c+1);
	c1->cost=fitnessValue(c1->arrangement);
	return c1;
}
chromosome* mutate(chromosome *t){
	int c=rand()%n;
	int x=rand()%n+1;
    t->arrangement[c]=x+48;
    t->cost=fitnessValue(t->arrangement);
    return t;
}
int random_population(){
	int x=rand()%p.size() %2;
	return x;
}
int isSolution(chromosome *t){
	if(t->cost==(((n-1)*n)/2)){
		return 1;
	}
	return 0;
}
bool comp(chromosome *a, chromosome*b)
{
    return(a->cost > b->cost);
}
chromosome* genetic_algorithm(){
	int count=1000000;
	
	population new_pol;
	while(count--){
		int p1,p2;
		sort(p.begin(),p.end(),comp);
		for(int i=0;i<size;i++){
			p1=random_population();
			chromosome *c1=p[p1];
			p2=random_population();
			chromosome *c2=p[p2];
			chromosome *new_chromo=reproduce(c1,c2);
			if(rand()%2==0)
			   new_chromo=mutate(new_chromo);
			if(isSolution(new_chromo)){ 	
			 	return new_chromo;
			}  
			new_pol.push_back(new_chromo);
	    }
	    p=new_pol;
	}
	sort(p.begin(),p.end(),comp);
	return p[0];
}
int main(){
	srand(2); 
	for(int i=0; i<3; i++){
		size=pow(10,i+1);
		cout<<size<<endl;
		generatePopulation();
		chromosome* ans=genetic_algorithm();
		if(isSolution(ans))
		   cout<<"The correct solution is "<<ans->arrangement<<endl;
		else
		   cout<<"The best solution found is "<<ans->arrangement<<endl;
	}
}
