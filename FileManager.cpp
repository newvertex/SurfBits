#include "FileManager.h"

#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDebug>

FileManager::FileManager()
{

}

const QString FileManager::writeToFile(const QString &fileName, QString &walletAddress, QList<Link> &links)
{
    QFile file(fileName);
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        return "Could not open the file for read!";
    }

    QTextStream out(&file);

    out << walletAddress << "\n";

    for(Link link: links)
    {
        out << link.getTitle() << "," <<
               link.getUrl() << "," <<
               link.getTime() << "\n";
    }

    out.flush();
    file.flush();
    file.close();
    return "Write to " + fileName + " successfully";
}

const QString FileManager::readFromFile(const QString &fileName, QString &walletAddress, QList<Link> &links)
{
    QFile file(fileName);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        return "Could not open the file for read!";
    }

    QTextStream in(&file);

    walletAddress = in.readLine();

    while(!in.atEnd())
    {
        QString line;
        in.readLineInto(&line);
        QStringList linkLine = line.split(",");
        Link link(linkLine.at(0), linkLine.at(1), linkLine.at(2).toInt());
        links.append(link);
    }
   return "Read from " + fileName + " successfully";
}
