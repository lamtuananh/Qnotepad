#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QtWidgets>
#include <QWidget>
#include <QtCore>
#include <QtGui>
#include <QLayout>
class MyWindow :public QHBoxLayout
{
public:
    MyWindow();

public:
    QVBoxLayout *vLayout;
    QFileSystemModel *dirModel;
    QTreeView *treeView;
    QFileSystemModel *fileModel;
    QString currentFileName;
    QString *currentFileContent;
    QTextEdit * textEdit;
};

#endif // MYWINDOW_H
