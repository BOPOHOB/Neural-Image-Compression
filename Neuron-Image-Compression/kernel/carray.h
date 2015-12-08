#ifndef CARRAY_H
#define CARRAY_H
#include <vector>
#include "crange.h"
class CRealRange;
class CIndexRange;

#ifndef NOT_QT_AVAILABLE
#include <QDataStream>
#include <QDebug>
#endif

///array it not the mathematic vector. It's just a numbers.

class CArray : public std::vector<double>
{
public:
    CArray(int size = 0, double val = 0.0f);

    CArray(double* data, int size);

    CRealRange estimateRange() const;
    CIndexRange estimateRangeIndex() const;

    /// split all values to bins with equal range. Move values from each bin to value which is middle of it's bin
    void grade(int bonsCount);

    bool operator==(const CArray&);
};

#ifndef NOT_QT_AVAILABLE
inline QDebug operator<<(QDebug out, const CArray& m)
{
    switch (m.size()) {
    case 0:
        out << "CArray( 0 ) { }";
        return out;
    case 1:
        out << "CArray( 1 ) {" << m.front() << "}";
        return out;
    case 2:
        out << "CArray( 2 ) {" << m[0] << ',' << m[1] << "}";
        return out;
    case 3:
        out << "CArray( 2 ) {" << m[0] << ',' << m[1] << ',' << m[2] << "}";
        return out;
    case 4:
        out << "CArray( 2 ) {" << m[0] << ',' << m[1] << ',' << m[2] << ',' << m[3] << "}";
        return out;
    case 5:
        out << "CArray( 2 ) {" << m[0] << ',' << m[1] << ',' << m[2] << ',' << m[3] << ',' << m[4] << "}";
        return out;
    case 6:
        out << "CArray( 2 ) {" << m[0] << ',' << m[1] << ',' << m[2] << ',' << m[3] << ',' << m[4] << ',' << m[5] << "}";
        return out;
    default:
        out << "CArray(" << m.size() << ") {" << m[0] << ',' << m[1] << ',' << m[2]
            << "..." << m[m.size() - 3] << ',' << m[m.size() - 2] << ',' << m[m.size() - 1] << "}";
        return out;
    }
}

inline QDataStream& operator<< (QDataStream& out, const CArray& m) {
    out << static_cast<const quint32>(m.size());
    const int writed(out.writeRawData(static_cast<const char*>(static_cast<const void*>(m.data())), m.size() * sizeof(CArray::value_type)));
    if (writed == static_cast<int>(m.size() * sizeof(CArray::value_type))) {
        out.setStatus(QDataStream::WriteFailed);
    }
    return out;
}

inline QDataStream& operator>> (QDataStream& in, CArray& m) {
    quint32 size;
    in >> size;
    m.resize(size);
    const int readed(in.readRawData(static_cast<char*>(static_cast<void*>(m.data())), m.size() * sizeof(CArray::value_type)));
    if (readed != static_cast<int>(m.size() * sizeof(CArray::value_type))) {
        in.setStatus(QDataStream::ReadCorruptData);
    }
    return in;
}
#endif //NOT_QT_AVAILABLE

#endif // CARRAY_H
