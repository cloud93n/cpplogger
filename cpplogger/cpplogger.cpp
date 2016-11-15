// clogger.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#define LOG_LEVEL 4
#define PRINT_VAR
#define CATCH_ERROR
#include "cpplogger.hpp"


int main(int argc, const char * argv[]) {
    LOGFILE

    LOG_DEBUG("Maybe i can touch this button...");

    LOG_INFO("please be careful");

    LOG_ERROR("Error is everywhere please respondsssssssssssssssssssssssssssssssssssssssssssssssssss");

 

    int i = 0;
    _(++i);

    for (int i = 0; i < 5; ++i)
    {
        _(i);
    }
    
    CATCH(
        throw 20;
    )
        return 0;
}