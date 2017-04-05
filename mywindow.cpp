#include "mywindow.h"
#include <iostream>
#include <QTextStream>
#include <QModelIndex>
#include <QDir>

MyWindow::MyWindow( QWidget *parent)
{

    dockWidget = new QDockWidget;
    mainWidget = new QMainWindow();
    filesWidget = new QMainWindow();
    listView = new QListView(parent);
    //get current Project path
    QString sPath;
//    sPath = "G:/";
    sPath =QDir::currentPath();
  //  std::cout << sPath.toStdString();
    sPath = QString("C:\\Users\\a.lam.tuan\\Documents\\build-Qnotepad-Desktop_Qt_5_7_0_MSVC2015_64bit-Debug\\debug");
    dirModel = new QFileSystemModel(filesWidget);
    dirModel->setRootPath(sPath);
    treeView = new QTreeView();
    treeView->setModel(dirModel);
    sPath = "C:/";

    fileModel = new QFileSystemModel();
    fileModel->setFilter(QDir::NoDotAndDotDot | QDir::NoDotDot|QDir::AllDirs);
   // sPath = "C:/Users/a.lam.tuan";
  //  sPath = QString("C:/Users/a.lam.tuan/Documents/build-Qnotepad-Desktop_Qt_5_7_0_MSVC2015_64bit-Debug/debug");

    fileModel->setRootPath(sPath);
    listView->setModel(fileModel);

    //textEdit= new TextEdit();
    editor = new EditorComponent();
    editor->textEdit = new TextEdit();
    editor->highlighter = new MySyntaxHighlighter(editor->textEdit->document());
    editor->textEdit->highlighter = editor->highlighter;
    editor->highlighter->setDocument(editor->textEdit->document());
    QObject::connect(editor->textEdit,SIGNAL(activateResetHighlighter()),editor->textEdit,SLOT(resetHighlighter()));


    createDockWindows();
    //testButton = new QPushButton("Start check !!!");
    this->addWidget(filesWidget,0,0);
    this->addWidget(mainWidget,0,1,1,3);
   // this->addWidget(treeView,0,4);
    QObject::connect(treeView,SIGNAL(clicked(QModelIndex)),this, SLOT(on_treeView_clicked(index)));


    completer = new QCompleter(this);
    completer->setModel(modelFromFile(":/resources/keywords.txt"));
    completer->setModelSorting(QCompleter::CaseInsensitivelySortedModel);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setWrapAround(false);
    editor->textEdit->setCompleter(completer);
     QObject::connect(editor->textEdit,SIGNAL(activateUpdateCompleter()),editor->textEdit,SLOT(resetCompleter()));

}
void MyWindow::createDockWindows()
{
    QDockWidget *dock = new QDockWidget(tr("Project Explorer"), mainWidget);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea | Qt::BottomDockWidgetArea|Qt::TopDockWidgetArea);
    dock->setWidget(listView);
    mainWidget->addDockWidget(Qt::LeftDockWidgetArea, dock);
    dock = new QDockWidget(tr("Working file"), filesWidget);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea | Qt::BottomDockWidgetArea|Qt::TopDockWidgetArea);
    dock->setWidget(editor->textEdit);
    filesWidget->addDockWidget(Qt::RightDockWidgetArea, dock);
}
void MyWindow::on_treeView_clicked(QModelIndex index)
{
    QTextStream out(stdout);
    QString sPath = dirModel->fileInfo(index).absoluteFilePath();
    out<<"sPath"<<endl;
    listView->setRootIndex(fileModel->setRootPath(sPath));
}

/**
 * @brief updateWordList
 * update words for autocompletion
 */
void updateWordList()
{
}
/**
 * @brief MyWindow::resetCompleter
 * reset completer with new words list
 */
void MyWindow::resetCompleter()
{
}

/**
 * @brief MyWindow::setHighlighter
 * reset highlighter
 */
void MyWindow::setHighlighter()
{
    MySyntaxHighlighter *highlighter;
    highlighter = new MySyntaxHighlighter(this->editor->textEdit->document());
    highlighter->setDocument(this->editor->textEdit->document());
}
QAbstractItemModel *MyWindow::modelFromFile(const QString& fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly))
        return new QStringListModel(completer);

#ifndef QT_NO_CURSOR
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
#endif
   // QStringList words;
    // QTextStream out(stdout);
    words.clear();
    while (!file.atEnd()) {
        QByteArray line = file.readLine();
     //  out<< line << "  "<<endl;
        if (!line.isEmpty())
            words << line.trimmed();
    }
    if(editor->highlighter->variableNames.length()>0)
    {
        for(QString x: editor->highlighter->variableNames)
            words.append(x);
    }

#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif
    return new QStringListModel(words, completer);
}

