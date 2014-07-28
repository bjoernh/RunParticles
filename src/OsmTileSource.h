/*
 *  OsmTileSource.h
 *  RunParticles
 *
 *  Created by Doug Letterman on 6/30/14.
 *  Copyright 2014 Doug Letterman. All rights reserved.
 *
 */

#ifndef OSMTILESOURCE_H
#define OSMTILESOURCE_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

#include "Singleton.h"

#include "boost/shared_ptr.hpp"

#include "cinder/Surface.h"
#include "math.h"
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>

typedef std::shared_ptr<cinder::Surface8u> Surface8uRef;
typedef std::weak_ptr<cinder::Surface8u> Surface8uPtr;

struct OsmIndex {
    
    OsmIndex() : x(0), y(0), z(0) {};
    
    OsmIndex(unsigned int x, unsigned int y, unsigned int z)
    : x(x), y(y), z(z) {};
    
    unsigned int x, y, z;
    
    std::size_t hash() const {
        unsigned long offset = 0;
        for (unsigned int i=1; i < this->z; i++) {
            offset += pow(2, 2*i);
        }
        int edge = pow(2, this->z);
        return std::size_t(offset + this->x * edge + this->y);
    }
    
    bool operator==(const OsmIndex other) const {
        return hash() == other.hash();
    }
    
    bool operator<(const OsmIndex other) const {
        return hash() < other.hash();
    }
};

template<typename T>
struct OsmHasher
{
    std::size_t operator()(const T& t) const
    {
        return t.hash();
    }
};

typedef std::unordered_set<OsmIndex, OsmHasher<OsmIndex>> OsmIndexSet;

class OsmTileSource : public QObject
{
    Q_OBJECT
    
    struct OsmTile {
        OsmTile() { };
        OsmTile(OsmIndex idx, cinder::Surface *surf)
            : index(idx), surface(surf) {};
        
        OsmIndex index;
        Surface8uRef surface;
    };
    
    const QByteArray DEFAULT_USER_AGENT = "RunParticles";
    
    typedef std::shared_ptr<OsmTile*> OsmTileRef;
    
    typedef std::unordered_map<OsmIndex, OsmTile, OsmHasher<OsmIndex>>
        OsmTileMap;
    
    typedef std::map<time_t, OsmIndex> OsmTileTimeMap;
    
    typedef QMap<QNetworkReply*, OsmIndex> OsmReplyMap;
    
public:
    
    enum {
        memCacheSize = 128
    };
    
    void getTile(unsigned int x, unsigned int y, unsigned int z);
    
    cinder::Surface8u& retrieveFinishedTile(unsigned int x,
                                      unsigned int y,
                                      unsigned int z);
    
signals:
    
    void tileReady(unsigned int x, unsigned int y, unsigned int z);
    
public slots:
    
    void onRequestFinished();
    
protected:
    
    void _requestTile(const OsmIndex index);
    
    OsmTileMap _memoryTileCache;
    
    OsmTileTimeMap _memoryTileHistory;
    
    OsmIndexSet _pendingRequests;
    
    OsmReplyMap _pendingReplies;
    
};

#endif