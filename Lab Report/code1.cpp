#include <bits/stdc++.h>

using namespace std;

int findSubstringIndex(const std::string& a, const std::string& b)
{
    int n = a.size();
    int m = b.size();

    for (int i = 0; i <= n - m; ++i)
    {
        bool found = true;
        for (int j = 0; j < m; ++j)
        {
            if (a[i + j] != b[j])
            {
                found = false;
                break;
            }
            if (j == m - 1 && i + m < n && a[i + m] != ' ')
            {
                found = false;
                break;
            }
        }
        if (found)
            return i+m; // Substring found, return ending index
    }
    return -1; // Substring not found, return -1
}

int nextword(string &line, int index)
{
    for(int i = index; i < line.size(); i++)
    {
        if(line[i]!=' ')return i;
    }
}
int main()
{
    ifstream file("sourcefile.txt");

    if (!file.is_open())
    {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    string line;

    string datatypes [] = {"int", "double", "float", "char"};
    vector<string>datatype;
    vector<string>variablename;
    vector<string>functionname;
    vector<string>constants;
    vector<char>punctuations;
    vector<char>operators;

    while (getline(file, line))
    {
        if(findSubstringIndex(line,"#include")>=0) continue;
        else if(findSubstringIndex(line,"using namespace")>=0)continue;
        else if(findSubstringIndex(line,"#define")>=0)continue;
        else if(line=="")continue;
        else
        {
            //Searching for variable declaration -----
            for(auto &substring : datatypes)
            {
                if(findSubstringIndex(line,substring)>=0)
                {
                    datatype.push_back(substring);

                    int ind = nextword(line, (findSubstringIndex(line,substring)));

                    string variable;

                    while((line[ind]>='a'&&line[ind]<='z') && line[ind]!=';')
                    {
                        variable.push_back(line[ind]);
                        ind++;
                    }
                    if(line[ind]=='(')
                    {
                        variable.push_back('(');
                        variable.push_back(')');
                        ind+=3;
                        functionname.push_back(variable);
                    }
                    else
                    {
                        variablename.push_back(variable);
                        ind = nextword(line, ind);
                        if(line[ind]=='=')
                        {
                            ind++;
                            ind = nextword(line, ind);
                            string constt;
                            while(line[ind]!=' ' && line[ind]!= ';'){constt.push_back(line[ind]);ind++;}
                            constants.push_back(constt);
                        }
                    }
                }
            }

            //Searching for punctuations
            string punctuation = ";(){}[]""'':";

            for(int i = 0; i < line.size(); i++)
            {
                if(findSubstringIndex(line,punctuation)>=0)punctuations.push_back(line[i-1]);
            }

            //Searching for Operators
            string operators[] = {"+","-","*","/","%","=","<<",">>","&","&&","||","!"};

            for(int i = 0; i < line.size(); i++)
            {
                for(auto &it : operators)
                {
                    if(findSubstringIndex(line, it)>=0)punctuations.push_back(line[i]);
                }
            }
        }
    }


    for(auto &it : datatype)
    {
        cout<<it<<endl;
    }
    for(auto &it : functionname)
    {
        cout<<it<<endl;
    }
    for(auto &it : variablename)
    {
        cout<<it<<endl;
    }
    for(auto &it : constants)
    {
        cout<<it<<endl;
    }
    for(auto &it : operators)
    {
        cout<<it<<endl;
    }
    file.close();

    return 0;
}

//---------------------------------------------------------------------------------------------------------------

while (getline(file, line))
    {
        istringstream iss(line);

        string word;
        vector<string>words;

        while(iss >> word)
        {
            words.push_back(word);
        }

        for(int i = 0; i < words.size(); i++)
        {
            if(words[i]=="#include" || words[i]=="using" || words[i]=="#define" || words[i].size()==0)
            {
                words.clear();
                break;
            }
            //Check Variable Declaration

            if(ischar(words[i][0]))
            {
                //Check Data-type or Variable
                bool datatypeflag = false;
                for(auto &datatype : datatypes)
                {
                    //if Datatype
                    if(datatype == words[i])
                    {

                        datatypeflag = true;
                        int sizee = words[i+1].size();

                        if(words[i+1][sizee-1] == ')')
                        {
                            words[i+1].pop_back();
                            words[i+1].pop_back();
                        }
                        auto isvalidvar = isvalidvariable(words[i+1]);

                        if(isvalidvar.first == true)
                        {
                            variables[words[i+1]]++;
                            i++;
                            break;
                        }
                        else
                        {
                            cout<<"****** Invalid Naming ******"<<endl<<endl;
                            cout<<isvalidvar.second<<": "<<words[i+1]<<endl;
                            return 0;

                        }
                    }
                }
                if(iskeywords(words[i]))break;

                if(variables[words[i]]>0)break;

                else if(!datatypeflag)
                {
                    cout<<"****** Undefined Element ******"<<endl<<endl;
                    cout<<words[i+1]<<endl;
                    return 0;
                }
            }
            else if(iskeywords(words[i]))continue;
        }
    }
    cout<<"No Error."<<endl;
