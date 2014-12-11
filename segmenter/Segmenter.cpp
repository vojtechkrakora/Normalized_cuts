
/* FIT 2014 - segmenter implementation file */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>

#include "Global.h"
#include "Segmenter.h"
#include "TBAlloc.h"
#include "Pres2.h"
#include "Maths.h"
#include "KMeans.h"
#include "NCut.h"


// Computes gaussian blur
int gaussian_blur(float sigma, int d, int nr, int nc, int np, float ***in, float ***out) {
  float *w0, **w, norm, val;
  int i,r,c,rr,cc;

  vr_alloc(w0,-d,d); vr_alloc(w,-d,d,-d,d);
  for (i=-d;i<=d;i++) w0[i]=exp(-pow(i/sigma,2)/2);
  for (rr=-d;rr<=d;rr++) for (cc=-d;cc<=d;cc++) w[rr][cc]=w0[rr]*w0[cc];

  for (r=0;r<nr;r++) for (c=0;c<nc;c++) {

    norm=0; for (i=0;i<np;i++) out[i][r][c]=0;

    for (rr=-d;rr<=d;rr++) for (cc=-d;cc<=d;cc++) if (r+rr>=0&&r+rr<nr&&c+cc>=0&&c+cc<nc) {
      val=w[rr][cc]; norm+=val;
      for (i=0;i<np;i++) out[i][r][c]+=val*in[i][r+rr][c+cc];
    }

    if (norm) for (i=0;i<np;i++) out[i][r][c]/=norm;
  }

  vr_free(w0,-d,d); vr_free(w,-d,d,-d,d);

  return 0;
}


// Auxiliary buffer functions
void push(int &head, int &tail, int size, int* br, int* bc, int r, int c) { if (tail>=size) { printf("regbuf overflow! (%d,%d)\n",r,c); return; }  br[tail]=r; bc[tail]=c; tail++; }
int pop(int &head, int &tail, int size, int* br, int* bc, int &r, int &c) { if (tail<=head) return -1;  r=br[head]; c=bc[head]; head++;  return 0; }

// Finds disjoint regions and discards small of them
int distinct_regions(int nr, int nc, int** in, int** out, int min_area, int single, int w4, int w8) {
  int i,j,r,c,rr,cc,n,k=0,l=0, head=0,tail=0,size=nr*nc;
  int *br, *bc, *map;

  vr_alloc(br,0,size); vr_alloc(bc,0,size); vr_alloc(map,0,size);

  for (i=0;i<size;i++) map[i]=INT_MIN;
  for (r=0;r<nr;r++) for (c=0;c<nc;c++) out[r][c]=INT_MIN;

  for (r=0;r<nr;r++) for (c=0;c<nc;c++) if (out[r][c]==INT_MIN) {
    n=0; k++; j=in[r][c]; push(head,tail,size,br,bc,r,c); out[r][c]=k;
    while (!pop(head,tail,size,br,bc,rr,cc)) {
      n++;
      if (rr>0&&out[rr-1][cc]==INT_MIN&&in[rr-1][cc]==j) { out[rr-1][cc]=k; push(head,tail,size,br,bc,rr-1,cc); }
      if (rr+1<nr&&out[rr+1][cc]==INT_MIN&&in[rr+1][cc]==j) { out[rr+1][cc]=k; push(head,tail,size,br,bc,rr+1,cc); }
      if (cc>0&&out[rr][cc-1]==INT_MIN&&in[rr][cc-1]==j) { out[rr][cc-1]=k; push(head,tail,size,br,bc,rr,cc-1); }
      if (cc+1<nc&&out[rr][cc+1]==INT_MIN&&in[rr][cc+1]==j) { out[rr][cc+1]=k; push(head,tail,size,br,bc,rr,cc+1); }
    }
    if (n<min_area) map[k]=INT_MIN; else if (single) map[k]=l++; else map[k]=j;
  }

  tail=0; head=0;
  for (r=0;r<nr;r++) for (c=0;c<nc;c++) { if (out[r][c]!=INT_MIN) out[r][c]=map[out[r][c]]; if (out[r][c]==INT_MIN) push(head,tail,size,br,bc,r,c); }
  l=tail;

  while (!pop(head,tail,size,br,bc,r,c)) {

    for (i=0;i<k;i++) map[i]=0;

    if (r>0&&out[r-1][c]>=0) map[out[r-1][c]]+=w4;
    if (r+1<nr&&out[r+1][c]>=0) map[out[r+1][c]]+=w4;
    if (c>0&&out[r][c-1]>=0) map[out[r][c-1]]+=w4;
    if (c+1<nc&&out[r][c+1]>=0) map[out[r][c+1]]+=w4;

    if (r>0&&c>0&&out[r-1][c-1]>=0) map[out[r-1][c-1]]+=w8;
    if (r+1<nr&&c>0&&out[r+1][c-1]>=0) map[out[r+1][c-1]]+=w8;
    if (r>0&&c+1<nc&&out[r-1][c+1]>=0) map[out[r-1][c+1]]+=w8;
    if (r+1<nr&&c+1<nc&&out[r+1][c+1]>=0) map[out[r+1][c+1]]+=w8;

    n=0; j=INT_MIN; for (i=0;i<k;i++) if (n<map[i]) { n=map[i]; j=i; }
    if (j>=0) out[r][c]=-j-1; else push(head,tail,size,br,bc,r,c);

    if (l==head) {
      for (i=head;i<tail;i++) { br[i-head]=br[i]; bc[i-head]=bc[i]; }
      tail=tail-head; head=0; l=tail;
      for (r=0;r<nr;r++) for (c=0;c<nc;c++) if (out[r][c]<0&&out[r][c]!=INT_MIN) out[r][c]=-out[r][c]-1;
    }
  }

  vr_free(br,0,size); vr_free(bc,0,size); vr_free(map,0,size);

  return k;
}


// Computes image borders and optionally saves input image with embedded borders
int image_borders(int nr, int nc, int nimg, int** final, int** out, float level, float*** img, int key, const char* filename) {
  int r,c, k,l, nlev=255, ncol=nimg-1;
  float ***arr;

  vr_alloc(arr,0,nimg-1,0,nr-1,0,nc-1);

  for (r=0;r<nr;r++) for (c=0;c<nc;c++) {

    if (!(k=final[r][c])||(r>0&&final[r-1][c]!=k)||(r<nr-1&&final[r+1][c]!=k)||(c>0&&final[r][c-1]!=k)||(c<nc-1&&final[r][c+1]!=k)) {

      for (l=0;l<nimg;l++) arr[l][r][c]=(int)((1-fabs(level))*img[l][r][c]+256*((level<0)?((k)?-level/2:-level):0));
      for (l=0;l<nimg;l++) if (arr[l][r][c]>nlev) nlev=(int)arr[l][r][c];
      out[r][c]=(k)?255:1;

    } else { out[r][c]=0; for (l=0;l<nimg;l++) arr[l][r][c]=(int)((1-fabs(level))*img[l][r][c]+256*((level<0)?0:level)); }
  }

  if (filename) pres2(key,arr,&nc,&nr,&ncol,&nlev,filename);

  vr_free(arr,0,nimg-1,0,nr-1,0,nc-1);

  return 0;
}


// Compute KL-transformation (PCA)
int kl_trans(float*** in, float*** out, int nr, int nc, int n0, int n1, int ofs=0) {
  double tmp, **tr, *m, **s, *d, *e, **s2;
  int rot, r,c, i,j, ndat=nr*nc;

  if (n0<n1||n0<n1+ofs) { printf("!kl_trans: n0=%d n1=%d ofs=%d\n",n0,n1,ofs); return -1; }

  vr_alloc(tr,0,n0,0,n0); vr_alloc(m,0,n0); vr_alloc(s,0,n0,0,n0);
  vr_alloc(d,0,n0); vr_alloc(e,0,n0); vr_alloc(s2,0,n0,0,n0);

  for (i=0;i<n0;i++) m[i]=0;
  for (i=0;i<n0;i++) for (r=0;r<nr;r++) { tmp=0;  for (c=0;c<nc;c++) tmp+=in[i][r][c];  m[i]+=tmp; }
  for (i=0;i<n0;i++) m[i]/=ndat;

  for (i=1;i<=n0;i++) for (j=1;j<=n0;j++) s[i][j]=0;
  for (r=0;r<nr;r++) {
    for (i=0;i<n0;i++) for (j=i;j<n0;j++) s2[i][j]=0;
    for (c=0;c<nc;c++) {
      for (i=0;i<n0;i++) d[i]=in[i][r][c]-m[i];
      for (i=0;i<n0;i++) for (j=i;j<n0;j++) s2[i][j]+=d[i]*d[j];
    }
    for (i=0;i<n0;i++) for (j=i;j<n0;j++) s[i+1][j+1]+=s2[i][j];
  }
  for (i=1;i<=n0;i++) for (j=i;j<=n0;j++) s[i][j]/=ndat-1;
  for (i=1;i<=n0;i++) for (j=1;j<i;j++) s[i][j]=s[j][i];

  printf("kl_trans:\n"); for (i=1;i<=n0;i++) { printf("s[%d]",i); for (j=1;j<=n0;j++) printf(" %g",s[i][j]); printf("\n"); }

  jacobi(s,n0,e,tr,&rot); eigsrt(e,tr,n0);

  printf("eig:"); for (i=1;i<=n0;i++) printf(" %g",e[i]); printf("\n");
  for (i=1;i<=n0;i++) { printf("tr[%d]",i); for (j=1;j<=n0;j++) printf(" %g",tr[i][j]); printf("\n"); }

  for (r=0;r<nr;r++) for (c=0;c<nc;c++) {
    for (i=1;i<=n0;i++) d[i]=in[i-1][r][c];
    for (i=1;i<=n1;i++) { tmp=0; for(j=1;j<=n0;j++) tmp+=d[j]*tr[j][i+ofs]; out[i-1][r][c]=tmp; }
  }

  vr_free(s2,0,n0,0,n0); vr_free(e,0,n0); vr_free(d,0,n0);
  vr_free(s,0,n0,0,n0); vr_free(m,0,n0); vr_free(tr,0,n0,0,n0);

  return 0;
}



////  Segmenter class definition  ////


// Constructor - initializes variables
Segmenter::Segmenter() {
  img=NULL; feat=NULL; probs=NULL; final=NULL;
  nr=0; nc=0; nimg=0; nfeat=0; nclust=0;
}

// Destructor - frees memory
Segmenter::~Segmenter() {
  vr_free(img,0,nimg-1,0,nr-1,0,nc-1); vr_free(feat,0,nfeat-1,0,nr-1,0,nc-1);
  vr_free(probs,0,nclust-1,0,nr-1,0,nc-1); vr_free(final,0,nr-1,0,nc-1);
}


// Main method - calls appropriate functions
int Segmenter::run(DyXML_wrapper &par) {

// load parameters
  par.get_val_req(nr,"nr","Enter input images size (NR x NC):"); par.get_val_req(nc,"nc");

// execute sequence
  load_img(par);
  features(par);
  reduce_space(par);
  clustering(par);
  postprocessing(par);
  save_final(par);

  return 0;
}


// Loads input image
int Segmenter::load_img(DyXML_wrapper &par) {
  int key, ncolour, nlev;
  const char *filename;

// load parameters
  par.get_str_req(filename,"ImgFile","Enter name of image:");
  par.get_val_opt(key,"ImgType",PRES_READ_KEY_PNG,"Enter image format code:");
  par.get_val_opt(nimg,"planes",3,"Number of planes:");

// allocate input image array
  vr_alloc(img,0,nimg-1,0,nr-1,0,nc-1);

// load input image
  ncolour=nimg-1; nlev=255;
  pres2(key,img,&nc,&nr,&ncolour,&nlev,filename);

  return 0;
}


// Computes features from the input image
int Segmenter::features(DyXML_wrapper &par) {
  float sigma, ***temp=NULL;
  const char *filename;
  int d,key,rgb2lab;

// load parameters
  par.select("features");
  par.get_val_opt(sigma,"sigma",1.0f,"Sigma:");
  par.get_val_opt(d,"win",3,"Window size:");
  par.get_val_opt(rgb2lab,"rgb2lab",0,"Convert from RGB into Lab? (0/1)");
  par.back();

  if (rgb2lab) {
// allocate temporary image array
    vr_alloc(temp,0,nimg-1,0,nr-1,0,nc-1);
// copy input to temporary
    for (int i=0;i<nimg;i++) for (int r=0;r<nr;r++) for (int c=0;c<nc;c++) temp[i][r][c]=img[i][r][c];
// convert to Lab
    imgRGB2Lab(temp,nr,nc);
  }
  
// feature vector size is the same as the number of planes of input image
  nfeat=nimg;
// allocate input image array
  vr_alloc(feat,0,nfeat-1,0,nr-1,0,nc-1);

// blur the features
  gaussian_blur(sigma,d,nr,nc,nimg,(temp)?temp:img,feat);

// free temporary image array
  vr_free(temp,0,nimg-1,0,nr-1,0,nc-1);

// load optional parameters
  par.get_str_opt(filename,"FeatFile",NULL,"Enter name of features:");
  par.get_val_opt(key,"FeatType",PRES_WRITE_KEY_PNG,"Enter features format code:");
// save features as image
  if (filename) { int ncolour=nfeat-1, nlev=255; pres2(key,feat,&nc,&nr,&ncolour,&nlev,filename); }

  return 0;
}


// Calculates clusters in the feature space
int Segmenter::clustering(DyXML_wrapper &par) {
  int i,r,c, niter, norm;
  float neigh;

// load parameters
  par.get_val_req(nclust,"clusters","Enter number of clusters:");
  par.get_val_opt(niter,"iterations",100,"Enter maximum number of iterations:");
  par.get_val_opt(neigh,"neigh",0.0f,"Enter neighbourhood weight (0 .. w/o neighbourhood):");
  par.get_val_opt(norm,"norm",0,"Normalize values? (0/1):");

// allocate probability maps array and initialize
  vr_alloc(probs,0,nclust-1,0,nr-1,0,nc-1);
  for (r=0;r<nr;r++) for (c=0;c<nc;c++) for (i=0;i<nclust;i++) probs[i][r][c]=0;
  NCut nCut(img,nr,nc,nclust);
  nCut.Segmentation();
  nCut.SetProbs(probs);
    
  return 0;
}


// Reduce feature space by KL-transformation
int Segmenter::reduce_space(DyXML_wrapper &par) {
  const char *filename;
  float ***temp;
  int kl, key;

// load parameters
  par.get_val_opt(kl,"kl_trans",0,"Feature vector size after KL trans. (0=no trans; <0 reduce the size):");

  if (kl==0) return 0;
  if (kl<0) kl+=nfeat;

// allocate temporary array
  vr_alloc(temp,0,kl-1,0,nr-1,0,nc-1);
// compute KL transormation
  kl_trans(feat,temp,nr,nc,nfeat,kl);
// swap and free temporary array
  vr_free(feat,0,nfeat-1,0,nr-1,0,nc-1);
  feat=temp; nfeat=kl;

// load optional parameters
  par.get_str_opt(filename,"KLFile",NULL,"Enter name of reduced features:");
  par.get_val_opt(key,"KLType",PRES_WRITE_KEY_PNG,"Enter reduced features format code:");
// save features as image
  if (filename) { int ncolour=nfeat-1, nlev=255; pres2(key,feat,&nc,&nr,&ncolour,&nlev,filename); }

  return 0;
}


// Obtains segmentation from probability maps
int Segmenter::thematic_map(DyXML_wrapper &par) {
  float max, th, sigma, ***temp;
  int i,r,c,m,d;

// load parameters
  par.select("thematic");
  par.get_val_opt(th,"prob_thresh",0.0f,"Min. prob. threshold:");
  par.get_val_opt(sigma,"sigma",1.0f,"Sigma:");
  par.get_val_opt(d,"win",0,"Window size:");
  par.back();

  if (d>0&&sigma>0) {
// allocate temporary array
    vr_alloc(temp,0,nclust-1,0,nr-1,0,nc-1);
// blur probability maps
    gaussian_blur(sigma,d,nr,nc,nclust,probs,temp);
// swap and free temporary array
    vr_free(probs,0,nclust-1,0,nr-1,0,nc-1);
    probs=temp;
  }

  
// allocate array for final segmentation
  vr_alloc(final,0,nr-1,0,nc-1);

// obtain thematic map
  for (r=0;r<nr;r++) for (c=0;c<nc;c++) {
    m=0; max=0;
    for (i=0;i<nclust;i++) if (probs[i][r][c]>max) { max=probs[i][r][c]; m=i+1; }
    final[r][c]=(max>=th)?m:0;
  }
  return 0;
}


// Simple postprocessing - discards small regions
int Segmenter::postprocessing(DyXML_wrapper &par) {
  int **temp, min_area, single;
  float f;

// obtain thematic map
  thematic_map(par);

// load parameters
  par.select("postprocessing");
  par.get_val_opt(f,"min_area",0.0f,"Minimum region area:");
  par.get_val_opt(single,"single",0,"Distinct regions? (0/1)");
  par.back();

  if (f<1) min_area=(int)(nr*nc*f); else min_area=(int)f;

// allocate temporary array
  vr_alloc(temp,0,nr-1,0,nc-1);
// discard small regions
  distinct_regions(nr,nc,final,temp,min_area,single,2,1);
// swap and free temporary array
  vr_free(final,0,nr-1,0,nc-1);
  final=temp;

  return 0;
}


// Saves final segmentation and optionally saves image(s) with borders
int Segmenter::save_final(DyXML_wrapper &par) {
  int **temp, key, key2, ncolour, nlev;
  const char *filename;
  float level;

// load parameters
  par.get_str_req(filename,"OutFile","Enter name of output:");
  par.get_val_opt(key,"OutType",PRES_WRITE_KEY_PNG,"Enter image format code:");

// save final segmentation
  ncolour=0; nlev=nclust;
  pres2op(key,&final,&nc,&nr,&ncolour,&nlev,filename,0);

// load optional parameters
  par.get_val_opt(key2,"ImgType",PRES_READ_KEY_PNG);
  par.get_str_opt(filename,"IwBFile",NULL,"Enter name of image with borders:");
  par.get_val_opt(level,"level",0.5f,"Image borders level [-1..+1]:");

// allocate temporary image array
  vr_alloc(temp,0,nr-1,0,nc-1);

// compute segmentation borders (optionally save input image with borders)
  image_borders(nr,nc,nimg,final,temp,level,img,pres_get_writekey(key2),filename);

// load optional parameter
  par.get_str_opt(filename,"EdgeFile",NULL,"Enter name of image borders:");

// optionally save border image
  ncolour=0; nlev=255;
  if (filename) pres2op(key,&temp,&nc,&nr,&ncolour,&nlev,filename,0);

// free temporary array
  vr_free(temp,0,nr-1,0,nc-1);

  return 0;
}


