# TES Geant4

[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)

## Description

A brief description of your project goes here. Explain what your project does, why it's useful, and any key features.

## Table of Contents

- [Installation](#installation)
- [Usage](#usage)
- [Features](#features)
- [Contributing](#contributing)
- [License](#license)
- [Acknowledgments](#acknowledgments)

## Installation

### Geant4 on Jubail HPC

This guide explains how to install Geant4 on NYUAD Jubail high-performance computing (HPC) cluster.

#### Connecting to HPC

```terminal
ssh your_id@jubail.abudhabi.nyu.edu;
cd scratch/your_id;
```

#### Downloading GEANT4

```terminal
wget https://gitlab.cern.ch/geant4/geant4/-/archive/v11.1.2/geant4-v11.1.2.tar.gz ;
tar -xzf geant4-v11.1.2.tar.gz;
```

#### Installing GEANT4

```terminal
module load gcc cmake mpich expat;
mkdir geant4;
cd geant4;
mkdir build;
mkdir install;
mv ../geant4-v11.1.2 ./geant4-v11.1.2;
cd build;
ccmake ../geant4-v11.1.2;
```

Your screen should look something like this before you configure:
<!-- ![Alt text](<Pasted Graphic.png>){:height="10px" width="10px"} -->
<img src="README_files/BeforeConfigure.png" alt="Before Configure" style="width: 40%;">

You should press ``c`` to configure. If it prompts you to exit press ``e``. Then configure untill you see ``generate`` option at the bottom of the screen. Generate by pressing ``g``. 

After this you can ``make`` using a separate screen, because the installation may take a while, especially on login nodes.

```terminal
screen
```

Regardles of using screen or not you proceed with:

```terminal
make -j20;
make install;
```

You can detach the screen after you started ``make`` by first pressing ``Ctrl A `` and then ``Ctrl D``. To check the installation you just go back to screen by ``screen`` again.

After your installation is done you need to source GEANT4 by:

```terminal
source /scratch/tyour_id/geant4/install/bin/geant4.sh
```

#### Installing GEANT4 MPI (Message Passing Interaface)

Iff you have followed the guide you should do the following in order to insall MPI for GEANT4 to use multiprocessing on the HPC
```terminal
cd /scratch/your_ID/geant4;
mkdir g4mpi;
cd /scratch/your_ID/geant4/install/share/Geant4/examples/extended/parallel/MPI/source;
mkdir build;
cd build;
ccmake ..
```

![MPI ccmake](README_files/MPI.png)

In your ``ccmake`` change your ``CMAKE_INSTALL_PREFIX`` to:

```terminal
/scratch/your_ID/geant4/g4mpi
```

After this set your MPI variable:
```terminal
echo "export G4MPI_DIR=/scratch/your_ID/geant4/g4mpi/lib64/G4mpi-11.1.2" >> /home/your_ID/.bashrc;
source /home/your_ID/.bashrc;
```

Then:
```terminal
make;
make install
```

### tes-geant
```terminal
git clone git@github.com:nyuad-astroparticle/tes-geant.git
```
You will need a working ssh key on git generated on the HPC. For that please follow the official [GitHub guide](https://docs.github.com/en/authentication/connecting-to-github-with-ssh/generating-a-new-ssh-key-and-adding-it-to-the-ssh-agent).

After that you need to cry by doing the following:
```terminal
cd tes-geant;
tar -xzf cry_v1.7.tar.gzcry_v1.7.tar.gz
```


## Usage

Explain how to use your project. Include examples or code snippets to demonstrate its functionality. You can also add screenshots or gifs to visually illustrate usage.

## Features

List the main features of your project. This helps users quickly understand what your project can do.

## Contributing

If you welcome contributions to your project, outline the guidelines for contributing. Include information on how to submit bug reports, feature requests, and pull requests.

## License

Specify the license under which your project is distributed. If you're not sure which license to use, the MIT License is a popular choice for open-source projects. Include a link to the full license file.

## Acknowledgments

If your project builds upon the work of others, acknowledges any third-party libraries or tools that you've used. You can also mention contributors or people who have inspired your project.

## Contact

Provide a way for users to get in touch with you or your team if they have questions, concerns, or feedback about the project.

