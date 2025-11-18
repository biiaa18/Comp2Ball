#include "rollingball.h"

RollingBall::RollingBall() {}



float RollingBall::barysentriske(QVector2D vertx, float dt) //dt - delta time
{
    float ballX = vertx.x();
    float ballZ = vertx.y();
    //qDebug()<<"x : "<<ballX<<" y: "<< ballZ<<"\n";
    //float ballY = 0.f;

    for (size_t i = 0; i < triangle_surf->mIndices.size(); i += 3)
    {
        Vertex A = triangle_surf->mVertices[triangle_surf->mIndices[i]];
        Vertex B = triangle_surf->mVertices[triangle_surf->mIndices[i + 1]];
        Vertex C = triangle_surf->mVertices[triangle_surf->mIndices[i + 2]];
        //qDebug()<<"x "<<A.x<<" "<<B.x<<" "<<C.z<<" y:"<<A.z<<" "<<B.z<<" "<<C.z<<"\n";        //barycentric coordinates
        QVector2D AB=QVector2D{B.x-A.x, B.z-A.z};
        QVector2D AC=QVector2D{C.x-A.x, C.z-A.z};
        QVector2D AP=QVector2D{ballX-A.x, ballZ-A.z};
        float denominator = AB.x()*AC.y() -AB.y()*AC.x();   //CROSS PRODUCT OF AB, AC



        if (denominator == 0.0f)
        {
            continue;
        }


        // QVector3D PA=QVector3D{A.x-ballX, A.y-ballY, A.z-ballZ};
        // QVector3D PB=QVector3D{B.x-ballX, B.y-ballY, B.z-ballZ};
        // QVector3D PC=QVector3D{C.x-ballX, C.y-ballY, C.z-ballZ};


        // float lambda1 = (PB.x()*PC.z() -PB.z()*PC.x())/denominator;
        // float lambda2 = (PC.x()*PA.z() -PC.z()*PA.x())/denominator;
        // float lambda3 = (PA.x()*PB.z() -PA.z()*PB.x())/denominator;


        float lambda1 = (AP.x()*AC.y() -AC.x()*AP.y())/denominator;
        float lambda2 = (AB.x()*AP.y() -AB.y()*AP.x())/denominator;
        float lambda3 = 1.0f-lambda1-lambda2;


        if (lambda1 >= 0.f && lambda2 >= 0.f && lambda3 >= 0.f &&
            lambda1 <= 1.f && lambda2 <= 1.f && lambda3 <= 1.f)
        {

            PointsCount+=1;
            height=lambda1 * B.y + lambda2 * C.y + lambda3 * A.y+radius*1.1f;
            //break;

            //normal for the plane to calculate rotation and acceleration
            //normal vector of surface calculations
            QVector3D AB_=QVector3D{B.x-A.x, B.y-A.y, B.z-A.z};
            QVector3D AC_=QVector3D{C.x-A.x, C.y-A.y, C.z-A.z};
            QVector3D normal_v =QVector3D::crossProduct(AB_, AC_);    //CROSS PRODUCT OF AB, AC
            normal_v.normalize();

            //acceleration vector
            acceleration={g*normal_v.x()*normal_v.y(), g*normal_v.z()*normal_v.y(), g*(normal_v.y()*normal_v.y()-1)}; //height from the surface?

            //N works in the opposite direction of G
            // (G* n)*n - PROJECTION OF G on the surface normal, so it goes in the opposite direction of N
            //otherwise we can't sum it, need them to be in the same "axis" of local coordinate system
            // QVector3D Gn=QVector3D::dotProduct(G,normal_v)*normal_v;
            // //G and N "cancel" each other out, working in opposite direction
            // //have to be equal, so the ball doesnt fly off or "sink" into the ground
            // QVector3D N=-Gn; //comment
            // QVector3D F=N+G; //sum of all forces F=ma;
            // acceleration=F/mass;
            // acceleration.normalize();
            //update velocity and position
            velocity+=acceleration*dt; //v1=v0+a*dt
            position+=velocity*dt; //p1=p0+v*dt
            setPosition(getPosition().x()+position.x(), height, getPosition().z()+position.z());
            //setPosition(position.x(), height, position.z());

            //rotation
            rotation=QVector3D::crossProduct(normal_v,velocity)/radius;
            rotation.normalize();
            float degree=qRadiansToDegrees(position.length()/radius);//qRadiansToDegrees(rotation.length())*dt;
            //not sure why degree is inverted...
            rotate(degree, rotation.x(),rotation.y(), rotation.z());
            if(PointsCount>12 && PushCount<10){
                //push every 10th point
                ctrl_p_flate.push_back({getPosition().x(),getPosition().y(),getPosition().z()});
                PointsCount=0;
                PushCount+=1;
            }
            if(PushCount==10){//(PointsCount==11){
                isNotMoving=true;
                PushCount=11;
            }
            else{
                isNotMoving=false;
            }

            //qDebug()<<getPosition().x()<<" y: "<< getPosition().y()<<" "<< getPosition().z()<<"\n";
            break;
        }
        else{

                //qDebug("not inside triangle of  triangle_surf");
        }
    }

    return height;

};

RollingBall::RollingBall(TriangleSurface *surface) {
    triangle_surf = surface;
    //setPosition( -2.f, 3.f, 3.f);
    //setPosition( 2.f, 3.f, 2.f);
    //setPosition( -1.8f, 3.f, 3.7f); //most fun to look at
    setPosition( 3.9f, 2.f, 3.9f); //lowest point doesnt move anywhere
    //setPosition( 0.f, 2.f, 2.f); //in the middle
    //setPosition(-70.3f, 11.3f, 100.55f);
    //setPosition(90.3f, 11.3f, 70.55f);//wall collision right
    //setPosition(-10.3f, 11.3f, 30.55f);//wall collision left

};
