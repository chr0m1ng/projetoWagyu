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

double Haralick::mediaH(const double * __restrict__ p, int tam)
{
    double soma = 0.0;

    #pragma omp parallel for reduction(+:soma)
    for (int i = 0; i < tam; ++i)
    {
        double soma1 = 0.0;
        #pragma omp simd reduction(+:soma1)
        for (int j = 0; j < tam; ++j)
            soma1 += i * p[i * tam + j];
        soma += soma1;
    }

    return soma;
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

double Haralick::P_x_menos_y(const double * __restrict__ p, const int k, int tam)
{
    double result = 0.0;

    for (int i=0; i < tam; ++i)
    {
    #pragma omp simd reduction(+:result)
        for (int j=0; j < tam; ++j)
            if ( std::abs(i - j) == k)
                result += p[i * tam + j];
    }

    return result;
}

/*
 * Haralick
 */

double Haralick::energia()
{
    int tTotal = this->Ng * this->Ng;
    double energia = 0.0;
    const double * __restrict__ matrizCoN = this->matriz;

    #pragma omp parallel for simd reduction(+:energia)
    for(int i = 0; i < tTotal; ++i)
        energia +=  matrizCoN[i] * matrizCoN[i];

    return energia;
}

double Haralick::contraste()
{
    const int tam = this->Ng;
    double contraste = 0.0;
    const double * __restrict__ matrizCoN = this->matriz;

    #pragma omp parallel for reduction(+:contraste)
    for (int i = 0; i < tam; ++i)
    {
        double con = 0.0;
        #pragma omp simd reduction(+:con)
        for(int j = 0; j < tam; ++j)
            con += ( std::abs(i - j) * std::abs(i - j)) * matrizCoN[i * tam + j];
        contraste += con;
    }

    return contraste;
}

double Haralick::correlacao()
{
    const int tam = this->Ng;
    double cor = 0.0;
    double var = 0.0;
    const double * __restrict__ matrizCoN = this->matriz;

    double media = this->mediaH(matrizCoN, tam);

    #pragma omp parallel for reduction(+:cor,var)
    for (int i = 0; i < tam; ++i)
    {
        double var1 = 0.0;
        double cor1 = 0.0;
        double tmp = (i - media) * (i - media);
        #pragma omp simd reduction(+:var1,cor1)
        for (int j = 0; j < tam; ++j)
        {
            cor1 += (i - media) * (j - media) * matrizCoN[i * tam + j];
            var1 += tmp * matrizCoN[i * tam + j];
        }
        var += var1;
        cor += cor1;
    }

    return cor/var;
}


double Haralick::variancia()
{
    const int TAM = this->Ng;
    double variancia = 0.0;
    const double * __restrict__ matrizCoN = this->matriz;

    double media = this->mediaH(matrizCoN, TAM);

    #pragma omp parallel for reduction(+:variancia)
    for (int i = 0; i < TAM; i++)
    {
        double var = 0.0;
        double tmp = (i - media) * (i - media);
        #pragma omp simd reduction(+:var)
        for(int j = 0; j < TAM; j++)
            var += tmp * matrizCoN[i * TAM + j];
        variancia += var;
    }

    return variancia;
}

double Haralick::mdi()
{
    const int tam = this->Ng;
    double mdi = 0.0;
    const double * __restrict__ matrizCoN = this->matriz;

    #pragma omp parallel for reduction(+:mdi)
    for(int i = 0; i < tam; ++i)
    {
        double mdi1 = 0.0;
        #pragma omp simd reduction(+:mdi1)
        for(int j = 0; j < tam; ++j)
            mdi1 += ( matrizCoN[i * tam + j] / (1 + ((i - j)*(i - j)) ) );
        mdi += mdi1;
    }

    return mdi;
}

double Haralick::mediaSoma()
{
    int tam = this->Ng;
    int tTotal = (2*tam) - 2;
    double resultado = 0.0;
    const double * __restrict__ matrizCoN = this->matriz;

    #pragma omp parallel for reduction(+:resultado)
    for (int k = 0; k <= tTotal; ++k)
        resultado += k * P_x_mais_y(matrizCoN, k, tam);

    return resultado;
}

double Haralick::varianciaSoma()
{
    int tam = this->Ng;
    int tTotal = (2*tam) - 2;
    double mediaS = 0.0;
    double varSoma = 0.0;
    const double * __restrict__ matrizCoN = this->matriz;

    mediaS = mediaSoma();

    #pragma omp parallel for reduction(+:varSoma)
    for (int k = 0; k <= tTotal; ++k)
        varSoma += (k - mediaS) * (k - mediaS) * P_x_mais_y(matrizCoN, k, tam);

    return varSoma;
}

double Haralick::somaEntropia()
{
    int tam = this->Ng;
    const int tTotal = (2*tam) - 2;
    double somaEnt = 0.0;
    const double * __restrict__ matrizCoN = this->matriz;

    #pragma omp parallel for reduction(+:somaEnt)
    for (int k = 0; k <= tTotal; ++k)
    {
        double tmp = P_x_mais_y(matrizCoN, k, tam);
        if (tmp > 0.0)
            somaEnt += tmp * log(tmp);
    }

    return (-1.0) * somaEnt;
}

double Haralick::entropia()
{
    const int tTotal = Ng * Ng;
    double entropia = 0.0;
    const double * __restrict__ matrizCoN = this->matriz;


    #pragma omp parallel for simd reduction(+:entropia)
    for (int i = 0; i < tTotal; ++i)
    {
        double valor = matrizCoN[i];
        entropia += (valor > 0.0) ? valor * log(valor) : 0.0;
    }

    return entropia * (-1.0);
}

double Haralick::varianciaDiferenca()
{
    double * __restrict__ pxmy_temp = new double[Ng];
    double resultado = 0.0;
    const double * __restrict__ matrizCoN = this->matriz;


/****/
    #pragma omp parallel for
    for (int k = 0; k < Ng; ++k)
        pxmy_temp[k] = P_x_menos_y(matrizCoN, k, Ng);
/****/

    #pragma omp parallel for simd reduction(+:resultado)
    for (int k=0; k < Ng; ++k)
        resultado += ( (k - k*pxmy_temp[k])*(k - k*pxmy_temp[k]) ) * pxmy_temp[k] ;

    return resultado;
}

double Haralick::diferencaEntropia()
{
    int tam = this->Ng;
    double difEnt = 0.0;
    const double * __restrict__ matrizCoN = this->matriz;


    #pragma omp parallel for reduction(+:difEnt)
    for (int k = 0; k < tam; ++k)
    {
        double tmp = P_x_menos_y(matrizCoN, k, tam);
        if (tmp > 0.0)
            difEnt += tmp * log(tmp);
    }

    return (-1.0) * difEnt;
}

double Haralick::px(int i)
{
    int tam  = this->Ng;
    double px = 0.0;
    const double * __restrict__ matrizCoN = this->matriz;

    #pragma omp parallel for reduction(+:px)
    for(int k = 0; k < tam; ++k)
        px += matrizCoN[i * tam + k];
    return px;
}

double Haralick::py(int j)
{
    int tam = this->Ng;
    double py = 0.0;
    const double * __restrict__ matrizCoN = this->matriz;

    #pragma omp parallel for reduction(+:py)
    for(int k = 0; k < tam; ++k)
        py += matrizCoN[k * tam + j];
    return py;
}

double Haralick::hx()
{
    int tam = this->Ng;
    double hx = 0.0;
    double rpx = 0.0;

    #pragma omp parallel for reduction(+:hx) private(rpx)
    for(int h = 0; h < tam; ++h)
    {
        rpx = px(h);
        if(rpx)
            hx += rpx * log(rpx);
    }

    return hx * -1;
}

double Haralick::hy()
{
    int tam = this->Ng;
    double hy = 0.0;
    double rpy = 0.0;

    #pragma omp parallel for reduction(+:hy) private(rpy)
    for(int h = 0; h < tam; ++h)
    {
        rpy = py(h);
        if(rpy)
            hy += rpy * log(rpy);
    }
    return hy * -1;
}

double Haralick::hxy()
{
    int tTotal = this->Ng * this->Ng;
    double hxy = 0.0;
    double rlog = 0.0;
    const double * __restrict__ matrizCoN = this->matriz;
    #pragma omp parallel for reduction(+:hxy) private(rlog)
    for(int k = 0; k < tTotal; ++k)
        if(matrizCoN[k])
        {
            rlog = log(matrizCoN[k]);
            hxy += matrizCoN[k] * rlog;
        }
    return hxy * -1;
}

double Haralick::hxy1()
{
    int tam = this->Ng;
    double hxy1 = 0.0;
    const double * __restrict__ matrizCoN = this->matriz;

    #pragma omp parallel for reduction(+:hxy1)
    for(int k = 0; k < tam; ++k)
        for(int h = 0; h < tam; ++h)
            if(px(k) && py(h))
                hxy1 += matrizCoN[k * tam + h] * log(px(k) * py(h));
    return hxy1 * -1;
}

double Haralick::hxy2()
{
    int tam = this->Ng;
    double hxy2 = 0.0;
    double rpx = 0.0;
    double rpy = 0.0;
    double rlog = 0.0;

    #pragma omp parallel for reduction(+:hxy2) private(rpx, rpy, rlog)
    for(int k = 0; k < tam; ++k)
    {
        for(int h = 0; h < tam; ++h)
        {
            rpx = px(k);
            rpy = py(h);
            if(rpx && rpy)
            {
                rlog = log(rpx * rpy);
                hxy2 += rpx * rpy * rlog;
            }
        }
    }
    return hxy2 * -1;
}

double Haralick::medidasCorrelacao1()
{
    double rhxy1 = 0.0;
    double mc = 0.0;

    rhxy1 = hxy1();
    mc = (entropia() - rhxy1) / std::max(hx(), hy());

    return mc;
}

double Haralick::medidasCorrelacao2()
{
    double mc = 0.0;
    double rhxy2 = 0.0;

    rhxy2 = hxy2();

    mc = std::sqrt(1 - std::exp(-2 * abs(rhxy2 - entropia())));

    return mc;
}
