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

    Variant JSEval(String code,String functionname=NULL_String,String *mistake=nullptr);
    void JSSendJSPar(JSParStru Parame);
    Variant JSEvalFile(String path,String functionname=NULL_String,String *mistake=nullptr);
    Variant JSCallFun(String functionname,String *mistake=nullptr);
    void DeleteJSVM(JSVM *VM){delete VM;}

};
