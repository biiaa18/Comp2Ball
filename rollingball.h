#ifndef ROLLINGBALL_H
#define ROLLINGBALL_H
#include "TriangleSurface.h"
#include "oktaederclass.h"
class RollingBall: public oktaederClass
{
public:
    RollingBall();
    RollingBall(TriangleSurface *surface);
    TriangleSurface* triangle_surf; //using barycentric
    //need to get normal vector from the suface for calculating acceleration vector
    QVector3D position;
    QVector3D velocity={0.f, 0.f, 0.f};
    QVector3D acceleration;
    QVector3D rotation;
    float mass=0.1;
    float radius=0.1;
    const float g=9.81;
    QVector3D G={0.f,-mass*g,0.f};
    //move
    float barysentriske(QVector2D vertx, float dt) override;
    float height;
};


#endif // ROLLINGBALL_H
