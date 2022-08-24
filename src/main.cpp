#include "MGKLogger.hpp"

mgk::Logger logg(mgk::ErrLevel::Debug);
using mgk::CoStyle;
using mgk::ErrLevel;

int main(){
    logg << ErrLevel::Debug << "Kekw" << mgk::endl << "Second Kekw";
    logg << ErrLevel::Debug << "hhh\n" << "solovasf";
    logg << CoStyle::Cyan << CoStyle::Bold << "Lol";
    logg << ErrLevel::Warning << CoStyle::Underline << CoStyle::Bold << CoStyle::Green << "Warinig";
    logg << ErrLevel::Error << CoStyle::Underline << CoStyle::Bold << CoStyle::Red << "Error";
    logg << ErrLevel::Fatal << CoStyle::Cyan << "Fatal" << ErrLevel::Fatal << "aegag" << ErrLevel::Fatal;
}