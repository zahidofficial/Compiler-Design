#include<bits/stdc++.h>
using namespace std;

int main(){
	
	int n;
	cout<<"Enter the size of the array: ";
	cin>>n;
	float arr[n];


	
	for(int i=0;i<n;i++){
		cin>>arr[i];
	}
	float sum =0;
	for(int j=0;j<n;j++){
		sum = sum+arr[j];
	}
	float avg = sum/n;
	cout<<"\nAverage value of the elements are: "<<avg;

}