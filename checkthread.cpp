#include "checkthread.h"
#include <iostream>
#include <QTextStream>
#include <printer.cpp>
#include <QTextBlock>
#include <mysyntaxhighlighter.h>
CheckThread::CheckThread(const MyWindow *parent)
{
     mywindow = parent;
}
void CheckThread ::run()
{
    int i=0;
    QTextStream out(stdout);
    hightlighter=new MySyntaxHighlighter( mywindow->textEdit);
    hightlighter->setDocument(mywindow->textEdit->document());

    while(true)
    {
        sleep(1);
//        out<<"text "<<endl;
        //out<< mywindow->textEdit->toPlainText()<<endl;
       // for(QTextBlock text: mywindow->textEdit->document()->)
        //    out<<i++<<" "<<text<<endl;
/*        QTextBlock itera=mywindow->textEdit->document()->begin();
        while(itera!= mywindow->textEdit->document()->end())
        {
            out<<i++<<" "<<itera.<<endl;
            itera = itera.next();

        }
*/
        //MySyntaxHighlighter hightlight;
     //   hightlighter->setDocument(mywindow->textEdit->document());
        for(int j = 0; j<mywindow->textEdit->document()->blockCount();j++)
        {
            QTextBlock *block = & mywindow->textEdit->document()->findBlockByLineNumber(j);
            out<<j<<" "<< block->text() <<endl;
//            MySyntaxHighlighter hightlight;
 //           hightlight.setDocument(block->document());

        }
    }
}
