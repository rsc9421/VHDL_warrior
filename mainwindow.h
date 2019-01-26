#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QWidget>
#include <QFile>
#include <QMainWindow>
#include <QTextStream>
#include<QFileDialog>
#include<QProcess>
#include<QCursor>
#include<QTextCursor>
#include<QScrollBar>
#include<QListWidgetItem>
#include<QFontDialog>
#include<QFont>
#include<QMessageBox>
#include<QDir>
#include<QStringList>
#include<QListWidgetItem>
#include<QDebug>
#include <sstream>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <ctype.h>
#include<locale>
#include<QTextEdit>
#include<QPlainTextEdit>
#include<QApplication>
#include"highlighter.h"
#include"ejemplos.h"
#include<QPainter>
#include<QItemDelegate>
namespace Ui {
class MainWindow;
}




/*
class MyTextEdit : public QTextEdit
{
    Q_OBJECT
public :
    //void keyPressEvent(QKeyEvent *e);
   void keyPressEvent ( QKeyEvent * event );


};
*/
/*
class MyTextEdit : public QTextEdit
{
    Q_OBJECT
public:
    explicit MyTextEdit(QWidget *parent = 0);
//~MyTextEdit();
protected:
   virtual void keyPressEvent ( QKeyEvent * event );
signals:
public slots:
};
*/

class MyDelegate : public QItemDelegate {
  public:

    MyDelegate( QObject *parent ) : QItemDelegate( parent ) { }

    void paint( QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index ) const {
      QItemDelegate::paint( painter, option, index );

       painter->setPen(QPen(QColor(0,200,0),1));
//painter->drawLine(option.rect.bottomLeft(),option.rect.topLeft());
//painter->drawLine(option.rect.bottomRight(),option.rect.topRight());

   if( index.data(Qt::UserRole)==1) {
       painter->drawLine(option.rect.topLeft(),option.rect.topRight());
      }

   if( index.data(Qt::UserRole)==2) {
       painter->drawLine(option.rect.bottomLeft(),option.rect.bottomRight());
      }

   if( index.data(Qt::UserRole)==3) {
       painter->drawLine(option.rect.topLeft(),option.rect.topRight());
       painter->drawLine(option.rect.bottomLeft(),option.rect.topLeft());
      }

   if( index.data(Qt::UserRole)==4) {
       painter->drawLine(option.rect.topLeft(),option.rect.topRight());
        painter->drawLine(option.rect.bottomRight(),option.rect.topRight());
      }

   if( index.data(Qt::UserRole)==10) {
       painter->drawLine(option.rect.bottomLeft(),option.rect.topLeft());
       painter->drawLine(option.rect.topLeft(),option.rect.topRight());
       painter->drawLine(option.rect.bottomRight(),option.rect.topRight());
      }

    }

    };



class MainWindow : public QMainWindow
{
    Q_OBJECT


public:



    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QString dir;
    QFile file;
    QFileInfo fileInfo;
    QTextStream in;
    QString errorConsola="nada";
    QString Consola;
    QString codigo[100];
    QString direccion[100];
    QString nombre[100];
    QString dirPuro[100];
    QString codigo_t[100];
    QString direccion_t[100];
    QString nombre_t[100];
    QString dirPuro_t[100];
    int i=-1,ii=-1,j=0;
    QProcess process;
    QString convertidorActual="decimal";
    QString dirPuro_actual;
private slots:
    void on_actionAbrir_triggered();

    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

    void on_actionGuardar_triggered();

    void on_actionGuardar_como_triggered();

    void on_pushButton_clicked();

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_lineEdit_returnPressed();

    void on_listWidget_clicked(const QModelIndex &index);

    void on_textEdit_cursorPositionChanged();

    void on_pushButton_6_clicked();

    void on_checkBox_clicked();
void processFinished(int code , QProcess::ExitStatus status);
    void on_pushButton_7_clicked();

    void on_tableWidget_cellPressed(int row, int column);

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_tableWidget_pressed(const QModelIndex &index);

    void on_radioButton_3_clicked();

    void on_radioButton_4_clicked();

    void on_actionmodo_Blanco_triggered();

    void on_actionmodo_Dark_triggered();

    void on_actionFuente_2_triggered();

    void on_textEdit_textChanged();

    void on_actionNuevo_triggered();
void resizeEvent(QResizeEvent* event);
    void on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    void on_lineEdit_7_returnPressed();

    void on_pushButton_9_clicked();

    void on_pushButton_8_clicked();

    void on_listWidget_currentRowChanged(int currentRow);

    void on_pushButton_10_clicked();

    void on_textEdit_copyAvailable(bool b);

    void on_pushButton_11_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_12_clicked();

    void on_actionEjemplos_triggered();

    void on_actionAgregar_componente_triggered();

void saveNew();
void on_menu_clicked(QAction*);
void on_menu2_clicked(QAction*);
void showContextMenu(const QPoint &pt);
void on_pushButton_15_clicked();

void on_actionGuardar_todo_triggered();

void on_treeView_clicked(const QModelIndex &index);

void on_listView_doubleClicked(const QModelIndex &index);
void on_listView_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
void on_treeView_doubleClicked(const QModelIndex &index);

void on_listWidget_itemChanged(QListWidgetItem *item);

void on_treeView_collapsed(const QModelIndex &index);
bool eventFilter(QObject *object, QEvent *event);
void closeEvent (QCloseEvent *event);
//QString get_component2(QString dir);
//void keyPressEvent(QKeyEvent *e);
QString get_component3(QString dir, QString codigo);
void insertCompletion(const QString& completion);
void insertCompletion2(const QString& completion);
void on_actionInstanciar_componente_triggered();

void on_actionCompilar_triggered();
void declarar_componente();
void instancear_componente();
bool compilar(QString dir);
void guardar(QString dir) ;
void on_listWidget_itemClicked(QListWidgetItem *item);

void on_listWidget_2_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

void on_tabWidget_tabBarClicked(int index);

void on_tabWidget_currentChanged(int index);

void on_actionSalir_triggered();

void on_lineEdit_6_returnPressed();

void on_horizontalSlider_valueChanged(int value);

void on_pushButton_17_clicked();

void on_pushButton_18_clicked();

void on_pushButton_19_clicked();

void on_tableWidget_cellClicked(int row, int column);

private:
    Ui::MainWindow *ui;
    Highlighter *highlighter;
    ejemplos ejemplo;


};

#endif // MAINWINDOW_H
