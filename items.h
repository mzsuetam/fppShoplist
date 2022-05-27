#ifndef ITEMS_H
#define ITEMS_H

#include <QString>
#include <QStringList>

//////////////////////////////////////////////////

struct ItemInCart{
  double amount;
  QString id;
  QString name;
  ItemInCart( double _amount, QString _id, QString _name);
};

//////////////////////////////////////////////////

struct Item{
  QString id;
  QString name;
  QString category;
  QString unit1;
  QString unit2;
  QString price;
  Item(QString _id, QString _name);
  Item(QString _id, QString _name, QString _category);
  Item(QString _id, QString _name, QString _category, QString _unit1, QString  _unit2, QString _price);

  bool search(QString input) const;

  QString removeAccents(QString input) const;

};

//////////////////////////////////////////////////

#endif // ITEMS_H
