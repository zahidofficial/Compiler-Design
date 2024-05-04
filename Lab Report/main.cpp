#include <bits/stdc++.h>

using namespace std;

bool ischar(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool doubleoperators(string s)
{
    string operators[] = {"<<", ">>", "==", "&&", "||", "++", "+=", "-=", "*=", "/=", "!=", ">=", "<="};
    return find(begin(operators), end(operators), s) != end(operators);
}

bool ispunctuation(char c)
{
    string punctuations = ",.!;:'\"()[]{}&_/$#@|~^`";
    return punctuations.find(c) != string::npos;
}

bool isoperator(char c)
{
    string operators = "+-*/%=><&|!^?:.";
    return operators.find(c) != string::npos;
}

bool iskeyword(string s)
{
    string keywords[] =
    {
        "auto", "bool", "break", "case", "catch", "char", "class", "const",
        "continue", "default", "delete", "do", "double", "else", "enum", "explicit",
        "export", "extern", "false", "float", "for", "friend", "goto", "if", "inline",
        "int", "long", "mutable", "namespace", "new", "operator", "private", "protected",
        "public", "register", "return", "short", "signed", "sizeof", "static", "struct",
        "switch", "template", "this", "throw", "true", "try", "typedef", "typeid",
        "typename", "union", "unsigned", "using", "virtual", "void", "volatile", "while",
        "cout", "cin", "endl"
    };

    return find(begin(keywords), end(keywords), s) != end(keywords);
}

pair<bool,string> isvalidvariable(string s)
{
    string reason;

    if(iskeyword(s))
    {
        reason = "Variable name cannot be a keyword or object name.";
        return make_pair(false,reason);
    }
    for(int i = 0; i < s.size(); i++)
    {
        if(s[i]=='*' || s[i]=='+' || s[i]=='*' || s[i]=='/')
        {
            reason = "Operator Found in the variable name";
            return make_pair(false,reason);
        }
        else if(((s[i]>='A' && s[i] <= 'Z')==false && (s[i]>='a' && s[i]<='z')==false) &&
                ((s[i]>='0' && s[i] <= '9'))==false && s[i] != '_')
        {
            reason = "Special Character Found in the variable name";
            return make_pair(false,reason);
        }
    }
    if((s[0]>='a' && s[0] <= 'z')==false && (s[0]>='A' && s[0]<='Z')==false)
    {
        reason = "Digit in the front";
        return make_pair(false,reason);
    }
    else return make_pair(true,reason);
}

bool isconstant(const string& str)
{
    return (str[0] == '"' && str[str.size() - 1] == '"') || (str[0] == '\'' && str[str.size() - 1] == '\'') ||
           (all_of(str.begin(), str.end(), ::isdigit));
}

int main()
{
    ifstream file("sourcefile.txt");

    if (!file.is_open())
    {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    string datatypes [] = {"int", "double", "float", "char", "long", "short"};
    string line;
    map<string, int> variables;
    map<string, int> identifiermap;
    vector<string> keywords;
    vector<string> identifiers;
    vector<string> constants;
    vector<char> punctuations;
    vector<string> operators;

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
                            cout<<endl<<"****** Invalid Naming ******"<<endl<<endl;
                            cout<<"            "<<isvalidvar.second<<": "<<words[i+1]<<endl;
                            return 0;

                        }
                    }
                }
                if(iskeyword(words[i]))break;

                if(variables[words[i]]>0)break;

                else if(!datatypeflag)
                {
                    cout<<endl<<"****** Undefined Element ******"<<endl<<endl;
                    cout<<"            "<<words[i+1]<<endl;
                    return 0;
                }
            }
            else if(iskeyword(words[i]))continue;
        }
    }

    ifstream file2("sourcefile.txt");

    if (!file2.is_open())
    {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    while (getline(file2, line))
    {
        istringstream iss(line);
        string word;

        while (iss >> word)
        {
            if (word == "#include" || word == "using" || word == "#define" || word.size() == 0)
            {
                break;
            }

            if(word.back()==';')
            {
                punctuations.push_back(word.back());
                word.pop_back();
            }

            if (doubleoperators(word))
            {
                operators.push_back(word);
            }
            else if (iskeyword(word))
            {
                keywords.push_back(word);
            }
            else if (ischar(word[0]))
            {
                if(identifiermap[word]<1)
                {
                    identifiers.push_back(word);
                    identifiermap[word]++;
                    if(word.back() == ')')
                    {
                        punctuations.push_back(word[word.size()-2]);
                        punctuations.push_back(word.back());
                    }
                }

            }
            else if (isconstant(word))
            {
                constants.push_back(word);
            }
            else
            {
                for (char c : word)
                {
                    if (ispunctuation(c))
                    {
                        punctuations.push_back(c);
                    }
                    else if (isoperator(c))
                    {
                        string op(1, c);
                        operators.push_back(op);
                    }
                }
            }
        }
    }

    cout << left << setw(24) << "Constants" << setw(24) << "Identifiers" << setw(24) << "Keywords" << setw(26) << "Punctuations" << "Operators" << endl<<endl;

    for (size_t i = 0; i < max({constants.size(), identifiers.size(), keywords.size(), punctuations.size(), operators.size()}); ++i)
    {
        cout << left << setw(24) << (i < constants.size() ? constants[i] : "")
             << setw(24) << (i < identifiers.size() ? identifiers[i] : "")
             << setw(24) << (i < keywords.size() ? keywords[i] : "")
             << setw(26) << (i < punctuations.size() ? string(1, punctuations[i]) : "")
             << (i < operators.size() ? operators[i] : "") << endl;
    }

    getchar();
}

