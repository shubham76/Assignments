#include <bits/stdc++.h>
using namespace std;

template <class T> class array{
	T *arr;
	int SIZE;
	public:
		array(int n){
			SIZE=n;
			arr=(T*)(malloc(n*sizeof(T)));
		}

		~array(){
			free(arr);
		}

		int getSize(){
			return SIZE;
		}

		T &operator[](int i){
		  	if(i>SIZE){
		      cout << "Index out of bounds" <<endl;
		      return arr[0];
		    }
		    return arr[i];
		}

		bool operator!=(array &A){
			if(SIZE!=A.SIZE)
				return false;
			
			int cnt=0;
			for(int i=0; i<SIZE; i++){
				if(arr[i]==A.arr[i])
					cnt++;
			}
			if(cnt==SIZE)
				return false;

			return true;
		}

		bool operator==(array &A){
			if(SIZE!=A.SIZE)
				return false;

			for(int i=0; i<SIZE; i++){
				if(arr[i]!=A.arr[i])
					return false;
			}

			return true;
		}

		
		array<T> &operator=(array &A){
			if(*this!=A){
				if(SIZE==A.getSize()){
					int n=SIZE;
					delete[] arr;
					arr=(T*)(malloc(n*sizeof(T)));
					for(int i=0; i<A.getSize(); i++){
						arr[i]=A.arr[i];
					}
					return *this;
				}
				else{
					std::cout << "The size of the left array is not equal to the right array." << std::endl;
				}
			}
		}
		template <typename U>
		friend ostream& operator<<(ostream& os, const array<U>& A);
		
		template <typename U>
		friend istream& operator>>(istream& os, const array<U>& A);
};

template <typename U>
ostream& operator<<(ostream& os, const array<U>& A){

	for(int i=0; i<A.SIZE; i++){
		os<<A.arr[i]<<"\t";
	}
	return os;
}

template <typename U>
istream& operator>>(istream& is, const array<U>& A){
	
	int n;
	cout<<"Enter the number of elements you want to input: ";
	is>>n;
	
	if(n<=A.SIZE){
		cout<<"Enter "<<n<<" elements continously:\n";
		for(int i=0; i<n; i++){
			is>>A.arr[i];
		}
	}
	else{
		cout<<"Size is more than capacity.\n";
	}
	return is;
}



int main(int argc, char const *argv[]) {
	int l;
	array<int> arr(2), ar(2);
	
	cin>>arr;
	cout<<arr;
	
	ar=arr;
	if(arr==ar){
		cout<<"Equal\n";
	}
	else if(arr!=ar){
		cout<<"Not Equal\n";
	}
	
	cout<<arr[10]<<endl;
	cout<<arr[0];

	return 0;
}
