#include <mainwindow.h>
#include <ui_mainwindow.h>

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
   // QObject::connect(mywindow->textEdit,SIGNAL(textChanged()),this,SLOT(onTextEditChanged()));
     QObject::connect(mywindow->testButton,SIGNAL(clicked()),this,SLOT(onTestButtonClicked()));
}
void MainWindow::onTestButtonClicked()
{
    mywindow->highlighter = new MySyntaxHighlighter( mywindow);
    mywindow->highlighter->setDocument( mywindow->textEdit->document());
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
    QString file= QFileDialog::getOpenFileName(this,"Open the file","C:\\Program Files","*.v *.sv *.svh *.sh");
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
         mywindow->currentFileName = QFileDialog::getSaveFileName(this,"Open file to save","C:\\Program Files","*.v *.sv *.svh *.sh");

    QFile sFile( mywindow->currentFileName);
    if(sFile.open(QFile::WriteOnly | QFile::Text))
    {
        QTextStream out(&sFile);
        //cout<<mywindow->textEdit->toPlainText();

        sFile.flush();
        sFile.close();
    }
}
void MainWindow::on_actionSave_as_triggered()
{
    QString file = QFileDialog::getSaveFileName(this,"Open file to save","C:\\Program Files","*.v *.sv *.svh *.sh");
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

/*void MainWindow::onTextEditChanged()
{
    //QString *content;
   QString  content; //= mywindow->textEdit->toPlainText();
   // mywindow->textEdit->setHtml("<p style=\"color:red;\">" "</p>");
    mywindow->textEdit->setHtml("<h6><p>Here is HTML content</p></h6>");

    //std::cout<< content.toStdString();
}
*/
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
