#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "color_brightness_changer.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QString>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->get_ports,SIGNAL(clicked(bool)),this,SLOT(get_ports()) );
    connect(ui->open_port,SIGNAL(clicked(bool)),this,SLOT(open_port()) );
    connect(ui->change_baudRate,SIGNAL(clicked(bool)),this,SLOT(change_baud_rate()) );
    connect(ui->read_serial,SIGNAL(clicked(bool)),this,SLOT(read_serial()) );
    connect(ui->close_port,SIGNAL(clicked(bool)),this,SLOT(close_port()) );
    connect(ui->write_to_serial,SIGNAL(clicked(bool)),this,SLOT(write_to_serial()) );
    connect(ui->actionLED_brightness_changer,SIGNAL(triggered(bool)),this,SLOT(show_color_brightness_changer()) );

    for (int i=0; i < QSerialPortInfo::standardBaudRates().length() ; i++){
        ui->baud_rates->addItem(QString::number(QSerialPortInfo::standardBaudRates().at(i) ));
    }
}

void MainWindow::get_ports(){
    QList<QSerialPortInfo> ports = port_info.availablePorts();
    QString txt="<font color=blue> <b>Ports</b> :<br/>";
    for(int i=0; i < ports.count(); ++i){
        txt.append(ports.at(i).portName().append(" - ").append(ports.at(i).description()).append("<br/>") );
    }
    txt.append("</font>");
    ui->output->append(txt);

}

void MainWindow::open_port(){
    QString port_name=ui->port_name->text();
    if(port_name.isEmpty()){
      ui->output->append("<font color=red>Please, Enter port name !</font>");
    }else if (m_port.isOpen()){
        ui->output->append("<font color=red>Port is already opened !</font>");
    }else{
        m_port.setPortName(port_name);
        m_port.open(QIODevice::ReadWrite);
        if(m_port.isOpen()){
            m_port.setBaudRate((QSerialPort::BaudRate) ui->baud_rates->currentText().toInt());
            ui->output->append("<font color=green>Port opened successfully </font>");
        }else{
            ui->output->append("<font color=red>Port wasn't opened successfully !</font>");
            return ;
        }
    }
}

void MainWindow::change_baud_rate(){
    if (m_port.isOpen()){
        if(m_port.setBaudRate((QSerialPort::BaudRate) ui->baud_rates->currentText().toInt())){
            ui->output->append("<font color=green>Baud Rate changed successfully </font>");
        }
    }else{
            ui->output->append("<font color=red>Serial port is not opened !</font>");
    }
}

void MainWindow::read_serial(){
    if(m_port.isOpen()){
        if(m_port.readAll().isNull()) {
            ui->output->append("<font color=red>Nothing to read !</font>");
            return ;
        }else{
            ui->output->append(m_port.readAll());
        }
     }else{
        ui->output->append("<font color=red>Serial port is not opened !</font>");
    }
}

void MainWindow::write_to_serial (){
    if(m_port.isOpen()){
        QString user_input=ui->user_input->text();
        if(user_input.isEmpty()){
            ui->output->append("<font color=red>Nothing to write !</font>");
        }else{
            QByteArray s;
            s.append(user_input);
            m_port.write(s);
            ui->output->append(m_port.readAll());
        }
    }else{
        ui->output->append("<font color=red>Serial port is not opened !</font>");
    }
}

void MainWindow::close_port(){
    if(m_port.isOpen()){
        m_port.close();
        ui->output->append("<font color=green>Port opened successfully </font>");
    }else{
        ui->output->append("<font color=red>Port is already closed ! </font>");
    }
}

void MainWindow::show_color_brightness_changer(){
    color_brightness_changer *color_brightness_changer_dialog = new color_brightness_changer();
    color_brightness_changer_dialog->pass_args(&m_port,ui->output); // pass port variable and output text form
    color_brightness_changer_dialog->show();
}



MainWindow::~MainWindow()
{
    delete ui;
}
