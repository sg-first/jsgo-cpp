#include "JS.h"

//JSParStru
void JSParStru::add(QObject *pointer,QString name)
{
    pointerVec<<pointer;
    nameVec<<name;
}

bool JSParStru::operator !=(const JSParStru &par)
{
    if(pointerVec==par.pointerVec&&nameVec==par.nameVec)
    {return false;}
    return true;
}

//JS
JS::JS(Lib *aLib)
{
    VM=AddJSVM(aLib);
    this->aLib=aLib;
}

JSVM* JS::AddJSVM(Lib *aLib)
{
    JSVM *VM=new JSVM;
    QScriptValue qsLib=VM->newQObject(aLib);
    VM->globalObject().setProperty("lib",qsLib);
    return VM;
}

Variant JS::JSEval(String code,String functionname,String *mistake)
{
    QScriptValue ret;
    if(code!=NULL_String)
    {ret=VM->evaluate(code);}
    if(functionname!=NULL_String)
    {
        ret=VM->globalObject().property(functionname);
        ret.call(QScriptValue());
    }
    if(ret.isError())
    {
        if(mistake!=nullptr)
        {*mistake=String::number(ret.property("lineNumber").toInt32())+" line:"+ret.toString();}
        return NULL;
    }
    return ret.toVariant();
}

/*void JS::JSSendPar(ParametersStru *Parame,String ParameName) //注意，使用指针仅因迫不得已，实际创建请不要new
{
    QScriptValue para=VM->newQObject(Parame);
    VM->globalObject().setProperty(ParameName,para);
}*/

void JS::JSSendJSPar(JSParStru Parame)
{
    for(int i=0;i<Parame.pointerVec.length();i++)
    {
        QScriptValue para=VM->newQObject(Parame.pointerVec[i]);
        VM->globalObject().setProperty(Parame.nameVec[i],para);
    }
}

Variant JS::JSEvalFile(String path,String functionname,String *mistake)
{return JSEval(aLib->ReadTXT(path),functionname,mistake);}

Variant JS::JSCallFun(String functionname,String *mistake)
{return JSEval(NULL_String,functionname,mistake);}

