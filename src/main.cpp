#include "MGKLogger.hpp"

mgk::Logger log;
using mgk::CoStyle;
using mgk::ErrLevel;

int main(){
    log << "Kekw" << mgk::endl;
    log << CoStyle::Yellow << CoStyle::Bold << "Lol" << mgk::endl;
    log << ErrLevel::Warning << CoStyle::Bold  << CoStyle::Red << "Warinig" << mgk::endl;
}