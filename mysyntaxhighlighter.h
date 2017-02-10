#ifndef MYSYNTAXHIGHLIGHTER_H
#define MYSYNTAXHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QVector>
class MySyntaxHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT
    public:
    MySyntaxHighlighter(QObject *parent = 0);
 //   void highlightBlock(const QString &text);

protected:
    void highlightBlock(const QString &text) Q_DECL_OVERRIDE;

private :
    QMap<QString,QFont> mapFont;
    QMap<QString,QString> mapPattern;
    QVector<QString> vector;
    QString modulePattern;
    QString commandPattern;

    struct HighlightingRule
        {
            QRegExp pattern;
            QTextCharFormat format;
        };
        QVector<HighlightingRule> highlightingRules;

        QRegExp commentStartExpression;
        QRegExp commentEndExpression;

        QTextCharFormat keywordFormat;
        HighlightingRule keywordRule;

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
        HighlightingRule numberRule;



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



signals:
public slots:
};

#endif // MYSYNTAXHIGHLIGHTER_H
