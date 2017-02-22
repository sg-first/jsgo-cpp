#include <QCoreApplication>
#include "JS.h"

void registerType()
{
    //RegisterJSType(JSVM*,"JSVM*");
    RegisterJSType(String,"String");
    RegisterJSType(Lib*,"Lib");
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    registerType();
    Lib *aLib=new Lib;
    JS myjs(aLib);
    String mistake;
    myjs.JSEval("lib.WriteTXT(\"D:/123.txt\",\"hello world!\")",NULL_String,&mistake);
}
