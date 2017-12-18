#include<iostream>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
using namespace std;

//存放处理后的字符串
char tempstr[255]={};
//空格标志
bool temp=false;
//临时数组
char word[255]={};
//keyword关键字

string keyword[8] = {
    "begin", "if", "then", "while", "do", "end"};
int keyword_num[8]={1,2,3,4,5,6};
//部分运算符，定界符等
char symbol[9]={'+','-','*','/','=',';','(',')','#'};
//对应的种码值
int symbol_num[9]={13,14,15,16,25,26,27,28,0};

//判断是否为字母
bool IsLetter(char ch)
{
    if((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z'))
        return true;
    return false;
}

//判断是否为数字
bool IsDigit(char ch)
{
    if(ch>='0'&&ch<='9')
        return true;
    return false;
}

//判断是否为定界符等
int IsSymbol(char ch)
{
    for(int i=0; i<9; i++)
    {
        if(ch==symbol[i])
        {
            return i;
        }
    }
    return -1;
}

//判断是否为关键字
int IsKeyword(string str)
{
    for(int i=0; i<6; i++)
    {
        if(str==keyword[i])
        {
            return i;
        }
    }
    //不是关键字即为ID
    return 10;
}

//空格处理
void HandleSpace(char a[])
{
    int j=0;
    memset(word,0,255);//需要清空，不然可能残留上次的字符串
    temp=false;
    for(int i=0; i<strlen(a); i++)
    {

        if(a[i]!=' ' && a[i]!='\t')
        {
            word[j++]=a[i];
            temp=false;
        }
        else
        {

            if(!temp&&a[i]!='\t')
            {
                word[j++]=a[i];
                temp=true;
            }

        }
    }
}

//处理"//"注释
void prePro()
{
    int j=0;
    memset(tempstr,0,255);
    for(int i=0; i<strlen(word); i++)
    {
        if(word[i]=='/'&&word[i+1]=='/')
        {
            while(i<strlen(word))
            {
                i++;
            }
        }
        else
        {
            tempstr[j++]=word[i];
        }
    }
}

int main()
{
    char instr[255]={}; //接收输入字符串
    bool flag=false; //多行注释标志,false为未处于注释区域
    string Token;//存放字符串
    char *str=NULL;//存放每行的字符串
    char delims[]=" ";//分割标志
    freopen("test.cpp","r",stdin);
    freopen("result.txt","w",stdout); //此行注释后，控制台输出，
    //否则文本输出
    while((gets(instr))!=NULL)
    {
        HandleSpace(instr);
        prePro();

        str=strtok(tempstr,delims);//分割字符串

        while(str!=NULL)
        {
            //头文件，宏定义
            if(*(str)=='#')
            {
                printf("#   0\n");
                break;
            }

            for(int i=0; i<strlen(str); i++)
            {
                if(*(str+i)=='/')
                {
                    if(*(str+i+1)=='*')
                    {
                        flag=true;
                        break;
                    }
                }
                //注释处理: */,注释区域结束
                if(*(str+i)=='*'&&flag)
                {
                    if(*(str+i+1)=='/')
                    {
                        flag=false;
                        i++;
                        break;
                    }
                }
                //标识符，关键词
              if(IsLetter(*(str+i))&&(!flag))
              {
                    ///printf("进入标识符判断\n");
                    while(IsLetter(*(str+i))||IsDigit(*(str+i))
                    ||*(str+i)=='_')
                    {
                        Token+=*(str+i);
                        i++;
                    }

                    if(IsKeyword(Token)!=10)
                    {
                        printf("%s   %d\n",Token.c_str(),
                        keyword_num[IsKeyword(Token)]);
                    }
                    else
                    {
                        printf("%s   10\n",Token.c_str());
                    }


                    Token="";
                  // printf("退出标识符判断\n");
                }
                if(IsDigit(*(str+i))&&(!flag))
                {
//                        printf("进入数字判断\n");
                    while(IsDigit(*(str+i)))
                    {
                        Token+=*(str+i);
                        i++;
                    }
                    printf("%s   11\n",Token.c_str());
                        Token="";
                }

                //<,<=,<>
                if(*(str+i)=='<'&&(!flag))
                {
                    if(*(str+i+1)=='=')    {printf("<=   22\n");i++;}
                    if(*(str+i+1)=='>')    {printf("<>   21\n");i++;}
                    else printf("<   20\n");
                }
                //>,>=
                else if(*(str+i)=='>'&&(!flag))
                {
                    if(*(str+i+1)=='=') {printf(">=   24\n"); i++;}
                    else printf(">   23\n");
                }
                //:,:=
                else  if(*(str+i)==':'&&(!flag))
                {
                    if(*(str+i+1)=='=') {printf(":=   18\n"); i++;}
                    else printf(":   17\n");
                }
                //余下定界符等
                else if(IsSymbol(*(str+i))!=-1&&(!flag))
                {
                    printf("%c   %d\n",*(str+i),
                            symbol_num[IsSymbol(*(str+i))]);
                }
            }
            str=strtok(NULL,delims);
        }
    }
    return 0;
}
