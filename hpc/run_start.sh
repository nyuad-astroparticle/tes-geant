#!/bin/bash

# Number of tasks per core
#SBATCH -c 1

# Number of tasks 
#SBATCH -n 10

# Set WALLTIME
#SBATCH --time 02:00:00

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
srun hostname ../build/sim 
