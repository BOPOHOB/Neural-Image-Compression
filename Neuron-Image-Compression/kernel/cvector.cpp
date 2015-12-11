#include "cvector.h"
#include <vector>
#include <iostream>


CVector::CVector(int size, double initialValue, Orientation theOrientation)
  : CArray(size, initialValue)
  , orientation(theOrientation) { }

CVector::CVector(const CVector& enother)
    : CArray(enother)
    , orientation(enother.orientation)
{

}

void CVector::setOrientation(const Orientation theOrientation){
    orientation = theOrientation;
}

CVector::Orientation CVector::getOrientation() const {
    return orientation;
}

void CVector::transpose()
{
    orientation == Horizontal ? orientation = Vertical : orientation = Horizontal;
}

CVector CVector::transposed() const
{
    CVector r(*this);
    r.orientation = orientation == Horizontal ? Vertical : Horizontal;
    return r;
}
