#ifndef GENERAL_H
#define GENERAL_H
// all the system #include's we'll ever need
/*#include <fstream>
#include <cmath>
#include <complex>
#include <iostream>
#include <iomanip>
#include <vector>
#include <limits>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>
*/
#include "control.h"
#include "nr3.h"
#include <cstdlib>

#ifdef KILL_HANDLER
#include_next "signal.h"
#endif //KILL_HANDLER

/*
// TODO: make ALL members static!! (const parece no funcionar)
class ESCALAS{
    public:
        ESCALAS(void){};
        void build(const Doub);
        Doub Bo;              // [] campo B *constante*
        Doub rl;              // [cm] radio larmor
        Doub wc;              // [s^-1] freq ciclotron
        Doub vel;             // [cm/s] velocidad
        Doub beta;
        Doub gamma;
        #ifdef CYTHON
        const static Doub _clight = clight;
        const static Doub _AU_in_cm = AU_in_cm;
        const static Doub _nT_in_G = nT_in_G;
        #endif //CYTHON
    private:
        Doub mo;// = (1.6726*1e-24);        // [gr] masa PROTON
        Doub Ereposo;// = 938272013.0;      // [eV] energia de reposo PROTON
        Doub Z;// = +1.;                    // [e] carga (positiva) del proton en unidades de carga electronica
        Doub q;// = (4.8032*1e-10);         // [statC] carga PROTON
        Doub B;// = 5e-5;                   // [G] 5nT en Gauss
};


extern ESCALAS scl;    // global instance
*/
#endif //GENERAL_H
