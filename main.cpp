#include "Login.h"
#include <QApplication>
#include <QScreen>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login w;
    w.setFixedSize( 480, 760 );
    w.setWindowTitle("Library Management");
    w.show();
    return a.exec();
}
