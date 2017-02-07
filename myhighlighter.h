#ifndef MYHIGHLIGHTER_H
#define MYHIGHLIGHTER_H
#include<QSyntaxHighlighter>

class MyHighlighter:public  QSyntaxHighlighter
{
public:
    MyHighlighter();
    void highlightBlock(const QString &text);

};

#endif // MYHIGHLIGHTER_H
