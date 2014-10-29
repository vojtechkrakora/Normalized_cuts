
/* FIT 2014 - image I/O */

#ifndef pres2_c
#define pres2_c

#include "PresInfo.h"

template <class TYPE>
const char* pres_typeid_name(TYPE &x);

/*! the general image output routine
\note param  aux:  asrgb - EXR format;  nImage - NITF format
 * @return IMGIO_OK (0) in case of success*/
template <class TYPE>
int pres2(int key, TYPE*** ma, int* nc, int* nr, int* ncolour, int* nlevels, const char c[], int aux=-1);

int pres_header(const char* filename, int key=PRES_NO_KEY, int* nc=NULL, int* nr=NULL, int* np=NULL, int *flags=NULL);

template <class TYPE>
int pres2op(int key, TYPE*** a, int* nc, int* nr, int* ncolour, int* nlevels, const char c[], int oneplane=-1, int aux=-1) {
  TYPE  **sa=(oneplane<0)?(TYPE**)a:a[oneplane];    /* single-plane pointer */
  TYPE ***ma=(*ncolour==0)?&sa:(TYPE***)a;           /* multi-plane pointer */

  return pres2(key,ma,nc,nr,ncolour,nlevels,c,aux);
}


//TODO: pres_read, pres_write


#endif
