#!/bin/bash
# Number of tasks 
#SBATCH --ntasks 1024 
# Set Memory
#SBATCH --mem 64GB
# Set WALLTIME
#SBATCH --time 05:00:00
# Set output and error files
#SBATCH -o start-job.%J.out
#SBATCH -e start-job.%J.err
# Send email when done
#SBATCH --mail-type=END,FAIL
#SBATCH --mail-user=po524@nyu.edu

#----------------------------------#
#------------EXECUTION-------------#
#----------------------------------#

# Load modules
module purge
source load_modules.sh

# Run the application
cd /scratch/po524/tes-geant/build/
start_time=`date +%s`
mpiexec -n 1024 ./sim ./macros/start.mac
end_time=`date +%s`
echo execution time was `expr $end_time - $start_time` s.
echo "SIM IS DONE!"
# echo "MERGING!"
# ../hpc/merge.sh ./output > ./output/merge.csv
