#ifndef ITEMS_H
#define ITEMS_H

#include <QString>
#include <QStringList>

//////////////////////////////////////////////////

class Item{
protected:
  QString id;
  QString name;
  QString category;
  QString unit1;
  QString unit2;
  QString price;
public:
  Item(){}
  //Item(QString _id, QString _name);
  //Item(QString _id, QString _name, QString _category);
  Item(QString _id, QString _name, QString _category, QString _unit1, QString  _unit2, QString _price);
  ~Item(){}

  QString getId() const {return id;}
  QString getName() const {return name;}
  QString getCategory() const {return category;}
  QString getUnit1() const {return unit1;}
  QString getUnit2() const {return unit2;}
  QString getPrice() const {return price;}

  bool search(QString input) const;

  QString removeAccents(QString input) const;

};

//////////////////////////////////////////////////

class ItemInCart : public Item{
protected:
  double amount;
public:
  //ItemInCart( double _amount, QString _id, QString _name);
  ItemInCart(double _amount, QString _id, QString _name, QString _unit1, QString  _unit2, QString _price);
  ~ItemInCart(){}

  double getAmount() const {return amount;}
};

//////////////////////////////////////////////////

#endif // ITEMS_H
