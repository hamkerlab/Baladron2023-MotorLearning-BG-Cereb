import icub
import numpy as np
import time
import YARP_motor_control as mtr_ctrl
import matplotlib.pyplot as plt

min_shoulder = 0.
max_shoulder = 160.8

min_elbow = 15.5
max_elbow = 106.

left_arm_pos =  [-80., 45., 80., 15., -67., 0., 0., 60., 80., 15., 30., 30., 45., 30., 45., 90. ]

trajectory = []
alpha_shldr = np.flip(np.arange(min_shoulder, max_shoulder, 0.5))
alpha_lbw = np.arange(min_elbow, max_elbow+0.5, 0.5)

path1 = []
path2 = []
path3 = []
path4 = []

for i in alpha_shldr:
    print("shoulder:", i)
    left_arm_pos[1] = i
    if i == min_shoulder:
        for j in alpha_lbw:
            left_arm_pos[3] = j
            path1.append(left_arm_pos[0:7])
    elif i == 160.5:
        for j in alpha_lbw:
            left_arm_pos[3] = j
            path2.append(left_arm_pos[0:7])
    else:
        left_arm_pos[3] = min_elbow
        path3.append(left_arm_pos[0:7])
        left_arm_pos[3] = max_elbow
        path4.append(left_arm_pos[0:7])

trajectory.extend(path4)
path1.reverse()
trajectory.extend(path1)
path3.reverse()
trajectory.extend(path3)
trajectory.extend(path2)

print(len(trajectory))

iCub_arm = icub.iCubArm("left_v1")
iCub_arm.releaseLink(0)
iCub_arm.releaseLink(1)
iCub_arm.releaseLink(2)
space = []
for i in range(len(trajectory)):
    for j in range(len(trajectory[i])):
        iCub_arm.setAng(j+3, np.radians(trajectory[i][j]))

    TrEnd = mtr_ctrl.yarpvec_2_npvec(iCub_arm.EndEffPosition())
    space.append([TrEnd[1], -TrEnd[0]])


np.savetxt('Workspace.txt', space)

space_np = np.array(space)

plt.plot(space_np[:,0],space_np[:,1],'g',lw=1)
plt.show()