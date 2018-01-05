#include "mediacache.h"
#include "QPixmapCache"
#include <QPixmap>
#include <cassert>
#include <QDebug>

MediaCache::MediaCache()
{
    QPixmapCache::setCacheLimit(40000);
    pic = new QPixmap("map_picture.jpg");
}

MediaCache::~MediaCache()
{
    QPixmapCache::clear();
}

QPixmap *MediaCache::getPicture(Pictures::Type type)
{
    QPixmap *pix = new QPixmap;

    switch (type) {
    case Pictures::GameplayMap12000x12000:
//        if (!QPixmapCache::find(QString("$gpl_mp"), pix)) {
//            qDebug() << "Hello there!";
//            pix->load("map_picture.jpg");
//            QPixmapCache::insert(QString("$gpl_mp"), *pix);
//        }
//        qDebug() << "Another happy landing!";
//        return pix;
        return pic;
    }
    assert("Invalid type.Fix this.");
}
