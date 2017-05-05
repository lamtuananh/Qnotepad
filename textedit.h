#ifndef TEXTEDIT_H
#define TEXTEDIT_H

//#include <QTextEdit>
#include <QtWidgets>

#include <QPlainTextEdit>
#include<QPainter>
#include<QTextBlock>
#include <mysyntaxhighlighter.h>
class QCompleter;

class TextEdit : public QPlainTextEdit
{
    Q_OBJECT

public:
    TextEdit(QWidget *parent = 0);
   // TextEdit();

    ~TextEdit();

    //completer
    void setCompleter(QCompleter *completeTool);
    QCompleter *completer() const;

    //count lines
    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();

    MySyntaxHighlighter * highlighter;
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
    void highlightLineOnCusor();
    void updateLineNumberArea(const QRect &, int);


 public slots:
    void resetHighlighter();
    void resetCompleter();
signals:
    void activateResetHighlighter();
    void activateUpdateCompleter();


private:
    QString textUnderCursor() const;

    QWidget *lineNumberArea; // count line variable

public:
    QCompleter *completeTool; //GUI class use to show popup for word menu to complete.
    QStringList wordList; // word list for complete tool
    QStringListModel *model; // the model used for completerTool variable.
};

#endif // TEXTEDIT_H
