#ifndef CONTROL
#define CONTROL

//#define CYTHON     1 // stuff for cython handling
#define KILL_HANDLER 1 // removes current *.owned files
#define MONIT_SCATTERING 1 // monitorea scattering de plas
#define MONIT_STEP 1 // monitorea el step
#define BETA_CHECK 1 // checkea q siempre beta<1
#define NVAR    (6)

//--------------------------------------CTES UNIVERSALES
#define SIM_MAXSTP      (150*50000) // max nuber of steps in Odeint
#define clight          (3.0*1e10)              // [cm/s]
#define AU_in_cm        (1.5e13)                // [cm]
#define nT_in_G         (1.0*1e-5)              // [1G=1e5nT]

//----- operations
#define NORM(x,y,z)  (sqrt(x*x+y*y+z*z))


//--- some members better be public, when cython is ON
#ifdef CYTHON
    #define PRIVATE_OR_PUBLIC public
#else
    #define PRIVATE_OR_PUBLIC private
#endif //CYTHON


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++ turbulence spectrum (Shalchi or Giacalone-Jokipii) +++++++++

// Shalchi (Nonlinear CR Diffusion Theories)
#define SPECTRA_SHALCHI_2D(x)   pow(1. + x,(-5./6.))/x
#define SPECTRA_SHALCHI_SLAB(x) pow(1. + x,(-5./6.)) 
// Giacalone & Jokipii (1999)
#define SPECTRA_GJ99_2D(x)   1./(1. + pow(x,(8./3.)))
#define SPECTRA_GJ99_SLAB(x) 1./(1. + pow(x,(5./3.)))

//--- choose spectra shape (from above options)
#define SPECTRA_2D(x)       SPECTRA_GJ99_2D(x)
#define SPECTRA_SLAB(x)     SPECTRA_GJ99_SLAB(x)
//#define SPECTRA_2D(x)       SPECTRA_SHALCHI_2D(x)
//#define SPECTRA_SLAB(x)     SPECTRA_SHALCHI_SLAB(x)
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


#endif //CONTROL
