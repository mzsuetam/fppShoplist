#include "infodialog.h"
#include "ui_infodialog.h"

#include <QString>

InfoDialog::InfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InfoDialog)
{
    ui->setupUi(this);
}

InfoDialog::~InfoDialog()
{
    root_ptr->setEnabled(true);
    delete ui;
}


void InfoDialog::init(root *_root, QString mode){
    root_ptr = _root;
    QString text;

    if ( mode == "About" ){
        setWindowTitle("About");
        setWindowIcon(QIcon(":/icons/resources/icons/info-circle.svg"));

        text = "# FppShoplist \n _____\n"
               "## About: \n"
               "Version: " + root_ptr->getVer() + "\n\n"
               "Author: Mateusz Mazur \n"
               "#### Description: \n FppShoplist is an addition to FPP Firma++ and is intended to extend"
               "the basic functions of FPP to more computer stations. \n"
               "#### Usage: \n"
               "FppShoplist allows to operate on items menaged in FPP by impoprting FPP Export file \"CENNIK.CDN\". "
               "After the impot user has permament access to all items and their stats. "
               "Items can be simply searched or inserted into main list, as if a recipt or invoice were made. "
               "The list can be transfered via internet to FppShoplist server and inserted to real receipt or invoice in FPP Firma++. "
               "To transfer client must be connected to the host computer. "
               "To do that, turn on server application on host computer and then select Menu > Search for Host option in client application. "
               ;
    }
    else if ( mode == "Shortcuts" ){
        setWindowTitle("Shortcuts");
        setWindowIcon(QIcon(":/icons/resources/icons/keyboard.svg"));

        text = "# FppShoplist \n _____\n"
               "## Shortcuts: \n"
               "Ins - insert item to the list \n\n"
               "Del - delete selected item \n\n"
               "CTRL+E - edit selected item \n\n"
               "CTRL+T - transfer list \n\n"
               "CTRL+R - restore list form backup \n\n"
               "CTRL+Del - clear list \n\n"
               "CTRL+S - search item \n\n"
               ;
    }

    ui->textBrowser->setMarkdown(text);
}
