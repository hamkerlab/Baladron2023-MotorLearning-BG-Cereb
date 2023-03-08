# -*- coding: utf-8 -*-
"""
Created on Sun Jun 11 15:59:26 2017

@author: nasjo, tofo (iCub adaption)

"""

import importlib
import sys

import icub
import matplotlib.pyplot as plt
import numpy as np
import yarp

from ..iCub_connect import YARP_motor_control as mtr_ctrl
from ..parameter import iCub_joint_names
iCubMotor = importlib.import_module(iCub_joint_names)


def fPlot2DArm(All_Sensor, StartInd, ArmDraw, side):
    """
        Plot hand trajectory in a predefined workspace. With option "ArmDraw" on -> plot simplified 2D arm
    """

    TrajX=[]
    TrajY=[]

    fig = plt.figure(figsize=(8,6.73))

    # Denavit-Hartenberg-Transformation
    #           cos(theta_i)    -cos(alpha_i)sin(theta_i)   sin(alpha_i)sin(theta_i)    a_i*cos(theta_i)
    #           sin(theta_i)    cos(alpha_i)cos(theta_i)    -sin(alpha_i)cos(theta_i)   a_i*sin(theta_i)
    #   M_i =       0                  sin(alpha_i)                cos(alpha_i)                d_i
    #               0                       0                           0                       1

    iCub_arm = icub.iCubArm(side + "_v1")
    iCub_arm.releaseLink(0)
    iCub_arm.releaseLink(1)
    iCub_arm.releaseLink(2)

    theta = All_Sensor[StartInd:]
    if side == "left":
        arm_offset = iCubMotor.LShoulderPitch
    elif side == "right":
        arm_offset = iCubMotor.RShoulderPitch
    else:
        print("No correct side descriptor given! Select left or right.")

    for i in range(len(theta)):

        for j in range(16):
            iCub_arm.setAng(j+3, theta[i][arm_offset + j])

        TrSho = mtr_ctrl.yarpvec_2_npvec(iCub_arm.Position(3))
        TrElb = mtr_ctrl.yarpvec_2_npvec(iCub_arm.Position(6))
        TrEnd = mtr_ctrl.yarpvec_2_npvec(iCub_arm.EndEffPosition())

        XX=np.array ([TrSho[1], TrElb[1], TrEnd[1]])
        YY=-1 * np.array ([TrSho[0], TrElb[0], TrEnd[0]])


        if ArmDraw=='arm_on':
            plt.plot( XX, YY,'y', lw=1)
        plt.grid(True)
        # plt.axis([-350,50,0,350])


        TrajX.append(TrEnd[1])
        TrajY.append(-TrEnd[0])


    plt.plot( TrajX, TrajY,'b',lw=2)
    SW = np.loadtxt('CPG_lib/ICUBROBOT/iCub_leftHand_Workspace.txt')
    plt.plot(SW[:,0],SW[:,1],'g',lw=1)

    plt.show()

    return TrajX , TrajY
