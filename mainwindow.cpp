#include <mainwindow.h>
#include <ui_mainwindow.h>
#include <QtWidgets>

#include <iostream>
#include <QFileDialog>
#include <QDirModel>
#include <checkthread.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), completer(0),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    mywindow = new MyWindow(parent);

   // completingTextEdit = new TextEdit;
    completer = new QCompleter(this);
    completer->setModel(modelFromFile(":/resources/keywords.txt"));
    completer->setModelSorting(QCompleter::CaseInsensitivelySortedModel);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setWrapAround(false);
    mywindow->textEdit->setCompleter(completer);


     mythread = new CheckThread(mywindow);
   // ui->setupUi(mywindow);
    ui->centralWidget->setLayout(mywindow);
    mywindow->highlighter = new MySyntaxHighlighter( mywindow->textEdit);
    mywindow->highlighter->setDocument( mywindow->textEdit->document());
   // QObject::connect(mywindow->textEdit,SIGNAL(textChanged()),this,SLOT(onTextEditChanged()));
     QObject::connect(mywindow->testButton,SIGNAL(clicked()),this,SLOT(onTestButtonClicked()));
     QObject::connect(mywindow->testButton,SIGNAL(clicked()),mythread,SLOT(getListWords()));

}
void MainWindow::onTestButtonClicked()
{

   // CheckThread *mythread = new CheckThread();
    mythread->start();
    //mythread.start();
 //   mywindow->highlighter = new MySyntaxHighlighter( mywindow);
 //   mywindow->highlighter->setDocument( mywindow->textEdit->document());
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
    QString file= QFileDialog::getOpenFileName(this,"Open the file","C:\\Program Files","*.v *.sv");
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
         mywindow->currentFileName = QFileDialog::getSaveFileName(this,"Open file to save","C:\\Program Files","*.v *.sv");

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
    QString file = QFileDialog::getSaveFileName(this,"Open file to save","C:\\Program Files","*.v *.sv");
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

//get keywords from file for completer
QAbstractItemModel *MainWindow::modelFromFile(const QString& fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly))
        return new QStringListModel(completer);

#ifndef QT_NO_CURSOR
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
#endif
    QStringList words;
    // QTextStream out(stdout);

    while (!file.atEnd()) {
        QByteArray line = file.readLine();
     //  out<< line << "  "<<endl;
        if (!line.isEmpty())
            words << line.trimmed();
    }


#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif
    return new QStringListModel(words, completer);
}



