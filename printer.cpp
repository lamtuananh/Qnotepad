#include <iostream>
#include<QTextStream>
 class Printer {
    public:
        static void print(const QString &text) {
        QTextStream out(stdout);
        out<<text<<endl;
}
 };
