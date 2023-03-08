#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
Code for the paper: 

Baladron, J., Vitay, J., Fietzek, T. and Hamker, F. H.
The contribution of the basal ganglia and cerebellum to motor learning: a neuro-computational approach.

Copyright the Authors (License MIT)

Definition of the CPG module.
"""

import os.path
from scipy.stats import multivariate_normal

from ANNarchy import *

LinearNeuron = Neuron(
    parameters= """
        tau = 10.0
        baseline = 0.0
        noise = 0.0
        tau_trace = 250
        factor_exc = 1.0
    """,
    equations="""
        tau*dmp/dt + mp = factor_exc*sum(exc) - sum(inh) + baseline + noise*Uniform(-1.0,1.0)
        tau_trace*dtrace/dt + trace = r 
        r = pos(mp)
    """
)

LinearNeuron_saturated = Neuron(
    parameters= """
        tau = 10.0
        baseline = 0.0
        noise = 0.0
        tau_trace = 250
        factor_exc = 1.0
    """,
    equations="""
        tau*dmp/dt + mp = factor_exc*sum(exc) - sum(inh) + baseline + noise*Uniform(-1.0,1.0)
        tau_trace*dtrace/dt + trace = r 
        r = pos(mp) : max=1.0
    """
)

PositiveCovariance = Synapse(
    parameters="""
        tau = 500.0 
        tau_alpha = 10.0 
        regularization_threshold = 100.2
        threshold_post = 0.0
        threshold_pre = 0.3
    """,
    equations="""
        tau_alpha*dalpha/dt + alpha = pos(post.r - regularization_threshold)
        trace = pos(pre.r - mean(pre.r) - threshold_pre) * (post.r  - mean(post.r) - threshold_post)
        delta = trace 
        tau*dw / dt = delta : min=0
    """
)

PostCovariance = Synapse(
    parameters="""
        tau = 100.0
        tau_alpha = 10.0 
        regularization_threshold = 1.5
        threshold_post = 0.0
        threshold_pre = 0.0
    """,
    equations="""
        tau_alpha*dalpha/dt + alpha = pos(post.r - regularization_threshold)
        trace = (pre.r - mean(pre.r) - threshold_pre) * pos(post.r  - mean(post.r)-threshold_post)
        delta = trace - alpha*pos(post.r-mean(post.r) - threshold_post)*pos(post.r-mean(post.r) - threshold_post)*w
        tau*dw / dt = delta : min=0
    """
)


prename = 'lalalalala' #'40prim2'

weight_local_inh = 1.0 #1.0

num_cell_per_parm = 20
num_cell_per_ax = 20
num_joints = 4

RG_Pat1 =  Population(name='RG_Pattern_parm1',geometry=(num_joints,num_cell_per_parm),neuron=LinearNeuron)
RG_Pat2 =  Population(name='RG_Pattern_parm2',geometry=(num_joints,num_cell_per_parm),neuron=LinearNeuron)
RG_Pat3 =  Population(name='RG_Pattern_parm3',geometry=(num_joints,num_cell_per_parm),neuron=LinearNeuron)
RG_Pat4 =  Population(name='RG_Pattern_parm4',geometry=(num_joints,num_cell_per_parm),neuron=LinearNeuron)
PF_Pat1 =  Population(name='PF_Pattern_parm1',geometry=(num_joints,num_cell_per_parm),neuron=LinearNeuron)
PF_Pat2 =  Population(name='PF_Pattern_parm2',geometry=(num_joints,num_cell_per_parm),neuron=LinearNeuron)
Inj_Curr = Population(name='Injected_current',geometry=(num_joints,num_cell_per_parm),neuron=LinearNeuron)





#Motor primitives encoding cells
Intermediate = Population(name='Intermediate',geometry=120,neuron=LinearNeuron)#_saturated)
Intermediate.tau=10
Intermediate.noise=0.0   #IN ORIGINAL


weight_matrix = np.zeros((num_joints*num_cell_per_parm,num_joints*num_cell_per_parm))

for jj in range(num_joints):
    weight_matrix[jj*num_cell_per_parm:(jj+1)*num_cell_per_parm,jj*num_cell_per_parm:(jj+1)*num_cell_per_parm] = weight_local_inh
np.fill_diagonal(weight_matrix,0)


#Local inhibitory connections - implement competition.
RGPat1RGPat1 = Projection(pre=RG_Pat1,post=RG_Pat1,target='inh')
RGPat1RGPat1.connect_from_matrix(weight_matrix)

RGPat2RGPat2 = Projection(pre=RG_Pat2,post=RG_Pat2,target='inh')
RGPat2RGPat2.connect_from_matrix(weight_matrix)

RGPat3RGPat3 = Projection(pre=RG_Pat3,post=RG_Pat3,target='inh')
RGPat3RGPat3.connect_from_matrix(weight_matrix)

RGPat4RGPat4 = Projection(pre=RG_Pat4,post=RG_Pat4,target='inh')
RGPat4RGPat4.connect_from_matrix(weight_matrix)

PFPat1PFPat1 = Projection(pre=PF_Pat1,post=PF_Pat1,target='inh')
PFPat1PFPat1.connect_from_matrix(weight_matrix)

PFPat2PFPat2 = Projection(pre=PF_Pat2,post=PF_Pat2,target='inh')
PFPat2PFPat2.connect_from_matrix(weight_matrix)

InjCurrInjCurr = Projection(pre=Inj_Curr,post=Inj_Curr,target='inh')
InjCurrInjCurr.connect_from_matrix(weight_matrix)

InterInter = Projection(pre=Intermediate,post=Intermediate,target='inh')
InterInter.connect_all_to_all(weights=1.0,allow_self_connections=False)#IN ORIGINAL



VelRG_Pat1= []
for i in range(num_joints):
    temp =  Projection(pre=Intermediate,post=RG_Pat1[i,:],target='exc') #,synapse=PositiveCovariance)
    if(os.path.isfile(prename+'weights_RG_Pat1_'+str(i)+'.data')):
        print('loading weights from file')
        temp.connect_from_file(filename=prename+'weights_RG_Pat1_'+str(i)+'.data')
    else:
        print('Resetting the connectivity...')
        temp.connect_all_to_all(weights=Uniform(0.1,0.5)) #weights=0.0)
    VelRG_Pat1.append(temp)


VelRG_Pat2 = []
for i in range(num_joints):
    temp = Projection(pre=Intermediate,post=RG_Pat2[i,:],target='exc') #,synapse=PositiveCovariance)
    if(os.path.isfile(prename+'weights_RG_Pat2_'+str(i)+'.data')):
        temp.connect_from_file(filename=prename+'weights_RG_Pat2_'+str(i)+'.data')
    else:
        temp.connect_all_to_all(weights=Uniform(0.1,0.5))#weights=0.0)
    VelRG_Pat2.append(temp)

VelRG_Pat3 = []
for i in range(num_joints): 
    temp = Projection(pre=Intermediate,post=RG_Pat3[i,:],target='exc') #,synapse=PositiveCovariance)
    if(os.path.isfile(prename+'weights_RG_Pat3_'+str(i)+'.data')):
        temp.connect_from_file(filename=prename+'weights_RG_Pat3_'+str(i)+'.data')
    else:
        temp.connect_all_to_all(weights=Uniform(0.1,0.5)) #weights=0.0)
    VelRG_Pat3.append(temp)

VelRG_Pat4 = [] 
for i in range(num_joints):
    temp = Projection(pre=Intermediate,post=RG_Pat4[i,:],target='exc') #,synapse=PositiveCovariance)
    if(os.path.isfile(prename+'weights_RG_Pat4_'+str(i)+'.data')):
        temp.connect_from_file(filename=prename+'weights_RG_Pat4_'+str(i)+'.data')
    else:
        temp.connect_all_to_all( weights=Uniform(0.1,0.5) )#weights=0.0)
    VelRG_Pat4.append(temp)


VelPF_Pat1 = []
for i in range(num_joints): 
    temp = Projection(pre=Intermediate,post=PF_Pat1[i,:],target='exc') #,synapse=PositiveCovariance)
    if(os.path.isfile(prename+'weights_PF_Pat1_'+str(i)+'.data')):
        temp.connect_from_file(filename=prename+'weights_PF_Pat1_'+str(i)+'.data')
    else:
        temp.connect_all_to_all(weights=Uniform(0.1,0.5) )#weights=0.0)

    VelPF_Pat1.append(temp)


VelPF_Pat2 = []
for i in range(num_joints): 
    temp = Projection(pre=Intermediate,post=PF_Pat2[i,:],target='exc') #,synapse=PositiveCovariance)
    if(os.path.isfile(prename+'weights_PF_Pat2_'+str(i)+'.data')):
        temp.connect_from_file(filename=prename+'weights_PF_Pat2_'+str(i)+'.data')
    else:
        temp.connect_all_to_all( weights=Uniform(0.1,0.5) )#weights=0.0)
    VelPF_Pat2.append(temp)


VelInjCurr = []
for i in range(num_joints):
    temp = Projection(pre=Intermediate,post=Inj_Curr[i,:], target='exc') #,synapse=PositiveCovariance)
    if(os.path.isfile(prename+'weights_InjCurr'+str(i)+'.data')):
        temp.connect_from_file(filename=prename+'weights_InjCurr'+str(i)+'.data')
        print('Injecting current from file...')
    else:
        temp.connect_all_to_all(weights=0.0)
        print('Injecting current from scratch...')
    VelInjCurr.append(temp)


min_position = 0
max_position = 0.2

def parameter_readout(population,min_value,max_value):
    #integrate the rates to get a parameter value
    total_rate = np.sum(population.r)  #.r
    aux = population.r/(total_rate+1e-20)
    size_step = (max_value-min_value)/num_cell_per_parm
    aux = aux*(size_step*np.arange(num_cell_per_parm))
    return min_value+np.sum(aux)

def gs(velocity):
    x, y, z = np.mgrid[-max_position:max_position:(2*max_position/num_cell_per_ax), -max_position:max_position:(2*max_position/num_cell_per_ax), -max_position:max_position:(2*max_position/num_cell_per_ax)]
    pos = np.empty(x.shape + (3,))
    pos[:, :, :,0] = x
    pos[:, :,:, 1] = y
    pos[:, :, :,2] = z
    rr = multivariate_normal(velocity,cov = np.identity(3)*0.0001) #0.0001
    a = rr.pdf(pos)
    return a

def gs2(velocity,max_position):
    x, y, z = np.mgrid[-max_position:max_position:(2*max_position/num_cell_per_ax), -max_position:max_position:(2*max_position/num_cell_per_ax), -max_position:max_position:(2*max_position/num_cell_per_ax)]
    pos = np.empty(x.shape + (3,))
    pos[:, :, :,0] = x
    pos[:, :,:, 1] = y
    pos[:, :, :,2] = z
    rr = multivariate_normal(velocity,cov = np.identity(3)*0.001) #0.001// 0.01 IN ORIGINAL // 0.02 in best new version
    a = rr.pdf(pos)
    return a

def gaussian(x,mu, sig):
    return np.exp(-(np.power(x[0] - mu[0], 2.) / (2 * np.power(sig[0], 2.)) + np.power(x[1] - mu[1], 2.) / (2 * np.power(sig[1], 2.)) + np.power(x[2] - mu[2], 2.) / (2 * np.power(sig[2], 2.))))


def neuron_update(population, velocity, factor, max_position):
    g = gs2(velocity, max_position) 
    population.baseline = g*factor/(np.sum(g)) 
    




