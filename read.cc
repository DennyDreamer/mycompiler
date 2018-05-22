#ifndef COMPILER_READ
#define COMPILER_READ
#include<fstream>

#include<iostream>
#include<string>
#include<string.h>
using namespace std;
class read
{
private:
    int index;
    bool over;
    char getC(int _index)
    {
        if(s[_index]=='\0')
        {
            nextLine();
            return s[index];
        }
        return s[_index];
    }
public:
    string s;
    int row;
    int col;
    ifstream in;
    ofstream out;
    read(string _in,string _out="out.txt")
    {
        in.open(_in);
        if(getline(in,s)) over=0;
        else over=1;
        index=0;
        row=1;
        col=index+1;
    }
    void nextLine()
    {
        if(getline(in,s))
        {
            row++;
            index=0;
            col=1;
        }
        else over=1;
    }
    bool isOver(){return over;}
    char getC(){return getC(index);}
    char getNext(){return s[index+1];}
    void next(){index++;col++;}

    int getRow(){return row;}
    int getCol(){return col;}
    string getWord()
    {
        string ss;
        while(getC()==' '&&getC()!=EOF)
        {
            next();
        }
        while(getC()!=' ')
        {
            if(over)  return "";
            string s1(1,getC());
            ss=ss+s1;
            if(getNext()=='\0')
            {
                break;
            }
            else next();
        }
        return ss;
    }
    string readline()
    {
        string str=s;
        nextLine();
        return str;
    }
};
#endif
