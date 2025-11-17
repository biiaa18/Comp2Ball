#ifndef TRIANGLESURFACE_H
#define TRIANGLESURFACE_H

#include <string>
// #include <vector>
#include <QVector2D>
#include "VisualObject.h"
#include "Triangle.h"
#include <QPointF>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "quadtree.h"

// Structure to represent a 2D point
struct Point {
    double x, y;
    bool operator==(const Point& other) const {
        return std::abs(x - other.x) < 1e-6 && std::abs(y - other.y) < 1e-6;
    }
};
// Structure to represent a triangle
struct Triangle_ {
    Point a, b, c;
    bool operator==(const Triangle_& other) const {
        return (a == other.a && b == other.b && c == other.c) ||
               (a == other.a && b == other.c && c == other.b) ||
               (a == other.b && b == other.a && c == other.c) ||
               (a == other.b && b == other.c && c == other.a) ||
               (a == other.c && b == other.a && c == other.b) ||
               (a == other.c && b == other.b && c == other.a);
    }
};
//Defaults to a quad, but can read a mesh from file
class TriangleSurface : public VisualObject
{
public:
    TriangleSurface();
    TriangleSurface(const std::string& punktsky, int drawT);
    TriangleSurface(const std::string& vertics, const std::string& indics);
    TriangleSurface(const std::string& filename);
    // Function to check if a point is inside the circumcircle of a given triangle

    float xmin{0}, xmax{0}, ymin{0},ymax{0};
    QuadTree* quad;
    //float barysentriske(QVector2D vertx, float dt) override;
    // float averageHeight(QuadTree* quadtr);
    std::vector<QuadTree*> leaves;
    std::vector<Vertex> Vertices;
    void triangulate (int width, int height);
    void reorderVertices();
};

struct rute { //potentially use a quadtree?? and subdivide it will decide the "oppløsning"?
    rute(float xmin_, float ymin_, float xmax_, float ymax_): xmin(xmin_), ymin(ymin_), xmax(xmax_), ymax(ymax_){};
    float xmin, xmax, ymin,ymax;
    QVector2D midtpunkt=middle({xmin,ymin},{xmax,ymax});

    QVector2D middle(const QVector2D& p1,const QVector2D& p2){
        QVector2D m;
        m.setX((p2.x()+p1.x())/2);
        m.setY((p2.y()+p1.y())/2);
        return m;
    }
};

struct wall:public VisualObject {
    wall();

};

#endif // TRIANGLESURFACE_H
