#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qbytearray.h"
#include "../TEMU/temu/include/initsys.h"
using namespace std;
MainWindow::MainWindow(int argc, char *argv[],QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    char* str = initSys(argc , argv);
    ui->setupUi(this);
    ui->textEdit->setText(QString(str));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString str = ui->textEdit->toPlainText();
    char*  ch;
    QByteArray ba = str.toLatin1();
    ch=ba.data();
    printf("%s",ch);
}
