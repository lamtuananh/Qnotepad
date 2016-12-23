#ifndef MYFILEDIALOG_H
#define MYFILEDIALOG_H

#include<QFileDialog>
class MyFileDialog: public QFileDialog
{
public:
    MyFileDialog();
    void getOpenFileName(QWidget *parent, const QString &caption, const QString &dir, const QString &filter, QString *selectedFilter, Options options);
    void getSaveFileName(QWidget *parent, const QString &caption, const QString &dir, const QString &filter, QString *selectedFilter, Options options);
};

#endif // MYFILEDIALOG_H
