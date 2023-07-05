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
srun -n 10 ../build/sim ../build/macros/start.mac 
