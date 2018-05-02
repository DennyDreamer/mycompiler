#include<iostream>
#include<string>
#include"parser.cc"
using namespace std;
int  main()
{
    lexer L("code.txt");

    L.codeProcess();
    LR_parse p(L.getToken(),"grammer.txt");
    return 0;
}
