#include "csize.h"

CSize::CSize() {}
CSize::CSize(const CSize& s) : w(s.w), h(s.h) {}
CSize::CSize(int width, int height) : w(width), h(height) {}

CSize::~CSize() { }

void CSize::setWidth(const int width)
{
    w = width;
}

void CSize::setHeight(const int height)
{
    h = height;
}

int CSize::width() const
{
    return w;
}

int CSize::height() const
{
    return h;
}
