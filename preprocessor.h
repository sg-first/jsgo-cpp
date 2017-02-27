#pragma once
#include "JSVM.h"

class preprocessor
{
public:
    static void run(String codepath,JSVM* VM);
    static String PCodeFile(String codepath);
    static String prepro(String str, String &newcode);

private:
    static void deleteComment(String &str);
    static void deleteSpace(String &str); //把几个连一起的空格变成一个空格
};
