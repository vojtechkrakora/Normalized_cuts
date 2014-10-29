
/* FIT 2014 - information about image I/O keys */

#ifndef PRESINFO_h
#define PRESINFO_h

#include <stdlib.h>
#include <stdio.h>


/*

  The definition of pres keys constants.

  PRES_NO_KEY  -  no format ( 0 )

  PRES_DEFAULT_KEY  -  default format (PNG)

following are used for read/write distinguishing when image format is not specified
  PRES_FMT_KEY  -  value represents enum key value
  PRES_READ_KEY  -  value represents read key value
  PRES_WRITE_KEY  -  value represents write key value

following are triple constant for every image format (see PresEntries.h)
  PRES_FMT_KEY_*
  PRES_READ_KEY_*
  PRES_WRITE_KEY_*

*/

// PresEntries.inc; 2.01

const int PRES_ENUM_BEGIN = 10001; const int PRES_DEFAULT_KEY = 10001; const int PRES_NO_KEY = 0; const int PRES_FMT_KEY = 10001 - 1; const int PRES_READ_KEY = 10001 - 2; const int PRES_WRITE_KEY = 10001 - 3;
const int PRES_FMT_KEY_PNG = 10001; const int PRES_READ_KEY_PNG = 301; const int PRES_WRITE_KEY_PNG = 302;
const int PRES_FMT_KEY_PNG_MONO = 10002; const int PRES_READ_KEY_PNG_MONO = 3010; const int PRES_WRITE_KEY_PNG_MONO = 3020;
const int PRES_FMT_KEY_PNG_RGB = 10003; const int PRES_READ_KEY_PNG_RGB = 3011; const int PRES_WRITE_KEY_PNG_RGB = 3021;
const int PRES_FMT_KEY_JPEG = 10004; const int PRES_READ_KEY_JPEG = 257; const int PRES_WRITE_KEY_JPEG = 258;
const int PRES_FMT_KEY_PPM_ASCII = 10005; const int PRES_READ_KEY_PPM_ASCII = 259; const int PRES_WRITE_KEY_PPM_ASCII = 260;
const int PRES_FMT_KEY_PPM_RAW = 10006; const int PRES_READ_KEY_PPM_RAW = 255; const int PRES_WRITE_KEY_PPM_RAW = 256;
const int PRES_FMT_KEY_PGM_ASCII = 10007; const int PRES_READ_KEY_PGM_ASCII = 14; const int PRES_WRITE_KEY_PGM_ASCII = 11;
const int PRES_FMT_KEY_PGM_RAW = 10008; const int PRES_READ_KEY_PGM_RAW = 9; const int PRES_WRITE_KEY_PGM_RAW = 10;
const int PRES_FMT_KEY_BMP_RGB = 10009; const int PRES_READ_KEY_BMP_RGB = -303; const int PRES_WRITE_KEY_BMP_RGB = 304;
const int PRES_FMT_KEY_BMP = 10010; const int PRES_READ_KEY_BMP = 311; const int PRES_WRITE_KEY_BMP = 312;
const int PRES_FMT_KEY_HDR = 10011; const int PRES_READ_KEY_HDR = 313; const int PRES_WRITE_KEY_HDR = 314;
const int PRES_FMT_KEY_EXR_RGBA = 10012; const int PRES_READ_KEY_EXR_RGBA = 315; const int PRES_WRITE_KEY_EXR_RGBA = 316;
const int PRES_FMT_KEY_EXR_XYZ = 10013; const int PRES_READ_KEY_EXR_XYZ = 319; const int PRES_WRITE_KEY_EXR_XYZ = 320;
const int PRES_FMT_KEY_EXR_GEN = 10014; const int PRES_READ_KEY_EXR_GEN = 317; const int PRES_WRITE_KEY_EXR_GEN = 318;
const int PRES_FMT_KEY_NITF = 10015; const int PRES_READ_KEY_NITF = 400; const int PRES_WRITE_KEY_NITF = 401;
const int PRES_FMT_KEY_RAW_REAL = 10016; const int PRES_READ_KEY_RAW_REAL = 253; const int PRES_WRITE_KEY_RAW_REAL = 254;
const int PRES_FMT_KEY_RAW_ = 10017; const int PRES_READ_KEY_RAW_ = 25; const int PRES_WRITE_KEY_RAW_ = -26;
const int PRES_FMT_KEY_RAW_2B = 10018; const int PRES_READ_KEY_RAW_2B = 15; const int PRES_WRITE_KEY_RAW_2B = 16;
const int PRES_FMT_KEY_RAW_1B_A = 10019; const int PRES_READ_KEY_RAW_1B_A = 3; const int PRES_WRITE_KEY_RAW_1B_A = 4;
const int PRES_FMT_KEY_RAW_1B_B = 10020; const int PRES_READ_KEY_RAW_1B_B = 5; const int PRES_WRITE_KEY_RAW_1B_B = -105;
const int PRES_FMT_KEY_RAW_1B_C = 10021; const int PRES_READ_KEY_RAW_1B_C = -107; const int PRES_WRITE_KEY_RAW_1B_C = -7;
const int PRES_FMT_KEY_RAW_1B_D = 10022; const int PRES_READ_KEY_RAW_1B_D = -108; const int PRES_WRITE_KEY_RAW_1B_D = 8;
const int PRES_FMT_KEY_RAW_1B_SI0 = 10023; const int PRES_READ_KEY_RAW_1B_SI0 = 1; const int PRES_WRITE_KEY_RAW_1B_SI0 = 2;
const int PRES_FMT_KEY_RAW_1B_SI1 = 10024; const int PRES_READ_KEY_RAW_1B_SI1 = 6; const int PRES_WRITE_KEY_RAW_1B_SI1 = -106;
const int PRES_FMT_KEY_SUN_NUL = 10025; const int PRES_READ_KEY_SUN_NUL = 23; const int PRES_WRITE_KEY_SUN_NUL = 24;
const int PRES_FMT_KEY_SUN_EXT = 10026; const int PRES_READ_KEY_SUN_EXT = 19; const int PRES_WRITE_KEY_SUN_EXT = 20;
const int PRES_FMT_KEY_PNM = 10027; const int PRES_READ_KEY_PNM = 17; const int PRES_WRITE_KEY_PNM = 18;
const int PRES_FMT_KEY_PBM = 10028; const int PRES_READ_KEY_PBM = 12; const int PRES_WRITE_KEY_PBM = 13;
const int PRES_FMT_KEY_BUGS = 10029; const int PRES_READ_KEY_BUGS = 21; const int PRES_WRITE_KEY_BUGS = -22;
const int PRES_FMT_KEY_MLI = 10030; const int PRES_READ_KEY_MLI = 305; const int PRES_WRITE_KEY_MLI = 306;
const int PRES_FMT_KEY_MLF = 10031; const int PRES_READ_KEY_MLF = 307; const int PRES_WRITE_KEY_MLF = 308;
const int PRES_FMT_KEY_XLF = 10032; const int PRES_READ_KEY_XLF = 309; const int PRES_WRITE_KEY_XLF = 310;
const int PRES_FMT_KEY_FITS = 10033; const int PRES_READ_KEY_FITS = 27; const int PRES_WRITE_KEY_FITS = -127;
const int PRES_FMT_KEY_FITS_UPDN = 10034; const int PRES_READ_KEY_FITS_UPDN = 28; const int PRES_WRITE_KEY_FITS_UPDN = -128;
const int PRES_ENUM_END = 10034; const int PRES_ENUM_COUNT = PRES_ENUM_END - PRES_ENUM_BEGIN + 1;


const unsigned int PRES_FLAG_STATUS_MASK     = 0x0007;
const unsigned int PRES_FLAG_OK              = 0x0000;
const unsigned int PRES_FLAG_ERROR           = 0x0001;
const unsigned int PRES_FLAG_OBSOLETE        = 0x0002;
const unsigned int PRES_FLAG_EXPERIMENTAL    = 0x0004;
const unsigned int PRES_FLAG_COMMON_ROUTINE  = 0x0008;

const unsigned int PRES_FLAG_16BIT           = 0x0010;
const unsigned int PRES_FLAG_FLOAT           = 0x0020;
const unsigned int PRES_FLAG_FIRST3PLANES    = 0x0040;
const unsigned int PRES_FLAG_TEXT_FORMAT     = 0x0080;

const unsigned int PRES_FLAG_NCOLOUR_MASK    = 0x0F00;
const unsigned int PRES_FLAG_NCOLOUR0        = 0x0100;
const unsigned int PRES_FLAG_NCOLOUR2        = 0x0200;
const unsigned int PRES_FLAG_NCOLOUR13       = 0x0400;
const unsigned int PRES_FLAG_NCOLOURN        = 0x0800;

const unsigned int PRES_FLAG_MONO            = 0x0100;
const unsigned int PRES_FLAG_RGB             = 0x0200;
const unsigned int PRES_FLAG_MULTI           = 0x0800;

const unsigned int PRES_FLAG_SERIE_MONO      = 0x0900;
const unsigned int PRES_FLAG_SERIE_RGB       = 0x0A00;

const unsigned int PRES_FLAG_GETHEADER       = 0x1000;
const unsigned int PRES_FLAG_HASMAGICVALUE   = 0x2000;
const unsigned int PRES_FLAG_DEFAULTFOREXT   = 0x4000;


typedef struct pres_entry {

  const char *id;
  const char *label;
  unsigned int flags;
  int readkey, writekey, fmtkey;
  int numberofextensions;
  const char **extensions;
  const char *magicvalue;
  const char *auxvarname;
  const char *note;

} PresEntry;

int pres_get_pe(int key, const PresEntry* &pe, int* rw = NULL, const char* ext = NULL);   // negative key .. not implemented or don't use;  keys > 10000 .. enumerate formats
inline const PresEntry* pres_get_pe(int key) { const PresEntry* pe=NULL;  return (pres_get_pe(key,pe)!=PRES_NO_KEY)?pe:NULL; }

int pres_key_for_ext(const char* extension, const PresEntry** pe = NULL);

inline const char* pres_get_label(int key) { const PresEntry *pe=NULL; pres_get_pe(key,pe); return (pe)?pe->label:NULL; }
inline unsigned int pres_get_flags(int key) { const PresEntry *pe=NULL; pres_get_pe(key,pe); return (pe)?pe->flags:0; }
inline int pres_get_readkey(int key) { const PresEntry *pe=NULL; pres_get_pe(key,pe); return (pe)?pe->readkey:PRES_NO_KEY; }
inline int pres_get_writekey(int key) { const PresEntry *pe=NULL; pres_get_pe(key,pe); return (pe)?pe->writekey:PRES_NO_KEY; }
inline int pres_is_readkey(int key) { return (abs(pres_get_readkey(key))==abs(key)||key==PRES_READ_KEY)?1:0; }
inline int pres_is_writekey(int key) { return (abs(pres_get_writekey(key))==abs(key)||key==PRES_WRITE_KEY)?1:0; }
inline int pres_is_validkey(int key) { const PresEntry *pe=NULL; return (key>0&&pres_get_pe(key,pe)==key)?1:0; }

inline int pres_is_serie(unsigned int flags) { return (((flags&PRES_FLAG_MULTI)!=0)&&((flags&PRES_FLAG_NCOLOUR_MASK)!=PRES_FLAG_NCOLOUR_MASK))?1:0; }
inline void pres_serie_filename(char* name, const char* templ, int m) { sprintf(name,templ,m); }

int pres_file_exist(const char* name, int rw = PRES_READ_KEY, char* ext = NULL, int m = 0);
int pres_filename_check(char* name, const char* base, int rw, const PresEntry* &pe, int m = 0, char type = 'f');  // assumes the length of name is PRES_PATH_MAX_SIZE

#endif


/***************************************************************************************************************************************************************

  label                       read  write  extensions  stat   ncolour  16  get note
  -----                       ----  -----  ----------  ----  0 2 1+3 n bit hdr ----

  PNG                          301   302  *png          ok   + /  <  <  x   o  non-standard (0,2) multiplane support - only first 3 planes get saved
  PNG series (mono)           3010  3020   png          ok   + +  +  +  x      appends  _XXXX  to name
  PNG series (RGB)            3011  3021   png          ok   + +  +  +  x      appends  _XXXX  to name

  JPEG                         257   258  *jpg, jpeg    ok   + /            o  (WARNING: due to system-dependent defines inside the jpeg library problems may occure on different systems!)

  PPM 'P3' (ascii)             259   260   ppm          ok     +            o  normalized 0-255, uncompressed
  PPM 'P6' (raw)               255   256  *ppm          ok     +            o  normalized 0-255, rowwise 3B/pix

  PGM 'P2' (ascii)              14    11   pgm          ok   *              o  normalized 0-255, uncompressed
  PGM 'P5' (raw)                 9    10  *pgm          ok   *              o  normalized 0-255, rowwise 1B/pix

  BMP                         -303   304   bmp               + +               rgb|single-plane -> uncompressed rgb, reading is not implemeted
  BMP (uncomp. RGB only)       311   312  *bmp          ok   + /  <  <      o  rgb or single-plane data (oneplane support)

  HDR - Radiance RGBE          313   314  *hdr          ok     /            o  rgb images only (ncolour=2)

  EXR - OpenEXR (rgba)         315   316   exr          ok   + +  +         o  half-float, max. 4 spectral planes (asrgb=save 1 plane as rgb)
  EXR - OpenEXR (xyz)          315   320   exr          ok   + +            o  half-float, max. 3 spectral planes (asrgb=save 1 plane as rgb)
  EXR - OpenEXR (general)      315   318  *exr          ok   + +  +  +      o  full-float, multiplane

  NTF - NITF format            400   401  *ntf         exp.  + +  +  +  x   o  integer values, uses NITRO library, writing not fully functioning yet

  raw data - real              253   254               obs.  *                 as C-style text float values
  raw data - real (INRIA)       25     0               obs.  *                 same as key=253, but jump over the header (256B)

  raw data - 2byte              15    16               obs.  *                 2B/pix binary |odd B smaller|even B higher|

  raw data - 1byte               3     4               obs.  *                 1B/pix binary (originally described as ASCII format, each byte understood as char)
  raw data - 1byte               5     0               obs.  *                 1B/pix binary (ignores first 256 bytes)
  raw data - 1byte               0     7               err   *                 1B/pix binary (should add 'INRIA' header, but currently is not functional)
  raw data - 1byte               0     8               err   *                 1B/pix binary (seems incorrect, as it simply writes int values using putc) ('ics' format - rowwise pixel 1B unsigned int)

  raw data - 1B (SCILIMAGE)      1     2               obs.  *                 rowwise 1B/pix binary, values shifted to interval <-128,127> (originally described as ASCII format, each byte understood as char)
  raw data - 1B (SCILIMAGE)      6     0               obs.  *                 same as key=1, but ignores first 256 bytes

  SUN rasterfile                23    24               obs.  *              o  normalized 0-255 (WARNING: may produce incorrect headers on some systems!)
  SUN rasterfile                19    20  *ras         obs.  *              o  normalized 0-255 (WARNING: may produce incorrect headers on some systems!)

  PNM 'P5' (raw)                17    18   pnm         obs.  *              o  normalized 0-255
  PBM 'P1' (ascii)              12    13   pbm         obs.  *              o  binary 0/1, writes pixel as 1 if a[][]==1, 0 otherwise

  Bugs                          21     0               obs.  *                 '{int float} per row', format not checked

  MLI 'P7' (multi, integer)    305   306  *mli         exp.  + +  +  +      o  range (0-255) of arbitrary number of spectral layers (based on PPM)
  MLF 'P8' (multi, float)      307   308  *mlf         exp.  + +  +  +      o  floats of arbitrary number of spectral layers (based on PPM)
  XLF 'P9' (multi, float)      309   310  *xlf         exp.  + +  +  +      o  floats of arbitrary number of spectral layers, faster read/write [non-cross platform] (based on PPM)

  FITS                          27     0   fit, fits   exp.  *                 1B 2D FITS format
  FITS                          28     0   fit, fits   exp.  *                 1B 2D FITS format, upside down

***************************************************************************************************************************************************************/
