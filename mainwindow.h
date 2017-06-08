#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    //Q_PROPERTY(QSerialPort port READ port )

private slots:
    void get_ports(); // get a list of all available ports
    void open_port(); // open serial port
    void change_baud_rate(); // open serial port
    void read_serial(); // read from serial port
    void write_to_serial(); // write to serial port
    void close_port(); // close opened port ;
    void show_color_brightness_changer(); //show color brightness changer dialog

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QSerialPortInfo port_info; // holds all ports inforamtion
    QSerialPort m_port; //hold current opened port

protected:

};


#endif // MAINWINDOW_H
