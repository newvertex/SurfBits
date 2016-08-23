#ifndef READYMODEL_H
#define READYMODEL_H

#include <QAbstractListModel>
#include <QList>

#include "Link.h"

class ReadyModel: public QAbstractListModel
{
    Q_OBJECT
public:
    explicit ReadyModel(QObject *parent=0);
    virtual int rowCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;

    void addLinks(QList<Link> &links);
    QList<Link> &getLinks();

    void removeLink(int index);
    Link *getLink(int index);

    void checked(int index);

public slots:
    void addLink(const Link &link);

signals:
    void linkChecked(const Link &link);

private:
    QList<Link> mLinks;
};

#endif // READYMODEL_H
