#ifndef ENCRYPTER_H
#define ENCRYPTER_H

#include <QMainWindow>
#include "settings.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void loadSettings();
    void saveSettings();
    ~MainWindow();

private slots:
    void on_ED_file_clicked();
    void on_ED_Message_clicked();
    void on_settings_button_clicked();
    void on_about_button_clicked();

    void on_pushButton_clicked();

    void on_SaveDir_button_clicked();

    void on_Icon_button_clicked();

    void on_history_button_clicked();

    void on_lineEdit_3_selectionChanged();

    void on_lineEdit_2_selectionChanged();

    void on_textEdit_2_selectionChanged();

    void on_Icon_line_selectionChanged();

    void on_lineEdit_5_selectionChanged();

    void on_SaveDir_line_selectionChanged();

    void on_lineEdit_selectionChanged();

    void on_textEdit_selectionChanged();

    void on_SaveDir_line_textChanged(const QString &arg1);

    void on_SaveDir_line_editingFinished();

private:
    Ui::MainWindow *ui;
    Settings *settings;
    QString temp;
};

#endif // ENCRYPTER_H
