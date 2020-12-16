#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qfiledialog.h"
#include "qbytearray.h"
#include "outputfunc.h"
#include "ui_buffer.h"
#include <qdebug.h>

using namespace std;
MainWindow::MainWindow(int argc, char *argv[],QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->regInfo->setLineWrapMode(QTextBrowser::NoWrap);
    ui->cp0Info->setLineWrapMode(QTextBrowser::NoWrap);
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
    int i = ui_solvecmd(ch);
    if(i == -2)
        QApplication::exit();
    ui->cmd->setText(QString::fromUtf8(result_buf));
    if(strncmp(ch,"info" , 4) == 0 ||
       strcmp(ch , "c") == 0 ||
       strncmp(ch , "si" , 2) == 0){
       ui->regInfo->setText(QString::fromUtf8(reg_buf));
       ui->cp0Info->setText(QString::fromUtf8(cp0_buf));
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



void MainWindow::on_actionopen_triggered()
{
    char buf[1024];
    char *c = buf;
    int space_left = sizeof(buf);
    int sz = 0;

    QString fileName = QFileDialog::getOpenFileName(this,
                                                        tr("open a .S file！"),
                                                        "../TEMU/mips_sc/src",
                                                        tr("*S"));
    if(fileName.isEmpty()){
        return;
    }
    QStringList file = fileName.split("/");
    QByteArray ba = file[file.size()-1].split(".")[0].toLatin1();
    char* file_name = ba.data();

    sz = snprintf(c, space_left, "../TEMU/mips_sc/start.sh %s ",file_name);
    c += sz;
    space_left -= sz;

    system(buf);
    int argc = 1;
    char* argv[2];
    strcpy(ui_inst , "");
    char* str = initSys(argc , argv);
    ui->cmd->setText(QString(str));
    ui->regInfo->setText(reg_buf);
    ui->cp0Info->setText(cp0_buf);
    ui->text->setText(QString(ui_inst));
}
