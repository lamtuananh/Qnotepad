#include "mysyntaxhighlighter.h"
#include <QTextCharFormat>
#include <QMap>
#include <QFont>
#include <iostream>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include "checkthread.h"
#include <algorithm>
#include <QtAlgorithms>
//inicialization fonts

//static const QFont TEXTFONT = QFont("Courier",12);
int INSTRING = 1;
int OUTOFCOMMENT = 2;
int INCOMMENT = 3;
int INSINGLECOMMENT = 4;
int WAITINGFORSEMICOLON = 5;
int countQuotion = 0;


QTextStream out(stdout);
QVector<QString> currentBlockVariableNames;


//MySyntaxHighlighter::MySyntaxHighlighter(TextEdit *parent) : QSyntaxHighlighter(parent),textEdit(parent)
MySyntaxHighlighter::MySyntaxHighlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
QTextStream out(stdout);
   datatypes.append("input");
   datatypes.append("output");
   datatypes.append("wire");
   datatypes.append("supply0");
   datatypes.append("supply1");
   datatypes.append("wand");
   datatypes.append("trior");
   datatypes.append("wor");
   datatypes.append("shortint");
   datatypes.append("int");
   datatypes.append("longint");
   datatypes.append("byte");
   datatypes.append("bit");
   datatypes.append("logic");
   datatypes.append("reg");
   datatypes.append("integer");
   datatypes.append("time");
   datatypes.append("parameter");
   datatypes.append("inout");


     HighlighRule rule;
    QFont errorFont  = QFont("Courier",12);
    defaultFormat.setFont(errorFont);
    // defaultFormat.setUnderlineStyle(QTextCharFormat::);
    QFont normalFont  = QFont("Courier",12);
    blankFormat.setFont(normalFont);
    defaultFormat.setFont(normalFont);

    keywordFormat.setForeground(Qt::blue);
    keywordFormat.setFontWeight(QFont::Bold);
       QStringList keywordPatterns;

//       QString path = QDir::currentPath() +"/systemTaskFunction.txt";
       QString path = ":/resources/keywords.txt";

       QFile file(path);
       if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
             {
           // out<<path.toStdString();
           out<<"errow while reading file";
           return;
       }
        QTextStream in(&file);
        QString line = in.readLine();
        while (!line.isNull()) {
        keywordPatterns.append("\\b"+line+"\\b");
        keywords.append(line);
        line = in.readLine();
          }
        file.close();
       QString path2=":/resources/systemTaskFunction.txt";
       QFile file2(path2);
       if (!file2.open(QIODevice::ReadOnly | QIODevice::Text))
             {
           out<<"errow while reading file";
           return;
       }
       QTextStream in2(&file2);
        QString line2 = in2.readLine();
        while (!line2.isNull()) {
            out<<line2;
        systemTaskFunction.append(line2);
        line2 = in2.readLine();

        }
        file2.close();
        systemFunctionFormat.setFontWeight(QFont::Bold);
        systemFunctionFormat.setForeground(Qt::red);
        foreach (const QString &pattern, systemTaskFunction) {
            rule.pattern = QRegExp("\\$"+pattern+"\\b");
            rule.format = systemFunctionFormat;
            highlightingRules.append(rule);
        }

       foreach (const QString &pattern, keywordPatterns) {
           rule.pattern = QRegExp(pattern);
           rule.format = keywordFormat;
           highlightingRules.append(rule);
       }
       QTextCharFormat datatypeFormat;
       normalFont.setBold(true);
       datatypeFormat.setFont(normalFont);
       datatypeFormat.setForeground(Qt::darkBlue);
       foreach (const QString &pattern, datatypes) {
           rule.pattern = QRegExp("\\b"+pattern+"\\b");
           rule.format = datatypeFormat;
           highlightingRules.append(rule);
       }
       errorFont.setBold(false);
       errorFont.setItalic(true);
       variableFormat.setFont(errorFont);
       variableFormat.setForeground(Qt::red);
       initVariableRule.pattern = QRegExp("\\b(input\\s+|output\\s+)?(input|output|wire|supply0|supply1|wand|trior|wor|shortint|int|longint|byte|bit|logic|reg|integer|time)\\s+[_a-zA-Z0-9$]+\s\*(\\[[0-9]\*:[0-9]\*\\])?\\s\*(,\\s\*[_a-zA-Z0-9$]+\\s\*\s\*(\\[[0-9]\*:[0-9]\*\\])?\\s\*)\*;");       
       initVariableRule.format = variableFormat;

       variableRule.pattern = QRegExp("[_a-zA-Z]+");
       variableRule.format = variableFormat;

       operatorFormat.setForeground(Qt::darkRed);
       operatorRule.pattern = QRegExp("([\\*|\\+|\\-|\\/|\\%|&&|!|\\?|=|==|@]){1}");
       operatorRule.format = operatorFormat;
       highlightingRules.append(operatorRule);

       //Include
       includeFormat.setFontWeight(QFont::Bold);
       includeFormat.setForeground(Qt::green);
       includeRule.pattern = QRegExp("^`include+\\s+");
       includeRule.format = includeFormat;
       highlightingRules.append(includeRule);

       //define
       defineRule.pattern = QRegExp("`[_a-zA-Z]+\\b");
       defineRule.format = includeFormat;
       highlightingRules.append(defineRule);

       parameterFormat.setFontWeight(QFont::Bold);
       parameterFormat.setForeground(Qt::red);
       parameterRule.pattern = QRegExp("hello (?=\\s+parameter\\s+)");
       parameterRule.format = parameterFormat;
       highlightingRules.append(parameterRule);


       ioFormat.setFontWeight(QFont::Bold);
       ioFormat.setForeground(Qt::red);
       ioRule.pattern = QRegExp("[\\n\\r].*(input|output)?\\s*([^\\n\\r]*)");
       ioRule.format = ioFormat;\
       highlightingRules.append(ioRule);

       //System function call
       systemFunctionFormat.setFontWeight(QFont::Bold);
       systemFunctionFormat.setForeground(Qt::red);
       systemFunctionRule.pattern = QRegExp("\\$[a-zA-Z]+\\b");
       systemFunctionRule.format = systemFunctionFormat;
       //highlightingRules.append(systemFunctionRule);

       //single line comment format
        QFont font= QFont("Courier",12);
       font.setUnderline(false);
       singleLineCommentFormat.setFont(font);
       singleLineCommentFormat.setForeground(Qt::darkGreen);
       singleLineCommentRule.pattern = QRegExp("//[^\\n]*");
       singleLineCommentRule.format = singleLineCommentFormat;
       highlightingRules.append(singleLineCommentRule);

       multiLineCommentFormat.setForeground(Qt::darkGreen);

       //String format
       quotationFormat.setForeground(Qt::darkRed);
       quotationRule.pattern = QRegExp("\".*\"");
       quotationRule.format = quotationFormat;
       highlightingRules.append(quotationRule)
               ;

       //Number format
       numberFormat.setForeground(Qt::black);
       numberFormat.setFontWeight(QFont::Bold);
       decimalNumberRule.pattern = QRegExp("\\b[0-9]+\\b");
       decimalNumberRule.format = numberFormat;
       highlightingRules.append(decimalNumberRule);

       //Hex Number format
       hexNumberRule.pattern = QRegExp("\\b0[xX][0-9a-fA-F]+\\b");
       hexNumberRule.format = numberFormat;
       highlightingRules.append(hexNumberRule);

       //octal number
       octalNumberRule.pattern=QRegExp("\\b[0-9]+'h[0-9]+\\b");
       octalNumberRule.format = numberFormat;
       highlightingRules.append(octalNumberRule);

       //identifier format

       identifierFormat.setForeground(Qt::blue);
       identifierRule.pattern = QRegExp("[_a-zA-Z][_a-zA-Z0-9]{0,30}");
       identifierRule.format = keywordFormat;


       // function name format
       functionNameFormat.setFontItalic(true);
       functionNameFormat.setForeground(Qt::black);
       functionNameRule.pattern = QRegExp("^[^\\$][A-Za-z0-9_]+(?=\\()");
       functionNameRule.format = functionNameFormat;
       highlightingRules.append(functionNameRule);

       commentStartExpression = QRegExp("/\\*");
       commentEndExpression = QRegExp("\\*/");

       functionStartExpression = QRegExp("function;");
       functionEndExpression = QRegExp("end;");

}

QString getText(const QString &text, int from, int to)
{
    int length = text.length();
    if(to>from && to<=length)
    return text.left(to).right(to-from);//.right(from-to);
    else return "";
}
void MySyntaxHighlighter::highlightBlock(const QString &text)
{
  //  int textLength = text.length();
    if(text == "") countQuotion = 0;
    int index = 0;
    foreach (const HighlighRule &rule, highlightingRules) {
        QRegExp expression(rule.pattern);
        int index = expression.indexIn(text);
        while (index >= 0) {
            int length = expression.matchedLength();
            setFormat(index, length, rule.format);
            index = expression.indexIn(text, index + length);
        }
    }

    foreach (const QString &datatype, datatypes) {
    int index = -1;
    QRegExp initVariableExpression=QRegExp("\\b"+datatype+"\\b");
    index = initVariableExpression.indexIn(text);
    while (index >= 0) {
        int indexOfSemicolon=-1;
        for(int i = index; i<text.length();i++)
        {
            if(text.at(i)==';') {
                indexOfSemicolon = i;
                break;
            }
        }
     QString workingText = getText(text,index,text.length());
        if(indexOfSemicolon != -1)
     {
         workingText =getText(text,index,indexOfSemicolon);
        }
       int length = initVariableExpression.matchedLength();
    int affterDatatypeIndex = index+datatype.length();
    QString pom = workingText.right(workingText.length() - datatype.length());
    out<< workingText.length() - affterDatatypeIndex <<endl;

    QRegExp variableExpression(variableRule.pattern);
    int varindex = variableExpression.indexIn(pom);
    while(varindex>=0)
    {
        int varlength = variableExpression.matchedLength();
      QString varName = pom.right(pom.length()-varindex).left(varlength);
        if(std::find(keywords.begin(),keywords.end(),varName) == keywords.end())
        {
            if(std::find(variableNames.begin(),variableNames.end(),varName) == variableNames.end())
            {
                out<<"datatype is :" <<datatype<<endl;
                if(datatype.compare("parameter")==0)
                {
                    out<<"Parametereererre"<<endl;
                    parameterNames.append(varName);
                }
                    else
                    if(datatype.compare("input")==0)
                    inputOutputNames.append(varName);
                    else
                        if(datatype.compare("output")==0)
                        inputOutputNames.append(varName);
                        else
                        variableNames.append(varName);

            }
                //setFormat(affterDatatypeIndex+varindex,varlength,variableRule.format);
        }
        boolean isFinish = false; // check semicolon char
       if(isFinish) break;
        varindex = variableExpression.indexIn(pom, varindex+varlength);
    }
    index = initVariableExpression.indexIn(text, index + length);
}
}
    foreach (const QString &variable, variableNames) {

        QRegExp expression =QRegExp("\\b"+variable+"\\b");
        int index = expression.indexIn(text);
        while (index >= 0) {
            int length = expression.matchedLength();
              out<<"checking "<<endl;
            setFormat(index, length, variableFormat);
            index = expression.indexIn(text, index + length);
        }
    }
    foreach (const QString &parameter, parameterNames) {

        QRegExp expression =QRegExp("\\b"+parameter+"\\b");
        int index = expression.indexIn(text);
        while (index >= 0) {
            int length = expression.matchedLength();
              out<<"checking "<<endl;
            setFormat(index, length, parameterFormat);
            index = expression.indexIn(text, index + length);
        }
    }
    foreach (const QString &inputoutput, inputOutputNames) {

        QRegExp expression =QRegExp("\\b"+inputoutput+"\\b");
        int index = expression.indexIn(text);
        while (index >= 0) {
            int length = expression.matchedLength();
              out<<"checking "<<endl;
            setFormat(index, length, ioFormat);
            index = expression.indexIn(text, index + length);
        }
    }
   QRegExp singleLineCommentexpression(singleLineCommentRule.pattern);
    index = singleLineCommentexpression.indexIn(text);
    while (index >= 0) {
        int length = singleLineCommentexpression.matchedLength();
        int coutQuotion = 0;
        for(int i=0;i<=index;i++)
            if(text.at(i) == '"') coutQuotion++;
         if(coutQuotion%2 == 0)
             setFormat(index, length, singleLineCommentRule.format);
          index = singleLineCommentexpression.indexIn(text, index + length);
    }

  //  out<<"check point 0" << endl;
    setCurrentBlockState(OUTOFCOMMENT);
        int startIndex = 0;
        if (previousBlockState() != INCOMMENT)
            startIndex = commentStartExpression.indexIn(text);

  //      out<<"check point 1" << endl;
        int coutQuotion = 0;
        for(int i=0;i<startIndex;i++)
            if(text.at(i) == '"') coutQuotion++;

  //      out<<"check point 2" << endl;
        while (startIndex >= 0 && coutQuotion%2 ==0) {
            int endIndex = commentEndExpression.indexIn(text, startIndex);
            int commentLength;
            if (endIndex == -1) {
                setCurrentBlockState(INCOMMENT);
                commentLength = text.length() - startIndex;

 //               out<<"check point 3" << endl;
            } else {
                commentLength = endIndex - startIndex
                                + commentEndExpression.matchedLength();
            }
             if(previousBlockState()!= INSTRING) setFormat(startIndex, commentLength, multiLineCommentFormat);
            startIndex = commentStartExpression.indexIn(text, startIndex + commentLength);

   //         out<<"check point 4" << endl;
        }
  /*      out<<"Variable names "<<endl;
        for(QString var:variableNames)
            out<<var<<" ";
*/


        QRegExp expression(parameterRule.pattern);
        out<<"xxxxxxxxxxxxxxxxxxxxxxx";
         index = expression.indexIn(text);
        while (index >= 0) {
             out<<"check point 4 " << endl;
            int length = expression.matchedLength();
            setFormat(index, length, parameterRule.format);
            out<<index<<" "<<length<<endl;
            index = expression.indexIn(text, index + length);
        }
}

void MySyntaxHighlighter::reset()
{
   // currentBlockVariableNames.clear();
    out<<"removing all variables "<<endl;
    variableNames.clear();
}

