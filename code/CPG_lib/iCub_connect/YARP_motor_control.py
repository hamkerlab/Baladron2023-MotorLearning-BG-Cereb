"""
Created on Thu Apr 13 15:16:32 2018

@author: tofo

library for functions related to the motor control
"""

import time

import numpy as np
import yarp


######################################################################
######################### init motor control #########################
def motor_init(part, control="position", robot_prefix="icubSim", client_prefix="client"):
    '''
        initialize motor control for the given part

        params: part        -- part of the iCub to be controlled (string: head, left_arm, right_arm, ...)
                control     -- control type: position(default) -> joint angle control ; velocity -> joint velocity control

        return: iPos    -- Position Controller for the given iCub part
                iEnc    -- Encoder for the controlled joints
                jnts    -- number of controlled joints
                driver  -- device driver; need to be returned, otherwise joint controlboard is closed

                Returns None for all if an error occured
    '''
    # prepare a property object
    props = yarp.Property()
    props.put("device", "remote_controlboard")
    props.put("local", "/" + client_prefix + "/" + part)
    props.put("remote", "/" + robot_prefix + "/" + part)

    # create remote driver
    driver = yarp.PolyDriver(props)

    if driver == None:
        print("Error: Motor initialization failed!")
        return None, None, None, None

    # query motor control interfaces
    if control == "position":
        iCtrl = driver.viewIPositionControl()
    elif control == "velocity":
        iCtrl = driver.viewIVelocityControl()
    iEnc = driver.viewIEncoders()

    if iCtrl == None:
        print("Error: Motor initialization failed!")
        return None, None, None, None

    # retrieve number of joints
    jnts = iCtrl.getAxes()

    print('----- Controlling', jnts, 'joints -----')
    return iCtrl, iEnc, jnts, driver


######################################################################
###################### go to head zero position ######################
def goto_zero_head_pos(iPos_head, iEnc_head, jnts_head):
    '''
        go to the all joints at 0 degree position

        params: iPos_head   -- Position Controller for the iCub head
                iEnc_head   -- Encoder for the head joints
                jnts_head   -- number of head joints
    '''

    zero_pos = set_pos_vector_same(0.0, jnts_head)
    iPos_head.positionMove(zero_pos.data())
    motion = False
    while not motion:
        act_pos = get_joint_position(iEnc_head, jnts_head)
        motion = iPos_head.checkMotionDone() and (
            abs(act_pos[4]) < (abs(zero_pos[4]) + 0.2))


######################################################################
########## Move joints of controlled part to a new position ##########
def goto_position_block(iPos, iEnc, jnts, position):
    '''
        Go to given position and block until motion done

        params: iPos        -- Position Controller for the iCub part
                iEnc        -- Encoder for the joints
                jnts        -- number of controlled joints
                position    -- new position as YARP-Vector
    '''

    iPos.positionMove(position.data())
    while not iPos.checkMotionDone():
        act_pos = get_joint_position(iEnc, jnts)
        # and (abs(act_pos[4]) < (abs(new_pos[4]) + 0.2))


######################################################################
##################### Move eyes to new position ######################
def move_eyes(eye_pos, iPos_h, jnts_h, offset_h=0.0):
    '''
        move the iCub eyes to a new position

        params: eye_pos     -- target eye position [ gaze_y, gaze_x, vergence_angle ]
                iPos_h      -- Position Controller for the iCub head
                jnts_h      -- number of head joints
                offset_h    -- head offset in left/right direction
    '''
    targ_pos = set_pos_vector_same(0.0, jnts_h)
    targ_pos.set(2, offset_h)
    targ_pos.set(3, eye_pos[0])
    targ_pos.set(4, (eye_pos[1] - offset_h))
    targ_pos.set(5, eye_pos[2])

    iPos_h.positionMove(targ_pos.data())
    motion = False
    while not motion:
        time.sleep(0.01)
        motion = iPos_h.checkMotionDone()
    time.sleep(0.1)


######################################################################
###################### get the joints positions ######################
def get_joint_position(iEnc, jnts, as_np=False):
    '''
        get position of controlled joints

        params: iEnc        -- Encoder for the controlled joints
                jnts        -- number of joints
                as_np       -- if True: a numpy array is returned
                                  False: a YARP vector is returned

        return: vector containing the joint positions -> YARP-Vector or numpy array dependent on as_np
    '''
    # read encoders
    yarp_angles = yarp.Vector(jnts)
    read = False
    read = iEnc.getEncoders(yarp_angles.data())
    while not read:
        time.sleep(0.1)
        read = iEnc.getEncoders(yarp_angles.data())
    if as_np:
        return yarpvec_2_npvec(yarp_angles)
    return yarp_angles


######################################################################
################## map motor control to dictionary ###################
def create_motor_dict(parts_used):
    '''
        wrap the motor control interfaces in a dictionary for a given set of robot parts
        (Used to connect the CPG to the iCub)

        params: parts_used      -- list with strings for the used robot parts

        return: joint_mapping   -- mapping of the part joint numbers to a sequence containing all joints
                ctrl_interfaces -- dictionary for all control interfaces
                motor_driver    -- list with all created device drivers
    '''

    joint_mapping = {}
    ctrl_interfaces = {}
    motor_driver = []
    sequence = {"head": 6, "torso": 3, "right_arm": 16, "right_leg": 6, "left_arm": 16, "left_leg": 6}
    j = 0
    for key in sequence:
        if key in parts_used:
            iCtrl, iEnc, jnts, driver = motor_init(key, client_prefix="CPG")
            if not (driver == None):
                if jnts != sequence[key]:
                    print("Error while motor initialization of part:", key)
                    break
                motor_driver.append((key, driver))
                for i in range(j, j + sequence[key]):
                    joint_mapping[str(i)] = key
                    ctrl_interfaces[key] = (iCtrl, iEnc, jnts)
                j += sequence[key]

    return joint_mapping, ctrl_interfaces, motor_driver


######################################################################
############# set YARP position vector with given values #############
def set_pos_vector(pos_vec, val_j0, val_j1, val_j2, val_j3, val_j4, val_j5):
    '''
        set position vector with given values for each joint (6 joints like iCub head)

        params: pos_vec     -- YARP position vector
                val_j0      -- value joint 0, double value
                val_j1      -- value joint 1, double value
                val_j2      -- value joint 2, double value
                val_j3      -- value joint 3, double value
                val_j4      -- value joint 4, double value
                val_j5      -- value joint 5, double value

        return: pos_vec     -- position as YARP vector
    '''
    pos_vec.set(0, val_j0)
    pos_vec.set(1, val_j1)
    pos_vec.set(2, val_j2)
    pos_vec.set(3, val_j3)
    pos_vec.set(4, val_j4)
    pos_vec.set(5, val_j5)

    return pos_vec


def set_pos_vector_array(position, jnts):
    '''
        set position vector with given values for each joint (e.g. 6 joints for iCub head)

        params: position    -- position in array-like structure (list/numpy array), double values
                jnts        -- number of joints

        return: pos_vec     -- position as YARP vector
    '''
    pos_vec = yarp.Vector(jnts)

    for j in range(jnts):
        pos_vec.set(j, position[j])

    return pos_vec


def set_pos_vector_same(value, jnts):
    '''
        set position vector with one value for all joints

        params: pos_vec     -- position vector
                value       -- value for all joints, double value
                jnts        -- number of joints

        return: pos_vec     -- position as YARP vector
    '''
    pos_vec = yarp.Vector(jnts)

    for j in range(jnts):
        pos_vec.set(j, value)

    return pos_vec


######################################################################
############ Convert between YARP vector and numpy array #############
def npvec_2_yarpvec(array):
    '''
        convert a 1D numpy array into a YARP vector

        params: array       -- 1D array-like position vector

        return: yarp_vec    -- YARP vector, result of conversion
    '''
    vector = np.array(array, dtype=np.float64)
    yarp_vec = yarp.Vector(vector.shape[0])

    for i in range(vector.shape[0]):
        yarp_vec.set(i, vector[i])

    return yarp_vec


def yarpvec_2_npvec(yarp_vec):
    '''
        convert a YARP vector into a 1D numpy array

        params: yarp_vec    -- 1D YARP vector

        return: vector      -- 1D Numpy array, result of conversion
    '''
    vector = np.zeros(yarp_vec.length(), dtype=np.float64)

    for i in range(yarp_vec.length()):
        vector[i] = yarp_vec.get(i)

    return vector
