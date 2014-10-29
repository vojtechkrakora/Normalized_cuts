
/* FIT 2014 - segmenter header file */

#include "DyXML_wrapper.h"

class Segmenter {

  int nr, nc;       // size rows, columns

  int nimg;         // number of image planes
  float*** img;     // image data

  int nfeat;        // feature vector length
  float*** feat;    // features

  int nclust;       // number of clusters
  float*** probs;   // probabilistic maps (can be 0/1)

  int** final;      // final segmentation

public:

  Segmenter();
  ~Segmenter();

  int run(DyXML_wrapper &par);

  int load_img(DyXML_wrapper &par);
  int save_final(DyXML_wrapper &par);
  int thematic_map(DyXML_wrapper &par);

  virtual int features(DyXML_wrapper &par);
  virtual int clustering(DyXML_wrapper &par);
  virtual int postprocessing(DyXML_wrapper &par);

};
