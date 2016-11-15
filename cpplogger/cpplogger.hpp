

#ifndef HLOGGER_H
#define HLOGGER_H

/**

cpplogger.h
Purpose : Provided logging function
How to use : 
1. cpplogger.hpp must be included in main file.
2. define log_level using #define LOG_LEVEL #level main file 
    where #level is
    -DEBUG_LEVEL : log debug, info and error
    -INFO_LEVEL : log info and error
    -ERROR_LEVEL : log error
    -NO_LOG : log error only for defined condition
3. if LOG_LEVEL is set as DEBUG_LEVEL then additional funtions are provided
    -to print variabel name and value, #define PRINT_VAR must be included in main file.
        function _(x) is used to print variable where x is the identifier
    -to use try-catch block for code, #define CATCH_ERROR can be included in main file.
        function CATCH(CODE) is used for exception handling whece CODE is block of code
*/




#include <time.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <exception>

// === auxiliar functions
static inline char *timenow();

//logging file
#define LOGFILE std::ofstream outfile;\
               outfile.open("LOGNAME.LOG", std::ios::out | std::ios::trunc);


//shorten file path
#define _FILE strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__

#define NO_LOG          0
#define ERROR_LEVEL     1
#define INFO_LEVEL      2
#define DEBUG_LEVEL     3

#ifndef LOG_LEVEL
#define LOG_LEVEL   DEBUG_LEVEL
#endif

//to prevent unexpected value for log_level
#ifdef LOG_LEVEL
#if LOG_LEVEL <0 || LOG_LEVEL>3
#define LOG_LEVEL DEBUG_LEVEL
#endif
#endif


//print to file
#define PRINTFUNCTION(LOG_TAG,message)      outfile<< std::left << timenow() << " | " << std::setw(7) << LOG_TAG << " | " << std::setw(20) << _FILE;\
                                            outfile << " | "  << std::setw(10) << std::right << __FUNCTION__ << " : " << std::left <<std::setw(4) <<__LINE__ << " | " << message << '\n'

#define ERROR_TAG   "ERROR"
#define INFO_TAG    "INFO"
#define DEBUG_TAG   "DEBUG"

#if LOG_LEVEL >= DEBUG_LEVEL
#define LOG_DEBUG(message, ...)     PRINTFUNCTION(DEBUG_TAG,message)
#else
#define LOG_DEBUG(message, ...)
#endif

#if LOG_LEVEL >= INFO_LEVEL
#define LOG_INFO(message, ...)      PRINTFUNCTION(INFO_TAG,message)
#else
#define LOG_INFO(message, ...)
#endif

#if LOG_LEVEL >= ERROR_LEVEL
#define LOG_ERROR(message, ...)    PRINTFUNCTION(ERROR_TAG,message)
#else
#define LOG_ERROR(message, ...)
#endif

#if LOG_LEVEL >= NO_LOG
#define LOG_IF_ERROR(condition, message, ...) if (condition) PRINTFUNCTION(ERROR_TAG,message)
#else
#define LOG_IF_ERROR(condition, message, ...)
#endif

#if LOG_LEVEL == DEBUG_LEVEL
//catch error using try block
#ifdef CATCH_ERROR 
#define CATCH(CODE) try{CODE} \
                    catch (const std::exception& e)\
                    {LOG_DEBUG(e.what());}\
                    catch(...)\
                    {LOG_DEBUG("unknown exception");}
#endif // CATCH_ERROR

//function to print expression and identifier
// use _()
#ifdef PRINT_VAR
#define _(X) std::cout << #X << " = " << X << std::endl; 
#endif //print_var

#else
#define CATCH(CODE)
#define _(X) X
#endif //log_level==debug_level

static inline char *timenow() {
    static char buffer[64];
    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer, 64, "%Y-%m-%d %H:%M:%S", timeinfo);

    return buffer;
}



#endif