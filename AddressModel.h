#ifndef ADDRESSMODEL_H
#define ADDRESSMODEL_H

#include <QAbstractListModel>
#include <QList>

#include "Link.h"

class AddressModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit AddressModel(QObject *parent=0);
    virtual int rowCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;

    void addLinks(QList<Link> &links);
    QList<Link> &getLinks();

    void addLink(Link &link);
    void removeLink(int index);
    Link getLink(int index);

private:
    QList<Link> mLinks;

};

#endif // ADDRESSMODEL_H
