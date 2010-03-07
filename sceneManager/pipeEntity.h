#ifndef PIPEENTITY_H
#define PIPEENTITY_H

#include<sceneManager/netEntity.h>

class PipeEntity : public NetEntity{

public:
    PipeEntity(Geometry *g, qreal iRad, qreal oRad, qreal depth, int numSectors);

};

#endif // PIPEENTITY_H
