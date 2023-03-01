	
from ANNarchy import *
#from motor_jiggling_intermediate import *
#from bg_loop3 import *
from reservoir_bg3 import *
from kinematic import *
from iCub_jiggling_bg3 import *

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

sim = sys.argv[1]
print(sim)

compile()
setup(num_threads=2)
#setup(dt=0.66)

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
#VelInter.disable_learning()




RG_Pat1.factor_exc = 1.0
RG_Pat2.factor_exc = 1.0
RG_Pat3.factor_exc = 1.0
RG_Pat4.factor_exc = 1.0
PF_Pat1.factor_exc = 1.0
PF_Pat2.factor_exc = 1.0
Inj_Curr.factor_exc = 1.0



def gaussian_input(x,mu,sig):
             return np.exp(-np.power(x-mu,2.)/(2*np.power(sig,2)))


num_trials_test = 100

distance_history = np.zeros(num_trials_test)
goal_history= np.zeros((num_trials_test,3))
parameter_history = np.zeros((num_trials_test,4,6))
final_pos_history = np.zeros((num_trials_test,3))







max_angle = 0
num_tests = 0
a = [0,0,0]





pop.enable()


#HERE YOU CAN SET THE NUMBER OF GOALS, 2 AND 8 ARE USED IN THE MANUSCRIPT
num_goals = 2

num_trials = num_goals*300 #600

error_history = np.zeros(num_trials)



dh = np.zeros(num_trials)


simulation_type = 0 #SET TO 0 TO USE THE BG AND 1 TO USE THE RESERVOIR ALONE


#BG CONTROLLER, COMMENT/REMOVE TO RUN WITH THE RESERVOIR ALONE
#THIS TAKE A LONG COMPUTATIONAL TIME AS THE PRE-TRAINING OF THE BG IS PERFORMED HERE
#THE PRE TRAINNG IS UNNECESSARY IF THE RESERVOIR ALONE IS USED
print('Tranning BG')
goal_history, parameter_history = preproc(num_goals)



ph = np.zeros((num_trials,4,6))

print('Training reservoir')
for t in range(num_trials):
    current_goal =  goal_history[t%num_goals]
    current_parms =   np.copy(parameters_per_goal(current_goal))


    ph[t] = current_parms


    pop.x = Uniform(-0.01, 0.01).get_values(N)
    pop.r = np.tanh(pop.x)
    pop[1].r = np.tanh(1.0)
    pop[10].r = np.tanh(1.0)
    pop[11].r = np.tanh(-1.0)

    inp[(t%num_goals)].r = 1.0
    
    simulate(200)

    inp.r = 0.0

    simulate(200)

    rec = m.get()
    
    output = rec['r'][-200:,-24:]
    output = np.mean(output,axis=0)


    if(simulation_type==0):
        output=output*2

    if(t>-1):
        current_parms+=output.reshape((4,6))
    
    
    
    #current_parms[:,6] = parameter_history[a[t%2],:,6] #TEST!!!
    if(simulation_type == 1):

        current_parms[:,0] = np.clip( (1+current_parms[:,0])*(5.0/2.0),0.001,5)  
        current_parms[:,1] = np.clip( (1+current_parms[:,1])*(5.0/2.0),0.001,5) 
        current_parms[:,2] = np.clip(current_parms[:,2]*4,-4,4)  
        current_parms[:,3] = np.clip( (1+current_parms[:,3])*(10.0/2.0),0.001,10)  
        current_parms[:,4] = np.clip( (1+current_parms[:,4]),0.01,2.0)  
        current_parms[:,5] = np.clip( (1+current_parms[:,5]),0.01,2.0)
 

    
    can = np.copy(angles)
    final_pos = execute_movement(current_parms,can)
    distance = np.linalg.norm(final_pos-current_goal)

    error = 0
    initial_distance = np.linalg.norm(initial_position-current_goal)    
    if(t>-1):
        error = distance 

    dh[t] = distance


    if(t>10):
        # Apply the learning rule
        Wrec.learning_phase = 1.0
        Wrec.error = error
        Wrec.mean_error = R_mean[t%num_goals]
        # Learn for one step
        step()
        # Reset the traces
        Wrec.learning_phase = 0.0
        Wrec.trace = 0.0
        _ = m.get()

    
    R_mean[t%num_goals] = alpha * R_mean[t%num_goals] + (1.- alpha) * error
    

    error_history[t] = error





np.save(sim+'error.npy',error_history)
np.save(sim+'dh.npy',dh)
#Wi.save_connectivity(filename='Wi.data')
#Wrec.save_connectivity(filename='Wrec.data')

np.save('pm.npy',mpm.get('r'))
