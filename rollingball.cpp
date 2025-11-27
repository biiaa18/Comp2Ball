#include "rollingball.h"

RollingBall::RollingBall() {}



float RollingBall::barysentriske(QVector2D vertx, float dt) //dt - delta time
{
    float ballX = vertx.x();
    float ballZ = vertx.y();
    //qDebug()<<"x : "<<ballX<<" y: "<< ballZ<<"\n";
    for (size_t i = 0; i < triangle_surf->mIndices.size(); i += 3)
    {
        Vertex A = triangle_surf->mVertices[triangle_surf->mIndices[i]];
        Vertex B = triangle_surf->mVertices[triangle_surf->mIndices[i + 1]];
        Vertex C = triangle_surf->mVertices[triangle_surf->mIndices[i + 2]];
        //qDebug()<<"A ("<<A.x<<" "<<A.z<<" )   B ("<<B.x<<" "<<B.z<<")   C ("<<C.x<<" "<<C.z<<")\n";        //barycentric coordinates
        QVector2D AB=QVector2D{B.x-A.x, B.z-A.z};
        QVector2D AC=QVector2D{C.x-A.x, C.z-A.z};
        QVector2D AP=QVector2D{ballX-A.x, ballZ-A.z};
        float denominator = AB.x()*AC.y() -AB.y()*AC.x();   //CROSS PRODUCT OF AB, AC
        if (denominator == 0.0f)
        {
            continue;
        }
        float lambda1 = (AP.x()*AC.y() -AC.x()*AP.y())/denominator;
        float lambda2 = (AB.x()*AP.y() -AB.y()*AP.x())/denominator;
        float lambda3 = 1.0f-lambda1-lambda2;
        if (lambda1 >= 0.f && lambda2 >= 0.f && lambda3 >= 0.f &&
            lambda1 <= 1.f && lambda2 <= 1.f && lambda3 <= 1.f)
        {
            new_index=i;
            PointsCount+=1;
            height=lambda1 * B.y + lambda2 * C.y + lambda3 * A.y+radius*1.1f;
            //break;

            //normal for the plane to calculate rotation and acceleration
            //normal vector of surface calculations
            QVector3D AB_=QVector3D{B.x-A.x, B.y-A.y, B.z-A.z};
            QVector3D AC_=QVector3D{C.x-A.x, C.y-A.y, C.z-A.z};
            QVector3D normal_v =QVector3D::crossProduct(AB_, AC_);    //CROSS PRODUCT OF AB, AC TO FIND NORMAL VECTOR
            normal_v.normalize();
            old_normal=normal_v.normalized();
            acceleration={g*normal_v.x()*normal_v.y(), g*normal_v.z()*normal_v.y(), g*(normal_v.y()*normal_v.y()-1)}; //9.14
            //qDebug()<<"normal vector "<<normal_v.x()<<" "<<normal_v.y()<<" "<<normal_v.z()<<" \n";


            if(new_index!=old_index){
                QVector3D new_n=normal_v.normalized();
                if((new_n + old_normal).lengthSquared()<0.0001){ //avoid denominator be 0 when calculating collision vector
                    collision_vector=new_n;
                }
                else{
                    collision_vector=(new_n + old_normal)/(new_n + old_normal).lengthSquared();
                }

                velocity-=QVector3D::dotProduct(velocity,collision_vector)*collision_vector; //9.9
                position+=velocity*dt; //p1=p0+v*dt      9.17
                setPosition(getPosition().x()+position.x(), height, getPosition().z()+position.z());
                old_index=new_index;
            }

            old_normal=normal_v.normalized();

            // qDebug()<<"acceleration "<<acceleration.x()<<" "<<acceleration.y()<<" "<<acceleration.z()<<" \n";

            //ACCELERATION WITH FORCES
            //N works in the opposite direction of G
            // (G* n)*n - PROJECTION OF G on the surface normal, so it goes in the opposite direction of N
            //otherwise we can't sum it, need them to be in the same "axis" of local coordinate system
            // QVector3D Gn=QVector3D::dotProduct(G,normal_v)*normal_v;
            // //G and N "cancel" each other out, working in opposite direction
            // //have to be equal, so the ball doesnt fly off or "sink" into the ground
            // QVector3D N=-Gn;
            // //QVector3D R
            // //QVector3D Ff=friction*N;
            // QVector3D F=N+G; //+Ff; //sum of all forces F=ma;
            // acceleration=F/mass;
            // qDebug()<<"acceleration with forces "<<a.x()<<" "<<a.y()<<" "<<a.z()<<" \n";



            //update velocity and position
            float previous_velocity=velocity.length(); //need this to compare to updated velocity to define that ball has stopped moving.
            velocity+=acceleration*dt; //v1=v0+a*dt  9.16
            position+=velocity*dt; //p1=p0+v*dt      9.17
            setPosition(getPosition().x()+position.x(), height, getPosition().z()+position.z());
            //qDebug()<<getPosition().x()<<" y: "<< getPosition().y()<<" "<< getPosition().z()<<"\n";

            //rotation
            rotation=QVector3D::crossProduct(normal_v,velocity);//radius; //9.11 (added radius so match the ball size)
            //rotation.normalize();
            float degree=qRadiansToDegrees(position.length()/radius);//position is translation and angle= based on 9.10
            rotate(degree, rotation.x(),rotation.y(), -rotation.z());

            //check if ball stopped moving for drawing b spline track
            if(PointsCount>50 && velocity.length()!=previous_velocity && !isFinishedMoving){
                //push every 10th point
                if(madeBSpline){
                    ctrl_p_flate.clear();
                    PointsCount=0;
                    dtime=0.0f; //for redrawing b splines for fluid
                    qDebug()<<ctrl_p_flate.size();
                }
                else{
                    ctrl_p_flate.push_back({getPosition().x()-radius,getPosition().y(),getPosition().z()-radius});
                    PointsCount=0;
                }

                //qDebug()<<velocity.length()<<" "<<previous_velocity<<"\n";
            }
            if(!isFinishedMoving){
                if (fabs(velocity.length()-previous_velocity)<0.0001 || velocity.length()==previous_velocity){
                    dtime+=dt;
                    //qDebug()<<dtime<< " time and index "<<i;
                    if(dtime>1.3f){ //ball stopped moving, because velocity has been the same for too long (from testing: optimal is 1.0-1.5 seconds)
                        isNotMoving=true;
                        isFinishedMoving=true;

                    }
                }
                else{ //ball is moving
                    dtime=0.f;
                    isNotMoving=false;
                }
            }
            else { //of ball stopped moving, put isNotmoving back to false, so we dont create more than 1 b spline
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
    drawType=0;
    isBall=true;
    triangle_surf = surface;
    //setPosition( -2.f, 3.f, -3.f);
    //setPosition( 2.f, 3.f, -2.f);
    //setPosition( -1.8f, 3.f, -3.7f); //most fun to look at

    //-----checking with 9.10.9
    setPosition( 4.0f, 3.f, 0.f); // point C
    //setPosition( 3.9f, 3.f, -0.1f);


    //setPosition( 2.f, 2.1f, -1.9f); //in the middle
    //setPosition(-70.3f, 11.3f, -100.55f);
    //setPosition(-30.3f, 11.3f, 70.55f);//wall collision left
    //setPosition(40.3f, 11.3f, 50.55f);//wall collision right
    scale(1.5);
};
