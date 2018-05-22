#include<iostream>
#include<vector>
#include<stack>
#include"lexer.h"
#include"parse_table.cc"
#include<string>
#include"semantic.h"
#include<string.h>
#define PRODUCTION_SIZE 10
using namespace std;
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
    int state;
    string str;
    string symbol=iter->value;
    string s;
    int m;
    int cfg_index;
    while(true)
    {
        state=state_stack[state_stack.size()-1];
        cout<<"当前符号"<<symbol<<endl;
        str=action(state,symbol);
        if(str[0]=='r')
        {
             s=getNonTerminal(str);                 /*归约的非终结符*/
             m=getNumber(str);
             cfg_index=getCfg_index(str);
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
             cout<<"归约的产生式为"<<endl;
             cout <<s<<"->";
             for(auto&n:pt.C[s][cfg_index]) cout<<n<<" ";
             call(s+"_"+std::to_string(cfg_index+1));
             cout<<endl;
            cout<<"符号栈大小"<<symbol_stack.size()<<endl;
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
            SymInfo si;
            si.t=*iter;
            symbol_stack.push_back(si);
            cout<<1<<"符号栈大小"<<symbol_stack.size()<<endl;
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

