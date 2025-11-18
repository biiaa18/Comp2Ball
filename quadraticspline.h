#ifndef QUADRATICSPLINE_H
#define QUADRATICSPLINE_H
#include <vector>
#include <QVector2D>
#include <QVector3D>
#include "VisualObject.h"
#include "Vertex.h"
#include "TriangleSurface.h"
using namespace std;
class QuadraticSpline:public VisualObject
{
public:
    //QuadraticSpline(vector<QVector2D> ctrl_p_flate){ctrl_p=ctrl_p_flate;};

    QuadraticSpline(vector<QVector2D> ctrl_p_flate, int n_, int d_, TriangleSurface* surf) ;
    QuadraticSpline(vector<QVector3D> ctrl_p_flate, int n_, int d_);
    int n; //antall kontrollpunkter
    int d; //grad
    int iterations=100;
    QVector2D evaluateBSplineSimple(float t);
    QVector3D getVertex(float t);
    TriangleSurface* triangle_surf;//get height from the surface by its control points
    //vector<QVector3D> ctrl_p_surface={surf->mVertices.at(0)}; //kontrollpunktene
    //QVector3D evaluateBSplineSimple(float t);
    int finnSkjotVektor(float t);//float parameter_t, vector<double> skjt_vector, int splineDegree);

    //to get a spline, we will make a small curve from 3 points on each triangle of the surface and then it will be joined into one spline
    vector<double> skjt={0.0,0.0,1.0,1.0}; //grad d =1; d+1 repetitions
    vector<QVector2D> ctrl_p; //kontrollpunktene fra trekantpflaten;
    vector<QVector3D> ctrl_p3D;
    float height;
    float barysentriske(QVector2D vertx, float dt)override;
};


#endif // QUADRATICSPLINE_H
