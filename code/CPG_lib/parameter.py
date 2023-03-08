"""
Created on Wed July 22 2020

@author tofo

parameterfile for the CPG with iCub
-> handles the creation of the config files

Set used_parts, path_prefix and filename_postfix denpendent on the setup
"""

from .supportive.create_motor_config_files import create_all_files

# parts from the iCub to be controlled with the CPG
# possible parts: ["head", "torso", "right_arm", "right_leg", "left_arm", "left_leg"]
used_parts = ["head", "torso", "right_arm", "left_arm"]

# path from main file e.g. iCub_drawing to CPG_lib folder
path_prefix = ""

# postfix for the names of the configuration files
filename_postfix = "_nolegs"

## automatically created parameter
number_cpg, my_iCub_limits, positive_angle_dir, iCub_joint_names = create_all_files(used_parts, path_prefix, filename_postfix)
