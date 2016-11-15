// clogger.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#define LOG_LEVEL 1
#define PRINT_VAR
#define CATCH_ERROR
#include "cpplogger.h"


int main(int argc, const char * argv[]) {
    LOGFILE
        
    LOG_DEBUG("Maybe i can touch this button...");

    LOG_INFO("Pressure is dropping...");

    LOG_ERROR("Error is everywhere please respondmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm");

    int going_down = 1;
    LOG_IF_ERROR(going_down, "i'm going down... if only i had used macro-logger...");

    int i = 0;
    _(++i);
    std::cout << i;
    CATCH(
        int i;

    )
        return 0;
}