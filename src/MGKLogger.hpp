#ifndef MKGLIB_MKGLOGGER_MGKLOOGGER_H
#define MKGLIB_MKGLOGGER_MGKLOOGGER_H
#include <iostream>

namespace mgk{

    class endl {};

    enum class CoStyle{
        Reset     = 0,
        Bold      = 1,
        Underline = 4,
        Black     = 30,
        Red       = 31,
        Green     = 32,
        Yellow    = 33,
        Blue      = 34,
        Mangenta  = 35,
        Cyan      = 36,
        White     = 37,
    };

    class Logger{
        void printHeader();

        std::ostream &out;

    public:
        Logger() : out(std::cerr) {};
        Logger(std::ostream &out) : out(out) {};

        Logger& operator <<(char                n) {out << n; return *this;};
        Logger& operator <<(int                 n) {out << n; return *this;};
        Logger& operator <<(unsigned            n) {out << n; return *this;};
        Logger& operator <<(long long           n) {out << n; return *this;};
        Logger& operator <<(unsigned long long  n) {out << n; return *this;};
        Logger& operator <<(float               n) {out << n; return *this;};
        Logger& operator <<(double              n) {out << n; return *this;};
        Logger& operator <<(const char*         s) {out << s; return *this;};

        Logger& operator <<(endl);
        Logger& operator <<(CoStyle style) {out << "\033[" << (int)style << "m"; return *this};
    };

};

#endif