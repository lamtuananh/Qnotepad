#include "mytextedit.h"
#include <iostream>
MyTextEdit::MyTextEdit()
{
    this->setFont(QFont ("Courier", 12));
}
 void MyTextEdit::onTextContentChanged()
 {
    std::cout<<" I am here in my text edit";
 }
