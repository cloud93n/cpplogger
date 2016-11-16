

#ifndef HLOGGER_H
#define HLOGGER_H

/**

cpplogger.h
Purpose : Provide logging function
How to use : 
1. cpplogger.hpp must be included in main file.
2. define log_level using #define LOG_LEVEL #level main file 
    where #level is
    -DEBUG_LEVEL : log debug, info and error
    -INFO_LEVEL : log info and error
    -ERROR_LEVEL : log error
3. by default, LOG_LEVEL is set to DEBUG_LEVEL
4. if LOG_LEVEL is set as DEBUG_LEVEL then additional funtions are provided
    -to print variabel name and value, #define PRINT_VAR must be included in main file.
        function _(x) is used to print variable where x is the identifier
    -to use try-catch block for code, #define CATCH_ERROR can be included in main file.
        function CATCH(CODE) is used for exception handling where CODE is block of code
5. LOGFILE must be included in main function to define log file
6. a. Function for debug message is LOG_DEBUG(message) where message is string of character
   b. Function for info message is LOG_INFO(message) where message is string of character
   c. Function for error message is LOG_ERROR(message) where message is string of character
7. every function must be ended with semicolon(;) except for CATCH(CODE)
  
*/




#include <time.h>
//#include <string.h>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <exception>

// for time function
static inline char *timenow();

//logging file
#define LOGFILE std::ofstream outfile;\
               outfile.open("LOGNAME.LOG", std::ios::out | std::ios::trunc);


//shorten file path
#define _FILE strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__

#define ERROR_LEVEL     0
#define INFO_LEVEL      1
#define DEBUG_LEVEL     2

#ifndef LOG_LEVEL
#define LOG_LEVEL   DEBUG_LEVEL
#endif

//to prevent unexpected value for log_level
#ifdef LOG_LEVEL
#if LOG_LEVEL <0 || LOG_LEVEL>2
#define LOG_LEVEL DEBUG_LEVEL
#endif
#endif


//print to file
#define PRINTFUNCTION(LOG_TAG,message,...)      outfile<< std::left << timenow() << " | " << std::setw(7) << LOG_TAG << " | " << std::setw(20) << _FILE;\
                                            outfile << " | "  << std::setw(10) << std::right << __FUNCTION__ << " : " << std::left <<std::setw(4) <<__LINE__ << " | " << message ## __VA_ARGS__

#define ERROR_TAG   "ERROR"
#define INFO_TAG    "INFO"
#define DEBUG_TAG   "DEBUG"

#if LOG_LEVEL >= DEBUG_LEVEL
#define LOG_DEBUG(message, ...)     PRINTFUNCTION(DEBUG_TAG,message, ##__VA_ARGS__) << '\n'
#else
#define LOG_DEBUG(message, ...)
#endif

#if LOG_LEVEL >= INFO_LEVEL
#define LOG_INFO(message, ...)      PRINTFUNCTION(INFO_TAG,message) << '\n'
#else
#define LOG_INFO(message, ...)
#endif

#if LOG_LEVEL >= ERROR_LEVEL
#define LOG_ERROR(message, ...)    PRINTFUNCTION(ERROR_TAG,message) << '\n'
#else
#define LOG_ERROR(message, ...)
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
#define _(X) LOG_DEBUG(#X,<< " : " << X ) 
#endif //print_var

#else
#define CATCH(CODE)
#define _(X) X
#endif //log_level==debug_level

static inline char *timenow() 
{
    static char buffer[80];
    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", timeinfo);

    return buffer;
}



#endif