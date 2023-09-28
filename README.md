# TES Geant4

[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)

## Description

This repo is for building a GEANT4 simulation of a Cryostat with a Transition edge sensor (TES) substrate within it. 

## Table of Contents

- [Installation](#installation)
- [Usage](#usage)
- [Features](#features)
- [Contributing](#contributing)
- [Acknowledgments](#acknowledgments)
- [Contact](#contact)

## Installation

### Geant4 on Jubail HPC

Please follow the guide on [our wiki](https://github.com/nyuad-astroparticle/tes-geant/wiki/NYUAD-Jubail-HPC-GEANT4-installation).


## Usage

After you modify any of the code, from your directory create a ``build`` directory if it does not exist:
```terminal
mkdir build
```
Otherwise remove all of the CMake cash from the ``build`` folder:
```terminal
rm -rf CMakeCache.txt cmake_install.cmake CMakeFiles Makefile;
```

Then make. Use -j flag to denote number of cores you want to use in the process. It is not recommened to use all of the cores available.
```terminal
make -j7
```

### Running with mpi

To run on NYUAD Jubail HPC you need to be registered. Please read on the [official website](https://crc-docs.abudhabi.nyu.edu/hpc/hpc.html) how to register an account and submit jobs.

Go to tes-geant/hpc and modify run-start.sh file:
```terminal
cd tes-geant/hpc;
vim run-start.sh
```
<img src="README_files/run-statr.png" alt="run-start" style="width: 40%;">

Then submit the job by typing:
```terminal
sbatch run-start.sh
```
You can see the output of programm by tailing the output file:
```terminal
tail -f start-job....out
```

To exit, simply press ``Ctrl + C``
To see the status of your job you can use ``sacct`` or ``squeue``. To check the HPC use you can type ``cmap``.

### Pre-run checklist:

- [ ] Are you on a correct branch?
- [ ] Have you pulled all the changes?
- [ ] Have you loaded all modules?
- [ ] Have you sourced GEANT4?
- [ ] Have you ccmade your build directory?
- [ ] Have you made your directory?
- [ ] Have you adjusted macros in your directory?
- [ ] Have you modified run_start.sh?
- [ ] Have you run sbatch?
- [ ] Have you tailed the output to verify if it is loading?
- [ ] Have you waited for 2 mins after starting the job to verify that it does not crash in a short time?

## Features

- HPC-enabled multiprocessing for optimized performance on parallel systems.
- Support for various mesh file formats, including gdml.
- Built-in radioactive decay simulation option.
- Toggleable geometry and property settings for flexible customization.
- Integration of low-energy physics.

## Contributing

We welcome contributions to this project! If you find a bug, have a feature request, or want to improve the code, feel free to fork this repository and create your own version.
After you've submitted the pull request, we will review your changes and provide feedback if necessary. Once everything looks good, we'll merge your changes into the main project. 

### Creating Your Own Version

We encourage you to create your own version of this project based on your needs. You are free to modify, extend, or adapt the code in any way you want. There are no restrictions on using this project as a starting point for your own creations.

### Feedback and Support

If you have any questions, feedback, or need assistance, don't hesitate to open an issue on this repository.

Thank you for considering contributing to our project and making it better for everyone.

## Acknowledgments

Tools:
- [CADMesh](https://github.com/christopherpoole/CADMesh)
- [cad-to-geant4-converter](https://github.com/tihonav/cad-to-geant4-converter/tree/master)
- [GEANT4](https://geant4.web.cern.ch/)
- [FreeCad](https://www.freecad.org/)
- [Fusion360](https://www.autodesk.com/products/fusion-360/overview?term=1-YEAR&tab=subscription)
- [MeshLab](https://www.meshlab.net/)
- [CRY](https://nuclear.llnl.gov/simulation/)

Contributors:
- Danish Khan
- Panos Economou
- Tengiz Ibrayev
- Zak Saeed

## Contact

[Panos Economou](https://github.com/PanosEconomou), [Tengiz Ibrayev](https://github.com/F7East)

