# The contribution of the basal ganglia and cerebellum to motor learning: a neuro-computational approach

Code for the paper: 

Baladron, J., Vitay, J., Fietzek, T. and Hamker, F. H. \
**The contribution of the basal ganglia and cerebellum to motor learning: a neuro-computational approach**\
*submitted.*

The code in the folder `Reaching/` contains the model definitions and implements the reaching task. The number of goals (2 and 8 used in the manuscript) can be changed as a parameter in `iCub_jiggling_reservoir.py`.  

The code in the folder `Adaptation/` are the version of the files required for simulating the adaptation task. The three conditions of the task can be simulated by making the appropriate changes in `iCub_jiggling_reservoir.py`. The same model definitions as in `Reaching/` are required.

To run a simulation: python3 iCub_jiggling_reservoir.py
This will initialize the random concrete action, run the initial basal ganglia training and then run the full model simulation with 2 or 8 goals. A full simulation will take several hours.

The basic requirement is having installed ANNarchy (https://annarchy.readthedocs.io/en/latest/). Installation instrucions for Linux and Mac are available in the oficial ANNarchy documentation.

ANNarchy requirements are the following:
:
  + g++ >= 4.8
  + make >= 3.0
  + python >= 3.6 (with the development files, e.g. python-dev or python-devel)
  + cython >= 0.20
  + setuptools >= 40.0
  + numpy >= 1.13
  + sympy >= 1.6
  + scipy >= 0.19
  +matplotlib >= 2.0
 

The code has only been tested on linux Ubuntu 22.4 Mint 20.2, using python 3.9 and 3.8 and ANNarchy version 4.6 or 4.7. We can not assure it will work on other versions.

The code will output two files:
error_history_bg.npy which is a numpy array with the error on each trial of the initial basal ganglia training procedure
error.npy  which is a numpy array with the error during the training with 2 or 8 goals of the full model

In order to run a simulation of the motor adaptation task it is necesary to take the code in the Reaching folder and change the corresponding files. In this case directional error will be saved in a file called angle3.npy and aiming error on cerror.npy


