#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QDebug>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QTimer>
#include <QtWebKitWidgets>
#include <QLabel>
#include <QInputDialog>
#include <QSoundEffect>
#include <QNetworkReply>
#include <QDesktopServices>
#include <QVariant>

#include "AddLinkDialog.h"

#include "AddressModel.h"
#include "PendingModel.h"
#include "ReadyModel.h"
#include "Link.h"
#include "FileManager.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    webView(new QWebView(this)),
    walletAddress(new QLabel()),
    sndLinkIsReady(new QSoundEffect()),
    addressModel(new AddressModel()),
    pendingModel(new PendingModel()),
    readyModel(new ReadyModel()),
    currentLink(nullptr)
{
    ui->setupUi(this);

    ui->addressListView->setModel(addressModel);
    ui->pendingListView->setModel(pendingModel);
    ui->readyListView->setModel(readyModel);

    QTimer *timer = new QTimer();
    connect(timer,&QTimer::timeout, pendingModel, &PendingModel::countDown);
    timer->start(1000);

    sndLinkIsReady->setSource(QUrl("qrc:/SndFX/Ding.wav"));

    connect(pendingModel, &PendingModel::linkIsReady, readyModel, &ReadyModel::addLink);
    connect(pendingModel, &PendingModel::linkIsReady, sndLinkIsReady, &QSoundEffect::play);

    connect(readyModel, &ReadyModel::linkChecked, pendingModel, &PendingModel::addLink);

    ui->vlWebPage->addWidget(webView);

    QNetworkProxyFactory::setUseSystemConfiguration(true);
    QWebSettings::globalSettings()->setAttribute(QWebSettings::PluginsEnabled, true);
    QWebSettings::globalSettings()->setAttribute(QWebSettings::AutoLoadImages, true);
    QWebSettings::globalSettings()->setAttribute(QWebSettings::JavascriptEnabled, true);
    loadWebPage();

    connect(webView, &QWebView::loadProgress, this, &MainWindow::updateLoadingBar);
    connect(webView->page()->networkAccessManager(), &QNetworkAccessManager::sslErrors, this, &MainWindow::handleSslErrors);

    ui->mainToolBar->addWidget(walletAddress);

    ui->toolBarViews->addAction(ui->dockLinksAddress->toggleViewAction());
    ui->toolBarViews->addAction(ui->dockPendingLinks->toggleViewAction());
    ui->toolBarViews->addAction(ui->dockReadyLinks->toggleViewAction());

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addNewLink(Link &link)
{
    addressModel->addLink(link);
}

void MainWindow::on_actionRun_triggered()
{
    readyModel->getLinks().clear();
    pendingModel->addLinks(addressModel->getLinks());
    ui->pendingListView->reset();
    ui->readyListView->reset();
}

void MainWindow::changeCurrentLink()
{
    if(!readyModel->getLinks().isEmpty())
    {
        if(currentLink != nullptr)
        {
            readyModel->checked(0);

            if(!readyModel->getLinks().isEmpty())
            {
                currentLink = readyModel->getLink(0);
            }else{
                currentLink = nullptr;
            }

        }else {
            currentLink = readyModel->getLink(0);

        }
    }else {
        currentLink = nullptr;
    }

    loadWebPage();
}

void MainWindow::loadWebPage()
{
    if(currentLink != nullptr)
        webView->load(QUrl(currentLink->getUrl()));
    else
        webView->load(QUrl("http://example.com"));

    updateAddressBar();
}

void MainWindow::on_btnCheckNextLink_clicked()
{
    changeCurrentLink();
}

void MainWindow::on_btnRemoveLinkFromPendingList_clicked()
{
    pendingModel->removeLink(ui->pendingListView->currentIndex().row());
}

void MainWindow::on_btnReload_clicked()
{
    webView->reload();
    updateAddressBar();
}

void MainWindow::on_btnRemoveLinkFromAddressList_clicked()
{
    addressModel->removeLink(ui->addressListView->currentIndex().row());
}

void MainWindow::on_btnAddLink_clicked()
{
    addLinkDialog = new AddLinkDialog(this, this);
    addLinkDialog->setModal(true);
    addLinkDialog->exec();
}

void MainWindow::updateAddressBar()
{
    ui->leAddressBar->setText(webView->url().toString());
}

void MainWindow::updateLoadingBar(int value)
{
    ui->pbLoading->setValue(value);
    updateAddressBar();
    if(value > 99)
        ui->leAddressBar->setEnabled(true);
    else
        ui->leAddressBar->setEnabled(false);
}

void MainWindow::on_actionSetWalletAddress_triggered()
{
    bool ok;
    QString result = QInputDialog::getText(this,"Set Wallet Address", "Enter Bitcoin Wallet Address:",QLineEdit::Normal, QString(), &ok);

    if(ok)
    {
        walletAddress->setText(result);
    }
}

void MainWindow::on_actionCopyWalletAddress_triggered()
{
    QApplication::clipboard()->setText(walletAddress->text());
}

void MainWindow::handleSslErrors(QNetworkReply* reply, const QList<QSslError> &errors)
{
    d("handleSslErrors: \n");
    foreach (QSslError e, errors)
    {
        d("ssl error: " + e.errorString() + "\n");
    }

    reply->ignoreSslErrors();
}

void MainWindow::on_pushButton_clicked()
{
    QDesktopServices::openUrl(QUrl(currentLink->getUrl()));
}

void MainWindow::d(QString value)
{
    ui->ptxtConsole->appendPlainText(value);
}

void MainWindow::on_actionLoad_triggered()
{
    addressModel->getLinks().clear();
    QString walletAdder;
    FileManager fm;
    d(fm.readFromFile(FILE_NAME, walletAdder, addressModel->getLinks()));
    walletAddress->setText(walletAdder);
    ui->addressListView->reset();
}

void MainWindow::on_actionSave_triggered()
{
    QString walletAdder = walletAddress->text();
    FileManager fm;
    d(fm.writeToFile(FILE_NAME, walletAdder, addressModel->getLinks()));
}

void MainWindow::on_actionNew_triggered()
{
    walletAddress->clear();
    addressModel->getLinks().clear();
    pendingModel->getLinks().clear();
    readyModel->getLinks().clear();
    ui->addressListView->reset();
    ui->pendingListView->reset();
    ui->readyListView->reset();
}
