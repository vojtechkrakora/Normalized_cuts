/* FIT 2014 - DyXML wrapper for easier XML parameter file reading/writing



  supposed XML parameter input file structure:
 ----------------------------------------------------------------

  <main>
    <var name="nrun"        rem="number of runs"> 1 </var>
    <var name="prefix"      rem="section prefix"> run </var>
    <var name="from"        rem="run from index"> 1 </var>
    <!-- global vars and sections -->
    <section name="run_!1">
      <!-- local vars and sections -->
    </section>
    <!-- run_!2, ... -->
  </main> 

 ----------------------------------------------------------------


  usage scenario:
 ----------------------------------------------------------------

  int main(int argc, char *argv[]) {
    // ...

    // class constructor
    DyXML_wrapper par(argc,argv,"AppName");

    // reading global flags
    par.get_val_opt(flag,"flag",0,"Global flag:");

    // loop and output initialization  
    par.init_output(DYXMLW_OUTPUT_INDEPENDENT); par.init_runs();

    // select next run
    while (par.next_run()) {

      // required or optional parameters
      par.get_val_req(ncolour,"ncolour","Enter number of input planes:");
      par.get_val_req(nr,"nr","Enter size of the input image NRxNC:"); par.get_val_req(nc,"nc");
      par.get_str_req(ImgName,"iImgName","Enter input image name (without extension):");
      par.get_val_opt(ImgType,"iImgType",301,"Enter input image type:");

      // array length (nfactor) is detected automatically; array is allocated if =NULL
      factor=NULL; coef=NULL; nfactor=DYXMLW_DETECT_ARRAY_LEN;  // par.get_val_opt(nfactor,"nfactor",1,"Enter number of factors:");
      par.get_arr_val(factor,"factor",nfactor,"Enter factor:");  // vr_alloc(factor,0,nfactor);
      par.get_arr_opt(coef,"coef",nfactor,(TREAL)1.0,"Enter coeficient:");    // vr_alloc(coef,0,nfactor);

      // hexadecimal values support  0x0123
      if (par.get_hex_opt(flags,"invar_flags",flags,"Enter invariance flags:")==DYXMLW_DEF_WRONGHEX)
       par.get_val_opt(flags,"invar_flags",flags,"Enter invariance flags:");

      ///save=0;
      ///par.get_bit_opt(save,SAVE_MEAN,"mean",0,"Save mean as parameter? (0/1):");
      ///par.get_bit_opt(save,SAVE_NOISE,"noise",0,"Save noise_var as parameter? (0/1):");
      ///par.get_bit_opt(save,SAVE_PLANE,"plane",0,"Save parameter planes? (0/1):");

      // select named section and return back after
      if (par.select("neighbourhood")) { load_neigh_settings(par,c,ModelOrder,NeighCorr,NeighSize,Threshold); par.back(); }

      // do something ...
    }

    // ...
  }

 ----------------------------------------------------------------


*/


#ifndef DyXML_wrapper_h
#define DyXML_wrapper_h

#include <stdlib.h>
#include "Global.h"

#define DYXMLW__NRUN__NAME                "nrun"

#define DYXMLW_DEFAULT_PREFIX              "run"
#define DYXMLW_DEFAULT_FROM                    1
#define DYXMLW_DEFAULT_NRUN                    1

#define DYXMLW_MAX_NESTED_LEVEL               63
#define DYXMLW_ERROR_NESTED_LEVEL             -1
#define DYXMLW_ZERO_NESTED_LEVEL               0

#define DYXMLW_INIT_RUNS_DEFAULT          0x1717
#define DYXMLW_NEXT_RUN_DEFAULT           0x0320

#define DYXMLW_OUTPUT_INDEPENDENT              0
#define DYXMLW_OUTPUT_SYNCHRONIZED             1
#define DYXMLW_OUTPUT_SAME_AS_INPUT            2

#define DYXMLW_VALUE_CONFIG                   -1  // not implemented yet -> value required
#define DYXMLW_VALUE_OPTIONAL                  0
#define DYXMLW_VALUE_REQUIRED                  1
#define DYXMLW_ARRAY_REQUIRED                  2

#define DYXMLW_SECTION_CONFIG                 -1  // not implemented yet -> section add
#define DYXMLW_SECTION_SELECT                  0
#define DYXMLW_SECTION_ADD                     1

#define DYXMLW_DETECT_ARRAY_LEN               -1  // get_arr*() functions array size detection
#define DYXMLW_USE_RUN_AS_ARG             -32767  // use 'run' variable for %d argument in prompt
#define DYXMLW_DO_NOT_USE_ARG             -32766  

#define DYXMLW_LOOP_RUN                        1
#define DYXMLW_LOOP_STOP                       0

#define DYXMLW_ERROR                           0
#define DYXMLW_OK                              1
#define DYXMLW_DEF                             2
#define DYXMLW_DEF_WRONGHEX                    3


class DyXML_wrapper {

  int from, nrun, run;
  int level, olevel;

  int pop();                                    // restores pointers; returns current nested level
  int clear();                                  // resets to root pointers; returns current nested level

  int opop();                                   // returns current nested level; must be in the independent mode
  int oclear();                                 // returns current nested level; must be in the independent mode

public:

  DyXML_wrapper(const char* _app_name=NULL, int _state=IOPOK);
  DyXML_wrapper(const char* filename, const char* _app_name=NULL, int _state=IOPOK);
  DyXML_wrapper(int argc, char* argv[], const char* _app_name=NULL, int _state=IOPOK);
  ~DyXML_wrapper();

  // loads parameters nrun, from, prefix from DyXML and prepare for next_run(); returns number of runs, or -1 if error
  int init_runs(int flags=DYXMLW_INIT_RUNS_DEFAULT, const char* _nrun=DYXMLW__NRUN__NAME, const char* _prefix=DYXMLW_DEFAULT_PREFIX, int _from=DYXMLW_DEFAULT_FROM, int _runs=DYXMLW_DEFAULT_NRUN, const char* prompt=NULL);
  // select next 'run' section; return 0/1 for while loop
  int next_run(int flags=DYXMLW_NEXT_RUN_DEFAULT);
  // set 'run' section
  int set_run(int flags=DYXMLW_NEXT_RUN_DEFAULT, int loop1=DYXMLW_USE_RUN_AS_ARG);
  // select section (if output is synchronized, creates new section too)
  int select(const char* section, int req=DYXMLW_VALUE_CONFIG, int add=DYXMLW_SECTION_CONFIG, const char* prompt=NULL, int arg=DYXMLW_USE_RUN_AS_ARG);
  int select_i(const char* section, int i, int req=DYXMLW_VALUE_CONFIG, int add=DYXMLW_SECTION_CONFIG, const char* prompt=NULL, int arg=DYXMLW_USE_RUN_AS_ARG);

  int set_out(const char* prefix, int flags=DYXMLW_NEXT_RUN_DEFAULT, int loop1=DYXMLW_USE_RUN_AS_ARG, int loop2=DYXMLW_USE_RUN_AS_ARG, int loop3=DYXMLW_USE_RUN_AS_ARG);
  int output_section(const char* section, int req=DYXMLW_VALUE_CONFIG, int add=DYXMLW_SECTION_CONFIG);  // must be in the independent mode

  // initializing DyXML output
  int init_output(int _synchronized=DYXMLW_OUTPUT_SYNCHRONIZED);
  // save DyXML output to file
  int save_output(const char* filename);

  // return protected variables
  inline int get_run() { return run; }
  inline int get_nrun() { return nrun; }
  inline int get_from() { return from; }

  // DyXML input parameters
  inline int get_level() { return level; }
  inline int back() { return pop(); }
  inline int top() { return clear(); }

  // DyXML output
  inline int get_olevel() { return olevel; }
  inline int oback() { return opop(); }                                // must be in the independent mode
  inline int otop() { return oclear(); }                               // must be in the independent mode

  // load single value from DyXML
  template <typename val_type>  // val_type can be one of {int|long|float|double|char}
  int get_val(val_type &val, const char *name, int req=DYXMLW_VALUE_CONFIG, val_type def=(val_type)(0), const char* prompt=NULL, int arg=DYXMLW_USE_RUN_AS_ARG);
  template <typename val_type>  // val_type can be one of {int|long|float|double|char}
  inline int get_val_req(val_type &val, const char* name, const char* prompt=NULL, int arg=DYXMLW_USE_RUN_AS_ARG) { return get_val(val,name,DYXMLW_VALUE_REQUIRED,(val_type)(0),prompt,arg); }
  template <typename val_type>  // val_type can be one of {int|long|float|double|char}
  inline int get_val_opt(val_type &val, const char* name, val_type def=(val_type)(0), const char* prompt=NULL, int arg=DYXMLW_USE_RUN_AS_ARG) { return get_val(val,name,DYXMLW_VALUE_OPTIONAL,def,prompt,arg); }

  // load 1D array from DyXML; can detect array dimension; can allocate memory for it; if 'name' is value, can fill array with it; if 'name' not found, 'def' can be used
  template <typename val_type>  // val_type can be one of {int|long|float|double}
  int get_arr(val_type* &arr, const char* name, int &len1, int req=DYXMLW_VALUE_CONFIG, val_type def=(val_type)(0), const char* prompt=NULL, int arg=DYXMLW_USE_RUN_AS_ARG);
  template <typename val_type>  // val_type can be one of {int|long|float|double}
  inline int get_arr_req(val_type* &arr, const char* name, int &len1, const char* prompt=NULL, int arg=DYXMLW_USE_RUN_AS_ARG) { return get_arr(arr,name,len1,DYXMLW_ARRAY_REQUIRED,(val_type)(0),prompt,arg); }
  template <typename val_type>  // val_type can be one of {int|long|float|double}
  inline int get_arr_val(val_type* &arr, const char* name, int &len1, const char* prompt=NULL, int arg=DYXMLW_USE_RUN_AS_ARG) { return get_arr(arr,name,len1,DYXMLW_VALUE_REQUIRED,(val_type)(0),prompt,arg); }
  template <typename val_type>  // val_type can be one of {int|long|float|double}
  inline int get_arr_opt(val_type* &arr, const char* name, int &len1, val_type def=(val_type)(0), const char* prompt=NULL, int arg=DYXMLW_USE_RUN_AS_ARG) { return get_arr(arr,name,len1,DYXMLW_VALUE_OPTIONAL,def,prompt,arg); }

  // load 2D array from DyXML; can detect array dimension; can allocate memory for it; if 'name' is value, can fill array with it; if 'name' not found, 'def' can be used
  template <typename val_type>  // val_type can be one of {int|long|float|double}
  int get_arr(val_type** &arr, const char* name, int &len1, int &len2, int req, val_type def, const char* prompt, int arg);
  template <typename val_type>  // val_type can be one of {int|long|float|double}
  inline int get_arr_req(val_type** &arr, const char* name, int &len1, int &len2, const char* prompt=NULL, int arg=DYXMLW_USE_RUN_AS_ARG) { return get_arr(arr,name,len1,len2,DYXMLW_ARRAY_REQUIRED,(val_type)(0),prompt,arg); }
  template <typename val_type>  // val_type can be one of {int|long|float|double}
  inline int get_arr_val(val_type** &arr, const char* name, int &len1, int &len2, const char* prompt=NULL, int arg=DYXMLW_USE_RUN_AS_ARG) { return get_arr(arr,name,len1,len2,DYXMLW_VALUE_REQUIRED,(val_type)(0),prompt,arg); }
  template <typename val_type>  // val_type can be one of {int|long|float|double}
  inline int get_arr_opt(val_type** &arr, const char* name, int &len1, int &len2, val_type def=(val_type)(0), const char* prompt=NULL, int arg=DYXMLW_USE_RUN_AS_ARG) { return get_arr(arr,name,len1,len2,DYXMLW_VALUE_OPTIONAL,def,prompt,arg); }

  // load 3D array from DyXML; can detect array dimension; can allocate memory for it; if 'name' is value, can fill array with it; if 'name' not found, 'def' can be used
  template <typename val_type>  // val_type can be one of {int|long|float|double}
  int get_arr(val_type*** &arr, const char* name, int &len1, int &len2, int &len3, int req, val_type def, const char* prompt, int arg);
  template <typename val_type>  // val_type can be one of {int|long|float|double}
  inline int get_arr_req(val_type*** &arr, const char* name, int &len1, int &len2, int &len3, const char* prompt=NULL, int arg=DYXMLW_USE_RUN_AS_ARG) { return get_arr(arr,name,len1,len2,len3,DYXMLW_ARRAY_REQUIRED,(val_type)(0),prompt,arg); }
  template <typename val_type>  // val_type can be one of {int|long|float|double}
  inline int get_arr_val(val_type*** &arr, const char* name, int &len1, int &len2, int &len3, const char* prompt=NULL, int arg=DYXMLW_USE_RUN_AS_ARG) { return get_arr(arr,name,len1,len2,len3,DYXMLW_VALUE_REQUIRED,(val_type)(0),prompt,arg); }
  template <typename val_type>  // val_type can be one of {int|long|float|double}
  inline int get_arr_opt(val_type*** &arr, const char* name, int &len1, int &len2, int &len3, val_type def=(val_type)(0), const char* prompt=NULL, int arg=DYXMLW_USE_RUN_AS_ARG) { return get_arr(arr,name,len1,len2,len3,DYXMLW_VALUE_OPTIONAL,def,prompt,arg); }

  // load 4D array from DyXML; can detect array dimension; can allocate memory for it; if 'name' is value, can fill array with it; if 'name' not found, 'def' can be used
  template <typename val_type>  // val_type can be one of {int|long|float|double}
  int get_arr(val_type**** &arr, const char* name, int &len1, int &len2, int &len3, int &len4, int req, val_type def, const char* prompt, int arg);
  template <typename val_type>  // val_type can be one of {int|long|float|double}
  inline int get_arr_req(val_type**** &arr, const char* name, int &len1, int &len2, int &len3, int &len4, const char* prompt=NULL, int arg=DYXMLW_USE_RUN_AS_ARG) { return get_arr(arr,name,len1,len2,len3,len4,DYXMLW_ARRAY_REQUIRED,(val_type)(0),prompt,arg); }
  template <typename val_type>  // val_type can be one of {int|long|float|double}
  inline int get_arr_val(val_type**** &arr, const char* name, int &len1, int &len2, int &len3, int &len4, const char* prompt=NULL, int arg=DYXMLW_USE_RUN_AS_ARG) { return get_arr(arr,name,len1,len2,len3,len4,DYXMLW_VALUE_REQUIRED,(val_type)(0),prompt,arg); }
  template <typename val_type>  // val_type can be one of {int|long|float|double}
  inline int get_arr_opt(val_type**** &arr, const char* name, int &len1, int &len2, int &len3, int &len4, val_type def=(val_type)(0), const char* prompt=NULL, int arg=DYXMLW_USE_RUN_AS_ARG) { return get_arr(arr,name,len1,len2,len3,len4,DYXMLW_VALUE_OPTIONAL,def,prompt,arg); }


  // load string from DyXML
  int get_str(const char* &str, const char *name, int req=DYXMLW_VALUE_CONFIG, const char* def=NULL, const char* prompt=NULL, int arg=DYXMLW_USE_RUN_AS_ARG);
  inline int get_str_req(const char* &str, const char* name, const char* prompt=NULL, int arg=DYXMLW_USE_RUN_AS_ARG) { return get_str(str,name,DYXMLW_VALUE_REQUIRED,NULL,prompt,arg); }
  inline int get_str_opt(const char* &str, const char* name, const char* def=NULL, const char* prompt=NULL, int arg=DYXMLW_USE_RUN_AS_ARG) { return get_str(str,name,DYXMLW_VALUE_OPTIONAL,def,prompt,arg); }

  // load string array from DyXML
  int get_str(const char** &arr, const char* name, int &len1, int req=DYXMLW_VALUE_CONFIG, const char* def=NULL, const char* prompt=NULL, int arg=DYXMLW_USE_RUN_AS_ARG);
  inline int get_str_req(const char** &arr, const char* name, int &len1, const char* prompt=NULL, int arg=DYXMLW_USE_RUN_AS_ARG) { return get_str(arr,name,len1,DYXMLW_ARRAY_REQUIRED,NULL,prompt,arg); }
  inline int get_str_val(const char** &arr, const char* name, int &len1, const char* prompt=NULL, int arg=DYXMLW_USE_RUN_AS_ARG) { return get_str(arr,name,len1,DYXMLW_VALUE_REQUIRED,NULL,prompt,arg); }
  inline int get_str_opt(const char** &arr, const char* name, int &len1, const char* def=NULL, const char* prompt=NULL, int arg=DYXMLW_USE_RUN_AS_ARG) { return get_str(arr,name,len1,DYXMLW_VALUE_OPTIONAL,def,prompt,arg); }


  // load binary value from DyXML; set 'var' by 'msk'
  int get_bit(int &var, int msk, const char* name, int req=DYXMLW_VALUE_CONFIG, int def=FALSE, const char* prompt=NULL, int arg=DYXMLW_USE_RUN_AS_ARG);
  inline int get_bit_req(int &var, int msk, const char* name, const char* prompt=NULL, int arg=DYXMLW_USE_RUN_AS_ARG) { return get_bit(var,msk,name,DYXMLW_VALUE_REQUIRED,FALSE,prompt,arg); }
  inline int get_bit_opt(int &var, int msk, const char* name, int def=FALSE, const char* prompt=NULL, int arg=DYXMLW_USE_RUN_AS_ARG) { return get_bit(var,msk,name,DYXMLW_VALUE_OPTIONAL,def,prompt,arg); }

  // load hex value from DyXML
  int get_hex(int &hex, const char *name, int req=DYXMLW_VALUE_CONFIG, int def=0, const char* prompt=NULL, int arg=DYXMLW_USE_RUN_AS_ARG);
  inline int get_hex_req(int &hex, const char* name, const char* prompt=NULL, int arg=DYXMLW_USE_RUN_AS_ARG) { return get_hex(hex,name,DYXMLW_VALUE_REQUIRED,0,prompt,arg); }
  inline int get_hex_opt(int &hex, const char* name, int def=0, const char* prompt=NULL, int arg=DYXMLW_USE_RUN_AS_ARG) { return get_hex(hex,name,DYXMLW_VALUE_OPTIONAL,def,prompt,arg); }


  // store single value into DyXML output; val_type can be one of {int|long|float|double|char}
  template <typename val_type> int set_val(const char* name, val_type val, int req=DYXMLW_VALUE_CONFIG);

  // store 1D-4D array into DyXML output (name should contain dimensions); val_type can be one of {int|long|float|double|char}
  template <typename val_type> int set_arr(const char* name_n0, val_type const* arr, int req=DYXMLW_VALUE_CONFIG);
  template <typename val_type> int set_arr(const char* name_n0_n1, val_type const*const* arr, int req=DYXMLW_VALUE_CONFIG);
  template <typename val_type> int set_arr(const char* name_n0_n1_n2, val_type const*const*const* arr, int req=DYXMLW_VALUE_CONFIG);
  template <typename val_type> int set_arr(const char* name_n0_n1_n2_n3, val_type const*const*const*const* arr, int req=DYXMLW_VALUE_CONFIG);

  // store 1D-4D array into DyXML output; val_type can be one of {int|long|float|double|char}
  template <typename val_type> int set_arr(const char* name, int n0, val_type const* arr, int req=DYXMLW_VALUE_CONFIG);
  template <typename val_type> int set_arr(const char* name, int n0, int n1, val_type const*const* arr, int req=DYXMLW_VALUE_CONFIG);
  template <typename val_type> int set_arr(const char* name, int n0, int n1, int n2, val_type const*const*const* arr, int req=DYXMLW_VALUE_CONFIG);
  template <typename val_type> int set_arr(const char* name, int n0, int n1, int n2, int n3, val_type const*const*const*const* arr, int req=DYXMLW_VALUE_CONFIG);

  // store string into DyXML output
  int set_str(const char* name, const char* str, int req=DYXMLW_VALUE_CONFIG);

  // store string array into DyXML output
  int set_str(const char* name, const char** arr, int n0, int req=DYXMLW_VALUE_CONFIG);

  // store hex value into DyXML output
  int set_hex(const char* name, int hex, int req=DYXMLW_VALUE_CONFIG);

};


#endif  // DyXML_wrapper_h
