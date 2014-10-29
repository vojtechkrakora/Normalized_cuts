
/* FIT 2014 - main file */

#include "Segmenter.h"
#include "DyXML_wrapper.h"
#include <stdlib.h>
#include <stdio.h>


class MySegmenter : public Segmenter {
  virtual int postprocessing(DyXML_wrapper &par);
};


int MySegmenter::postprocessing(DyXML_wrapper &par) {
  Segmenter::postprocessing(par);

  printf("hello\n");

  return 0;
}


int main(int argc, char* argv[]) {
  DyXML_wrapper par(argc,argv,"Segmenter");

  par.init_runs();
  while (par.next_run()) {
    MySegmenter seg;

    seg.run(par);
  }

  return 0;
}
