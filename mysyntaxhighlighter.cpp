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
    QFont errorFont  = QFont("Courier",12);
    errorFont.setUnderline(true);
    defaultFormat.setFont(errorFont);
    defaultFormat.setUnderlineColor(Qt::red);
    defaultFormat.setUnderlineStyle(QTextCharFormat::SpellCheckUnderline);


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
       classRule.pattern = QRegExp("\\bQ[A-Za-z]+\\b");
       classRule.format = classFormat;
       highlightingRules.append(classRule);

       //single line comment format
        QFont font= QFont("Courier",12);
       font.setUnderline(true);
       singleLineCommentFormat.setFont(font);
       singleLineCommentFormat.setForeground(Qt::red);
       singleLineCommentRule.pattern = QRegExp("//[^\n]*");
       singleLineCommentRule.format = singleLineCommentFormat;
       highlightingRules.append(singleLineCommentRule);

       multiLineCommentFormat.setForeground(Qt::red);

       //String format
       quotationFormat.setForeground(Qt::darkGreen);
       quotationRule.pattern = QRegExp("\".*\"");
       quotationRule.format = quotationFormat;
       highlightingRules.append(quotationRule);

       //Number format
       numberFormat.setForeground(Qt::black);
       numberFormat.setFontWeight(QFont::Bold);
       numberRule.pattern = QRegExp("\".*\"");
       numberRule.format = numberFormat;
       highlightingRules.append(numberRule);

       // function name format
       functionNameFormat.setFontItalic(true);
       functionNameFormat.setForeground(Qt::blue);

       functionNameRule.pattern = QRegExp("\\b[A-Za-z0-9_]+(?=\\()");
       functionNameRule.format = functionNameFormat;
       highlightingRules.append(functionNameRule);

       commentStartExpression = QRegExp("/\\*");
       commentEndExpression = QRegExp("\\*/");

       functionStartExpression = QRegExp("function;");
       functionEndExpression = QRegExp("end;");

}

void MySyntaxHighlighter::highlightBlock(const QString &text)
{

    setFormat(0,text.length(),defaultFormat);
    foreach (const HighlightingRule &rule, highlightingRules) {
        QRegExp expression(rule.pattern);
        int index = expression.indexIn(text);

        while (index >= 0) {
            int length = expression.matchedLength();
            setFormat(index, length, rule.format);
            index = expression.indexIn(text, index + length);
        }
    }

     int index;
    //highlight comment line last
     QRegExp singleLineCommentexpression(singleLineCommentRule.pattern);
    index = singleLineCommentexpression.indexIn(text);
    while (index >= 0) {
        int length = singleLineCommentexpression.matchedLength();
        setFormat(index, length, singleLineCommentRule.format);
        index = singleLineCommentexpression.indexIn(text, index + length);
    }
      QRegExp quotationexpression(quotationRule.pattern);
    index = quotationexpression.indexIn(text);
    while (index >= 0) {
        int length = quotationexpression.matchedLength();
        setFormat(index, length, quotationRule.format);
        index = quotationexpression.indexIn(text, index + length);
    }
      QRegExp numberexpression(numberRule.pattern);
    index = numberexpression.indexIn(text);
    while (index >= 0) {
        int length = numberexpression.matchedLength();
        setFormat(index, length, numberRule.format);
        index = numberexpression.indexIn(text, index + length);
    }
     QRegExp functionNameexpression(functionNameRule.pattern);
    index = functionNameexpression.indexIn(text);
    while (index >= 0) {
        int length = functionNameexpression.matchedLength();
        setFormat(index, length, functionNameRule.format);
        index = functionNameexpression.indexIn(text, index + length);
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
