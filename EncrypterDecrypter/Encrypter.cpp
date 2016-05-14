#include "Encrypter.h"
#include "ui_Encrypter.h"
#include "QFileDialog"
#include "QMessageBox"

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


void MainWindow::on_pushButton_clicked()
{
    QFileDialog browse_win;

    if(browse_win.exec())
    {
    QStringList file_selected = browse_win.selectedFiles();
    ui->lineEdit->setText(file_selected[0]);
    }
}
