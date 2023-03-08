#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
Code for the paper: 

Baladron, J., Vitay, J., Fietzek, T. and Hamker, F. H.
The contribution of the basal ganglia and cerebellum to motor learning: a neuro-computational approach.

Copyright the Authors (License MIT)

Definition of the basal ganglia module.
"""

from ANNarchy import *

from cpg import *
import pickle

LinearNeuron_trace = Neuron(
    parameters= """
        tau = 10.0
        baseline = 0.0
        noise = 0.0
        tau_trace = 120.0
        lesion = 1.0
    """,
    equations="""
        tau*dmp/dt + mp = sum(exc) - sum(inh) + baseline + noise*Uniform(-1.0,1.0)
        r = lesion*pos(mp)
        tau_trace*dtrace/dt + trace = r
    """
)

LinearNeuron = Neuron(
    parameters= """
        tau = 10.0
        baseline = 0.0
        noise = 0.0
        lesion = 1.0
    """,
    equations="""
        tau*dmp/dt + mp = sum(exc) - sum(inh) + baseline + noise*Uniform(-1.0,1.0)
        r = lesion*pos(mp)
    """
)

LinearNeuron_neg = Neuron(
    parameters= """
        tau = 10.0
        baseline = 0.0
        noise = 0.0
        lesion = 1.0
    """,
    equations="""
        tau*dmp/dt + mp = sum(exc) - sum(inh) + baseline + noise*Uniform(-1.0,1.0)
        r = lesion*mp
    """
)

DopamineNeuron = Neuron(
    parameters="""
        tau = 10.0
        firing = 0
        inhibition = 0.0
        baseline = 0.0
        exc_threshold = 0.001
        factor_inh = 10.0
    """,
    equations="""
        ex_in = if (sum(exc)>exc_threshold): 1 else: 0
        s_exc = sum(exc)
        s_inh = sum(inh)
        aux = if (firing>0): (ex_in)*( pos(sum(exc)-baseline-s_inh) + baseline) + (1-ex_in)*(-factor_inh*sum(inh)+baseline)  else: baseline
        tau*dmp/dt + mp =  aux
        r = if (mp>0.0): mp else: 0.0
    """
)

PostCovariance = Synapse(
    parameters="""
        tau = 1000.0
        tau_alpha = 10.0
        regularization_threshold = 1.0
        threshold_post = 0.0
        threshold_pre = 0.0
    """,
    equations="""
        tau_alpha*dalpha/dt  + alpha =  pos(post.mp - regularization_threshold)
        trace = (pre.r - mean(pre.r) - threshold_pre) * pos(post.r - mean(post.r) - threshold_post)
	delta = (trace - alpha*pos(post.r - mean(post.r) - threshold_post)*pos(post.r - mean(post.r) - threshold_post)*w)
        tau*dw/dt = delta : min=0
   """
)
PreCovariance = Synapse(
    parameters="""
        tau = 1000.0
        tau_alpha = 10.0
        regularization_threshold = 1.0
        threshold_post = 0.0
        threshold_pre = 0.0
    """,
    equations="""
        tau_alpha*dalpha/dt  + alpha =  pos(post.mp - regularization_threshold)
        trace = pos(pre.r - mean(pre.r) - threshold_pre) * (post.r - mean(post.r) - threshold_post)
	delta = (trace - alpha*pos(post.r - mean(post.r) - threshold_post)*pos(post.r - mean(post.r) - threshold_post)*w)
        tau*dw/dt = delta : min=0
   """
)

ReversedSynapse = Synapse(
    parameters="""
        reversal = 0.3
    """,
    psp="""
        w*pos(reversal-pre.r)
    """

)

#DA_typ = 1  ==> D1 type  DA_typ = -1 ==> D2 type
DAPostCovarianceNoThreshold = Synapse(
    parameters="""
        tau=1000.0
        tau_alpha=10.0
        regularization_threshold=1.0
        baseline_dopa = 0.1
        K_burst = 1.0
        K_dip = 0.4
        DA_type = 1
        threshold_pre=0.0
        threshold_post=0.0
    """,
    equations="""
        tau_alpha*dalpha/dt  + alpha = pos(post.mp - regularization_threshold)
        dopa_sum = 2.0*(post.sum(dopa) - baseline_dopa)
        trace = pos(post.r -  mean(post.r) - threshold_post) * (pre.r - mean(pre.r) - threshold_pre)
	condition_0 = if (trace>0.0) and (w >0.0): 1 else: 0
        dopa_mod = if (DA_type*dopa_sum>0): DA_type*K_burst*dopa_sum else: condition_0*DA_type*K_dip*dopa_sum
        delta = (dopa_mod* trace - alpha*pos(post.r - mean(post.r) - threshold_post)*pos(post.r - mean(post.r) - threshold_post))
        tau*dw/dt = delta : min=0
    """


)


DAPostCovarianceNoThreshold_trace = Synapse(
    parameters="""
        tau=1000.0
        tau_alpha=10.0
        regularization_threshold=1.0
        baseline_dopa = 0.1
        K_burst = 1.0
        K_dip = 0.4
        DA_type = 1
        threshold_pre=0.0
        threshold_post=0.0
    """,
    equations="""
        tau_alpha*dalpha/dt  + alpha = pos(post.mp - regularization_threshold)
        dopa_sum = 2.0*(post.sum(dopa) - baseline_dopa)
        trace = pos(post.trace -  mean(post.trace) - threshold_post) * (pre.r - mean(pre.r) - threshold_pre)
	condition_0 = if (trace>0.0) and (w >0.0): 1 else: 0
        dopa_mod = if (DA_type*dopa_sum>0): DA_type*K_burst*dopa_sum else: condition_0*DA_type*K_dip*dopa_sum
        delta = (dopa_mod* trace - alpha*pos(post.r - mean(post.r) - threshold_post)*pos(post.r - mean(post.r) - threshold_post))
        tau*dw/dt = delta : min=0
    """


)

#Excitatory synapses STN -> SNr
DAPreCovariance_excitatory = Synapse(
    parameters="""
    tau=1000.0
    tau_alpha=10.0
    regularization_threshold=1.0
    baseline_dopa = 0.1
    K_burst = 1.0
    K_dip = 0.4
    DA_type= 1
    threshold_pre=0.0
    threshold_post=0.0
    """,
    equations = """
        tau_alpha*dalpha/dt  = pos( post.mp - regularization_threshold) - alpha
        dopa_sum = 2.0*(post.sum(dopa) - baseline_dopa)
        trace = pos(pre.r - mean(pre.r) - threshold_pre) * (post.r - mean(post.r) - threshold_post)
        aux = if (trace<0.0): 1 else: 0
        dopa_mod = if (dopa_sum>0): K_burst * dopa_sum else: K_dip * dopa_sum * aux
        delta = dopa_mod * trace - alpha * pos(trace)
        tau*dw/dt = delta : min=0
    """
)


#Inhibitory synapses SNr -> SNr and STRD2 -> GPe
DAPreCovariance_inhibitory = Synapse(
    parameters="""
    tau=1000.0
    tau_alpha=10.0
    regularization_threshold=1.0
    baseline_dopa = 0.1
    K_burst = 1.0
    K_dip = 0.4
    DA_type= 1
    threshold_pre=0.0
    threshold_post=0.0
    negterm = 1
    """,
    equations="""
        tau_alpha*dalpha/dt = pos( -post.mp - regularization_threshold) - alpha
        dopa_sum = 2.0*(post.sum(dopa) - baseline_dopa)
        trace = pos(pre.r - mean(pre.r) - threshold_pre) * (mean(post.r) - post.r  - threshold_post)
        aux = if (trace>0): negterm else: 0
        dopa_mod = if (DA_type*dopa_sum>0): DA_type*K_burst*dopa_sum else: aux*DA_type*K_dip*dopa_sum
        trace2 = trace
        delta = dopa_mod * trace2 - alpha * pos(trace2)
        tau*dw/dt = delta : min=0
    """
)


DAPreCovariance_inhibitory_trace = Synapse(
    parameters="""
    tau=1000.0
    tau_alpha=10.0
    regularization_threshold=1.0
    baseline_dopa = 0.1
    K_burst = 1.0
    K_dip = 0.4
    DA_type= 1
    threshold_pre=0.0
    threshold_post=0.0
    """,
    equations="""
        tau_alpha*dalpha/dt = pos( -post.mp - regularization_threshold) - alpha
        dopa_sum = 2.0*(post.sum(dopa) - baseline_dopa)
        trace = pos(pre.r - mean(pre.r) - threshold_pre) * (mean(post.trace) - post.trace  - threshold_post)
        aux = if (trace>0): 1 else: 0
        dopa_mod = if (DA_type*dopa_sum>0): DA_type*K_burst*dopa_sum else: aux*DA_type*K_dip*dopa_sum
        trace2 = trace
        delta = dopa_mod * trace2 - alpha * pos(trace2)
        tau*dw/dt = delta : min=0
    """
)


DAPrediction = Synapse(
    parameters="""
        tau = 100000.0
        baseline_dopa = 0.1
   """,
   equations="""
       aux = if (post.sum(exc)>0): 1.0 else: 3.0
       delta = aux*pos(post.r - baseline_dopa)*pos(pre.r - mean(pre.r))
       tau*dw/dt = delta : min=0
   """


)


num_actions = 120
baseline_dopa = 0.1

Cortical_input = Population(name="Cortex", geometry=(20,20,20),neuron = LinearNeuron_trace) 
Cortical_input.tau = 10.0
Cortical_input.noise = 0.0
Cortical_input.baseline = 0.0
Cortical_input.lesion = 1.0


StrD1_putamen = Population(name="StrD1_putamen", geometry=num_actions,neuron = LinearNeuron_trace)
StrD1_putamen.tau = 10.0
StrD1_putamen.noise = 0.0
StrD1_putamen.baseline = 0.0
StrD1_putamen.lesion = 1.0


StrThal_putamen = Population(name="StrThal_putamen", geometry = num_actions, neuron=LinearNeuron)
StrThal_putamen.tau = 5.0
StrThal_putamen.noise = 0.0
StrThal_putamen.baseline = 0.0
StrThal_putamen.lesion = 1.0

SNr_putamen = Population(name="SNr_putamen", geometry =num_actions, neuron=LinearNeuron_trace)
SNr_putamen.tau = 5.0
SNr_putamen.noise = 0.05
SNr_putamen.baseline = 1.1
SNr_putamen.tau_trace = 350.

VA_putamen = Population(name="VA_putamen", geometry=num_actions, neuron=LinearNeuron)
VA_putamen.tau = 8.0
VA_putamen.noise = 0 #0.001
VA_putamen.baseline = 0.9 #0.4

SNc_put = Population(name='SNc_put',geometry=1,neuron=DopamineNeuron)
SNc_put.exc_threshold=0.001 #1.5
SNc_put.baseline = baseline_dopa
SNc_put.factor_inh = 1.0

PM = Population(name="PM", geometry = num_actions, neuron=LinearNeuron, stop_condition = "r > 2.0") # stop condition was 1.8
PM.tau = 20.0
PM.noise = 0 #0.001#0.1

reward = Population(geometry=1,neuron=LinearNeuron)
reward_inh = Population(geometry=1,neuron=LinearNeuron)


factor = 1.0


StrThalStrThal_putamen = Projection(pre=StrThal_putamen,post=StrThal_putamen,target='inh')
StrThalStrThal_putamen.connect_all_to_all(weights=0.4)


SNrSNr_putamen = Projection(pre=SNr_putamen,post=SNr_putamen,target='exc',synapse=ReversedSynapse)
SNrSNr_putamen.connect_all_to_all(weights=0.1)  
SNrSNr_putamen.reversal = 1.2 

VAVA_putamen = Projection(pre=VA_putamen,post=VA_putamen,target='inh')
VAVA_putamen.connect_all_to_all(weights=0.4)



def load_connectivity_dense(filename):
    """
    The code loads a single(!) connectivity matrix from a file stored by ANNarchy.

    In case of dense matrix you can simply use the stored values. Dense means
    all_to_all.
    """
    with open(filename, mode = 'rb') as r_file:
        desc = pickle.load(r_file)

    return np.array(desc['w']) # Full-LIL to matrix



prename = '40prim2_'

CortexStrD1_putamen = Projection(pre=Cortical_input,post=StrD1_putamen,target='exc',synapse=DAPostCovarianceNoThreshold)# DAPreCovariance_inhibitory)
CortexStrD1_putamen.connect_all_to_all(weights=0)  #Uniform(1.0,1.1)) #weights=0)
CortexStrD1_putamen.tau = 2200 #2200  
CortexStrD1_putamen.regularization_threshold =  1.200 #2.0#1500 
CortexStrD1_putamen.tau_alpha = 20.0
CortexStrD1_putamen.baseline_dopa = baseline_dopa
CortexStrD1_putamen.K_dip = 0.1 #0.1 IN ORIGINAL
CortexStrD1_putamen.K_burst = 1.2
CortexStrD1_putamen.threshold_post = 0.1
CortexStrD1_putamen.threshold_pre = 0.0 #0.1
CortexStrD1_putamen.DA_type=1



StrD1SNr = Projection(pre=StrD1_putamen,post=SNr_putamen,target='inh')
StrD1SNr.connect_one_to_one(weights=0.8) 


SNrVA_putamen = Projection(pre=SNr_putamen,post=VA_putamen,target='inh')
SNrVA_putamen.connect_one_to_one(weights=0.6) #0.5 #0.5

VAPM_putamen = Projection(pre=VA_putamen,post=PM,target='exc')
VAPM_putamen.connect_one_to_one(weights=1.0) #1.0 #3.0


PMStr = Projection(pre=PM,post=StrD1_putamen,target='exc')
PMStr.connect_one_to_one(weights=0.5)


SNcStrD1_put = Projection(pre=SNc_put,post=StrD1_putamen,target='dopa')
SNcStrD1_put.connect_all_to_all(weights=1.0) 

SNcSNr_put = Projection(pre=SNc_put,post=SNr_putamen,target='dopa')
SNcSNr_put.connect_all_to_all(weights=1.0)

HvSNc = Projection(pre=reward,post=SNc_put,target='exc')
HvSNc.connect_all_to_all(weights=1.0)
HvSNc_inh = Projection(pre=reward_inh,post=SNc_put,target='inh')
HvSNc_inh.connect_all_to_all(weights=1.0)



StrD1SNc_put = Projection(pre=StrD1_putamen,post=SNc_put,target='inh',synapse=DAPrediction)
StrD1SNc_put.connect_all_to_all(weights=0.0)
StrD1SNc_put.tau = 10000 
StrD1SNc_put.baseline_dopa = baseline_dopa
