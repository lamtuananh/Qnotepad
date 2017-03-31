#ifndef MYWINDOW_H
#define MYWINDOW_H
#include <QtWidgets>
#include <QWidget>
#include <QDockWidget>
#include <QtCore>
#include <QtGui>
#include <QLayout>
#include <QCompleter>
#include <mysyntaxhighlighter.h>
#include <textedit.h>
class MyWindow :public QGridLayout
{
  //  Q_OBJECT
public:
    MyWindow( QWidget *parent);

public:
    QVBoxLayout *vLayout;
    QFileSystemModel *dirModel;
    QTreeView *treeView;
    QFileSystemModel *fileModel;
    QListView *listView;
    QString currentFileName;
    QString *currentFileContent;

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
    void on_treeView_clicked(QModelIndex index );
signals:
    void activateUpdateCompleter();


private:
    QStringList words;
    QCompleter *completer;

};

#endif // MYWINDOW_H
