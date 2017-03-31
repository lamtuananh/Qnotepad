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
    while(true)
    {
        sleep(1);
        emit mywindow->editor->textEdit->activateResetHighlighter();
        sleep(1);
        emit mywindow->editor->textEdit->activateUpdateCompleter();
    }
}
