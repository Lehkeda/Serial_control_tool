#ifndef COLOR_BRIGHTNESS_CHANGER_H
#define COLOR_BRIGHTNESS_CHANGER_H

#include <QDialog>
#include "mainwindow.h"
#include <QSerialPort>
#include <QTextBrowser>

namespace Ui {
class color_brightness_changer;
}

class color_brightness_changer : public QDialog
{
    Q_OBJECT

public:
    explicit color_brightness_changer(QWidget *parent = 0);
    void pass_args(QSerialPort *p, QTextBrowser *t);
    ~color_brightness_changer();

private slots:
    void change_red_brightness(int);
    void change_green_brightness(int);
    void change_blue_brightness(int);

private:
    Ui::color_brightness_changer *ui;
    void write_value_to_serial(QByteArray data);
    QSerialPort *opened_port;
    QTextBrowser *output_textBox;

};

#endif // COLOR_BRIGHTNESS_CHANGER_H
