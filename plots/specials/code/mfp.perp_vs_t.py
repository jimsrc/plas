from pylab import *
from numpy import *

# omega ciclotron para proton:
# Ek: [eV] energ cinetica
# Bo: [G] campo guia
def calc_omega(Bo, Ek):
        q = 0.00000000048032
        mo = 1.6726e-24
        c = 3e10
        Ereposo = 938272013.0

        rigidity = sqrt(Ek*Ek + 2.*Ek*Ereposo);
        gamma = pow(pow(rigidity/Ereposo,2) + 1. , 0.5)
        beta = pow(1. - 1/(gamma*gamma) , 0.5);
        OMEGA   = q * Bo / (gamma * mo * c)             # [s^-1]
        return OMEGA

# param relativistas de un proton
def calc_beta_gamma(Ek):
        Ereposo = 938272013.0          # [eV]
        rigidity = sqrt(Ek*Ek + 2.*Ek*Ereposo)
        gamma = pow(pow(rigidity/Ereposo,2) + 1. , 0.5)
        beta = pow(1. - 1/(gamma*gamma) , 0.5)
        return (beta, gamma)

# inputs:
# k     : [cm^2/s] difussion coef
# Ek    : [eV] kinetic energy of proton
def calc_mfp(kdiff, Ek):
        c = 3e10                        # [cm/s]
        beta, g = calc_beta_gamma(Ek)   # parametros relativ del proton
        mfp = 3.*kdiff / (beta*c)       # [cm]
        return mfp 

def larmor(Bo, Ek):
        c  = 3e10                       # [cm/s]
        beta, g = calc_beta_gamma(Ek) 
        v = beta*c                      # [cm/s]
        wc = calc_omega(Bo, Ek)         # [s-1]
        rl = v/wc                       # [cm]
        return rl

AUincm	= 1.5e13	# [cm]
Bo	= 5e-5
Ek	= 1e8
fname	= '../../../post/k_vs_t_Ek.%1.1eeV_Nm128_slab0.20_sig.1.0e+00_Lc2d.1.0e-02_LcSlab.1.0e-02.dat' % Ek
data 	= loadtxt(fname, unpack=True)
t	= data[0]
kxx	= data[1]
kyy	= data[2]
kzz	= data[3]
kperp	= 0.5*(kxx + kyy)
mfp_perp = calc_mfp(kperp, Ek)/AUincm	# [AU]

fig	= figure(1, figsize=(6, 4))
ax	= fig.add_subplot(111)

ax.plot(t/1e4, mfp_perp*1e3, '-o', alpha=0.6)
ax.grid()
ax.set_xlabel('time [$\Omega^{-1}$]  ($\\times 10^4$)', fontsize=16)
ax.set_ylabel('$\lambda_\perp (t)$ [AU]  ($\\times 10^{-3}$)', fontsize=16)

fname_fig = '../mfp.perp_Ek.%1.1e.png' % Ek
savefig(fname_fig, dpi=100, format='png', bbox_inches='tight')
close()
