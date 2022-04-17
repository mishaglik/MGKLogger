#include "MGKLogger.hpp"

namespace mgk{

    Logger& Logger::operator <<(endl){
        out << '\n';
        printHeader();
        return *this;
    }

    Logger& Logger::operator <<(CoStyle style){
        
    }
    
}