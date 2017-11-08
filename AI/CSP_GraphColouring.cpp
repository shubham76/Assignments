#include<iostream>
#include<stdlib.h>
#include<vector>
#include<algorithm>
 
using namespace std;
int graph[200][200];
void GenerateRandGraphs(int NOE, int NOV){
	int i, j, edge[NOE][2], count;
	i = 0;
	while(i < NOE){
		edge[i][0] = rand()%NOV+1;
		edge[i][1] = rand()%NOV+1;
        if(edge[i][0] == edge[i][1])
			continue;
		else{
			for(j = 0; j < i; j++){
				if((edge[i][0] == edge[j][0] && edge[i][1] == edge[j][1]) || (edge[i][0] == edge[j][1] && edge[i][1] == edge[j][0]))
					i--;
			}
		}
		i++;
	}
    for(i = 0; i < NOV; i++){
		count = 0;
		for(j = 0; j < NOE; j++){
			if(edge[j][0] == i+1){
				graph[i][edge[j][1]-1]=1;
			}
			else if(edge[j][1] == i+1)
			{
			    graph[i][edge[j][0]-1]=1;	
			}
			
		}
		
	}	
}
typedef struct {
	int vertex;
	vector<int> edges;
	vector<int> domain;
	int count;
}node;
vector<node *> graph_struct;
vector<node *> graph_struct1;
bool comp(const node*a,const node*b){
	return(a->domain.size()<b->domain.size());
}
bool comp1(const node*a,const node*b){
	return(a->edges.size()>b->edges.size());
}
int color[200]={0};
int chose_next(){
	int i=0;
		vector<node *>::iterator it;
		for(it=graph_struct.begin();it!=graph_struct.end();it++){
			int a=(*it)->vertex;
			//cout<<" "<<a;
			if(color[a]==0)
			   return a;
		}
	return 0;
}
int ifpossible(int x,node *n){
	vector<int>::iterator it;
		for(it=n->edges.begin();it!=n->edges.end();it++){
			int b=*it;
			//cout<<b;
			if(color[b]==0){
				vector<node *> ::iterator n1;
			
				for(n1=graph_struct.begin();n1!=graph_struct.end();n1++){
					if((*n1)->vertex==b){
						vector<int>::iterator position = find((*n1)->domain.begin(), (*n1)->domain.end(), x);
                        if (position != (*n1)->domain.end() && (*n1)->domain.size()<2)
							return 0;
                             
                                     
						}
					}
			}
			
		}
	return 1;
}

int graph_coloring(int t,int v){
	int a;
	if(t==v){
		cout<<"Graph colored . Possible solution can be: ";
		for(int i=0;i<v;i++)
		   cout<<color[i]<<" ";
		cout<<"\n";
	    return 1;
	}
	else{
		a=chose_next();
		node *n;
		vector<node *> ::iterator n1;
		
		for(n1=graph_struct.begin();n1!=graph_struct.end();n1++){
			if((*n1)->vertex==a){
				n=*n1;
			}
		}

		vector<int>::iterator it;
		for(it=n->domain.begin();it!=n->domain.end();it++){
			if(ifpossible(*it,n)){
				color[n->vertex]=*it;int d=*it;
				vector<int>::iterator it1;

				for(it1=n->edges.begin();it1!=n->edges.end();it1++){
					int b=*it1;
					vector<node *> ::iterator n1;
					for(n1=graph_struct.begin();n1!=graph_struct.end();n1++){
						if((*n1)->vertex==b){
							vector<int>::iterator position = find((*n1)->domain.begin(), (*n1)->domain.end(), d);
                             if (position != (*n1)->domain.end())
                                       (*n1)->domain.erase(position);
						}
					}
				
				}
				sort(graph_struct.begin(),graph_struct.end(),comp);
				if(graph_coloring(t+1,v)==1)
				   return 1;
			}
		}
	}
      return 0;
}
int main()
{
	int n, i, e, v,c;
 
	cout<<"Random graph generation: ";
    cout<<"\nEnter number of vertex";
    cin>>v;

    e=((v*(v-1))/2);
  	GenerateRandGraphs(e, v);
  	
  	cout<<"\n Enter number of colors\n";
	cin>>c;
  	
  	cout<<"\nThe generated random graph is: \n";
  	
  	for(i=0;i<v;i++){
  		node *n=new node;
  		n->vertex=i;
  		for(int j=0;j<v;j++){
  			if(graph[i][j])
  			n->edges.push_back(j);
  			cout<<graph[i][j]<<" ";
		  }
		  cout<<endl;
		  for(int k=1;k<=c;k++)
		     n->domain.push_back(k);
	      graph_struct.push_back(n);
	      graph_struct1.push_back(n);
	      
	  }
	  
	  sort(graph_struct.begin(),graph_struct.end(),comp1);
	  
	  if(!graph_coloring(0,v)){
	  	cout<<"Solution does not exist!\n";
	  }
}
