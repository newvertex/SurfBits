#ifndef PENDINGMODEL_H
#define PENDINGMODEL_H

#include <QAbstractListModel>
#include <QList>

#include "Link.h"

class PendingModel: public QAbstractListModel
{
    Q_OBJECT
public:
    explicit PendingModel(QObject *parent=0);
    virtual int rowCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;

    void addLinks(QList<Link> &links);
    QList<Link> &getLinks();

    void removeLink(int index);
    Link getLink(int index);

    void countDown();

public slots:
    void addLink(const Link &link);

signals:
    void linkIsReady(const Link &link);

private:
    QList<Link> mLinks;
};

#endif // PENDINGMODEL_H
