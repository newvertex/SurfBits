#include "ReadyModel.h"

ReadyModel::ReadyModel(QObject *parent):
    QAbstractListModel(parent)
{

}

int ReadyModel::rowCount(const QModelIndex &parent) const
{
    return mLinks.size();
}

QVariant ReadyModel::data(const QModelIndex &index, int role) const
{
    if(role == Qt::DisplayRole) {
        return mLinks.at(index.row()).getTitle() + ": "+ QString::number(mLinks.at(index.row()).getClicks());
    }
    return QVariant::Invalid;
}

void ReadyModel::addLinks(QList<Link> &links)
{
    beginResetModel();
    mLinks = links;
    endResetModel();
}

QList<Link> &ReadyModel::getLinks()
{
    return mLinks;
}

void ReadyModel::addLink(const Link &link)
{
    beginResetModel();
    mLinks.append(link);
    endResetModel();
}

void ReadyModel::removeLink(int index)
{
    beginResetModel();
    mLinks.removeAt(index);
    endResetModel();
}

Link *ReadyModel::getLink(int index)
{
    return &mLinks[index];
}

void ReadyModel::checked(int index)
{
    beginResetModel();
    mLinks[index].addClicks();
    mLinks[index].resetTimer();

    emit linkChecked(mLinks.at(index));
    removeLink(index);
    endResetModel();
}
