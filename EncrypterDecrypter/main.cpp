#include "Encrypter.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Encrypter/Decrypter");
    w.show();

    return a.exec();
}
