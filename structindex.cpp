#include "structindex.h"



std::ostream& operator<< (std::ostream& os, const StructIndex& i) {
    os << std::fixed;
    os << "(" << i.v0 << ", " << i.v1 << ", " << i.v2 << ") ";

    return os;
}
std::istream& operator>> (std::istream& is, StructIndex& i) {
    // Trenger fire temporære iariabler som kun skal lese inn parenteser og komma
    char dum, dum2, dum3, dum4;
    is >> dum >> i.v0 >> dum2 >> i.v1 >> dum3 >> i.v2 >> dum4;

    return is;
}
