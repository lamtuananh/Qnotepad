#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QtCore>
#include <QtGui>
#include "mywindow.h"
#include <QLayout>
#include "checkthread.h"

class QAbstractItemModel;
class QComboBox;
class QCompleter;
class QLabel;
class QLineEdit;
class QProgressBar;

class TextEdit;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    CheckThread *mythread;

private slots:
    void on_actionNew_File_triggered();

    void on_actionOpen_file_triggered();

    void on_actionSave_file_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_actionSave_as_triggered();

    void on_actionShowHtml_triggered();

    void onTextEditChanged();

    void resetHighlighter();

public:
    Ui::MainWindow *ui;
    QString *mFileName;
    MyWindow *mywindow;

    //autocompleter


private:

    QAbstractItemModel *modelFromFile(const QString& fileName);
    QCompleter *completer;

};

#endif // MAINWINDOW_H
