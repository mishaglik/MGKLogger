/**
 * @file MGKLogger.cpp
 * @author mishaglik (toomicle@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-17
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "MGKLogger.hpp"
#include <ctime>

namespace mgk{

    Logger& Logger::operator <<(Special sp){
        if(curlevel >= loglevel){
            switch (sp)
            {
            case Special::Endl:
                out << "\033[0;m\n";
                printHeader();
                for(unsigned i = 0; i < tabs; ++i) out << '\t';
                break;
            case Special::Time:
                printTime();
                break;
            default:
                break;
            }
        }
        return *this;
    }

    Logger::Logger(ErrLevel level, std::ostream &ostream) : 
            out(ostream), loglevel(level)
    {
        operator<<(CoStyle::Bold);
        out << "Log started at ";
        printTime();
        operator<<(endl);
    }


    Logger::~Logger(){
        tabs = 0;
        operator<<(CoStyle::Reset);
        out << "\n";
        operator<<(CoStyle::Bold);
        out << "Log stopped at ";
        printTime();
        out << "\n"
        "Thanks for using MGKLogger (c) Mishaglik 2022\n\n";
        operator<<(CoStyle::Reset);
    }

    void Logger::printTime(){
        const size_t strSz = 100;

        static char str[strSz] = "";

        std::time_t time = std::time(nullptr);
        std::strftime(str, strSz, "%d %b %T", std::localtime(&time));

        out << str;
    }

    Logger& Logger::operator <<(ErrLevel level){
        curlevel = level;
        operator<<(endl);
        return *this;
    }

    void Logger::printHeader(){
        printTime();
        out << '[';

        operator<<(CoStyle::Bold);
        
        switch (curlevel)
        {
        case ErrLevel::Debug:
            out << "Debug";
            break;

        case ErrLevel::Info:
            out << "Info";
            break;

        case ErrLevel::Warning:
            operator<<(CoStyle::Yellow);
            out << "Warning";
            break;

        case ErrLevel::Error:
            operator<<(CoStyle::Red);
            out << "Error";
            break;

        case ErrLevel::Fatal:
            operator<<(CoStyle::Red);
            out << "Fatal";
            break;

        default:
            break;
        }
        operator<<(CoStyle::Reset);
        out << "]: ";
    }
}