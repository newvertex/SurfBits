#ifndef LINK_H
#define LINK_H

#include <QString>

class Link
{
private:
    QString title;
    QString url;
    int time;
    int deltaTime;
    int clicks;

public:
    Link(const QString &title="NoTitle", const QString &url="http://example.com", int time=0, int deltaTime=0, int clicks=0);

    QString getTitle() const;
    void setTitle(const QString &value);

    QString getUrl() const;
    void setUrl(const QString &value);

    int getTime() const;
    void setTime(int value);

    int getDeltaTime() const;

    void resetTimer();
    int countDown();

    int getClicks() const;
    int addClicks(int value=1);

};
#endif // LINK_H
