#ifndef ADDOBJECTDIALOG_H
#define ADDOBJECTDIALOG_H

#include <QDialog>
#include <QTimer>
//#include <opencv2/features2d/features2d.hpp>
//#include <opencv2/core/core.hpp>

namespace Ui {
class AddObjectDialog;
}

class AddObjectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddObjectDialog(QWidget *parent = 0);
    ~AddObjectDialog();

private slots:
    void on_addObjectButton_clicked();

private:
    Ui::AddObjectDialog *ui;
};

#endif // ADDOBJECTDIALOG_H
