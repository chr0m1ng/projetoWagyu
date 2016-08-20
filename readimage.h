#ifndef READIMAGE_H
#define READIMAGE_H

#include <QString>
#include "globalvar.h"

class ReadImage
{
private:
    const char * fileName   = NULL;
    int coluna;
    int linha;
public:
    ReadImage(QString fileName, unsigned short int coluna, unsigned short int linha);
    tImage vectorImage();
    tImage vectorImage_();
};

#endif // READIMAGE_H

