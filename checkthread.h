#ifndef QMYTHREAD_H
#define QMYTHREAD_H
#include <QThread>
#include <iostream>
#include <QTextStream>
#include <QVector>
#include <mywindow.h>
#include <mysyntaxhighlighter.h>

class CheckThread : public QThread
{
    Q_OBJECT
public:
     CheckThread(MyWindow *parent=0);
    static QVector<QString> listWords;
    MyWindow *mywindow;
    MySyntaxHighlighter *hightlighter;
    void run() override{
        int i=0;
        QTextStream out(stdout);
       // hightlighter = new MySyntaxHighlighter( mywindow);
       // hightlighter->setDocument( mywindow->textEdit->document());
        while(true)
        {
            sleep(10);
            out<<"text "<<i++<<endl;
             out  << mywindow->textEdit->toPlainText()<<endl;
        }
    }
public


    slots:
    void getListWords(){
      //  QString *text;
      //  *text = mywindow->textEdit->toPlainText();

        QTextStream out(stdout);
    //  out  << mywindow->textEdit->toPlainText()<<endl;
    }



};


#endif // QMYTHREAD_H
