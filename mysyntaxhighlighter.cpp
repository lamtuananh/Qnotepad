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

           variableRule.pattern = QRegExp("[a-zA-Z]+[_a-zA-Z0-9]*");
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
           octalNumberRule.pattern=QRegExp("\\b[0-9]+'h[0-9a-fA-F]+\\b");
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
        int index = 0;
        foreach (const HighlighRule &rule, highlightingRules) {
            QRegExp expression(rule.pattern);// call regular expression of term category
            int index = expression.indexIn(text); // get index of first string matched with expression, is -1 if not exist.
            while (index >= 0) { //if exist a string matched with expression
                int length = expression.matchedLength(); // get length of matched string
                setFormat(index, length, rule.format); // set detected string with initialized format for the category
                index = expression.indexIn(text, index + length); //get index of next matched string with expression.
            }
        }


    //start detect variables and highlight them
        foreach (const QString &datatype, datatypes) {
        int index = -1;
        QRegExp initVariableExpression=QRegExp("\\b"+datatype+"\\b"); //initialize regular expression to detect data type keyword
        index = initVariableExpression.indexIn(text); //get index of detected data type keyword
        while (index >= 0) {
            int indexOfSemicolon=-1;
            for(int i = index; i<text.length();i++) //get index of first semicolon char after detected data type keyword.
            {
                if(text.at(i)==';') {
                    indexOfSemicolon = i;
                    break;
                }
            }
         QString workingText = getText(text,index,text.length()); //get substring from datatype keyword to index of semicolon
            if(indexOfSemicolon != -1)
         {
             workingText =getText(text,index,indexOfSemicolon);
            }
           int length = initVariableExpression.matchedLength();
        QString pom = workingText.right(workingText.length() - datatype.length()); //get substring from after datatype keyword until semicolon
        QRegExp variableExpression(variableRule.pattern); //set regular expression to detect variable
        int varindex = variableExpression.indexIn(pom); //
        while(varindex>=0)
        {
            int varlength = variableExpression.matchedLength();
          QString varName = pom.right(pom.length()-varindex).left(varlength); //get detected variable name as substring from
            if(std::find(keywords.begin(),keywords.end(),varName) == keywords.end()) //if the detected variable name is not same as any keyword
            {
                if(std::find(variableNames.begin(),variableNames.end(),varName) == variableNames.end()) // if the detected variable name is not the same with any detected variable before
                {
                    if(datatype.compare("parameter")==0) //if is parameter variable
                    {
                        parameterNames.append(varName); //add to parameter name
                    }
                        else
                        if(datatype.compare("input")==0) //if is input variable
                        inputOutputNames.append(varName);
                        else
                            if(datatype.compare("output")==0) //if is output variable
                            inputOutputNames.append(varName);
                            else
                            variableNames.append(varName); // is normal variable
                }
            }
            varindex = variableExpression.indexIn(pom, varindex+varlength);
        }
        index = initVariableExpression.indexIn(text, index + length);
    }
    }
        //highlight variable name
        foreach (const QString &variable, variableNames) {
            QRegExp expression =QRegExp("\\b"+variable+"\\b");
            int index = expression.indexIn(text);
            while (index >= 0) {
                int length = expression.matchedLength();
                setFormat(index, length, variableFormat);
                index = expression.indexIn(text, index + length);
            }
        }
        //highlight parameter variables
        foreach (const QString &parameter, parameterNames) {

            QRegExp expression =QRegExp("\\b"+parameter+"\\b");
            int index = expression.indexIn(text);
            while (index >= 0) {
                int length = expression.matchedLength();
                setFormat(index, length, parameterFormat);
                index = expression.indexIn(text, index + length);
            }
        }
        //highlight input output variables.
        foreach (const QString &inputoutput, inputOutputNames) {
            QRegExp expression =QRegExp("\\b"+inputoutput+"\\b");
            int index = expression.indexIn(text);
            while (index >= 0) {
                int length = expression.matchedLength();
                setFormat(index, length, ioFormat);
                index = expression.indexIn(text, index + length);
            }
        }

       QRegExp singleLineCommentexpression(singleLineCommentRule.pattern);//regular expression to detect single comment
        index = singleLineCommentexpression.indexIn(text);
        while (index >= 0) {
            int length = singleLineCommentexpression.matchedLength();
            int coutQuotion = 0;
            for(int i=0;i<=index;i++) //check the detected single comment is in ""
                if(text.at(i) == '"') coutQuotion++;//cout mount of " character from start to index of detected //
             if(coutQuotion%2 == 0) //if count of " chararacter is par
                 setFormat(index, length, singleLineCommentRule.format); //set comment format to text.
              index = singleLineCommentexpression.indexIn(text, index + length);
        }

        setCurrentBlockState(OUTOFCOMMENT);
            int startIndex = 0;
            if (previousBlockState() != INCOMMENT) //if previous block is not in comment
                startIndex = commentStartExpression.indexIn(text);

            int coutQuotion = 0;
            for(int i=0;i<startIndex;i++)
                if(text.at(i) == '"') coutQuotion++;

            while (startIndex >= 0 && coutQuotion%2 ==0) {
                int endIndex = commentEndExpression.indexIn(text, startIndex);
                int commentLength;
                if (endIndex == -1) {
                    setCurrentBlockState(INCOMMENT);
                    commentLength = text.length() - startIndex;

                } else {
                    commentLength = endIndex - startIndex
                                    + commentEndExpression.matchedLength();
                }
                 if(previousBlockState()!= INSTRING) setFormat(startIndex, commentLength, multiLineCommentFormat);
                startIndex = commentStartExpression.indexIn(text, startIndex + commentLength);
            }
    }

    void MySyntaxHighlighter::reset()
    {
        variableNames.clear();
        parameterNames.clear();
        inputOutputNames.clear();
    }
