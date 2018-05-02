#pragma
#include<vector>
#include<string>
using namespace std;
/*分隔符和单操作符的种别码定义为他们的anscii码*/
#define ID              256         /* 标识符起始标号*/
#define INT             257
#define REAL            258
#define CHAR            259
#define STRING          260
#define DOUBLEOPERATOR  261         /*符起始标号*/
#define KEYWORD         300         /*关键字起始*/
#define SIZE            50
static vector<string> keywordArray{"", "int" ,"char","float","bool","void","if","else","for","while","break","continue","return","include","do","switch","case","default"};
static vector<char> operatorArray{' ','+','-','*','/','!','>','<','='};
static vector<char> separationArray{' ','.','\'','\"','}','{','[',']',',',';','(',')','\\','#',':','&'};
static vector<string> doubleOperator{"",">=","<=","==","!=",">>","<<","++","--","&&","||"};


