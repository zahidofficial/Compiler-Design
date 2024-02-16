#include <bits/stdc++.h>
using namespace std;

bool checkop(string s){

    int op =1;
    string operators = "+-*/%=";

    for(int i=0;i<s.size();i++){
        for(int j=0;j<operators.size();j++){
            if(s[i] == operators[j] ){
                cout<<"Operator"<<i<<": "<<s[i]<<endl;
                op++;
            }
        }
    }

}

int main() {
    string s;
    cout<<"Enter any input: ";
    cin>>s;
    checkop(s);


    return 0;
}
