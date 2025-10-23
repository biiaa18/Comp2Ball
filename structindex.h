#ifndef STRUCTINDEX_H
#define STRUCTINDEX_H

#include <iostream>

struct  StructIndex {
    uint32_t v0;
    uint32_t v1;
    uint32_t v2;


    StructIndex() = default;

    //! Overloaded ostream operator which writes all vertex data on an open textfile stream
    friend std::ostream& operator<< (std::ostream&, const StructIndex&);

    //! Overloaded ostream operator which reads all vertex data from an open textfile stream
    friend std::istream& operator>> (std::istream&, StructIndex&);
};
#endif // STRUCTINDEX_H
