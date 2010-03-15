#include <qmath.h>
#include <math.h>
#include <stdio.h>
#include <iostream>
#include"sceneManager/pipeEntity.h"

#define PI 3.14159265


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

void PipeEntity::rotatePipe(QVector3D node1, QVector3D node2){

    //calculating the angle on a plan passing for 2 points

    //Plan xy

    double radians1;
    double degreesXY;
    if(node2.y()-node1.y() == 0){
        degreesXY = 0.0;
    }
    else{
        radians1 = atan((node2.x()-node1.x())/(node2.y()-node1.y()));
        degreesXY= radians1 *  180 / PI;
    }
    std::cout.precision(2);
    std::cout << "asse X:" << degreesXY << std::endl;



    //Plan zy
    double radians2;
    double degreesYZ;
    if(node2.z()-node1.z() == 0){
        degreesYZ= 0.0;
    }
    else{

        radians2 = atan((node2.y()-node1.y())/(node2.z()-node1.z()));
        degreesYZ = radians2 *  180 / PI;
    }
    std::cout.precision(2);
    std::cout << "asse Y:" << degreesYZ << std::endl;

    //Plan zx
    double radians3;
    double degreesZX;
    if(node2.x()-node1.x() == 0){
        degreesZX= 0.0;
    }
    else{

        radians3 = atan((node2.z()-node1.z())/(node2.x()-node1.x()));
        degreesZX = radians3 *  180 / PI;
    }
    std::cout.precision(2);
    std::cout << "asse Z:" << degreesZX << std::endl;




    rotate(degreesXY,QVector3D(1.0,0.0,0.0));
    rotate(degreesYZ,QVector3D(0.0,1.0,0.0));
    rotate(degreesZX,QVector3D(0.0,0.0,1.0));

}
