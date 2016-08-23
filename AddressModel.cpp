#include "AddressModel.h"

AddressModel::AddressModel(QObject *parent):
    QAbstractListModel(parent)
{

}

int AddressModel::rowCount(const QModelIndex &parent) const
{
    return mLinks.size();
}

QVariant AddressModel::data(const QModelIndex &index, int role) const
{
    if(role == Qt::DisplayRole) {
        return mLinks.at(index.row()).getTitle() + ": "+  QString::number(mLinks.at(index.row()).getTime());
    }
    return QVariant::Invalid;
}

void AddressModel::addLinks(QList<Link> &links)
{
    beginResetModel();
    mLinks = links;
    endResetModel();
}

QList<Link> &AddressModel::getLinks()
{
    return mLinks;
}

void AddressModel::addLink(Link &link)
{
    beginResetModel();
    mLinks.append(link);
    endResetModel();
}

void AddressModel::removeLink(int index)
{
    beginResetModel();
    mLinks.removeAt(index);
    endResetModel();
}

Link AddressModel::getLink(int index)
{
    return mLinks.at(index);
}
