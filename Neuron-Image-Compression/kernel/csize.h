#ifndef CSIZE_H
#define CSIZE_H


class CSize
{
public:
    CSize(const CSize&);
    CSize(int width, int height);
    CSize();
    ~CSize();

    void setWidth(const int width);
    void setHeight(const int height);
    int width() const;
    int height() const;
private:
    int w;
    int h;
};

#endif // CSIZE_H
