#include<string>
#include<vector>
#include<bits/stdc++.h>
using std::vector;
using std::string;
using std::list;
using std::unordered_map;
string   getNonTerminal(string s)
{
    int i=1;
    string nonTerminal="";
    while(s[i]>='0' && s[i]<='9'){i++;}
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

    while(s[i]>='0' && s[i]<='9'){i++;}
    while(s[i]<'0' || s[i]>'9'){i++;}
    while(s[i]>='0'&&s[i]<='9')
    {
        number=number+s[i];
        i++;
    }
    return atoi(number.c_str());
}
int getCfg_index(string s)
{
    int i=1;
    string number="";
    while(s[i]>='0' && s[i]<='9') {
        number =number +s[i];
        i++;
    }
    return atoi(number.c_str());

}
class Code
{
public:
    string label;
    string code;
    Code()
    {
        label="    ";
        code="";
    }
    Code(string s)
    {
        label="    ";
        code=s;
    }
    Code& operator=(const Code& c)
    {
        label=c.label;
        code=c.code;
        return *this;
    }
};
class Symbol
{
public:
    int addr_;
    int width_;
    string type_;
    string value_;
    Symbol(int addr,string type,int width ,string value)
    {
        addr_=addr;
        type_=type;
        width_=width;
        value="";
    }
    Symbol()
    {
        addr_=0;
        width_=0;
        type_="";
        value_="";
    }
    void show() {
        cout<<"addr: "<<addr_<<" width_ "<<width_<<" type " <<type_<<" value_ "<<value_<<endl;
    }
};
class SymInfo
{
public:
    token  t;
    int    addr_;
    int    width_;
    list<Code> code_;
    string name_;
    string type_;
    string true_;
    string false_;
    string first_;
    string next_;
    string part_;
    SymInfo():t(),code_()
    {
        addr_=0;
        width_=0;
        name_="";
        type_="";
        true_="";
        false_="";
        first_="";
        next_="";
        part_="";
    }
    void show()
    {
        cout<<"addr: "<<addr_<<" width_ "<<width_<<" type " <<type_<<" name "<<name_<<endl;
        cout<<t.name;
        /* cout<<code_<<endl; */
    }

};

class LR_parse
{
    private:
        typedef unordered_map<string,Symbol> Symbol_table;
        typedef void (LR_parse::* fun)();
    private:
        vector<token> tk;      /*token流*/
        vector<int>   state_stack;/* 状态栈*/
        vector<SymInfo> symbol_stack;
        vector<string> character;
        parse_table   pt;
        vector<Symbol_table> symbol_table_vector;
        int current_table_index;//当前符号表索引
        Symbol_table current_table;
        int tempindexi_;
        int labelindex_;

        string action(int m,string s);
        int goto_(int m,int state);
        void parse();
        void show_spot();
        int offset_;


        map<string,fun> SDT;
    public:
        void call(string s)
        {
            (this->*SDT[s])();
        }
        LR_parse(vector<token> _tk,string filename)
              : tk(_tk),
                state_stack(),
                symbol_stack(),
                character(),
                pt(filename),
                symbol_table_vector(),
                SDT()
        {
            state_stack.push_back(0);
            character.push_back("#");
            Symbol_table st;
            symbol_table_vector.push_back(st);
            current_table=st;
            current_table_index=0;
            tempindexi_=0;
            labelindex_=0;

            SDT["S_1"]=&LR_parse::S_1;
            SDT["stmts_1"]=&LR_parse::stmts_1;
            SDT["stmts_2"]=&LR_parse::stmts_2;
            SDT["stmt_1"]=&LR_parse::stmt_1;
            SDT["stmt_2"]=&LR_parse::stmt_2;
            SDT["stmt_3"]=&LR_parse::stmt_3;
            SDT["block_stmt_1"]=&LR_parse::block_stmt_1;
            SDT["M_1"]=&LR_parse::M_1;
            SDT["define_stmt_1"]=&LR_parse::define_stmt_1;
            SDT["define_stmts_1"]=&LR_parse::define_stmts_1;
            SDT["define_stmts_2"]=&LR_parse::define_stmts_2;
            SDT["type_1"]=&LR_parse::type_1;
            SDT["type_2"]=&LR_parse::type_2;
            SDT["type_3"]=&LR_parse::type_3;
            SDT["type_4"]=&LR_parse::type_4;
            SDT["const_1"]=&LR_parse::const_1;
            SDT["const_2"]=&LR_parse::const_2;
            SDT["const_3"]=&LR_parse::const_3;
            SDT["factor_1"]=&LR_parse::factor_1;
            SDT["factor_2"]=&LR_parse::factor_2;
            SDT["factor_3"]=&LR_parse::factor_3;
            SDT["valueM_1"]=&LR_parse::value1_1;
            SDT["valueN_1"]=&LR_parse::value2_1;
            SDT["valueM__1"]=&LR_parse::value1__1;
            SDT["valueM__2"]=&LR_parse::value1__2;
            SDT["valueN__1"]=&LR_parse::value2__1;
            SDT["valueN__2"]=&LR_parse::value2__2;
            SDT["expression_1"]=&LR_parse::expression_1;
            SDT["operation_1"]=&LR_parse::operation_1;
            SDT["operation_2"]=&LR_parse::operation_2;
            SDT["opM_1"]=&LR_parse::op_1;
            SDT["opM_2"]=&LR_parse::op_1;
            SDT["opN_1"]=&LR_parse::op_1;
            SDT["opN_2"]=&LR_parse::op_1;
            SDT["assign_stmt_1"]=&LR_parse::assign_stmt_1;
            SDT["compare_op_1"]=&LR_parse::compare_op;
            SDT["compare_op_2"]=&LR_parse::compare_op;
            SDT["compare_op_3"]=&LR_parse::compare_op;
            SDT["compare_op_4"]=&LR_parse::compare_op;
            SDT["compare_op_5"]=&LR_parse::compare_op;
            SDT["compare_op_6"]=&LR_parse::compare_op;
            SDT["lop_1"]=&LR_parse::lop_1;
            SDT["lop_2"]=&LR_parse::lop_2;
            SDT["bool_expression_1"]=&LR_parse::bool_expression_1;
            SDT["bool_expression_2"]=&LR_parse::bool_expression_2;
            SDT["logical_expression_1"]=&LR_parse::logical_expression_1;
            SDT["logical_expression_2"]=&LR_parse::logical_expression_2;
            SDT["branch_stmt_1"]=&LR_parse::branch_stmt_1;
            SDT["result_1"]=&LR_parse::result_1;
            SDT["result_2"]=&LR_parse::result_2;
            SDT["iteration_stmt_1"]=&LR_parse::iteration_stmt_1;
            parse();
        }
        ~LR_parse(){}


        void S_1(){
            auto iter=symbol_stack.end()-1;
            cout<<endl;
            for (auto& n: iter->code_) cout<<n.label<<n.code<<endl;
        }

        void stmt_1(){}
        void stmt_2(){}
        void stmt_3(){}
        void stmts_1()
        {
            auto iter=symbol_stack.end()-1;
            (iter-1)->code_.splice((iter-1)->code_.end(),iter->code_);
            symbol_stack.erase(iter);
        }

        void stmts_2(){
            SymInfo si;
            symbol_stack.push_back(si);
        }

        void assign_stmt_1() {
            auto iter=symbol_stack.end()-1;
            SymInfo si;
            si.code_=(iter-1)->code_;
            Code code((iter-3)->t.name+"="+(iter-1)->name_);
            si.code_.push_back(code);

            symbol_stack.erase(symbol_stack.end()-1);
            symbol_stack.erase(symbol_stack.end()-1);
            symbol_stack.erase(symbol_stack.end()-1);
            symbol_stack.erase(symbol_stack.end()-1);
            symbol_stack.push_back(si);
            for (auto& n: si.code_) cout<<n.label<<n.code<<endl;

        }
        void define_stmts_1(){}
        void define_stmts_2(){}

        /*声明语句的翻译*/
        void type(string _type,int width)
        {
            auto iter=symbol_stack.end()-1;
            iter->type_=_type;
            iter->width_=width;
        }
        void M_1() {offset_=0;}
        void type_1() {type("int",4);}
        void type_2() {type("char",4);}
        void type_3() {type("float",4);}
        void type_4() {type("bool",4);}
        void define_stmt_1()
        {
            auto iter=symbol_stack.end()-1;
            SymInfo si;
            if(symbol_table_vector[current_table_index].count((iter-1)->t.name)==0)
            {
                Symbol symbol(offset_,(iter-1)->type_,(iter-1)->width_,iter->t.value);
                symbol_table_vector[current_table_index][iter->name_]=symbol;
                offset_=offset_+(iter-1)->width_;
                symbol_stack.erase(symbol_stack.end()-1);
                symbol_stack.erase(symbol_stack.end()-1);
                symbol_stack.erase(symbol_stack.end()-1);
                cout<<-3<<" 符号栈大小"<<symbol_stack.size()<<endl;
            }
            else {
                cout<<"error"<<endl;
                cout<<iter->t.name<<endl;

            }

        }
        /*表达式语句的翻译*/
        string newtemp() //得到新变量
        {
            string s("t");
            s=s+std::to_string(tempindexi_);
            if(current_table.count(s)==0)
            {
                Symbol symbol;
                symbol.addr_=offset_;
                offset_=offset_+4;
                current_table[s]=symbol;
                tempindexi_++;
            }
            else
            {
                tempindexi_++;
                return newtemp();
            }

            return s;
        }
        string newlabel()
        {
            string s("L");
            s=s+std::to_string(labelindex_);
            labelindex_++;
            return s;
        }
        void const_(string type,int width)
        {
            auto iter =symbol_stack.end() -1;
            SymInfo si;
            si.type_=type;
            si.width_=width;
            si.addr_=offset_;
            string v("const");
            Symbol symbol(offset_,v+"type",width,iter->t.value);
        }
        void const_1()
        {
            string _s("int");
            const_(_s,4);
        }
        void const_2()
        {

            string _s("char");
            const_(_s,4);
        }
        void const_3()
        {
            string _s("float");
            const_(_s,4);
        }
        void op_1(){}

        void value_(bool type)
        {
            auto iter = symbol_stack.end()-1;
            SymInfo si;
            string temp=newtemp();
            si.name_=temp;
            si.code_=iter->code_;
            si.code_.splice(si.code_.end(),(iter-1)->code_);
            if(type)
            {
                si.code_.push_back(temp+"="+(iter-1)->name_+iter->part_);
                si.part_=(iter-2)->t.value+temp;
                symbol_stack.erase(symbol_stack.end()-1);
            }
            else
            {
                si.code_.push_back(temp+"="+(iter-1)->name_+iter->part_);
            }
            si.name_=temp;
            cout<<endl;
            for (auto&n : si.code_) cout<<n.label<<n.code<<"\n"<<endl;
            symbol_stack.erase(symbol_stack.end()-1);
            symbol_stack.erase(symbol_stack.end()-1);
            symbol_stack.push_back(si);
        }
        void value2__1()  {value_(1);}
        void value2__2()
        {
            SymInfo si;
            symbol_stack.push_back(si);
        }
        void value2_1()   {value_(0);}
        void value1__1()  {value_(1);}
        void value1__2()
        {
            SymInfo si;
            symbol_stack.push_back(si);
        }
        void value1_1()   {value_(0);}
        void factor_1()
        {
            auto iter = symbol_stack.end()-1;
            SymInfo si;
            si.name_=iter->t.value;
            symbol_stack.erase(symbol_stack.end()-1);
            symbol_stack.push_back(si);
        }
        void factor_2()
        {
            auto iter =symbol_stack.end()-1;
            SymInfo si;
            si.name_=(iter-1)->name_;
            symbol_stack.erase(symbol_stack.end()-1);
            symbol_stack.erase(symbol_stack.end()-1);
            symbol_stack.erase(symbol_stack.end()-1);
            symbol_stack.push_back(si);
        }
        void factor_3()
       {
           auto iter=symbol_stack.end()-1;
           iter->name_=iter->t.name;
        }
        //布尔表达式的翻译
        void compare_op(){}

        void lop_1() {}
        void lop_2() {}

        void operation_1() {
            auto iter = symbol_stack.end()-1;
            SymInfo si;
            si.part_=(iter-1)->t.value+iter->name_;
            si.code_=iter->code_;
            symbol_stack.erase(symbol_stack.end()-1);
            symbol_stack.erase(symbol_stack.end()-1);
            symbol_stack.push_back(si);
        }
        void operation_2(){
            SymInfo si;
            symbol_stack.push_back(si);
        }

        void expression_1()
        {
            auto iter =symbol_stack.end()-1;
            SymInfo si;
            si.code_=(iter-1)->code_;
            si.code_.splice(si.code_.end(),iter->code_);
            string temp=newtemp();
            Code code(temp+"="+(iter-1)->name_+iter->part_);
            si.code_.push_back(code);
            si.name_=temp;
            symbol_stack.erase(symbol_stack.end()-1);
            symbol_stack.erase(symbol_stack.end()-1);
            symbol_stack.push_back(si);
        }
        void bool_expression_1() {value_(1);}
        void bool_expression_2()
        {
            SymInfo si;
            symbol_stack.push_back(si);
        }

        void logical_expression_1() {value_(0);}
        void logical_expression_2()
        {
            value_(0);
        }

        void branch_stmt_1()
        {
            auto iter=symbol_stack.end()-1;
            SymInfo si;
            si.code_=(iter-3)->code_;
            Code c1("if " + (iter-3)->name_+" goto " +(iter-1)->first_);
            si.code_.push_back(c1);
            Code c2("goto" + iter->first_);
            si.code_.push_back(c2);
            si.code_.splice(si.code_.end(),(iter-1)->code_);
            Code c3("goto" + iter->next_);
            if(!iter->code_.empty()) si.code_.push_back(c3);
            si.code_.splice(si.code_.end(),iter->code_);
            symbol_stack.erase(symbol_stack.end()-1);
            symbol_stack.erase(symbol_stack.end()-1);
            symbol_stack.erase(symbol_stack.end()-1);
            symbol_stack.erase(symbol_stack.end()-1);
            symbol_stack.erase(symbol_stack.end()-1);
            symbol_stack.erase(symbol_stack.end()-1);
            symbol_stack.push_back(si);
        }
        void result_1()
        {
            symbol_stack.erase(symbol_stack.end()-2);
        }
        void result_2() {}
        void iteration_stmt_1()
        {
            auto iter=symbol_stack.end()-1;
            SymInfo si;
            si.code_=(iter-5)->code_;
            si.code_.splice(si.code_.end(),(iter-2)->code_);
            Code c("if "+(iter-2)->name_+" goto " +(iter-5)->first_);
            si.code_.push_back(c);
            symbol_stack.erase(symbol_stack.end()-1);
            symbol_stack.erase(symbol_stack.end()-1);
            symbol_stack.erase(symbol_stack.end()-1);
            symbol_stack.erase(symbol_stack.end()-1);
            symbol_stack.erase(symbol_stack.end()-1);
            symbol_stack.erase(symbol_stack.end()-1);
            symbol_stack.erase(symbol_stack.end()-1);
            symbol_stack.push_back(si);
        }
        void block_stmt_1()
        {
            auto iter=symbol_stack.end()-1;
            SymInfo si;
            si.code_=(iter-1)->code_;
            string l1=newlabel();
            string l2=newlabel();
            Code c;
            c.label=l2;
            si.code_.push_back(c);
            c.label=l1;
            si.code_.push_front(c);
            si.first_=l1;
            si.next_=l2;
            symbol_stack.erase(symbol_stack.end()-1);
            symbol_stack.erase(symbol_stack.end()-1);
            symbol_stack.erase(symbol_stack.end()-1);
            symbol_stack.push_back(si);
        }



};
