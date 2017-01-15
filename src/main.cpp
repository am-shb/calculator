#include "calculator.h"
#include <QApplication>

#include "biginteger.h"
#include <qdebug.h>
#include <ctime>
#include <cstdlib>

#define SELFTEST false

int main(int argc, char *argv[])
{
    if(SELFTEST) {
        long long int l1, l2;
        bool add=true, subtract=true, multiply=true, division=true, mod=true;
        srand(time(NULL));

        for(int i=0; i<1000; i++) {
            l1 = rand();
            l2 = rand();
            if(BigInteger(l1 + l2) != (BigInteger(l1) + BigInteger(l2))) {
                qDebug() << "(+)fail! => " << l1 << ", " << l2 << endl;
                add = false;
            }

            if(BigInteger(l1 - l2) != (BigInteger(l1) - BigInteger(l2))) {
                qDebug() << "(-)fail! => " << l1 << ", " << l2 << endl;
                subtract = false;
            }

            if(BigInteger(l1 * l2) != (BigInteger(l1) * BigInteger(l2))) {
                qDebug() << "(*)fail! => " << l1 << ", " << l2 << endl;
                multiply = false;
            }

            if(BigInteger(l1 / l2) != (BigInteger(l1) / BigInteger(l2))) {
                qDebug() << "(/)fail! => " << l1 << ", " << l2 << endl;
                division = false;
            }

            if(BigInteger(l1 % l2) != (BigInteger(l1) % BigInteger(l2))) {
                qDebug() << "(%)fail! => " << l1 << ", " << l2 << endl;
                mod = false;
            }
        }

        qDebug() << "+ operator test: " << (add ? "pass!" : "fail!");
        qDebug() << "- operator test: " << (subtract ? "pass!" : "fail!");
        qDebug() << "* operator test: " << (multiply ? "pass!" : "fail!");
        qDebug() << "/ operator test: " << (division ? "pass!" : "fail!");
        qDebug() << "% operator test: " << (mod ? "pass!" : "fail!");

        return 0;
    }
    else {
        QApplication a(argc, argv);
        Calculator w;
        w.show();
        return a.exec();
    }
}
