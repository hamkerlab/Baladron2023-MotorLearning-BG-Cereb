# The contribution of the basal ganglia and cerebellum to motor learning: a neuro-computational approach

Code for the paper: 

Baladron, J., Vitay, J., Fietzek, T. and Hamker, F. H. \
**The contribution of the basal ganglia and cerebellum to motor learning: a neuro-computational approach**\
*submitted.*

## Dependencies

The code depends on the neuro-simulator ANNarchy (Artificial Neural Networks architect) version 4.7.2. Installation instructions for Linux and MacOS are available in the official ANNarchy documentation:

<https://annarchy.github.io/>

ANNarchy has the following minimal requirements:

+ python >= 3.8 (with the development files, e.g. python-dev or python-devel)
+ g++ >= 6.1 (7.4 recommended)
+ make >= 3.0
+ setuptools >= 40.0
+ numpy >= 1.13
+ cython >= 0.20
+ sympy >= 1.6
+ scipy >= 0.19
+ matplotlib >= 2.0

ANNarchy can then be installed with:

```bash
pip install ANNarchy
```

## Simulations

The code in the folder `code/` contains the model definitions and implements the reaching and adaptation tasks. 

The number of goals in the reaching task (2 and 8 in the manuscript) can be changed at the beginning of `run_reaching.py`.  

```python
python run_reaching.py
```

The three conditions of the adaptation task can be simulated by making the appropriate changes at the beginning of `run_adaptation.py`. 


```python
python run_adaptation.py
```

The scripts will initialize the random concrete action, optionally run the initial basal ganglia training and then run the full model simulation with 2 or 8 goals. A full simulation will take **several hours**.

The code has been tested on Linux Ubuntu 22.4 Mint 20.2, using python 3.9 and 3.8 and ANNarchy version 4.7. We cannot assure that it will work on other versions.

The reaching code will output two files:

* `error_history_bg.npy` which is a numpy array with the error on each trial of the initial basal ganglia training procedure.
* `error.npy`  which is a numpy array with the error during the training with 2 or 8 goals of the full model.

The adaptation code will save the directional error in `angle3.npy` and the aiming error in `cerror.npy`.


