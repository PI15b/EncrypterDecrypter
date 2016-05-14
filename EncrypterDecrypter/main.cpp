#include "mainwindow.h"
#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QWidget *mainWindow = new QWidget;
    mainWindow->setWindowTitle("Buttons");

    QPushButton *encrypt = new QPushButton("Encrypt");
     QPushButton *overview = new QPushButton("Overview");
     QObject::connect(encrypt, SIGNAL(clicked()), , SLOT());
      QObject::connect(overview, SIGNAL(clicked()), , SLOT());]

      QHBoxLayout *buttons = new QHBoxLayout;
      buttons->addWidget(encrypt);
      buttons->addWidget(overview);

    mainWindow->setLayout(buttons);
    mainWindow->show();

    return a.exec();
}
