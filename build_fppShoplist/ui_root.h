/********************************************************************************
** Form generated from reading UI file 'root.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ROOT_H
#define UI_ROOT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_root
{
public:
    QAction *actionInsert;
    QAction *actionDelete;
    QAction *actionEdit;
    QAction *actionTransfer;
    QAction *actionRestore;
    QAction *actionImport_data_from_file;
    QAction *actionClear;
    QAction *actionShortcuts;
    QAction *actionAbout;
    QAction *actionSearch_Item;
    QAction *actionBackup;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QListView *listViewItemsInCart;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuList;
    QMenu *menuHelp;
    QToolBar *toolBar;

    void setupUi(QMainWindow *root)
    {
        if (root->objectName().isEmpty())
            root->setObjectName(QString::fromUtf8("root"));
        root->resize(1200, 800);
        root->setMinimumSize(QSize(800, 600));
        QFont font;
        font.setFamily(QString::fromUtf8("Ubuntu"));
        root->setFont(font);
        actionInsert = new QAction(root);
        actionInsert->setObjectName(QString::fromUtf8("actionInsert"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/resources/icons/plus-square.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionInsert->setIcon(icon);
        actionDelete = new QAction(root);
        actionDelete->setObjectName(QString::fromUtf8("actionDelete"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/resources/icons/x-square.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionDelete->setIcon(icon1);
        actionEdit = new QAction(root);
        actionEdit->setObjectName(QString::fromUtf8("actionEdit"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/resources/icons/pencil-square.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionEdit->setIcon(icon2);
        actionTransfer = new QAction(root);
        actionTransfer->setObjectName(QString::fromUtf8("actionTransfer"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/resources/icons/arrow-up-square.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionTransfer->setIcon(icon3);
        actionRestore = new QAction(root);
        actionRestore->setObjectName(QString::fromUtf8("actionRestore"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icons/resources/icons/arrow-clockwise.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionRestore->setIcon(icon4);
        QFont font1;
        actionRestore->setFont(font1);
        actionImport_data_from_file = new QAction(root);
        actionImport_data_from_file->setObjectName(QString::fromUtf8("actionImport_data_from_file"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/icons/resources/icons/file-earmark-arrow-down.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionImport_data_from_file->setIcon(icon5);
        actionImport_data_from_file->setFont(font1);
        actionClear = new QAction(root);
        actionClear->setObjectName(QString::fromUtf8("actionClear"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/icons/resources/icons/trash.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionClear->setIcon(icon6);
        actionClear->setFont(font1);
        actionShortcuts = new QAction(root);
        actionShortcuts->setObjectName(QString::fromUtf8("actionShortcuts"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/icons/resources/icons/keyboard.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionShortcuts->setIcon(icon7);
        actionShortcuts->setFont(font1);
        actionAbout = new QAction(root);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/icons/resources/icons/info-circle.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionAbout->setIcon(icon8);
        actionAbout->setFont(font1);
        actionSearch_Item = new QAction(root);
        actionSearch_Item->setObjectName(QString::fromUtf8("actionSearch_Item"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/icons/resources/icons/search.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionSearch_Item->setIcon(icon9);
        actionBackup = new QAction(root);
        actionBackup->setObjectName(QString::fromUtf8("actionBackup"));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/icons/resources/icons/download.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionBackup->setIcon(icon10);
        centralwidget = new QWidget(root);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        centralwidget->setMinimumSize(QSize(0, 0));
        centralwidget->setMaximumSize(QSize(16777215, 16777215));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        listViewItemsInCart = new QListView(centralwidget);
        listViewItemsInCart->setObjectName(QString::fromUtf8("listViewItemsInCart"));
        listViewItemsInCart->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Ignored, QSizePolicy::Ignored);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(listViewItemsInCart->sizePolicy().hasHeightForWidth());
        listViewItemsInCart->setSizePolicy(sizePolicy1);
        QFont font2;
        font2.setFamily(QString::fromUtf8("Monospace"));
        font2.setPointSize(13);
        font2.setStyleStrategy(QFont::PreferDefault);
        listViewItemsInCart->setFont(font2);
        listViewItemsInCart->setEditTriggers(QAbstractItemView::NoEditTriggers);

        horizontalLayout->addWidget(listViewItemsInCart);

        root->setCentralWidget(centralwidget);
        menubar = new QMenuBar(root);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1200, 22));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuList = new QMenu(menubar);
        menuList->setObjectName(QString::fromUtf8("menuList"));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        root->setMenuBar(menubar);
        toolBar = new QToolBar(root);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Ubuntu"));
        font3.setPointSize(11);
        toolBar->setFont(font3);
        toolBar->setMovable(true);
        root->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuList->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionImport_data_from_file);
        menuList->addAction(actionClear);
        menuList->addSeparator();
        menuList->addAction(actionBackup);
        menuList->addAction(actionRestore);
        menuHelp->addAction(actionShortcuts);
        menuHelp->addAction(actionAbout);
        toolBar->addAction(actionInsert);
        toolBar->addAction(actionEdit);
        toolBar->addAction(actionDelete);
        toolBar->addSeparator();
        toolBar->addAction(actionSearch_Item);
        toolBar->addSeparator();
        toolBar->addAction(actionTransfer);

        retranslateUi(root);

        QMetaObject::connectSlotsByName(root);
    } // setupUi

    void retranslateUi(QMainWindow *root)
    {
        root->setWindowTitle(QCoreApplication::translate("root", "root", nullptr));
        actionInsert->setText(QCoreApplication::translate("root", "Insert", nullptr));
#if QT_CONFIG(tooltip)
        actionInsert->setToolTip(QCoreApplication::translate("root", "Insert (Ins)", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionInsert->setShortcut(QCoreApplication::translate("root", "Ins", nullptr));
#endif // QT_CONFIG(shortcut)
        actionDelete->setText(QCoreApplication::translate("root", "Delete", nullptr));
#if QT_CONFIG(tooltip)
        actionDelete->setToolTip(QCoreApplication::translate("root", "Delete (Del)", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionDelete->setShortcut(QCoreApplication::translate("root", "Del", nullptr));
#endif // QT_CONFIG(shortcut)
        actionEdit->setText(QCoreApplication::translate("root", "Edit", nullptr));
#if QT_CONFIG(tooltip)
        actionEdit->setToolTip(QCoreApplication::translate("root", "Edit (Ctrl+E)", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionEdit->setShortcut(QCoreApplication::translate("root", "Ctrl+E", nullptr));
#endif // QT_CONFIG(shortcut)
        actionTransfer->setText(QCoreApplication::translate("root", "Transfer", nullptr));
#if QT_CONFIG(tooltip)
        actionTransfer->setToolTip(QCoreApplication::translate("root", "Transfer (Ctrl+T)", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionTransfer->setShortcut(QCoreApplication::translate("root", "Ctrl+T", nullptr));
#endif // QT_CONFIG(shortcut)
        actionRestore->setText(QCoreApplication::translate("root", "Restore", nullptr));
#if QT_CONFIG(shortcut)
        actionRestore->setShortcut(QCoreApplication::translate("root", "Ctrl+R", nullptr));
#endif // QT_CONFIG(shortcut)
        actionImport_data_from_file->setText(QCoreApplication::translate("root", "Import data from file", nullptr));
        actionClear->setText(QCoreApplication::translate("root", "Clear", nullptr));
#if QT_CONFIG(shortcut)
        actionClear->setShortcut(QCoreApplication::translate("root", "Ctrl+Del", nullptr));
#endif // QT_CONFIG(shortcut)
        actionShortcuts->setText(QCoreApplication::translate("root", "Shortcuts", nullptr));
        actionAbout->setText(QCoreApplication::translate("root", "About", nullptr));
        actionSearch_Item->setText(QCoreApplication::translate("root", "Search Item", nullptr));
#if QT_CONFIG(shortcut)
        actionSearch_Item->setShortcut(QCoreApplication::translate("root", "Ctrl+S", nullptr));
#endif // QT_CONFIG(shortcut)
        actionBackup->setText(QCoreApplication::translate("root", "Backup", nullptr));
        menuFile->setTitle(QCoreApplication::translate("root", "File", nullptr));
        menuList->setTitle(QCoreApplication::translate("root", "List", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("root", "Help", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("root", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class root: public Ui_root {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ROOT_H
