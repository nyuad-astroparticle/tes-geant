#!/bin/bash
# A little script to load the required modules for compiling this beautiful simulation

# HPC Modules -----------------------------------------------
module load cmake
module load gcc
module load mpich
module load expat

# Geant4 ----------------------------------------------------
source /scratch/ti602/geant4/install/bin/geant4.sh
export G4MPI_DIR="/scratch/ti602/geant4/g4mpi/lib64/G4mpi-11.1.2"

# Now you should be all set to compile with the ENABLE_MPI flag on ccmake.
