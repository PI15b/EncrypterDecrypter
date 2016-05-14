#include "Encrypter.h"
#include <fstream>
#include "ui_Encrypter.h"
#include "QFileDialog"
#include "QMessageBox"
#include "Rijndael/Rijndael.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
  //  ui->stackedWidget->setStyleSheet("border: 1px solid red");
   /* ui->ED_file->setIcon(QIcon(QPixmap("D:/programs/qt/proj/Encypter/icons/icons/button.png")));
    ui->ED_file->setIconSize(QSize(264, 32)); */
    QPixmap pixmap(QDir::currentPath() + "/icons/button.png");
       QIcon ButtonIcon(pixmap);
       ui->ED_file->setIcon(ButtonIcon);
       ui->ED_file->setIconSize(pixmap.rect().size());
       ui->ED_Message->setIcon(ButtonIcon);
       ui->ED_Message->setIconSize(pixmap.rect().size());
    ui->centralWidget->setStyleSheet("background-color: #DCDCDC;");
    ui->ED_file->setStyleSheet("QPushButton{border: none;outline: none;}");
    ui->ED_Message->setStyleSheet("QPushButton{border: none;outline: none;}");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ED_file_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_ED_Message_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_settings_button_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_about_button_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

static unsigned char * ReadBytesFromFile(const QString &filename, size_t &fsize)
{
    std::fstream f(filename.toStdString().c_str(), std::ios::in | std::ios::binary);
    if(!f.is_open())
        exit(EXIT_FAILURE);
    f.seekg(0, std::ios_base::end);
    fsize = f.tellg();
    f.seekg(0, std::ios_base::beg);
    unsigned char *file = new unsigned char[fsize];
    f.read((char*)file, fsize);
    return file;
}


void MainWindow::on_pushButton_clicked()
{
    QFileDialog browse_win;

    if(browse_win.exec())
    {
        QStringList file_selected = browse_win.selectedFiles();
        ui->lineEdit->setText(file_selected[0]);
        size_t fsize;
        unsigned char *file = ReadBytesFromFile(file_selected[0], fsize);
        size_t key_size;
        unsigned char *cipher_key = ReadBytesFromFile("3511F41EA5DFC1DF2CD521F7B6A5F", key_size);
        unsigned char *encrypted = new unsigned char[fsize];
        Rijndael rj;
        rj.SetParameters(256);
        rj.StartEncryption(cipher_key);
        rj.Encrypt(file, encrypted, fsize / 16);
        QMessageBox msgBox;
        msgBox.setText(*(new QString((char*)encrypted)));
    }
}
