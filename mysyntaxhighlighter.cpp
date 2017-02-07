#include "mysyntaxhighlighter.h"
#include <QTextCharFormat>
#include <QMap>
#include <QFont>
#include <iostream>
#include <QFile>
#include <QTextStream>
#include <QDir>
MySyntaxHighlighter::MySyntaxHighlighter(QObject *parent) : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;
    keywordFormat.setForeground(Qt::blue);
       keywordFormat.setFontWeight(QFont::Bold);
       QStringList keywordPatterns;

       QString path = QDir::currentPath() +"/keywords.txt";
       QFile file(path);
       if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
             {
            std::cout<<path.toStdString();
           std::cout<<"errow while reading file";
           return;
       }
       QTextStream in(&file);
        QString line = in.readLine();
   while (!line.isNull()) {
        keywordPatterns.append("\\b"+line+"\\b");
              line = in.readLine();
          }

       foreach (const QString &pattern, keywordPatterns) {
           rule.pattern = QRegExp(pattern);
           rule.format = keywordFormat;
           highlightingRules.append(rule);
       }

       classFormat.setFontWeight(QFont::Bold);
       classFormat.setForeground(Qt::darkMagenta);
       rule.pattern = QRegExp("\\bQ[A-Za-z]+\\b");
       rule.format = classFormat;
       highlightingRules.append(rule);

       singleLineCommentFormat.setForeground(Qt::red);
       rule.pattern = QRegExp("//[^\n]*");
       rule.format = singleLineCommentFormat;
       highlightingRules.append(rule);

       multiLineCommentFormat.setForeground(Qt::red);

       quotationFormat.setForeground(Qt::darkGreen);
       rule.pattern = QRegExp("\".*\"");
       rule.format = quotationFormat;
       highlightingRules.append(rule);

       functionFormat.setFontItalic(true);
       functionFormat.setForeground(Qt::blue);
       rule.pattern = QRegExp("\\b[A-Za-z0-9_]+(?=\\()");
       rule.format = functionFormat;
       highlightingRules.append(rule);

       commentStartExpression = QRegExp("/\\*");
       commentEndExpression = QRegExp("\\*/");

       functionStartExpression = QRegExp("function;");
       functionEndExpression = QRegExp("end;");

}
/*
void MySyntaxHighlighter::highlightBlock(const QString &text)
{
//    QMapIterator<QString,QString> i(mapPattern);
  //  while(i.hasNext())
    for (int i = 0; i < vector.size(); ++i) {
    QTextCharFormat format;
    QString pattern = vector[i];
    QRegExp rx(pattern);

    if(!rx.isValid()  || rx.isEmpty() || rx.exactMatch("")){
        setFormat(0, text.length(),format);
        std::cout<<"not correct regular expression";
        return;
    }
 //   QFont serifFont = mapFont.value(i.key());
 QFont serifFont = QFont("Bavaria",10,QFont::Bold);
    //format.setBackground(Qt::yellow);
    format.colorProperty(Qt::red);

    format.setFont(serifFont);
    int index = rx.indexIn(text);
    while (index>=0) {
        int length = rx.matchedLength();
        setFormat(index,length,format);
        index = rx.indexIn(text,index + length);
    }
    }
}
*/
void MySyntaxHighlighter::highlightBlock(const QString &text)
{

    foreach (const HighlightingRule &rule, highlightingRules) {
        QRegExp expression(rule.pattern);
        int index = expression.indexIn(text);

        while (index >= 0) {
            int length = expression.matchedLength();
            setFormat(index, length, rule.format);
            index = expression.indexIn(text, index + length);
        }
    }
    setCurrentBlockState(0);

    int startIndex = 0;
    if (previousBlockState() != 1)
        startIndex = commentStartExpression.indexIn(text);

    while (startIndex >= 0) {
        int endIndex = commentEndExpression.indexIn(text, startIndex);
        int commentLength;
        if (endIndex == -1) {
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        } else {
            commentLength = endIndex - startIndex
                            + commentEndExpression.matchedLength();
        }
        setFormat(startIndex, commentLength, multiLineCommentFormat);
        startIndex = commentStartExpression.indexIn(text, startIndex + commentLength);
    }

  /*  setCurrentBlockState(2);

    int startIndex1 = 0;
    if (previousBlockState() != 3)
        startIndex1 = functionStartExpression.indexIn(text);

    while (startIndex1 >= 0) {
        int endIndex1 = functionEndExpression.indexIn(text, startIndex1);
        int commentLength1;
        if (endIndex1 == -1) {
            setCurrentBlockState(3);
            commentLength1 = text.length() - startIndex1;
        } else {
            commentLength1 = endIndex1 - startIndex1
                            + functionEndExpression.matchedLength();
        }
        setFormat(startIndex1, commentLength1, classFormat);
        startIndex1 = functionStartExpression.indexIn(text, startIndex1 + commentLength1);
    }*/
}
