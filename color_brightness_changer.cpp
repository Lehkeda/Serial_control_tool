#include "color_brightness_changer.h"
#include "ui_color_brightness_changer.h"
#include <QByteArray>
#include <QString>

color_brightness_changer::color_brightness_changer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::color_brightness_changer)
{
    ui->setupUi(this);
    connect(ui->red_slider,SIGNAL(valueChanged(int)),this,SLOT(change_red_brightness(int)) );
    connect(ui->blue_slider,SIGNAL(valueChanged(int)),this,SLOT(change_blue_brightness(int)) );
    connect(ui->green_slider,SIGNAL(valueChanged(int)),this,SLOT(change_green_brightness(int)) );

}

void color_brightness_changer::pass_args(QSerialPort *current_port, QTextBrowser *textBox){
    opened_port = current_port;
    output_textBox = textBox;
}

void color_brightness_changer::change_red_brightness(int v){
    QByteArray color_value;
    color_value.append("red").append(QString::number(v));
    write_value_to_serial(color_value);
}

void color_brightness_changer::change_blue_brightness(int v){
    QByteArray color_value;
    color_value.append("blu").append(QString::number(v));
    write_value_to_serial(color_value);
}

void color_brightness_changer::change_green_brightness(int v){
    QByteArray color_value;
    color_value.append("gre").append(QString::number(v));
    write_value_to_serial(color_value);
}

void color_brightness_changer::write_value_to_serial(QByteArray data){
    if(opened_port->isOpen()){
        // make sure that data is 6 characters lenth
        if(data.length()==5){
            data.insert(3,"0");
        }else if(data.length()==4){
            data.insert(3,"00");
        }
        output_textBox->append(data);
        this->opened_port->write(data);
        opened_port->flush();
        //output_textBox->append(opened_port->readAll());
    }else{
        output_textBox->append("<font color=red>Serial port is not opened !</font>");
        return ;
    }
}

color_brightness_changer::~color_brightness_changer()
{
    delete ui;
}
