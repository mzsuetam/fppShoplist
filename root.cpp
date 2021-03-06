#include "root.h"
#include "ui_root.h"

#include "addnewitem.h"
#include "infodialog.h"
#include "tcpsocket.h"

#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QList>

// @TODO:
// auto-maximise - done, to settings?
// input from utf8 files on windows32bit - done, to check


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

    // importing settings:
    loadSettings();
    showMaximized();

    // refresh list:
    ui->HeaderViewItemsInCart->setText("  n: AMOUNT - PRICE SUM -    ID - NAME [PRICE PER UNIT]");
    refreshList();
}

root::~root()
{
    backupItemList();
    delete ui;
}

void root::listItemClicked(const QModelIndex &index){
    int id = index.row();
    if ( id == selected_item || id < 0 || id > items_in_cart.size() -1 ) return;
    selected_item = id;
}

void root::refreshList(){
    double sum=0;
    // clear model
    model_items_in_cart->removeRows( 0,model_items_in_cart->rowCount() );
    // add searched elements
    for (int i=0; i<items_in_cart.size(); i++){
        QString label = "";
        double row_cost = items_in_cart[i].getPrice().toDouble()*items_in_cart[i].getAmount();
        sum += row_cost;
        model_items_in_cart->insertRow(model_items_in_cart->rowCount());
        QModelIndex index = model_items_in_cart->index(i);
        label += QString::number(i+1).rightJustified(3, ' ')
            + ": " + QString::number( items_in_cart[i].getAmount() ).rightJustified(6, ' ') + " - "
            //+ "[" + items_in_cart[i].getCategory().rightJustified(5,' ') + "] "
            + QString::number( row_cost ).rightJustified(6,' ') + "z?? - "
            + items_in_cart[i].getId().rightJustified(5,' ')+ " - "
            + items_in_cart[i].getName() + " ["
            + items_in_cart[i].getPrice() + "z??/"
            + items_in_cart[i].getUnit1()
            //+ " " + items_in_cart[i].getUnit2()
            + "]"
            ;
        model_items_in_cart->setData(index, label);

        // @TODO: add unit1, unit2 and price displaying
    }

    // connecting pressing items in the list with function
    connect( ui->listViewItemsInCart, SIGNAL(clicked(const QModelIndex &) ), this, SLOT( listItemClicked(const QModelIndex &) ) );

    // refreshing summary
    ui->SummaryViewItemsInCart_amount->setText("Total items in cart: " + QString::number(items_in_cart.size()));
    ui->SummaryViewItemsInCart_value->setText( "Total value: " + QString::number(sum)+ "z??");
}

void root::addItemToList(double _amount, QString _id, QString _name, QString _unit1, QString  _unit2, QString _price){
    // creating item
    ItemInCart new_item(_amount,_id,_name,_unit1,_unit2,_price);
    items_in_cart.append(new_item);

    refreshList();
}

bool root::importItemList(QString path, QList<Item>& list){
    QFile inputFile(path);
    if (inputFile.open(QIODevice::ReadOnly))
    {
       list.clear();
       QTextStream in(&inputFile);
       in.setCodec("windows-1250");
       while (!in.atEnd())
       {
          QString line = in.readLine();
          QStringList data_in_record = {};
          bool quoting = false;
          int l=0, p=0, c; // c - quote signs correction
          while ( p < line.size() ){
              if ( line[p] == ',' && !quoting ){
                  if ( line[l] == '"') c=1;
                  else c=0;
                  data_in_record.append( line.mid(l+c,p-l-2*c) );
                  l = ++p;
              }
              if ( line[p] == '"' ){
                  quoting = !quoting;
              }
              p++;
          }
          if ( line[l] == '"') c=1;
          else c=0;
          data_in_record.append( line.mid(l+c,p-l-2*c) );

          if ( data_in_record.size() >= 16 ){
              QString cat = data_in_record[0];
              QString id = data_in_record[1];
              QString name = data_in_record[2];
              QString unit1 = data_in_record[7];
              QString unit2 = data_in_record[8];
              QString price = data_in_record[15];

              list.append( Item(id,name,cat,unit1,unit2,price) );
          }
          else if ( data_in_record.size() >= 6 ){
              QString cat = data_in_record[0];
              QString id = data_in_record[1];
              QString name = data_in_record[2];
              QString unit1 = data_in_record[3];
              QString unit2 = data_in_record[4];
              QString price = data_in_record[5];

              list.append( Item(id,name,cat,unit1,unit2,price) );
          }
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
       in.setCodec("windows-1250");
       while (!in.atEnd())
       {
           QString line = in.readLine();
           QStringList data_in_record = {};
           bool quoting = false;
           int l=0, p=0, c; // quote signs correction
           while ( p < line.size() ){
               if ( line[p] == ',' && !quoting ){
                   if ( line[l] == '"') c=1;
                   else c=0;
                   data_in_record.append( line.mid(l+c,p-l-2*c) );
                   l = ++p;
               }
               if ( line[p] == '"' ){
                   quoting = !quoting;
               }
               p++;
           }
           if ( line[l] == '"') c=1;
           else c=0;
           data_in_record.append( line.mid(l+c,p-l-2*c) );

           if ( data_in_record.size() >= 6 ){
               double amount = data_in_record[0].toDouble();
               QString id = data_in_record[1];
               QString name = data_in_record[2];
               QString unit1 = data_in_record[3];
               QString unit2 = data_in_record[4];
               QString price = data_in_record[5];

               list.append( ItemInCart(amount,id,name,unit1,unit2,price) );
            }
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
           stream.setCodec("windows-1250");
           stream << '"' << list[i].getCategory() << "\",\"" << list[i].getId() << "\",\"" << list[i].getName() << "\",\""
                   << list[i].getUnit1() << "\",\"" << list[i].getUnit2() << "\",\"" << list[i].getPrice() << '"' << Qt::endl;
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
           stream.setCodec("windows-1250");
           stream << '"' << list[i].getAmount() << "\",\"" << list[i].getId() << "\",\"" << list[i].getName() << "\",\""
                  << list[i].getUnit1() << "\",\"" << list[i].getUnit2() << "\",\"" << list[i].getPrice() << '"' << Qt::endl;
       }
       exportFile.close();
    }
    else{
        QMessageBox::critical(this, "Error!", "Error saving to file!");
        return false;
    }
    return true;
}

bool root::backupItemList(){
    QDir dir("resources"); // if folder doesnt exist, create it
    if (!dir.exists())
        dir.mkpath(".");
    QString epath = QDir::currentPath() + "/resources/backup.list";
    // cannot use resources because they are stored in exe in binary files in read-only for the exe
    if ( exportItemList(epath, items_in_cart) ) return true;
    return false;
}

void root::saveSettings(){
    QDir dir("resources"); // if folder doesnt exist, create it
    if (!dir.exists())
        dir.mkpath(".");
    QFile exportFile(QDir::currentPath() + "/resources/settings.cfg");
    if ( exportFile.open(QIODevice::WriteOnly) ){
       QTextStream stream(&exportFile);
       stream.setCodec("UTF-8");
       // default_ip:
       stream << "default_ip:" << server_ip << '\n';
       exportFile.close();
       // other settings:
    }
    else{
        QMessageBox::critical(this, "Error!", "Error saving the default settings!");
    }
}

void root::loadSettings(){
    QFile inputFile(QDir::currentPath() + "/resources/settings.cfg");
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       in.setCodec("UTF-8");
       while (!in.atEnd())
       {
          QString line = in.readLine();
          // default ip
          if ( line.contains("default_ip:") && line.split(":")[0] != line )
              server_ip = line.split(":")[1];
          // other settings
       }
       inputFile.close();
    }
    else{
        QMessageBox::critical(this, "Error!", "Error accessing default settings!");
    }
}

// SLOTS  ////////////////////////////////////////////////////////////////

void root::on_actionImport_data_from_file_triggered()
{
    // cannot have data in cart
    if ( items_in_cart.size() > 0 ){
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
    items_in_cart.clear();
    refreshList();
}

void root::on_actionDelete_triggered()
{
    if ( selected_item < 0 || selected_item > items_in_cart.size() -1 ) return;

    model_items_in_cart->removeRows(selected_item,1);
    items_in_cart.removeAt(selected_item);

    refreshList();
}

void root::on_actionEdit_triggered()
{
    if ( selected_item < 0 || selected_item > items_in_cart.size() -1 ) return;

    int _n = items_in_cart.size();
    QString _id = items_in_cart[selected_item].getId();
    double _amount = items_in_cart[selected_item].getAmount();

    addNewItem new_window;
    new_window.setModal(true);
    new_window.init(this, &all_items, _id, _amount);
    setEnabled(false);
    new_window.exec();

    if ( _n != items_in_cart.size() ){
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

void root::on_actionTransfer_triggered()
{
    backupItemList();

    if ( server_ip == "" ){
        QMessageBox::critical(this, "Error!", "No host computer saved!");
        return;
    }

    if ( items_in_cart.size() == 0 ){
        QMessageBox::critical(this, "Error!", "List for transfer cannot be empty!");
        return;
    }

    setEnabled(false);

    // TRANSFER SECTION:
    TcpSocket *socket = new TcpSocket(server_ip);

    bool ok;
    if ( !socket->isConnected() ){ // if failed to aquire connection
        QMessageBox::critical(this, "Error!", "Unable to connect to Host computer!");
        delete socket;
        setEnabled(true);
        return;
    }
    // if connection aquired:
    socket->writeValidateMsg(); // ask for connection validation
    bool recieved;
    QString ans = socket->read( recieved ); // get validation ans
    if ( recieved && ans=="Connection to FppShoplist host validated!" ){ // if conection validated
        QString server_status = socket->read(ok); // get server status
        if ( ok && server_status == "0" ){ // 0 - server ready
            socket->writeDataMsg(); // inform server about data transfer
            socket->write("n:"+QString::number(items_in_cart.size())); // how many products
            for (int i=0; i<items_in_cart.size(); i++){ // sending all produckts
                socket->write(items_in_cart[i].getId() + ":" + QString::number(items_in_cart[i].getAmount())); // in format id:amount
            }
            socket->write("e:"); // inform about the end
            QString server_transfer_status = socket->read(ok); // get server response about the stattus
            if ( ok && server_transfer_status == "1" ){ // 1 - error, transfer corrupted
                QMessageBox::critical(this, "Error!", "Data transfer corrupted!");
                setEnabled(true);
                return;
            }
            else if ( ok ){
                QMessageBox::information(this, "Success!", "Data imported successfully!");
            }
            else{ // ok == false
                QMessageBox::critical(this, "Error!", "Host computer not responding!");
                setEnabled(true);
                return;
            }
        }
        else if ( ok && server_status == "1" ){
            QMessageBox::critical(this, "Error!", "Host computer is not expecting transfer!\nTry CTRL+Ins");
            socket->writeDisconnectMsg();
            setEnabled(true);
            return;
        }
        else if ( ok && server_status == "2" ){
            QMessageBox::critical(this, "Error!", "Host computer busy!");
            socket->writeDisconnectMsg();
            setEnabled(true);
            return;
        }
        else { // ok == false
            QMessageBox::critical(this, "Error!", "Host computer not responding!");
            setEnabled(true);
            return;
        }
    }
    else { // ( recieved && ans=="Connection to FppShoplist host validated!" ) == false
        QMessageBox::critical(this, "Error!", "Connection error!");
        setEnabled(true);
        return;
    }
    setEnabled(true);
    delete socket;
}

void root::on_actionRestore_triggered()
{
    QDir dir("resources");
    QString epath = QDir::currentPath() + "/resources/backup.list";
    if ( !dir.exists() || !importItemList(epath, items_in_cart) ){
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

void root::on_actionSearch_for_Host_triggered()
{
    QMessageBox::information(this, "Info!", "Searching for host computer\nwill start after closing this window!\nThis can take a while.");
    setEnabled(false);
    TcpSocket *socket = new TcpSocket();
    QString found_ip = socket->searchLocalForHost();
    if ( found_ip != "" ){
        QMessageBox::information(this, "Success!", "Found host computer!");
        server_ip = found_ip;
        saveSettings();
    }
    else{
        QMessageBox::critical(this, "Error!", "Unable to find host computer!");
    }
    setEnabled(true);
    delete socket;
}

