#ifndef CVECTOR_H
#define CVECTOR_H
#include "carray.h"

class CVector : public CArray
{

public:

    enum Orientation {
        Horizontal,//as default
        Vertical
    };

    CVector(int size, Orientation = Horizontal);
    ~CVector();

    Orientation getOrientation() const;
    void setOrientation(Orientation = Horizontal);
    void transpose();

private:
    Orientation orientation;

};

#endif // CVECTOR_H
