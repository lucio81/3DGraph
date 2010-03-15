#ifndef PIPEENTITY_H
#define PIPEENTITY_H

#include<sceneManager/netEntity.h>
#include<sceneManager/nodeEntity.h>

class PipeEntity : public NetEntity{

public:
    PipeEntity(Geometry *g, qreal iRad, qreal oRad, qreal depth, int numSectors);
    void rotatePipe(QVector3D node1, QVector3D node2);
    void translatePipe(QVector3D node1, QVector3D node2);

};

#endif // PIPEENTITY_H
