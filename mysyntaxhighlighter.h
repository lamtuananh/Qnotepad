#ifndef MYSYNTAXHIGHLIGHTER_H
#define MYSYNTAXHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QVector>
#include <textedit.h>
class MySyntaxHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT
    public:
     MySyntaxHighlighter(QTextDocument *parent = 0);
   // MySyntaxHighlighter(TextEdit *parent = 0);
 //   void highlightBlock(const QString &text);

protected:
    void highlightBlock(const QString &text) Q_DECL_OVERRIDE;
private :
  //  TextEdit *textEdit;
    QMap<QString,QFont> mapFont;
    QMap<QString,QString> mapPattern;
    QVector<QString> vector;
    QVector<QString> datatypes;
    QVector<QString> keywords;

    QVector<QString> variableNames;
    QVector<QString> classNames;
    QVector<QString> moduleNames;
    QVector<QString> functionNames;
    //QVector<QString> variableNames;




    QString modulePattern;
    QString commandPattern;

    struct HighlightingRule
        {
            QRegExp pattern;
            QTextCharFormat format;
        };

     QTextCharFormat defaultFormat;
    QVector<HighlightingRule> highlightingRules;


        QRegExp commentStartExpression;
        QRegExp commentEndExpression;

        QTextCharFormat keywordFormat;
        HighlightingRule keywordRule;

        QTextCharFormat includeFormat;
        HighlightingRule includeRule;

        QTextCharFormat defineFormat;
        HighlightingRule defineRule;

        QTextCharFormat variableFormat;
        HighlightingRule initVariableRule;
        HighlightingRule variableRule;

        QTextCharFormat operatorFormat;
        HighlightingRule operatorRule;

        QTextCharFormat classFormat;
        HighlightingRule classRule;

        QTextCharFormat singleLineCommentFormat;
        HighlightingRule singleLineCommentRule;

        QTextCharFormat multiLineCommentFormat;
        HighlightingRule multiLineCommentRule;

        QTextCharFormat quotationFormat;
        HighlightingRule quotationRule;

        QTextCharFormat functionNameFormat;
        HighlightingRule functionNameRule;

        QTextCharFormat numberFormat;
        HighlightingRule decimalNumberRule,hexNumberRule,binaryNumberRule,realNumberRule,octalNumberRule;

        QTextCharFormat identifierFormat;
        HighlightingRule identifierRule;


        QTextCharFormat systemFunctionFormat;
        HighlightingRule systemFunctionRule;

        QTextCharFormat blankFormat;
        HighlightingRule blankRule;


        QTextCharFormat functionStart;
        QTextCharFormat functionEnd;
        QRegExp functionStartExpression;
        QRegExp functionEndExpression;

        QTextCharFormat moduleStart;
        QTextCharFormat moduleEnd;
        QRegExp moduleStartExpression;
        QRegExp moduleEndExpression;

        QTextCharFormat beginStart;
        QTextCharFormat beginEnd;



};

#endif // MYSYNTAXHIGHLIGHTER_H
