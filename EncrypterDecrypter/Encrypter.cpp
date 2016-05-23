#include "Encrypter.h"
#include <fstream>
#include <cstring>
#include "ui_Encrypter.h"
#include "QFileDialog"
#include "QMessageBox"
#include "Rijndael/Rijndael.h"
#include "Rijndael/aes.h"
#include <iostream>

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
    uint8_t *file = new uint8_t[fsize];
    f.read((char*)file, fsize);
    return file;
}

void SaveBytesToFile(const QString &filename, const uint8_t *bytes, size_t size)
{
    std::fstream f(filename.toStdString().c_str(), std::ios::out | std::ios::binary);
    if(!f.is_open())
        exit(EXIT_FAILURE);
    f.write((char*)bytes, size);
}


void MainWindow::on_pushButton_clicked()
{
    QFileDialog browse_win;

    if(browse_win.exec())
    {
        QStringList file_selected = browse_win.selectedFiles();
        ui->lineEdit->setText(file_selected[0]);
        size_t fsize;
        uint8_t *file = ReadBytesFromFile(file_selected[0], fsize);
        size_t key_size = 256;
        uint8_t *cipher_key = new uint8_t[key_size / 8];
        for(size_t i = 0; i < key_size / 8; ++i)
            cipher_key[i] = (rand() & 0xff ^ rand() & 0xFF) << rand() % 7;
        Aes aes;
        /*uint8_t *input = new uint8_t[16];
        uint8_t input_temp[16] = {0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff};
        for(size_t i = 0; i < 16; ++i)
            input[i] = input_temp[i];
        uint8_t key[16] = {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f};*/
        uint8_t * cipher_text = aes.encrypt(file, fsize, cipher_key, key_size);
        uint8_t * plain_text = aes.decrypt(cipher_text, (fsize - fsize % (16)) + 16, cipher_key, key_size);
        SaveBytesToFile(file_selected[0], plain_text, fsize);
    }
}
