#include "ejemplos.h"
#include "ui_ejemplos.h"
#include<QFile>
#include<QDirIterator>
#include<QDebug>
#include<QMessageBox>
#include<QClipboard>
QString fileName,f;QFile file; QFileInfo fileInfo;QTextStream in;
ejemplos::ejemplos(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ejemplos)
{
    ui->setupUi(this);
highlighter = new Highlighter(ui->textEdit->document());

    QString path = "./Ejemplos";
        QDir dir(path);
        QStringList filters;
        filters << "*.vhdl";

        foreach (QFileInfo fileInfo, dir.entryInfoList(filters, QDir::Files))
        {
            fileName = fileInfo.absoluteFilePath();
            f=fileInfo.absolutePath();
           //qDebug(fileInfo.absoluteFilePath().toLocal8Bit());
           QFile readFile(fileInfo.absoluteFilePath());
           if(!readFile.open(QIODevice::ReadOnly | QIODevice::Text ) )
                 {
                   ui->textEdit->setText("Failed to read file.....");
                   //return ;
                 }
                 QTextStream in(&fileName);
                 while (!in.atEnd())
                 {
                     QString line = in.readLine();

                     ui->listWidget->addItem(fileInfo.fileName());
                     ui->textEdit->append(fileName);

                 }
        }


//ui->textEdit->setText("");

}

ejemplos::~ejemplos()
{
    delete ui;
}




void ejemplos::on_listWidget_itemChanged(QListWidgetItem *item)
{





}

void ejemplos::on_listWidget_itemSelectionChanged()
{
    QFile file("Ejemplos/"+ui->listWidget->currentItem()->text());
    QTextStream in(&file);
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }
    else {ui->textEdit->setPlainText("");
        ui->textEdit->setText(in.readAll());

    }
}

void ejemplos::on_pushButton_2_clicked()
{
    QClipboard *clipboard = QApplication::clipboard();
            QString n=ui->textEdit->toPlainText();
            clipboard->setText(n);
}
