#ifndef TEXTEDIT_H
#define TEXTEDIT_H

//#include <QTextEdit>
#include <QPlainTextEdit>
#include<QPainter>
#include<QTextBlock>
class QCompleter;

class TextEdit : public QPlainTextEdit
{
    Q_OBJECT

public:
    TextEdit(QWidget *parent = 0);
   // TextEdit();

    ~TextEdit();

    //completer
    void setCompleter(QCompleter *c);
    QCompleter *completer() const;

    //count lines
    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();


protected:
    void keyPressEvent(QKeyEvent *e) override;
    void focusInEvent(QFocusEvent *e) override;

    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE; // count lines


private slots:
    /** autocompletion slot
     * @brief insertCompletion
     * @param completion
     */
    void insertCompletion(const QString &completion);

    /** count line slots
     * @brief updateLineNumberAreaWidth
     * @param newBlockCount
     */
    void updateLineNumberAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &, int);


private:
    QString textUnderCursor() const;

    QWidget *lineNumberArea; // count line variable

private:
    QCompleter *c;
};

#endif // TEXTEDIT_H
