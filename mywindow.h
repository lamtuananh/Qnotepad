#ifndef MYWINDOW_H
#define MYWINDOW_H
#include <codeedit.h>
#include <QtWidgets>
#include <QWidget>
#include <QDockWidget>
#include <QtCore>
#include <QtGui>
#include <QLayout>
#include <mysyntaxhighlighter.h>
#include <textedit.h>
class MyWindow :public QGridLayout
{
  //  Q_OBJECT
public:
    MyWindow(const QWidget *parent);

public:
    QVBoxLayout *vLayout;
    QFileSystemModel *dirModel;
    QTreeView *treeView;
    QFileSystemModel *fileModel;
    QString currentFileName;
    QString *currentFileContent;
    TextEdit *textEdit;
    MySyntaxHighlighter *highlighter;

    QVector<CodeEditor> textEditAreas;
    QTextEdit *textEdit2;
    QPushButton *testButton;
    //MySyntaxHighlighter *highlighter;
    QMainWindow *mainWidget,*filesWidget;
    QDockWidget *dockWidget;
    QTextEdit *textEdit3;
    QListWidget *customerList;
    QListWidget *paragraphsList;
    void createDockWindows();
  //  MainWindow *mainWindow;
    /*
public slots:
    void onTestButtonClicked();
*/
public slots:
    void setHighlighter();
};

#endif // MYWINDOW_H
