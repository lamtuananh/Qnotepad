#include "mywindow.h"

MyWindow::MyWindow()
{

    //get current Project path
    QString sPath = QDir::currentPath();
    dirModel = new QFileSystemModel();
  //  dirModel->setFilter( QDir::Name);

    dirModel->setRootPath(sPath);

    treeView = new QTreeView();
    treeView->setModel(dirModel);
    textEdit = new QTextEdit();

    this->addWidget(treeView);
    this->addWidget(textEdit);
}
