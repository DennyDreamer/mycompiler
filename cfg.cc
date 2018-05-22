#include<iostream>
#include<vector>
#include<map>
#include<string>
#include<string.h>
#include"read.cc"
#include<set>
#include<algorithm>
/* @视为空*/
using namespace std;
typedef std::vector<string> a_production;
typedef vector<a_production> production;
typedef set<string>  first_set;
typedef std::set<string> follow_set;
class cfg
{
    public:
    private:
        bool has_null(string s);
        void read_cfg(string file);
        void first_compute();
        void follow_compute();
        void non_terminal_seek();
        void terminal_seek();
        first_set first_compute(string s);
    public:
        string start;
        set<string> T;
        void showC();
        bool is_non_terminal(string s);
        map<string,production> C;
        map<string,first_set> firstset;
        map<string,follow_set> followset;
        map<string,production>::iterator it;
        map<string,production>::iterator first_iter;
        set<string> non_terminal;
        set<string> terminal;
        first_set pro_first(a_production _ap);
        cfg(string file): C()
        {
            read_cfg(file);
            non_terminal_seek();
            terminal_seek();
            first_compute();
            cout<<"非终结符"<<endl;
            for(auto&n:non_terminal) cout<<n<<"00";
            cout<<endl<<"终结符"<<endl;
            for(auto&n:terminal) cout<<n<<"11";
            cout<<endl;
            cout<<"first集"<<endl;
            auto it=firstset.begin();
            while(it!=firstset.end())
            {
                std::cout<<it->first<<" "<<endl;
                auto iter=it->second.begin();
                while(iter!=it->second.end())
                {
                    cout<<*iter<<" ";
                    iter++;
                }
                cout<<endl;
                it++;
            }

        }
};
first_set cfg::pro_first(a_production _ap)
{
    first_set fs;
    auto index=_ap.begin();
    while(index!=_ap.end())
    {
        string s=*index;
        if(!is_non_terminal(*index))
        {
            fs.insert(s);
            return fs;
        }
        else
        {
            auto iter=firstset[s].begin();
            while(iter!=firstset[s].end())
            {
                if((*iter)!="@")
                    fs.insert(*iter);
                iter++;
            }
            if(!has_null(*index)) return fs;
        }
        index++;
    }
}
bool cfg::has_null(string s)
{
    if(is_non_terminal(s))
    {
        auto index=C[s].begin();
        while(index!=C[s].end())
        {
            if((*index)[0]=="@") return 1;
            else index++;
        }
        return 0;
    }
    return 0;
}

bool  cfg::is_non_terminal(string s)
{
    auto index=std::find(non_terminal.begin(),non_terminal.end(),s);
    //cout<<s<<"1111"<<endl;
    if(index==non_terminal.end()) return 0;
    else return 1;
}
void cfg::non_terminal_seek()
{
    it=C.begin();
    while(it!=C.end())
    {
        non_terminal.insert(it->first);
        it++;
    }
}
void cfg::terminal_seek()
{
    for(auto&n:C)
    {
        for(auto&m:n.second)
        {
            for(auto&p:m)
            {
                if(!is_non_terminal(p)&&p!="@") terminal.insert(p);
            }
        }
    }

}
void cfg::first_compute()
{
    it=C.begin();
    production::iterator iter;
    while(it!=C.end())
    {
        iter =(it->second).begin();
        while(iter!=(it->second).end())
        {
            if(!is_non_terminal((*iter)[0]))
            {
                firstset[it->first].insert((*iter)[0]);
            }
            iter++;
        }
        it++;
    }//ok

    it=C.begin();
    int k=0;
    int number=0;
    int size;
    string s1,s;
    while(true)
    {
        s=it->first;
        iter =(it->second).begin();
        while(iter!=(it->second).end())
        {
            for(unsigned long  i=0;i<(*iter).size();i++)
            {

                s1=(*iter)[i];
                if(is_non_terminal(s1))
                {
                    first_set::iterator iter2=firstset[s1].begin();
                    size=firstset[s].size();
                    while(iter2!=firstset[s1].end())
                    {
                        firstset[s].insert(*iter2);
                        iter2++;
                    }
                    if(size!=firstset[s].size()) number++;
                }
                else
                {
                    firstset[s].insert(s1);
                    break;
                }
                if(!has_null(s1)) break;
            }
            iter++;
        }
        k++;
        if(k==C.size())
        {
            if(number==0) break;
            else
            {
                k=0;
                number=0;
            }
        }
        it++;
        if(it==C.end()) it=C.begin();

    }


}
void cfg::follow_compute()
{

}
/* 读入文法*/
void cfg::read_cfg(string file)
{
    read r(file);
    start=r.getWord();
    r.next();
    //cout<<start<<endl;
    while(!r.isOver())
    {

        string s=r.getWord();
        string m=r.getWord();
        if(strcmp(m.c_str(),"->")!=0) return;
        T.insert(s);
        production* p=&C[s];
        a_production *ap=new vector<string>();
        while(!r.isOver()&&r.getNext()!='\0')
        {
            s=r.getWord();
            if(!strcmp(s.c_str(),";"))
            {
                r.nextLine();
                break;
            }
            else if(strcmp(s.c_str(),"->")==0) continue;
            else if(!strcmp(s.c_str(),"|"))
            {
                p->push_back(*ap);
                ap=new vector<string>();
            }
            else
            {
                if(!strcmp(s.c_str(),"\\;"))
                {

                    ap->push_back(";");
                    T.insert(";");
                }
                else ap->push_back(s);
                if(s!="@"&&s!="\\;")
                    T.insert(s);
            }

        }
        p->push_back(*ap);
    }
}
void cfg::showC()
{

    auto iter=C.begin();
    while(iter!=C.end())
    {
        auto iter2=(iter->second).begin();
        while(iter2!=(iter->second).end())
        {
            first_set fs=pro_first(*iter2);
            auto iter3=fs.begin();
            while(iter3!=fs.end())
            {
                cout<<*iter3;
                iter3++;
            }
            iter2++;
            cout<<endl;
        }
        iter++;
    }
}
void T()
{

}
/*测试*/
/*int main()
{
    cfg c("context.txt");
    cout<<c.start<<endl;
    auto iter4=c.T.begin();
    cout<<"符号合集"<<endl;
    while(iter4!=c.T.end())
    {
        cout<<*iter4<<" ";
        iter4++;
    }
    cout<<endl;
    cout<<"first集"<<endl;
    auto it=c.firstset.begin();
    while(it!=c.firstset.end())
    {
        std::cout<<it->first<<" "<<endl;
        auto iter=it->second.begin();
        while(iter!=it->second.end())
        {
            cout<<*iter<<" ";
            iter++;
        }
        cout<<endl;
        it++;
    }
    cout<<"产生式"<<endl;
    auto iter=c.C.begin();
    while(iter!=c.C.end())
    {
        cout<<iter->first<<"     dsfsf"<<endl;
        auto iter2=(iter->second).begin();
        while(iter2!=(iter->second).end())
        {
            first_set fs=c.pro_first(*iter2);
            auto iter3=fs.begin();
            while(iter3!=fs.end())
            {
                cout<<*iter3;
                iter3++;
            }
            iter2++;
            cout<<endl;
        }
        iter++;
    }
}*/
