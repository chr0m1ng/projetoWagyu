#include "haralick.h"

Haralick::~Haralick()
{
}

void Haralick::calcularMatrizCoN(double * __restrict__ matrizCoN, int distancia)
{
    int imgLin = this->altura;
    int imgCol = this->largura;
    unsigned short * __restrict__ mIMG = this->matrizImg;

    const int N = this->Ng;

    int * __restrict__ matrizCoF = new int[N*N];

    this->distancia = distancia;

    int num_threads = 0;
       #pragma omp parallel
           num_threads = omp_get_num_threads();
    std::cout<< "Threads: "<< num_threads << std::endl;

    int **mc;
    mc = new int*[num_threads];
    for(int i = 0; i < num_threads; i++)
        mc[i] = new int[N*N];

    #pragma omp parallel
    {
        int tid = omp_get_thread_num();
        #pragma omp for
        for(int i = 0; i < imgLin; ++i)
        {
            for(int j = 0; j < imgCol; ++j)
            {

                mc0_    (mIMG, i, j, mc[tid]);
                mc45_   (mIMG, i, j, mc[tid]);
                mc90_   (mIMG, i, j, mc[tid]);
                mc135_  (mIMG, i, j, mc[tid]);
            }
        }
    }

   #pragma omp parallel for
   for (int i = 0; i < N; ++i)
       for (int j = 0; j < N; ++j)
           for(int k = 1; k < num_threads; k++)
               mc[0][i*N + j] += mc[k][i*N + j];

   //Transposta
    #pragma omp parallel for
    for (int i = 0; i < N; ++i)
    {
        #pragma omp simd
        for (int j = 0; j < N; ++j)
            matrizCoF[i*N + j] = mc[0][i*N + j] + mc[0][j*N + i];
    }

    // Normalizacao

    const int TAM_TOTAL = N*N;
    int soma = 0;

    #pragma omp parallel for simd reduction(+:soma)
    for(int i = 0; i < TAM_TOTAL; ++i)
        soma += matrizCoF[i];

    std::cout<< "Soma CPU: " << soma << std::endl;

    #pragma omp parallel for simd
    for(int i = 0; i < TAM_TOTAL; ++i)
        matrizCoN[i] = 1.0*matrizCoF[i] / soma;

    delete [] matrizCoF;


}

inline void Haralick::mc0_(unsigned short * __restrict__ mIMG, int i, int j, int* matrizCoTmp)
{
    int k = j + distancia;

    if (k < largura)
    {
        int z1 = mIMG[ i*largura + j];
        int z2 = mIMG[ i*largura + k];

        int pos = z1*Ng + z2;

        matrizCoTmp[pos] += 1;
    }
}

inline void Haralick::mc45_(unsigned short * __restrict__ mIMG, int i, int j, int* matrizCoTmp)
{
    int ii = i - distancia;
    int jj = j + distancia;

    if (jj < largura && ii >= 0)
    {
        int z1 = mIMG[i*largura + j];
        int z2 = mIMG[ii*largura + jj];

        int pos = z1*Ng + z2;

        matrizCoTmp[pos] += 1;
    }

}

inline void Haralick::mc90_(unsigned short * __restrict__ mIMG, int i, int j, int* matrizCoTmp)
{
    int ii = i - distancia;

    if (ii >= 0 && ii < altura )
    {
        int z1 = mIMG[i*largura + j];
        int z2 = mIMG[ii*largura + j];

        int pos = z1*Ng + z2;

        matrizCoTmp[pos] += 1;
    }
}

inline void Haralick::mc135_(unsigned short * __restrict__ mIMG, int i, int j, int* matrizCoTmp)
{
    int ii = i - distancia;
    int jj = j - distancia;

    if (jj >= 0 && ii >= 0)
    {
        int z1 = mIMG[i*largura + j];
        int z2 = mIMG[ii*largura + jj];

        int pos = z1*Ng + z2;

        matrizCoTmp[pos] += 1;
    }
}

double Haralick::P_x_mais_y(const double * __restrict__ p, const int k, int tam)
{
    double result = 0.0;

    for (int i=0; i < tam; ++i)
    {
        #pragma omp simd reduction(+:result)
        for (int j=0; j < tam; ++j)
            if ( (i + j) == k)
                result += p[i * tam + j];
    }

    return result;
}

