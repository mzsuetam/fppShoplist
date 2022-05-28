#include "addnewitem.h"
#include "ui_addnewitem.h"

#include <QDebug>
#include <QMessageBox>
#include <QShortcut>


addNewItem::addNewItem(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addNewItem)
{
    ui->setupUi(this);

    // listViewItems
    model_searched_items = new QStringListModel(this);
    ui->listViewItems->setModel(model_searched_items);

    // connecting
    //QShortcut *shortcut = new QShortcut(QKeySequence(Qt::Key_Return), parent);
    //QObject::connect(shortcut, SIGNAL(activated()), this, SLOT(on_pushButtonOk_pressed()));

    // all inits in init()

}

void addNewItem::init(root* _root, QList<Item>* _all_items){
    // ADD INIT
    root_ptr = _root;
    all_items = _all_items;

    setWindowTitle("Edit item in cart");
    setWindowIcon(QIcon(":/icons/resources/icons/plus-square.svg"));

    // starting with all items as searched
    searched_items = *all_items;
    refreshList();
}

void addNewItem::init(root* _root, QList<Item>* _all_items, QString id, double amount){
    // EDIT INIT

    root_ptr = _root;
    all_items = _all_items;

    setWindowTitle("Edit item in cart");
    setWindowIcon(QIcon(":/icons/resources/icons/pencil-square.svg"));

    // configuring window for edit purposes
    ui->inputID->setPlainText(id);
    ui->inputAmount->setPlainText(QString::number(amount));

    // starting with all items as searched
    searched_items = *all_items;
    refreshList();
}

void addNewItem::init(root* _root, QList<Item>* _all_items, bool search){
    // SEARCH INIT

    root_ptr = _root;
    all_items = _all_items;
    searchmode = search;

    // starting with all items as searched
    searched_items = *all_items;


    setWindowTitle("Search Items");
    setWindowIcon(QIcon(":/icons/resources/icons/search.svg"));

    // configuring window for search purposes
    delete ui->inputAmount;
    delete ui->pushButtonOk;

    ui->pushButtonCancel->setText("Back");
    ui->pushButtonCancel->setIcon(QIcon());
    ui->inputID->setMinimumWidth(200);
    ui->inputID->setPlaceholderText("Search...");


    refreshList();
}

addNewItem::~addNewItem()
{
    root_ptr->setEnabled(true);
    delete ui;

}

void addNewItem::listItemClicked(const QModelIndex &index){
    int id = index.row();
    if ( id < 0 || id > searched_items.size() -1 ) return;
    //qDebug() << id;
    Item itm = searched_items[id];
    ui->inputID->clear();
    ui->inputID->insertPlainText(itm.id);
    ui->inputAmount->setFocus();
}

void addNewItem::refreshList(){
    // clear model
    model_searched_items->removeRows( 0, model_searched_items->rowCount() );
    // add searched elements
    for (int i=0; i<searched_items.size(); i++){
        QString label = "[";
        model_searched_items->insertRow(model_searched_items->rowCount());
        QModelIndex index = model_searched_items->index(i);
        label += searched_items[i].category.rightJustified(5,' ') + "] "
                + searched_items[i].id.rightJustified(5,' ')+ " - " +  searched_items[i].name;
        model_searched_items->setData(index, label);
    }

    // connecting pressing items in the list with function
    if ( !searchmode )
        connect( ui->listViewItems, SIGNAL(clicked(const QModelIndex &) ), this, SLOT( listItemClicked(const QModelIndex &) ) );
}


void addNewItem::on_pushButtonCancel_pressed()
{
    this->close();
}


void addNewItem::on_pushButtonOk_pressed()
{
    QString id = ui->inputID->toPlainText();
    QString name;
    QString _amount = ui->inputAmount->toPlainText().replace(',','.');

    bool amount_ok;
    double amount = _amount.toDouble(&amount_ok);
    if ( !amount_ok ){ // amount is not a number
        QMessageBox::critical(this, "Error!", "Amount is not a number!");
        ui->inputAmount->setFocus();
        return;
    }
    if ( ( amount <= 0) || ( amount > AMOUNT_MAX) ){ // amount is not a number
        QMessageBox::critical(this, "Error!", "Amount must be bigger than 0 and smaller than " + QString::number(AMOUNT_MAX)) + "!";
        ui->inputAmount->setFocus();
        return;
    }

    bool id_ok = false;
    for ( int i=0; i<all_items->size();i++){
        if ( id == (*all_items)[i].id ){
            id_ok = true;
            name = (*all_items)[i].name;
            break;
        }
    }
    if ( !id_ok ){ // thers no such id in the sytem
        QMessageBox::critical(this, "Error!", "Unknown symbol!");
        ui->inputID->setFocus();
        return;
    }

    // all data is correct at this point
    root_ptr->addItemToList(amount,id,name);
    this->close();
}

void addNewItem::on_inputID_textChanged()
{
    QString input = ui->inputID->toPlainText();
    if ( input != "" ){
        if ( input.length() < 3 ) return;
        searched_items.clear();
        for ( int i=0; i<all_items->size();i++){
            if ( (*all_items)[i].search(input) ){
                searched_items.append(Item((*all_items)[i].id,(*all_items)[i].name,(*all_items)[i].category));
            }
        }
    }
    else searched_items = *all_items;
    refreshList();
}


