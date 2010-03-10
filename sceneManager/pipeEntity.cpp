#include <qmath.h>
#include"sceneManager/pipeEntity.h"


static inline QVector<QVector3D> extrude(const QVector<QVector3D> &verts, qreal depth)
{
    QVector<QVector3D> extr = verts;
    for (int v = 0; v < extr.count(); ++v)
        extr[v].setZ(extr[v].z() - depth);
    return extr;
};


PipeEntity::PipeEntity(Geometry *g, qreal iRad, qreal oRad, qreal depth, int numSectors){
    QVector<QVector3D> inside;
    QVector<QVector3D> outside;
    for (int i = 0; i < numSectors; ++i) {
        qreal angle = (i * 2 * M_PI) / numSectors;
        inside << QVector3D(iRad * qSin(angle), iRad * qCos(angle), depth / 2.0);
        outside << QVector3D(oRad * qSin(angle), oRad * qCos(angle), depth / 2.0);
    }
    inside << QVector3D(0.0, iRad, 0.0);
    outside << QVector3D(0.0, oRad, 0.0);
    QVector<QVector3D> in_back = extrude(inside, depth);
    QVector<QVector3D> out_back = extrude(outside, depth);

    
    // Create front, back and sides as seperate patches so that smooth normals
    // are generated for the curving sides, but a faceted edge is created between
    // sides and front/back
    Patch *front = new Patch(g);
    for (int i = 0; i < numSectors; ++i)
        front->addQuad(outside[i], inside[i],
                       inside[(i + 1) % numSectors], outside[(i + 1) % numSectors]);
    Patch *back = new Patch(g);
    for (int i = 0; i < numSectors; ++i)
        back->addQuad(in_back[i], out_back[i],
                      out_back[(i + 1) % numSectors], in_back[(i + 1) % numSectors]);
    Patch *is = new Patch(g);
    for (int i = 0; i < numSectors; ++i)
        is->addQuad(in_back[i], in_back[(i + 1) % numSectors],
                    inside[(i + 1) % numSectors], inside[i]);
    Patch *os = new Patch(g);
    for (int i = 0; i < numSectors; ++i)
        os->addQuad(out_back[(i + 1) % numSectors], out_back[i],
                    outside[i], outside[(i + 1) % numSectors]);
    parts << front << back << is << os;
}
