#ifndef EJEMPLOS_H
#define EJEMPLOS_H

#include <QDialog>
#include<QListWidgetItem>
#include"highlighter.h"
namespace Ui {
class ejemplos;
}

class ejemplos : public QDialog
{
    Q_OBJECT

public:
    explicit ejemplos(QWidget *parent = nullptr);
    ~ejemplos();

private slots:




    void on_listWidget_itemChanged(QListWidgetItem *item);

    void on_listWidget_itemSelectionChanged();

    void on_pushButton_2_clicked();

private:
    Ui::ejemplos *ui;
    Highlighter *highlighter;
};

#endif // EJEMPLOS_H
