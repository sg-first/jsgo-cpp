#pragma once
#include "Lib.h"

class preprocessor
{
public:
    static String PCodeFile(String codepath);
    static String prepro(String str);

private:
    static void deleteComment(String &str);
    static void deleteSpace(String &str); //把几个连一起的空格变成一个空格
};
