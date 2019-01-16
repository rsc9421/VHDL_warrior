#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<math.h>
#include<QComboBox>
#include<QMessageBox>
using namespace std;
#include<QStringList>
#include<QFont>
#include<QRegularExpressionMatchIterator>
#include<QSplitter>
#include<QFileSystemModel>
#include <QCloseEvent>
#include<QCompleter>
#include<QToolTip>
#include<QStringListModel>
#include<QMovie>
int current1,current2,previous1,previous2;
QFileSystemModel *dirModel;
QFileSystemModel *fileModel;
  int n_component=0;
 QCompleter *completer;
QStringList items,items_cargados,init_component,inst_component,items_normales,items_testbench;
 char r[500];
 QStringList fa;
 QMenu* menu_componente;
 int hh;
 string str2,str,str3,str4; size_t found,found2,found3,found4;string yut;int h2=0;
 bool oscuro=0,gtkwave=0;
    QString ubicacionActual,nombreActual;
    QStringList nombres_verticales_entradas,bits_lista,in_lista;
string proyecto,proyecto_copia;
void reemplazar( string &s, const string &search, const string &replace ) {
    for( size_t pos = 0; ; pos += replace.length() ) {
        // Locate the substring to replace
        pos = s.find( search, pos );
        if( pos == string::npos ) break;
        // Replace by erasing and inserting
        s.erase( pos, search.length() );
        s.insert( pos, replace );
    }
}

void MainWindow::guardar(QString dir) {
    dir=dir.replace(".vhdl","");
    dir+=".vhdl";
    QFile file2(dir);
        if(!file2.open(QFile::WriteOnly | QFile::Text)){}
        QTextStream out(&file2);
        out << ui->textEdit->toPlainText();
        file2.flush();
        file2.close();
        QString a= ui->listWidget->currentItem()->text();
        a=a.replace("*","");
        ui->listWidget->currentItem()->setText(a);
}
QString MainWindow::get_component3(QString dir, QString codigo){
    string proyecto,proyecto2;
    proyecto.clear();
    QString nombre_puro=nombreActual.replace(".vhdl","");

    proyecto2+=": "+nombre_puro.toStdString()+" port map(";

    QString txt2,txt,a2;int primer_parentesis,segundo_parentesis;QStringList lista2,b2;QString temp32;int tempo2=0,mas_sig2,menos_sig2;
    QString component;
    QFileInfo fileInfo;QTextStream in;
    QStringList signal_lista,lista;int i=0;QString temp3;int mas_sig,menos_sig;
/*
    QFile file(dir);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {   }
    else {
        fileInfo=(file.fileName());
        in.setDevice(&file);
        txt2=in.readAll();
    }
*/
    txt2=codigo;

    signal_lista.clear();
    txt=txt2;
    txt=txt.simplified();
    txt.replace( " ", "" );
     primer_parentesis=txt.indexOf("port(");
    segundo_parentesis=txt.indexOf(");end");

    primer_parentesis+=5;
    segundo_parentesis+=0;
    r[0]='\0';

    for(i=primer_parentesis;i<segundo_parentesis;i++){
        r[i-primer_parentesis]=txt.toUtf8().constData()[i];
    }
    r[i]='\0';
     lista=QString(r).split(';');

    for(i=0;i<lista.length();i++){
    mas_sig=0;menos_sig=0;
    QString a=lista[i];
    if(a.contains("in")||a.contains("out")){
    QStringList b=a.split(':');

    temp3=b[0];


    if(temp3.contains(',')){

    QStringList b=temp3.split(',');
    for(int k=0;k<b.length();k++){
        signal_lista<<b[k];
        proyecto+='\n';
       proyecto+=b[k].toStdString();
       proyecto+=" => ";
       proyecto+=b[k].toStdString();

            proyecto+=",";
    }
    }
    else{
        signal_lista<<temp3;
        proyecto+='\n';
        proyecto+=temp3.toStdString();
        proyecto+=" => ";
        proyecto+=temp3.toStdString();

               proyecto+=",";
    }
    }
    }
    for(int i=0;i<signal_lista.length();i++){
      proyecto2+=signal_lista[i].toStdString()+" =>  ";
      if(i!=signal_lista.length()-1)proyecto2+=",";
    }
    //QString a56=QString::fromStdString(proyecto2);
    //int k=proyecto2.find_last_of(',');
    //proyecto2[k]=' ';
    proyecto2+=");";

    //qDebug()<<"signal_lista"<<signal_lista;
    return QString::fromStdString(proyecto2);
}
QString get_component2(QString dir, QString codigo){
    string proyecto;
    proyecto.clear();
    QString nombre_puro=nombreActual.replace(".vhdl","");

    proyecto+="component "+nombre_puro.toStdString()+" is port(\n";

    QString txt2,a2;int primer_parentesis2,segundo_parentesis2;QStringList lista2,b2;QString temp32;int tempo2=0,mas_sig2,menos_sig2;
    QString component;
    QFileInfo fileInfo;QTextStream in;
/*
    QFile file(dir);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {   }
    else {
        fileInfo=(file.fileName());
        in.setDevice(&file);
        txt2=in.readAll();
    }
*/
    txt2=codigo;
    txt2=txt2.simplified();
    txt2.replace( " ", "" );
     primer_parentesis2=txt2.indexOf("port(");
     segundo_parentesis2=txt2.indexOf(");end");

    primer_parentesis2+=5;
    segundo_parentesis2+=0;
    r[0]='\0';
int i=0;
    for(i=primer_parentesis2;i<segundo_parentesis2;i++){
        r[i-primer_parentesis2]=txt2.toUtf8().constData()[i];
    }
    r[i]='\0';
     lista2=QString(r).split(';');

    for(i=0;i<lista2.length();i++){
    a2=lista2[i];
    if(a2.contains("in") || a2.contains("out") || a2.contains("inout")){
    b2=a2.split(':');

    component+=b2[0];
    component+=" : ";
     if(a2.contains("in")) component+="in ";
     if(a2.contains("out")) component+="out ";
     if(a2.contains("inout")) component+="inout ";


    if(b2[1].contains("downto")){
    QRegularExpression rx("[0-9]+");
    QRegularExpressionMatchIterator matches = rx.globalMatch(b2[1]);
    tempo2=0;
    while (matches.hasNext()) {

        QRegularExpressionMatch match = matches.next();
        if(tempo2==0){mas_sig2 = match.captured(0).toInt();tempo2=1;}else {
            menos_sig2 = match.captured(0).toInt();
        }
    }
    //nombres_in<<temp3+" : std_logic_vector("+QString::number(mas_sig)+" downto "+QString::number(menos_sig)+");";

    component+="std_logic_vector("+QString::number(mas_sig2)+" downto "+QString::number(menos_sig2)+");\n";
    }
    else{
 component+="std_logic;\n";

    }
    }
    }

    proyecto+=component.toStdString();


    QString h2=QString::fromStdString(proyecto);
    int h3=h2.lastIndexOf(";");
    h2.replace(h3,1,");");
    proyecto=h2.toStdString();

    proyecto+="end component;\n";
    return QString::fromStdString(proyecto);
}
string removeSpaces(string input)
{
  input.erase(std::remove(input.begin(),input.end(),' '),input.end());
  return input;
}

void MainWindow::declarar_componente(){
    QString fileName,f;QFile file; QFileInfo fileInfo;QTextStream in;
    QStringList archivos;
    //ubicacionActual=dirPuro[ui->listWidget->currentRow()];
    QString path = ubicacionActual;
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
                     if(!fileInfo.fileName().contains("_tb.vhdl"))
                     archivos<<fileInfo.fileName();
                 }
        }


fa.clear();init_component.clear();

for(int i=0;i<archivos.length();i++){
    if(!oscuro) ui->textEdit_2->setTextColor(Qt::black);
    else {
       ui->textEdit_2->setTextColor(Qt::white);
    }
nombreActual=archivos[i];
if(!archivos[i].contains("_tb.vhdl")){
    fa<<nombreActual;
           QString dir=ubicacionActual+nombreActual;
           QString r=get_component2((dir),codigo[i]);
           QString r1=get_component3((dir),codigo[i]);
         init_component<<r;
inst_component<<r1;
}
}

    QStringList wordList;
    wordList = fa;



     completer = new QCompleter(wordList, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setWidget(ui->textEdit);
QRect a=ui->textEdit->cursorRect();
QRect b(a.x(),a.y(),300,20);
completer->complete(b);
connect(completer, SIGNAL(activated(QString)),
                     this, SLOT(insertCompletion(QString)));
}

void MainWindow::instancear_componente(){
    QString fileName,f;QFile file; QFileInfo fileInfo;QTextStream in;
    QStringList archivos;
    //ubicacionActual=dirPuro[ui->listWidget->currentRow()];
    QString path = ubicacionActual;
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
                     if(!fileInfo.fileName().contains("_tb.vhdl"))
                     archivos<<fileInfo.fileName();
                 }
        }

fa.clear();init_component.clear();
for(int i=0;i<archivos.length();i++){
    if(!oscuro) ui->textEdit_2->setTextColor(Qt::black);
    else {
       ui->textEdit_2->setTextColor(Qt::white);
    }
nombreActual=archivos[i];
if(!archivos[i].contains("_tb.vhdl")){
    fa<<nombreActual;
           QString dir=ubicacionActual+nombreActual;
           QString r=get_component2((dir),codigo[i]);
           QString r1=get_component3((dir),codigo[i]);
         init_component<<r;
inst_component<<r1;
}
}
    QStringList wordList;
    wordList = fa;
     completer = new QCompleter(wordList, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setWidget(ui->textEdit);
QRect a=ui->textEdit->cursorRect();
QRect b(a.x(),a.y(),300,20);
completer->complete(b);
connect(completer, SIGNAL(activated(QString)),
                     this, SLOT(insertCompletion2(QString)));
}

bool MainWindow::compilar(QString dir){
  bool  compiladobn=0;
    if(!oscuro) ui->textEdit_2->setTextColor(Qt::black);
    else {
       ui->textEdit_2->setTextColor(Qt::white);
    }


    dir=dir.replace(".vhdl","");
    dir+=".vhdl";



 process.setWorkingDirectory(ubicacionActual);
 ui->textEdit_2->append("$ ghdl -a "+dir);
     process.start("ghdl -a "+dir);
     process.waitForFinished(-1); // will wait forever until finished

      Consola = process.readAllStandardOutput();
      errorConsola = process.readAllStandardError();
      if(errorConsola.isEmpty()){
          if(!oscuro)ui->textEdit_2->setTextColor(Qt::darkGreen);
          else {
              ui->textEdit_2->setTextColor(Qt::green);
          }
          ui->textEdit_2->append("<html><font color=\"blue\"><b>Build successful</b</html>");
      compiladobn=1;}

     else{ui->textEdit_2->setTextColor(Qt::black);
          QStringList b2=errorConsola.split("\n");
          for(int i=0;i<b2.length()-1;i++){
             QStringList b1=b2[i].split(":");
             if(!oscuro)
          ui->textEdit_2->append("<html><font color=\"red\"><b>Error in line "+b1[1]+": </b</html>"+"<html><font color=\"black\">"+errorConsola+"</html>");
             else {
                  ui->textEdit_2->append("<html><font color=\"red\"><b>Error in line "+b1[1]+": </b</html>"+"<html><font color=\"white\">"+errorConsola+"</html>");
             }


         QTextCursor cursor(ui->textEdit->document()->findBlockByLineNumber(b1[1].toInt()-1));
    ui->textEdit->setTextCursor(cursor);
          }
 }
 ui->textEdit_2->verticalScrollBar()->setValue(ui->textEdit_2->verticalScrollBar()->maximum());
 return compiladobn;
}
long long DtoB(int n)
{
    long long binaryNumber = 0;
    int remainder, i = 1, step = 1;

    while (n!=0)
    {
        remainder = n%2;
        n /= 2;
        binaryNumber += remainder*i;
        i *= 10;
    }
    return binaryNumber;
}
int BtoD(long long n)
{
    int decimalNumber = 0, i = 0, remainder;
    while (n!=0)
    {
        remainder = n%10;
        n /= 10;
        decimalNumber += remainder*pow(2,i);
        ++i;
    }
    return decimalNumber;
}
std::string nameFromFile(const std::string& fullPath)
{
  const size_t lastSlashIndex = fullPath.find_last_of("/\\");
  return fullPath.substr(lastSlashIndex + 1);
}
string get_component(string direccion_archivo){
    std::locale loc;
    ifstream file(direccion_archivo);
    string str, component, b;
    string signal_out,signal_out_nombres,signal_in,singla_in_nombres;
     while (getline(file, str))
     {
     b.clear();
     for (std::string::size_type i=0; i<str.length(); ++i)
     b+= std::toupper(str[i],loc);
     if (b.find("END") != std::string::npos){break;}
     else {
         component+=b;
         component+='\n';
    }
    }
    reemplazar(component,"ENTITY","COMPONENT");
    component+="END COMPONENT;\n";

    return component;
}
string testbench;
unsigned int sd=1;
QStringList signal_lista;
QString convertidorActual="decimal",signales_valores;
string name_actual,namePuro_actual,name_tb_actual,namePuro_tb_actual;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->textEdit_3->setText("");
for(sd=1;sd<= ui->textEdit->document()->blockCount();sd++){
    ui->textEdit_3->append(QString::number(sd));
ui->textEdit_3->setAlignment(Qt::AlignRight);}
ui->textEdit_3->verticalScrollBar()->setValue(ui->textEdit->verticalScrollBar()->value());
    connect(ui->textEdit->verticalScrollBar(), SIGNAL(valueChanged(int)), ui->textEdit_3->verticalScrollBar(), SLOT(setValue(int)));
    //connect(ui->textEdit_3->verticalScrollBar(), SIGNAL(valueChanged(int)), ui->textEdit->verticalScrollBar(), SLOT(setValue(int)));
    connect(&process , SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(processFinished(int, QProcess::ExitStatus)));
    //
 ui->textEdit->setContextMenuPolicy(Qt::CustomContextMenu);
      connect(ui->textEdit,SIGNAL(customContextMenuRequested(const QPoint&)),
        this,SLOT(showContextMenu(const QPoint &)));

    ui->textEdit->verticalScrollBar()->setValue(0); ui->textEdit_3->verticalScrollBar()->setValue(0);
    ui->textEdit_3->setReadOnly(true);
QMainWindow::showMaximized();
highlighter = new Highlighter(ui->textEdit->document());

ui->groupBox_2->setVisible(false);
ui->groupBox->setVisible(false);
ui->groupBox_5->setVisible(false);
ui->groupBox_4->setVisible(true);
oscuro=0;

QPixmap p(":/iconos/sm.jpg"); // load pixmap
//ui->label->setPixmap(p);
//ui->groupBox->setStyleSheet("QGroupBox{padding-top:15px; margin-top:-15px}");

QString sPath = QDir::rootPath();
   dirModel = new QFileSystemModel(this);
   dirModel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
   dirModel->setRootPath(sPath);
   ui->treeView->setModel(dirModel);
   fileModel = new QFileSystemModel(this);
   fileModel->setFilter(QDir::NoDotAndDotDot | QDir::Files);
   fileModel->setRootPath(sPath);

       QStringList filters;
       filters << "*.vhdl";
       fileModel->setNameFilters(filters);
       fileModel->setNameFilterDisables(false);
   for (int i = 1; i < dirModel->columnCount(); ++i)
       ui->treeView->hideColumn(i);


ui->groupBox->setStyleSheet("QGroupBox {  border: 0px solid gray;}");


ui->textEdit_3->setStyleSheet("color: rgb(110,110,110);"
                              "background-color: rgb(240,240,240);"
                              "foreground-color: rgb(110,110,110);"
                              "selection-background-color: rgb(90,90,90);");
//cambiar la fuente por monospace del sistema

//const QFont fixedFont = QFontDatabase::systemFont(QFontDatabase::FixedFont);
//ui->textEdit->setFont(fixedFont);
//ui->textEdit_3->setFont(fixedFont);
QFont font("Courier New");
font.setStyleHint(QFont::Monospace);
 ui->textEdit->setFont(font);
 ui->textEdit_3->setFont(font);
  ui->textEdit_2->setFont(font);
  ui->pushButton_3->setFont(font);
   ui->pushButton_6->setFont(font);


ui->textEdit->installEventFilter(this);
ui->textEdit->setLineWrapMode(QTextEdit::NoWrap);
ui->textEdit_2->installEventFilter(this);
ui->textEdit_2->setLineWrapMode(QTextEdit::NoWrap);
ui->textEdit_3->setAlignment(Qt::AlignRight);
//ui->textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);



/*
QPixmap pixmap3(":/iconos/b4.png");
QIcon ButtonIcon3(pixmap3);
ui->pushButton_2->setIcon(ButtonIcon3);
ui->pushButton_2->setIconSize(pixmap3.size());
ui->pushButton->setIcon(ButtonIcon3);
ui->pushButton->setIconSize(pixmap3.size());
*/



ui->treeView->setVisible(false);

//ui->groupBox_3->sizePolicy().setHorizontalStretch(4);
//ui->groupBox_8->sizePolicy().setHorizontalStretch(1);
QMainWindow::showNormal();
QMainWindow::resize(840,720);
ui->splitter_3->setSizes(QList<int>() << 350 << 100);
ui->splitter_2->setSizes(QList<int>() << 50 << 100);


ui->centralWidget->setStyleSheet(
                              "selection-background-color: rgba(0, 0, 255, 200);");
ui->menuBar->setStyleSheet(
            "selection-background-color: rgba(0, 0, 255, 200);");


QMovie *mv = new QMovie(":/iconos/dragoon1.gif");
//ui->label->setWindowFlag(Qt::FramelessWindowHint);
//ui->label->setMask((new QPixmap(":/iconos/dragoon1.png"))->mask());
ui->label->setAttribute(Qt::WA_NoSystemBackground);
ui->label->setMovie(mv);
mv->start();
}


void MainWindow::resizeEvent(QResizeEvent* event)
{
   QMainWindow::resizeEvent(event);
   QPixmap p("F.png"); // load pixmap
   // get label dimensions
   int w = ui->groupBox_4->width();
   int h = ui->groupBox_4->height();

   // set a scaled pixmap to a w x h window keeping its aspect ratio
   //ui->label_5->setPixmap(p.scaled(w,h,Qt::KeepAspectRatio));
}

MainWindow::~MainWindow()
{





        ejemplo.close();
    delete ui;

}
void MainWindow::closeEvent (QCloseEvent *event)
{
    if(ui->listWidget->count()>0){
    for(int i = 0; i < ui->listWidget->count(); i++){
         if(ui->listWidget->item(i)->text().contains("*")){
             QMessageBox::StandardButton reply;
             QString b=ui->listWidget->item(i)->text().replace("*","");
           reply =  QMessageBox::question(this,"Files without saving","There are files without saving\nSave "+b+"?", QMessageBox::Yes | QMessageBox::No);
           if (reply == QMessageBox::Yes) { guardar(ubicacionActual+b);event->ignore();} else{event->accept();}
         }
    }
    }

}
void MainWindow::on_actionAbrir_triggered()
{
    dir = QFileDialog::getOpenFileName( this,tr("Abrir .VHDL")," ",tr("VHDL (*.vhdl)"));
    QString nom=dir.mid(dir.lastIndexOf("/")+1,dir.length());
    QString fol=dir.mid(0,dir.lastIndexOf("/"));fol+="/";
//ui->listView->setRootIndex(fileModel->setRootPath(fol));
ui->treeView->setCurrentIndex(dirModel->setRootPath(fol));
//ui->listWidget->setRootIndex(fileModel->setRootPath(nom));
//guardar
ubicacionActual=fol;
nombreActual=nom;
nombreActual.replace(".vhdl","");
nombreActual+=".vhdl";
QString dir=ubicacionActual+nombreActual;

//cargar


  //  dirModel->setRootPath("");
ui->treeView->setCurrentIndex(dirModel->setRootPath(fol));


    ui->listWidget->blockSignals(true);
    ui->listWidget->clear();
    ui->listWidget->blockSignals(false);

    items.clear();items_normales.clear();items_testbench.clear();
            QDir path(fol);
            QStringList filters;
            filters << "*.vhdl";
            path.setNameFilters(filters);
            items = path.entryList();


for(int i=0;i<items.length();i++){
QListWidgetItem * a = new QListWidgetItem(items[i]);
if(!a->text().contains("_tb")){
items_normales<<items[i];
a->setIcon(QIcon(":/iconos/file7.png"));
ui->listWidget->addItem(a);
}
else {

items_testbench<<items[i];
a->setIcon(QIcon(":/iconos/file8.png"));
ui->listWidget_2->addItem(a);
}
}

for(int i=0;i<items_testbench.length();i++){
QString dir=ubicacionActual+items_testbench[i];
QFile file(dir);
if (!file.open(QIODevice::ReadOnly | QIODevice::Text))return;
else {
 fileInfo=(file.fileName());
 nombre_t[i]=fileInfo.fileName();
 dirPuro_t[i]=fileInfo.absolutePath();dirPuro[i]+='/';
 in.setDevice(&file);
 codigo_t[i]=in.readAll();
 ui->textEdit_3->setText("");
 for(sd=1;sd<= ui->textEdit->document()->blockCount();sd++){
 ui->textEdit_3->append(QString::number(sd));
 ui->textEdit_3->setAlignment(Qt::AlignRight);}
 ui->textEdit_3->verticalScrollBar()->setValue(ui->textEdit->verticalScrollBar()->value());
 ui->listWidget_2->setCurrentRow(0);
}
}

for(int i=0;i<items_normales.length();i++){
QString dir=ubicacionActual+items_normales[i];
QFile file(dir);
if (!file.open(QIODevice::ReadOnly | QIODevice::Text))return;
else {
 fileInfo=(file.fileName());
 nombre[i]=fileInfo.fileName();
 dirPuro[i]=fileInfo.absolutePath();dirPuro[i]+='/';
 in.setDevice(&file);
 codigo[i]=in.readAll();
 ui->textEdit_3->setText("");
 for(sd=1;sd<= ui->textEdit->document()->blockCount();sd++){
 ui->textEdit_3->append(QString::number(sd));
 ui->textEdit_3->setAlignment(Qt::AlignRight);}
 ui->textEdit_3->verticalScrollBar()->setValue(ui->textEdit->verticalScrollBar()->value());
 if(items_normales[i]==nom){ui->listWidget->setCurrentRow(i);ui->textEdit->setText(codigo[i]);}
}
}

ui->groupBox->setVisible(true);
ui->groupBox_2->setVisible(false);
ui->groupBox_4->setVisible(false);
ui->groupBox_5->setVisible(false);



}

void MainWindow::on_pushButton_4_clicked()
{
    if(ui->listWidget->count()>0){
    for(int i = 0; i < ui->listWidget->count(); i++){
         if(ui->listWidget->item(i)->text().contains("*")){
             QMessageBox::StandardButton reply;
             QString b=ui->listWidget->item(i)->text().replace("*","");
            reply =  QMessageBox::question(this,"Files without saving","There are files without saving\nSave "+b+"?", QMessageBox::Yes | QMessageBox::No);
           if (reply == QMessageBox::Yes) { guardar(ubicacionActual+b);} else{}
         }
    }
    }

    ui->groupBox_4->setVisible(false);
    ui->groupBox_2->setVisible(false);
    ui->groupBox->setVisible(false);
    ui->groupBox_5->setVisible(true);
    int n = ui->lineEdit_7->text().toULong();

    ui->tableWidget_2->setRowCount(n);
    ui->tableWidget_2->setColumnCount(3);
    QStringList lis2=(QStringList()<<"Port name"<<"Direction"<<"Bits");
    ui->tableWidget_2->setHorizontalHeaderLabels(lis2);

    for(int i=0;i<n;i++){
    QComboBox* combobox = new QComboBox();
    ui->tableWidget_2->setCellWidget(i,1,combobox);
    QStringList list=(QStringList()<<"in"<<"out"<<"inout");
    combobox->addItems(list);

    #if (defined (_WIN32) || defined (_WIN64))
     ui->lineEdit_5->setText("C:\Windows");
    #endif
    #if (defined (LINUX) || defined (__linux__))
     ui->lineEdit_5->setText("/home/"+qgetenv("USER")+"/");
    #endif


    }
}



void MainWindow::on_pushButton_2_clicked()
{
         ui->textEdit_2->setText("");
    //guardar todo
 codigo[ui->listWidget->currentRow()]=ui->textEdit->toPlainText();
    for (int f=0;f<ui->listWidget->count();f++){

        QString dir=ubicacionActual+items_normales[f];
        QFile file2(dir);
            if(!file2.open(QFile::WriteOnly | QFile::Text)){return;}
            QTextStream out(&file2);
            out << codigo[f];
            file2.flush();
            file2.close();

                QString a= ui->listWidget->item(f)->text();
                a=a.replace("*","");
                ui->listWidget->item(f)->setText(a);

    }
    for (int f=0;f<ui->listWidget->count();f++){
        QString dir=ubicacionActual+items_normales[f];
        compilar(items_normales[f]);
    }

}

void MainWindow::on_actionGuardar_triggered()
{
    QString dir=ubicacionActual+nombreActual+".vhdl";
    QFile file2(dir);
        if(!file2.open(QFile::WriteOnly | QFile::Text)){return;}
        QTextStream out(&file2);
        out << ui->textEdit->toPlainText();
        file2.flush();
        file2.close();
        QString a= ui->listWidget->currentItem()->text();
        a=a.replace("*","");
        ui->listWidget->currentItem()->setText(a);
}

void MainWindow::on_actionGuardar_como_triggered()
{
    dir = QFileDialog::getSaveFileName(this, tr("Save"),"new_file",tr("VHDL (*.vhdl)"));
    QFile file2(dir);
        if(!file2.open(QFile::WriteOnly | QFile::Text)){return;}
        QTextStream out(&file2);
        out << ui->textEdit->toPlainText();
        file2.flush();
        file2.close();
        QString a= ui->listWidget->currentItem()->text();
        a=a.replace("*","");
        ui->listWidget->currentItem()->setText(a);
}

void MainWindow::on_pushButton_clicked()
{
         ui->textEdit_2->setText("");


 guardar(ubicacionActual+nombreActual+".vhdl");
 compilar(nombreActual+".vhdl");
}

void MainWindow::on_radioButton_clicked()
{
    QStringList nn;
    if(convertidorActual=="decimal"){
        for(int i=0;i<ui->tableWidget->model()->rowCount();i++){
            for(int j=0;j<ui->tableWidget->model()->columnCount();j++){
ui->tableWidget->setItem(i,j,new QTableWidgetItem(QString::number(DtoB(ui->tableWidget->item(i,j)->text().toLong()))));
            }
        }
    }
    convertidorActual="binario";
}

void MainWindow::on_radioButton_2_clicked()
{
    if(convertidorActual=="binario"){
        for(int i=0;i<ui->tableWidget->model()->rowCount();i++){
            for(int j=0;j<ui->tableWidget->model()->columnCount();j++){

    ui->tableWidget->setItem(i,j,new QTableWidgetItem(QString::number(BtoD(ui->tableWidget->item(i,j)->text().toLong()))));
            }
        }
    }
    convertidorActual="decimal";
}

void MainWindow::on_lineEdit_returnPressed()
{

}

void MainWindow::on_listWidget_clicked(const QModelIndex &index)
{


 /*
    codigo[ui->listWidget->currentRow()]=ui->textEdit->toPlainText();
ui->textEdit->setText("");
    int n= ui->listWidget->currentRow();
i=n;
    ui->textEdit->setText(codigo[n]);
    name_actual=nombre[n].toUtf8().constData();
    QString tmp=name_actual.c_str();
    name_tb_actual = tmp.replace(".vhdl","_tb.vhdl").toUtf8().constData();
    namePuro_actual = tmp.replace(".vhdl"," ").toUtf8().constData();
    namePuro_tb_actual = tmp.replace(".vhdl","_tb").toUtf8().constData();


    dir=direccion[n];
*/


//    ui->listWidget->setPalette(this->style()->standardPalette());
//    QListWidgetItem *item= ui->listWidget->currentItem();
//    item->setBackgroundColor(QColor(255,196,0));
}


void MainWindow::on_pushButton_6_clicked()
{
    dir = QFileDialog::getOpenFileName( this,tr("Abrir .VHDL")," ",tr("VHDL (*.vhdl)"));
    QString nom=dir.mid(dir.lastIndexOf("/")+1,dir.length());
    QString fol=dir.mid(0,dir.lastIndexOf("/"));fol+="/";
//ui->listView->setRootIndex(fileModel->setRootPath(fol));
ui->treeView->setCurrentIndex(dirModel->setRootPath(fol));
//ui->listWidget->setRootIndex(fileModel->setRootPath(nom));
//guardar
ubicacionActual=fol;
nombreActual=nom;
nombreActual.replace(".vhdl","");
nombreActual+=".vhdl";
QString dir=ubicacionActual+nombreActual;

//cargar


  //  dirModel->setRootPath("");
ui->treeView->setCurrentIndex(dirModel->setRootPath(fol));


    ui->listWidget->blockSignals(true);
    ui->listWidget->clear();
    ui->listWidget->blockSignals(false);

    items.clear();items_normales.clear();items_testbench.clear();
            QDir path(fol);
            QStringList filters;
            filters << "*.vhdl";
            path.setNameFilters(filters);
            items = path.entryList();


for(int i=0;i<items.length();i++){
QListWidgetItem * a = new QListWidgetItem(items[i]);
if(!a->text().contains("_tb")){
items_normales<<items[i];
a->setIcon(QIcon(":/iconos/file7.png"));
ui->listWidget->addItem(a);
}
else {

items_testbench<<items[i];
a->setIcon(QIcon(":/iconos/file8.png"));
ui->listWidget_2->addItem(a);
}
}

for(int i=0;i<items_testbench.length();i++){
QString dir=ubicacionActual+items_testbench[i];
QFile file(dir);
if (!file.open(QIODevice::ReadOnly | QIODevice::Text))return;
else {
 fileInfo=(file.fileName());
 nombre_t[i]=fileInfo.fileName();
 dirPuro_t[i]=fileInfo.absolutePath();dirPuro[i]+='/';
 in.setDevice(&file);
 codigo_t[i]=in.readAll();
 ui->textEdit_3->setText("");
 for(sd=1;sd<= ui->textEdit->document()->blockCount();sd++){
 ui->textEdit_3->append(QString::number(sd));
 ui->textEdit_3->setAlignment(Qt::AlignRight);}
 ui->textEdit_3->verticalScrollBar()->setValue(ui->textEdit->verticalScrollBar()->value());
 ui->listWidget_2->setCurrentRow(0);
}
}

for(int i=0;i<items_normales.length();i++){
QString dir=ubicacionActual+items_normales[i];
QFile file(dir);
if (!file.open(QIODevice::ReadOnly | QIODevice::Text))return;
else {
 fileInfo=(file.fileName());
 nombre[i]=fileInfo.fileName();
 dirPuro[i]=fileInfo.absolutePath();dirPuro[i]+='/';
 in.setDevice(&file);
 codigo[i]=in.readAll();
 ui->textEdit_3->setText("");
 for(sd=1;sd<= ui->textEdit->document()->blockCount();sd++){
 ui->textEdit_3->append(QString::number(sd));
 ui->textEdit_3->setAlignment(Qt::AlignRight);}
 ui->textEdit_3->verticalScrollBar()->setValue(ui->textEdit->verticalScrollBar()->value());
 if(items_normales[i]==nom){ui->listWidget->setCurrentRow(i);ui->textEdit->setText(codigo[i]);}
}
}

ui->groupBox->setVisible(true);
ui->groupBox_2->setVisible(false);
ui->groupBox_4->setVisible(false);
ui->groupBox_5->setVisible(false);



}

void MainWindow::on_checkBox_clicked()
{

}
 //string jaja3;


void MainWindow::on_tableWidget_cellPressed(int row, int column)
{
//    QModelIndex next_index = ui->tableWidget->model()->index(row + 1, 0);
//    ui->tableWidget->setCurrentIndex(next_index);

}

void MainWindow::on_pushButton_3_clicked()
{


ui->groupBox_4->setVisible(false);
ui->groupBox_2->setVisible(false);
ui->groupBox->setVisible(false);
ui->groupBox_5->setVisible(true);
int n = ui->lineEdit_7->text().toULong();

ui->tableWidget_2->setRowCount(n);
ui->tableWidget_2->setColumnCount(3);
QStringList lis2=(QStringList()<<"Port name"<<"Direction"<<"Bits");
ui->tableWidget_2->setHorizontalHeaderLabels(lis2);

for(int i=0;i<n;i++){
QComboBox* combobox = new QComboBox();
ui->tableWidget_2->setCellWidget(i,1,combobox);
QStringList list=(QStringList()<<"in"<<"out"<<"inout");
combobox->addItems(list);

#if (defined (_WIN32) || defined (_WIN64))
 ui->lineEdit_5->setText("C:\Windows");
#endif
#if (defined (LINUX) || defined (__linux__))
 ui->lineEdit_5->setText("/home/"+qgetenv("USER")+"/");
#endif


}
}

void MainWindow::on_pushButton_5_clicked()
{

    ui->listWidget_2->blockSignals(true);
    ui->listWidget_2->clear();
    ui->listWidget_2->blockSignals(false);

    QString dir=ubicacionActual+nombreActual;



    //cargar

        QString nom=dir.mid(dir.lastIndexOf("/")+1,dir.length());
        QString fol=dir.mid(0,dir.lastIndexOf("/"));fol+="/";

      //  dirModel->setRootPath("");
    ui->treeView->setCurrentIndex(dirModel->setRootPath(fol));


        ui->listWidget->blockSignals(true);
        ui->listWidget->clear();
        ui->listWidget->blockSignals(false);

        items.clear();items_normales.clear();items_testbench.clear();
                QDir path(fol);
                QStringList filters;
                filters << "*.vhdl";
                path.setNameFilters(filters);
                items = path.entryList();


    for(int i=0;i<items.length();i++){
    QListWidgetItem * a = new QListWidgetItem(items[i]);
    if(!a->text().contains("_tb")){
    items_normales<<items[i];
    a->setIcon(QIcon(":/iconos/file7.png"));
    ui->listWidget->addItem(a);
    }
    else {

    items_testbench<<items[i];
    a->setIcon(QIcon(":/iconos/file8.png"));
    ui->listWidget_2->addItem(a);
    }
    }

    for(int i=0;i<items_testbench.length();i++){
    QString dir=ubicacionActual+items_testbench[i];
    QFile file(dir);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))return;
    else {
     fileInfo=(file.fileName());
     nombre_t[i]=fileInfo.fileName();
     dirPuro_t[i]=fileInfo.absolutePath();dirPuro[i]+='/';
     in.setDevice(&file);
     codigo_t[i]=in.readAll();
     ui->textEdit_3->setText("");
     for(sd=1;sd<= ui->textEdit->document()->blockCount();sd++){
     ui->textEdit_3->append(QString::number(sd));
     ui->textEdit_3->setAlignment(Qt::AlignRight);}
     ui->textEdit_3->verticalScrollBar()->setValue(ui->textEdit->verticalScrollBar()->value());
     //ui->listWidget_2->setCurrentRow(0);
    }
    }

    for(int i=0;i<items_normales.length();i++){
    QString dir=ubicacionActual+items_normales[i];
    QFile file(dir);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))return;
    else {
     fileInfo=(file.fileName());
     nombre[i]=fileInfo.fileName();
     dirPuro[i]=fileInfo.absolutePath();dirPuro[i]+='/';
     in.setDevice(&file);
     codigo[i]=in.readAll();
     ui->textEdit_3->setText("");
     for(sd=1;sd<= ui->textEdit->document()->blockCount();sd++){
     ui->textEdit_3->append(QString::number(sd));
     ui->textEdit_3->setAlignment(Qt::AlignRight);}
     ui->textEdit_3->verticalScrollBar()->setValue(ui->textEdit->verticalScrollBar()->value());
     //if(items_normales[i]==nom){ui->listWidget->setCurrentRow(i);ui->textEdit->setText(codigo[i]);}
    }
    }

    ui->groupBox->setVisible(true);
    ui->groupBox_2->setVisible(false);
    ui->groupBox_4->setVisible(false);
    ui->groupBox_5->setVisible(false);

}

void MainWindow::on_tableWidget_pressed(const QModelIndex &index)
{

}

void MainWindow::on_radioButton_3_clicked()
{

}

void MainWindow::on_radioButton_4_clicked()
{

}

void MainWindow::on_actionmodo_Blanco_triggered()
{
    oscuro=0;
    highlighter->setcolor(1);

   ui->textEdit->setStyleSheet("");
   ui->textEdit_2->setStyleSheet("");
   ui->tabWidget->setStyleSheet("");
   ui->listWidget_2->setStyleSheet("");
   ui->textEdit_3->setStyleSheet("");
   ui->textEdit_3->setStyleSheet("color: rgb(110,110,110);"
                                 "background-color: rgb(240,240,240);"
                                 "foreground-color: rgb(110,110,110);"
                                 "selection-background-color: rgb(90,90,90);");



   ui->pushButton->setStyleSheet("");ui->pushButton_2->setStyleSheet("");ui->pushButton_7->setStyleSheet("");
      ui->tableWidget->setStyleSheet("");   ui->tableWidget_2->setStyleSheet("");ui->listWidget->setStyleSheet("");
ui->centralWidget->setStyleSheet("");

ui->centralWidget->setStyleSheet(
                              "selection-background-color: rgba(0, 0, 255, 200);");
ui->menuBar->setStyleSheet(
            "selection-background-color: rgba(0, 0, 255, 200);");

QFont font("Courier New");
font.setStyleHint(QFont::Monospace);
 ui->textEdit->setFont(font);
 ui->textEdit_3->setFont(font);
}

void MainWindow::on_actionmodo_Dark_triggered()
{
    oscuro=1;
    highlighter->setcolor(0);

    ui->textEdit->setStyleSheet("color: rgb(250,250,250);"
                                  "background-color: rgb(30,30,30);"
                                  "foreground-color: rgb(250,250,250);"
                                  "selection-background-color: rgb(90,90,90);");


    ui->textEdit_2->setStyleSheet("color: rgb(220,220,220);"
                                  "background-color: rgb(30,30,30);"
                                  "foreground-color: rgb(220,220,220);"
                                  "selection-background-color: rgb(90,90,90);");



    ui->textEdit_3->setStyleSheet("color: rgb(170,170,170);"
                                  "background-color: rgb(35,35,35);"
                                  "foreground-color: rgb(170,170,170);"
                                  "selection-background-color: rgb(90,90,90);");


    ui->listWidget->setStyleSheet("color: rgb(220,220,220);"
                                  "background-color: rgb(30,30,30);"
                                  "foreground-color: rgb(220,220,220);"
                                  "selection-background-color: rgb(0,90,40);");

    ui->listWidget_2->setStyleSheet("color: rgb(220,220,220);"
                                  "background-color: rgb(30,30,30);"
                                  "foreground-color: rgb(220,220,220);"
                                  "selection-background-color: rgb(0,90,40);");

    ui->tabWidget->setStyleSheet("color: rgb(220,220,220);"
                                  "background-color: rgb(30,30,30);"
                                  "foreground-color: rgb(220,220,220);"
                                  "selection-background-color: rgb(150,150,90);");

    ui->pushButton->setStyleSheet("color: rgb(220,220,220);"
                                  "background-color: rgb(50,50,50);"
                                  "foreground-color: rgb(220,220,220);"
                                  "selection-background-color: rgb(0,90,90);");
    ui->pushButton_2->setStyleSheet("color: rgb(220,220,220);"
                                  "background-color: rgb(50,50,50);"
                                  "foreground-color: rgb(220,220,220);"
                                  "selection-background-color: rgb(0,90,90);");
    ui->pushButton_7->setStyleSheet("color: rgb(220,220,220);"
                                  "background-color: rgb(50,50,50);"
                                  "foreground-color: rgb(220,220,220);"
                                  "selection-background-color: rgb(0,90,90);");



    ui->tableWidget->setStyleSheet("color: white;"
                                  "background-color: rgb(40,40,40);"
                                  "foreground-color: white;"
                                  "selection-background-color: rgba(0, 0, 255, 200);");

    ui->tableWidget_2->setStyleSheet("color: white;"
                                  "background-color: rgb(40,40,40);"
                                  "foreground-color: white;"
                                  "selection-background-color: rgba(0, 0, 255, 200);");


    ui->centralWidget->setStyleSheet("color: white;"
                                  "background-color: rgb(50,50,50);"
                                  "foreground-color: white;"
                                  "selection-background-color: rgba(0, 0, 255, 200);");




QFont font("Courier New");
    font.setStyleHint(QFont::Monospace);
     ui->textEdit->setFont(font);
     ui->textEdit_3->setFont(font);
}

void MainWindow::on_actionFuente_2_triggered()
{
    bool ok;
    QFont font=QFontDialog::getFont(&ok,this);
    if(ok){ui->textEdit->setFont(font);ui->textEdit_3->setFont(font);}
    else return;
}

void MainWindow::on_textEdit_textChanged()
{



}
void MainWindow::on_textEdit_cursorPositionChanged()
{
    //ui->textEdit_2->setText(QString::number(ui->textEdit->textCursor().columnNumber())+","+QString::number(ui->textEdit->textCursor().blockNumber()+1));

    ui->textEdit_3->setText("");
            for(sd=1;sd<= ui->textEdit->document()->blockCount();sd++){
                //ui->textEdit_3->append(QString::number(sd));
             if(sd==ui->textEdit->textCursor().blockNumber()+1)
                 if(!oscuro)
                 ui->textEdit_3->append("<html><font color=\"black\"><b>"+QString::number(sd)+"</b</html>");
                 else {
                     ui->textEdit_3->append("<html><font color=\"white\"><b>"+QString::number(sd)+"</b</html>");
                 }
    else ui->textEdit_3->append(QString::number(sd));
                      ui->textEdit_3->setAlignment(Qt::AlignRight);

            }

}

void MainWindow::on_actionNuevo_triggered()
{
//nuevoproy.show();
    if(ui->listWidget->count()>0){
    for(int i = 0; i < ui->listWidget->count(); i++){
         if(ui->listWidget->item(i)->text().contains("*")){
             QMessageBox::StandardButton reply;
             QString b=ui->listWidget->item(i)->text().replace("*","");
           reply =  QMessageBox::question(this,"Archivos sin guardar","Before continuing, you must save all the files\nSave "+b+"?", QMessageBox::Yes | QMessageBox::No);
           if (reply == QMessageBox::Yes) { guardar(ubicacionActual+b);} else{}
         }
    }
    }

    ui->groupBox_4->setVisible(false);
    ui->groupBox_2->setVisible(false);
    ui->groupBox->setVisible(false);
    ui->groupBox_5->setVisible(true);
    int n = ui->lineEdit_7->text().toULong();

    ui->tableWidget_2->setRowCount(n);
    ui->tableWidget_2->setColumnCount(3);
    QStringList lis2=(QStringList()<<"Port name"<<"Direction"<<"Bits");
    ui->tableWidget_2->setHorizontalHeaderLabels(lis2);

    for(int i=0;i<n;i++){
    QComboBox* combobox = new QComboBox();
    ui->tableWidget_2->setCellWidget(i,1,combobox);
    QStringList list=(QStringList()<<"in"<<"out"<<"inout");
    combobox->addItems(list);

    #if (defined (_WIN32) || defined (_WIN64))
     ui->lineEdit_5->setText("C:\Windows");
    #endif
    #if (defined (LINUX) || defined (__linux__))
     ui->lineEdit_5->setText("/home/"+qgetenv("USER")+"/");
    #endif


    }

}

void MainWindow::on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
  //  ui->groupBox->setTitle("Proyecto actual: "+current->text());
current1=ui->listWidget->row(current);
previous1=ui->listWidget->row(previous);
nombreActual=items_normales[ui->listWidget->row(current)];
ui->label_11->setText(" "+nombreActual);
 codigo[ui->listWidget->row(previous)]=ui->textEdit->toPlainText();
    ui->textEdit->setText(codigo[ui->listWidget->row(current)]);

    }

void MainWindow::on_lineEdit_7_returnPressed()
{
    int n = ui->lineEdit_7->text().toULong();

    ui->tableWidget_2->setRowCount(n);
    ui->tableWidget_2->setColumnCount(3);
    QStringList lis2=(QStringList()<<"Port name"<<"Direction"<<"Bits");
    ui->tableWidget_2->setHorizontalHeaderLabels(lis2);

    for(int i=0;i<n;i++){
    QComboBox* combobox = new QComboBox();
    ui->tableWidget_2->setCellWidget(i,1,combobox);
    QStringList list=(QStringList()<<"in"<<"out"<<"inout");
    combobox->addItems(list);
}
}

void MainWindow::on_pushButton_9_clicked()
{
    int n = ui->lineEdit_7->text().toULong();

    ui->tableWidget_2->setRowCount(n);
    ui->tableWidget_2->setColumnCount(3);
    QStringList lis2=(QStringList()<<"Port name"<<"Direction"<<"Bits");
    ui->tableWidget_2->setHorizontalHeaderLabels(lis2);

    for(int i=0;i<n;i++){
        QComboBox* combobox = new QComboBox();
        ui->tableWidget_2->setCellWidget(i,1,combobox);
        QStringList list=(QStringList()<<"in"<<"out"<<"inout");
        combobox->addItems(list);
}
}

void MainWindow::on_pushButton_8_clicked()
{


   proyecto.clear();
 //   if(i>=0)codigo[i]=ui->textEdit->toPlainText();
    bool bien=true;
    proyecto+="library ieee;\nuse ieee.std_logic_1164.all;\n\nentity ";
    proyecto+=ui->lineEdit_6->text().toUtf8().constData();
    proyecto+=" is\nport(\n";

  //  QString item_2,item_3;QStringList InputComboData;
for(int j=0;j<ui->tableWidget_2->model()->rowCount();j++){
    bien=true;
    QTableWidgetItem* item = ui->tableWidget_2->item(j,0);
    if (!item || item->text().isEmpty())
    {
      bien=false;
    }
    //if(ui->tableWidget_2->item(j,0)->text().isEmpty()){bien=false;break;}
    if(bien){
    proyecto+=ui->tableWidget_2->item(j,0)->text().toUtf8().constData();proyecto+=" : ";
    QComboBox *m = qobject_cast<QComboBox*>(ui->tableWidget_2->cellWidget(j,1));
   proyecto+=m->currentText().toUtf8().constData();proyecto+=" ";


    int num = ui->tableWidget_2->item(j,2)->text().toInt();
   //  int num=2;
   if(num>1){
   if(j==ui->tableWidget_2->model()->rowCount()-1)
       proyecto+="std_logic_vector("+to_string(num-1)+" downto 0)\n";
   else
       proyecto+="std_logic_vector("+to_string(num-1)+" downto 0);\n";
   }
   else{if(j==ui->tableWidget_2->model()->rowCount()-1)proyecto+="std_logic\n";
       else
           proyecto+="std_logic;\n";}

    //InputComboData << m->currentText();
    }}
//cout<<proyecto<<endl;

proyecto+=");\n";
proyecto+="end ";
proyecto+=ui->lineEdit_6->text().toUtf8().constData();
proyecto+=";\n\n";
proyecto+="architecture arc of ";
proyecto+=ui->lineEdit_6->text().toUtf8().constData();
proyecto+=" is\n\nbegin\n\nend arc;";




ui->groupBox->setVisible(true);
ui->groupBox_2->setVisible(false);
ui->groupBox_4->setVisible(false);
ui->groupBox_5->setVisible(false);

for(sd=1;sd<= ui->textEdit->document()->blockCount();sd++){
    ui->textEdit_3->append(QString::number(sd));
ui->textEdit_3->setAlignment(Qt::AlignRight);}
ui->textEdit_3->verticalScrollBar()->setValue(ui->textEdit->verticalScrollBar()->value());

//guardar
ubicacionActual=ui->lineEdit_5->text();
nombreActual=ui->lineEdit_6->text();
nombreActual.replace(".vhdl","");
nombreActual+=".vhdl";
QString dir=ubicacionActual+nombreActual;
QFile file(dir);
    if(!file.open(QFile::WriteOnly | QFile::Text)){return;}
    QTextStream out(&file);
out << proyecto.c_str();
    file.flush();
    file.close();


//cargar

    QString nom=dir.mid(dir.lastIndexOf("/")+1,dir.length());
    QString fol=dir.mid(0,dir.lastIndexOf("/"));fol+="/";

  //  dirModel->setRootPath("");
ui->treeView->setCurrentIndex(dirModel->setRootPath(fol));


    ui->listWidget->blockSignals(true);
    ui->listWidget->clear();
    ui->listWidget->blockSignals(false);

    items.clear();items_normales.clear();items_testbench.clear();
            QDir path(fol);
            QStringList filters;
            filters << "*.vhdl";
            path.setNameFilters(filters);
            items = path.entryList();


for(int i=0;i<items.length();i++){
QListWidgetItem * a = new QListWidgetItem(items[i]);
if(!a->text().contains("_tb")){
items_normales<<items[i];
a->setIcon(QIcon(":/iconos/file7.png"));
ui->listWidget->addItem(a);
}
else {

items_testbench<<items[i];
a->setIcon(QIcon(":/iconos/file8.png"));
ui->listWidget_2->addItem(a);
}
}

for(int i=0;i<items_testbench.length();i++){
QString dir=ubicacionActual+items_testbench[i];
QFile file(dir);
if (!file.open(QIODevice::ReadOnly | QIODevice::Text))return;
else {
 fileInfo=(file.fileName());
 nombre_t[i]=fileInfo.fileName();
 dirPuro_t[i]=fileInfo.absolutePath();dirPuro[i]+='/';
 in.setDevice(&file);
 codigo_t[i]=in.readAll();
 ui->textEdit_3->setText("");
 for(sd=1;sd<= ui->textEdit->document()->blockCount();sd++){
 ui->textEdit_3->append(QString::number(sd));
 ui->textEdit_3->setAlignment(Qt::AlignRight);}
 ui->textEdit_3->verticalScrollBar()->setValue(ui->textEdit->verticalScrollBar()->value());
 ui->listWidget_2->setCurrentRow(0);
}
}

for(int i=0;i<items_normales.length();i++){
QString dir=ubicacionActual+items_normales[i];
QFile file(dir);
if (!file.open(QIODevice::ReadOnly | QIODevice::Text))return;
else {
 fileInfo=(file.fileName());
 nombre[i]=fileInfo.fileName();
 dirPuro[i]=fileInfo.absolutePath();dirPuro[i]+='/';
 in.setDevice(&file);
 codigo[i]=in.readAll();
 ui->textEdit_3->setText("");
 for(sd=1;sd<= ui->textEdit->document()->blockCount();sd++){
 ui->textEdit_3->append(QString::number(sd));
 ui->textEdit_3->setAlignment(Qt::AlignRight);}
 ui->textEdit_3->verticalScrollBar()->setValue(ui->textEdit->verticalScrollBar()->value());
 if(items_normales[i]==nom){ui->listWidget->setCurrentRow(i);ui->textEdit->setText(codigo[i]);}
}
}




}

void MainWindow::on_listWidget_currentRowChanged(int currentRow)
{

}

void MainWindow::on_pushButton_10_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Abrir carpeta"),
                                                "",
                                                QFileDialog::ShowDirsOnly
                                                | QFileDialog::DontResolveSymlinks);
    ui->lineEdit_5->setText(dir+"/");
}

void MainWindow::on_textEdit_copyAvailable(bool b)
{

}

void MainWindow::on_pushButton_11_clicked()
{
    if(i<0){
        ui->groupBox->setVisible(false);
        ui->groupBox_2->setVisible(false);
        ui->groupBox_4->setVisible(true);
        ui->groupBox_5->setVisible(false);
    }else{
        ui->groupBox->setVisible(true);
        ui->groupBox_2->setVisible(false);
        ui->groupBox_4->setVisible(false);
        ui->groupBox_5->setVisible(false);
    }
}

void MainWindow::on_pushButton_13_clicked()
{

    QStringList wordList;
    wordList = fa;



     completer = new QCompleter(wordList, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setWidget(ui->textEdit);
QRect a=ui->textEdit->cursorRect();
QRect b(a.x(),a.y(),300,20);
completer->complete(b);
connect(completer, SIGNAL(activated(QString)),
                     this, SLOT(insertCompletion(QString)));
    //ui->textEdit->setCompleter(completer);


}
void MainWindow::insertCompletion(const QString& completion)
{
//int extra = completion.length() - completer->completionPrefix().length();
// ui->textEdit->append(completion.right(extra));
qDebug()<<completion;
    for(int i=0;i<init_component.length();i++){
        if(fa[i]==completion) {ui->textEdit->textCursor().insertText(init_component[i]);break;qDebug()<<"yes";}
    }


}

void MainWindow::insertCompletion2(const QString& completion)
{
//int extra = completion.length() - completer->completionPrefix().length();
// ui->textEdit->append(completion.right(extra));

    for(int i=0;i<inst_component.length();i++){
        if(fa[i]==completion) {    ui->textEdit->textCursor().insertText("cmp_"+QString::number(n_component));
            ui->textEdit->textCursor().insertText(inst_component[i]);
             n_component++;break;}
    }

}
void MainWindow::on_pushButton_14_clicked()
{
QStringList clock;
int stop_time=ui->lineEdit_9->text().toInt();
int intervalo=ui->lineEdit_8->text().toInt();
int n_columnas=stop_time/intervalo;
for(int i=1;i<=n_columnas;i++){
    clock<<QString::number(i*intervalo)+" ns";
}
ui->tableWidget->setColumnCount(n_columnas);
   ui->tableWidget->setHorizontalHeaderLabels(clock);

//nombres_verticales_entradas<<"A"<<"B";
//ui->tableWidget->setVerticalHeaderLabels(nombres_verticales_entradas);
}


void MainWindow::on_pushButton_7_clicked()
{
    ui->textEdit_2->setText("");ui->label_5->setText(nombreActual);
//guardar todo
codigo[ui->listWidget->currentRow()]=ui->textEdit->toPlainText();
for (int f=0;f<ui->listWidget->count();f++){

   QString dir=ubicacionActual+items_normales[f];
   QFile file2(dir);
       if(!file2.open(QFile::WriteOnly | QFile::Text)){return;}
       QTextStream out(&file2);
       out << codigo[f];
       file2.flush();
       file2.close();
           QString a= ui->listWidget->item(f)->text();
           a=a.replace("*","");
           ui->listWidget->item(f)->setText(a);

}
bool compilado=0;
for (int f=0;f<ui->listWidget->count();f++){
   QString dir=ubicacionActual+items_normales[f];
   compilado=compilar(items_normales[f]);
   if(compilado==0)break;
}

 if(compilado){

int  primer_parentesis,segundo_parentesis;
 QString txt;
 yut.clear();txt.clear();
 txt=ui->textEdit->toPlainText();
yut=ui->textEdit->toPlainText().toStdString();


 primer_parentesis+=5;
 segundo_parentesis+=0;


 txt=ui->textEdit->toPlainText();
yut=ui->textEdit->toPlainText().toStdString();
proyecto.clear();
QString nombre_puro=nombreActual.replace(".vhdl","");
proyecto+="--testbench automatically generated by a robot :D\n";
proyecto+="library ieee;\nuse ieee.std_logic_1164.all;\n\n";
proyecto+="entity "+nombre_puro.toStdString()+"_tb"+" is\n";
proyecto+="end "+nombre_puro.toStdString()+"_tb;\n\n";
proyecto+="architecture arc of "+nombre_puro.toStdString()+"_tb"+" is\n";
proyecto+="component "+nombre_puro.toStdString()+" is port(\n";

QString txt2,a2;int primer_parentesis2,segundo_parentesis2;QStringList lista2,b2;QString temp32;int tempo2=0,mas_sig2,menos_sig2;
QString component;

QString n=ui->textEdit->toPlainText();
QStringList lines = ui->textEdit->toPlainText().split('\n', QString::SkipEmptyParts);
QStringList limpio;
//qDebug()<<lines;
for(int i=0;i<lines.length();i++){
    if(lines[i].contains("--")){
        int c=lines[i].indexOf("--");
            limpio<<lines[i].mid(0,c);
    }
    else {
        limpio<<lines[i];
    }
}
//qDebug()<<limpio;
//txt2=ui->textEdit->toPlainText();
for(int i=0;i<limpio.length();i++){
    txt2+=limpio[i];
}
txt2=txt2.simplified();
txt2.replace( " ", "" );
 primer_parentesis2=txt2.indexOf("port(");
 segundo_parentesis2=txt2.indexOf(");end");

primer_parentesis2+=5;
segundo_parentesis2+=0;
r[0]='\0';

for(i=primer_parentesis2;i<segundo_parentesis2;i++){
    r[i-primer_parentesis2]=txt2.toUtf8().constData()[i];
}
r[i]='\0';
 lista2=QString(r).split(';');

for(i=0;i<lista2.length();i++){
a2=lista2[i];
if(a2.contains("in") || a2.contains("out") || a2.contains("inout")){
b2=a2.split(':');

component+=b2[0];
component+=" : ";
 if(a2.contains("in")) component+="in ";
 if(a2.contains("out")) component+="out ";
 if(a2.contains("inout")) component+="inout ";


if(b2[1].contains("downto")){
QRegularExpression rx("[0-9]+");
QRegularExpressionMatchIterator matches = rx.globalMatch(b2[1]);
tempo2=0;
while (matches.hasNext()) {

    QRegularExpressionMatch match = matches.next();
    if(tempo2==0){mas_sig2 = match.captured(0).toInt();tempo2=1;}else {
        menos_sig2 = match.captured(0).toInt();
    }
}
//nombres_in<<temp3+" : std_logic_vector("+QString::number(mas_sig)+" downto "+QString::number(menos_sig)+");";

component+="std_logic_vector("+QString::number(mas_sig2)+" downto "+QString::number(menos_sig2)+");\n";
}
else{
component+="std_logic;\n";

}
}
}

proyecto+=component.toStdString();


QString h2=QString::fromStdString(proyecto);
int h3=h2.lastIndexOf(";");
h2.replace(h3,1,");");
proyecto=h2.toStdString();

proyecto+="end component;\n";
ui->textEdit_2->setText(QString::fromStdString(proyecto));


txt=txt2;
txt=txt.simplified();
txt.replace( " ", "" );
 primer_parentesis=txt.indexOf("port(");
segundo_parentesis=txt.indexOf(");end");

primer_parentesis+=5;
segundo_parentesis+=0;
r[0]='\0';

for(i=primer_parentesis;i<segundo_parentesis;i++){
    r[i-primer_parentesis]=txt.toUtf8().constData()[i];
}
r[i]='\0';
QString u;
QStringList lista=QString(r).split(';');
QStringList temp,nombres_in;
QString temp3;
int mas_sig,menos_sig,tempo=0;
QStringList b;QString a;
for(i=0;i<lista.length();i++){
a=lista[i];
if(a.contains("in") || a.contains("out")){
b=a.split(':');

temp3=b[0];


if(b[1].contains("downto")){
QRegularExpression rx("[0-9]+");
QRegularExpressionMatchIterator matches = rx.globalMatch(b[1]);
tempo=0;
while (matches.hasNext()) {

    QRegularExpressionMatch match = matches.next();
    if(tempo==0){mas_sig = match.captured(0).toInt();tempo=1;}else {
        menos_sig = match.captured(0).toInt();
    }
}
//nombres_in<<temp3+" : std_logic_vector("+QString::number(mas_sig)+" downto "+QString::number(menos_sig)+");";


proyecto+="signal ";
u=temp3+" : std_logic_vector("+QString::number(mas_sig)+" downto "+QString::number(menos_sig)+");";
proyecto+=u.toStdString();
proyecto+='\n';
}
else{
    //nombres_in<<temp3+" : std_logic;";


    proyecto+="signal ";
   u= temp3+" : std_logic;";
   proyecto+=u.toStdString();
   proyecto+='\n';
}
}
}

proyecto+="begin\n";
proyecto+="RSC: ";
proyecto+=nombre_puro.toStdString() + " port map (";
//asignacion de señales
signal_lista.clear();
txt=txt2;
txt=txt.simplified();
txt.replace( " ", "" );
 primer_parentesis=txt.indexOf("port(");
segundo_parentesis=txt.indexOf(");end");

primer_parentesis+=5;
segundo_parentesis+=0;
r[0]='\0';

for(i=primer_parentesis;i<segundo_parentesis;i++){
    r[i-primer_parentesis]=txt.toUtf8().constData()[i];
}
r[i]='\0';
 lista=QString(r).split(';');

for(i=0;i<lista.length();i++){
mas_sig=0;menos_sig=0;
QString a=lista[i];
if(a.contains("in")||a.contains("out")){
QStringList b=a.split(':');

temp3=b[0];


if(temp3.contains(',')){

QStringList b=temp3.split(',');
for(int k=0;k<b.length();k++){
    signal_lista<<b[k];
    proyecto+='\n';
   proyecto+=b[k].toStdString();
   proyecto+=" => ";
   proyecto+=b[k].toStdString();

        proyecto+=",";
}
}
else{
    signal_lista<<temp3;
    proyecto+='\n';
    proyecto+=temp3.toStdString();
    proyecto+=" => ";
    proyecto+=temp3.toStdString();

           proyecto+=",";
}
}
}
proyecto[proyecto.size()-1] = ' ';
 proyecto+='\n';
 proyecto+=");\n";
  proyecto+="process\n";
    proyecto+="begin\n";

//ui->textEdit_2->setText("");
//for(int i=0;i<nombres_in.length();i++)ui->textEdit_2->append(nombres_in[i]);




//valores al tablewidget

txt=txt2;
txt=txt.simplified();
txt.replace( " ", "" );
 primer_parentesis=txt.indexOf("port(");
 segundo_parentesis=txt.indexOf(");end");

primer_parentesis+=5;
segundo_parentesis+=0;
r[0]='\0';

for(i=primer_parentesis;i<segundo_parentesis;i++){
    r[i-primer_parentesis]=txt.toUtf8().constData()[i];
}
r[i]='\0';
 lista=QString(r).split(';');



for(i=0;i<lista.length();i++){
mas_sig=0;menos_sig=0;
QString a=lista[i];
if(a.contains("in")){
QStringList b=a.split(':');

temp3=b[0];


if(temp3.contains(',')){

QStringList b=temp3.split(',');
for(int k=0;k<b.length();k++){
   nombres_in<<b[k];
}
}
else
nombres_in<<temp3;
}
}


in_lista=nombres_in;


QStringList clock;
int stop_time=ui->lineEdit_9->text().toInt();
int intervalo=ui->lineEdit_8->text().toInt();
int n_columnas=stop_time/intervalo;
for(int i=1;i<=n_columnas;i++){
clock<<QString::number(i*intervalo)+" ns";
}
ui->tableWidget->setColumnCount(n_columnas);
ui->tableWidget->setHorizontalHeaderLabels(clock);

/*
for(i=0;i<nombres_in.length();i++){
ui->textEdit_2->append(nombres_in[i]);
}
*/


ui->groupBox->setVisible(false);
ui->groupBox_2->setVisible(true);
ui->groupBox_4->setVisible(false);
ui->groupBox_5->setVisible(false);
 }



proyecto_copia=proyecto;

//obtener bits y guardarlos en bits_lista

QString txt,a;int primer_parentesis,segundo_parentesis;QStringList lista,b,m;QString temp3;int tempo=0,mas_sig,menos_sig;
QString n=ui->textEdit->toPlainText();
QStringList lines = ui->textEdit->toPlainText().split('\n', QString::SkipEmptyParts);
QStringList limpio;
//qDebug()<<lines;
for(int i=0;i<lines.length();i++){
    if(lines[i].contains("--")){
        int c=lines[i].indexOf("--");
            limpio<<lines[i].mid(0,c);
    }
    else {
        limpio<<lines[i];
    }
}
//qDebug()<<limpio;
//txt2=ui->textEdit->toPlainText();
for(int i=0;i<limpio.length();i++){
    txt+=limpio[i];
}

txt=txt.simplified();
txt.replace( " ", "" );
 primer_parentesis=txt.indexOf("port(");
 segundo_parentesis=txt.indexOf(");end");

primer_parentesis+=5;
segundo_parentesis+=0;
r[0]='\0';

for(i=primer_parentesis;i<segundo_parentesis;i++){
    r[i-primer_parentesis]=txt.toUtf8().constData()[i];
}
r[i]='\0';
 lista=QString(r).split(';');

for(i=0;i<lista.length();i++){
a=lista[i];
if(a.contains("in") || a.contains("out")){
b=a.split(':');

temp3=b[0];


if(b[1].contains("downto")){
QRegularExpression rx("[0-9]+");
QRegularExpressionMatchIterator matches = rx.globalMatch(b[1]);
tempo=0;
while (matches.hasNext()) {

    QRegularExpressionMatch match = matches.next();
    if(tempo==0){mas_sig = match.captured(0).toInt();tempo=1;}else {
        menos_sig = match.captured(0).toInt();
    }
}
//nombres_in<<temp3+" : std_logic_vector("+QString::number(mas_sig)+" downto "+QString::number(menos_sig)+");";
 if(b[0].contains(",")){
 m=b[0].split(",");
for(int i=0;i<m.length();i++){
    bits_lista<<QString::number(mas_sig-menos_sig+1);
}
m.clear();
 }
else bits_lista<<QString::number(mas_sig-menos_sig+1);

}
else{
    if(b[0].contains(",")){
    m=b[0].split(",");
   for(int i=0;i<m.length();i++){
       bits_lista<<QString::number(1);
   }
   m.clear();
    }
    else bits_lista<<QString::number(1);

}
}
}
QStringList valores_finales;
for(int i=0;i<in_lista.length();i++){
    valores_finales<<in_lista[i]+" ["+bits_lista[i]+" bit]";
}
ui->tableWidget->setRowCount(valores_finales.length());
ui->tableWidget->setVerticalHeaderLabels(valores_finales);

//ui->textEdit_2->setText("");for(int i=0;i<bits_lista.length();i++){ui->textEdit_2->append(bits_lista[i]);}
}

void MainWindow::on_pushButton_12_clicked()
{
    proyecto=proyecto_copia;
//check si hay items nulos, si los hay ponerles 0
    for(int i=0;i<ui->tableWidget->model()->columnCount();i++){
        for(int j=0;j<ui->tableWidget->model()->rowCount();j++){
//QMessageBox::information(this,"hola",ui->tableWidget->item(j,i)->text());
            QTableWidgetItem *item1(ui->tableWidget->item(j,i));
            if(!item1)ui->tableWidget->setItem(j, i, new QTableWidgetItem("0"));
        }
        }

    //get valores del tablewidget
signales_valores.clear();
    for(int i=0;i<ui->tableWidget->model()->columnCount();i++){
        for(int j=0;j<ui->tableWidget->model()->rowCount();j++){


    if(convertidorActual=="binario"){
    if(ui->tableWidget->item(j,i)->text().length()>1){
    signales_valores+=signal_lista[j];signales_valores+=" <= \"";signales_valores+=ui->tableWidget->item(j,i)->text();signales_valores+="\";";
    }
    else
    {signales_valores+=signal_lista[j];signales_valores+=" <= '";signales_valores+=ui->tableWidget->item(j,i)->text();signales_valores+="';";}

    }

            if(convertidorActual=="decimal"){

      /*
            //   if(QString::number(DtoB(ui->tableWidget->item(j,i)->text().toLong())).length()>1){
                        signales_valores+=signal_lista[j];signales_valores+=" <= ";
                               string kk=QString::number(DtoB(ui->tableWidget->item(j,i)->text().toLong())).toUtf8().constData();
                               signales_valores+="(";
                               for(int i=0;i<kk.length();i++){
                               signales_valores+=QString::number(i);signales_valores+=" => '";signales_valores+=kk[kk.length()-i-1];signales_valores+="',";
                               }
                               signales_valores+="others => '0'); ";
            //      }
              //    else {signales_valores+=signal_lista[j];signales_valores+=" <= '";signales_valores+=QString::number(DtoB(ui->tableWidget->item(j,i)->text().toLong()));signales_valores+="';";}
            }
*/
                if(bits_lista[j].toInt()==1)
                {
                    signales_valores+=signal_lista[j];signales_valores+=" <= '";signales_valores+=QString::number(DtoB(ui->tableWidget->item(j,i)->text().toLong()));signales_valores+="';";
                }

                else if(bits_lista[j].toInt()>1 ){
                    signales_valores+=signal_lista[j];signales_valores+=" <= ";
                           string kk=QString::number(DtoB(ui->tableWidget->item(j,i)->text().toLong())).toUtf8().constData();
                           signales_valores+="(";
                           for(int i=0;i<kk.length();i++){
                           signales_valores+=QString::number(i);signales_valores+=" => '";signales_valores+=kk[kk.length()-i-1];signales_valores+="',";
                           }
                           signales_valores+="others => '0'); ";
                }
                else QMessageBox::information(this,"Error en la tabla","Solo se admiten decimales positivos(los negativos ponerlos en binario)\nHexadecimal todavia no desarrollado");


                }

        }//signales_valores+="WAIT FOR 10 ns; \n";
        signales_valores+="wait for ";signales_valores+=ui->lineEdit_8->text()+" ns;\n";
    }


 proyecto+=signales_valores.toStdString();
 proyecto+="\nwait;";
 proyecto+="end process;\nend;";

 QString name_testbench=nombreActual+"_tb";
 QString dir=ubicacionActual+name_testbench+".vhdl";
 QFile file(dir);
     if(!file.open(QFile::WriteOnly | QFile::Text)){return;}
     QTextStream out(&file);
     out << QString::fromStdString(proyecto);
     file.flush();
     file.close();


     if(!oscuro) ui->textEdit_2->setTextColor(Qt::black);
     else {
        ui->textEdit_2->setTextColor(Qt::white);
     }
     qDebug()<<"test "<<name_testbench+".vhdl";
  //compilando tb
  process.setWorkingDirectory(ubicacionActual);
  ui->textEdit_2->append("$ghdl -a "+name_testbench+".vhdl");
      process.start("ghdl -a "+name_testbench+".vhdl");
      process.waitForFinished(-1); // will wait forever until finished

       Consola = process.readAllStandardOutput();
       errorConsola = process.readAllStandardError();
       if((!errorConsola.isEmpty() && errorConsola.contains("warning"))||errorConsola.isEmpty()){
                // -e
           ui->textEdit_2->append("$ghdl -e "+name_testbench);
               process.start("ghdl -e "+name_testbench);
               process.waitForFinished(-1); // will wait forever until finished

                Consola = process.readAllStandardOutput();
                errorConsola = process.readAllStandardError();
                if((!errorConsola.isEmpty() && errorConsola.contains("warning"))||errorConsola.isEmpty()){

                    // -r
                    ui->textEdit_2->append("$ghdl -r "+name_testbench);
                        process.start("ghdl -r "+name_testbench+" --vcd=ondas.vcd");
                        process.waitForFinished(-1); // will wait forever until finished

                         Consola = process.readAllStandardOutput();
                         errorConsola = process.readAllStandardError();
                       if((!errorConsola.isEmpty() && errorConsola.contains("warning"))||errorConsola.isEmpty()){

                             // gtkwave
                             ui->textEdit_2->append("gtkwave ondas.vcd");
                                 process.start("gtkwave ondas.vcd");
gtkwave=1;
ui->centralWidget->setEnabled(false);




                                  Consola = process.readAllStandardOutput();
                                  errorConsola = process.readAllStandardError();
                         }
                        else{QMessageBox::critical(this,"Error compilando1 "+nombreActual+"_tb.vhdl",errorConsola);
                    }

                }
               else{QMessageBox::critical(this,"Error compilando2 "+nombreActual+"_tb.vhdl",errorConsola);
           }

       }
      else{QMessageBox::critical(this,"Error compilando3 "+nombreActual+"_tb.vhdl",errorConsola);

           /*
       Consola = process.readAllStandardOutput();
       errorConsola = process.readAllStandardError();
       if(errorConsola.isEmpty()){
                // -e
           ui->textEdit_2->append("ghdl -e "+name_testbench);
               process.start("ghdl -e "+name_testbench);
               process.waitForFinished(-1); // will wait forever until finished

                Consola = process.readAllStandardOutput();
                errorConsola = process.readAllStandardError();
                if(errorConsola.isEmpty()){

                    // -r
                    ui->textEdit_2->append("ghdl -r "+name_testbench);
                        process.start("ghdl -r "+name_testbench+" --vcd=ondas.vcd");
                        process.waitForFinished(-1); // will wait forever until finished

                         Consola = process.readAllStandardOutput();
                         errorConsola = process.readAllStandardError();
                         if(errorConsola.isEmpty()){

                             // gtkwave
                             ui->textEdit_2->append("gtkwave ondas.vcd");
                                 process.start("gtkwave ondas.vcd");
gtkwave=1;
ui->centralWidget->setEnabled(false);




                                  Consola = process.readAllStandardOutput();
                                  errorConsola = process.readAllStandardError();
                         }
                        else{QMessageBox::critical(this,"Error compilando"+nombreActual+"_tb.vhdl",errorConsola);
                    }

                }
               else{QMessageBox::critical(this,"Error compilando"+nombreActual+"_tb.vhdl",errorConsola);
           }

       }
      else{QMessageBox::critical(this,"Error compilando"+nombreActual+"_tb.vhdl",errorConsola);
*/
  }








  ui->textEdit_2->verticalScrollBar()->setValue(ui->textEdit_2->verticalScrollBar()->maximum());

//ui->textEdit_4->setText(QString::fromStdString(proyecto));
}

void MainWindow::processFinished(int code , QProcess::ExitStatus status)
{
if(gtkwave){
ui->centralWidget->setEnabled(true);
    //QMessageBox::information(this,"se termino","se termino");
    gtkwave=0;}
}

void MainWindow::on_actionEjemplos_triggered()
{
    ejemplo.show();
}

void MainWindow::on_actionAgregar_componente_triggered()
{

    //obtener los nombres de todos los .vhdl de la carpeta
    QString fileName,f;QFile file; QFileInfo fileInfo;QTextStream in;
    QStringList archivos;
    //ubicacionActual=dirPuro[ui->listWidget->currentRow()];
    QString path = ubicacionActual;
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
                     if(!fileInfo.fileName().contains("_tb.vhdl"))
                     archivos<<fileInfo.fileName();
                 }
        }


fa.clear();init_component.clear();

for(int i=0;i<archivos.length();i++){
    if(!oscuro) ui->textEdit_2->setTextColor(Qt::black);
    else {
       ui->textEdit_2->setTextColor(Qt::white);
    }
nombreActual=archivos[i];
if(!archivos[i].contains("_tb.vhdl")){
    fa<<nombreActual;
           QString dir=ubicacionActual+nombreActual;
           QString r=get_component2((dir),codigo[i]);
           QString r1=get_component3((dir),codigo[i]);
         init_component<<r;
inst_component<<r1;
}
}

    QStringList wordList;
    wordList = fa;



     completer = new QCompleter(wordList, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setWidget(ui->textEdit);
QRect a=ui->textEdit->cursorRect();
QRect b(a.x(),a.y(),300,20);
completer->complete(b);
connect(completer, SIGNAL(activated(QString)),
                     this, SLOT(insertCompletion(QString)));
}






void MainWindow::showContextMenu(const QPoint &pt)
{

    //obtener los nombres de todos los .vhdl de la carpeta
    QString fileName,f;QFile file; QFileInfo fileInfo;QTextStream in;
    QStringList archivos;
    //ubicacionActual=dirPuro[ui->listWidget->currentRow()];
    QString path = ubicacionActual;
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
                     if(!fileInfo.fileName().contains("_tb.vhdl"))
                     archivos<<fileInfo.fileName();
                 }
        }


fa.clear();init_component.clear();

for(int i=0;i<archivos.length();i++){
    if(!oscuro) ui->textEdit_2->setTextColor(Qt::black);
    else {
       ui->textEdit_2->setTextColor(Qt::white);
    }
nombreActual=archivos[i];
if(!archivos[i].contains("_tb.vhdl")){
    fa<<nombreActual;
           QString dir=ubicacionActual+nombreActual;
           QString r=get_component2((dir),codigo[i]);
           QString r1=get_component3((dir),codigo[i]);
         init_component<<r;
         inst_component<<r1;


}
}

/*
QMenu *menu = ui->textEdit->createStandardContextMenu();
menu_componente = menu->addMenu( "Declarar componente" );
for(int i=0;i<fa.length();i++){
     QAction* a=menu_componente->addAction(fa[i]);
     a->setData(i);
}
connect(menu, SIGNAL(triggered(QAction*)), this, SLOT(on_menu_clicked(QAction*)));
menu->exec(ui->textEdit->mapToGlobal(pt));
delete menu;
*/
QMenu *menu = ui->textEdit->createStandardContextMenu();

menu_componente = menu->addMenu( QIcon(":/iconos/r1.png"),"Declare component" );
for(int i=0;i<fa.length();i++){
     QAction* a=menu_componente->addAction(fa[i]);
     a->setData(i);
}
menu_componente->addSeparator();
menu_componente = menu->addMenu(QIcon(":/iconos/r2.png"), "Instance component" );
for(int i=fa.length();i<fa.length()*2;i++){
     QAction* a=menu_componente->addAction(fa[i-fa.length()]);
     a->setData(i);
}
connect(menu, SIGNAL(triggered(QAction*)), this, SLOT(on_menu_clicked(QAction*)));
menu->exec(ui->textEdit->mapToGlobal(pt));
delete menu;



}

/*
void MainWindow::showContextMenu(const QPoint &pt)
{
    QMenu *menu = ui->textEdit->createStandardContextMenu();
    //menu->addAction(tr("Hola"));
  menu->addAction("Agregar componente", this, SLOT(saveNew()));

  QTextCursor cursor = ui->textEdit->textCursor();
  int y = cursor.blockNumber() + 1;
qDebug()<<y;
ui->textEdit->textCursor().insertText("holaAA");

    menu->exec(ui->textEdit->mapToGlobal(pt));
    delete menu;
}
*/
void MainWindow::on_menu_clicked(QAction*action){

if(action->data().toInt()<fa.length()) ui->textEdit->textCursor().insertText(init_component[action->data().toInt()]);
else{
    ui->textEdit->textCursor().insertText("cmp_"+QString::number(n_component));
    ui->textEdit->textCursor().insertText(inst_component[action->data().toInt()-fa.length()]);
     n_component++;
}

}
void MainWindow::on_menu2_clicked(QAction*action){
   //  qDebug()<<action->data().toInt();
     //ui->textEdit->textCursor().insertText(fa[action->data().toInt()]);
     ui->textEdit->textCursor().insertText(QString::number(action->data().toInt()));


}
void MainWindow::saveNew(){
ejemplo.show();

      ui->textEdit->append("holar");

/*
    if(menu_componente->actions().at(hh)->text()==fa[hh]){
        ui->textEdit->append(fa[hh]);

    }
*/


}


void MainWindow::on_pushButton_15_clicked()
{

}

void MainWindow::on_actionGuardar_todo_triggered()
{
    //qDebug()<<nombre[0]+dirPuro[0];

    for (int j=0;j<=i;j++){
        QString dir=dirPuro[j]+nombre[j];
        QFile file2(dir);
            if(!file2.open(QFile::WriteOnly | QFile::Text)){return;}
            QTextStream out(&file2);
            out << codigo[j];
            file2.flush();
            file2.close();
    }

/*

            QString dir=ubicacionActual+nombreActual+".vhdl";
            QFile file2(dir);
                if(!file2.open(QFile::WriteOnly | QFile::Text)){return;}
                QTextStream out(&file2);
                out << ui->textEdit->toPlainText();
                file2.flush();
                file2.close();
*/




}

void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
    ui->listWidget->clear();
QString sPath = dirModel->fileInfo(index).absoluteFilePath();
ui->listWidget->setRootIndex(fileModel->setRootPath(sPath));
QDir path(sPath);
QStringList filters;
filters << "*.vhdl";
path.setNameFilters(filters);
items = path.entryList();

//ui->listWidget->addItems(items);
for(int i=0;i<items.length();i++){
    QListWidgetItem * a = new QListWidgetItem(QIcon(":/iconos/file4.png"),items[i]);

    ui->listWidget->addItem(a);
  //  ui->listWidget->addItem(new QListWidgetItem(QIcon(":/f/F.png"),items[i]));
}
}

void MainWindow::on_listView_doubleClicked(const QModelIndex &index)
{
    QString sPath = dirModel->fileInfo(index).absoluteFilePath();
    //ui->textEdit->append(sPath);
    dir=sPath;
    file.setFileName(dir);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    return;
    else {
       i++;

        fileInfo=(file.fileName());
        nombre[i]=fileInfo.fileName();
        dirPuro[i]=fileInfo.absolutePath();dirPuro[i]+='/';
        //ui->listWidget->addItem(nombre[i]);
        in.setDevice(&file);
        codigo[i]=in.readAll();
      //  ui->textEdit->setText(codigo[i]);
        ui->textEdit_3->setText("");
            for(sd=1;sd<= ui->textEdit->document()->blockCount();sd++){
                ui->textEdit_3->append(QString::number(sd));
ui->textEdit_3->setAlignment(Qt::AlignRight);
            //
            }
            ui->textEdit_3->verticalScrollBar()->setValue(ui->textEdit->verticalScrollBar()->value());
//ui->listWidget->setCurrentRow(i);
if(i==0)ui->textEdit->setText(codigo[0]);

ui->groupBox->setVisible(true);
ui->groupBox_2->setVisible(false);
ui->groupBox_4->setVisible(false);
ui->groupBox_5->setVisible(false);
    }

//connect(ui->listView, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)), this, SLOT(currentItemChanged(QListWidgetItem*,QListWidgetItem*)));
}

void MainWindow::on_listView_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
   // ui->groupBox->setTitle("Proyecto actual: "+current->text());
   ui->textEdit->append(current->text());
/*
if(i>=1){
  //  ui->textEdit_2->setText(current->text());
  //  ui->textEdit_2->append(previous->text());
    ui->textEdit_2->setText(QString::number(ui->listWidget->row(current)));
    ui->textEdit_2->append(QString::number(ui->listWidget->row(previous)));
codigo[ui->listWidget->row(previous)]=ui->textEdit->toPlainText();
ui->textEdit->setText(codigo[ui->listWidget->row(current)]);
ubicacionActual=dirPuro[ui->listWidget->row(current)];
nombreActual=nombre[ui->listWidget->row(current)];
}
*/
}

void MainWindow::on_treeView_doubleClicked(const QModelIndex &index)
{

}

void MainWindow::on_listWidget_itemChanged(QListWidgetItem *item)
{

}

void MainWindow::on_treeView_collapsed(const QModelIndex &index)
{

}
/*
void MyTextEdit::keyPressEvent(QKeyEvent *event){
    if(event->key()==Qt::Key_1){
        qDebug()<<"hola";
    }
    else {
       QTextEdit::keyPressEvent( event );
    }
}

*/

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->textEdit)
    {
        if(event->type() == QKeyEvent::KeyPress)
        {

            QKeyEvent * ke = static_cast<QKeyEvent*>(event);
            //if(ke->key() == Qt::Key_F1)
             if ( (ke->key() == Qt::Key_G)  && QApplication::keyboardModifiers() && Qt::ControlModifier)
            {
instancear_componente();
                return true; // do not process this event further
            }

             if ( (ke->key() == Qt::Key_F)  && QApplication::keyboardModifiers() && Qt::ControlModifier)
            {
declarar_componente();
                return true; // do not process this event further
            }

             if ( (ke->key() == Qt::Key_R)  && QApplication::keyboardModifiers() && Qt::ControlModifier)
            {
                compilar(ubicacionActual+nombreActual+".vhdl");
                 return true; // do not process this event further
             }


            if(ui->listWidget->count()>0){
                QString a= ui->listWidget->currentItem()->text();
                a=a.replace("*","");
                ui->listWidget->currentItem()->setText("*"+a);
            }
        }
        return false; // process this event further
    }
    else
    {
        // pass the event on to the parent class
        return QMainWindow::eventFilter(watched, event);
    }
}

void MainWindow::on_actionInstanciar_componente_triggered()
{
 instancear_componente();
}

void MainWindow::on_actionCompilar_triggered()
{
    guardar(ubicacionActual+nombreActual+".vhdl");
compilar(nombreActual+".vhdl");
}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{

}

void MainWindow::on_listWidget_2_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    current2=ui->listWidget_2->row(current);
    previous2=ui->listWidget_2->row(previous);
    nombreActual=items_testbench[ui->listWidget_2->row(current)];
     codigo_t[ui->listWidget_2->row(previous)]=ui->textEdit->toPlainText();
        ui->textEdit->setText(codigo_t[ui->listWidget_2->row(current)]);

}

void MainWindow::on_tabWidget_tabBarClicked(int index)
{
    //ui->textEdit_2->append("si"+QString::number(index));
}

void MainWindow::on_tabWidget_currentChanged(int index)
{

    if(index==1){
        //nombreActual=items_normales[current1];
         codigo[current1]=ui->textEdit->toPlainText();
         ui->listWidget_2->setCurrentRow(0);
            ui->textEdit->setText(codigo_t[current2]);
    }
    if(index==0){
         codigo_t[current2]=ui->textEdit->toPlainText();
         ui->textEdit->setText(codigo[current1]);
    }
}

void MainWindow::on_actionSalir_triggered()
{
    close();
}

void MainWindow::on_lineEdit_6_returnPressed()
{

    proyecto.clear();
 //   if(i>=0)codigo[i]=ui->textEdit->toPlainText();
    bool bien=true;
    proyecto+="library ieee;\nuse ieee.std_logic_1164.all;\n\nentity ";
    proyecto+=ui->lineEdit_6->text().toUtf8().constData();
    proyecto+=" is\nport(\n";

  //  QString item_2,item_3;QStringList InputComboData;
for(int j=0;j<ui->tableWidget_2->model()->rowCount();j++){
    bien=true;
    QTableWidgetItem* item = ui->tableWidget_2->item(j,0);
    if (!item || item->text().isEmpty())
    {
      bien=false;
    }
    //if(ui->tableWidget_2->item(j,0)->text().isEmpty()){bien=false;break;}
    if(bien){
    proyecto+=ui->tableWidget_2->item(j,0)->text().toUtf8().constData();proyecto+=" : ";
    QComboBox *m = qobject_cast<QComboBox*>(ui->tableWidget_2->cellWidget(j,1));
   proyecto+=m->currentText().toUtf8().constData();proyecto+=" ";


    int num = ui->tableWidget_2->item(j,2)->text().toInt();
   //  int num=2;
   if(num>1){
   if(j==ui->tableWidget_2->model()->rowCount()-1)
       proyecto+="std_logic_vector("+to_string(num-1)+" downto 0)\n";
   else
       proyecto+="std_logic_vector("+to_string(num-1)+" downto 0);\n";
   }
   else{if(j==ui->tableWidget_2->model()->rowCount()-1)proyecto+="std_logic\n";
       else
           proyecto+="std_logic;\n";}

    //InputComboData << m->currentText();
    }}
//cout<<proyecto<<endl;

proyecto+=");\n";
proyecto+="end ";
proyecto+=ui->lineEdit_6->text().toUtf8().constData();
proyecto+=";\n\n";
proyecto+="architecture arc of ";
proyecto+=ui->lineEdit_6->text().toUtf8().constData();
proyecto+=" is\n\nbegin\n\nend arc;";




ui->groupBox->setVisible(true);
ui->groupBox_2->setVisible(false);
ui->groupBox_4->setVisible(false);
ui->groupBox_5->setVisible(false);

for(sd=1;sd<= ui->textEdit->document()->blockCount();sd++){
    ui->textEdit_3->append(QString::number(sd));
ui->textEdit_3->setAlignment(Qt::AlignRight);}
ui->textEdit_3->verticalScrollBar()->setValue(ui->textEdit->verticalScrollBar()->value());

//guardar
ubicacionActual=ui->lineEdit_5->text();
nombreActual=ui->lineEdit_6->text();
nombreActual.replace(".vhdl","");
nombreActual+=".vhdl";
QString dir=ubicacionActual+nombreActual;
QFile file(dir);
    if(!file.open(QFile::WriteOnly | QFile::Text)){return;}
    QTextStream out(&file);
out << proyecto.c_str();
    file.flush();
    file.close();


//cargar

    QString nom=dir.mid(dir.lastIndexOf("/")+1,dir.length());
    QString fol=dir.mid(0,dir.lastIndexOf("/"));fol+="/";

  //  dirModel->setRootPath("");
ui->treeView->setCurrentIndex(dirModel->setRootPath(fol));


    ui->listWidget->blockSignals(true);
    ui->listWidget->clear();
    ui->listWidget->blockSignals(false);

    items.clear();items_normales.clear();items_testbench.clear();
            QDir path(fol);
            QStringList filters;
            filters << "*.vhdl";
            path.setNameFilters(filters);
            items = path.entryList();


for(int i=0;i<items.length();i++){
QListWidgetItem * a = new QListWidgetItem(items[i]);
if(!a->text().contains("_tb")){
items_normales<<items[i];
a->setIcon(QIcon(":/iconos/file7.png"));
ui->listWidget->addItem(a);
}
else {

items_testbench<<items[i];
a->setIcon(QIcon(":/iconos/file8.png"));
ui->listWidget_2->addItem(a);
}
}

for(int i=0;i<items_testbench.length();i++){
QString dir=ubicacionActual+items_testbench[i];
QFile file(dir);
if (!file.open(QIODevice::ReadOnly | QIODevice::Text))return;
else {
 fileInfo=(file.fileName());
 nombre_t[i]=fileInfo.fileName();
 dirPuro_t[i]=fileInfo.absolutePath();dirPuro[i]+='/';
 in.setDevice(&file);
 codigo_t[i]=in.readAll();
 ui->textEdit_3->setText("");
 for(sd=1;sd<= ui->textEdit->document()->blockCount();sd++){
 ui->textEdit_3->append(QString::number(sd));
 ui->textEdit_3->setAlignment(Qt::AlignRight);}
 ui->textEdit_3->verticalScrollBar()->setValue(ui->textEdit->verticalScrollBar()->value());
 ui->listWidget_2->setCurrentRow(0);
}
}

for(int i=0;i<items_normales.length();i++){
QString dir=ubicacionActual+items_normales[i];
QFile file(dir);
if (!file.open(QIODevice::ReadOnly | QIODevice::Text))return;
else {
 fileInfo=(file.fileName());
 nombre[i]=fileInfo.fileName();
 dirPuro[i]=fileInfo.absolutePath();dirPuro[i]+='/';
 in.setDevice(&file);
 codigo[i]=in.readAll();
 ui->textEdit_3->setText("");
 for(sd=1;sd<= ui->textEdit->document()->blockCount();sd++){
 ui->textEdit_3->append(QString::number(sd));
 ui->textEdit_3->setAlignment(Qt::AlignRight);}
 ui->textEdit_3->verticalScrollBar()->setValue(ui->textEdit->verticalScrollBar()->value());
 if(items_normales[i]==nom){ui->listWidget->setCurrentRow(i);ui->textEdit->setText(codigo[i]);}
}
}

}
