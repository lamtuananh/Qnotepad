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
        QTextCharFormat classFormat;
        QTextCharFormat singleLineCommentFormat;
        QTextCharFormat multiLineCommentFormat;
        QTextCharFormat quotationFormat;
        QTextCharFormat functionFormat;


signals:
public slots:
};

#endif // MYSYNTAXHIGHLIGHTER_H
