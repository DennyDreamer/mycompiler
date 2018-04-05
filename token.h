#pragma
#include"lexer.h"
#include"keyword.cc"
#include<string>

void lexer::toToken(int tag,string  index)
{
    token *T=token(tag,index);
    tokenArray.push_back(T);
}
void lexer::numberProcess()
{
    number=0;
    char c=r.getC();
    string s=""+code[index];
    while(isNumber(c)||c=='.')
    {
        if(c=='.') number++;
        if(number>1) break;
        r.next();
    }
    if(number==1)
    {
        toToken(REAL,s);
    }
    else if(number ==0)
    {
        toToken(INT,s);
    }
}

void lexer::wordProcess()
{
    char c=r.getC();
    string s=""+c;
    while(isNumber(c)||isCharacter(c)||c=='_')
    {
        s=s+c;
        c=r.getC();
    }
    int _index=isKeyWord(s)
    if(!_index)
    {
        toToken(KEYWORD+_index,0);
    }
    else
    {
        toToken(ID,i);
    }
}
/*asfasfad*/
void lexer::operatorProcess()
{
    string s=""+r.getC()+r.getNext();
    bool type=0;
    for(int i=0;i<50;i++)
    {
        if(strcmp(s,doubleOperator[i])==0)
        {
            type=1;
            break;
        }
    }
    if(type)
    {
        toToken(DOUBLEOPERATOR+i,0);
    }
    else
    {
        toToken(r.getC(),0);
    }
}
void lexer::charProcess()
{
    r.next();
    if(r.getNext()=='')
      toToken(r.getC(),"0");
}
void lexer::stringProces()
{
	string s="";
    while(r.getC()!='\"')
	{
		s=s+r.getC();
		r.next();
	}
	toToken(STRING,s);
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
