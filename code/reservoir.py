#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
Code for the paper: 

Baladron, J., Vitay, J., Fietzek, T. and Hamker, F. H.
The contribution of the basal ganglia and cerebellum to motor learning: a neuro-computational approach.

Copyright the Authors (License MIT)

Definition of the  reservoir / cerebellum module.
"""

from ANNarchy import *


RC_neuron = Neuron(
    parameters = """
        tau = 30.0 : population # Time constant
        constant = 0.0 # The four first neurons have constant rates
        alpha = 0.05 : population # To compute the sliding mean 0.05
        f = 9.0 : population # Frequency of the perturbation 3/9
        A = 20. : population # Perturbation amplitude. dt*A/tau should be 0.5... original=16/20
    """,
    equations="""
        # Perturbation
        perturbation = if Uniform(0.0, 1.0) < f/1000.: 1.0 else: 0.0 
        noise = if perturbation > 0.5: A*Uniform(-1.0, 1.0) else: 0.0

        # ODE for x
        x += dt*(sum(in) + sum(exc) - x + noise)/tau

        # Output r
        rprev = r
        r = if constant == 0.0: tanh(x) else: tanh(constant)

        # Sliding mean
        delta_x = x - x_mean
        x_mean = alpha * x_mean + (1 - alpha) * x
    """
)

#changed weight change to positive
#eta * trace * (mean_error) * (error - mean_error)
TraceMiconi = Synapse(
    parameters="""
        eta = 0.8: projection # Learning rate 0.5 -- 0.6 in icubs_bg/2
        learning_phase = 0.0 : projection # Flag to allow learning only at the end of a trial
        error = 0.0 : projection # Reward received
        mean_error = 0.0 : projection # Mean Reward received
        max_weight_change = 0.0005 : projection # Clip the weight changes 0.0003/0.0005
    """,
    equations="""
        # Trace
        trace += if learning_phase < 0.5:
                    power(pre.rprev * (post.delta_x), 3)
                 else:
                    0.0

        # Weight update only at the end of the trial
        delta_w = if learning_phase > 0.5:
                eta * trace * (mean_error) * (error - mean_error)
             else:
                 0.0 : min=-max_weight_change, max=max_weight_change
        w -= if learning_phase > 0.5:
                delta_w
             else:
                 0.0
    """
)

inp = Population(9, Neuron(parameters="r=0.0"))
inp.r = 0.0

# Recurrent population
N = 400
pop = Population(N, RC_neuron)
pop[1].constant = 1.0
pop[10].constant = 1.0
pop[11].constant = -1.0
pop.x = Uniform(-0.1, 0.1)

# Input weights
Wi = Projection(inp, pop, 'in')
Wi.connect_all_to_all(weights=Uniform(-0.2, 0.2))


# Recurrent weights
g = 1.0 
Wrec = Projection(pop, pop,'exc', TraceMiconi)  
Wrec.connect_all_to_all(weights=Normal(0., g/np.sqrt(N)), allow_self_connections=True)


m = Monitor(pop,['r'])

