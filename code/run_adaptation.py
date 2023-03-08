#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
Code for the paper: 

Baladron, J., Vitay, J., Fietzek, T. and Hamker, F. H.
The contribution of the basal ganglia and cerebellum to motor learning: a neuro-computational approach.

Copyright the Authors (License MIT)

Script for the adaptation task.

> python run_adaptation.py
"""

# Parameters
num_goals = 2 # Number of goals. 2 or 8 in the manuscript
num_goals_per_trial = 300 # Number of trials per goal
num_rotation_trials = 200 # Number of rotation trials
num_test_trials = 200 # Number of test trials
strategy = 0 # Set to 1 to simulate a condition which includes an explicit instruction 
rotation = 1 # Set to 1 to simulate a conditioon in which the 45 rotation is included

# Imports
import importlib
import sys
import time
import numpy as np
from numpy import cross, eye, dot
from scipy.linalg import expm, norm

# Import ANNarchy
from ANNarchy import *
setup(num_threads=2)

# Model
from reservoir import *
from kinematic import *
from train_BG_adaptation import *

# CPG
import CPG_lib.parameter as params
from CPG_lib.MLMPCPG.MLMPCPG import *
from CPG_lib.MLMPCPG.myPloting import *
from CPG_lib.MLMPCPG.SetTiming import *

# Compile the network
compile()

# Initialize robot connection
sys.path.append('../../CPG_lib/MLMPCPG')
sys.path.append('../../CPG_lib/icubPlot')
iCubMotor = importlib.import_module(params.iCub_joint_names)
myT = fSetTiming()

# Create list of CPG objects
myCont = fnewMLMPcpg(params.number_cpg)
# Instantiate the CPG list with iCub robot data
myCont = fSetCPGNet(myCont, params.my_iCub_limits, params.positive_angle_dir)

"""
    NeckPitch, NeckRoll, NeckYaw, EyesTilt, EyesVersion, EyesVergence, TorsoYaw, TorsoRoll, TorsoPitch, RShoulderPitch, RShoulderRoll, \
    RShoulderYaw, RElbow, RWristProsup, RWristPitch, RWristYaw, RHandFinger, RThumbOppose, RThumbProximal, RThumbDistal, RIndexProximal, \
    RIndexDistal, RMiddleProximal, RMiddleDistal, RPinky, RHipPitch, RHipRoll, RHipYaw, RKnee, RAnklePitch, RAnkleRoll, \
    LShoulderPitch, LShoulderRoll, LShoulderYaw, LElbow, LWristProsup, LWristPitch, LWristYaw, LHandFinger, LThumbOppose, LThumbProximal, \
    LThumbDistal, LIndexProximal, LIndexDistal, LMiddleProximal, LMiddleDistal, LPinky, LHipPitch, LHipRoll, LHipYaw, LKnee, \
    LAnklePitch, LAnkleRoll
"""

# Initiate PF and RG patterns for the joints
joint1 = iCubMotor.LShoulderRoll
joint2 = iCubMotor.LElbow
joint3 = iCubMotor.LShoulderPitch
joint4 = iCubMotor.LShoulderYaw
joints = [joint4,joint3,joint1,joint2]
AllJointList = joints
num_joints = 4
angles = np.zeros(params.number_cpg)
angles[iCubMotor.LShoulderPitch] = 40
angles[iCubMotor.LElbow] = -10
#angles = np.radians(angles)

# Update CPG initial position (reference position)
for i in range(0, len(myCont)):
    myCont[i].fUpdateInitPos(angles[i])
# Update all joints CPG, it is important to update all joints
# at least one time, otherwise, non used joints will be set to
# the default init position in the CPG which is 0
for i in range(0, len(myCont)):
    myCont[i].fUpdateLocomotionNetwork(myT, angles[i])


for ff in range(num_joints):
    VelRG_Pat1[ff].disable_learning()
    VelRG_Pat2[ff].disable_learning()
    VelRG_Pat3[ff].disable_learning()
    VelRG_Pat4[ff].disable_learning()
    VelPF_Pat1[ff].disable_learning()
    VelPF_Pat2[ff].disable_learning()
    VelInjCurr[ff].disable_learning()

RG_Pat1.factor_exc = 1.0
RG_Pat2.factor_exc = 1.0
RG_Pat3.factor_exc = 1.0
RG_Pat4.factor_exc = 1.0
PF_Pat1.factor_exc = 1.0
PF_Pat2.factor_exc = 1.0
Inj_Curr.factor_exc = 1.0


def gaussian_input(x,mu,sig):
    return np.exp(-np.power(x-mu,2.)/(2*np.power(sig,2)))



hc_goals = [ [0.3286242/2.,  0.33601961/2., 0.55/2.], [-0.8713758/2.,   0.3360196/2.,  0.55/2.]]

max_angle = 0
num_tests = 0
a = [0,0,0]

pop.enable()

num_trials = num_goals * num_goals_per_trial

error_history = np.zeros(num_trials+num_rotation_trials+num_test_trials)
angle_history3 = np.zeros(num_trials+num_rotation_trials+num_test_trials)
#error_historyP = np.zeros(num_trials+10)

dh = np.zeros(num_trials)

###################
# BG controller
###################
print('Training BG')
goal_history, parameter_history = train_bg(num_goals)


###################
# Reservoir
###################
print('Training reservoir')

def M(axis, theta):
    return expm(cross(eye(3), axis/norm(axis)*theta))


def unit_vector(vector):
    """ Returns the unit vector of the vector.  """
    return vector / np.linalg.norm(vector)

def angle_between(v1, v2):
    v1_u = unit_vector(v1)
    v2_u = unit_vector(v2)
    return np.arccos(np.clip(np.dot(v1_u, v2_u), -1.0, 1.0))

def normalize(x):
    return x/ np.linalg.norm(x)

def project_onto_plane(x, n):
    d = np.dot(x, n) / np.linalg.norm(n)
    p = d * normalize(n)
    return x-p

StrD1SNc_put.disable_learning()

perpendicular_vector = np.cross(goal_history[0],goal_history[1])
perpendicular_normalized = perpendicular_vector/np.linalg.norm(perpendicular_vector)
rot = rotation_matrix( perpendicular_vector  ,np.radians(45))

def angle_in_plane(v1,v2,n):
    dot = np.dot(v1,v2)
    det = v1[0]*v2[1]*n[2] + v2[0]*n[1]*v1[2] + n[0]*v1[1]*v2[2]  - v1[2]*v2[1]*n[0] - v2[2]*n[1]*v1[0] - n[2]*v1[1]*v2[0]
    return np.arctan2(det,dot)

cerror = np.zeros(num_trials+num_rotation_trials+num_test_trials)

# Compute the mean reward per trial
R_mean = np.zeros(num_goals)
alpha = 0.33 #0.75 0.33 

for t in range(num_trials+num_rotation_trials+num_test_trials):

    # Select goal
    goal_id = t % num_goals
    if(t>num_trials):
        goal_id = 0
    current_goal =  goal_history[goal_id]   
    
    # Reinitialize reservoir
    pop.x = Uniform(-0.01, 0.01).get_values(N)
    pop.r = np.tanh(pop.x)
    pop[1].r = np.tanh(1.0)
    pop[10].r = np.tanh(1.0)
    pop[11].r = np.tanh(-1.0)


    # Set input
    inp[goal_id].r = 1.0
    simulate(200)

    # ISI
    inp.r  = 0.0
    simulate(200)

    rec = m.get()
    output = rec['r'][-200:,-24:]
    output = np.mean(output,axis=0) * 2.0

    current_params =  np.copy(parameter_history[goal_id])

    # Turn this on for simulations with strategy
    if(strategy==1):
        if(t>(num_trials+2) and t<(num_trials+num_rotation_trials-10) ):
            current_params = np.copy(parameter_history[2])

    if(t>-1):
        current_params+=output.reshape((4,6))        
    
    s = 0
    pf = ''
    if(t>(num_trials-3)):
        s = 1
        pf = str(t)
    final_pos = execute_movement(current_params,s,pf)

    #Turn this on for simulations with perturbation
    if(rotation==1):
        if(t>num_trials and t<(num_trials+num_rotation_trials) ):
            final_pos = np.dot(rot,final_pos) 


    distance = np.linalg.norm(final_pos-current_goal)

    # Activate this for simulations with strategy
    if(strategy==1):
        if(t>(num_trials) and t<(num_trials+num_rotation_trials)):
            distance = np.linalg.norm(final_pos-goal_history[2]) 
    error = distance 

    # Plasticity
    if(t>10):
        # Apply the learning rule
        Wrec.learning_phase = 1.0
        Wrec.error = error
        Wrec.mean_error = R_mean[goal_id]

        # Learn for one step
        step()

        # Reset the traces
        Wrec.learning_phase = 0.0
        Wrec.trace = 0.0
        _ = m.get()

    # Update mean error
    R_mean[goal_id] = alpha * R_mean[goal_id] + (1.- alpha) * error
    error_history[t] = error

    rotated_proj = project_onto_plane(final_pos,perpendicular_vector)
    angle_history3[t] = np.degrees( angle_in_plane(rotated_proj,current_goal,perpendicular_normalized) )
    cerror[t] = error

np.save('angle3.npy', angle_history3) # Directional error
np.save('cerror.npy', cerror) # Aiming error


