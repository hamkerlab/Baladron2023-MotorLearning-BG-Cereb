"""


@author: Torsten Follak

This file creates automatically the iCub-based config files needed for the CPG
"""

import os
import pickle

import numpy as np

from ..supportive.joint_limits import joint_limits, joint_names
from ..supportive.joint_positive_dir import posdir_dict


# create MyiCub file
def create_joint_limits(parts, path_prefix, name_postfix, j_names, j_limits):
    """
        create config file for joint limits
    """

    filepath = path_prefix + "CPG_lib/ICUBROBOT/Conf_Limits/"
    if not os.path.isdir(filepath):
        os.mkdir(os.path.abspath(filepath))
    name = "MyiCub" + name_postfix + ".txt"
    filename = filepath + name

    names = []
    limits_min = []
    limits_max = []

    joint_count = 0
    for part in parts:
        for i in range(len(j_limits[part])//2):
            names.append(joint_names[part][i])
            limits_min.append(j_limits[part]['joint_' + str(i) + '_min'])
            limits_max.append(j_limits[part]['joint_' + str(i) + '_max'])

            joint_count += 1

    text = np.zeros(len(names), dtype=[('names', 'U25'), ('min', float), ('max', float)])
    text['names'] = names
    text['min'] = np.radians(limits_min)
    text['max'] = np.radians(limits_max)

    np.savetxt(filename, text, fmt="%s %.4f %.4f")
    return joint_count, filename

# create MyiCubPositiveAngle file
def create_pos_angle(parts, path_prefix, name_postfix, j_names, j_pos_dir):
    """
        create config file for joint positive direction
    """
    
    filepath = path_prefix + "CPG_lib/ICUBROBOT/Conf_PosDir/"
    if not os.path.isdir(filepath):
        os.mkdir(os.path.abspath(filepath))
    name = "MyiCubPositiveAngle_E_or_F" + name_postfix + ".txt"
    filename = filepath + name

    names = []
    joint_count = 0
    for part in parts:
        for name in j_names[part]:
            names.append(name)
            joint_count += 1

    with open(filename, 'w') as f:
        for joint in names:
            f.write(joint + " " + posdir_dict[joint] + "\n")
    return joint_count, filename

# create iCubMotor
def create_joint_mapping(parts, path_prefix, name_postfix, j_names):
    """
        create config file for joint names
    """
    filename = path_prefix + "CPG_lib/ICUBROBOT/JointNames/iCubMotor" + name_postfix + ".py"
    names = []

    joint_count = 0
    for part in parts:
        for name in j_names[part]:
            names.append(name)
            joint_count += 1

    global_cmd = "global  "
    indx_list = ""

    for idx, name in enumerate(names):
        global_cmd += name
        indx_list  += '{:18s}'.format(name) + " = " + '{:2d}'.format(idx) + "\n"
        if idx < (len(names) - 1):
            global_cmd += ", "
        if idx%10 == 0 and idx > 0:
            global_cmd += "\\" "\n" "    "

    str_mtr_cmd = "global MotorCommand\n"
    str_set_mtr_cmd = "MotorCommand = [0 for x in range(" + str(len(names)) + ")]\n"

    with open(filename, 'w') as file:
        file.write("\n")
        file.write(global_cmd)
        file.write("\n\n")
        file.write(indx_list)
        file.write("\n")
        file.write(str_mtr_cmd)
        file.write(str_set_mtr_cmd)

    return joint_count, filename

# call all file creation methods
def create_all_files(parts_used, path_prefix, filename_postfix=""):
    """
        create all config files with given parameters
    """
    # Create ordered list of used parts
    part_list = []
    sequence = {"head": 6, "torso": 3, "right_arm": 16, "right_leg": 6, "left_arm": 16, "left_leg": 6}
    for key in sequence:
        if parts_used.count(key) > 0:
            part_list.append(key)

    print("Search configuration files...")
    filepath = path_prefix + "CPG_lib/supportive/Check_Conf/"
    if not os.path.isdir(filepath):
        os.mkdir(os.path.abspath(filepath))
    name = "check_config" + filename_postfix +  ".pkl"
    pickle_filename = filepath + name
    
    if os.path.isfile(pickle_filename):
        print("Found existing config files.")
        with open(pickle_filename, "rb") as checkfile:
            content = pickle.load(checkfile)
            if 'part_list' in content:
                if part_list == content['part_list']:
                    print("Existing config files matches given configuration. Skipped file creation.")
                    return content['jcount_limits'], content['file_limits'], content['file_posdir'], content['module_motor']

    print("Create configuration files...")
    jcount_limits, file_limits = create_joint_limits(part_list, path_prefix, filename_postfix, joint_names, joint_limits)
    jcount_posdir, file_posdir = create_pos_angle(part_list, path_prefix, filename_postfix, joint_names, posdir_dict)
    jcount_motor, file_motor = create_joint_mapping(part_list, path_prefix, filename_postfix, joint_names)

    tmp_string = file_motor.replace(path_prefix, "")
    tmp_string = tmp_string.replace("/", ".")
    module_motor = tmp_string.replace(".py", "")

    data_dict = {'part_list': part_list, 'jcount_limits': jcount_limits, 'file_limits': file_limits, 'file_posdir': file_posdir, 'module_motor': module_motor}

    if jcount_limits == jcount_posdir == jcount_motor:
        with open(pickle_filename, "wb") as checkfile:
            pickle.dump(data_dict, checkfile)

        print("File creation successful.")
        return jcount_limits, file_limits, file_posdir, module_motor
    else:
        print("ATTENTION!! Different joint count in the init files!")
        return 0, file_limits, file_posdir, module_motor


if __name__ == "__main__":
    path_prefix = "../"
    filename_postfix = "_larm"
    # parts: ["head", "torso", "right_arm", "right_leg", "left_arm", "left_leg"]
    parts_used = ["left_arm"]

    create_all_files(parts_used, path_prefix, filename_postfix)
