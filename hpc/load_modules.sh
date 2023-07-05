#!/bin/bash
# A little script to load the required modules for compiling this beautiful simulation

# HPC Modules -----------------------------------------------
module load gcc cmake mpich expat

# Geant4 ----------------------------------------------------
source /scratch/po524/geant4/geant4-v11.1.1-mpi-install/bin/geant4.sh
export G4MPI_DIR="/scratch/po524/geant4/g4mpi/lib64/G4mpi-11.1.1/"

# Now you should be all set to compile with the ENABLE_MPI flag on ccmake.
