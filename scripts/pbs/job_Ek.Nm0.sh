#!/bin/bash 
#PBS -l nodes=1:ppn=24
#PBS -M jimmy.ilws@gmail.com
#PBS -m abe 
#PBS -N 1e7eV.Nm0
#PBS -j oe
#PBS -k oe

THIS_DIR=/home/jimmy.meza/code/pure/scripts
EXEC=/home/jimmy.meza/code/pure/main_mpi.x
cd $THIS_DIR
INPUTS="../inputs/INPUT_TURB.Nm0.inp ../inputs/orientations_isotropic.inp ../inputs/INPUT_GRAL_Ek.1e7.inp"
NAMES_NODES="-machinefile ./names.list_Nm0"
DIR_OUTPUT="../output/output_Ek.1e7eV/Nm0"
MON1=$THIS_DIR/mon1_1e7eV_Nm0_ii.log
MON2=$THIS_DIR/mon2_1e7eV_Nm0_ii.log
NPROCS="-np 24"

mpirun $NPROCS $NAMES_NODES $EXEC $INPUTS $DIR_OUTPUT 1> $MON1 2> $MON2
