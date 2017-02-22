#pragma once
#include <QtScript/QScriptEngine>
#include <QtScript/QScriptValue>
#include <QVector>
#include "Lib.h"

typedef QScriptEngine JSVM;
typedef QVariant Variant;
#define RegisterJSType(TypeName,JSName) qRegisterMetaType<TypeName>(JSName)

class JSParStru
{
public:
    void add(QObject *pointer,QString name);
    QVector<QObject*>pointerVec;
    QVector<QString>nameVec;

    bool operator !=(const JSParStru &par);
};
const JSParStru _NULLJSParStru;


class JS : public QObject
{
    Q_OBJECT
private:
    JSVM* AddJSVM(Lib *aLib);

public:
    JS(const JS&):QObject(0){}
    JS(){}
    JS(Lib *aLib);
    JSVM* VM;
    Lib* aLib;

    Q_INVOKABLE Variant JSEval(String code,String functionname=NULL_String,String *mistake=nullptr);
    Q_INVOKABLE void JSSendJSPar(JSParStru Parame);
    Q_INVOKABLE Variant JSEvalFile(String path,String functionname=NULL_String,String *mistake=nullptr);
    Q_INVOKABLE Variant JSCallFun(String functionname,String *mistake=nullptr);
    Q_INVOKABLE void DeleteJSVM(JSVM *VM){delete VM;}

    //Q_INVOKABLE void JSSendPar(ParametersStru *Parame,String ParameName);
    /*Q_INVOKABLE ParametersStru* NewParametersStru() {return new ParametersStru();}
    Q_INVOKABLE ParametersStru GetParametersStruVal(ParametersStru *par) {return *par;}
    Q_INVOKABLE void DeleteParametersStru(ParametersStru *par) {delete par;}*/
};
