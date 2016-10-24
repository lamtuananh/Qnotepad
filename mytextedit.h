#ifndef MYTEXTEDIT_H
#define MYTEXTEDIT_H

#include<QTextEdit>

class MyTextEdit:public QTextEdit
{
    Q_OBJECT
public:
    MyTextEdit();
private slots:
    void onTextContentChanged();

};

#endif // MYTEXTEDIT_H
