#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "VisualObject.h"

class Triangle : public VisualObject{
public:
    //vertices for a triangle
    int indeks[3];
    // int v0;
    // int v1;
    // int v2;
    // //neighbours
    int nabo[3];
    // int n0;
    // int n1;
    // int n2;
   ///we dont need neighbours to build a surface, just to iterate through barysentic coordinates
    Triangle(); //=default;
    // //! Overloaded ostream operator which writes all vertex data on an open textfile stream
    // friend std::ostream& operator<< (std::ostream&, const Triangle&);

    // //! Overloaded ostream operator which reads all vertex data from an open textfile stream
    // friend std::istream& operator>> (std::istream&, Triangle&);
};


#endif // TRIANGLE_H
