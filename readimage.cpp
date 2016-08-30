#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>

#include "readimage.h"
#include "hex2int.h"

using namespace std;

ReadImage::ReadImage(const char *fileName, unsigned short int width, unsigned short int length)
{
    this->fileName = fileName;
    this->coluna = width;
    this->linha = length;

    cout << fileName << endl;
}

tImage ReadImage::vectorImage() {

    tImage st_image;
    char *vc_bitsvalue =  new char [2];

    st_image.vi_coluna = this->coluna;
    st_image.vi_linha = this->linha;
    st_image.vi_vector = new unsigned short [st_image.vi_coluna * st_image.vi_linha];

    ifstream fp (this->fileName, ios_base::binary );

    for ( long int i = 0; i < (st_image.vi_coluna * st_image.vi_linha) ; i++ ) { //&& !fp.eof()
        fp.read(vc_bitsvalue, 2 * sizeof(char) );
        st_image.vi_vector[i] = (unsigned short) hex2int(vc_bitsvalue);
        //if (st_image.vi_vector[i] > 4095)
          //  cout << i << " -> " << st_image.vi_vector[i] << endl;
        //cout << st_image.vi_vector[i] << endl;
    }

    fp.close();

    return st_image;
}

tImage ReadImage::vectorImage_() {
    FILE *pFile = NULL;
    tImage st_image;

    st_image.vi_coluna = this->coluna;
    st_image.vi_linha = this->linha;
    st_image.vi_vector = new unsigned short [st_image.vi_coluna * st_image.vi_linha];

    pFile = fopen ( this->fileName , "rb" );
    if (pFile==NULL) {
        fputs ("File error",stderr);
        exit (1);
    }

    st_image.vi_vector = new unsigned short[st_image.vi_coluna * st_image.vi_linha];
    char *buffer =  new char [2];

    for ( long int i = 0; i < (st_image.vi_coluna * st_image.vi_linha) ; i++ ) {

        fread(buffer, sizeof(char), 2, pFile);

        st_image.vi_vector[i] = (unsigned short) hex2int(buffer);

        //cout << st_image.vi_vector[i] << endl;

        if (st_image.vi_vector[i] > 4095)
            cout << i << " -> " << st_image.vi_vector[i] << endl;
    }

    fclose(pFile);

    return st_image;
}
