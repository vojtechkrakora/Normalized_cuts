
/* FIT 2014 -  some usefull mathematical methods, mostly from Numerical Recipies in C++ */

#ifndef maths_c
#define maths_c

#include <cmath>
    /* \brief rounding of doubles. round() is not standard on some systems, thus we have re-implemented it */
    /* double round(double arg); not necessary ? */

#ifdef MISSING_MATHSF_FUNCTIONS
    float fabsf (float x);
    float sqrtf (float x);
    float cosf (float x);
    float sinf (float x);
    float logf (float x);
    float log10f (float x);
#endif



    float betacf(float a, float b, float x);
    float betai(float a, float b, float x);
    void  choldc(float **a, int n, float p[],int ExitOnError=1);
    void  cholinv(float **a, int n, float p[]);
   
    void  matrixTrans(float **a, int n);
    void  cholmul(float **a, int n, float p[]);
   
    void  cholsl(float **a, int n, float p[],float b[], float x[]);
   
template <class TREAL>   // float | double
    void  covsrt(TREAL ** covar, int ma,int lista[], int mfit);
    float erfcc(float x);
    float gammln(float xx);
template <class TREAL>   // float | double
    int   gaussj(TREAL **a,int n,TREAL **b,int m);
    //int   gaussj2(double **a,int n,double **b,int m);
template <class TREAL>   // float | double
    void  lfit(float x[],float y[],float sig[],int ndat, float a[],
         int ia[], int ma,TREAL** covar,float* chisq,
         void (*funcs)(float,TREAL [],int) ); /*!< \brief  LS fitting using Normal equations */
    //void  lfit2(float x[],float y[],float sig[],int ndat, float a[],
    //     int ia[], int ma,double** covar,float* chisq,
    //     void (*funcs)(float,double [],int) ); /*!< \brief  The same as 'lfit' only 'covar' matrix is defined as double intead of float to suppres overflowing. */

    void svdfit(float x[], float y[], float sig[], int ndata, float a[], int ma, float **u, float **v, float w[], float *chisq, void (*funcs)(float, float [], int)); /*! \brief LS fitting using SVD */

inline   float MAXIMUM(float a, float b) {  return(a > b ? a : b); }
inline   float MINIMUM(float a, float b) {  return(a < b ? a : b); }
inline   float SIGN(float a, float b) { return((b) >= 0.0 ? fabs(a) : -fabs(a)); }


    void  pearsn(float x[], float y[], int n, float* r, float* prob, float* z);
    float PYTHAG(float a, float b);
    float SIGN(float a, float b);
    void  svdcmp(float **a,int m,int n,float *w,float **v); /*!< \brief SVD - singular values decomposition - Numerical Recepises*/
    void svbksb(float **u, float w[], float **v, int m, int n, float b[], float x[]); /*!< \brief Solves linear equations from U W V. Use after eigennumbers zeroing!*/
    int   ipow(int base,int exp); /*!< \brief Compute root of base by integer number 'exp' */
    float sqr(float base); /*!< returns base^2 */

template <class TREAL>   // float | double
    void  lubksb(TREAL **a,int n,int *indx,TREAL b[], const int idxshift=1); // from TBImage
template <class TREAL>   // float | double
    void  ludcmp(TREAL **a,int n,int *indx,TREAL *d, const int idxshift=1); // from TBImage
template <class TREAL>   // float | double
    void  minv(TREAL **a,int n, const int idxshift=1); /*!< \brief Computes inverze of symetric matrix */ // from TBImage
template <class TREAL>   // float | double
    TREAL determinant(TREAL **a,int n, const int idxshift=1); /*!< returns determinant of the matrix a*/
template <class TREAL>   // float | double
    TREAL determinant_abs05(TREAL **a,int n, const int idxshift=1); /*!< returns sqrt of determinant of the matrix a*/

    void matrixPri(float **a,char* name, int n, int m);
    /*!< \brief matrix print */
    void matrixPri(float *a,char* name, int n);
    void  gfirstm(float ***ma,float *mv,float **mafm, int NoOfPlanes, int nrl, int ncl); // firstm from TATransf
    void  gmidvalue(float ***ma,float *mv, int NoOfPlanes, int nr, int nc); // midvalue from TATransf
template <class TREAL>   // float | double
    void  jacobi(TREAL **a,int n,TREAL d[],TREAL **v,int *nrot); // from TATransf

    void normalize(float **Arr,int StartRow,int EndRow,int StartColumn,int EndColumn,float AktMinimum,float AktDifference, float NewMinimum,float NewDifference,float NewVariance);
    void  gnormreal255(float **Mat, int nr, int nc, int const*const* invMask = 0); // normreal255 from TAPS
    void  gnormreal255(float ***Mat, int NoOfPlanes, int nr, int nc, float *norm_shift, float *norm_range, int const*const* invMask = 0); // normreal255 from TATransf
    void  gdenormreal255(float ***Mat, int NoOfPlanes, int nr, int nc, float *norm_shift, float *norm_range, int const*const* invMask = 0); // denormreal255 from TBImage, originally from TSTransf
    void  gdenormreal(float ***Mat, int NoOfPlanes, int nr, int nc, float *norm_shift, float *norm_range, int const*const* invMask = 0); // denormreal255 from TBImage, originally from TSTransf
    void  gcutreal255(float ***Mat, int NoOfPlanes, int nr, int nc, int const*const* invMask = 0); // cutreal255 from TBImage

    void hist_equal(float **arr, int nr, int nc, int nrf=0, int nrl=-1, int ncf=0, int ncl=-1);

    void MatHist(float ***mainarr,int NoOfPlanes, int nr, int nc, const char *Coment);
    void MatHistCut(float ***mainarr, int NoOfPlanes, int nr, int nc, float Perc,const char *Coment,int PrintHistogram = 0);
    void MatHistPrint(float ***mainarr, int NoOfPlanes, int nr, int nc, const char *Coment);
    void MatStat(float ***mainarr,int NoOfPlanes, int nr, int nc, const char *Coment, int const*const* invMask = 0);
    void MatStat(float **mainarr, int nrf, int nrl, int ncf, int ncl, const char *Coment, int const*const* invMask = 0);

    /*! \brief The class collects static structures and routines for random generators*/
    class RandGen{
      protected:
        static int iset;
        static float gset;
        static long ix1,ix2,ix3;
        static float r[98];
        static int iff;
       //XS: shadow variables for context switching
        int _saved; int _iset; float _gset; long _ix1,_ix2,_ix3; float _r[98]; int _iff;
      public:
       //XS: context switching
        void init_ctx(); void save_ctx(); void load_ctx();
        RandGen(int save, int init=1) { init_ctx(); if (save) save_ctx(); if (init) initstatic(); };
        ~RandGen() { if (_saved) load_ctx(); }
       //XS: -----------------
        RandGen(){initstatic();init_ctx();};
        static float ran1(int *idum);
        static float gasdev(int *idum);
        static void initstatic();
        static float poidev(float xm, int *idum);
    };
    float gauss_mix(int *idum, int k, float *p, float *mu, float *sigma);
    int gauss_mix(int *idum, int k, int n, float *p, float **mean, float ***cov, float *vec);
    /** WARNING: In gauss functions, ncl, nrl indexes are ommited that differs from behaviour of Prog.cpp functions !!!*/
    int gauss(int lf,int nrf,int nrl,int ncf, int ncl,float ***a,float* mean,float** cov,int ExitOnError=1,int Seed=0);
    int gauss(int nrf,int nrl,int ncf, int ncl,float **a);

    int dis_gen(float *prob, int nlev, int *idum);
    void fourn(float data[],int nn[],int ndim,int isign); /*!< \brief Computes n-dimensional FFT - Numerical Recepises */
    void fourn(float data[],int nn1,int nn2,int isign); /*!< \brief Computes n-dimensional FFT - Numerical Recepises */

    void rlft3(float ***data, float **speq, unsigned long nn1, unsigned long nn2, unsigned long nn3, int isign); /*!< \brief Function computes FFT (uses routine "fourn") -  Numerical Recepises */
    /*! \brief Creates real and imaginary image of FFT coef. with the lowest frequncy in the center*/

    void FFTCoefWraparound(float ***data, float **coefRe, float **coefIm, int nr, int nc, int direct);
//  void FFTCoefWraparound(float ***data, TBImage3 *coefRe, TBImage3 *coefIm, int nr, int nc, int direct);
    /*! \brief Cuts specified part of FFT spectrum */
    void FFTImageFilter(float ***data, int pixelsLeft, int nr, int nc, int lowPass);

    /*! \brief compute fourier amplitude spectrum of given image layer defined by "isp" */
    void FFTamplitude(float ***image, float **spectrum, int nr, int nc, int isp);

    /*! \brief Returns accumulator matrix (image) computed by Hough transformation */
    void HoughTransform(float **binary, float **hough_space, int nr, int nc, int thetas, int rhos);

//    void eigs_nopivot(float **a, int n, float wr[], float wi[]);
template <class TREAL>   // float | double
    void eigsrt(TREAL d[],TREAL **v,int n); /*!< \brief Sorts eigennumbers according to their size - Numerical Recepises */

    void quickSort(int l,int r,float *data); /*!< \brief Fast routine for sorting of 1 dimensional float array of numbers */

    void quickSort(int l,int r,float *data,int *pos); /*!< \brief Fast routine for sorting of 1 dimensional float array of numbers and it gives number position in unsorted array in "pos"*/

    int round(float co); /*!< \brief Function simply rounds float numbers */

    void MatrixMultipl(float **ma1, int nr1,int nc1,float **ma2, int nr2, int nc2, float **result);

    void MatrixMultipl(float **ma1,int nr1,int nc1,float **ma2,int nc2,float **result);

    //! \brief Matrix multiplication with progress outprint
    void MatrixMultiplPrintProgress(float **ma1,int nr1,int nc1,float **ma2,int nr2,int nc2,float **result);

    //! \brief computin symmetric matrix with progress outprint
    void SymMatrixMultiplPrintProgress(float **ma, int nr, int nc, float **result);

    void MatrixTrMultipl(float **ma1,int nr1,int nc1,float **ma2,int nr2,
                 int nc2, float **result);

    void mrqcof(float **x, float y[], float sig[], int ndata, float a[], int ia[], int ma, float **alpha, float beta[], float *chisq, void (*funcs)(float **, int,  float [], float *, float [], int)); /*!< \brief Levenberg-Marquardt non linear parameters estimation routine - Numerical recepises */

    void mrqmin(float **x, float y[], float sig[], int ndata, float a[], int ia[], int ma, float **covar, float **alpha, float *chisq, void (*funcs)(float **, int, float [], float *, float [], int), float *alamda); /*!< \brief Levenberg-Marquardt non linear parameters estimation routine (uses routine "mrqcof" - Numerical recepises */

    /*! \brief Kullback-Leiber distance of two distributions 'A' and 'B' of 'n' bins */
    float distKullbackLeiber(float *A, float *B, int n);
    /*! \brief Jeffrey distance of two distributions 'A' and 'B' of 'n' bins */
    float distJeffrey(float *A, float *B, int n);

    //##### COLOURSPACE CONVERSION ###############################################

    /*! \brief Conversion from RGB into CIE XYZ (D65) color space */
    int RGB2XYZ(float *R, float *G, float *B);
    /*! \brief Conversion from CIE XYZ (D65) into RGB color space */
    int XYZ2RGB(float *X, float *Y, float *Z);

    int RGB2LogLuv(float *R, float *G, float *B);
    int LogLuv2RGB(float *L, float *u, float *v);
    int RGB2YUV(float *R, float *G, float *B);
    int YUV2RGB(float *Y, float *U, float *V);

int RGB2LogLuv(const float RGB[], float Luv[]);
int LogLuv2RGB(const float Luv[], float RGB[]);
int RGB2YUV(const float RGB[], float YUV[]);
int YUV2RGB(const float YUV[], float RGB[]);

    /*! \brief Conversion from CIE XYZ (D65) into CIE LAB (D65) color space */
    int XYZ2Lab(float *X, float *Y, float *Z);
    /*! \brief Conversion from CIE LAB (D65) into CIE XYZ (D65) color space */
    int Lab2XYZ(float *L, float *a, float *b);

    int CIE76_L_from_Y(double Y, double Yn, double * L);
    int CIE76_Y_from_L(double L, double Yn, double * Y);
    int XYZ76_Lab(double  X,  double Y,  double Z,
                double  Xn, double Yn, double Zn,
                double *L,  double *a, double *b,
                double *h_ab,          double *Chroma_ab);
    int Lab76_XYZ(double  L,  double a,  double b,
                double  Xn, double Yn, double Zn,
                double  *X, double *Y, double *Z);
    void Lab_diff(double L_samp, double a_samp, double b_samp,
                  double L_std, double a_std, double b_std,
                  double *DE, double *DC, double *DH, double *DEexp );

    int CIE00_L_from_Y(double Y, double Yn, double * L);
    int CIE00_Y_from_L(double L, double Yn, double * Y);
    int XYZ00_Lab(double  X,  double Y,  double Z,
                double  Xn, double Yn, double Zn,
                double *L,  double *a, double *b,
                double *h_ab,          double *Chroma_ab);
    int Lab00_XYZ(double  L,  double a,  double b,
                double  Xn, double Yn, double Zn,
                double  *X, double *Y, double *Z);

    void HSV2RGB( float h, float s, float v, float *r, float *g, float *b );
    int RGB2Opponent( float r, float g, float b, float *o1, float *o2, float *o3 );

    /*! \brief Pixelwise image conversion from RGB int CIE XYZ (D65) colourspace
    "actualPlane" specifies which RGB tripple should be converted into CIE XYZ */
    int imgRGB2XYZ(float ***img, int nr, int nc, int actualPlane=0);
    /*! \brief Pixelwise image conversion from CIE XYZ (D65) into RGB colourspace
    "actualPlane" specifies which CIE XYZ tripple should be converted into RGB */
    int imgXYZ2RGB(float ***img, int nr, int nc, int actualPlane=0);
    /*! \brief Pixelwise image conversion from RGB int CIE Lab (D65) colourspace
    "actualPlane" specifies which RGB tripple should be converted into CIE Lab */
    int imgRGB2Lab(float ***img, int nr, int nc, int actualPlane=0);
    /*! \brief Pixelwise image conversion from CIE Lab (D65) into RGB colourspace
    "actualPlane" specifies which CIE Lab tripple should be converted into RGB */
    int imgLab2RGB(float ***img, int nr, int nc, int actualPlane=0);

    int imgRGB2Lab2000(float ***img, int nr, int nc, int actualPlane=0);
    int imgLab20002RGB(float ***img, int nr, int nc, int actualPlane=0, int cutValues=1);

    int imgRGB2Opponent(float ***img, int nr, int nc, int actualPlane=0);

    /*! \brief Computes L2 distance between two colours in CIELab space */
    float distCIELab(float L1, float a1, float b1, float L2, float a2, float b2);

//#### 1D and 2D SPLINES #############################################

/*! \brief Given arrays x[1..n] and y[1..n] containing a tabulated function,i.e. y_i=f(x_i), with
x1<x2<..<xN, and given values yp1 and ypn for the first derivative of the interpolating
function at points 1 and n, respectively, this routine returns an array y2[1..n] that
contains the second derivatives of the interpolating function at the tabulated points x_i.
If yp1 and/or ypn are equal to 1 x 10^30 or larger, the routine is signaled to set the
corresponding boundary condition for a natural spline, with zero second derivative on
that boundary. JF*/
void spline(float x[], float y[], int n, float yp1, float ypn, float y2[]);

  /*! \brief  Given the arrays xa[1..n] and ya[1..n], which tabulate a function (with the xa_i's
     in order), and given the array y2a[1..n], which is the output from "spline()" above,
     and given a value of x, this routine returns a cubic-spline interpolated value y. JF */
void splint(float xa[], float ya[], float y2a[], int n, float x, float *y);

  /*! \brief  Given an m by n tabulated function ya[1..m][1..n], and tabulated independent
variables x2a[1..n], this routine constructs one-dimensional natural cubic splines
of the rows of ya and returns the second-derivatives in the array y2a[1..m][1..n].
(The array x1a[1..m] is included in the argument list merely for consistency with
routine "splin2()"). JF */
void splie2(float x1a[], float x2a[], float **ya, int m, int n, float y2[]);

  /*! \brief  Given x1a, x2a,ya, m,n as described in "splie2()" and y2a as produced by that routine;
and given a desired interpolating point x1,x2; this routine returns an interpolated function
value y by cubic spline interpolation. JF*/
void splin2(float x1a[], float x2a[], float **ya, float **y2a, int m, int n, float x1, float x2, float *y);

    //################## from mRoller ###########################
    int IsMin(float** I, int nr, int nc, int x, int y, int size);
    float min(float *A, int l, int r);
    float max(float *A, int l, int r);

    float min(float a, float b);
    float max(float a, float b);

    float maxInArray(float **A, int l1, int r1, int l2, int r2, int &i1, int &i2);
    float maxInRow(float **A, int row, int l, int r, int &index);
    float maxInCol(float **A, int col, int l, int r, int &index);

/**Given a matrix a[1..n][1..n], this routine replaces it by a balanced matrix with identical eigenvalues. A symmetric matrix is already balanced and is unaffected by this procedure. */
template <class TREAL>   // float | double
    void balanc(TREAL **a, int n);
/**Reduction to Hessenberg form by the elimination method. The real, nonsymmetric matrix a[1..n][1..n] is replaced by an upper Hessenberg matrix with identical eigenvalues. Recommended, but not required, is that this routine be preceded by balanc.*/
template <class TREAL>   // float | double
    void elmhes(TREAL **a, int n);
/** \brieaf Finds all eigenvalues of an upper Hessenberg matrix a[1..n][1..n]. The real and imaginary parts of the eigenvalues are returned in wr[1..n] and wi[1..n], respectively. Marix a is destroyed!*/
template <class TREAL>   // float | double
    void hqr(TREAL **a, int n, TREAL wr[], TREAL wi[]);
/** \brief Sort singular values in W from the biggest to the lowest and swap related vectors in U and V */
template <class TREAL>   // float | double
    void svdsrt(  TREAL ** u, TREAL *w, TREAL ** v, int nr, int nc );
/**All eigenvalues of square real, even nonsymetrix matrix a[1..n][1..n]. QR decomposition based method. Real and imaginar parts of eigenvalues are strored in wr[1..n] and wi[1..n], respectively. Marix a is destroyed!*/
template <class TREAL>   // float | double
    void eigs_qr(TREAL **a, int n, TREAL wr[], TREAL wi[], bool sort);
/** Sorts eigenvalues accoding to its absolute values (desceding), both [1..n] */
template <class TREAL>   // float | double
    void eigsrt(TREAL *wr, TREAL *wi, int n);

//    bool gauss_nopivot(float **a, int n);

/** \brief Two vectors of length 3 difference. */
    void vec_diff(float *x, float *y, float *res);
/** \brief 3D vector length. */
    float vec_len(float *x);
/** \brief Two vectors of length 3 cross product. */
    void vec_crossprod(float *x, float *y, float *res);
/** \brief 3D vector normalization. */
    int vec_norm(float *x);
/** \brief Trims the numrer into specified interval */
    void range(float *data, float low, float high);

// \brief  template functions for linear (lsfit) and non-linear (mrqcof,mrqmin) optimization
//==========================================================================================

template <class TREAL>   // float | double
void fpoly(float x, TREAL p[], int np);
//void fpolyd(float x, double p[], int np);

void fbrdf(float **x, int j, float a[], float *y, float dyda[], int na);

void fbrdf_iv(float **x, int j, float a[], float *y, float dyda[], int na);

void RGBtoYCbCr(const float RGB[], float YCbCr[]);
void YCbCrtoRGB(const float YCbCr[], float RGB[]);


inline float signum( const float x ) { if (x>0) return 1; else if (x==0) return 0; else return -1; };

#endif
