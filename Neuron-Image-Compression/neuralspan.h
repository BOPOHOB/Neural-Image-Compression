#ifndef NEURALSPAN_H
#define NEURALSPAN_H

#include "kernel/cmatrix.h"
class CVector;

class NeuralSpan : public CMatrix
{
    mutable CVector potential;
public:
    NeuralSpan(int n, int l);

    //Euclidean norm between given vector and pointed row from valid CMatrix
    static double euclideanNorm(const CVector& synapse, const CMatrix::T* row);
    int nearest(const CVector& synapse) const;

    typedef std::pair<int, CMatrix::T> DistanceItem;
    typedef std::vector<DistanceItem> Distances;
    Distances distance(const CVector& sample);

    void clearPotential() const;
};

#endif // NEURALSPAN_H
