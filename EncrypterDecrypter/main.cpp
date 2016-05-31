#include "Encrypter.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("TeamNMK");
    QCoreApplication::setApplicationName("EncrypterDecrypter");
    MainWindow w;
    w.loadSettings();
    w.setWindowTitle("Encrypter/Decrypter");
    w.init();
    w.show();
    return a.exec();
}
