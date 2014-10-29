
/* FIT 2014 - memory allocation routines, array copying etc. */

#ifndef TBAlloc_c
#define TBAlloc_c

#ifndef _HPUX
#include <stdint.h>
#else
#include <inttypes.h>
#endif
#include <inttypes.h>


typedef uint8_t   byte;
typedef uint16_t  word;
typedef uint32_t  dword;


// real numbers

  float*     allocation1(int nrl,int nrh); /*!< \brief allocation of 1D float array [nrl..nrh] */
  float**    allocation2(int nrl,int nrh,int ncl,int nch); /*!< \brief allocation of 2D float array [nrl..nrh][ncl..nch] */
  float***   allocation3(int nmf,int nml,int nrl,int nrh,int ncl,int nch); /*!< \brief allocation of 3D float array [nmf..nml][nrl..nrh][ncl..nch] */
  float****  allocation4(int ntf,int ntl,int nmf,int nml,int nrl,int nrh,int ncl,int nch); /*!< \brief allocation of 4D float array [ntf..ntl][nmf..nml][nrl..nrh][ncl..nch] */
  float***** allocation5(int nff,int nfl, int ntf, int ntl, int nmf,int nml,int nrl,int nrh,int ncl,int nch); /*!< \brief Allocation of 5D float matrix... */
  float***   allocation13(int nrl,int nrh); /*!< \brief allocation of 1D float** array [nrl..nrh] */
  float****  allocation14(int nrl,int nrh); /*!< \brief allocation of 1D float*** array [nrl..nrh] */

  void       freemem1(float* &m,int nrl,int nrh); /*!< \brief frees memory allocated by allocation1 */
  void       freemem2(float** &m,int nrl,int nrh,int ncl,int nch); /*!< \brief frees memory allocated by allocation2 */
  void       freemem3(float*** &m,int nmf,int nml,int nrl,int nrh,int ncl,int nch); /*!< \brief frees memory allocated by allocation3 */
  void       freemem4(float**** &m,int ntf,int ntl,int nmf,int nml,int nrl,int nrh,int ncl,int nch); /*!< \brief frees memory allocated by allocation4 */
  void       freemem5(float *****&m,int nff,int nfl,int ntf, int ntl, int nmf,int nml,int nrf,int nrl,int ncf,int ncl); /*!< \brief Dellocation of 5D float matrix... */
  void       freemem13(float*** &m,int nrl,int nrh); /*!< \brief frees memory allocated by allocation13 */
  void       freemem14(float**** &m,int nrl,int nrh); /*!< \brief frees memory allocated by allocation14 */

  double*    dallocation1(int nrl,int nrh); /*!< \brief allocation of 1D double array [nrl..nrh] */
  double**   dallocation2(int nrl,int nrh,int ncl,int nch); /*!< \brief allocation of 2D double array [nrl..nrh][ncl..nch] */
  double***   dallocation3(int nmf,int nml,int nrl,int nrh,int ncl,int nch); /*!< \brief allocation of 3D double array [nmf..nml][nrl..nrh][ncl..nch] */
  double****  dallocation4(int ntf,int ntl,int nmf,int nml,int nrl,int nrh,int ncl,int nch); /*!< \brief allocation of 4D double array [ntf..ntl][nmf..nml][nrl..nrh][ncl..nch] */
  double***** dallocation5(int nff,int nfl,int ntf,int ntl,int nmf,int nml,int nrl,int nrh,int ncl,int nch); /*!< \brief Allocation of 5D double matrix... */

  void       freedmem1(double* &m,int nrl,int nrh); /*!< \brief frees memory allocated by dallocation1 */
  void       freedmem2(double** &m,int nrl,int nrh,int ncl,int nch); /*!< \brief frees memory allocated by dallocation2 */
  void       freedmem3(double*** &m,int nmf,int nml,int nrl,int nrh,int ncl,int nch); /*!< \brief frees memory allocated by dallocation3 */
  void       freedmem4(double**** &m,int ntf,int ntl,int nmf,int nml,int nrl,int nrh,int ncl,int nch); /*!< \brief frees memory allocated by dallocation4 */
  void       freedmem5(double *****&m,int nff,int nfl,int ntf, int ntl, int nmf,int nml,int nrf,int nrl,int ncf,int ncl); /*!< \brief Deallocation of 5D double matrix... */


// integers

  byte*    ballocation1(int nl,int nh); /*!< \brief allocation of 1D byte array [nl..nh] */
  byte**   ballocation2(int nrl,int nrh,int ncl,int nch); /*!< \brief allocation of 2D byte array [nrl..nrh][ncl..nch] */
  byte***  ballocation3(int l1,int h1,int l2,int h2,int l3,int h3); /*!< \brief allocation of 3D byte array [l1..h1][l2..h2][l3..h3] */
  byte**** ballocation4(int l1,int h1,int l2,int h2,int l3,int h3,int l4,int h4); /*!< \brief allocation of 4D byte array [l1..h1][l2..h2][l3..h3][l4..h4] */

  void     freebmem1(byte* &v,int nl,int nh); /*!< \brief frees memory allocated by ballocation1 */
  void     freebmem2(byte** &m,int nrl,int nrh,int ncl,int nch); /*!< \brief frees memory allocated by ballocation2 */
  void     freebmem3(byte*** &m,int l1,int h1,int l2,int h2,int l3,int h3); /*!< \brief frees memory allocated by ballocation3 */
  void     freebmem4(byte**** &m,int l1,int h1,int l2,int h2,int l3,int h3,int l4,int h4); /*!< \brief frees memory allocated by ballocation4 */

  word*    wallocation1(int nl,int nh); /*!< \brief allocation of 1D word array [nl..nh] */
  word**   wallocation2(int nrl,int nrh,int ncl,int nch); /*!< \brief allocation of 2D word array [nrl..nrh][ncl..nch] */
  word***  wallocation3(int l1,int h1,int l2,int h2,int l3,int h3); /*!< \brief allocation of 3D word array [l1..h1][l2..h2][l3..h3] */
  word**** wallocation4(int l1,int h1,int l2,int h2,int l3,int h3,int l4,int h4); /*!< \brief allocation of 4D word array [l1..h1][l2..h2][l3..h3][l4..h4] */

  void     freewmem1(word* &v,int nl,int nh); /*!< \brief frees memory allocated by wallocation1 */
  void     freewmem2(word** &m,int nrl,int nrh,int ncl,int nch); /*!< \brief frees memory allocated by wallocation2 */
  void     freewmem3(word*** &m,int l1,int h1,int l2,int h2,int l3,int h3); /*!< \brief frees memory allocated by wallocation3 */
  void     freewmem4(word**** &m,int l1,int h1,int l2,int h2,int l3,int h3,int l4,int h4); /*!< \brief frees memory allocated by wallocation4 */

  int*     iallocation1(int nl,int nh); /*!< \brief allocation of 1D int array [nl..nh] */
  int**    iallocation2(int nrl,int nrh,int ncl,int nch); /*!< \brief allocation of 2D int array [nrl..nrh][ncl..nch] */
  int***   iallocation3(int l1,int h1,int l2,int h2,int l3,int h3); /*!< \brief allocation of 3D int array [l1..h1][l2..h2][l3..h3] */
  int****  iallocation4(int l1,int h1,int l2,int h2,int l3,int h3,int l4,int h4); /*!< \brief allocation of 4D int array [l1..h1][l2..h2][l3..h3][l4..h4] */
  int**    iallocation12(int nl,int nh); /*!< \brief allocation of 1D int* array [nl..nh] */

  void     freeimem1(int* &v,int nl,int nh); /*!< \brief frees memory allocated by iallocation1 */
  void     freeimem2(int** &m,int nrl,int nrh,int ncl,int nch); /*!< \brief frees memory allocated by iallocation2 */
  void     freeimem3(int*** &m,int l1,int h1,int l2,int h2,int l3,int h3); /*!< \brief frees memory allocated by iallocation3 */
  void     freeimem4(int**** &m,int l1,int h1,int l2,int h2,int l3,int h3,int l4,int h4); /*!< \brief frees memory allocated by iallocation4 */
  void     freeimem12(int** &v,int nl,int nh); /*!< \brief frees memory allocated by iallocation12 */

  long*    lallocation1(int nl,int nh); /*!< \brief allocation of 1D long array [nl..nh] */
  long**   lallocation2(int nrl,int nrh,int ncl,int nch); /*!< \brief allocation of 2D long array [nrl..nrh][ncl..nch] */
  long***  lallocation3(int l1,int h1,int l2,int h2,int l3,int h3); /*!< \brief allocation of 3D long array [l1..h1][l2..h2][l3..h3] */
  long**** lallocation4(int l1,int h1,int l2,int h2,int l3,int h3,int l4,int h4); /*!< \brief allocation of 4D long array [l1..h1][l2..h2][l3..h3][l4..h4] */

  void     freelmem1(long* &v,int nl,int nh); /*!< \brief frees memory allocated by lallocation1 */
  void     freelmem2(long** &m,int nrl,int nrh,int ncl,int nch); /*!< \brief frees memory allocated by lallocation2 */
  void     freelmem3(long*** &m,int l1,int h1,int l2,int h2,int l3,int h3); /*!< \brief frees memory allocated by lallocation3 */
  void     freelmem4(long**** &m,int l1,int h1,int l2,int h2,int l3,int h3,int l4,int h4); /*!< \brief frees memory allocated by lallocation4 */


// chars

  char*    callocation1(int nl,int nh); /*!< \brief allocation of 1D char array [nl..nh] */
  char**   callocation2(int nrl,int nrh,int ncl,int nch); /*!< \brief allocation of 2D char array [nrl..nrh][ncl..nch] */

  void     freecmem1(char* &v,int nl,int nh); /*!< \brief frees memory allocated by callocation1 */
  void     freecmem2(char** &v,int nrl,int nrh,int ncl,int nch); /*!< \brief frees memory allocated by callocation2 */


// const char*

  const char**  pcallocation1(int nl,int nh); /*!< \brief allocation of 1D const char* array [nl..nh] */
  const char*** pcallocation12(int nl,int nh); /*!< \brief allocation of 1D const char** array [nl..nh] */
  const char*** pcallocation2(int nrl,int nrh,int ncl,int nch); /*!< \brief allocation of 2D const char* array [nrl..nrh][ncl..nch] */

  void          freepcmem1(const char** &v,int nl,int nh); /*!< \brief frees memory allocated by pcallocation1 */
  void          freepcmem12(const char*** &v,int nl,int nh); /*!< \brief frees memory allocated by pcallocation12 */
  void          freepcmem2(const char*** &v,int nrl,int nrh,int ncl,int nch); /*!< \brief frees memory allocated by pcallocation2 */


// matrix copy & multiply functions

  void     cmama1(float *ma1,float *ma2,int nrf,int nrl,int pr); /*!< \todo Missing description to be added... */
  void     cmama2(float **ma1,float **ma2,int nrf,int nrl,int ncf,
		  int ncl,int pr,int pc); /*!< \todo Missing description to be added... */
  void     cmama1(double *ma1,double *ma2,int nrf,int nrl,int pr); /*!< \todo Missing description to be added... */
  void     cmama2(double **ma1,double **ma2,int nrf,int nrl,int ncf,
		  int ncl,int pr,int pc); /*!< \todo Missing description to be added... */
  void     cmama1(int *ma1,int *ma2,int nrf,int nrl,int pr); /*!< \todo Missing description to be added... */
  void     cmama2(int **ma1,int **ma2,int nrf,int nrl,int ncf,int ncl,
		  int pr,int pc); /*!< \todo Missing description to be added... */
  void     cmama1(char *ma1,char *ma2,int nrf,int nrl,int pr); /*!< \todo Missing description to be added... */
  void     cmama2(char **ma1,char **ma2,int nrf,int nrl,int ncf,
		  int ncl,int pr,int pc); /*!< \todo Missing description to be added... */
  void     cmama3(float ***ma1,float ***ma2, int nr, int nc); /*!< \todo Missing description to be added... */
  void     cmama3(double ***ma1,double ***ma2, int nr, int nc); /*!< \todo Missing description to be added... */
  void     vemuma2(float **ma1,int nrl,int ncl,float *map_,float *ma2); /*!< \todo Missing description to be added... */
  void     vemuma3(float ***ma1,int nplanes,int nrl,int ncl,float **map_,
		   float ***ma2); /*!< \todo Missing description to be added... */ // changed by VH third dimension for 3D matix
  void     vemuma3_part(float ***ma1,int nplanes,int nplanes2,int nrl,int ncl,
			float **map,float ***ma2);  // modified vemuma3 by xaos - map matrix dimensions [nplanes,nplanes2]
  void     vemuma3_mask(float ***ma1,int nplanes,int nplanes2,int nrl,int ncl,
			float **map,float ***ma2, int ** mask);  // modified vemuma3 by xaos - map matrix dimensions [nplanes,nplanes2]


// vr_alloc|vr_free  general wrappers

  inline int vr_alloc(float* &ptr, int nrf, int nrl) { ptr=allocation1(nrf,nrl);  return (ptr!=NULL); }
  inline int vr_alloc(float** &ptr, int nrf, int nrl, int ncf, int ncl) { ptr=allocation2(nrf,nrl,ncf,ncl);  return (ptr!=NULL); }
  inline int vr_alloc(float*** &ptr, int nmf, int nml, int nrf, int nrl, int ncf, int ncl) { ptr=allocation3(nmf,nml,nrf,nrl,ncf,ncl);  return (ptr!=NULL); }
  inline int vr_alloc(float**** &ptr, int ntf, int ntl, int nmf, int nml, int nrf, int nrl, int ncf, int ncl) { ptr=allocation4(ntf,ntl,nmf,nml,nrf,nrl,ncf,ncl);  return (ptr!=NULL); }
  inline int vr_alloc(float***** &ptr, int nff, int nfl, int ntf, int ntl, int nmf, int nml, int nrf, int nrl, int ncf, int ncl) { ptr=allocation5(nff,nfl,ntf,ntl,nmf,nml,nrf,nrl,ncf,ncl);  return (ptr!=NULL); }  
  inline int vr_alloc(float*** &ptr, int nrf, int nrl) { ptr=allocation13(nrf,nrl);  return (ptr!=NULL); }
  inline int vr_alloc(float**** &ptr, int nrf, int nrl) { ptr=allocation14(nrf,nrl);  return (ptr!=NULL); }

  inline int vr_free(float* &ptr, int nrf, int nrl) { freemem1(ptr,nrf,nrl);  return (ptr!=NULL); }
  inline int vr_free(float** &ptr, int nrf, int nrl, int ncf, int ncl) { freemem2(ptr,nrf,nrl,ncf,ncl);  return (ptr!=NULL); }
  inline int vr_free(float*** &ptr, int nmf, int nml, int nrf, int nrl, int ncf, int ncl) { freemem3(ptr,nmf,nml,nrf,nrl,ncf,ncl);  return (ptr!=NULL); }
  inline int vr_free(float**** &ptr, int ntf, int ntl, int nmf, int nml, int nrf, int nrl, int ncf, int ncl) { freemem4(ptr,ntf,ntl,nmf,nml,nrf,nrl,ncf,ncl);  return (ptr!=NULL); }
  inline int vr_free(float***** &ptr, int nff, int nfl, int ntf, int ntl, int nmf, int nml, int nrf, int nrl, int ncf, int ncl) { freemem5(ptr,nff,nfl,ntf,ntl,nmf,nml,nrf,nrl,ncf,ncl);  return (ptr!=NULL); }    
  inline int vr_free(float*** &ptr, int nrf, int nrl) { freemem13(ptr,nrf,nrl);  return (ptr!=NULL); }
  inline int vr_free(float**** &ptr, int nrf, int nrl) { freemem14(ptr,nrf,nrl);  return (ptr!=NULL); }

  inline int vr_alloc(double* &ptr, int nrf, int nrl) { ptr=dallocation1(nrf,nrl);  return (ptr!=NULL); }
  inline int vr_alloc(double** &ptr, int nrf, int nrl, int ncf, int ncl) { ptr=dallocation2(nrf,nrl,ncf,ncl);  return (ptr!=NULL); }
  inline int vr_alloc(double*** &ptr, int nmf, int nml, int nrf, int nrl, int ncf, int ncl) { ptr=dallocation3(nmf,nml,nrf,nrl,ncf,ncl);  return (ptr!=NULL); }
  inline int vr_alloc(double**** &ptr, int ntf, int ntl, int nmf, int nml, int nrf, int nrl, int ncf, int ncl) { ptr=dallocation4(ntf,ntl,nmf,nml,nrf,nrl,ncf,ncl);  return (ptr!=NULL); }
  inline int vr_alloc(double***** &ptr, int nff, int nfl, int ntf, int ntl, int nmf, int nml, int nrf, int nrl, int ncf, int ncl) { ptr=dallocation5(nff,nfl,ntf,ntl,nmf,nml,nrf,nrl,ncf,ncl);  return (ptr!=NULL); }  

  inline int vr_free(double* &ptr, int nrf, int nrl) { freedmem1(ptr,nrf,nrl);  return (ptr!=NULL); }
  inline int vr_free(double** &ptr, int nrf, int nrl, int ncf, int ncl) { freedmem2(ptr,nrf,nrl,ncf,ncl);  return (ptr!=NULL); }
  inline int vr_free(double*** &ptr, int nmf, int nml, int nrf, int nrl, int ncf, int ncl) { freedmem3(ptr,nmf,nml,nrf,nrl,ncf,ncl);  return (ptr!=NULL); }
  inline int vr_free(double**** &ptr, int ntf, int ntl, int nmf, int nml, int nrf, int nrl, int ncf, int ncl) { freedmem4(ptr,ntf,ntl,nmf,nml,nrf,nrl,ncf,ncl);  return (ptr!=NULL); }
  inline int vr_free(double***** &ptr, int nff, int nfl, int ntf, int ntl, int nmf, int nml, int nrf, int nrl, int ncf, int ncl) { freedmem5(ptr,nff,nfl,ntf,ntl,nmf,nml,nrf,nrl,ncf,ncl);  return (ptr!=NULL); }    


  inline int vr_alloc(byte* &ptr, int nrf, int nrl) { ptr=ballocation1(nrf,nrl);  return (ptr!=NULL); }
  inline int vr_alloc(byte** &ptr, int nrf, int nrl, int ncf, int ncl) { ptr=ballocation2(nrf,nrl,ncf,ncl);  return (ptr!=NULL); }
  inline int vr_alloc(byte*** &ptr, int nmf, int nml, int nrf, int nrl, int ncf, int ncl) { ptr=ballocation3(nmf,nml,nrf,nrl,ncf,ncl);  return (ptr!=NULL); }
  inline int vr_alloc(byte**** &ptr, int ntf, int ntl, int nmf, int nml, int nrf, int nrl, int ncf, int ncl) { ptr=ballocation4(ntf,ntl,nmf,nml,nrf,nrl,ncf,ncl);  return (ptr!=NULL); }

  inline int vr_free(byte* &ptr, int nrf, int nrl) { freebmem1(ptr,nrf,nrl);  return (ptr!=NULL); }
  inline int vr_free(byte** &ptr, int nrf, int nrl, int ncf, int ncl) { freebmem2(ptr,nrf,nrl,ncf,ncl);  return (ptr!=NULL); }
  inline int vr_free(byte*** &ptr, int nmf, int nml, int nrf, int nrl, int ncf, int ncl) { freebmem3(ptr,nmf,nml,nrf,nrl,ncf,ncl);  return (ptr!=NULL); }
  inline int vr_free(byte**** &ptr, int ntf, int ntl, int nmf, int nml, int nrf, int nrl, int ncf, int ncl) { freebmem4(ptr,ntf,ntl,nmf,nml,nrf,nrl,ncf,ncl);  return (ptr!=NULL); }

  inline int vr_alloc(word* &ptr, int nrf, int nrl) { ptr=wallocation1(nrf,nrl);  return (ptr!=NULL); }
  inline int vr_alloc(word** &ptr, int nrf, int nrl, int ncf, int ncl) { ptr=wallocation2(nrf,nrl,ncf,ncl);  return (ptr!=NULL); }
  inline int vr_alloc(word*** &ptr, int nmf, int nml, int nrf, int nrl, int ncf, int ncl) { ptr=wallocation3(nmf,nml,nrf,nrl,ncf,ncl);  return (ptr!=NULL); }
  inline int vr_alloc(word**** &ptr, int ntf, int ntl, int nmf, int nml, int nrf, int nrl, int ncf, int ncl) { ptr=wallocation4(ntf,ntl,nmf,nml,nrf,nrl,ncf,ncl);  return (ptr!=NULL); }

  inline int vr_free(word* &ptr, int nrf, int nrl) { freewmem1(ptr,nrf,nrl);  return (ptr!=NULL); }
  inline int vr_free(word** &ptr, int nrf, int nrl, int ncf, int ncl) { freewmem2(ptr,nrf,nrl,ncf,ncl);  return (ptr!=NULL); }
  inline int vr_free(word*** &ptr, int nmf, int nml, int nrf, int nrl, int ncf, int ncl) { freewmem3(ptr,nmf,nml,nrf,nrl,ncf,ncl);  return (ptr!=NULL); }
  inline int vr_free(word**** &ptr, int ntf, int ntl, int nmf, int nml, int nrf, int nrl, int ncf, int ncl) { freewmem4(ptr,ntf,ntl,nmf,nml,nrf,nrl,ncf,ncl);  return (ptr!=NULL); }

  inline int vr_alloc(int* &ptr, int nrf, int nrl) { ptr=iallocation1(nrf,nrl);  return (ptr!=NULL); }
  inline int vr_alloc(int** &ptr, int nrf, int nrl, int ncf, int ncl) { ptr=iallocation2(nrf,nrl,ncf,ncl);  return (ptr!=NULL); }
  inline int vr_alloc(int*** &ptr, int nmf, int nml, int nrf, int nrl, int ncf, int ncl) { ptr=iallocation3(nmf,nml,nrf,nrl,ncf,ncl);  return (ptr!=NULL); }
  inline int vr_alloc(int**** &ptr, int ntf, int ntl, int nmf, int nml, int nrf, int nrl, int ncf, int ncl) { ptr=iallocation4(ntf,ntl,nmf,nml,nrf,nrl,ncf,ncl);  return (ptr!=NULL); }
  inline int vr_alloc(int** &ptr, int nrf, int nrl) { ptr=iallocation12(nrf,nrl);  return (ptr!=NULL); }

  inline int vr_free(int* &ptr, int nrf, int nrl) { freeimem1(ptr,nrf,nrl);  return (ptr!=NULL); }
  inline int vr_free(int** &ptr, int nrf, int nrl, int ncf, int ncl) { freeimem2(ptr,nrf,nrl,ncf,ncl);  return (ptr!=NULL); }
  inline int vr_free(int*** &ptr, int nmf, int nml, int nrf, int nrl, int ncf, int ncl) { freeimem3(ptr,nmf,nml,nrf,nrl,ncf,ncl);  return (ptr!=NULL); }
  inline int vr_free(int**** &ptr, int ntf, int ntl, int nmf, int nml, int nrf, int nrl, int ncf, int ncl) { freeimem4(ptr,ntf,ntl,nmf,nml,nrf,nrl,ncf,ncl);  return (ptr!=NULL); }
  inline int vr_free(int** &ptr, int nrf, int nrl) { freeimem12(ptr,nrf,nrl);  return (ptr!=NULL); }

  inline int vr_alloc(long* &ptr, int nrf, int nrl) { ptr=lallocation1(nrf,nrl);  return (ptr!=NULL); }
  inline int vr_alloc(long** &ptr, int nrf, int nrl, int ncf, int ncl) { ptr=lallocation2(nrf,nrl,ncf,ncl);  return (ptr!=NULL); }
  inline int vr_alloc(long*** &ptr, int nmf, int nml, int nrf, int nrl, int ncf, int ncl) { ptr=lallocation3(nmf,nml,nrf,nrl,ncf,ncl);  return (ptr!=NULL); }
  inline int vr_alloc(long**** &ptr, int ntf, int ntl, int nmf, int nml, int nrf, int nrl, int ncf, int ncl) { ptr=lallocation4(ntf,ntl,nmf,nml,nrf,nrl,ncf,ncl);  return (ptr!=NULL); }

  inline int vr_free(long* &ptr, int nrf, int nrl) { freelmem1(ptr,nrf,nrl);  return (ptr!=NULL); }
  inline int vr_free(long** &ptr, int nrf, int nrl, int ncf, int ncl) { freelmem2(ptr,nrf,nrl,ncf,ncl);  return (ptr!=NULL); }
  inline int vr_free(long*** &ptr, int nmf, int nml, int nrf, int nrl, int ncf, int ncl) { freelmem3(ptr,nmf,nml,nrf,nrl,ncf,ncl);  return (ptr!=NULL); }
  inline int vr_free(long**** &ptr, int ntf, int ntl, int nmf, int nml, int nrf, int nrl, int ncf, int ncl) { freelmem4(ptr,ntf,ntl,nmf,nml,nrf,nrl,ncf,ncl);  return (ptr!=NULL); }


  inline int vr_alloc(char* &ptr, int nrf, int nrl) { ptr=callocation1(nrf,nrl);  return (ptr!=NULL); }
  inline int vr_alloc(char** &ptr, int nrf, int nrl, int ncf, int ncl) { ptr=callocation2(nrf,nrl,ncf,ncl);  return (ptr!=NULL); }

  inline int vr_free(char* &ptr, int nrf, int nrl) { freecmem1(ptr,nrf,nrl);  return (ptr!=NULL); }
  inline int vr_free(char** &ptr, int nrf, int nrl, int ncf, int ncl) { freecmem2(ptr,nrf,nrl,ncf,ncl);  return (ptr!=NULL); }


  inline int vr_alloc(const char** &ptr, int nrf, int nrl) { ptr=pcallocation1(nrf,nrl);  return (ptr!=NULL); }
  inline int vr_alloc(const char*** &ptr, int nrf, int nrl) { ptr=pcallocation12(nrf,nrl);  return (ptr!=NULL); }
  inline int vr_alloc(const char*** &ptr, int nrf, int nrl, int ncf, int ncl) { ptr=pcallocation2(nrf,nrl,ncf,ncl);  return (ptr!=NULL); }

  inline int vr_free(const char** &ptr, int nrf, int nrl) { freepcmem1(ptr,nrf,nrl);  return (ptr!=NULL); }
  inline int vr_free(const char*** &ptr, int nrf, int nrl) { freepcmem12(ptr,nrf,nrl);  return (ptr!=NULL); }
  inline int vr_free(const char*** &ptr, int nrf, int nrl, int ncf, int ncl) { freepcmem2(ptr,nrf,nrl,ncf,ncl);  return (ptr!=NULL); }


#endif
