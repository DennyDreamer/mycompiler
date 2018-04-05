
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

union tokenValue
{
	bool   type;
	char   ch;
	char*  st;
	int    in;
	float  fl;
	tokenValue(){;}
	tokenValue(char c){ ch=c; }
	tokenValue(char* s){st=s;}
	tokenValue(bool t){type=t;}
	tokenValue(int i){in=i;}
	tokenValue(float f){fl=f;}
	~tokenValue(){;}
};
struct token
{
	int     row;            /*行号*/
	int 	col;            /*列号*/
    int    tag;
    union tokenValue Value ;/*tag关键字时为0，tag为常数时为常数，tag为变量名时指向符号表入口*/
	string word;
	string type;
    token(int _tag,tokenValue _value,string _type,string _word)
    {
		word=_word;
        tag=_tag;
		Value.type=_value.type;
		Value.ch=_value.ch;
		Value.st=_value.st;
		Value.in=_value.in;
		Value.fl=_value.fl;
		type=_type;
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
    void toToken(int tag,union tokenValue,string _type,string word,int row,int col);
public:
   // vector<*property> fuhaobiao;
    lexer(string file):tokenArray(),r(file){}
	~lexer(){}
    vector<token>    tokenArray;
    void codeProcess();
};
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
    for(int i=1;i<keywordArray.size();i++)
    {
        if(!strcmp(s.c_str(),keywordArray[i].c_str())) return i;
    }
    return 0;

}
bool lexer::isOperator(char c)
{
    for (int i=0;i<operatorArray.size();i++)
    {
        if(operatorArray[i]==c) return 1;
	}
    return 0;
}

bool lexer::isSeparation(char c)
{
    for(int i=0;i<separationArray.size();i++)
    {
      if(separationArray[i]==c) return 1;
    }
    return 0;
}
/*判断字符类型*/

int  lexer::charKind()
{
	char c=r.getC();
    if(c==' ')              return 0;
    if(isNumber(c))         return 1;/*数字*/
    if(isCharacter(c))      return 2;/*字母*/
    if(isOperator(c))       return 3;
    if(c=='\"')              return 4;
    if(c=='\'')              return 5;
    if(c=='/'&&r.getNext()=='/')
							return 6;
	if(c=='/'&&r.getC()=='*')
							return 7;
    if(isSeparation(c))     return 8;/*运算符*/
}

void lexer::codeProcess()
{
	while(!r.isOver())
	{
		int k=charKind();
		switch(k)
		{
			case 0: r.next();           break;
			case 1: numberProcess();    break;
			case 2: wordProcess();      break;
			case 3: operatorProcess();  break;
			case 4: stringProcess();    break;
			case 5: charProcess();      break;
			case 6: noteProcess(1);     break;
			case 7: noteProcess(0);     break;
			case 8: separationProcess();break;
		}
	}

}


void lexer::toToken(int tag,union tokenValue t,string _type,string word,int row,int col)
{
    token T(tag,t,_type,word);
    tokenArray.push_back(T);
    cout<<row<<"  "<<col<<"  "<<tag<<" "<<word<<"               "<<_type<<endl;
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

		union tokenValue t(stof(s));
        toToken(REAL,t,"REAL",s,r.getRow(),r.getCol());
    }
    else if(number ==0)
    {
		union tokenValue t(stoi(s));
        toToken(INT,t,"INT",s,r.getRow(),r.getCol());
    }
}

void lexer::wordProcess()
{
    string s(1,r.getC());
	r.next();
	char c=r.getC();
    int _index;
	union tokenValue T((bool)0);
    while(isNumber(c)||isCharacter(c)||c=='_')
    {
        s=s+c;
		r.next();
        c=r.getC();
    }
	T.type=0;
	_index=isKeyWord(s);
    if(_index!=0)
    {
        toToken(KEYWORD+_index,T,"KEYWORD",s,r.getRow(),r.getCol());
    }
    else
    {
        toToken(ID,T,"ID",s,r.getRow(),r.getCol());
    }
}
/*处理单双运算符*/
void lexer::operatorProcess()
{
    string s1(1,r.getC());
	string s2(1,r.getNext());
	string s=s1+s2;
    bool type=0,m=0;
	int i=0;
	union tokenValue t(m);
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
        toToken(DOUBLEOPERATOR+i,t,"doubleOperatir",s,r.getRow(),r.getCol());
    }
    else
    {
		r.next();
        toToken(r.getC(),t,"operator",s1,r.getRow(),r.getCol());
    }

}
void lexer::charProcess()
{
    r.next();
	union tokenValue t(r.getC());
	string s(1,r.getC());
    if(r.getNext()==' ')
      toToken(r.getC(),t,"char",s,r.getRow(),r.getCol());
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
	union tokenValue t(s.c_str());
	r.next();
	toToken(STRING,t,"string",s,r.getRow(),r.getCol());
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
		while(r.getC()=='*' && r.getNext()=='/') r.next();
		r.next();
	}
}
void lexer::separationProcess()
{
	union tokenValue t((bool)0);
	string s(1,r.getC());
	toToken(r.getC(),t,"separation",s,r.getRow(),r.getCol());
	r.next();
}
