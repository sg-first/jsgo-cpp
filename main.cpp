#include <QCoreApplication>
#include "preprocessor.h"

void registerType()
{
    //RegisterJSType(JSVM*,"JSVM*");
    RegisterJSType(String,"String");
    RegisterJSType(Lib*,"Lib");
}

Lib *aLib;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    registerType();
    aLib=new Lib;
    JS myjs(aLib);

    String inipath=aLib->GetPath("makefile.ini");
    String mainpath=aLib->ReadINI(inipath,"project","main");
    preprocessor::run(mainpath,&myjs);
}
