#include<bits/stdc++.h>
using namespace std;
int main(){
	int n;
	cin>>n;

	int arr[n];

	for(int i=0;i<n;i++){
		cin>>arr[i];
	}

	int minn=arr[0], maxx=arr[0];
	for(int j=0;j<n;j++){
		
		if(arr[j]<minn){
			minn = arr[j];
		}
		if(arr[j]>maxx){
			maxx = arr[j];
		}
	}

	cout<<"Minimum Value: "<<minn;
	cout<<"\nMaximum Value: "<<maxx;



}