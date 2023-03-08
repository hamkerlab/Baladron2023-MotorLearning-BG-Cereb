"""
The following data are the joint limits for the iCub. Here, the minimum and maximum value is given.
The data is retrieved from the iCub-simulator. In the simulator files (directory: icub-main/app/simConfig/conf,
with icub-main as main directory of the simulator repository) for every robot part an ini file with the joint limits is given.
In order to ensure a save usage with the real robot, the values should be compared to the values in the robot documentation to avoid collisions.
"""

# [head]
head = {}
head['joint_0_min'] = -40.0
head['joint_1_min'] = -70.0
head['joint_2_min'] = -55.0
head['joint_3_min'] = -35.0
head['joint_4_min'] = -50.0
head['joint_5_min'] = -0.0

head['joint_0_max'] =  30.0
head['joint_1_max'] =  60.0
head['joint_2_max'] =  55.0
head['joint_3_max'] =  15.0
head['joint_4_max'] =  52.0
head['joint_5_max'] =  90.0


# [right_arm]
right_arm = {}
right_arm['joint_0_min'] = -95.0
right_arm['joint_1_min'] =  0.0
right_arm['joint_2_min'] = -37.0
right_arm['joint_3_min'] =  15.5
right_arm['joint_4_min'] = -90.0
right_arm['joint_5_min'] = -90.0
right_arm['joint_6_min'] = -20.0
right_arm['joint_7_min'] =  0.0
right_arm['joint_8_min'] =  10.0
right_arm['joint_9_min'] =  0.0
right_arm['joint_10_min'] =  0.0
right_arm['joint_11_min'] =  0.0
right_arm['joint_12_min'] =  0.0
right_arm['joint_13_min'] =  0.0
right_arm['joint_14_min'] =  0.0
right_arm['joint_15_min'] =  0.0

right_arm['joint_0_max'] =  10.0
right_arm['joint_1_max'] =  160.8
right_arm['joint_2_max'] =  80.0
right_arm['joint_3_max'] =  106.0
right_arm['joint_4_max'] =  90.0
right_arm['joint_5_max'] =  0.0
right_arm['joint_6_max'] =  40.0
right_arm['joint_7_max'] =  60.0
right_arm['joint_8_max'] =  90.0
right_arm['joint_9_max'] =  90.0
right_arm['joint_10_max'] =  180.0
right_arm['joint_11_max'] =  90.0
right_arm['joint_12_max'] =  180.0
right_arm['joint_13_max'] =  90.0
right_arm['joint_14_max'] =  180.0
right_arm['joint_15_max'] =  270.0


# [left_arm]
left_arm = {}
left_arm['joint_0_min'] = -95.0
left_arm['joint_1_min'] =  0.0
left_arm['joint_2_min'] = -37.0
left_arm['joint_3_min'] =  15.5
left_arm['joint_4_min'] = -90.0
left_arm['joint_5_min'] = -90.0
left_arm['joint_6_min'] = -20.0
left_arm['joint_7_min'] =  0.0
left_arm['joint_8_min'] =  10.0
left_arm['joint_9_min'] =  0.0
left_arm['joint_10_min'] =  0.0
left_arm['joint_11_min'] =  0.0
left_arm['joint_12_min'] =  0.0
left_arm['joint_13_min'] =  0.0
left_arm['joint_14_min'] =  0.0
left_arm['joint_15_min'] =  0.0

left_arm['joint_0_max'] =  10.0
left_arm['joint_1_max'] =  160.8
left_arm['joint_2_max'] =  80.0
left_arm['joint_3_max'] =  106.0
left_arm['joint_4_max'] =  90.0
left_arm['joint_5_max'] =  0.0
left_arm['joint_6_max'] =  40.0
left_arm['joint_7_max'] =  60.0
left_arm['joint_8_max'] =  90.0
left_arm['joint_9_max'] =  90.0
left_arm['joint_10_max'] =  180.0
left_arm['joint_11_max'] =  90.0
left_arm['joint_12_max'] =  180.0
left_arm['joint_13_max'] =  90.0
left_arm['joint_14_max'] =  180.0
left_arm['joint_15_max'] =  270.0


# [right_leg]
right_leg = {}
right_leg['joint_0_min'] = -30.0
right_leg['joint_1_min'] = -0.0
right_leg['joint_2_min'] = -80.0
right_leg['joint_3_min'] = -125.0
right_leg['joint_4_min'] = -20.0
right_leg['joint_5_min'] = -22.0

right_leg['joint_0_max'] =  90.0
right_leg['joint_1_max'] =  90.0
right_leg['joint_2_max'] =  78.0
right_leg['joint_3_max'] =  15.0
right_leg['joint_4_max'] =  44.0
right_leg['joint_5_max'] =  22.0


# [left_leg]
left_leg = {}
left_leg['joint_0_min'] = -30.0
left_leg['joint_1_min'] = -0.0
left_leg['joint_2_min'] = -80.0
left_leg['joint_3_min'] = -125.0
left_leg['joint_4_min'] = -20.0
left_leg['joint_5_min'] = -22.0

left_leg['joint_0_max'] =  90.0
left_leg['joint_1_max'] =  90.0
left_leg['joint_2_max'] =  78.0
left_leg['joint_3_max'] =  15.0
left_leg['joint_4_max'] =  44.0
left_leg['joint_5_max'] =  22.0


# [torso]
torso = {}
torso['joint_0_min'] = -50.0
torso['joint_1_min'] = -30.0
torso['joint_2_min'] = -10.0

torso['joint_0_max'] =  50.0
torso['joint_1_max'] =  30.0
torso['joint_2_max'] =  70.0

joint_limits = {'head': head, 'torso': torso, 'right_arm': right_arm, 'right_leg': right_leg, 'left_arm': left_arm, 'left_leg': left_leg }


name_head = ["NeckPitch", "NeckRoll", "NeckYaw", "EyesTilt", "EyesVersion", "EyesVergence"]
name_torso = ["TorsoYaw", "TorsoRoll", "TorsoPitch"]
name_rarm = ["RShoulderPitch", "RShoulderRoll", "RShoulderYaw", "RElbow", "RWristProsup", "RWristPitch", "RWristYaw", "RHandFinger", "RThumbOppose", "RThumbProximal", "RThumbDistal", "RIndexProximal", "RIndexDistal", "RMiddleProximal", "RMiddleDistal", "RPinky"]
name_rleg = ["RHipPitch", "RHipRoll", "RHipYaw", "RKnee", "RAnklePitch", "RAnkleRoll"]
name_larm = ["LShoulderPitch", "LShoulderRoll", "LShoulderYaw", "LElbow", "LWristProsup", "LWristPitch", "LWristYaw", "LHandFinger", "LThumbOppose", "LThumbProximal", "LThumbDistal", "LIndexProximal", "LIndexDistal", "LMiddleProximal", "LMiddleDistal", "LPinky"]
name_lleg = ["LHipPitch", "LHipRoll", "LHipYaw", "LKnee", "LAnklePitch", "LAnkleRoll"]

joint_names = {'head': name_head, 'torso': name_torso, 'right_arm': name_rarm, 'right_leg': name_rleg, 'left_arm': name_larm, 'left_leg': name_lleg }


