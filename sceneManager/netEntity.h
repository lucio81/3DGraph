#ifndef NETENTITY_H
#define NETENTITY_H

#include<QList>
#include<sceneManager/patch.h>

class NetEntity{

public:
    void translate(const QVector3D &t);
    void rotate(qreal deg, QVector3D axis);
    // No special Rectoid destructor - the parts are fetched out of this member
    // variable, and destroyed by the new owner
    QList<Patch*> parts;
};


#endif // NETENTITY_H
