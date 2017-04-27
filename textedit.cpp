
#include "textedit.h"
#include <QCompleter>
#include <QKeyEvent>
#include <QAbstractItemView>
#include <QtDebug>
#include <QApplication>
#include <QModelIndex>
#include <QAbstractItemModel>
#include <QScrollBar>

//#include <iostream>
#include <linenumberarea.h>
//#include <QTextStream>
class QAbstractItemModel;
class QComboBox;
class QCompleter;
class QLabel;
class QLineEdit;
class QProgressBar;

class TextEdit;
boolean completerInprogress=false;
TextEdit::TextEdit(QWidget *parent)
: QPlainTextEdit(parent), c(0)

//TextEdit::TextEdit()
{
   // wordList = new QStringList();
    wordList.append("module");
    wordList.append("endmodule");
    model = new QStringListModel(wordList,c);
    setLineWrapMode(QPlainTextEdit::NoWrap);
    lineNumberArea = new LineNumberArea(this);
    connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
    connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateLineNumberArea(QRect,int)));
    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightLineOnCusor()));
    QFont font = QFont("Courier",12);
    this->setFont(font);
    updateLineNumberAreaWidth(0);
    highlightLineOnCusor();

}

TextEdit::~TextEdit()
{
}

void TextEdit::resetHighlighter()
{
    highlighter->reset();
    highlighter->setDocument(this->document());
}

QString text;
void TextEdit::resetCompleter()
{
    QTextStream out(stdout);
    wordList.clear();
    text= this->document()->toPlainText();
    QRegExp expression("\\b[_a-zA-Z]+\\b");
    int index = expression.indexIn(text);

    while (index >= 0) {
        int length = expression.matchedLength();
        QString word = text.mid(index,length);
           if(!wordList.contains(word))
               wordList.append(word);
        index = expression.indexIn(text, index + length);
    }
    foreach(QString s ,highlighter->keywords)
    if(!wordList.contains(s))wordList.append(s);
    foreach(QString s ,highlighter->systemTaskFunction)
    if(!wordList.contains(s))wordList.append(s);
    wordList.sort();
    QStringListModel *model = (QStringListModel*)(c->model());
        model->setStringList(wordList);
}

void TextEdit::setCompleter(QCompleter *completer)
{
    if (c)
        QObject::disconnect(c, 0, this, 0);

    c = completer;

    if (!c)
        return;

    c->setWidget(this);
    c->setCompletionMode(QCompleter::PopupCompletion);
    c->setCaseSensitivity(Qt::CaseInsensitive);
    QObject::connect(c, SIGNAL(activated(QString)),
                     this, SLOT(insertCompletion(QString)));
}

QCompleter *TextEdit::completer() const
{
    return c;
}

void TextEdit::insertCompletion(const QString& completion)
{
    if (c->widget() != this)
        return;
    QTextCursor tc = textCursor();
    int extra = completion.length() - c->completionPrefix().length();
    tc.movePosition(QTextCursor::Left);
    tc.movePosition(QTextCursor::EndOfWord);
    tc.insertText(completion.right(extra));
    setTextCursor(tc);
}

QString TextEdit::textUnderCursor() const
{
    QTextCursor tc = textCursor();
    tc.select(QTextCursor::WordUnderCursor);
    return tc.selectedText();
}

void TextEdit::focusInEvent(QFocusEvent *e)
{
    if (c)
        c->setWidget(this);
    QPlainTextEdit::focusInEvent(e);
}

void TextEdit::keyPressEvent(QKeyEvent *e)
{
    if (c && c->popup()->isVisible()) {
        completerInprogress = true;

        // The following keys are forwarded by the completer to the widget
       switch (e->key()) {
       case Qt::Key_Enter:
       case Qt::Key_Return:
       case Qt::Key_Escape:
       case Qt::Key_Tab:
       case Qt::Key_Backtab:
            e->ignore();
            return; // let the completer do default behavior
       default:
           break;
       }
    }

    bool isShortcut = ((e->modifiers() & Qt::ControlModifier) && e->key() == Qt::Key_E); // CTRL+E
    if (!c || !isShortcut) // do not process the shortcut when we have a completer
        QPlainTextEdit::keyPressEvent(e);

    const bool ctrlOrShift = e->modifiers() & (Qt::ControlModifier | Qt::ShiftModifier);
    if (!c || (ctrlOrShift && e->text().isEmpty()))
    {
        return;
}
    static QString eow("~!@#$%^&*()_+{}|:\"<>?,./;'[]\\-="); // end of word
    bool hasModifier = (e->modifiers() != Qt::NoModifier) && !ctrlOrShift;
    QString completionPrefix = textUnderCursor();

    if(eow.contains(e->key())||e->key()==Qt::Key_Enter ||e->key()==Qt::Key_Space )
    {
        resetCompleter();
    //    out<<"hello worlds"<<endl;
    }
        if (!isShortcut && (hasModifier || e->text().isEmpty()|| completionPrefix.length() < 3
                      || eow.contains(e->text().right(1)))) {
        c->popup()->hide();

   //     out<<"check 1"<<endl;
         return;
    }

  //  out<<"check 2"<<endl;
    if (completionPrefix != c->completionPrefix()) {
        c->setCompletionPrefix(completionPrefix);
        c->popup()->setCurrentIndex(c->completionModel()->index(0, 0));
   //     out<<"check 3"<<endl;

    }


    QRect cr = cursorRect();
    cr.setWidth(c->popup()->sizeHintForColumn(0)
                + c->popup()->verticalScrollBar()->sizeHint().width());
    c->complete(cr); // popup it up!
}



int TextEdit::lineNumberAreaWidth()
{
    int digits = 1;
    int max = qMax(1, blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }
    digits++;
    int space = 6 + fontMetrics().width(QLatin1Char('9')) * digits ;

    return space;
}
void TextEdit::updateLineNumberAreaWidth(int /* newBlockCount */)
{
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}
void TextEdit::updateLineNumberArea(const QRect &rect, int dy)
{
    if (dy)
        lineNumberArea->scroll(0, dy);
    else
        lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

    if (rect.contains(viewport()->rect()))
        updateLineNumberAreaWidth(0);
}
void TextEdit::resizeEvent(QResizeEvent *e)
{
    QPlainTextEdit::resizeEvent(e);


    QRect cr = contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}
void TextEdit::highlightLineOnCusor()
{
    QList<QTextEdit::ExtraSelection> extraSelections;

    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;

        QColor lineColor = QColor(Qt::yellow).lighter(160);

        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }

    setExtraSelections(extraSelections);
}
void TextEdit::lineNumberAreaPaintEvent(QPaintEvent *event)
{
    QPainter painter(lineNumberArea);
    painter.fillRect(event->rect(), Qt::lightGray);
    QTextBlock block = firstVisibleBlock();
     int blockNumber = block.blockNumber();
     int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
     int bottom = top + (int) blockBoundingRect(block).height();
     while (block.isValid() && top <= event->rect().bottom()) {
         if (block.isVisible() && bottom >= event->rect().top()) {
             QString number = QString::number(blockNumber + 1);
             painter.setPen(Qt::black);
             painter.drawText(0, top, lineNumberArea->width(), fontMetrics().height(),
                              Qt::AlignCenter, number);
         }

         block = block.next();
         top = bottom;
         bottom = top + (int) blockBoundingRect(block).height();
         ++blockNumber;
     }
 }


