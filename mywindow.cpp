#include "mywindow.h"
#include <iostream>
using namespace std;
MyWindow::MyWindow()
{

    //get current Project path
    QString sPath;// = new QString();
    sPath ="C:\Users\Lam\Qnotepad";
    cout << sPath.toStdString();
    dirModel = new QFileSystemModel();
  //  dirModel->setFilter( QDir::Name);

    dirModel->setRootPath(sPath);

    treeView = new QTreeView();
    treeView->setModel(dirModel);
    textEdit = new QTextEdit();
    QObject::connect(textEdit,SIGNAL(textChanged()),this,SLOT(onTextEditChanged(QString)));
        this->addWidget(treeView);
    this->addWidget(textEdit);
}
