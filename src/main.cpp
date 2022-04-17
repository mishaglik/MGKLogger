#include "MGKLogger.hpp"

mgk::Logger logg;
using mgk::CoStyle;
using mgk::ErrLevel;

int main(){
    logg << "Kekw" << mgk::endl;
    logg.incTabs();
    logg << CoStyle::Cyan << CoStyle::Bold << "Lol" << mgk::endl;
    logg << ErrLevel::Warning << CoStyle::Underline << CoStyle::Bold << CoStyle::Green << "Warinig" << mgk::endl;
}