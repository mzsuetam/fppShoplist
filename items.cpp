#include <QString>
#include <QStringList>

#include "items.h"

////////////////////////////////////////////////

ItemInCart::ItemInCart( double _amount, QString _id, QString _name):amount(_amount),id(_id),name(_name){}

//////////////////////////////////////////////////

Item::Item(QString _id, QString _name):id(_id),name(_name),category(""){}
Item::Item(QString _id, QString _name, QString _category):id(_id),name(_name),category(_category){}
Item::Item(QString _id, QString _name, QString _category, QString _unit1, QString  _unit2, QString _price):id(_id),name(_name),category(_category),unit1(_unit1),unit2(_unit2),price(_price){}

bool Item::search(QString input) const{
  input = removeAccents(input);
  QStringList keys = input.toLower().split(" ");
  bool found = true;
  for (int i=0; i<keys.size(); i++){
      if ( !removeAccents(category).toLower().contains(keys[i])
           && !removeAccents(id).toLower().contains(keys[i])
           && !removeAccents(name).toLower().contains(keys[i]) )
         found = false;
  }
  return found;
}


QString Item::removeAccents(QString s) const {
    QStringList noDiacriticLetters_;

    //QString diacriticLetters_ = QString::fromUtf8("ŠŒŽšœžŸ¥µÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖØÙÚÛÜÝßàáâãäåæçèéêëìíîïðñòóôõöøùúûüýÿąĄćĆęĘłŁńŃóÓśŚźŹżŻ");
    //noDiacriticLetters_ << "S"<<"OE"<<"Z"<<"s"<<"oe"<<"z"<<"Y"<<"Y"<<"u"<<"A"<<"A"<<"A"<<"A"<<"A"<<"A"<<"AE"<<"C"<<"E"<<"E"<<"E"<<"E"<<"I"<<"I"<<"I"<<"I"<<"D"<<"N"<<"O"<<"O"<<"O"<<"O"<<"O"<<"O"<<"U"<<"U"<<"U"<<"U"<<"Y"<<"s"<<"a"<<"a"<<"a"<<"a"<<"a"<<"a"<<"ae"<<"c"<<"e"<<"e"<<"e"<<"e"<<"i"<<"i"<<"i"<<"i"<<"o"<<"n"<<"o"<<"o"<<"o"<<"o"<<"o"<<"o"<<"u"<<"u"<<"u"<<"u"<<"y"<<"y"<<"a"<<"A"<<"c"<<"C"<<"e"<<"E"<<"l"<<"L"<<"n"<<"N"<<"o"<<"O"<<"s"<<"S"<<"z"<<"Z"<<"z"<<"Z";

    QString diacriticLetters_ = QString::fromUtf8("ąĄćĆęĘłŁńŃóÓśŚźŹżŻ");
    noDiacriticLetters_ << "a"<<"A"<<"c"<<"C"<<"e"<<"E"<<"l"<<"L"<<"n"<<"N"<<"o"<<"O"<<"s"<<"S"<<"z"<<"Z"<<"z"<<"Z";

    QString output = "";
    for (int i = 0; i < s.length(); i++) {
        QChar c = s[i];
        int dIndex = diacriticLetters_.indexOf(c);
        if (dIndex < 0) {
            output.append(c);
        } else {
            QString replacement = noDiacriticLetters_[dIndex];
            output.append(replacement);
        }
    }

    return output;
}

//////////////////////////////////////////////////
