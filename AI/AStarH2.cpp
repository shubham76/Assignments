#include <bits/stdc++.h>

using namespace std;

#define N 3

struct node{
	int tile [3][3];
	int fValue;
	int gValue;
	int hValue;
};

int getManhattanDistance(int tile[3][3]){
	int sum=0;
	int x_val[9]={0,0,0,1,1,1,2,2,2};
	int y_val[9]={0,1,2,0,1,2,0,1,2};
	int k=1,i,j;
	
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			if(tile[i][j]!=k && tile[i][j]!=0){
				sum=sum+abs(x_val[(tile[i][j])-1]-i)+abs(y_val[(tile[i][j])-1]-j);
			}
			k++;
			if(k==9){
				k=0;
			}
		}	
	}
	
	return sum;
}

struct compare{
    bool operator()(const node* a, const node* b){
		if(a->fValue > b->fValue){
			return 1;
		}
		else{
		    return 0;
	    }
    }
};

bool isSolvable(int tile[N][N]){
	int arr[9];
	int k=0;
	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			arr[k++]=tile[i][j];
		}
	}

	int invCount=0;

	for(int i=0;i<8;i++){
		for(int j=i+1;j<9;j++){
			if(arr[i]!=0 && arr[j]!=0 && arr[i]>arr[j]){
				invCount++;
			}
		}
	}

	if(invCount%2==1){
		return false;
	}
	else{
		return true;
	}
}

bool areAllUnique(int tile[N][N]){
	int hist[9]={0};

	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			hist[tile[i][j]]++;
		}
	}

	for(int i=0; i<9; i++){
		if(hist[i]==0 || hist[i]>1){
			return false;
		}
	}

	return true;
}

bool isFinalState(int tile[N][N]){
	int value=1;

	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			if(tile[i][j]==value){
				value++;
				if(value==9)
					return true;
			}
			else{
				return false;
			}
		}
	}
	return true;
}

node* makeNode(node* curr_head, int currX, int currY, int newX, int newY)
{
	int i,j,temp;

	node* new_node=(node*)malloc(sizeof(node));
	
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			new_node->tile[i][j]=curr_head->tile[i][j];
		}
	}
	
	temp=new_node->tile[currX][currY];
	new_node->tile[currX][currY]=new_node->tile[newX][newY];
	new_node->tile[newX][newY]=temp;
	
	new_node->gValue=curr_head->gValue+1;
	new_node->hValue=getManhattanDistance(new_node->tile);
	new_node->fValue=new_node->gValue+new_node->hValue;
	
	return new_node;
}

int main(int argc, char const *argv[])
{
	node* head=(node*)malloc(sizeof(node));

	cout<<"Enter intial state: Put 0 for blank state.\n";

	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			int temp;
			cin>>temp;
			head->tile[i][j]=temp;
		}
	}

	if(!areAllUnique(head->tile)){
		cout<<"All the values in tile must be unique.\n";
		exit(0);
	}
	if(!isSolvable(head->tile)){
		cout<<"The given  instance of puzzle is not solvable.\n";
		exit(0);
	}

	head->gValue=0;
	head->hValue=getManhattanDistance(head->tile);
	head->fValue=head->gValue+head->hValue;

	printf("hValue = %d\n",head->hValue);

	priority_queue<node *, vector<node *>, compare> tree;

	tree.push(head);

	int steps=0, currX, currY;
	while(!tree.empty()){
		node* curr_head=tree.top();
		tree.pop();

		if(isFinalState(curr_head->tile)){
			cout<<"The solution is found!.\n";
			cout<<"The total number of steps required are "<<steps<<"."<<endl;
			exit(0);
		}
		else{
			for(int i=0; i<N; i++){
				for(int j=0; j<N; j++){
					if(curr_head->tile[i][j]==0){
						currX=i, currY=j;
						break;
					}
				}
			}

			if(currX-1>=0){
				steps++;
				node* new_node=makeNode(curr_head,currX,currY,currX-1,currY);
				tree.push(new_node);
			}
			if(currY-1>=0){
				steps++;
				node* new_node=makeNode(curr_head,currX,currY,currX,currY-1);
				tree.push(new_node);
			}
			if(currX+1<=2){
				steps++;
				node* new_node=makeNode(curr_head,currX,currY,currX+1,currY);
				tree.push(new_node);
			}
			if(currY+1<=2){
				steps++;
				node* new_node=makeNode(curr_head,currX,currY,currX,currY+1);
				tree.push(new_node);
			}
		}
	}
	return 0;
}