#ifndef ODEINT_CC
#define ODEINT_CC
#include "nr3.h"
#include "funcs.h"
#include "odeintt.h"

template<class Stepper>
Odeint<Stepper>::Odeint(VecDoub_IO &ystartt, const Doub xx1, const Doub xx2,
    const Doub atol, const Doub rtol, const Doub h1, const Doub hminn,
    Output<Stepper> &outt,typename Stepper::Dtype &derivss, PARAMS parr,
    Int nHist, Int nThColl_, int wrankk) : 
    nvar(ystartt.size()),
    y(nvar),yold(nvar),dydx(nvar),ystart(ystartt),x(xx1),nok(0),nbad(0),
    x1(xx1),x2(xx2),hmin(hminn),dense(outt.dense),out(outt),derivs(derivss),
    s(y,dydx,x,atol,rtol,dense, parr), 
    par(parr), wrank(wrankk) {
    EPS=numeric_limits<Doub>::epsilon();
    h=SIGN(h1,x2-x1);
    for (Int i=0;i<nvar;i++) y[i]=ystart[i];
    out.init(s.neqn, x1, x2, nHist, nThColl_);
    //out.init(const Int neqn, const Doub xlo, const Doub xhi, Int nHist, Int nThColl_) {
}


#ifdef KILL_HANDLER
template<class Stepper>
void Odeint<Stepper>::abort_mission(int signum){
    printf(" [r:%d] ---> ABORTANDO SIMULACION (signal: %d): %s\n", wrank, signum, out.fname_owned);
    char syscommand[4000];
    sprintf(syscommand, "rm %s", out.fname_owned);
    if (system(syscommand)==0)
        printf(" [r:%d] removed: %s\n", wrank, out.fname_owned);
    else
        printf(" [r:%d] Couldn't remove!: %s\n", wrank, out.fname_owned);
}
#endif //KILL_HANDLER


template<class Stepper>
void Odeint<Stepper>::integrate() {
    #ifdef MONIT_STEP
    out.build_HistSeq(s);       // inicializa histog del "nseq"
    #endif

    int i=0;
    derivs(par, x, y, dydx);
    if (dense)
        out.out(-1,x,y,s,h);         // aqui solo guarda x,y
    else{
        out.save(x,y);
        i++;
        cout << " i " << i << endl;
    }
    out.dtau = 0.0;  // collision-time (instantaneous)
    for (nstp=0;nstp<MAXSTP;nstp++) {
        save_history();                 //--- scattering stuff
        if ((x+h*1.0001-x2)*(x2-x1) > 0.0)
            h=x2-x;
        s.step(h, derivs);

        #ifdef MONIT_SCATTERING
        out.check_scattering(x,&y[0],s.hdid,mu_old); //--- scattering stuff
        #endif //MONIT_SCATTERING

        if (s.hdid == h) ++nok; else ++nbad;

        #ifdef MONIT_STEP
        out.monit_step(s);               // monitoreo del step
        #endif //MONIT_STEP

        if (dense){
            out.out(nstp, x, y, s, s.hdid); // guarda solo si x>xout
        }
        else
            out.save(x,y);

        if ((x-x2)*(x2-x1) >= 0.0) {    // aqui termina la simulacion
            for (Int i=0;i<nvar;i++) ystart[i]=y[i];
            if (out.kmax > 0 && abs(out.xsave[out.count-1]-x2) > 100.0*abs(x2)*EPS){
                out.save(x,y);
            }
            out.nsteps = nstp;   // me gusta saber el nro total de pasos
            return;
        }
        if (abs(s.hnext) <= hmin) throw_nr("Step size too small in Odeint");
        h=s.hnext;
    }
    throw_nr("Too many steps in routine Odeint");
}


template<class Stepper>
void Odeint<Stepper>::save_history(){
    Doub xyz[3] = {y[0],y[2],y[4]};
    par.calc_B(xyz);
    Bmod = NORM(par.B[0], par.B[1], par.B[2]); // [1]
    vmod = NORM(y[1], y[3], y[5]); // [1]
    mu_old = (y[1]*par.B[0] + y[3]*par.B[1] + y[5]*par.B[2])/(vmod*Bmod);
}


// declare/define (?) class w/ specific template (BS: Bulirsch-Stoer)
#include "stepperbs.h"
template class Odeint<StepperBS<rhs> >;


#endif //ODEINT_CC
//EOF
