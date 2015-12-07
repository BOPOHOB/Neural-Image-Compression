#include "cvector.h"
#include <vector>
#include <iostream>


CVector::CVector(int size, Orientation theOrientation)
  : CArray(size),
    orientation(theOrientation){

}

CVector::~CVector(){

}

void CVector::setOrientation(Orientation theOrientation){
    orientation = theOrientation;
}

CVector::Orientation CVector::getOrientation() const {
    return orientation;
}

void CVector::transpose(){
    orientation == Horizontal ? orientation = Vertical : orientation = Horizontal;
}


