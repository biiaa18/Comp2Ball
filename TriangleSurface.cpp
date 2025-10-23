#include "TriangleSurface.h"
#include <fstream>
#include <QDebug>
TriangleSurface::TriangleSurface() : VisualObject()
{

    Vertex v1{ 0.0f,  3.0f,  0.0f,   1.0f, 0.0f, 0.0f,  0.0f, 0.0f};  //  bottom-left corner
    Vertex v2{ 2.0f,  2.0f,  0.0f,   0.0f, 1.0f, 0.0f,  1.0f, 0.0f }; //  bottom-right corner
    Vertex v3{ 2.0f,  1.0f,  2.0f,   0.0f, 0.0f, 1.0f,  0.0f, 1.0f }; //  top-left corner
    Vertex v4{ 0.0f,  2.0f,  2.0f,   1.0f, 1.0f, 0.0f,  1.0f, 1.0f }; //  top-right corner

    Vertex v5{ 2.0f,  3.0f,  4.0f,   1.0f, 0.0f, 0.0f,  0.0f, 0.0f};  //  bottom-left corner
    Vertex v6{ 0.0f,  3.0f,  4.0f,   0.0f, 1.0f, 0.0f,  1.0f, 0.0f }; //  bottom-right corner
    Vertex v7{ 4.0f,  3.0f,  0.0f,   0.0f, 0.0f, 1.0f,  0.0f, 1.0f }; //  top-left corner
    Vertex v8{ 4.0f,  2.0f,  2.0f,   1.0f, 1.0f, 0.0f,  1.0f, 1.0f }; //  top-right corner

    Vertex v9{ 4.0f,  3.0f,  4.0f,   1.0f, 1.0f, 0.0f,  1.0f, 1.0f }; //  top-right corner

    //Pushing 1st triangle,
    // mVertices.push_back(v1);
    // mVertices.push_back(v2);
    // mVertices.push_back(v3);
    // mVertices.push_back(v4);
    // mVertices.push_back(v5);
    // mVertices.push_back(v6);
    // mVertices.push_back(v7);
    // mVertices.push_back(v8);
    // mVertices.push_back(v9);
    // //Indexes for the two triangles to form a quad
    // mIndices.push_back(0);
    // mIndices.push_back(2);
    // mIndices.push_back(3);

    // mIndices.push_back(0);
    // mIndices.push_back(1);
    // mIndices.push_back(2);

    // mIndices.push_back(3);
    // mIndices.push_back(4);
    // mIndices.push_back(5);

    // mIndices.push_back(3);
    // mIndices.push_back(2);
    // mIndices.push_back(4);

    // mIndices.push_back(1);
    // mIndices.push_back(7);
    // mIndices.push_back(2);

    // mIndices.push_back(1);
    // mIndices.push_back(6);
    // mIndices.push_back(7);

    // mIndices.push_back(2);
    // mIndices.push_back(8);
    // mIndices.push_back(4);

    // mIndices.push_back(2);
    // mIndices.push_back(7);
    // mIndices.push_back(8);

    //Temporary scale and positioning
    mMatrix.scale(0.5f);
    mMatrix.translate(0.5f, 0.1f, 0.1f);
}

TriangleSurface::TriangleSurface(const std::string& punktsky, int drawT)
{
    drawType=drawT;
    std::ifstream inn(punktsky);
    if (!inn.is_open())
        return;
    // read input from math part of compulsory
    int n; //number of vertices
    Vertex v;
    inn >> n;
    for (auto i=0; i<n; i++)
    {
        inn >> v;
        Vertex v1;
        v1.x=v.x+0.1f;
        v1.y=v.y+0.1f;
        v1.z=v.z+0.1f;
        v1.r=1.f;
        v1.g=0.f;
        v1.b=0.f;
        v1.u=0.f;
        v1.v=0.f;
        mVertices.push_back(v);
        mVertices.push_back(v1);
    }
    inn.close();
    qDebug()<<"\n-------------------------------------------------im drawing-------------------------";
}

TriangleSurface::TriangleSurface(const std::string& vertics, const std::string& indics)
{

    std::ifstream inn(vertics);
    if (!inn.is_open())
        return;
    // read input from math part of compulsory
    int n; //number of vertices
    Vertex v;
    inn >> n;
    for (auto i=0; i<n; i++)
    {
        inn >> v;
        mVertices.push_back(v);

        // mIndices.push_back(i);
        //qDebug() << v.x << v.y << v.z;
    }
    inn.close();

    std::ifstream inn2(indics);
    if (!inn.is_open())
        return;
    int tr; //number of triangles
    StructIndex in;
    inn2>>tr;
    for (auto i=0; i<tr; i++)
    {
        inn2 >> in;
        mIndices.push_back(in.v0);
        mIndices.push_back(in.v1);
        mIndices.push_back(in.v2);
        //qDebug() << v.x << v.y << v.z;
    }
    inn2.close();


}

TriangleSurface::TriangleSurface(const std::string& filename)
{
    drawType=0;

    std::ifstream inn(filename);
    if (!inn.is_open())
        return;
    // read input from math part of compulsory
    int n; //number of vertices
    Vertex v;
    std::vector<Point> points;
    std::vector<Triangle_> result;
    inn >> n;
    for (auto i=0; i<n; i++)
    {
        inn >> v;
        mVertices.push_back(v);
       // points.push_back({v.x, v.z});

        ctrl_p_flate.push_back({v.x,v.z});
        //mIndices.push_back(i);
        //qDebug() << v.x << v.y << v.z;
    }

    //
    // Output the triangles
    // result = delaunayTriangulation(points);
    // qDebug()<< "Delaunay Triangles:\n";
    // for (const auto& tri : result) {

    //     qDebug()<< "Triangle: (" << tri.a.x << ", " << tri.a.y << ") - "
    //              << "(" << tri.b.x << ", " << tri.b.y << ") - "
    //              << "(" << tri.c.x << ", " << tri.c.y << ")\n";
    //     mIndices.push_back(tri.a);
    // }

    int tr; //number of triangles
    StructIndex in;
    inn>>tr;
    for (auto i=0; i<tr; i++)
    {
        inn >> in;
        mIndices.push_back(in.v0);
        mIndices.push_back(in.v1);
        mIndices.push_back(in.v2);
        //qDebug() << v.x << v.y << v.z;
    }
    inn.close();


}

Triangle_ TriangleSurface::getSuperTriangle(const std::vector<Point> &points) {
    double minX = points[0].x, minY = points[0].y;
    double maxX = minX, maxY = minY;
    for (const auto& p : points) {
        minX = std::min(minX, p.x);
        minY = std::min(minY, p.y);
        maxX = std::max(maxX, p.x);
        maxY = std::max(maxY, p.y);
    }
    double dx = maxX - minX, dy = maxY - minY;
    double dmax = std::max(dx, dy) * 2.0;
    return { {minX - dmax, minY - dmax},
            {minX + dmax * 2, minY - dmax},
            {minX + dmax, minY + dmax * 2} };
}

std::vector<Triangle_> TriangleSurface::delaunayTriangulation(std::vector<Point> &points) {
    std::vector<Triangle_> triangles;
    Triangle_ superTriangle = getSuperTriangle(points);
    triangles.push_back(superTriangle);
    for (const auto& p : points) {
        std::vector<Triangle_> badTriangles;
        std::vector<std::pair<Point, Point>> edges;
        for (const auto& tri : triangles) {
            if (isPointInCircumcircle(tri, p)) {
                badTriangles.push_back(tri);
                edges.push_back({ tri.a, tri.b });
                edges.push_back({ tri.b, tri.c });
                edges.push_back({ tri.c, tri.a });
            }
        }
        // Remove bad triangles
        triangles.erase(std::remove_if(triangles.begin(), triangles.end(),
                                       [&badTriangles](const Triangle_& t) {
                                           return std::find(badTriangles.begin(), badTriangles.end(), t) !=
                                                  badTriangles.end();
                                       }), triangles.end());
        // Reconstruct triangles
        for (const auto& edge : edges) {
            triangles.push_back({ edge.first, edge.second, p });
        }
    }
    // Remove super-triangle-related triangles
    triangles.erase(std::remove_if(triangles.begin(), triangles.end(),
                                   [&superTriangle](const Triangle_& t) {
                                       return (t.a == superTriangle.a || t.b == superTriangle.a || t.c ==
                                                                                                       superTriangle.a ||
                                               t.a == superTriangle.b || t.b == superTriangle.b || t.c ==
                                                                                                       superTriangle.b ||
                                               t.a == superTriangle.c || t.b == superTriangle.c || t.c ==
                                                                                                       superTriangle.c);
                                   }), triangles.end());
    return triangles;
}
