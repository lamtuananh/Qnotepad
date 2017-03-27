#ifndef MYTEXTEDIT_H
#define MYTEXTEDIT_H

#include<QPlainTextEdit>
#include<QPainter>
#include<QTextBlock>
#include <QCompleter>
class QCompleter;
class CodeEditor : public QPlainTextEdit
{
    Q_OBJECT

public:
    CodeEditor(QWidget *parent = 0);
     ~CodeEditor();


    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();


    void setCompleter(QCompleter *c); //for autocompleter
        QCompleter *completer() const;//for autocompleter

protected:
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
    void keyPressEvent(QKeyEvent *e) override;
    void focusInEvent(QFocusEvent *e) override;

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &, int);
     void insertCompletion(const QString &completion); // for autocompleter

private:
    QWidget *lineNumberArea;

    QString textUnderCursor() const;//for autocompleter


    QCompleter *c;//for autocompleter

};

#endif // MYTEXTEDIT_H
