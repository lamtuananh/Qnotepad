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

//MySyntaxHighlighter::MySyntaxHighlighter(TextEdit *parent) : QSyntaxHighlighter(parent),textEdit(parent)
MySyntaxHighlighter::MySyntaxHighlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
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


     HighlightingRule rule;
    QFont errorFont  = QFont("Courier",12);
    defaultFormat.setFont(errorFont);
    // defaultFormat.setUnderlineStyle(QTextCharFormat::);
    QFont normalFont  = QFont("Courier",12);
    blankFormat.setFont(normalFont);
    defaultFormat.setFont(normalFont);

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
       // CheckThread::listWords.append(line);
        keywordPatterns.append("\\b"+line+"\\b");
        keywords.append(line);
        line = in.readLine();
          }

       foreach (const QString &pattern, keywordPatterns) {
           rule.pattern = QRegExp(pattern);
           rule.format = keywordFormat;
           highlightingRules.append(rule);
       }
       foreach (const QString &pattern, datatypes) {
           rule.pattern = QRegExp(pattern);
           rule.format = keywordFormat;
           highlightingRules.append(rule);
       }
       errorFont.setBold(true);
       errorFont.setItalic(true);
       variableFormat.setFont(errorFont);
       variableFormat.setForeground(Qt::red);
       initVariableRule.pattern = QRegExp("\\b(input\\s+|output\\s+)?(input|output|wire|supply0|supply1|wand|trior|wor|shortint|int|longint|byte|bit|logic|reg|integer|time)\\s+[_a-zA-Z0-9$]+\s\*(\\[[0-9]\*:[0-9]\*\\])?\\s\*(,\\s\*[_a-zA-Z0-9$]+\\s\*\s\*(\\[[0-9]\*:[0-9]\*\\])?\\s\*)\*;");       
       initVariableRule.format = variableFormat;

       variableRule.pattern = QRegExp("[_a-zA-Z]+");
       variableRule.format = variableFormat;

  /*     classFormat.setFontWeight(QFont::Bold);
       classFormat.setForeground(Qt::darkMagenta);
       classRule.pattern = QRegExp("\\bQ[A-Za-z]+\\b");
       classRule.format = classFormat;
       highlightingRules.append(classRule);
*/
       //operatorFormat.setFontWeight(QFont::Bold);
       operatorFormat.setForeground(Qt::red);
       operatorRule.pattern = QRegExp("([\\*|\\+|\\-|\\/|\\%]){1}");
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


       //System function call
       systemFunctionFormat.setFontWeight(QFont::Bold);
       systemFunctionFormat.setForeground(Qt::red);
       systemFunctionRule.pattern = QRegExp("\\$[a-zA-Z]+\\b");
       systemFunctionRule.format = systemFunctionFormat;
       highlightingRules.append(systemFunctionRule);
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
       highlightingRules.append(quotationRule);

       //Number format
       numberFormat.setForeground(Qt::black);
       numberFormat.setFontWeight(QFont::Bold);
       decimalNumberRule.pattern = QRegExp("\\b[0-9]+\\b");
       decimalNumberRule.format = numberFormat;
       highlightingRules.append(decimalNumberRule);

       //Hex Number format
       hexNumberRule.pattern = QRegExp("\\b0[xX][0-9a-fA-F]+\\b");
       hexNumberRule.format = numberFormat;

       //identifier format

       identifierFormat.setForeground(Qt::blue);
       identifierRule.pattern = QRegExp("[_a-zA-Z][_a-zA-Z0-9]{0,30}");
       identifierRule.format = keywordFormat;

    //  highlightingRules.append(identifierRule);

       //blank characters format
   //    blankFormat.setForeground(Qt::green);
  //     blankFormat.setFontWeight(QFont::Bold);
  //     blankRule.pattern = QRegExp("[a-zA-Z0-9+-*/,./_]+");
   //    blankRule.pattern = QRegExp("/^$|\s+/");


  //     blankRule.format = defaultFormat;
    //   highlightingRules.append(blankRule);

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
/*
void MySyntaxHighlighter::highlightBlock(const QString &text)
{
    QTextStream out(stdout);
    int index;

    setFormat(0,text.length(),defaultFormat);
    QRegExp blankexpression(blankRule.pattern);
           index = blankexpression.indexIn(text);
           while (index >= 0) {
                 out<< "errorrrrrrrrrrr text matched changed!!" <<endl;
               int length = blankexpression.matchedLength();
               setFormat(index, length,blankRule.format);
               index = blankexpression.indexIn(text, index + length);
           }

    foreach (const HighlightingRule &rule, highlightingRules) {
        QRegExp expression(rule.pattern);
        int index = expression.indexIn(text);
        while (index >= 0) {
           // out<< "datatypes !!" <<endl;

            int length = expression.matchedLength();
            setFormat(index, length, rule.format);
            index = expression.indexIn(text, index + length);
        }
    }


    QRegExp includerexpression(includeRule.pattern);
    int x = 0;
index = includerexpression.indexIn(text);
while (index >= 0) {
     out<< "error text matched changed!!" <<endl;
    int length = includerexpression.matchedLength();
    setFormat(index, length, includeRule.format);
    index = includerexpression.indexIn(text, index + length);
   return;
}
//if(x==1) return;

        QRegExp numberexpression(decimalNumberRule.pattern);
    index = numberexpression.indexIn(text);
    while (index >= 0) {
        int length = numberexpression.matchedLength();
        setFormat(index, length, decimalNumberRule.format);
        index = numberexpression.indexIn(text, index + length);
    }

        QRegExp hexnumberexpression(hexNumberRule.pattern);
    index = hexnumberexpression.indexIn(text);
    while (index >= 0) {
      int length = hexnumberexpression.matchedLength();
      setFormat(index, length, hexNumberRule.format);
      index = hexnumberexpression.indexIn(text, index + length);
    }
        QRegExp functionNameexpression(functionNameRule.pattern);
    index = functionNameexpression.indexIn(text);
    while (index >= 0) {
        int length = functionNameexpression.matchedLength();
        setFormat(index, length, functionNameRule.format);
        index = functionNameexpression.indexIn(text, index + length);
    }
    QRegExp initVariableExpression(initVariableRule.pattern);
    index = initVariableExpression.indexIn(text);
    while (index >= 0) {
    int length = initVariableExpression.matchedLength();
    QString pom = text.right(text.length() - index).left(length);
    QRegExp variableExpression(variableRule.pattern);
    int varindex = variableExpression.indexIn(pom);
    //out<<"pom: "<<pom<<endl;
    while(varindex>=0)
    {
        int varlength = variableExpression.matchedLength();
        out<< "variable index: "<<varindex <<endl;
        out<< "variable length: "<<varlength <<endl;
        setFormat(varindex,varlength,variableRule.format);
        varindex = variableExpression.indexIn(pom, varindex+varlength);
    }
 //   setFormat(index, length, initVariableRule.format);
    index = initVariableExpression.indexIn(text, index + length);
}


foreach (const HighlightingRule &rule, highlightingRules) {
    QRegExp expression(rule.pattern);
    int index = expression.indexIn(text);
    while (index >= 0) {
       // out<< "datatypes !!" <<endl;

        int length = expression.matchedLength();
        setFormat(index, length, rule.format);
        index = expression.indexIn(text, index + length);
    }
}

    //highlight comment line last
  if(currentBlockState()!= 1){
    QRegExp singleLineCommentexpression(singleLineCommentRule.pattern);
    index = singleLineCommentexpression.indexIn(text);
    while (index >= 0) {
        int length = singleLineCommentexpression.matchedLength();

      if(format(index)!= quotationRule.format){
          setFormat(index, length, singleLineCommentRule.format);
        }
          index = singleLineCommentexpression.indexIn(text, index + length);
    }
}
  out<<"previous block state 1.  "<< previousBlockState()<<endl;
  out<<"Current block state 1.  "<< currentBlockState()<<endl;
   if(currentBlockState()!= 3)
   {
      // setCurrentBlockState(0);

    int startIndex = 0;
    if (previousBlockState() != 1)
        startIndex = commentStartExpression.indexIn(text);

    while (startIndex >= 0) {
        int endIndex = commentEndExpression.indexIn(text, startIndex);
        int commentLength;
        if (endIndex == -1) {
        //    setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        } else {
            commentLength = endIndex - startIndex
                            + commentEndExpression.matchedLength();
        }
        setFormat(startIndex, commentLength, multiLineCommentFormat);
        startIndex = commentStartExpression.indexIn(text, startIndex + commentLength);
    }
}
  setCurrentBlockState(2);

   out<<"previous block state 2. "<< previousBlockState()<<endl;
   setCurrentBlockState(3);

   out<<"Current block state 2. "<< currentBlockState()<<endl;

    //String highlight
        QRegExp quotationexpression(quotationRule.pattern);
    index = quotationexpression.indexIn(text);
    while (index >= 0) {
        int length = quotationexpression.matchedLength();
        if(currentBlockState()!=3)
        setFormat(index, length, quotationRule.format);
        index = quotationexpression.indexIn(text, index + length);
    }

        out<<"text :"<< text<<endl;
}

*/
QString getText(const QString &text, int from, int to)
{
    int length = text.length();
    if(to>from && to<=length)
    return text.left(to).right(to-from);//.right(from-to);
    else return "";
}

void MySyntaxHighlighter::highlightBlock(const QString &text)
{
    int textLength = text.length();
    out<<"hight light block text "<<text<<endl;
    if(text == "") countQuotion = 0;
    int index = 0;
    foreach (const HighlightingRule &rule, highlightingRules) {
        QRegExp expression(rule.pattern);
        int index = expression.indexIn(text);
        while (index >= 0) {
            int length = expression.matchedLength();
            setFormat(index, length, rule.format);
            index = expression.indexIn(text, index + length);
        }
    }


  /*  QRegExp initVariableExpression(initVariableRule.pattern);
    index = initVariableExpression.indexIn(text);
    while (index >= 0) {
    int length = initVariableExpression.matchedLength();
    QString pom = text.right(text.length() - index).left(length);
    QRegExp variableExpression(variableRule.pattern);
    int varindex = variableExpression.indexIn(pom);
    //out<<"pom: "<<pom<<endl;
    while(varindex>=0)
    {
        int varlength = variableExpression.matchedLength();
        out<< "variable index: "<<varindex <<endl;
        out<< "variable length: "<<varlength <<endl;
        setFormat(varindex,varlength,variableRule.format);
        varindex = variableExpression.indexIn(pom, varindex+varlength);
    }
 //   setFormat(index, length, initVariableRule.format);
    index = initVariableExpression.indexIn(text, index + length);
}
*/


    foreach (const QString &datatype, datatypes) {
    int index = -1;
    QRegExp initVariableExpression("\\b"+datatype+"\\b");
    index = initVariableExpression.indexIn(text);
   // out<<datatype<< "index: "<<index <<endl;
    while (index >= 0) {
        int indexOfSemicolon=-1;
        for(int i = index; i<text.length();i++)
        {
            if(text.at(i)==';') {
      //          out<<"asdfadfasdfdaaaaaaaaaaa";
                indexOfSemicolon = i;
                break;
            }
        }
     QString workingText = getText(text,index,text.length());
        if(indexOfSemicolon != -1)
     {
         workingText =getText(text,index,indexOfSemicolon);
        }
 /*      out<<"length text:" <<text.length()<<endl;
        out<<"working text:" << workingText<<" index "<<index<<" index of ; "<<indexOfSemicolon<<endl;
*/
        int length = initVariableExpression.matchedLength();
    int affterDatatypeIndex = index+datatype.length();
//    QString pom = text.right(text.length() - affterDatatypeIndex-1).left(length+1);
    QString pom = workingText.right(workingText.length() - datatype.length());
    out<< workingText.length() - affterDatatypeIndex <<endl;

    QRegExp variableExpression(variableRule.pattern);
    int varindex = variableExpression.indexIn(pom);
  /*  out<<"pom: "<<pom<<endl;
    out<< "affter datatype index: "<<affterDatatypeIndex <<endl;
   */
    while(varindex>=0)
    {
        int varlength = variableExpression.matchedLength();
   /*     out<< "variable index: "<<varindex <<endl;
        out<< "variable length: "<<varlength <<endl;
        out<< "variable name: " <<pom.right(pom.length()-varindex).left(varlength)<<endl;
     */   QString varName = pom.right(pom.length()-varindex).left(varlength);
        if(std::find(keywords.begin(),keywords.end(),varName) == keywords.end())
        {
            if(std::find(variableNames.begin(),variableNames.end(),varName) == variableNames.end())
            variableNames.append(varName);
            setFormat(affterDatatypeIndex+varindex,varlength,variableRule.format);
        }
        boolean isFinish = false; // check semicolon char
     //   out<< affterDatatypeIndex << " " << pom.length() << " " << text.length()<<endl;
    /*    for(int i = affterDatatypeIndex-1;i<affterDatatypeIndex+pom.length()-1;i++)
         {
              //  out<< "i " << i << " text at i: " << text.at(i)<<endl;
                if(text.at(i)== ';') isFinish = true;
        }*/
        if(isFinish) break;
        varindex = variableExpression.indexIn(pom, varindex+varlength);
    }
 //   setFormat(index, length, initVariableRule.format);
    index = initVariableExpression.indexIn(text, index + length);
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
        out<<"Variable names "<<endl;
        for(QString var:variableNames)
            out<<var<<" ";

}

