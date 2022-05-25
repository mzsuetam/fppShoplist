#include "root.h"
#include "ui_root.h"

#include "addnewitem.h"
#include "infodialog.h"

#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QList>


root::root(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::root)
{
    ui->setupUi(this);
    setWindowTitle("FppShoplist 2.0");
    setWindowIcon(QIcon(":/icons/resources/icons/cart-check.svg"));

    // tableViewItemsInCart
    model_items_in_cart = new QStringListModel(this);
    ui->listViewItemsInCart->setModel(model_items_in_cart);

    // importing data list
    QDir dir("resources"); // if folder doesnt exist, create it
    if (!dir.exists())
        dir.mkpath(".");
    importItemList(QDir::currentPath() + "/resources/items.list", all_items);


}

root::~root()
{
    backupItemList();
    delete ui;
}

void root::listItemClicked(const QModelIndex &index){
    int id = index.row();
    if ( id == selected_item || id < 0 || id > items_in_chart.size() -1 ) return;
    selected_item = id;
}

void root::refreshList(){
    // clear model
    model_items_in_cart->removeRows( 0, model_items_in_cart->rowCount() );
    // add searched elements
    for (int i=0; i<items_in_chart.size(); i++){
        QString label = "";
        model_items_in_cart->insertRow(model_items_in_cart->rowCount());
        QModelIndex index = model_items_in_cart->index(i);
        label += QString::number(i).rightJustified(3, ' ')
            + QString::number(items_in_chart[i].amount).rightJustified(10, ' ')
            + items_in_chart[i].id.rightJustified(10, ' ')
            + "     " +  items_in_chart[i].name;
        model_items_in_cart->setData(index, label);
    }

    // connecting pressing items in the list with function
    connect( ui->listViewItemsInCart, SIGNAL(clicked(const QModelIndex &) ), this, SLOT( listItemClicked(const QModelIndex &) ) );
}


void root::on_actionImport_data_from_file_triggered()
{
    // cannot have data in cart
    if ( items_in_chart.size() > 0 ){
        QMessageBox::critical(this, "Error!", "List must be empty to import new data!");
        return;
    }

    QString ipath = QFileDialog::getOpenFileName(this, tr("Open File"),"/path/to/file/",tr("FPP Backup files (*.CDN)"));
    if ( ipath.length() == 0 ) return;

    // computing file and getting data
    bool imp = importItemList(ipath, all_items);

    // saving data to default file
    QDir dir("resources"); // if folder doesnt exist, create it
    if (!dir.exists())
        dir.mkpath(".");
    QString epath = QDir::currentPath() + "/resources/items.list";
    // cannot use resources because they are stored in exe in binary files in read-only for the exe
    bool exp = exportItemList(epath, all_items);

    if ( imp && exp )
        QMessageBox::information(this, "Success!", "Data imported successfully!");
}

bool root::importItemList(QString path, QList<Item>& list){
    QFile inputFile(path);
    if (inputFile.open(QIODevice::ReadOnly))
    {
       list.clear();
       QTextStream in(&inputFile);
       while (!in.atEnd())
       {
          QString line = in.readLine();
          QStringList data = line.split( "," );
          QString cat = data[0].split( '"' )[1];
          QString id = data[1].split( '"' )[1];
          QString name = data[2].split( '"' )[1];

          list.append(Item(id,name,cat));
       }
       inputFile.close();
    }
    else{
        QMessageBox::critical(this, "Error!", "Error reading from file!");
        return false;
    }
    return true;
}

bool root::importItemList(QString path, QList<ItemInCart>& list){
    QFile inputFile(path);
    if (inputFile.open(QIODevice::ReadOnly))
    {
       list.clear();
       QTextStream in(&inputFile);
       while (!in.atEnd())
       {
          QString line = in.readLine();
          QStringList data = line.split( "," );
          double amo = data[0].split( '"' )[1].toDouble(); // assuming that data in backup is OK
          QString id = data[1].split( '"' )[1];
          QString name = data[2].split( '"' )[1];

          list.append(ItemInCart(amo,id,name));
       }
       inputFile.close();
    }
    else{
        QMessageBox::critical(this, "Error!", "Error reading from file!");
        return false;
    }
    return true;
}


bool root::exportItemList(QString path, QList<Item>& list){
    QFile exportFile(path);
    if ( exportFile.open(QIODevice::WriteOnly) ){
       for (int i=0; i<list.size();i++){
           QTextStream stream(&exportFile);
           stream << '"' << list[i].category << "\",\"" << list[i].id << "\",\"" << list[i].name << '"' << Qt::endl;
       }
       exportFile.close();
    }
    else{
        QMessageBox::critical(this, "Error!", "Error saving to file!");
        return false;
    }
    return true;
}
bool root::exportItemList(QString path, QList<ItemInCart>& list){
    QFile exportFile(path);
    if ( exportFile.open(QIODevice::WriteOnly) ){
       for (int i=0; i<list.size();i++){
           QTextStream stream(&exportFile);
           stream << '"'<< list[i].amount << "\",\"" << list[i].id << "\",\"" << list[i].name << '"' << Qt::endl;
       }
       exportFile.close();
    }
    else{
        QMessageBox::critical(this, "Error!", "Error saving to file!");
        return false;
    }
    return true;
}

void root::addItemToList( double _amount, QString _id, QString _name){
    // creating item
    ItemInCart new_item(_amount,_id,_name);
    items_in_chart.append(new_item);

    refreshList();
}

void root::on_actionInsert_triggered()
{
    addNewItem new_window;
    new_window.setModal(true);
    new_window.init(this, &all_items);
    setEnabled(false);
    new_window.exec();
}


void root::on_actionClear_triggered()
{
    model_items_in_cart->removeRows(0,model_items_in_cart->rowCount());
    items_in_chart.clear();
}


void root::on_actionDelete_triggered()
{
    if ( selected_item < 0 || selected_item > items_in_chart.size() -1 ) return;

    model_items_in_cart->removeRows(selected_item,1);
    items_in_chart.removeAt(selected_item);

    refreshList();
}


void root::on_actionEdit_triggered()
{
    if ( selected_item < 0 || selected_item > items_in_chart.size() -1 ) return;

    int _n = items_in_chart.size();
    QString _id = items_in_chart[selected_item].id;
    double _amount = items_in_chart[selected_item].amount;

    addNewItem new_window;
    new_window.setModal(true);
    new_window.init(this, &all_items, _id, _amount);
    setEnabled(false);
    new_window.exec();

    if ( _n != items_in_chart.size() ){
        on_actionDelete_triggered();
    }

    refreshList();
}


void root::on_actionSearch_Item_triggered()
{
    addNewItem new_window;
    new_window.setModal(true);
    new_window.init(this, &all_items, true); // true - search mode
    setEnabled(false);
    new_window.exec();
}

bool root::backupItemList(){
    QDir dir("resources"); // if folder doesnt exist, create it
    if (!dir.exists())
        dir.mkpath(".");
    QString epath = QDir::currentPath() + "/resources/backup.list";
    // cannot use resources because they are stored in exe in binary files in read-only for the exe
    if ( exportItemList(epath, items_in_chart) ) return true;
    return false;
}



void root::on_actionTransfer_triggered()
{
    backupItemList();

    // make transfer
}


void root::on_actionRestore_triggered()
{
    QDir dir("resources");
    QString epath = QDir::currentPath() + "/resources/backup.list";
    if ( !dir.exists() || !importItemList(epath, items_in_chart) ){
        QMessageBox::critical(this, "Error!", "Unable to access backup file!");
    }
    refreshList();
}

void root::on_actionBackup_triggered()
{
    backupItemList();
}


void root::on_actionAbout_triggered()
{
    InfoDialog new_window;
    new_window.setModal(true);
    new_window.init(this, "About");
    setEnabled(false);
    new_window.exec();
}


void root::on_actionShortcuts_triggered()
{
    InfoDialog new_window;
    new_window.setModal(true);
    new_window.init(this, "Shortcuts");
    setEnabled(false);
    new_window.exec();
}

