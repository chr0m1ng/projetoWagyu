/******************************************************************************************
 GLOBAL VAR FOR SEVERAL PROGRAMS 
******************************************************************************************/
#ifndef GLOBALVAR_H
#define GLOBALVAR_H

struct sImage {
    char *vc_filename;
    int  vi_coluna;  // largura (x)
    int  vi_linha; // comprimento (y)
    unsigned short *vi_vector;
    int  vi_bits;
};

typedef sImage tImage;

#endif
