#!/bin/bash
# Number of tasks 
#SBATCH --ntasks 128
# Set WALLTIME
#SBATCH --time 00:30:00
# Set output and error files
#SBATCH -o start-job.%J.out
#SBATCH -e start-job.%J.err


#----------------------------------#
#------------EXECUTION-------------#
#----------------------------------#

# Load modules
module purge
source load_modules.sh

# Run the application
cd /scratch/po524/tes-geant/build/
mpiexec -n 128 ./sim ./macros/start.mac
echo "SIM IS DONE!"
echo "MERGING!"
../hpc/merge.sh ./output > ./output/merge.csv
