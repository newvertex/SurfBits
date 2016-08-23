#include "PendingModel.h"

PendingModel::PendingModel(QObject *parent):
    QAbstractListModel(parent)
{

}

int PendingModel::rowCount(const QModelIndex &parent) const
{
    return mLinks.size();
}

QVariant PendingModel::data(const QModelIndex &index, int role) const
{
    if(role == Qt::DisplayRole) {
        return mLinks.at(index.row()).getTitle()+": "+ QString::number(mLinks.at(index.row()).getDeltaTime());
    }
    return QVariant::Invalid;
}

void PendingModel::addLinks(QList<Link> &links)
{
    beginResetModel();
    mLinks = links;
    endResetModel();
}

QList<Link> &PendingModel::getLinks()
{
    return mLinks;
}

void PendingModel::addLink(const Link &link)
{
    beginResetModel();
    mLinks.append(link);
    endResetModel();
}

void PendingModel::removeLink(int index)
{
    beginResetModel();
    mLinks.removeAt(index);
    endResetModel();
}

Link PendingModel::getLink(int index)
{
    return mLinks.at(index);
}

void PendingModel::countDown()
{
    beginResetModel();
    for(int i=0; i<mLinks.size(); i++)
    {
        if(mLinks[i].countDown() < 0)
        {
            emit linkIsReady(mLinks.at(i));
            removeLink(i);
        }
    }
    endResetModel();
}
