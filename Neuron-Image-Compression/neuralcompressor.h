#ifndef NEURALCOMPRESSOR_H
#define NEURALCOMPRESSOR_H
#ifdef QT_AVAILABLE
class QPixmap;
#endif
class TrainingSet;
#include "kernel/csize.h"
#include "neuralspan.h"
#include <map>

class NeuralCompressor
{
public:
    NeuralCompressor(const TrainingSet&, const int l, const CSize frameSize,  const CSize imageSize);

#ifdef QT_AVAILABLE
    QPixmap recoverQPixmap() const;
#endif

    static CMatrix::T ETA;

#ifdef ENABLE_PNG
    void saveAs(const char* fName, const char *exampleFName) const;
#endif
private:
    NeuralSpan weights;
    typedef std::multimap<int, int> Conformity;
    typedef std::pair<int, int> ConformityItem;
    Conformity conformity;

    const CSize image;
    const CSize frame;
};

#endif // NEURALCOMPRESSOR_H
