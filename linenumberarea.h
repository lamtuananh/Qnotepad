#ifndef LINENUMBERAREA_H
#define LINENUMBERAREA_H
#include<textedit.h>
#include<QWidget>

class LineNumberArea : public QWidget
{
public:
    LineNumberArea(TextEdit *editor) : QWidget(editor) {
        codeEditor = editor;
    }

    QSize sizeHint() const Q_DECL_OVERRIDE {
        return QSize(codeEditor->lineNumberAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE {
        codeEditor->lineNumberAreaPaintEvent(event);
    }

private:
    TextEdit *codeEditor;
};
#endif // LINENUMBERAREA_H
