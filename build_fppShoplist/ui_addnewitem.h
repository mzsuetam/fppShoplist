/********************************************************************************
** Form generated from reading UI file 'addnewitem.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDNEWITEM_H
#define UI_ADDNEWITEM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListView>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_addNewItem
{
public:
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QPlainTextEdit *inputID;
    QPlainTextEdit *inputAmount;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButtonOk;
    QPushButton *pushButtonCancel;
    QListView *listViewItems;

    void setupUi(QDialog *addNewItem)
    {
        if (addNewItem->objectName().isEmpty())
            addNewItem->setObjectName(QString::fromUtf8("addNewItem"));
        addNewItem->resize(1000, 600);
        horizontalLayout = new QHBoxLayout(addNewItem);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        inputID = new QPlainTextEdit(addNewItem);
        inputID->setObjectName(QString::fromUtf8("inputID"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(inputID->sizePolicy().hasHeightForWidth());
        inputID->setSizePolicy(sizePolicy);
        inputID->setMaximumSize(QSize(200, 28));
        inputID->setInputMethodHints(Qt::ImhNone);
        inputID->setTabChangesFocus(true);
        inputID->setLineWrapMode(QPlainTextEdit::NoWrap);
        inputID->setTabStopWidth(80);
        inputID->setTabStopDistance(80.000000000000000);
        inputID->setMaximumBlockCount(1);

        verticalLayout->addWidget(inputID);

        inputAmount = new QPlainTextEdit(addNewItem);
        inputAmount->setObjectName(QString::fromUtf8("inputAmount"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(inputAmount->sizePolicy().hasHeightForWidth());
        inputAmount->setSizePolicy(sizePolicy1);
        inputAmount->setMaximumSize(QSize(200, 28));
        inputAmount->setSizeIncrement(QSize(0, 0));
        inputAmount->setInputMethodHints(Qt::ImhPreferNumbers);
        inputAmount->setTabChangesFocus(true);
        inputAmount->setLineWrapMode(QPlainTextEdit::NoWrap);
        inputAmount->setTabStopWidth(80);
        inputAmount->setTabStopDistance(80.000000000000000);
        inputAmount->setMaximumBlockCount(1);

        verticalLayout->addWidget(inputAmount);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        pushButtonOk = new QPushButton(addNewItem);
        pushButtonOk->setObjectName(QString::fromUtf8("pushButtonOk"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/resources/icons/check-circle.svg"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonOk->setIcon(icon);

        horizontalLayout_2->addWidget(pushButtonOk);

        pushButtonCancel = new QPushButton(addNewItem);
        pushButtonCancel->setObjectName(QString::fromUtf8("pushButtonCancel"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/resources/icons/x-circle.svg"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonCancel->setIcon(icon1);

        horizontalLayout_2->addWidget(pushButtonCancel);


        verticalLayout->addLayout(horizontalLayout_2);


        horizontalLayout->addLayout(verticalLayout);

        listViewItems = new QListView(addNewItem);
        listViewItems->setObjectName(QString::fromUtf8("listViewItems"));
        listViewItems->setMinimumSize(QSize(400, 0));
        QFont font;
        font.setFamily(QString::fromUtf8("FreeMono"));
        font.setPointSize(16);
        listViewItems->setFont(font);
        listViewItems->setEditTriggers(QAbstractItemView::NoEditTriggers);

        horizontalLayout->addWidget(listViewItems);


        retranslateUi(addNewItem);

        QMetaObject::connectSlotsByName(addNewItem);
    } // setupUi

    void retranslateUi(QDialog *addNewItem)
    {
        addNewItem->setWindowTitle(QCoreApplication::translate("addNewItem", "Dialog", nullptr));
        inputID->setPlaceholderText(QCoreApplication::translate("addNewItem", "ID", nullptr));
        inputAmount->setPlaceholderText(QCoreApplication::translate("addNewItem", "Amount", nullptr));
        pushButtonOk->setText(QCoreApplication::translate("addNewItem", "OK", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("addNewItem", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class addNewItem: public Ui_addNewItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDNEWITEM_H
