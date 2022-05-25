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
  Item(QString _id, QString _name);
  Item(QString _id, QString _name, QString _category);

  bool search(QString input) const;

  QString removeAccents(QString input) const;

};

//////////////////////////////////////////////////

#endif // ITEMS_H
