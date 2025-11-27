#ifndef ROLLINGBALL_H
#define ROLLINGBALL_H
#include "TriangleSurface.h"
#include "oktaederclass.h"
#include "quadraticspline.h"


class RollingBall: public oktaederClass
{
public:
    RollingBall();
    RollingBall(TriangleSurface *surface);
    TriangleSurface* triangle_surf; //using barycentric
    //need to get normal vector from the suface for calculating acceleration vector
    // QVector3D position{0.f,0.f,0.f};//{40.3f, 11.3f, 50.55f};
    // QVector3D velocity={0.f, 0.f, 0.f};
    QVector3D acceleration{0.f,0.f,0.f};
    QVector3D rotation{0.f,0.f,0.f};
    float mass=0.1;
    // float radius=0.1;//1
    const float g=9.81;
    QVector3D G={0.f,-mass*g,0.f};
    //move
    float barysentriske(QVector2D vertx, float dt) override;
    float height;

    int old_index=-1;
    int new_index=0;
    QVector3D old_normal;
    QVector3D collision_vector;
    int PointsCount{0};
    float dtime{0};


    float previous_velocity;
    wall* static_wall= new wall();
    QVector3D wall_normal=static_wall->normal;
    float current_d =0;
    float wallDistance;
    bool wall_distance_static=false;
};


#endif // ROLLINGBALL_H
