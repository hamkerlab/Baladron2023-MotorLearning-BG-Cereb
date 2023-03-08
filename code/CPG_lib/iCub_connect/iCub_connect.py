"""

@author: tofo

Class to control the iCub joints
"""

import numpy as np
import yarp

from . import YARP_motor_control as mtr_ctrl


class iCub():
    """
        class handling the iCub control for the CPG
    """
    def __init__(self, parts):
        yarp.Network_init()
        self.joint_mapping, self.ctrl_interfaces, self.motor_driver = mtr_ctrl.create_motor_dict(parts)

        self.parts_in_use = []
        self.sequence = {"head": 6, "torso": 3, "right_arm": 16, "right_leg": 6, "left_arm": 16, "left_leg": 6}
        for key in self.sequence:
            if parts.count(key) > 0:
                self.parts_in_use.append(key)

    def __del__(self):
        self.iCub_close_driver()

    def iCub_get_angles(self):
        """
            get robot angles -> read joint encoders
        """

        angles = np.empty(0)
        for part in self.parts_in_use:
            yarp_angles = mtr_ctrl.get_joint_position(self.ctrl_interfaces[part][1], self.ctrl_interfaces[part][2])
            angles = np.append(angles, np.round(mtr_ctrl.yarpvec_2_npvec(yarp_angles), 2))
        return np.radians(angles)

    def iCub_set_angles(self, motor_command):
        """
            set robot angles -> move joints
        """

        if len(motor_command) != len(self.joint_mapping):
            print("[Error] Joint count in motor_command not matches used joints!")
            return False
        current_pos = self.iCub_get_angles()
        start = 0
        for part in self.parts_in_use:
            idx = start + self.sequence[part]
            position = mtr_ctrl.npvec_2_yarpvec(np.degrees(motor_command[start:idx]))
            if not np.allclose(current_pos[start:idx], motor_command[start:idx], atol=0.000001):
                mtr_ctrl.goto_position_block(self.ctrl_interfaces[part][0], self.ctrl_interfaces[part][1], self.ctrl_interfaces[part][2], position)
            start = idx
        return True

    def iCub_close_driver(self):
        """
            close device driver
        """
        for part, driver in self.motor_driver:
            print("Close:", part)
            driver.close()
