#include "Encrypter.h"
#include "ui_Encrypter.h"
#include "QFileDialog"
#include "QMessageBox"
#include <QSettings>

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
    QPixmap pixmap(QDir::currentPath() + "/icons/EDcrF.png");
    QIcon ButtonIcon(pixmap);
    ui->ED_file->setIcon(ButtonIcon);
    ui->ED_file->setIconSize(pixmap.rect().size());
    ui->ED_file->setStyleSheet("QPushButton{border: none;outline: none;}");
    QPixmap pixmap2(QDir::currentPath() + "/icons/EDcr.png");
    QIcon ButtonIcon2(pixmap2);
    ui->ED_Message->setIcon(ButtonIcon2);
    ui->ED_Message->setIconSize(pixmap.rect().size());
    ui->ED_Message->setStyleSheet("QPushButton{border: none;outline: none;}");
    QPixmap pixmap3(QDir::currentPath() + "/icons/Set.png");
    QIcon ButtonIcon3(pixmap3);
    ui->settings_button->setIcon(ButtonIcon3);
    ui->settings_button->setIconSize(pixmap.rect().size());
    ui->settings_button->setStyleSheet("QPushButton{border: none;outline: none;}");
    QPixmap pixmap4(QDir::currentPath() + "/icons/Ab.png");
    QIcon  ButtonIcon4(pixmap4);
    ui->about_button->setIcon(ButtonIcon4);
    ui->about_button->setIconSize(pixmap.rect().size());
    QPixmap pixmap5(QDir::currentPath() + "/icons/Hist.png");
    QIcon  ButtonIcon5(pixmap5);
    ui->history_button->setIcon(ButtonIcon5);
    ui->history_button->setIconSize(pixmap.rect().size());
    ui->history_button->setStyleSheet("QPushButton{border: none;outline: none;}");
   // ui->tableWidget->setStyleSheet(tr("background-color: #FFFFFF;", "QScrollBar:horizontal {background: #DCDCDC}"));
    QFile history("history.txt");
    if(history.open(QIODevice::ReadOnly |QIODevice::Text))
        {
        int i = 0;
            while(!history.atEnd())
            {
                QString str = history.readLine();
                QStringList lst = str.split(" ");
                int count = ui->tableWidget->rowCount( );
                ui->tableWidget->insertRow(count); // добавление строк
                for (int j=0;j<4;j++)
                {
                    QTableWidgetItem *item = new QTableWidgetItem(); // выделяем память под ячейку
                    item->setText(lst.at(j).arg(i).arg(j)); // вставляем текст
                    ui->tableWidget->setItem(i, j, item); // вставляем ячейку
                  /*  ui->tableWidget->setItem(i, j, new QTableWidgetItem());
                    (ui->tableWidget->item(i,j))->setText(lst.at(j)); */
                }
                i++;
            }
        }
}

void MainWindow::loadSettings()
{
    QSettings conf;
    settings->setCipherPath(conf.value("Encrypter/CipherPath").toString());
}

void MainWindow::saveSettings()
{
    QSettings conf;
    conf.setValue("Encrypter/CipherPath", settings->getCipherPath());
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


void MainWindow::on_history_button_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}


void MainWindow::on_about_button_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
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

void MainWindow::on_SaveDir_button_clicked()
{
    QFileDialog browse_win;

    if(browse_win.exec())
    {
    QStringList file_selected = browse_win.selectedFiles();
    ui->SaveDir_line->setText(file_selected[0]);
    }
}

void MainWindow::on_Icon_button_clicked()
{
    QFileDialog browse_win;

    if(browse_win.exec())
    {
    QStringList file_selected = browse_win.selectedFiles();
    ui->Icon_line->setText(file_selected[0]);
    }
}

void MainWindow::on_lineEdit_3_selectionChanged()
{
    ui->lineEdit_3->setText("");
}

void MainWindow::on_lineEdit_2_selectionChanged()
{
    ui->lineEdit_2->setText("");
}

void MainWindow::on_textEdit_2_selectionChanged()
{
    ui->textEdit_2->setText("");
}

void MainWindow::on_Icon_line_selectionChanged()
{
    ui->Icon_line->setText("");
}

void MainWindow::on_lineEdit_5_selectionChanged()
{
    ui->lineEdit_5->setText("");
}

void MainWindow::on_SaveDir_line_selectionChanged()
{
     ui->SaveDir_line->setText("");
}

void MainWindow::on_lineEdit_selectionChanged()
{
    ui->lineEdit->setText("");
}

void MainWindow::on_textEdit_selectionChanged()
{
    ui->textEdit->setText("");
}
