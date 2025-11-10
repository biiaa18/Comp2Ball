#include "TriangleSurface.h"
#include <fstream>
#include <QDebug>
// #include <bits/stdc++.h>
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
    drawType=0; //testing , should be 0 for triangles;

    std::ifstream inn(filename);
    if (!inn.is_open())
        return;
    // read input from math part of compulsory
    int n; //number of vertices 
    Vertex v;

    // std::vector<Point> points;
    // std::vector<Triangle_> result;
    inn >> n;
    for(int i=0; i<1; i++){
        inn>>v;
        xmin=v.x;
        xmax=v.x;
        ymin=v.z;
        ymax=v.z;
        Vertices.push_back(v);
        qDebug() <<"first line------ x min: "<<xmin <<"y min: "<< ymin <<"x max: "<< xmax<<"y max: "<<ymax<<"\n";
    }
    for (auto i=0; i<n-1; i++)
    {
        inn >> v;
        xmin=fmin(xmin,v.x);
        ymin=fmin(ymin,v.z);
        xmax=fmax(xmax,v.x);
        ymax=fmax(ymax,v.z);
        Vertices.push_back(v);
        //mVertices.push_back(v);
       // points.push_back({v.x, v.z});
        //ctrl_p_flate.push_back({v.x,v.z});
        //mIndices.push_back(i);
        //qDebug() << v.x << v.y << v.z;
    }
    inn.close();
    qDebug() << "x min: "<<xmin <<"y min: "<< ymin <<"x max: "<< xmax<<"y max: "<<ymax<<"\n";
    //---------------------sv--------so------------no----------nv
    quad=new QuadTree({xmin,ymin},{xmax,ymin}, {xmax,ymax},{xmin,ymax}); //convex hull
    int number=1;
    quad->subDivide(number);
    //number of quads in row and column are same, since quad tree is subdividing everything equally
    int opplosning=std::pow(2,number); //2^n, for 1 subdivision - 4 trees: 2 rows+ 2 columns, etc.
    int width=opplosning;
    int height=opplosning;

    for (Vertex& v: Vertices){
        QVector3D point={v.x, v.y,v.z}; //need height to calculate average height for the middle points (future indices)
        QVector3D* v_ptr;
        v_ptr=&point;
        quad->insertObject(v_ptr,quad); //insert points (vertices) into each corresponding quadtree so we can search where they are later)
    }
    //loop through all quads and calculate the average .y from quad->VerticesInQuad and update middle quad->m (middle point);
    quad->findLeaves(&leaves);//now we store all leaves with updated average height for middle point and have a grid made of middle points
    //pushing vertices (our middle points) into mvertices for rendering and
    for(QuadTree* it:leaves){
        Vertex v;
        v.x=it->m.x();
        v.y=it->m.y();
        v.z=it->m.z();
        v.r=1.f;
        v.g=0.f;
        v.b=0.f;
        v.u=0.f;
        v.v=0.f;
        qDebug() << v.x << v.y << v.z;
        mVertices.push_back(v);

        triangulate(width, height);
        //algorithm for mIndices.push_back(leaves[i])
    }

    //----------------------------------------------------------------------------------------------------------------------------------------



    // for (Vertex& v: mVertices){
    //     QVector2D point={v.x, v.z};
    //     QVector2D* v_ptr;
    //     v_ptr=&point;
    //     QuadTree* current_quad=quad->findObject(v_ptr);
    //     barysentriske(point,current_quad); //find which rute (small quad) is the current skypunkt
    // }


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

    // int tr; //number of triangles
    // StructIndex in;
    // inn>>tr;
    // for (auto i=0; i<tr; i++)
    // {
    //     inn >> in;
    //     mIndices.push_back(in.v0);
    //     mIndices.push_back(in.v1);
    //     mIndices.push_back(in.v2);
    //     //qDebug() << v.x << v.y << v.z;
    // }



}

void TriangleSurface::triangulate(int width, int height)
{
    for(int d{0}; d < height-1; ++d)        //height - 1 because we draw the last quad from height - 1 and in negative z direction
    {
        for(int w{0}; w < width-1; ++w)    //width - 1 because we draw the last quad from width - 1 and in positive x direction
        {
            //Indices for one quad:
            mIndices.emplace_back(w + d * width);               // 0 + 0 * mWidth               = 0
            mIndices.emplace_back(w + d * width + width + 1);   // 0 + 0 * mWidth + mWidth + 1  = mWidth + 1
            mIndices.emplace_back(w + d * width + width);       // 0 + 0 * mWidth + mWidth      = mWidth
            mIndices.emplace_back(w + d * width);               // 0 + 0 * mWidth               = 0
            mIndices.emplace_back(w + d * width + 1);           // 0 + 0 * mWidth + 1           = 1
            mIndices.emplace_back(w + d * width + width + 1);   // 0 + 0 * mWidth + mWidth + 1  = mWidth + 1
        }
    }
}

// float TriangleSurface::averageHeight(QuadTree *quadtr)
// {
//     float height=0;
//     for(QVector3D* p: quadtr->VerticesInQuad){
//         height+=p->y();
//     }
//     height=height/(quadtr->VerticesInQuad.size()-1);
//     return height;
// }

// float TriangleSurface::barysentriske(QVector2D vertx, QuadTree* quad)
// {
//     float pointX = vertx.x();
//     float pointZ = vertx.y();
//     //qDebug()<<"x : "<<pointX<<" y: "<< pointZ<<"\n";
//     //float pointZ = 0.f;


//     QVector2D A=quad->A;
//     QVector2D B=quad->B;
//     QVector2D C=quad->C;
//         //barycentric coordinates
//         QVector2D AB=QVector2D{B.x-A.x, B.z-A.z};
//         QVector2D AC=QVector2D{C.x-A.x, C.z-A.z};
//         QVector2D AP=QVector2D{pointX-A.x, pointZ-A.z};
//         float denominator = AB.x()*AC.y() -AB.y()*AC.x();   //CROSS PRODUCT OF AB, AC



//         if (denominator == 0.0f)
//         {
//             continue;
//         }


//         // QVector3D PA=QVector3D{A.x-pointX, A.y-pointZ, A.z-pointZ};
//         // QVector3D PB=QVector3D{B.x-pointX, B.y-pointZ, B.z-pointZ};
//         // QVector3D PC=QVector3D{C.x-pointX, C.y-pointZ, C.z-pointZ};


//         // float lambda1 = (PB.x()*PC.z() -PB.z()*PC.x())/denominator;
//         // float lambda2 = (PC.x()*PA.z() -PC.z()*PA.x())/denominator;
//         // float lambda3 = (PA.x()*PB.z() -PA.z()*PB.x())/denominator;


//         float lambda1 = (AP.x()*AC.y() -AC.x()*AP.y())/denominator;
//         float lambda2 = (AB.x()*AP.y() -AB.y()*AP.x())/denominator;
//         float lambda3 = 1.0f-lambda1-lambda2;

//         if (lambda1 >= 0.f && lambda2 >= 0.f && lambda3 >= 0.f &&
//             lambda1 <= 1.f && lambda2 <= 1.f && lambda3 <= 1.f)
//         {
//             height=lambda1 * B.y + lambda2 * C.y + lambda3 * A.y+radius;
// }

// Triangle_ TriangleSurface::getSuperTriangle(const std::vector<Point> &points) {
//     double minX = points[0].x, minY = points[0].y;
//     double maxX = minX, maxY = minY;
//     for (const auto& p : points) {
//         minX = std::min(minX, p.x);
//         minY = std::min(minY, p.y);
//         maxX = std::max(maxX, p.x);
//         maxY = std::max(maxY, p.y);
//     }
//     double dx = maxX - minX, dy = maxY - minY;
//     double dmax = std::max(dx, dy) * 2.0;
//     return { {minX - dmax, minY - dmax},
//             {minX + dmax * 2, minY - dmax},
//             {minX + dmax, minY + dmax * 2} };
// }

// std::vector<Triangle_> TriangleSurface::delaunayTriangulation(std::vector<Point> &points) {
//     std::vector<Triangle_> triangles;
//     Triangle_ superTriangle = getSuperTriangle(points);
//     triangles.push_back(superTriangle);
//     for (const auto& p : points) {
//         std::vector<Triangle_> badTriangles;
//         std::vector<std::pair<Point, Point>> edges;
//         for (const auto& tri : triangles) {
//             if (isPointInCircumcircle(tri, p)) {
//                 badTriangles.push_back(tri);
//                 edges.push_back({ tri.a, tri.b });
//                 edges.push_back({ tri.b, tri.c });
//                 edges.push_back({ tri.c, tri.a });
//             }
//         }
//         // Remove bad triangles
//         triangles.erase(std::remove_if(triangles.begin(), triangles.end(),
//                                        [&badTriangles](const Triangle_& t) {
//                                            return std::find(badTriangles.begin(), badTriangles.end(), t) !=
//                                                   badTriangles.end();
//                                        }), triangles.end());
//         // Reconstruct triangles
//         for (const auto& edge : edges) {
//             triangles.push_back({ edge.first, edge.second, p });
//         }
//     }
//     // Remove super-triangle-related triangles
//     triangles.erase(std::remove_if(triangles.begin(), triangles.end(),
//                                    [&superTriangle](const Triangle_& t) {
//                                        return (t.a == superTriangle.a || t.b == superTriangle.a || t.c ==
//                                                                                                        superTriangle.a ||
//                                                t.a == superTriangle.b || t.b == superTriangle.b || t.c ==
//                                                                                                        superTriangle.b ||
//                                                t.a == superTriangle.c || t.b == superTriangle.c || t.c ==
//                                                                                                        superTriangle.c);
//                                    }), triangles.end());
//     return triangles;
// }
