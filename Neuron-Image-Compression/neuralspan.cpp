#include "neuralspan.h"
#include <cstdlib>

NeuralSpan::NeuralSpan(int n, int l)
    : CMatrix(n, l)
{
    NeuralSpan& m(*this);
    for (double* it(m[0]), *end(m[m.height() - 1] + m.width()); it != end; ++it) {
        *it = rand() * 255.0 / RAND_MAX;
    }
}

