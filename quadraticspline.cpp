#include "quadraticspline.h"

QuadraticSpline::QuadraticSpline(vector<QVector2D> ctrl_p_flate, int n_, int d_, TriangleSurface* surf):VisualObject(){
    drawType=1;
    ctrl_p=ctrl_p_flate;
    triangle_surf=surf;
    n=n_;
    d=d_;
    //adjust skjøtvektor so it interpolates through first and last points, based on amount of controll points and degree
    skjt.resize(n+d+1); //5+2+1
    for(int i=0;i<skjt.size();i++){
        if(i<=d){
            skjt[i]=0.0; //{0.0, 0.0...
        }
        else if (i>=n){
            skjt[i]=float(n-d); //...3.0 ,3.0}
        }
        else{
            skjt[i]=skjt[i-1]+1.0;
        }
        qDebug()<<skjt[i];
    }

    float t_start=skjt[d];
    float t_end=skjt[skjt.size()-d-1];
    float step=(t_end-t_start)/(iterations -1);
    for(int i=0; i<iterations;i++){
        float t_=t_start+i*step;
        QVector2D vertx=evaluateBSplineSimple(t_);
        float y=barysentriske(vertx, 0.f);
        Vertex V;
        V.x=vertx.x();
        V.z=vertx.y();
        V.y=y;
        V.r= 0.f;
        V.g= 1.f;
        V.b= 0.f;
        V.u= 0.f,
        V.v=0.f;
        mVertices.push_back(V);
        //mIndices.push_back(i);
        //qDebug()<<V.x<<" "<<V.y;        //mIndices.push_back(i);
    }

}

QuadraticSpline::QuadraticSpline(vector<QVector3D> ctrl_p_flate, int n_, int d_): VisualObject()
{
    drawType=1;
    ctrl_p3D=ctrl_p_flate;
    n=n_;
    d=d_;
    //adjust skjøtvektor so it interpolates through first and last points, based on amount of controll points and degree
    skjt.resize(n+d+1); //5+2+1
    for(int i=0;i<skjt.size();i++){
        if(i<=d){
            skjt[i]=0.0; //{0.0, 0.0...
        }
        else if (i>=n){
            skjt[i]=float(n-d); //...3.0 ,3.0}
        }
        else{
            skjt[i]=skjt[i-1]+1.0;
        }
        qDebug()<<skjt[i];
    }

    float t_start=skjt[d];
    float t_end=skjt[skjt.size()-d-1];
    float step=(t_end-t_start)/(iterations -1);
    for(int i=0; i<iterations;i++){
        float t_=t_start+i*step;
        QVector3D vertx=getVertex(t_);
        //float y=barysentriske(vertx, 0.f);
        Vertex V;
        V.x=vertx.x();
        V.z=vertx.z();
        V.y=-(vertx.y()+3.f);
        V.r= 0.f;
        V.g= 1.f;
        V.b= 0.f;
        V.u= 0.f,
        V.v=0.f;
        mVertices.push_back(V);
        //mIndices.push_back(i);
        qDebug()<<"spline x, height and y  "<<V.x<<" "<<V.y<<" "<<V.z<<"\n";        //mIndices.push_back(i);
    }


}

QuadraticSpline::QuadraticSpline(): VisualObject()
{
    drawType=1;
    Vertex v1{ 4.0f,  -5.5f,  4.0f,   1.0f, 0.0f, 0.0f,  0.0f, 0.0f};  //  bottom-left corner
    Vertex v2{ 0.0f,  -5.5f,  0.0f,   0.0f, 1.0f, 0.0f,  1.0f, 0.0f };
    mVertices.push_back(v1);
    mVertices.push_back(v2);
}

QuadraticSpline::QuadraticSpline(float color):VisualObject()
{
    drawType=1;
    Vertex v1{ 4.0f,  -5.5f,  4.0f,   0.f, 0.0f, color,  0.0f, 0.0f};  //  bottom-left corner
    Vertex v2{ 0.0f,  -5.5f,  0.0f,   1.0f, 0.0f, color,  1.0f, 0.0f };
    mVertices.push_back(v1);
    mVertices.push_back(v2);
}

QVector2D QuadraticSpline::evaluateBSplineSimple(float t)
{
    int mi=finnSkjotVektor(t);
    if (t == skjt.back()) return ctrl_p.back();
    // if(mi<d || mi>=ctrl_p.size()){
    //     return QVector2D(0,0);
    // }
    vector<QVector2D> a(d+1);  //a.resize(d+1);
    float w;
    for (int i=0;i<=d;i++){
        a[d-i]=ctrl_p[mi-i];
    }

    for(int j=d;j>0;j--){
        int k=mi-j;
        for(int i=0;i<j;i++){
            k++;
            float denom=skjt[k+j]-skjt[k];
            if(denom==0.f){
                continue;
            }
            else{
                w=(t-skjt[k])/denom;
            }

            a[i]=a[i]*(1-w)+a[i+1]*w; //corner cutting  (from de casteljau)
        }
    }
    return a[0];

}

QVector3D QuadraticSpline::getVertex(float t)
{
    int mi=finnSkjotVektor(t);
    if (t == skjt.back()) return ctrl_p3D.back();
    // if(mi<d || mi>=ctrl_p.size()){
    //     return QVector2D(0,0);
    // }
    vector<QVector3D> a(d+1);  //a.resize(d+1);
    float w;
    for (int i=0;i<=d;i++){
        a[d-i]=ctrl_p3D[mi-i];
    }

    for(int j=d;j>0;j--){
        int k=mi-j;
        for(int i=0;i<j;i++){
            k++;
            float denom=skjt[k+j]-skjt[k];
            if(denom==0.f){
                continue;
            }
            else{
                w=(t-skjt[k])/denom;
            }

            a[i]=a[i]*(1-w)+a[i+1]*w; //corner cutting  (from de casteljau)
        }
    }
    return a[0];


}

int QuadraticSpline::finnSkjotVektor(float t) //t is "parameter verdi"
{/*
    int mi=n-1; //index to the last control point, since we have "n" of then
    //and it is 0, 1, 2,...n-1 control points

    //mi will be how many "basis funksjoner" we have for the spline curve
    while (t<skjt[mi] && mi>d){
        mi--;
    }*/

    int mi = -1;
    for (int i = d; i < skjt.size() - d - 1; ++i) {
        if (t >= skjt[i] && t < skjt[i + 1]) {
            mi = i;
            //qDebug() << "MI "<< mi;
            break;
        }
    }

    return mi;
}

float QuadraticSpline::barysentriske(QVector2D vertx, float dt)
{
    float ballX = vertx.x();
    float ballZ = vertx.y();
    //float ballY = 0.f;

    for (size_t i = 0; i < triangle_surf->mIndices.size(); i += 3)
    {
        Vertex A = triangle_surf->mVertices[triangle_surf->mIndices[i]];
        Vertex B = triangle_surf->mVertices[triangle_surf->mIndices[i + 1]];
        Vertex C = triangle_surf->mVertices[triangle_surf->mIndices[i + 2]];

        //barycentric coordinates
        QVector2D AB=QVector2D{B.x-A.x, B.z-A.z};
        QVector2D AC=QVector2D{C.x-A.x, C.z-A.z};
        QVector2D AP=QVector2D{ballX-A.x, ballZ-A.z};
        float denominator = AB.x()*AC.y() -AB.y()*AC.x();   //CROSS PRODUCT OF AB, AC

        // //barycentric coordinates
        // QVector3D AB=QVector3D{B.x-A.x, B.y-A.y, B.z-A.z};
        // QVector3D AC=QVector3D{C.x-A.x, C.y-A.y, C.z-A.z};


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
            height=lambda1 * B.y + lambda2 * C.y + lambda3 * A.y ;
            break;


        }
        else{

                //qDebug("not inside triangle of  triangle_surf");
            }
        }

    return height;
}

