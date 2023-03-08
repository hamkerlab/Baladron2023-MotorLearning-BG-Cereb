#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
Code for the paper: 

Baladron, J., Vitay, J., Fietzek, T. and Hamker, F. H.
The contribution of the basal ganglia and cerebellum to motor learning: a neuro-computational approach.

Copyright the Authors (License MIT)

Training procedure of the basal ganglia module in the adaptation task.
"""

from ANNarchy import *
from basalganglia import *
from kinematic import *




#import yarp
#import CPG_lib.iCub_connect.iCub_connect as robot_connect
import CPG_lib.parameter as params
from CPG_lib.MLMPCPG.MLMPCPG import *
from CPG_lib.MLMPCPG.myPloting import *
from CPG_lib.MLMPCPG.SetTiming import *


import importlib
import sys
import time
import numpy as np
#compile()
#setup(num_threads=2)




#initialize robot connection
sys.path.append('../../CPG_lib/MLMPCPG')
sys.path.append('../../CPG_lib/icubPlot')
iCubMotor = importlib.import_module(params.iCub_joint_names)
global All_Command
global All_Joints_Sensor
global myCont, angles, myT
All_Command = []
All_Joints_Sensor = []
RG_Layer_E = []
RG_Layer_F = []
PF_Layer_E = []
PF_Layer_F = []
MN_Layer_E = []
MN_Layer_F = []
myT = fSetTiming()


#sim =  sys.argv[1]
#print(sim)

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


'''
for ff in range(num_joints):
    VelRG_Pat1[ff].disable_learning()
    VelRG_Pat2[ff].disable_learning()
    VelRG_Pat3[ff].disable_learning()
    VelRG_Pat4[ff].disable_learning()
    VelPF_Pat1[ff].disable_learning()
    VelPF_Pat2[ff].disable_learning()
    VelInjCurr[ff].disable_learning()
#VelInter.disable_learning()

#Hand_velocity.disable()


RG_Pat1.factor_exc = 1.0
RG_Pat2.factor_exc = 1.0
RG_Pat3.factor_exc = 1.0
RG_Pat4.factor_exc = 1.0
PF_Pat1.factor_exc = 1.0
PF_Pat2.factor_exc = 1.0
Inj_Curr.factor_exc = 1.0

num_trials = 0 #1001#1200
'''

angles = np.zeros(params.number_cpg)


angles[iCubMotor.LShoulderPitch] = 40
angles[iCubMotor.LElbow] = -10

initial_position = wrist_position(np.radians(angles[joints]))[0:3]

#VelInter.transmission = False

def gaussian_input(x,mu,sig):
             return np.exp(-np.power(x-mu,2.)/(2*np.power(sig,2)))



def execute_movement(pms,s=0,pf=''):
    myCont = fnewMLMPcpg(params.number_cpg)
    myCont = fSetCPGNet(myCont, params.my_iCub_limits, params.positive_angle_dir)


    an = np.zeros((120,4))

    for j in range(4):
        myCont[joints[j]].fSetPatternRG(RG_Patterns(pms[j,0], pms[j,1], pms[j,2], pms[j,3]))
        myCont[joints[j]].fSetPatternPF(PF_Patterns(pms[j,4], pms[j,5]))

        myCont[joints[j]].RG.F.InjCurrent_value = 1.0 * myCont[joints[j]].RG.F.InjCurrent_MultiplicationFactor
        myCont[joints[j]].RG.E.InjCurrent_value = -1.0 * myCont[joints[j]].RG.E.InjCurrent_MultiplicationFactor

    current_angles = np.copy(angles)
    current_angles = np.radians(current_angles)

    #execute a movement
    for i in AllJointList:
            myCont[i].fUpdateLocomotionNetwork(myT, current_angles[i])
    for idx, controller in enumerate(myCont):
            iCubMotor.MotorCommand[idx] = controller.joint.joint_motor_signal
    #iCub_robot.iCub_set_angles(iCubMotor.MotorCommand)
    All_Command.append(iCubMotor.MotorCommand[:])
    All_Joints_Sensor.append(current_angles)
    I=0
    while I<120:
        I+=1
        for i in AllJointList:
            myCont[i].fUpdateLocomotionNetwork(myT, current_angles[i])
        for idx, controller in enumerate(myCont):
            iCubMotor.MotorCommand[idx] = controller.joint.joint_motor_signal
        #iCub_robot.iCub_set_angles(iCubMotor.MotorCommand)
        All_Command.append(iCubMotor.MotorCommand[:])
        All_Joints_Sensor.append(current_angles)
        if(s==1):
            mc_a = np.array(iCubMotor.MotorCommand[:])
            an[I-1] = mc_a[joints] 

    mc_a = np.array(iCubMotor.MotorCommand[:])
    final_pos = wrist_position(mc_a[joints])[0:3]
    #if(s==1):
    #    np.save(sim+'_'+pf+'_angles.npy',an)
    return final_pos


def random_goal(initial_position):
    nvd = 0
    goal = [0,0,0]
    current_angles = np.copy(angles)
    while(nvd<0.5):#(nvd<0.15): 0.15 or 0.5
        current_angles[iCubMotor.LShoulderPitch] = angles[iCubMotor.LShoulderPitch] + np.random.normal(0,20)
        current_angles[iCubMotor.LShoulderRoll] = angles[iCubMotor.LShoulderRoll] + np.random.normal(0,20)
        current_angles[iCubMotor.LShoulderYaw] = angles[iCubMotor.LShoulderYaw] + np.random.normal(0,20)
        current_angles[iCubMotor.LElbow] = angles[iCubMotor.LElbow] + np.random.normal(0,20)
        current_angles = np.radians(current_angles)
        goal = wrist_position(current_angles[joints])[0:3]
        nvd = np.linalg.norm(goal-initial_position)
    return goal


def rotation_matrix(axis, theta):
    """   
    Return the rotation matrix associated with counterclockwise rotation about
    the given axis by theta radians.
    """
    axis = np.asarray(axis)
    axis = axis / math.sqrt(np.dot(axis, axis))
    a = math.cos(theta / 2.0)
    b, c, d = -axis * math.sin(theta / 2.0)
    aa, bb, cc, dd = a * a, b * b, c * c, d * d
    bc, ad, ac, ab, bd, cd = b * c, a * d, a * c, a * b, b * d, c * d
    return np.array([[aa + bb - cc - dd, 2 * (bc + ad), 2 * (bd - ac)],
                     [2 * (bc - ad), aa + cc - bb - dd, 2 * (cd + ab)],
                     [2 * (bd + ac), 2 * (cd - ab), aa + dd - bb - cc]])




def train_bg(nt):

    num_trials_test = 450



    error_history = np.zeros(num_trials_test+nt+1)

    goals = np.zeros((nt+1,3))
    parameter_history = np.zeros((nt+1,4,6))
    distance_history = np.zeros(nt+1)

    for trial in range(num_trials_test+nt+1):

        print("trial", trial)

        RG_Pat1.noise = 0.0
        RG_Pat2.noise = 0.0
        RG_Pat3.noise = 0.0
        RG_Pat4.noise = 0.0
        PF_Pat1.noise = 0.0
        PF_Pat2.noise = 0.0
        Inj_Curr.noise = 0.0
        RG_Pat1.trace = 0.0
        RG_Pat2.trace = 0.0
        RG_Pat3.trace = 0.0
        RG_Pat4.trace = 0.0
        PF_Pat1.trace = 0.0
        PF_Pat2.trace = 0.0
        Inj_Curr.trace = 0.0
        RG_Pat1.baseline = 0.0
        RG_Pat2.baseline = 0.0
        RG_Pat3.baseline = 0.0
        RG_Pat4.baseline = 0.0
        PF_Pat1.baseline = 0.0
        PF_Pat2.baseline = 0.0
        Inj_Curr.noise = 0.0
        RG_Pat1.r = 0.0
        RG_Pat2.r = 0.0
        RG_Pat3.r = 0.0
        RG_Pat4.r = 0.0
        PF_Pat1.r = 0.0
        PF_Pat2.r = 0.0
        Inj_Curr.r = 0.0
        Intermediate.baseline=0.0
        StrD1_putamen.baseline=0.0
        StrD1_putamen.r= 0.0
        PM.baseline = 0.0
        SNr_putamen.r = 1.1
        StrThal_putamen.r = 0.0
        VA_putamen.r = 0.0


        #inter trial
        simulate(650)

        #test random angles instead of position
        nvd = 0.0
        vel_d = [0,0,0]
        goal = np.zeros(3)


        goal = random_goal(initial_position)

        if(trial==(num_trials_test+nt)):
            perpendicular_vector = np.cross(goals[0],goals[1])
            rot_inv = rotation_matrix( perpendicular_vector  ,np.radians(-45))
            goal = np.dot(rot_inv,goals[0])
           

        vel_d = (goal-initial_position) 

        vel_d = vel_d 
        neuron_update(Cortical_input,goal,10.0,0.5)
        simulate(200)


        ran_prim = np.random.randint(120)
        if(np.max(PM.r)<0.05):
            Intermediate[ran_prim].baseline = 1.0
            PM[ran_prim].baseline = 1.0
            simulate(150)
            #print('random test trial ')
        else:
            ran_prim = np.argmax(PM.r)
            Intermediate[ran_prim].baseline = 1.0
            simulate(150)
            #print(np.argmax(PM.r))



        pms = np.zeros((4,6)) 
        for j in range(4):
            RG1_joint = 5+parameter_readout(RG_Pat1[j,:],0,5)
            RG2_joint = 5+parameter_readout(RG_Pat2[j,:],0,5)
            RG3_joint =  0.001+parameter_readout(RG_Pat3[j,:],-4,4)
            RG4_joint = 5+parameter_readout(RG_Pat4[j,:],0,10)


            PF1_joint = 0.001+parameter_readout(PF_Pat1[j,:],0,2.0)
            PF2_joint = 0.001+parameter_readout(PF_Pat2[j,:],0,2.0)

            
            pms[j] = [RG1_joint,RG2_joint,RG3_joint,RG4_joint,PF1_joint,PF2_joint]


                
        #execute a movement
        final_pos = execute_movement(pms,0,' ')
        vel_final = final_pos-initial_position
        nvf = np.linalg.norm(vel_final)


        if(nvf>0.3):
            reward.baseline = np.clip(2*(0.5 - np.linalg.norm(final_pos-goal)),0,1.0)  
            SNc_put.firing = 1.0
            simulate(100)
            SNc_put.firing = 0.0
            reward.baseline=0.0

        

        Intermediate.baseline = 0

        error_history[trial]  = np.linalg.norm(final_pos-goal)
        

        if(trial>=num_trials_test):
            goals[trial-num_trials_test] = goal
            parameter_history[trial-num_trials_test] = pms
            distance_history[trial-num_trials_test] = np.linalg.norm(final_pos-goal)

    np.save('error_history_bg.npy',error_history)

    
    return goals,parameter_history


def prim_profiles():
    counter=0
    num_actions = 120
    vel_history = np.zeros((num_actions,3))
    parameter_history = np.zeros((num_actions,4,6))
    for a in range(num_actions):
        #print('Testing action '+str(a))
        RG_Pat1.r = 0.0
        RG_Pat2.r = 0.0
        RG_Pat3.r = 0.0
        RG_Pat4.r = 0.0
        PF_Pat1.r = 0.0
        PF_Pat2.r = 0.0
        Inj_Curr.r = 0.0

        Intermediate.r = 0.0
        Intermediate.baseline = 0.0

        simulate(100)


        current_angles = np.copy(angles)  
        current_angles = np.radians(current_angles)
        myCont = fnewMLMPcpg(params.number_cpg)
        myCont = fSetCPGNet(myCont, params.my_iCub_limits, params.positive_angle_dir)

        for i in range(0, len(myCont)):
            myCont[i].fUpdateInitPos(current_angles[i])
        for i in range(0, len(myCont)):
            myCont[i].fUpdateLocomotionNetwork(myT, current_angles[i])
      
        initial_pos = wrist_position(current_angles[joints])[0:3]

        Intermediate[a].baseline = 1.0 #[a]
        simulate(100)

       
        for j in range(4):
            RG1_joint = 5+parameter_readout(RG_Pat1[j,:],0,5)
            RG2_joint = 5+parameter_readout(RG_Pat2[j,:],0,5)
            RG3_joint =  0.001+parameter_readout(RG_Pat3[j,:],-4,4)
            RG4_joint = 5+parameter_readout(RG_Pat4[j,:],0,10)


            PF1_joint = 0.001+parameter_readout(PF_Pat1[j,:],0,2.0)
            PF2_joint = 0.001+parameter_readout(PF_Pat2[j,:],0,2.0)

            
            parameter_history[a] = [RG1_joint,RG2_joint,RG3_joint,RG4_joint,PF1_joint,PF2_joint]

        final_pos = execute_movement(parameter_history[a])

        '''
        #execute a movement
        for i in AllJointList:
                myCont[i].fUpdateLocomotionNetwork(myT, current_angles[i])
        for idx, controller in enumerate(myCont):
                iCubMotor.MotorCommand[idx] = controller.joint.joint_motor_signal
        #iCub_robot.iCub_set_angles(iCubMotor.MotorCommand)
        All_Command.append(iCubMotor.MotorCommand[:])
        All_Joints_Sensor.append(current_angles)
        I=0
        while I<120:
            I+=1
            for i in AllJointList:
                myCont[i].fUpdateLocomotionNetwork(myT, current_angles[i])
            for idx, controller in enumerate(myCont):
                iCubMotor.MotorCommand[idx] = controller.joint.joint_motor_signal
            #iCub_robot.iCub_set_angles(iCubMotor.MotorCommand)
            All_Command.append(iCubMotor.MotorCommand[:])
            All_Joints_Sensor.append(current_angles)

        #compute obtained velocity
        mc_a = np.array(iCubMotor.MotorCommand[:])
        final_pos = wrist_position(mc_a[joints])[0:3]
        '''
 
        vel_a = final_pos-initial_pos

        #print(initial_pos)
        #print(final_pos)

        vel_a = final_pos-initial_pos
        nvel_a = np.linalg.norm(vel_a)
        if(nvel_a<0.3): #1e-3):
            vel_a = [0.0,0.0,0.0]
            counter+=1
        #else:
        #    vel_a = vel_a/nvel_a
        vel_history[a] = final_pos#vel_a
        #print(nvel_a)
    #print(counter)

    #print(vel_history)
    #np.save(sim+'vel_history.npy',vel_history)
    return vel_history, parameter_history

def parameters_per_goal(goal):


    #print('max w '+str(np.max(StrD1SNr_putamen.w)))

    pars = np.zeros((4,6))

    #pop.disable()
    
    #Hand_velocity.baseline = 0.0
    #Hand_velocity.r = 0.0
    RG_Pat1.noise = 0.0
    RG_Pat2.noise = 0.0
    RG_Pat3.noise = 0.0
    RG_Pat4.noise = 0.0
    PF_Pat1.noise = 0.0
    PF_Pat2.noise = 0.0
    Inj_Curr.noise = 0.0
    RG_Pat1.trace = 0.0
    RG_Pat2.trace = 0.0
    RG_Pat3.trace = 0.0
    RG_Pat4.trace = 0.0
    PF_Pat1.trace = 0.0
    PF_Pat2.trace = 0.0
    Inj_Curr.trace = 0.0
    RG_Pat1.baseline = 0.0
    RG_Pat2.baseline = 0.0
    RG_Pat3.baseline = 0.0
    RG_Pat4.baseline = 0.0
    PF_Pat1.baseline = 0.0
    PF_Pat2.baseline = 0.0
    Inj_Curr.noise = 0.0
    RG_Pat1.r = 0.0
    RG_Pat2.r = 0.0
    RG_Pat3.r = 0.0
    RG_Pat4.r = 0.0
    PF_Pat1.r = 0.0
    PF_Pat2.r = 0.0
    Inj_Curr.r = 0.0
    Intermediate.baseline=0.0
    StrD1_putamen.baseline=0.0
    StrD1_putamen.r= 0.0
    PM.baseline = 0.0

    #inter trial
    simulate(650)


    nvd = np.linalg.norm(goal)
    vel_d = goal
    
    
    neuron_update(StrD1_putamen, goal, 1.0, 1.0) #0.2,1 // 0.005,1.0 IN ORIGINAL

    simulate(200)

    primitive = -1

    if(np.max(PM.r)<0.05):
            ran_prim = np.random.randint(120)
            #print('random test trial after bg trainning'+str(np.max(PM.r)))
            primitive = ran_prim
            simulate(150)
    else:
            primitive = np.argmax(PM.r)
            #print(np.argmax(PM.r))
            simulate(150)


    pms = np.zeros((4,6)) 
    for j in range(4):
        RG1_joint = 5+parameter_readout(RG_Pat1[j,:],0,5)
        RG2_joint = 5+parameter_readout(RG_Pat2[j,:],0,5)
        RG3_joint =  0.001+parameter_readout(RG_Pat3[j,:],-4,4)
        RG4_joint = 5+parameter_readout(RG_Pat4[j,:],0,10)


        PF1_joint = 0.001+parameter_readout(PF_Pat1[j,:],0,2.0)
        PF2_joint = 0.001+parameter_readout(PF_Pat2[j,:],0,2.0)

        
        pms[j] = [RG1_joint,RG2_joint,RG3_joint,RG4_joint,PF1_joint,PF2_joint]



    return pms #primitive



