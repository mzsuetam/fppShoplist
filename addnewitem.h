#ifndef ADDNEWITEM_H
#define ADDNEWITEM_H

#include <QDialog>
#include <QMainWindow>
#include <QtGui>
#include <QList>

#include "root.h"
#include "items.h"

namespace Ui {
class addNewItem;
}

class addNewItem : public QDialog
{
    Q_OBJECT

public:
    explicit addNewItem(QWidget *parent = nullptr);
    ~addNewItem();

    void refreshList();

    void init(root* _root, QList<Item>* _all_items);
    void init(root* _root, QList<Item>* _all_items, QString id, double amount);
    void init(root* _root, QList<Item>* _all_items, bool search);

private slots:

    void on_pushButtonCancel_pressed();

    void listItemClicked(const QModelIndex &index);

    void on_pushButtonOk_pressed();

    void on_inputID_textChanged();

private:
    Ui::addNewItem *ui;

    QStringListModel *model_searched_items;

    bool searchmode = false;

    int AMOUNT_MAX = 100000;

public:
    root* root_ptr;
    QList<Item> searched_items;
    const QList<Item>* all_items;

};

#endif // ADDNEWITEM_H
