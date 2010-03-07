#ifndef NODEENTITY_H
#define NODEENTITY_H

#include<sceneManager/netEntity.h>

class NodeEntity : public NetEntity{

public:
    NodeEntity(Geometry *g, qreal width, qreal height, qreal depth);

};

#endif // NODEENTITY_H
