#include "AddLinkDialog.h"
#include "ui_AddLinkDialog.h"

#include <QStringList>
#include <QString>

#include "MainWindow.h"
#include "Link.h"

AddLinkDialog::AddLinkDialog(QWidget *parent, MainWindow *mainWindow) :
    QDialog(parent),
    ui(new Ui::AddLinkDialog)
{
    ui->setupUi(this);
    connect(this, &AddLinkDialog::addNewLink, mainWindow, &MainWindow::addNewLink);
}

AddLinkDialog::~AddLinkDialog()
{
    delete ui;
}

void AddLinkDialog::on_btnOk_clicked()
{
    const QString title = ui->leTitle->text();
    const QString url = ui->leUrl->text();
    QStringList timeString = ui->leTime->text().split(".");

    int timeInSecond = (timeString.at(0).toInt() * 60);

    if(timeString.size() > 1)
        timeInSecond += timeString.at(1).toInt();


    Link link(title, url, timeInSecond);
    emit addNewLink(link);

    this->close();
}

void AddLinkDialog::on_btnCancel_clicked()
{
    this->close();
}
