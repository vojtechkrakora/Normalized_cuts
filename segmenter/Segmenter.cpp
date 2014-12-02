
/* FIT 2014 - segmenter implementation file */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "Global.h"
#include "Segmenter.h"
#include "TBAlloc.h"
#include "Pres2.h"
#include "Maths.h"
#include "KMeans.h"
#include "NCut.h"


Segmenter::Segmenter() {
  img=NULL; feat=NULL; probs=NULL; final=NULL;
  nr=0; nc=0; nimg=0; nfeat=0; nclust=0;
}

Segmenter::~Segmenter() {
  vr_free(img,0,nimg-1,0,nr-1,0,nc-1); vr_free(feat,0,nfeat-1,0,nr-1,0,nc-1);
  vr_free(probs,0,nclust-1,0,nr-1,0,nc-1); vr_free(final,0,nr-1,0,nc-1);
}


int Segmenter::run(DyXML_wrapper &par) {

  par.get_val_req(nr,"nr","Enter input images size (NR x NC):"); par.get_val_req(nc,"nc");

  load_img(par);
  features(par);
  clustering(par);
  postprocessing(par);
  save_final(par);

  return 0;
}


int Segmenter::load_img(DyXML_wrapper &par) {
  int key, ncolour, nlev;
  const char *filename;

  par.get_str_req(filename,"ImgFile","Enter name of image:");
  par.get_val_opt(key,"ImgType",PRES_READ_KEY_PNG,"Enter image format code:");
  par.get_val_opt(nimg,"planes",3,"Number of planes:");

  vr_alloc(img,0,nimg-1,0,nr-1,0,nc-1);

  ncolour=nimg-1; nlev=255;
  pres2(key,img,&nc,&nr,&ncolour,&nlev,filename);

  return 0;
}


int Segmenter::features(DyXML_wrapper &par) {
  float sigma, *w0, **w, norm, val;
  int i,r,c,d,rr,cc,key,rgb2lab;
  const char *filename;

  par.select("features");
  par.get_val_opt(sigma,"sigma",1.0f,"Sigma:");
  par.get_val_opt(d,"win",3,"Window size:");
  par.get_val_opt(rgb2lab,"rgb2lab",0,"Convert from RGB into Lab? (0/1)");
  par.back();

  if (rgb2lab) imgRGB2Lab(img,nr,nc);
  
  vr_alloc(w0,-d,d); vr_alloc(w,-d,d,-d,d);
  for (i=-d;i<=d;i++) w0[i]=exp(-pow(i/sigma,2)/2);
  for (rr=-d;rr<=d;rr++) for (cc=-d;cc<=d;cc++) w[rr][cc]=w0[rr]*w0[cc];

  nfeat=nimg;
  vr_alloc(feat,0,nfeat-1,0,nr-1,0,nc-1);

  for (r=0;r<nr;r++) for (c=0;c<nc;c++) {

    norm=0; for (i=0;i<nimg;i++) feat[i][r][c]=0;

    for (rr=-d;rr<=d;rr++) for (cc=-d;cc<=d;cc++) if (r+rr>=0&&r+rr<nr&&c+cc>=0&&c+cc<nc) {
      val=w[rr][cc]; norm+=val;
      for (i=0;i<nimg;i++) feat[i][r][c]+=val*img[i][r+rr][c+cc];
    }

    if (norm) for (i=0;i<nimg;i++) feat[i][r][c]/=norm;
  }

  vr_alloc(w0,-d,d); vr_free(w,-d,d,-d,d);

  par.get_str_opt(filename,"FeatFile",NULL,"Enter name of features:");
  par.get_val_opt(key,"FeatType",PRES_WRITE_KEY_PNG,"Enter features format code:");
  if (filename) { int ncolour=nfeat-1, nlev=255; pres2(key,feat,&nc,&nr,&ncolour,&nlev,filename); }
  return 0;
}

int Segmenter::clustering(DyXML_wrapper &par) {
  int nclust=2;
  par.get_val_req(nclust,"clusters","Enter number of clusters:");
  
  if(nr>64){
      // resize picture
  }
  NCut nCut(img,nr,nc,3,nclust);

  nCut.Segmentation();
  final =nCut.getResult();

  
  //zapis do souboru
 /* int key;
  const char * filename;
  par.get_str_opt(filename,"FeatFile",NULL,"Enter name of features:");
  par.get_val_opt(key,"FeatType",PRES_WRITE_KEY_PNG,"Enter features format code:");
  pres2(key,img,&nc,&nr,new int(5),new int(6),filename);*/
  return 0;
}

/*int Segmenter::clustering(DyXML_wrapper &par) {
  int i,r,c, niter, norm;
  float neigh;

  par.get_val_req(nclust,"clusters","Enter number of clusters:");
  par.get_val_opt(niter,"iterations",100,"Enter maximum number of iterations:");
  par.get_val_opt(neigh,"neigh",0.0f,"Enter neighbourhood weight (0 .. w/o neighbourhood):");
  par.get_val_opt(norm,"norm",0,"Normalize values? (0/1):");

  vr_alloc(probs,0,nclust-1,0,nr-1,0,nc-1);
  for (r=0;r<nr;r++) for (c=0;c<nc;c++) for (i=0;i<nclust;i++) probs[i][r][c]=128;

  KMeans kmeans(nclust,nr,nc,nfeat+((neigh!=0)?2:0));

  for (r=0;r<nr;r++) for (c=0;c<nc;c++) for (i=0;i<nfeat;i++) kmeans.arr[i][r][c]=feat[i][r][c];
  if (neigh!=0) for (r=0;r<nr;r++) for (c=0;c<nc;c++) { kmeans.arr[nfeat][r][c]=neigh*r/(float)(nr-1); kmeans.arr[nfeat+1][r][c]=neigh*c/(float)(nc-1); }

  kmeans.initialize(norm);
  kmeans.compute(niter);

  for (r=0;r<nr;r++) for (c=0;c<nc;c++) probs[(kmeans.ind[r][c]<0)?0:kmeans.ind[r][c]][r][c]=1;
  int key;
  const char * filename;
  par.get_str_opt(filename,"FeatFile",NULL,"Enter name of features:");
  par.get_val_opt(key,"FeatType",PRES_WRITE_KEY_PNG,"Enter features format code:");
  pres2(key,kmeans.arr,&nc,&nr,new int(5),new int(6),filename);

  return 0;
}
*/

int Segmenter::thematic_map(DyXML_wrapper &par) {
  int i,r,c,m;
  float max;

  vr_alloc(final,0,nr-1,0,nc-1);

  for (r=0;r<nr;r++) for (c=0;c<nc;c++) {
    m=0; max=0;
    for (i=0;i<nclust;i++) if (probs[i][r][c]>max) { max=probs[i][r][c]; m=i; }
    final[r][c]=m;
  }

  return 0;
}


int Segmenter::postprocessing(DyXML_wrapper &par) {

  thematic_map(par);

//  par.select("postprocessing");

//  /* read parameters and do something */

//  par.back();

  return 0;
}


int Segmenter::save_final(DyXML_wrapper &par) {
  int key, ncolour, nlev;
  const char *filename;

  par.get_str_req(filename,"OutFile","Enter name of output:");
  par.get_val_opt(key,"OutType",PRES_WRITE_KEY_PNG,"Enter image format code:");

  ncolour=0; nlev=nclust;
  pres2op(key,&final,&nc,&nr,&ncolour,&nlev,filename,0);
	
  return 0;
}

