/**
 * @file MGKLogger.hpp
 * @author mishaglik
 * @brief MGKLogger header. 
 * @version 0.1
 * @date 2022-04-17
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef MKGLIB_MKGLOGGER_MGKLOOGGER_H
#define MKGLIB_MKGLOGGER_MGKLOOGGER_H
#include <iostream>

namespace mgk{
    enum class ErrLevel : int{
        Debug = 0,
        Info,
        Warning,
        Error,
        Fatal,
    };

    enum class CoStyle{
        Reset       = 0,

        Bold        = 1,
        Underline   = 4,
        Inverse     = 7,

        UnBold      = 21,
        UnUnderline = 24,
        UnInverse   = 27,

        Black       = 30,
        Red         = 31,
        Green       = 32,
        Yellow      = 33,
        Blue        = 34,
        Mangenta    = 35,
        Cyan        = 36,
        White       = 37,

        BBlack      = 40,
        BRed        = 41,
        BGreen      = 42,
        BYellow     = 43,
        BBlue       = 44,
        BMangenta   = 45,
        BCyan       = 46,
        BWhite      = 47,
    };

    class Logger{
        std::ostream &out = std::cerr;

        ErrLevel loglevel = ErrLevel::Info;
        ErrLevel curlevel = ErrLevel::Info;

        unsigned tabs = 0;

        void printHeader();
        void printTime();
    public:
        enum class Special{
            Endl,
            Newl,
            Time,
        };

        Logger(ErrLevel level = ErrLevel::Info, std::ostream &ostream = std::cerr); 
        ~Logger();

        void incTabs(unsigned x = 1) {tabs += x;}
        void decTabs(unsigned x = 1) {tabs -= (x < tabs ? x : tabs);}

        void setLoglevel(ErrLevel level) {loglevel = level;}

        Logger& operator <<(char                n) {if(curlevel >= loglevel) out << n; return *this;};
        Logger& operator <<(int                 n) {if(curlevel >= loglevel) out << n; return *this;};
        Logger& operator <<(unsigned            n) {if(curlevel >= loglevel) out << n; return *this;};
        Logger& operator <<(long long           n) {if(curlevel >= loglevel) out << n; return *this;};
        Logger& operator <<(unsigned long long  n) {if(curlevel >= loglevel) out << n; return *this;};

        Logger& operator <<(float               n) {if(curlevel >= loglevel) out << n; return *this;};
        Logger& operator <<(double              n) {if(curlevel >= loglevel) out << n; return *this;};
        Logger& operator <<(const char*         s) {if(curlevel >= loglevel) out << s; return *this;};
        Logger& operator <<(const void*         p) {if(curlevel >= loglevel) out << p; return *this;};

        Logger& operator <<(CoStyle style) {if(curlevel >= loglevel) out << "\033[" << (int)style << "m"; return *this;};
        
        Logger& operator <<(Special sp);

        Logger& operator <<(ErrLevel level);
    };

    const Logger::Special endl = Logger::Special::Endl;
};

#endif