#include<stdio.h>
#include<map>
#include<vector>
#include<string>
#include"cfg.cc"
#include<set>
/**/
using std::vector;
using std::string;
struct item
{
    /*
     * 增加一个数据结构用于寻找原产生式
     */

    string reduce;
    a_production pro;
    int index;
    string next;
    int cfg_index;
    string xu;
    item(string _reduce,a_production _pro,int _index,int _cfg_index,string _next)
    {

        reduce=_reduce;
         pro=_pro;
         index=_index;
         next=_next;
         cfg_index=_cfg_index;
         xu=reduce;
         for(auto &n:pro) xu=xu+n;
         xu=xu+next;
         xu=xu+std::to_string(cfg_index);
         xu=xu+std::to_string(index);
    }
    bool operator<(const item& _i) const
    {
        return xu<_i.xu;
    }
    bool operator==(const item& _i) const
    {
        if((this->reduce==_i.reduce)&&(this->pro==_i.pro)&&(this-> index==_i.index)&&(this->next==_i.next)&&(this->cfg_index==_i.cfg_index))
          return 1;
        else  return 0;
    }
};
typedef vector<item> I_set;
class parse_table : public  cfg
{
    private:
        typedef map<string,vector<int>> table;
    private:
        vector<I_set> iset_family;
        int  is_incol(I_set is);
        int  is_inIset(item _it,I_set is);
        bool conflict;
    public:
        parse_table(string filename):cfg(filename),iset_family(),collection(){
            conflict=0;
            items();
            //show();
        }
        map<int,map<string,string>> collection;
        void showC();
        ~parse_table(){}
        I_set GOTO(I_set _i,string X);
        I_set closure(I_set _i);
        void items();
        void show();
        void show_table();
        void showIset(I_set is);
        bool is_conflict(){return conflict;}
};
void parse_table::showIset(I_set is)
{

    for(auto& n:is)
    {
        cout<<n.reduce<<"->";
        for(auto&m:n.pro ) cout<<m<<" ";
        cout<<endl;
        cout<<"index="<<n.index<<"next="<<n.next<<endl;
    }
}


int parse_table::is_inIset(item _it,I_set is)
{
    for(unsigned long  i=0;i<is.size();i++)
    {
        if(is[i]==_it) return i;
    }
    return -1;
}
I_set parse_table::closure(I_set iset)
{
    for(unsigned long  i=0;i<iset.size();i++)
    {
        if(iset[i].pro.size()==static_cast<unsigned long>(iset[i].index)) continue;
        string symbol=iset[i].pro[iset[i].index];
        auto iter2=C[symbol].begin();
        a_production newpro((iset[i].pro.begin())+(iset[i].index+1),iset[i].pro.end());
        newpro.push_back(iset[i].next);
        first_set fs=pro_first(newpro);
        //while(iter2!=C[symbol].end())
        for (unsigned long i=0;i<C[symbol].size();i++)
        {
            auto iter3=fs.begin();
            while(iter3!=fs.end())
            {
                item _item(symbol,C[symbol][i],0,i,*iter3);
                if((*iter2)[0]=="@") _item.index=1;
                if(is_inIset(_item,iset)==-1)
                {
                    iset.push_back(_item);
                }
                iter3++;
            }
            iter2++;
        }
    }
    return iset;
}
I_set parse_table::GOTO(I_set _iset,string X)
{
    I_set iset;
    auto index=_iset.begin();
    while(index!=_iset.end())
    {
        item i=*index;
        if(i.pro.size()>static_cast<unsigned long> (i.index) && i.pro[i.index]==X) {
            i.index++;
            if(is_inIset(i,iset)==-1) iset.push_back(i);
        }
        index++;
    }
    iset=closure(iset);
    return iset;
}
int parse_table::is_incol(I_set is)
{
    for(unsigned long  i=0;i<iset_family.size();i++ )
    {
        if(is==iset_family[i]) return i;
    }
    return -1;
}
void parse_table::items()
{
    I_set I0;

   /* cout<<"T="<<endl;
    for(auto& n:T) cout<<n<<" ";
    cout<<endl;
    */

    a_production  ap{start};
    //cout<<start<<endl;
    production pm{ap};
    C["end"]=pm;
    item _i("end",ap,0,0,"#");
    I0.push_back(_i);
    I0=closure(I0);
    std::sort(I0.begin(),I0.end());
    iset_family.push_back(I0);
    int j;
    I_set is;
    for(unsigned long  i=0;i<iset_family.size();i++)
    {
        for(auto& n:T)
        {
            is=GOTO(iset_family[i],n);
            std::sort(is.begin(),is.end());
           /* cout<<"I"<<i<<endl;
            showIset(iset_family[i]);
            cout<<"新的"<<endl;
            showIset(is);*/
            if(!is.empty())
            {
                j=is_incol(is);
                if(collection[i][n]!="") conflict=1;
                if(j==-1)
                {
                    iset_family.push_back(is);
                    collection[i][n]+=std::to_string(iset_family.size()-1);
                }
                else
                    collection[i][n]+=std::to_string(j);
               // cout<<i<<"         "<<n<<"   "<< collection[i][n]<<endl;
            }
        }
    }
    for(unsigned long  i=0;i<iset_family.size();i++)
    {
        for(unsigned long  j=0;j<iset_family[i].size();j++)
        {
            item n=iset_family[i][j];
            if(static_cast<unsigned long >(n.index)==n.pro.size())
            {
                if(collection[i][n.next]!="") conflict=1;
                if(n.pro[0]==start&&n.pro.size()==1) collection[i][n.next]+="accept";
                else if(n.pro[0]=="@" && n.index==1) collection[i][n.next]+="r"+std::to_string(n.cfg_index)+n.reduce+"0";
                else collection[i][n.next]+="r"+std::to_string(n.cfg_index)+n.reduce+std::to_string(n.pro.size());
            }
        }
    }
}
void parse_table::show()
{
    for(unsigned long  i=0;i<iset_family.size();i++)
    {
        cout<<i<<endl;
        showIset(iset_family[i]);
    }

    cout<<"\t";
    for(auto &n:T)
    {
        cout<<n<<"\t";
    }
    cout<<"\n";
    /*for(auto &n:collection)
    {
        cout<<n.first<<"\t";
        for(auto &m:T)
        {
            cout<<n.second[m]<<"\t";
        }
        cout<<"\n";
    }*/

}
void parse_table::showC()
{

/*    auto iter=C.begin();
    while(iter!=C.end())
    {
        cout<<iter->first<<endl;
        auto iter2=(iter->second).begin();
        while(iter2!=(iter->second).end())
        {
            for(auto& n:*iter2) cout<<n<<" ";
            cout<<endl;
            iter2++;
        }
        iter++;
    }*/

}

/*int main()
{
    parse_table pt("context.txt");
   // pt.showC();
    pt.show();
    if(pt.is_conflict())
    {
        cout<<"冲突"<<endl;
    }
    else
    {
        cout<<"不冲突"<<endl;
    }



}*/

