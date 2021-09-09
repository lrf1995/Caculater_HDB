#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label_H->setAlignment(Qt::AlignCenter);
    ui->label_L->setAlignment(Qt::AlignCenter);

    //set HEX LEN 10
    ui->HEX_QLineEdit->setMaxLength(10);
    //set DEC_LINEEDIT


    connect(ui->HEX_QLineEdit, SIGNAL(returnPressed()), this, SLOT(turnCode()));
    connect(ui->DEC_QLineEdit, SIGNAL(returnPressed()), this, SLOT(turnCode()));


}
void MainWindow::turnCode()
{
    QLineEdit *lineEdit = (QLineEdit *)sender();
        if(lineEdit == ui->HEX_QLineEdit)
        {
            QString str = ui->HEX_QLineEdit->text();
            formatHex(str);

            // QString to HEX
            ulong hex_str = str.right(8).toULong(0,16);

            //unit to DEC, then to QString
            QString str_DEC= QString::number(hex_str,10);

            ui->HEX_QLineEdit->setText(str);
            ui->DEC_QLineEdit->setText(str_DEC);
        }
        else if(lineEdit == ui->DEC_QLineEdit)
        {
            QString str = ui->DEC_QLineEdit->text();
            // QString to DEC
            ulong hex_str = str.right(10).toULong(0,10);
            //unit to DEC, then to QString
            QString str_DEC= "0x"+ QString::number(hex_str,16);
            ui->HEX_QLineEdit->setText(str_DEC);

        }
        else
        {
            qDebug() << "others \n";
        }

}

void MainWindow::formatHex( QString &str)
{
    if ((str[1]=="x")||(str[1]=="X"))
    {
        str.replace(0,2,"0x");
        str = str.left(10);
    }
    else
    {
        str.insert(0,"0x");
        str = str.left(10);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
