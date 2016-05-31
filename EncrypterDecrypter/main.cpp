#include "Encrypter.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //QCoreApplication::setOrganizationName("Team");
    //QCoreApplication::setApplicationName("EncrypterDecrypter");
    MainWindow w;
    //w.loadSettings();
    w.setWindowTitle("Encrypter/Decrypter");
    w.show();
    //w.saveSettings();
    return a.exec();
}
