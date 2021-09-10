#include "mainwindow.h"
#include "ui_mainwindow.h"

#define NAME(i)  #i

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label_H->setAlignment(Qt::AlignCenter);
    ui->label_L->setAlignment(Qt::AlignCenter);

    //INIT
    //1.1 set HEX LEN 10
    ui->HEX_QLineEdit->setMaxLength(10);

    //2.1set DEC_LINEEDIT

    //3.1 set PushButton
    QList<QPushButton*> QPushButton_list = findChildren<QPushButton*>();

    for(int i = 0 ; i < 32; i++)
    {
        QPushButton_list[i]->setStyleSheet("QPushButton{color:black;background:white}");
     }



    // HEX/DEC
    connect(ui->HEX_QLineEdit, SIGNAL(returnPressed()), this, SLOT(turnCode()));
    connect(ui->DEC_QLineEdit, SIGNAL(returnPressed()), this, SLOT(turnCode()));
    //HEX/DEC TO  BIN
    connect(ui->HEX_QLineEdit, SIGNAL(returnPressed()), this, SLOT(turnBIN()));
    connect(ui->DEC_QLineEdit, SIGNAL(returnPressed()), this, SLOT(turnBIN()));


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
            g_data = hex_str;
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
            g_data = hex_str;
            //unit to DEC, then to QString
            QString str_DEC= "0x"+ QString::number(hex_str,16);
            ui->HEX_QLineEdit->setText(str_DEC);

        }
        else
        {
            qDebug() << "others \n";
        }

}

void MainWindow::turnBIN()
{
//    QList<QPushButton*> QPushButton_list;//test
//           QPushButton_list <<ui->PB1<<ui->PB2\
//                                <<ui->PB3<<ui->PB4<<ui->PB5<<ui->PB6\
//                                <<ui->PB7<<ui->PB8<<ui->PB9<<ui->PB10\
//                                <<ui->PB11<<ui->PB12<<ui->PB13<<ui->PB14\
//                                <<ui->PB15<<ui->PB16<<ui->PB17<<ui->PB18\
//                                <<ui->PB19<<ui->PB20<<ui->PB21<<ui->PB22\
//                                <<ui->PB23<<ui->PB24<<ui->PB25<<ui->PB26\
//                                <<ui->PB27<<ui->PB28<<ui->PB29<<ui->PB30\
//                                <<ui->PB31<<ui->PB32;

   QList<QPushButton*> QPushButton_list = findChildren<QPushButton*>();
   QString bin_str =  QString("%1").arg(g_data, 32, 2, QChar('0'));
   int i = 0;
   for( i ; i < 32; i++)
   {
         QString temp_str = bin_str.mid( i, 1);
         qDebug() << temp_str;
         QPushButton_list[i] ->setText(temp_str);
         QString one = "1";
         if(one == temp_str)
         {
             QPushButton_list[i]->setStyleSheet("QPushButton{color:red;background:yellow}");
         }
         else
         {
             QPushButton_list[i]->setStyleSheet("QPushButton{color:black;background:white}");
         }
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
