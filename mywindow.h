#ifndef MYWINDOW_H
#define MYWINDOW_H
#include <codeedit.h>
#include <QtWidgets>
#include <QWidget>
#include <QtCore>
#include <QtGui>
#include <QLayout>
#include <mysyntaxhighlighter.h>
class MyWindow :public QHBoxLayout
{
  //  Q_OBJECT
public:
    MyWindow();
public:
    QVBoxLayout *vLayout;
    QFileSystemModel *dirModel;
    QTreeView *treeView;
    QFileSystemModel *fileModel;
    QString currentFileName;
    QString *currentFileContent;
    CodeEditor *textEdit;
    QTextEdit *textEdit2;
    QPushButton *testButton;
    MySyntaxHighlighter *highlighter;

  //  MainWindow *mainWindow;
//public slots:
  //  void onTextEditChanged();

};

#endif // MYWINDOW_H
