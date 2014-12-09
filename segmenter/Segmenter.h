
/* FIT 2014 - segmenter header file */

#include "DyXML_wrapper.h"


// Computes gaussian blur
int gaussian_blur(float sigma, int d, int nr, int nc, int np, float ***in, float ***out);

// Finds disjoint regions and discards small of them
int distinct_regions(int nr, int nc, int** in, int** out, int min_area, int single, int w4, int w8);

// Computes image borders and optionally saves input image with embedded borders
int image_borders(int nr, int nc, int nimg, int** final, int** out, float level, float*** img, int key, const char* filename);


class Segmenter {

  int nr, nc;       // size rows, columns of the image

  int nimg;         // number of input image planes
  float*** img;     // input image data  [0..nimg-1][0..nr-1][0..nc-1]

  int nfeat;        // feature vector length
  float*** feat;    // feature values  [0..nfeat-1][0..nr-1][0..nc-1]

  int nclust;       // number of clusters
  float*** probs;   // probabilistic maps (can be 0/1)  [0..nclust-1][0..nr-1][0..nc-1]

  int** final;      // final segmentation - index map  [0..nr-1][0..nc-1]

public:

// Constructor - initializes variables
  Segmenter();
// Destructor - frees memory
  ~Segmenter();

// Main method - calls appropriate functions
  int run(DyXML_wrapper &par);
// Loads input image
  int load_img(DyXML_wrapper &par);

// Reduce feature space by KL-transformation
  int reduce_space(DyXML_wrapper &par);
// Saves final segmentation and optionally saves image(s) with borders
  int save_final(DyXML_wrapper &par);
// Obtains segmentation from probability maps
  int thematic_map(DyXML_wrapper &par);

// Computes features from the input image
  virtual int features(DyXML_wrapper &par);
// Calculates clusters in the feature space
  virtual int clustering(DyXML_wrapper &par);
// Simple postprocessing - discards small regions
  virtual int postprocessing(DyXML_wrapper &par);

};