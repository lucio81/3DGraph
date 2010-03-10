#include<sceneElement.h>


static const qreal tee_height = 0.5;
static const qreal cross_width = 0.02;
static const qreal bar_thickness = 0.02;
static const qreal logo_depth = 0.02;

SceneElement::SceneElement(QObject *parent, int divisions, qreal scale)
    : QObject(parent)
    , geom(new Geometry())
{
    buildGeometry(divisions, scale);
}

SceneElement::~SceneElement()
{
    qDeleteAll(parts);
    delete geom;
}

void SceneElement::setColor(QColor c)
{
    for (int i = 0; i < parts.count(); ++i)
        parts[i]->qSetColor(parts[i]->faceColor, c);
}

//! [3]
void SceneElement::buildGeometry(int divisions, qreal scale)
{
    qreal cw = cross_width;
    qreal bt = bar_thickness;
    qreal ld = logo_depth;
    //qreal th = tee_height;


    NodeEntity node1(geom, cw, bt, ld);
    NodeEntity node2(geom, cw, bt, ld);
    NodeEntity node3(geom, cw, bt, ld);


    //RectPrism stem(geom, bt, th, ld);
    //RectPrism cross1(geom, cw+3, bt+3, ld+3);
    //RectPrism stem1(geom, bt+4, th+4, ld+4);
    //RectPrism cross2(geom, cw+5, bt+5, ld+5);
    //RectPrism stem2(geom, bt+6, th+6, ld+6);
    //RectPrism cross3(geom, cw+7, bt+7, ld+7);
    //RectPrism stem3(geom, bt, th, ld);
    //RectPrism stem_prova(geom,32,30,2);

    //QVector3D z(0.0, 1.0, 0.0);
    //cross.rotate(0.0, z);
    //stem.rotate(0.0, z);
    //stem_prova.rotate(0.0, z);

    //qreal stem_downshift =  (th + bt);
    //stem.translate(QVector3D(0.0, -stem_downshift, 0.0));
    node1.translate(QVector3D(0.1, 0.2, 0.0));
    //node2.translate(QVector3D(0.06, 0.4, 0.5));
    //node3.translate(QVector3D(0.01, 0.4, -0.5));


    PipeEntity body(geom, 0.005, 0.01, 0.3, 20);
    body.translate(QVector3D(0.1, 0.2, 0.05));

    parts << body.parts << node1.parts ;//<< node2.parts << node3.parts << body.parts; << stem.parts

    geom->finalize();
}
//! [3]

//! [4]
void SceneElement::draw() const
{
    geom->loadArrays();

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    for (int i = 0; i < parts.count(); ++i)
        parts[i]->draw();

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
}
//! [4]
