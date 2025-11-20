#include "TriangleSurface.h"
#include <fstream>
#include <QDebug>
// #include <bits/stdc++.h>
TriangleSurface::TriangleSurface() : VisualObject()
{

    Vertex v1{ 0.0f,  3.0f,  0.0f,   1.0f, 0.0f, 0.0f,  0.0f, 0.0f};  //  bottom-left corner
    Vertex v2{ 2.0f,  2.0f,  0.0f,   0.0f, 1.0f, 0.0f,  1.0f, 0.0f }; //  bottom-right corner
    Vertex v3{ 2.0f,  1.0f,  -2.0f,   0.0f, 0.0f, 1.0f,  0.0f, 1.0f }; //  top-left corner
    Vertex v4{ 0.0f,  2.0f,  -2.0f,   1.0f, 1.0f, 0.0f,  1.0f, 1.0f }; //  top-right corner

    Vertex v5{ 2.0f,  3.0f,  -4.0f,   1.0f, 0.0f, 0.0f,  0.0f, 0.0f};  //  bottom-left corner
    Vertex v6{ 0.0f,  3.0f,  -4.0f,   0.0f, 1.0f, 0.0f,  1.0f, 0.0f }; //  bottom-right corner
    Vertex v7{ 4.0f,  3.0f,  0.0f,   0.0f, 0.0f, 1.0f,  0.0f, 1.0f }; //  top-left corner
    Vertex v8{ 4.0f,  2.0f,  -2.0f,   1.0f, 1.0f, 0.0f,  1.0f, 1.0f }; //  top-right corner

    Vertex v9{ 4.0f,  3.0f,  -4.0f,   1.0f, 1.0f, 0.0f,  1.0f, 1.0f }; //  top-right corner

    //Pushing 1st triangle,
    mVertices.push_back(v1);
    mVertices.push_back(v2);
    mVertices.push_back(v3);
    mVertices.push_back(v4);
    mVertices.push_back(v5);
    mVertices.push_back(v6);
    mVertices.push_back(v7);
    mVertices.push_back(v8);
    mVertices.push_back(v9);
    //Indexes for the two triangles to form a quad
    mIndices.push_back(0);
    mIndices.push_back(2);
    mIndices.push_back(3);

    mIndices.push_back(0);
    mIndices.push_back(1);
    mIndices.push_back(2);

    mIndices.push_back(3);
    mIndices.push_back(4);
    mIndices.push_back(5);

    mIndices.push_back(3);
    mIndices.push_back(2);
    mIndices.push_back(4);

    mIndices.push_back(1);
    mIndices.push_back(7);
    mIndices.push_back(2);

    mIndices.push_back(1);
    mIndices.push_back(6);
    mIndices.push_back(7);

    mIndices.push_back(2);
    mIndices.push_back(8);
    mIndices.push_back(4);

    mIndices.push_back(2);
    mIndices.push_back(7);
    mIndices.push_back(8);

    //Temporary scale and positioning
    // mMatrix.scale(0.5f);
    // mMatrix.translate(0.5f, 0.1f, 0.1f);
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
    if (!inn2.is_open())
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
        //qDebug() << in.v0 << in.v1 << in.v2;
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
        //qDebug() <<"first line------ x min: "<<xmin <<"y min: "<< ymin <<"x max: "<< xmax<<"y max: "<<ymax<<"\n";
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
    int number=5;
    quad->subDivide(number);
    //number of quads in row and column are same, since quad tree is subdividing everything equally
    int opplosning=std::pow(2,number); //2^n, for 1 subdivision - 4 trees: 2 rows+ 2 columns, etc.
    int width=opplosning;
    int height=opplosning;

    for (Vertex& v: Vertices){
         //need height to calculate average height for the middle points (future indices)
        QVector3D* v_ptr=new QVector3D(v.x, v.y,v.z);
        quad->insertObject(v_ptr,quad); //insert points (vertices) into each corresponding quadtree so we can search where they are later)
    }
    //loop through all quads and calculate the average .y from quad->VerticesInQuad and update middle quad->m (middle point);
    quad->findLeaves(&leaves);//now we store all leaves with updated average height for middle point and have a grid made of middle points
    //pushing vertices (our middle points) into mvertices for rendering and
    reorderVertices();
    float add;
    for(QuadTree* it:leaves){
        Vertex v;
        v.x=it->m.x()-588400.60f; //588400.60f, 0.f, -7181100.45f
        v.y=it->m.y();
        add=v.y/100.f;
        v.z=it->m.z()-7181100.45f;
        v.r=0.f;
        v.g=0.f;
        v.b=0.f;
        v.u=abs(add);//0.1f+add;
        v.v=abs(add);//3f+add;
        //qDebug() << v.x-588400.6<< v.y << v.z-7181100.45;
        mVertices.push_back(v);
        //algorithm for mIndices.push_back(leaves[i])
        //add+=0.1f;
    }
    triangulate(width, height);

    //----------------------------------------------------------------------------------------------------------------------
}

void TriangleSurface::triangulate(int width, int height)
{
    for(int d=0; d < height-1; ++d)        //height - 1 because we draw the last quad from height - 1 and in negative z direction
    {
        for(int w=0; w < width-1; ++w)    //width - 1 because we draw the last quad from width - 1 and in positive x direction
        {
            //Indices for one quad:
            //          --
            //          |/         start bottom left, go to right corner på skrå, then left, then "down"
            mIndices.emplace_back(w + d * width);               // 0 + 0 * mWidth               = 0             0
            mIndices.emplace_back(w + d * width + width + 1);   // 0 + 0 * mWidth + mWidth + 1  = mWidth + 1    3
            mIndices.emplace_back(w + d * width + width);       // 0 + 0 * mWidth + mWidth      = mWidth        2
            //second triangle
            //          /|
            //          --
            mIndices.emplace_back(w + d * width);               // 0 + 0 * mWidth               = 0             0
            mIndices.emplace_back(w + d * width + 1);           // 0 + 0 * mWidth + 1           = 1             1
            mIndices.emplace_back(w + d * width + width + 1);   // 0 + 0 * mWidth + mWidth + 1  = mWidth + 1    3
            //we end up with quad
            //         ---
            //         |/|
            //         ---
        }
    }
}

void TriangleSurface::reorderVertices()
{
    std::sort(leaves.begin(), leaves.end(),
              []( QuadTree*v, QuadTree*v_ ) { //leaves is vector of QuadTree*, so thats what we iterate through,
                    //but we care about comparing the x and z values of middle points of our leaves
                  //------- sort vertices from lowest y to highest
                  if (std::abs(v->m.z()-v_->m.z())>0.01f) {//check if they are in same column (have different y values)
                    return v->m.z()<v_->m.z(); ///if this returns true (z of v is less than z of v_) - we return v, if not - v_
                  }
                  //-----------sort vertices from lowest x to highest, if they are in same row (so they have same y values)
                  else{
                      return v->m.x()<v_->m.x();
                  }
                  // else{ //if it doesnt get sorted by x value because they are equal, it will differ in y value
                  //   return v_->m.x()<v->m.x();
                  // }
                  // sort vertices from lowest y to highest
                  /*if (v->m.z()<v_->m.z()) {
                      return v->m.z()<v_->m.z();
                  }
                  else{ //if it doesnt get sorted by x value because they are equal, it will differ in y value
                      return v_->m.z()<v->m.z();

                  }*/


    });
    // for (const auto& num : leaves) {
    //     qDebug() << "x  " << num->m.x() << " y " << num->m.z()
    //          << " )\n";
    // }
}


wall::wall():VisualObject()
{
    Vertex v1{ 0.5f,  0.0f,  50.0f,   1.0f, 0.0f, 0.0f,  0.0f, 0.0f};  //  bottom-right corner
    Vertex v2{ 0.5f,  0.0f,  100.0f,   0.0f, 1.0f, 0.0f,  1.0f, 0.0f }; //  bottom-left corner
    Vertex v3{ 0.5f,  10.0f,  50.0f,   0.0f, 0.0f, 1.0f,  0.0f, 1.0f }; //  top-right corner
    Vertex v4{ 0.5f,  10.0f,  100.0f,   1.0f, 1.0f, 0.0f,  1.0f, 1.0f }; //  top-left corner

    //Pushing 1st triangle,
    mVertices.push_back(v1);
    mVertices.push_back(v2);
    mVertices.push_back(v3);

    mVertices.push_back(v4);
    mVertices.push_back(v3);
    mVertices.push_back(v2);

    //Indexes for the two triangles to form a quad
    mIndices.push_back(0);
    mIndices.push_back(1);
    mIndices.push_back(2);

    mIndices.push_back(3);
    mIndices.push_back(2);
    mIndices.push_back(1);

    float z_= abs((v2.z-v1.z)/2);
    center={0.5f,  0.0f, 0.f};
    QVector3D AB={v2.x-v1.x,v2.y-v1.y,v2.z-v1.z};
    QVector3D AC={v3.x-v1.x,v3.y-v1.y,v3.z-v1.z};
    normal=QVector3D::crossProduct(AB, AC);
    normal=normal.normalized();
}
