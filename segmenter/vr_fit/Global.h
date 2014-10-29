
/* FIT 2014 - constants */

#ifndef global_c
#define global_c

/************************************************************************
 from/for Pres.cpp -> image IO definitions: -----------------------------
 ************************************************************************/
#define IMGIO_OK                      0
#define IMGIO_FILE_NOT_OPENED        -1
#define IMGIO_NOT_A_PNG              -2
#define IMGIO_ALLOCATION_PROBLEM     -3
#define IMGIO_FILE_READ_PROBLEM      -4
#define IMGIO_FILE_WRITE_PROBLEM     -5
#define IMGIO_FILE_CONTENTS_PROBLEM  -6
#define IMGIO_WRONG_PARAMETER        -7
#define IMGIO_16BIT_UNSUPPORTED      -8
#define IMGIO_UNEXPECTED_EOF         -9
#define IMGIO_NOT_IMPLEMENTED        -10

#define IMGIO_FITS_NOT_SIMPLE        -101
#define IMGIO_FITS_NOT_1BYTE         -102
#define IMGIO_FITS_NOT_2DIM          -103

#define IMGIO_SUN_BAD_HEADER         -111
#define IMGIO_SUN_NOT_MONO           -112

#define IMGIO_NITF_READ_ERROR        -131
#define IMGIO_NITF_WRONG_SIZE        -132
#define IMGIO_NITF_BPP_ERROR         -133
#define IMGIO_NITF_WRONG_NIMAGE      -134

#define PRES_PATH_MAX_SIZE    1024

#define PRES_SERIE_SUFFIX    "_%04d"


/* following definitions were originally defined as global const int */
#define IOPFILEAPPEND    1
#define IOPFILEOVERWRITE 2

#define IOPOK 255
#define IOPFALSE 0
#define IOPNOSECTION 100

/* ignore LastChar */
#define IOPIGNORECHAR 1
/* ignore end of line */
#define IOPIGNORELINE 2

#define IOPNEVER 0
#define IOPYES 1
#define IOPYESIFNDEF 2


/* TRUE, FALSE constants */

#ifdef TRUE
#undef TRUE
#endif
#ifdef FALSE
#undef FALSE
#endif

#define TRUE  1
#define FALSE 0


#endif
