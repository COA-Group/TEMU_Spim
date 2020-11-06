#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qbytearray.h"
#include "outputfunc.h"
#include "ui_buffer.h"
#include <qdebug.h>

using namespace std;
MainWindow::MainWindow(int argc, char *argv[],QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    char* str = initSys(argc , argv);
    ui->setupUi(this);
    ui->cmd->setText(QString(str));
    ui->regInfo->setText(reg_buf);
    ui->text->setText(QString(ui_inst));
    ui->regInfo->setLineWrapMode(QTextBrowser::NoWrap);
    ui->cmd->setLineWrapMode(QTextBrowser::NoWrap);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::action_cmd(){
    QString str = ui->lineEdit->text();
    char*  ch;
    QByteArray ba = str.toLatin1();
    ch=ba.data();
    qDebug()<<ch;
    int i = ui_solvecmd(ch);
    if(i == -2)
        QApplication::exit();
    ui->cmd->setText(QString::fromUtf8(result_buf));
    if(strncmp(ch,"info" , 4) == 0 ||
       strcmp(ch , "c") == 0 ||
       strncmp(ch , "si" , 2) == 0){
       ui->regInfo->setText(QString::fromUtf8(reg_buf));
    }

}

void MainWindow::on_pushButton_clicked()
{
    this->action_cmd();
}

void MainWindow::on_lineEdit_returnPressed()
{
    this->action_cmd();
}


