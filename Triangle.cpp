#include "Triangle.h"
#include "Vertex.h"


Triangle::Triangle() : VisualObject()
{
    mVertices.push_back(Vertex{-0.5f,   0.0f,  0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f});
    mVertices.push_back(Vertex{-0.5f,  -0.5f,  0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f});
    mVertices.push_back(Vertex{ 0.0f,   0.0f,  0.0f,   0.0f, 0.0f, 1.0f,   1.0f, 0.0f});

    //Temporary positioning
    //mMatrix.translate(-0.25f, 0, 0);
}

// std::ostream& operator<< (std::ostream& os, const Triangle& v) {
//     os << std::fixed;
//     os << "(" << v.v0 << ", " << v.v1 << ", " << v.v2 << ") ";
//     os << "(" << v.n0 << ", " << v.n1 << ", " << v.n2 << ") ";
//     return os;
// }
// std::istream& operator>> (std::istream& is, Triangle& v) {
//     // Trenger fire temporære variabler som kun skal lese inn parenteser og komma
//     char dum, dum2, dum3, dum4;
//     is >> dum >> v.v0 >> dum2 >> v.v1 >> dum3 >> v.v2 >> dum4;
//     is >> dum >> v.n0 >> dum2 >> v.n1 >> dum3 >> v.n2 >> dum4;

//     return is;
// }
