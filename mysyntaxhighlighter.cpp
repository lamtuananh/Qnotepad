#include "mysyntaxhighlighter.h"
#include<QTextCharFormat>
MySyntaxHighlighter::MySyntaxHighlighter(QObject *parent) : QSyntaxHighlighter(parent)
{

}
void MySyntaxHighlighter::highlightBlock(const QString &text)
{
    QTextCharFormat format;
    QRegExp rx(pattern);

    if(!rx.isValid()  || rx.isEmpty() || rx.exactMatch("")){
        setFormat(0, text.length(),format);
        return;
    }
    QFont serifFont("Times", 12, QFont::Bold);

    format.setBackground(Qt::yellow);
    format.colorProperty(Qt::red);
    format.setFont(serifFont);
    int index = rx.indexIn(text);
    while (index>=0) {
        int length = rx.matchedLength();
        setFormat(index,length,format);
        index = rx.indexIn(text,index + length);
    }
}
