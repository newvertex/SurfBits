#include "Link.h"

Link::Link(const QString &title, const QString &url, int time, int deltaTime, int clicks):
    title(title), url(url),time(time), deltaTime(deltaTime), clicks(clicks)
{
}

QString Link::getTitle() const
{
    return title;
}

void Link::setTitle(const QString &value)
{
    this->title = value;
}

QString Link::getUrl() const
{
    return url;
}

void Link::setUrl(const QString &value)
{
    this->url = value;
}

int Link::getTime() const
{
    return time;
}

void Link::setTime(int value)
{
    this->time = value;
}

int Link::getDeltaTime() const
{
    return deltaTime;
}

void Link::resetTimer()
{
    deltaTime = time;
}

int Link::countDown()
{
    return --deltaTime;
}

int Link::getClicks() const
{
    return clicks;
}

int Link::addClicks(int value)
{
    return (this->clicks += value);
}

