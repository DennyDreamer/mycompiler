#include<iostream>
#include<vector>
#include<stack>
#include"lexer.h"
#include"parse_table.cc"
#include<string>
#include<string.h>
#define PRODUCTION_SIZE 10
using namespace std;
string   getNonTerminal(string s)
{
    int i=1;
    string nonTerminal="";
    while(s[i]<'0' || s[i]>'9')
    {
        nonTerminal=nonTerminal+s[i];
        i++;
    }
    return nonTerminal;
}
int getNumber(string s)
{
    int i=1;
    string number="";

    while(s[i]<'0' || s[i]>'9'){i++;}
    while(s[i]>='0'&&s[i]<='9')
    {
        number=number+s[i];
        i++;
    }
    return atoi(number.c_str());
}
class LR_parse
{
    private:
        vector<token> tk;      /*token流*/
        vector<int>   state_stack;/* 状态栈*/
        vector<string> character;
        parse_table   pt;
        string action(int m,string s);
        int goto_(int m,int state);
        void parse();
        void show_spot();
    public:
        LR_parse(vector<token> _tk,string filename) ;
        ~LR_parse(){}
};
LR_parse::LR_parse(vector<token> _tk,string filename):pt(filename),state_stack(),character(),tk(_tk)
{
    state_stack.push_back(0);
    character.push_back("#");
    parse();
}
string  LR_parse::action(int m,string s)
{
    return pt.collection[m][s];
}
void LR_parse::show_spot()
{
    cout<<"状态栈"<<endl;
    for(auto&n:state_stack) cout<<n<<" ";
    cout<<endl;
    cout<<"符号栈"<<endl;
    for(auto&n:character) cout<<n<<" ";
    cout<<endl;
}
void LR_parse::parse()
{
    auto iter=tk.begin();
    int state,nextState;
    string str;
    string symbol=iter->value;
    string s;
    int m;
    while(true)
    {
        state=state_stack[state_stack.size()-1];
        cout<<"当前符号"<<symbol<<endl;
        str=action(state,symbol);
        if(str[0]=='r')
        {
             s=getNonTerminal(str);                 /*归约的非终结符*/
             m=getNumber(str);
             for(int i=0;i<m;i++)
             {
                state_stack.erase(state_stack.end()-1);         /*弹出当前状态*/
                character.erase(character.end()-1);
             }
             state=state_stack[state_stack.size()-1];   /*指向当前栈顶状态*/
             string K=action(state,s);
             state_stack.push_back(atoi(K.c_str()));
             character.push_back(s);
             show_spot();
             cout<<"归约为"<<s<<endl;
        }
        else if(str=="accept")
        {
            cout<<"accept"<<endl;
            break;
        }
        else if(str!="")
        {
            character.push_back(symbol);
            state_stack.push_back(atoi(str.c_str()));
            state=atoi(str.c_str());
            iter++;
            show_spot();
            cout<<"移入"<<endl;
        }
        else
        {
            cout<<str<<endl;
            cout<<state<<endl;
            cout<<"error"<<endl;
            break;
        }
        cout<<endl;
        if(iter==tk.end()) symbol="#";
        else symbol=iter->value;
    }
}

