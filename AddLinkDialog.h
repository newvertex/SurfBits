#ifndef ADDLINKDIALOG_H
#define ADDLINKDIALOG_H

#include <QDialog>

class MainWindow;
class Link;

namespace Ui {
    class AddLinkDialog;
}

class AddLinkDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddLinkDialog(QWidget *parent = 0, MainWindow *mainWindow = 0);
    ~AddLinkDialog();

signals:
    void addNewLink(Link &link);

private slots:
    void on_btnOk_clicked();

    void on_btnCancel_clicked();

private:
    Ui::AddLinkDialog *ui;
};

#endif // ADDLINKDIALOG_H
