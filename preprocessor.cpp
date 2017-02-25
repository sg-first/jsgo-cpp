#include "preprocessor.h"

String preprocessor::PCodeFile(String codepath)
{
    String code=aLib->ReadTXT(codepath);
    String newcode="";
    QStringList ary=code.split("\r\n");

    for(String i:ary)
    {
        newcode+=prepro(i,newcode)+"\r\n"; //一次处理一句
    }
    return newcode;
}

String preprocessor::prepro(String str,String &newcode)
{
    deleteComment(str);
    deleteSpace(str);

    if(str.indexOf("#require ")!=-1) //本句含有require语句
    {
        QStringList requireList=str.split("#require ");
        if(requireList[0]!="") //require前面没有任何字符，如果有就拒绝（看看这个分割一样不一样）
        {
            aLib->output("Unrecognized #require statement");
            return "";
        }
        //没有问题，开始处理被require的代码文本
        return preprocessor::PCodeFile(requireList[1]); //递归解析require的代码文本，直接返回解析后的结果
    }

    if(str.indexOf("#define ")!=-1) //本句含有define语句
    {
        QStringList defineList=str.split("#define ");
        if(defineList[0]!="") //define前面没有任何字符，如果有就拒绝（看看这个分割一样不一样）
        {
            aLib->output("Unrecognized #define statement");
            return "";
        }
        defineList=defineList[1].split(" ");
        newcode.replace(defineList[0],defineList[1]);
        return "";
    }

    return str; //什么都没有，原样返回
}

void findAndDelete(String &str,String findcontext,bool front=true)
{
    int pos=str.indexOf(findcontext);

    if(pos==-1)
    {return;}

    if(front)
    {
        str=str.left(pos);
        return;
    }
    else
    {
        str=str.right(str.length()-pos-findcontext.length());
        return;
    }
}

void preprocessor::deleteComment(String &str)
{
    findAndDelete(str,"//"); //处理双斜杠注释
    //处理区段注释
    //准备工作
    const String CL="/*";
    const String CR="*/";
    //处理CL
    int posLeft=str.indexOf(CL);
    if(posLeft==-1) //没有注释
    {return;}
    String commentLight=str.right(str.length()-posLeft-CL.length());
    //处理CR
    int posRight=str.indexOf(CR);
    String str2=""; //注释结束后的字符
    if(posRight!=-1) //存在就有后边，否则就前边一段
    {str2=commentLight.right(commentLight.length()-posRight-CR.length());}
    //处理完成，最后拼接
    str=str.left(posLeft); //注释结束前的字符
    str+=str2; //前后拼装
}

void preprocessor::deleteSpace(String &str)
{
    bool isSpace=false;
    bool isQuotes=false;
    String newstr="";

    for(auto i:str)
    {
        if(isQuotes) //前一个字符是引号
        {
            if(i=='"') //这个字符是反引号，出状态
                isQuotes=false;
            newstr+=i; //无论是否是反引号，这个字符都不会被去除
            continue;
        }
        //前一个不是引号就先检查这个是不是引号
        if(i=='"')
        {
            isQuotes=true; //进状态
            newstr+=i;
            continue;
        }
        //确定跟引号没关系了再检查空格
        if(i==' ')
        {
            if(isSpace) //前一个已经是空格了，这个直接忽略
                continue;
            //前一个不是空格，进状态并写入空格
            isSpace=true;
            newstr+=i;
            continue;
        }
        //普通字符
        isSpace=false; //无论如何都出空格状态
        newstr+=i;
    }
    str=newstr;
}
