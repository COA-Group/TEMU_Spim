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
    ui->text->setText(QString(ui_inst));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString str = ui->textEdit_2->toPlainText();
    char*  ch;
    QByteArray ba = str.toLatin1();
    ch=ba.data();
    qDebug()<<ch;

    int i = ui_solvecmd(ch);
//    qDebug()<<result_buf;
    if(i == -2)
        QApplication::exit();
    ui->cmd->setText(QString(result_buf));
    if(strcmp(ch,"c") == 0){
        ui->cmd->setText(QString::fromUtf8(result_buf));
    }
}
