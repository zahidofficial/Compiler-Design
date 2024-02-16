#include <bits/stdc++.h>
using namespace std;

int commentType(string a){
        int n=a.length();
        if(a[0] == '/' && a[1] == '/'){
            return 1;
        }
        else if( a[0] == '/' && a[1] == '*' && a[n - 2] == '*' && a[n - 1] == '/'){
            return 2;
        }
        else {
        return 0;
    }
}

int main() {
    string a;
    cout<<"Enter a string: ";
    getline(cin,a);

    int n = a.length();
    int commentTypeResult = commentType(a);

    if(commentTypeResult ==1){
        cout<<"It's a single line comment"<<endl;
    }
    else if(commentTypeResult== 2){
        cout<<"It's a Multiple Line comment"<<endl;
    }
    else{
        cout<<"It's a Normal Line"<<endl;
    }

    return 0;
}
