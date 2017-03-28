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
void CheckThread ::run()
{
    //int i=0;
    //QTextStream out(stdout);
    while(true)
    {
        sleep(2);
        emit mywindow->editor->textEdit->activateResetHighlighter();
        sleep(2);
        emit mywindow->activateUpdateCompleter();
       /* for(int j = 0; j<mywindow->editor->textEdit->document()->blockCount();j++)
        {
            QTextBlock *block = & mywindow->editor->textEdit->document()->findBlockByLineNumber(j);
            out<<j<<" "<< block->text() <<endl;
        }*/
    }
}
