#include<iostream>
#include<string>
#include"semantic.cc"
using namespace std;
int  main()
{
    string code;
    string grammer;
    std::cin>>code>>grammer;
    lexer L(code);

    L.codeProcess();
    LR_parse p(L.getToken(),grammer);
    return 0;
}
