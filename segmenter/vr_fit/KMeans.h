
/* FIT 2014 - k-means clustering */

#ifndef KMeans_c
#define KMeans_c

class KMeans {

 public:

   float *** dist;      //! vzdalenost od stredu
   float * changes;     //! zmeny stredu shluku
   float ** centers;    //! stredy shluku
   float ** values;     //! soucty hodnot
   float * weights;     //! vahy souradnic
   int * card;          //! kardinalita shluku

   int nk, nr, nc, nm;  //! pocet shluku, dimenze
   float *** arr;       //! hodnoty
   int ** ind;          //! indexy shluku

   KMeans(int nk, int nr, int nc, int nm);
   ~KMeans();

   int initialize(int norm);   //! norm ... (0/1) - use normalized weights
   int compute(int np);        //! np ... maximum iterations
};

#endif
