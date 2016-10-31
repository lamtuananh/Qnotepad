#include "mysyntaxhighlighter.h"
#include<QTextCharFormat>
#include <QMap>
#include <QFont>
#include <iostream>
#include <QFile>
#include <QTextStream>
#include <QDir>
MySyntaxHighlighter::MySyntaxHighlighter(QObject *parent) : QSyntaxHighlighter(parent)
{
//    mapFont = new QMap(QString,QFont);
 //   mapPattern = new QMap(QString,QString);
    QFont *moduleFont = new QFont("Bavaria",10,QFont::Bold);
    QFont *datatypeFont = new QFont("Times", 12, QFont::Bold);

 /*   mapFont.insert("module",*moduleFont);
    mapFont.insert("endmodule",*moduleFont);
    mapFont.insert("wire",*datatypeFont);
    mapFont.insert("reg",*datatypeFont);
    mapFont.insert("wand",*datatypeFont);
    mapFont.insert("wor",*datatypeFont);
    mapFont.insert("tri",*datatypeFont);*/
/*    mapPattern.insert("module","([ ]module[ ])");
    mapPattern.insert("endmodule","([ ]endmodule[ ])");
    mapPattern.insert("wand","([ ]wand[ ])");
    mapPattern.insert("wor","([ ]wor[ ])");
    mapPattern.insert("tri","([ ]tri[ ])");
    mapPattern.insert("reg","([ ]reg[ ])");
    mapPattern.insert("wire","([ ]wire[ ])"); */
    QDir dir;
    QString path = QDir::currentPath() +"/keywords.txt";
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
          {
         std::cout<<path.toStdString();
        std::cout<<"errow while reading file";
        return;
    }
    QTextStream in(&file);
     QString line = in.readLine();
while (!line.isNull()) {
   // QString line = in.readLine();
        //  std::cout<<line.toStdString();
           vector.append("\\b"+line+"\\b");
           // process_line(line);
           line = in.readLine();
       }
    modulePattern = "\\bmodule\\b.{*}\\bendmodule\\b";

}
void MySyntaxHighlighter::highlightBlock(const QString &text)
{
//    QMapIterator<QString,QString> i(mapPattern);
  //  while(i.hasNext())
    for (int i = 0; i < vector.size(); ++i) {
    QTextCharFormat format;
    QString pattern = vector[i];
    QRegExp rx(pattern);

    if(!rx.isValid()  || rx.isEmpty() || rx.exactMatch("")){
        setFormat(0, text.length(),format);
        std::cout<<"not correct regular expression";
        return;
    }
 //   QFont serifFont = mapFont.value(i.key());
 QFont serifFont = QFont("Bavaria",10,QFont::Bold);
    //format.setBackground(Qt::yellow);
    format.colorProperty(Qt::red);

    format.setFont(serifFont);
    int index = rx.indexIn(text);
    while (index>=0) {
        int length = rx.matchedLength();
        setFormat(index,length,format);
        index = rx.indexIn(text,index + length);
    }
    }
}
