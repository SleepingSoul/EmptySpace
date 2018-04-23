#include "mediacache.h"
#include "QPixmapCache"
#include <QPixmap>
#include <cassert>
#include <QDebug>

MediaCache::MediaCache()
{
    QPixmapCache::setCacheLimit(40000);
    pic = new QPixmap();
    qDebug() << "loaded? " << pic->load("media/map_picture.jpg");
}

MediaCache::~MediaCache()
{
    QPixmapCache::clear();
}

QPixmap *MediaCache::getPicture(Pictures::Type type)
{
    qDebug() << pic->size();

    switch (type) {
    case Pictures::GameplayMap12000x12000:
        return pic;
    }
    assert("Invalid type.Fix this.");
}
