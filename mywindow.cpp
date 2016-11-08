#include "mywindow.h"
#include <iostream>
#include <QDir>
MyWindow::MyWindow()
{

    //get current Project path
    QString sPath;
    sPath =QDir::currentPath();
   // std::cout << sPath.toStdString();
    dirModel = new QFileSystemModel();
  //  dirModel->setFilter( QDir::Name);

    dirModel->setRootPath(sPath);
    treeView = new QTreeView();
    treeView->setModel(dirModel);
    textEdit = new CodeEditor();
   // textEdit2 = new MyTextEdit();
    highlighter = new MySyntaxHighlighter(this);
    highlighter->setDocument(textEdit->document());
    //QString s = "[0-9]+";

    //highlighter->setPattern(s);
    testButton = new QPushButton("Here");
    this->addWidget(treeView);
    this->addWidget(textEdit);
    this->addWidget(testButton);
  //  this->addWidget(textEdit2);
   //  QObject::connect(textEdit,SIGNAL(textChanged()),this,SLOT(onTextEditChanged()));
}/*
void MyWindow::onTextEditChanged()
{
    QString s = "[a-Z]+";

    highlighter->setPattern(s);
}
*/
