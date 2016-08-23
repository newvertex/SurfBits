#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "Link.h"
#include <QList>

class QString;

class FileManager
{
public:
    FileManager();

    const QString writeToFile(const QString &fileName, QString &walletAddress, QList<Link> &links);
    const QString readFromFile(const QString &fileName, QString &walletAddress, QList<Link> &links);
};

#endif // FILEMANAGER_H
