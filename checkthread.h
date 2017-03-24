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
     CheckThread(const MyWindow *parent=0);
    static QVector<QString> listWords;
    const MyWindow *mywindow;
  //  MySyntaxHighlighter *hightlighter;
    void run() override;


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
