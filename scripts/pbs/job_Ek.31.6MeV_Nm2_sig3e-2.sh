#!/bin/bash 
#PBS -l nodes=1:ppn=24
#PBS -M jimmy.ilws@gmail.com
#PBS -m abe 
#PBS -N sig.3e-2
#PBS -j oe
#PBS -k oe

THIS_DIR=/home/jimmy.meza/code/pure/scripts
EXEC=/home/jimmy.meza/code/pure/main_mpi.x
cd $THIS_DIR
INPUTS="../inputs/INPUT.TURB_sig.3e-2.inp ../inputs/orientations_isotropic.inp ../inputs/INPUT.GRAL_Ek.31.6MeV.inp"
NAMES_NODES="-machinefile ./names.list_sig.3e-2"
DIR_OUTPUT="../output/output_Ek.31.6MeV/sig0"
MON1=$THIS_DIR/mon1_1e6eV_sig.3e-2.log
MON2=$THIS_DIR/mon2_1e6eV_sig.3e-2.log
NPROCS="-np 24"

mpirun $NPROCS $NAMES_NODES $EXEC $INPUTS $DIR_OUTPUT 1> $MON1 2> $MON2
