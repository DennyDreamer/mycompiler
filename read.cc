#pragma
#include<fstream>
#include<iostream>
#include<string>
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
            if(getline(in,s))
            {
                row++;
                index=0;
                col=1;

                return getC();
            }
            else over=1;
        }
        else return s[_index];
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
        getline(in,s);
        index=0;
    }
    bool isOver(){return over;}
    char getC(){return getC(index);}
    char getNext(){return s[index+1];}
    void next(){index++;col++;}

    int getRow(){return row;}
    int getCol(){return col;}
};

