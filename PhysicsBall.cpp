#include "TriangleSurface.h"

struct PhysicsBall{
    TriangleSurface* surf; //using barycentric
    //need to get normal vector from the suface for calculating acceleration vector
    QVector3D position;
    QVector3D velocity;
    QVector3D acceleration;
    double mass;
    double radius;
    void move();
    //v=v+a*dt;
    //p=p+v*dt;
};
