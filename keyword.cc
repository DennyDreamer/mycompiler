#pragma once
#include<vector>
#include<string>
using namespace std;
/*分隔符和单操作符的种别码定义为他们的anscii码*/
//#define ID              256         /* 标识符起始标号*/
#define INT             ""
#define REAL            ""
#define CHAR            ""
#define STRING          ""
#define DOUBLEOPERATOR  ""/*符起始标号*/
#define KEYWORD         ""/*关键字起始*/
#define SIZE            ""
static vector<string> keywordArray{"","void","unsighed","double","short","long","int" ,"char","float","bool","void","if","else","for","while","break","continue","return","include","do","switch","case","default"};
static vector<char> operatorArray{' ','+','-','*','/','>','<','=','!','%',' ','.','\'','\"','}','{','[',']',',',';','(',')','\\','#',':','&','|'};
static vector<char> separationArray{' ','.','\'','\"','}','{','[',']',',',';','(',')','\\','#',':','&'};
static vector<string> doubleOperator{"","+=",">=","<=","==","!=",">>","<<","++","--","&&","||"};
