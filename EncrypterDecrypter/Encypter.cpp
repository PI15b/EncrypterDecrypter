#include "Encrypter.h"
#include "ui_Encrypter.h"
#include "QFileDialog"
#include "QMessageBox"
#include <fstream>
#include "encrypt.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
  //  ui->stackedWidget->setStyleSheet("border: 1px solid red");
   /* ui->ED_file->setIcon(QIcon(QPixmap("D:/programs/qt/proj/Encypter/icons/icons/button.png")));
    ui->ED_file->setIconSize(QSize(264, 32)); */
    ui->centralWidget->setStyleSheet("background-color:  #242a45;");
    ui->frame->setStyleSheet("background-color:  #DCDCDC;");
    ui->stackedWidget->setStyleSheet("background-color:  #DCDCDC;");
    QPixmap pixmap(QDir::currentPath() + "/icons/ED_file.png");
    QIcon ButtonIcon(pixmap);
    ui->ED_file->setIcon(ButtonIcon);
    ui->ED_file->setIconSize(pixmap.rect().size());
    ui->ED_file->setStyleSheet("QPushButton{border: none;outline: none;}");
    QPixmap pixmap2(QDir::currentPath() + "/icons/ED_message.png");
    QIcon ButtonIcon2(pixmap2);
    ui->ED_Message->setIcon(ButtonIcon2);
    ui->ED_Message->setIconSize(pixmap.rect().size());
    ui->ED_Message->setStyleSheet("QPushButton{border: none;outline: none;}");
    QPixmap pixmap3(QDir::currentPath() + "/icons/Settings.png");
    QIcon ButtonIcon3(pixmap3);
    ui->settings_button->setIcon(ButtonIcon3);
    ui->settings_button->setIconSize(pixmap.rect().size());
    ui->settings_button->setStyleSheet("QPushButton{border: none;outline: none;}");
    QPixmap pixmap4(QDir::currentPath() + "/icons/About.png");
    QIcon  ButtonIcon4(pixmap4);
    ui->about_button->setIcon(ButtonIcon4);
    ui->about_button->setIconSize(pixmap.rect().size());
    ui->about_button->setStyleSheet("QPushButton{border: none;outline: none;}");
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

void MainWindow::on_SaveDir_button_clicked()
{
    QFileDialog browse_win;

    if(browse_win.exec())
    {
    QStringList file_selected = browse_win.selectedFiles();
    ui->lineEdit->setText(file_selected[0]);
    }
}

void MainWindow::on_Icon_button_clicked()
{
    QFileDialog browse_win;

    if(browse_win.exec())
    {
        QStringList file_selected = browse_win.selectedFiles();
        ui->lineEdit->setText(file_selected[0]);
    }
}

void MainWindow::on_pushButton_clicked()
{
    QFileDialog browse_win;

    if(browse_win.exec())
    {
        QStringList file_selected = browse_win.selectedFiles();
        ui->lineEdit->setText(file_selected[0]);
        Encrypt(Aes::CBC, Hash::MD5, file_selected[0], tr("/home/fuxy/cipher.text"), tr("/home/fuxy/cipher.key"), Key::key128, tr("/home/fuxy/hash.md5"));
        Decrypt(Aes::CBC, Hash::MD5, tr("/home/fuxy/plain.text"), tr("/home/fuxy/cipher.text"), tr("/home/fuxy/cipher.key"), tr("/home/fuxy/hash.md5"));
    }
}
