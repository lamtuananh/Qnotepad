#include "mywindow.h"
#include <iostream>
#include <QDir>
MyWindow::MyWindow(const QWidget *parent)
{

    //get current Project path
    QString sPath;
    sPath =QDir::currentPath();
    std::cout << sPath.toStdString();
    dirModel = new QFileSystemModel();
  //  dirModel->setFilter( QDir::Name);
    sPath = QString("C:\\Users\\a.lam.tuan\\Documents\\build-Qnotepad-Desktop_Qt_5_7_0_MSVC2015_64bit-Debug\\debug");
    dirModel->setRootPath(sPath);
    treeView = new QTreeView();
    treeView->setModel(dirModel);
 //   textEdit = new CodeEditor();
    textEdit= new TextEdit();

    dockWidget = new QDockWidget;
    mainWidget = new QMainWindow();
    filesWidget = new QMainWindow();
    createDockWindows();
    // textEdit2 = new MyTextEdit();

    //QString s = "[0-9]+";

    //highlighter->setPattern(s);
    testButton = new QPushButton("Start check !!!");
//    this->addWidget(dockWidget);
//    this->addWidget(treeView);
//    this->addWidget(textEdit);
    this->addWidget(filesWidget,0,0);
    this->addWidget(mainWidget,0,1,1,3);
    this->addWidget(testButton);
    //createDockWindows();
    //this->addWidget(testButton);
    //this->addWidget(textEdit2);


}
void MyWindow::createDockWindows()
{
    QDockWidget *dock = new QDockWidget(tr("Project Explorer"), mainWidget);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea | Qt::BottomDockWidgetArea|Qt::TopDockWidgetArea);
    dock->setWidget(treeView);

    mainWidget->addDockWidget(Qt::LeftDockWidgetArea, dock);

    dock = new QDockWidget(tr("Working file"), filesWidget);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea | Qt::BottomDockWidgetArea|Qt::TopDockWidgetArea);

    dock->setWidget(textEdit);

    filesWidget->addDockWidget(Qt::RightDockWidgetArea, dock);

}
/*
void MyWindow::createNewFileWindows(QString fileName)
{
    QDockWidget *dock = new QDockWidget(tr(fileName), mainWidget);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea | Qt::BottomDockWidgetArea|Qt::TopDockWidgetArea);
    dock->setWidget(treeView);

}*/
/*
void MyWindow::onTestButtonClicked()
{
    highlighter = new MySyntaxHighlighter(this);
    highlighter->setDocument(textEdit->document());
}
*/
