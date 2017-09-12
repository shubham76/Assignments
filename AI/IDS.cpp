#include <bits/stdc++.h>

#define N 3

using namespace std;

struct node{
	node * parent;
	int tile [N][N];
	int level;
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

void printTiles(int tile[N][N]){
	
	cout<<"---------------------------\n";

	for (int i = 0; i < N; ++i){
		for (int j = 0; j < N; ++j){
			cout<<tile[i][j]<<"\t";
		}
		cout<<endl;
	}

	cout<<"---------------------------\n";
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

node* makeNode(node* curr_head, int currX, int currY, int newX, int newY){
	int i,j,temp;

	node* new_node=(node*)malloc(sizeof(node));
	
	new_node->parent=curr_head;

	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			new_node->tile[i][j]=curr_head->tile[i][j];
		}
	}
	
	temp=new_node->tile[currX][currY];
	new_node->tile[currX][currY]=new_node->tile[newX][newY];
	new_node->tile[newX][newY]=temp;
	
	new_node->level=curr_head->level+1;

	return new_node;
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

void printPath(node *solutionNode){
	if(solutionNode==NULL){
		return;
	}

	printPath(solutionNode->parent);
	printTiles(solutionNode->tile);


}

int main(){
	node* head=(node*)malloc(sizeof(node));

	cout<<"Enter intial state: Put 0 for blank state.\n";

	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			int temp;
			cin>>temp;
			head->tile[i][j]=temp;
		}
	}
	/*cout<<"After taking input : \n";
	printTiles(head->tile);*/
	if(!areAllUnique(head->tile)){
		cout<<"All the values in tile must be unique.\n";
		exit(0);
	}
	if(!isSolvable(head->tile)){
		cout<<"The given  instance of puzzle is not solvable.\n";
		exit(0);
	}

	head->level=0;
	head->parent=NULL;

	int steps=0, currX,currY;
	for(int IDSLimits=0;;IDSLimits++){
		stack<node *> tree;

		tree.push(head);

		while(!tree.empty()){
			node* curr_head=tree.top();
			tree.pop();
			
			if(isFinalState(curr_head->tile)){
				cout<<"The solution is found!.\n";
				cout<<"The solution path is as follows.\n";
				printPath(curr_head);
				cout<<"The total number of steps required are "<<steps<<"."<<endl;
				exit(0);
			}
			else{
				if(curr_head->level < IDSLimits){
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
						printTiles(new_node->tile);
						tree.push(new_node);
					}
					if(currY-1>=0){
						steps++;
						node* new_node=makeNode(curr_head,currX,currY,currX,currY-1);
						printTiles(new_node->tile);
						tree.push(new_node);
					}
					if(currX+1<=2){
						steps++;
						node* new_node=makeNode(curr_head,currX,currY,currX+1,currY);
						printTiles(new_node->tile);
						tree.push(new_node);
					}
					if(currY+1<=2){
						steps++;
						node* new_node=makeNode(curr_head,currX,currY,currX,currY+1);
						printTiles(new_node->tile);
						tree.push(new_node);
					}
				}
			}
		}
	}
}