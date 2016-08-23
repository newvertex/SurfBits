#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSslError>

class AddLinkDialog;
class QWebView;
class QLabel;
class QSoundEffect;
class QNetworkReply;
class QVariant;

class AddressModel;
class PendingModel;
class ReadyModel;
class Link;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void addNewLink(Link &link);

private slots:
    void on_actionRun_triggered();

    void on_btnCheckNextLink_clicked();

    void on_btnRemoveLinkFromPendingList_clicked();

    void on_btnReload_clicked();

    void on_btnRemoveLinkFromAddressList_clicked();

    void on_btnAddLink_clicked();

    void on_actionSetWalletAddress_triggered();

    void on_actionCopyWalletAddress_triggered();

    void updateAddressBar();
    void updateLoadingBar(int value);
    void handleSslErrors(QNetworkReply* reply, const QList<QSslError> &errors);

    void on_pushButton_clicked();

    void on_actionLoad_triggered();

    void on_actionSave_triggered();

    void on_actionNew_triggered();

private:
    Ui::MainWindow *ui;
    AddLinkDialog *addLinkDialog;
    QWebView *webView;
    QLabel *walletAddress;
    QSoundEffect *sndLinkIsReady;

    AddressModel *addressModel;
    PendingModel *pendingModel;
    ReadyModel *readyModel;
    Link *currentLink;

    void changeCurrentLink();
    void loadWebPage();
    void d(QString value);

    const QString FILE_NAME = "mylinks.svb";
};

#endif // MAINWINDOW_H
