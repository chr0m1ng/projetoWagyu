#ifndef READIMAGE_H
#define READIMAGE_H

#include "globalvar.h"

class ReadImage
{
private:
    const char *fileName   = NULL;
    int coluna;
    int linha;
public:
    ReadImage(const char *fileName, unsigned short int coluna, unsigned short int linha);
    tImage vectorImage();
    tImage vectorImage_();
};

#endif // READIMAGE_H

