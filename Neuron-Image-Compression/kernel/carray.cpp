#include "carray.h"
#include "crange.h"
#include <cmath>
#include <cstring>

#ifndef NOT_QT_AVAILABLE
#include <QDataStream>
#include <cmath>
#endif // NOT_QT_AVAILABLE

CArray::CArray(int size, double val)
  : std::vector<double>(size, val) { }


CArray::CArray(double* data, int size)
  : std::vector<double>(size) {
    memcpy(this->data(), data, size * sizeof(double));
}

CIndexRange CArray::estimateRangeIndex() const {
    CIndexRange domain(0);
    CRealRange range(std::numeric_limits<double>::infinity(),
                    -std::numeric_limits<double>::infinity());
    int i(0);
    for(const_iterator it(this->begin()), end(this->end()); it != end; ++it, ++i) {
        if (*it == *it && fabs(*it) != std::numeric_limits<double>::infinity()) {
            if (range.getMin() > *it) {
                range.setMin(*it);
                domain.setMin(i);
            } else if (range.getMax() < *it) {
                range.setMax(*it);
                domain.setMax(i);
            }
        }
    }
    return domain;
}

CRealRange CArray::estimateRange() const {
    CRealRange domain(std::numeric_limits<double>::infinity(),
                    -std::numeric_limits<double>::infinity());
    for(const_iterator it(this->begin()), end(this->end()); it != end; ++it) {
        if (*it == *it && fabs(*it) != std::numeric_limits<double>::infinity()) {
            domain.include(*it);
        }
    }
    return domain;
}

void CArray::grade(int count) {
    CRealRange range(estimateRange());
    double h(range.range());
    double step = h / count;
    for (CArray::iterator i(this->begin()), end(this->end()); i != end; ++i) {
        int bin((*i - range.getMin()) / step);
        if (bin == count) {
            --bin;
        }
        *i = range.getMin() + step / 2. + bin * step;
    }
}

bool CArray::operator==(const CArray& op)
{
    if (op.size() == this->size()) {
        CArray::const_iterator it(this->begin());
        const CArray::const_iterator end(this->end());
        CArray::const_iterator jt(op.begin());
        while (it != end) {
            if (*it != *jt) {
                return false;
            }
            ++it;
            ++jt;
        }
    }
    return true;
}

