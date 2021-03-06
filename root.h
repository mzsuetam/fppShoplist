#ifndef ROOT_H
#define ROOT_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QList>
#include <QtDebug>

#include "items.h"

QT_BEGIN_NAMESPACE
namespace Ui { class root; }
QT_END_NAMESPACE

class root : public QMainWindow
{
    Q_OBJECT

public:
    root(QWidget *parent = nullptr);
    ~root();

    void refreshList();

    void addItemToList(double _amount, QString _id, QString _name, QString _unit1, QString  _unit2, QString _price);

    bool importItemList(QString path, QList<Item>& list);
    bool importItemList(QString path, QList<ItemInCart>& list);

    bool exportItemList(QString path, QList<Item>& list);
    bool exportItemList(QString path, QList<ItemInCart>& list);

    bool backupItemList();

    void saveSettings();
    void loadSettings();

    QString getVer(){return ver;}

    QList<Item> all_items;

private slots:
    void listItemClicked(const QModelIndex &index);

    void on_actionInsert_triggered();

    void on_actionImport_data_from_file_triggered();

    void on_actionClear_triggered();

    void on_actionDelete_triggered();

    void on_actionEdit_triggered();

    void on_actionSearch_Item_triggered();

    void on_actionTransfer_triggered();

    void on_actionRestore_triggered();

    void on_actionBackup_triggered();

    void on_actionAbout_triggered();

    void on_actionShortcuts_triggered();

    void on_actionSearch_for_Host_triggered();

private:
    Ui::root *ui;
    QString ver="2.0.1-b.1";

    QStringListModel *model_items_in_cart;
    QList<ItemInCart> items_in_cart;
    int selected_item;

    QString server_ip = ""; //"192.168.0.178";
};
#endif // ROOT_H
