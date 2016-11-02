#ifndef MYSYNTAXHIGHLIGHTER_H
#define MYSYNTAXHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QVector>
class MySyntaxHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT
    public:
   explicit MySyntaxHighlighter(QObject *parent = 0);
    void highlightBlock(const QString &text);

private :
    QMap<QString,QFont> mapFont;
    QMap<QString,QString> mapPattern;
    QVector<QString> vector;
    QString modulePattern;
    QString commandPattern;

signals:
public slots:
};

#endif // MYSYNTAXHIGHLIGHTER_H