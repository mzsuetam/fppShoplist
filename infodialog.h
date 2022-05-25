#ifndef INFODIALOG_H
#define INFODIALOG_H

#include <QDialog>

#include "root.h"

namespace Ui {
class InfoDialog;
}

class InfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InfoDialog(QWidget *parent = nullptr);
    ~InfoDialog();

    void init(root *_root, QString mode);

private:
    Ui::InfoDialog *ui;
public:
    root* root_ptr;
};

#endif // INFODIALOG_H
