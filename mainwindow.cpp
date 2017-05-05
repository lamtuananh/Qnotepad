#include <mainwindow.h>
#include <ui_mainwindow.h>
#include <QtWidgets>
#include<QTextStream>
#include <iostream>
#include <QFileDialog>
#include <QDirModel>
#include <checkthread.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    setFilter = tr("VHDL (*.v *.sv)");
    QString path = ":/resources/workingDirectory.txt";
 QTextStream out(stdout);
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
          {
    }
    QTextStream in(&file);
    directory = in.readLine();
   file.close();
    ui->setupUi(this); //set the ui form for this mainwindow class
    mywindow = new MyWindow(parent); // mywindow is resizeable layout, it contain main text editor
    ui->centralWidget->setLayout(mywindow); // set the window layout to this centralWidget of program
    mythread = new CheckThread(mywindow); //check thread used to reset highlight tool
    mythread->start();

}

MainWindow::~MainWindow()
{
    delete ui;
}
/**
 * @brief MainWindow::on_actionNew_File_triggered
 *  action called when user open a new file.
 * program empty content of text editor.
 * empty current working file name.
 */
void MainWindow::on_actionNew_File_triggered()
{
    mywindow->currentFileName = ""; //set current file name to empty
    mywindow->editor->textEdit->setPlainText(""); //emtpty content of main text editor
}
/**
 * @brief MainWindow::on_actionOpen_file_triggered
 * action called when user open a file.
 * first: get a file name from file dialog
 * Read content from file
 * Set text of the editor with the content.
 */
void MainWindow::on_actionOpen_file_triggered()
{
    const QString dir = directory;
    //get file frfom file dialog
    QString file= QFileDialog::getOpenFileName(this,"Open the file",dir,tr("All files (*.v *.sv);;VHDL (*.v);;SystemVerilog (*.sv)" ));
    if(!file.isEmpty()){
        QFile sFile(file);
        if(sFile.open(QFile::ReadOnly| QFile::Text)){
             mywindow->currentFileName = file;
            QTextStream in(&sFile);
            QString text = in.readAll();
            sFile.close();
            mywindow->editor->textEdit->setPlainText(text);
            mywindow->editor->textEdit->resetCompleter();
        }
    }
}
/**
 * @brief MainWindow::on_actionSave_file_triggered
 * action called when user choose save file
 */
void MainWindow::on_actionSave_file_triggered()
{
    if( mywindow->currentFileName=="") //if user dont work with any file. open a file to save.
         mywindow->currentFileName = QFileDialog::getSaveFileName(this,"Open file to save","C:\\Program Files",tr("All files (*.v *.sv);;VHDL (*.v);;SystemVerilog (*.sv)" ));

    QFile sFile( mywindow->currentFileName);
    if(sFile.open(QFile::WriteOnly | QFile::Text))
    {
        QTextStream out(&sFile);
        out<<mywindow->editor->textEdit->toPlainText();
        sFile.flush();
        sFile.close();
    }
}
/**
 * @brief MainWindow::on_actionSave_as_triggered
 * action called when user choose save as file.
 */
void MainWindow::on_actionSave_as_triggered()
{
    //open file to save
    QString file = QFileDialog::getSaveFileName(this,"Open file to save","C:\\Program Files",tr("All files (*.v *.sv);;VHDL (*.v);;SystemVerilog (*.sv)" ));
    if(!file.isEmpty())
    {
         mywindow->currentFileName = file;
        on_actionSave_file_triggered();
    }
}
/**
 * @brief MainWindow::on_actionCopy_triggered
 * action called when user choose copy.
 */
void MainWindow::on_actionCopy_triggered()
{
    mywindow->editor->textEdit->copy();
}
/**
 * @brief MainWindow::on_actionPaste_triggered
 * action called when user choose paste.
 */
void MainWindow::on_actionPaste_triggered()
{
    mywindow->editor->textEdit->paste();
}
/**
 * @brief MainWindow::on_actionUndo_triggered
 * action called when user choose undo.
 */
void MainWindow::on_actionUndo_triggered()
{
    mywindow->editor->textEdit->undo();
}
/**
 * @brief MainWindow::on_actionRedo_triggered
 * action called when user choose redo.
 */
void MainWindow::on_actionRedo_triggered()
{
    mywindow->editor->textEdit->redo();
}


void MainWindow::on_actionShowHtml_triggered()
{
  //  mywindow->textEdit->setHtml("<h6><p>Here is HTML content</p></h6>");
}

void MainWindow::onTextEditChanged()
{
/*    if(mywindow->testButton->text() == "Here")
   mywindow->testButton->setText("CHANGED");
    else mywindow->testButton->setText("Here");
    QString s = "<p  style=\"color:blue;\"> " + mywindow->textEdit->toPlainText()+ " </p>";
    std::cout<<s.toStdString();
    mywindow->textEdit2->setHtml(s);
    mywindow->textEdit->setHtml(s);
*/
    QString s = "[a-Z]+";
    //mywindow->highlighter->setPattern(s);
}



void MainWindow::on_actionOpen_directory_triggered()
{
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setOption(QFileDialog::ShowDirsOnly);
    directory =     dialog.getExistingDirectory(this,"Open working directory");

    QTextStream out(stdout);
    out<<"hello world"<<directory<<endl;
    QString path = ":/resources/workingDirectory.txt";

    QFile outputFile(path);
       outputFile.open(QIODevice::WriteOnly);

       /* Check it opened OK */
       if(!outputFile.isOpen()){
           out<<"fucking file"<<endl;
           return;
       }

       /* Point a QTextStream object at the file */
       QTextStream outStream(&outputFile);

       /* Write the line to the file */
       outStream << directory<<endl;

       /* Close the file */
       outputFile.close();
}
