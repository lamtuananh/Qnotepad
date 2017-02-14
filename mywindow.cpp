#include "mywindow.h"
#include <iostream>
#include <QDir>
MyWindow::MyWindow()
{

    //get current Project path
    QString sPath;
    sPath =QDir::currentPath();
    std::cout << sPath.toStdString();
    dirModel = new QFileSystemModel();
  //  dirModel->setFilter( QDir::Name);
    sPath = "C:\\Users\\a.lam.tuan\\";
    dirModel->setRootPath(sPath);
    treeView = new QTreeView();
    treeView->setModel(dirModel);
    textEdit = new CodeEditor();
   dockWidget = new QDockWidget;
   mainWidget = new QMainWindow();
   filesWidget = new QMainWindow();
   createDockWindows();
    // textEdit2 = new MyTextEdit();

    //QString s = "[0-9]+";

    //highlighter->setPattern(s);
    testButton = new QPushButton("Here");
   // this->addWidget(dockWidget);
//    this->addWidget(treeView);
//    this->addWidget(textEdit);
    this->addWidget(mainWidget);
    this->addWidget(filesWidget);

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

    dock = new QDockWidget(tr("Working file"), mainWidget);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea | Qt::BottomDockWidgetArea|Qt::TopDockWidgetArea);

    dock->setWidget(textEdit);

    mainWidget->addDockWidget(Qt::RightDockWidgetArea, dock);

}/*
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
