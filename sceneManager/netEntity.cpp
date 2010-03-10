#include"sceneManager/netEntity.h"

void NetEntity :: translate(const QVector3D &t)
{
    for (int i = 0; i < parts.count(); ++i)
        parts[i]->translate(t);
}

void NetEntity :: rotate(qreal deg, QVector3D axis)
{
    for (int i = 0; i < parts.count(); ++i)
        parts[i]->rotate(deg, axis);
}
