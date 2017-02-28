#include <QCoreApplication>
#include "preprocessor.h"

void registerType()
{
    //RegisterJSType(QScriptEngine*,"QScriptEngine*");
    RegisterJSType(String,"String");
    RegisterJSType(Lib*,"Lib");
}

Lib *aLib;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    registerType();
    aLib=new Lib;
    JSVM myjs(aLib);

    String inipath=aLib->getPath("makefile.ini");
    String mainpath=aLib->ReadINI(inipath,"project","main");
    if(aLib->ReadINI(inipath,"project","preprocessor")=="true")
    {preprocessor::run(mainpath,&myjs);}
    else
    {myjs.JSEvalFile(mainpath);}
    return a.exec();
}
