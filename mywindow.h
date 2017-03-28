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
#include <QCompleter>
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
//    TextEdit *textEdit;
//    MySyntaxHighlighter *highlighter;

    struct EditorComponent{
        TextEdit *textEdit;
        MySyntaxHighlighter *highlighter;
    };
    EditorComponent *editor;

    QMainWindow *mainWidget,*filesWidget;
    QDockWidget *dockWidget;
    QListWidget *customerList;
    QListWidget *paragraphsList;
    void createDockWindows();

    QAbstractItemModel *modelFromFile(const QString& fileName);

public slots:
    void setHighlighter();
    void resetCompleter();
signals:
    void activateUpdateCompleter();

private:
    QStringList words;
    QCompleter *completer;

};

#endif // MYWINDOW_H
