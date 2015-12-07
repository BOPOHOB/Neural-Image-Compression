#ifndef CARRAY_H
#define CARRAY_H
#include <vector>
#include "crange.h"
class CRealRange;

class CArray : public std::vector<double>
{
public:

    CArray(int size = 0, double val = 0.0f);

    CArray(double* data, int size);

    CRealRange estimateRange() const;
    CIndexRange estimateRangeIndex() const;

    void grade(int count);
};

#endif // CARRAY_H
