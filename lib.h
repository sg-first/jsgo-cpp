#pragma once
#include <QString>
#include <QDir>
#include <QSettings>
#include <QFile>
#include <QTextStream>
#include <QTextCodec>

typedef QString String;
#define NULL_String ""

class Lib : public QObject //传递给js用的Lib
{
    Q_OBJECT
public:
    Lib(const Lib&):QObject(0){}
    Lib(){}

    Q_INVOKABLE String ReadTXT(String path, int line=-1);
    Q_INVOKABLE void WriteTXT(String path,String text);
};
