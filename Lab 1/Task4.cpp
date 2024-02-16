#include<bits/stdc++.h>
using namespace std;

int main(){
	
	int fact=1;
	int n;
	cout<<"Enter a Number: ";
	cin>>n;

	if(n<0){
		cout<<"Invalid input";

	}
	else{
		for(int i=1;i<=n;i++){
		fact=fact*i;
		}
		cout<<"Factorial: "<<fact;
	}

	
}