#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <mywindow.h>
#include <iostream>
#include <QFileDialog>
#include <QDirModel>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mywindow = new MyWindow();
    ui->centralWidget->setLayout(mywindow);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_File_triggered()
{
    mywindow->currentFileName = "";
    mywindow->textEdit->setPlainText("");
}

void MainWindow::on_actionOpen_file_triggered()
{
    QString file= QFileDialog::getOpenFileName(this,"Open the file");
    if(!file.isEmpty()){
        QFile sFile(file);
        if(sFile.open(QFile::ReadOnly| QFile::Text)){
             mywindow->currentFileName = file;
            QTextStream in(&sFile);
            QString text = in.readAll();
            sFile.close();

            mywindow->textEdit->setPlainText(text);
        }
    }
}

void MainWindow::on_actionSave_file_triggered()
{
    if( mywindow->currentFileName=="")
         mywindow->currentFileName = QFileDialog::getSaveFileName(this,"Open file to save");

    QFile sFile( mywindow->currentFileName);
    if(sFile.open(QFile::WriteOnly | QFile::Text))
    {
        QTextStream out(&sFile);
        out<<mywindow->textEdit->toPlainText();

        sFile.flush();
        sFile.close();
    }
}
void MainWindow::on_actionSave_as_triggered()
{
    QString file = QFileDialog::getSaveFileName(this,"Open file to save");
    if(!file.isEmpty())
    {
         mywindow->currentFileName = file;
        on_actionSave_file_triggered();
    }
}

void MainWindow::on_actionCopy_triggered()
{
    mywindow->textEdit->copy();
}

void MainWindow::on_actionPaste_triggered()
{
    mywindow->textEdit->paste();
}

void MainWindow::on_actionUndo_triggered()
{
    mywindow->textEdit->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    mywindow->textEdit->redo();
}

void MainWindow::onTextEditChanged(QString s)
{
    //QString *content;
   //QString  content = mywindow->textEdit->toPlainText();
   // mywindow->textEdit->setHtml("<p style=\"color:red;\">" + content + "</p>");
    std::cout<< "Hello , content of text edit is changed"<<endl;
}

void MainWindow::on_actionShowHtml_triggered()
{
    mywindow->textEdit->setHtml("<h6><p>Here is HTML content</p></h6>");
}
