#include <bits/stdc++.h>
using namespace std;

int numericornot(string a){

    for(int i=0;i<a.length();i++)
        if(a[i]<0 || a[i]>9){
            return false;
        }
        else if(a[i]=='.'){
            return true;
        }
    }



int main() {
    string a;
    cout<<"Enter a value: ";
    cin>>a;
    //int numerictype = numericornot(a);

    if(numericornot(a)){
        cout<<"Not a numeric value";
    }
    else{
        cout<<"Numeric value";
    }

    return 0;
}
