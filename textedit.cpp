
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
: QPlainTextEdit(parent), completeTool(0)

//TextEdit::TextEdit()
{
   // wordList = new QStringList();
    wordList.append("module");
    wordList.append("endmodule");
    model = new QStringListModel(wordList,completeTool);
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
/**
 * @brief TextEdit::resetCompleter
 * update new word of remove deleted words from autocomplete word list
 */
void TextEdit::resetCompleter()
{
    wordList.clear(); //clear word list first
    text= this->document()->toPlainText(); // get text from editor
    QRegExp expression("\\b[A-Za-z_0-9]+\\b"); // define regular expression for word
    int index = expression.indexIn(text); //find index match with reg. expression

    while (index >= 0) {
        int length = expression.matchedLength();
        QString word = text.mid(index,length); //get word
           if(!wordList.contains(word)) // if the found word is not in word list
               wordList.append(word); //add it to word list
        index = expression.indexIn(text, index + length);
    }

    foreach(QString s ,highlighter->keywords) // for each keywords
    if(!wordList.contains(s))wordList.append(s); // add to word list
    foreach(QString s ,highlighter->systemTaskFunction) // same as keywords
    if(!wordList.contains(s))wordList.append(s); //system function tasks added to word list
    wordList.sort(); // sort word list for completer
    QStringListModel *model = (QStringListModel*)(completeTool->model()); //update wordlist of complete tool.
        model->setStringList(wordList);
}

void TextEdit::setCompleter(QCompleter *completer)
{
    if (completeTool)
        QObject::disconnect(completeTool, 0, this, 0);

    completeTool = completer;

    if (!completeTool)
        return;

    completeTool->setWidget(this);
    completeTool->setCompletionMode(QCompleter::PopupCompletion);
    completeTool->setCaseSensitivity(Qt::CaseSensitive);
    QObject::connect(completeTool, SIGNAL(activated(QString)),
                     this, SLOT(insertCompletion(QString)));
}

QCompleter *TextEdit::completer() const
{
    return completeTool;
}

void TextEdit::insertCompletion(const QString& completion)
{
    if (completeTool->widget() != this)
        return;
    QTextCursor tc = textCursor();
    int extra = completion.length() - completeTool->completionPrefix().length();
    tc.movePosition(QTextCursor::Left);
    tc.movePosition(QTextCursor::EndOfWord);
    tc.insertText(completion.right(extra));
    setTextCursor(tc);
}
/**
 * @brief TextEdit::textUnderCursor
 * get text typed by user under cursor
 * @return
 */
QString TextEdit::textUnderCursor() const
{
    QTextCursor tc = textCursor();
    tc.select(QTextCursor::WordUnderCursor);
    return tc.selectedText();
}

void TextEdit::focusInEvent(QFocusEvent *e)
{
    if (completeTool)
        completeTool->setWidget(this);
    QPlainTextEdit::focusInEvent(e);
}

void TextEdit::keyPressEvent(QKeyEvent *e)
{
    if (completeTool && completeTool->popup()->isVisible()) {
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
    if (!completeTool || !isShortcut) // do not process the shortcut when we have a completer
        QPlainTextEdit::keyPressEvent(e);

    const bool ctrlOrShift = e->modifiers() & (Qt::ControlModifier | Qt::ShiftModifier);
    if (!completeTool || (ctrlOrShift && e->text().isEmpty()))
    {
        return;
}
    static QString eow("~!@#$%^&*()_+{}|:\"<>?,./;'[]\\-="); // end of word
    bool hasModifier = (e->modifiers() != Qt::NoModifier) && !ctrlOrShift;
    QString completionPrefix = textUnderCursor();

    if(eow.contains(e->key())||e->key()==Qt::Key_Enter ||e->key()==Qt::Key_Space )
    {
        resetCompleter();
    }
        if (!isShortcut && (hasModifier || e->text().isEmpty()|| completionPrefix.length() < 2
                      || eow.contains(e->text().right(1)))) {
        completeTool->popup()->hide();
         return;
    }

    if (completionPrefix != completeTool->completionPrefix()) {
        completeTool->setCompletionPrefix(completionPrefix);
        completeTool->popup()->setCurrentIndex(completeTool->completionModel()->index(0, 0));
    }


    QRect cr = cursorRect();
    cr.setWidth(completeTool->popup()->sizeHintForColumn(0)
                + completeTool->popup()->verticalScrollBar()->sizeHint().width());
    completeTool->complete(cr); // popup it up!
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


