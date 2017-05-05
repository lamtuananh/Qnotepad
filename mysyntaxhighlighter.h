#ifndef MYSYNTAXHIGHLIGHTER_H
#define MYSYNTAXHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QVector>
//#include <textedit.h>
class MySyntaxHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT
    public:
     MySyntaxHighlighter(QTextDocument *parent = 0);
   // MySyntaxHighlighter(TextEdit *parent = 0);
 //   void highlightBlock(const QString &text);

protected:
    void highlightBlock(const QString &text) Q_DECL_OVERRIDE;
public :
  //  TextEdit *textEdit;
    QMap<QString,QFont> mapFont;
    QMap<QString,QString> mapPattern;
    QVector<QString> vector;
    QVector<QString> datatypes;
//    QVector<QString> keywords;
    QStringList keywords;
    QStringList systemTaskFunction;
    QStringList variableNames,parameterNames,inputOutputNames;
//    QVector<QString> variableNames;

    QVector<QString> classNames;
    QVector<QString> moduleNames;
    QVector<QString> functionNames;
    //QVector<QString> variableNames;




    QString modulePattern;
    QString commandPattern;

    struct HighlighRule
        {
            QRegExp pattern;
            QTextCharFormat format;
        };

     QTextCharFormat defaultFormat;
    QVector<HighlighRule> highlightingRules;


        QRegExp commentStartExpression;
        QRegExp commentEndExpression;

        QTextCharFormat keywordFormat;
        HighlighRule keywordRule;

        QTextCharFormat includeFormat;
        HighlighRule includeRule;

        QTextCharFormat parameterFormat;
        HighlighRule parameterRule;

        QTextCharFormat ioFormat;
        HighlighRule ioRule;


        QTextCharFormat defineFormat;
        HighlighRule defineRule;

        QTextCharFormat variableFormat;
        HighlighRule initVariableRule;
        HighlighRule variableRule;

        QTextCharFormat operatorFormat;
        HighlighRule operatorRule;

        QTextCharFormat classFormat;
        HighlighRule classRule;

        QTextCharFormat singleLineCommentFormat;
        HighlighRule singleLineCommentRule;

        QTextCharFormat multiLineCommentFormat;
        HighlighRule multiLineCommentRule;

        QTextCharFormat quotationFormat;
        HighlighRule quotationRule;

        QTextCharFormat functionNameFormat;
        HighlighRule functionNameRule;

        QTextCharFormat numberFormat;
        HighlighRule decimalNumberRule,hexNumberRule,binaryNumberRule,realNumberRule,octalNumberRule;

        QTextCharFormat identifierFormat;
        HighlighRule identifierRule;


        QTextCharFormat systemFunctionFormat;
        HighlighRule systemFunctionRule;

        QTextCharFormat blankFormat;
        HighlighRule blankRule;


        QTextCharFormat functionStart;
        QTextCharFormat functionEnd;
        QRegExp functionStartExpression;
        QRegExp functionEndExpression;

        QTextCharFormat moduleStart;
        QTextCharFormat moduleEnd;

        QVector<QRegExp> codeBlocks;
        QRegExp moduleBlock,functionBlock,beginEndBlock;


        QRegExp moduleStartExpression;
        QRegExp moduleEndExpression;


        QTextCharFormat beginStart;
        QTextCharFormat beginEnd;

public:
void reset();
};

#endif // MYSYNTAXHIGHLIGHTER_H
