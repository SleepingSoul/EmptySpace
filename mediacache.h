#ifndef MEDIACACHE_H
#define MEDIACACHE_H

#include "global_enumerations.h"

class QPixmapCache;
class QPixmap;

class MediaCache
{
public:
    MediaCache();
    ~MediaCache();

    QPixmap *getPicture(Pictures::Type);
    QPixmap *pic;
};

#endif // MEDIACACHE_H
