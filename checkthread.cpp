#include "checkthread.h"
#include <iostream>
#include <QTextStream>
#include <printer.cpp>
#include <QTextBlock>
#include <mysyntaxhighlighter.h>
CheckThread::CheckThread( MyWindow *parent)
{
     mywindow = parent;
}
int i = 0;
void CheckThread ::run()
{
    while(true)
    {
        i++;
        if(i==10){
        emit mywindow->editor->textEdit->activateResetHighlighter();
        i=0;
        }
        sleep(1);
    }
}
