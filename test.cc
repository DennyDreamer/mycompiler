#include<iostream>
#include<string>
#include"lexer.h"
using namespace std;
int  main()
{
    lexer L("token.h");
    L.codeProcess();
    return 0;
}
