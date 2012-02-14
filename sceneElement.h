#ifndef SCENELEMENT_H
#define SCENELEMENT_H

#include <QObject>
#include <QColor>
#include <GL/glu.h>
#include <GL/gl.h>

#include<sceneManager/patch.h>
#include<sceneManager/nodeEntity.h>
#include<sceneManager/pipeEntity.h>

//test change git

class SceneElement : public QObject
{
    
public:
    SceneElement (QObject *parent, int d = 1, qreal s = 80.0);
    ~SceneElement();
    void setColor(QColor c);
    void draw() const;
private:
    void buildGeometry(int d, qreal s);

    QList<Patch *> parts;
    Geometry *geom;
};


#endif // SCENELEMENT_H
