#include <QCoreApplication>
#include "JS.h"

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

    myjs.JSEval("lib.WriteTXT(\"D:/123.txt\",\"hello world!\")",NULL_String);
}
