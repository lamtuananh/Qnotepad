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
};

#endif // MYWINDOW_H
