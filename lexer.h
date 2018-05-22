
#include<iostream>
#include<vector>
#include<map>
#include<string>
#include<string.h>
#include"keyword.cc"
#include"read.cc"
/* 词法分析器
 * 词法分析器读入源码，输出token字的流*/

using namespace std;


/**字母表,单词表，用于检测读入字符**/
/*token*/
class token
{
public:
	int     row;            /*行号*/
	int 	col;            /*列号*/
    string 	name;
	string value;
    token(string _name,int _row,int _col,string _value)
    {
		row=_row;
		col=_col;
		value=_value;
        name=_name;
    }
	token()
	{
		row=0;
		col=0;
		value="";
		name="";
	}
	token& operator=(const token & t)
	{
		row=t.row;
		col=t.col;
		name=t.name;
		value=t.value;
		return *this;
	}
};


/*符号表元素
struct property
{
    int type;
    int name;
    string value;
};
*/

/*词法分析类*/
class lexer
{
private:
	read r;
    static bool isNumber(char c);    /*判断是否时数字*/
    static bool isCharacter(char c); /*判断是否是字母*/
    static bool isOperator(char c);  /*判断是否是字符*/
    static bool isSeparation(char c);/*判断是否是分界符*/
    static int  isKeyWord(string s);
private:
    int charKind();
	void numberProcess();
	void wordProcess();
	void operatorProcess();
	void stringProcess();
	void charProcess();
	void separationProcess();
	void noteProcess(bool type);
	void toToken(string name,string _type,string word,int row,int col);
public:
   // vector<*property> fuhaobiao;
    lexer(string file):tokenArray(),r(file),ID_list(){}
	~lexer(){}
    vector<token>    tokenArray;
	vector<string>   ID_list;
    void codeProcess();
	vector<token> getToken();
};
vector<token> lexer::getToken(){return tokenArray;}
bool lexer::isCharacter(char c)
{
    if((c>='a'&& c<='z')||(c>='A'&&c<='Z')||c=='_') return 1;
    else return 0;
}

bool lexer::isNumber(char c)
{
    if (c>='0'&&c<='9') return 1;
    else return 0;
}
int lexer::isKeyWord(string s)
{
    for(size_t i=1;i<keywordArray.size();i++)
    {
        if(!strcmp(s.c_str(),keywordArray[i].c_str())) return i;
    }
    return 0;

}
bool lexer::isOperator(char c)
{
    for (size_t i=0;i<operatorArray.size();i++)
    {
        if(operatorArray[i]==c) return 1;
	}
    return 0;
}

bool lexer::isSeparation(char c)
{

    for(size_t i=0;i<separationArray.size();i++)
    {
      if(separationArray[i]==c) return 1;
    }
    return 0;
}
/*判断字符类型*/


void lexer::codeProcess()
{
	while(!r.isOver())
	{
		char c=r.getC();
		if(c==' '||c=='\t')          r.next();
		else if(isNumber(c))         numberProcess();
		else if(isCharacter(c))      wordProcess();
		else if(c=='\"')    stringProcess();
		else if(c=='\'')    charProcess();
		else if(c=='/'&&r.getNext()=='/')
									 noteProcess(1);
		else if(c=='/'&&r.getNext()=='*')
									 noteProcess(0);
		else if(isOperator(c))       operatorProcess();
		else if(isSeparation(c))     separationProcess();
	}

}
void lexer::toToken(string  name,string _type,string word,int row,int col)
{
    token T(name,row,col,word);
    tokenArray.push_back(T);
    cout<<row<<"  "<<col<<"  "<<name<<" "<<word<<"               "<<_type<<endl;
}
void lexer::numberProcess()
{
    int number=0;
    char c=r.getC();
    string s="";
    while(isNumber(c)||c=='.')
    {
        if(c=='.') number++;
        if(number>1) break;
		s=s+r.getC();
		cout<<s<<endl;
		r.next();
		c=r.getC();
    }
    if(number==1)
    {

        toToken(REAL,"REAL","REAL",r.getRow(),r.getCol());
    }
    else if(number ==0)
    {
        toToken(INT,"INT","INT",r.getRow(),r.getCol());
    }
}

void lexer::wordProcess()
{
    string s(1,r.getC());
	r.next();
	char c=r.getC();
    int _index;
    while(isNumber(c)||isCharacter(c)||c=='_')
    {
        s=s+c;
		r.next();
        c=r.getC();
    }
	_index=isKeyWord(s);
    if(_index!=0)
    {
        toToken(KEYWORD,"KEYWORD",s,r.getRow(),r.getCol());
    }
    else
    {
		auto  iter=ID_list.begin();
		int i=0;
		while(iter!=ID_list.end())
		{
			if((*iter)==s) break;
			i++;
			iter++;
		}
        toToken(s,"ID","IDN",r.getRow(),r.getCol());
		ID_list.push_back(s);
    }
}
/*处理单双运算符*/
void lexer::operatorProcess()
{
    string s1(1,r.getC());
	string s2(1,r.getNext());
	string s=s1+s2;
    bool type=0;
	unsigned long  i=0;
    for(i=0;i<doubleOperator.size();i++)
    {

        if(strcmp(s.c_str(),doubleOperator[i].c_str())==0)
        {
            type=1;
            break;
        }
	}
    if(type)
    {
		r.next();
		r.next();
        toToken(DOUBLEOPERATOR,"doubleOperatir",s,r.getRow(),r.getCol());
    }
    else
    {
        toToken("","operator",s1,r.getRow(),r.getCol());
		r.next();
    }

}
void lexer::charProcess()
{
    r.next();
	string s="";
	while(r.getC()!='\'')
	{
		string s1(1,r.getC());
		s=s+s1;
		r.next();
	}
	r.next();
	toToken(CHAR,"char","CHAR",r.getRow(),r.getCol());
}
void lexer::stringProcess()
{
	string s="";
	r.next();
    while(r.getC()!='"')
	{
		string s1(1,r.getC());
		s=s+r.getC();
		r.next();
	}
	r.next();
	toToken(STRING,"string",s,r.getRow(),r.getCol());
}
/*处理注释 type=1表示此行注释
 * type=0表示大段注释*/
void lexer::noteProcess(bool type)
{
	if(type)
	{
		r.nextLine();
		return ;
	}
	else
	{
		while(r.getC()!='*' || r.getNext()!='/')
		{
			r.next();
		}
		r.next();
		r.next();
	}
}
void lexer::separationProcess()
{
	string s(1,r.getC());
	toToken("","separation",s,r.getRow(),r.getCol());
	r.next();
}
