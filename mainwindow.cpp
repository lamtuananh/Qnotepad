#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDirModel>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //this->setCentralWidget(ui->tabWidget_2);
    QDirModel *model;
    model =  new QDirModel();
    ui->treeView->setModel(model);
    ui->treeView->setRootIndex(model->index(QDir::currentPath()));
    ui->treeView->setColumnHidden( 1, true );
    ui->treeView->setColumnHidden( 2, true );
    ui->treeView->setColumnHidden( 3, true );
    ui->treeView->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_File_triggered()
{
    mFileName = "";
    ui->textEdit->setPlainText("");
}

void MainWindow::on_actionOpen_file_triggered()
{
    QString file= QFileDialog::getOpenFileName(this,"Open the file");
    if(!file.isEmpty()){
        QFile sFile(file);
        if(sFile.open(QFile::ReadOnly| QFile::Text)){
            mFileName = file;
            QTextStream in(&sFile);
            QString text = in.readAll();
            sFile.close();

            ui->textEdit->setPlainText(text);
        }
    }
}

void MainWindow::on_actionSave_file_triggered()
{
    if(mFileName=="")
        mFileName = QFileDialog::getSaveFileName(this,"Open file to save");

    QFile sFile(mFileName);
    if(sFile.open(QFile::WriteOnly | QFile::Text))
    {
        QTextStream out(&sFile);
        out<<ui->textEdit->toPlainText();

        sFile.flush();
        sFile.close();
    }
}
void MainWindow::on_actionSave_as_triggered()
{
    QString file = QFileDialog::getSaveFileName(this,"Open file to save");
    if(!file.isEmpty())
    {
        mFileName = file;
        on_actionSave_file_triggered();
    }
}

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}


