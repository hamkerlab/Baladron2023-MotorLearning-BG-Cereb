import matplotlib.pyplot as plt
import numpy as np

def fPlotJointCommandSensor(All_Command,All_Sensor,JointIndex,Str):

    data2print1=[]
    for i in range(0,len(All_Command)):
        data2print1.append(All_Command[i][JointIndex])

    data2print2=[]
    for i in range(0,len(All_Sensor)):
        data2print2.append(All_Sensor[i][JointIndex])

    plt.plot( range(len(data2print1)), data2print1,'b', range(len(data2print2)),data2print2,'r')
    plt.xlabel('Time')
    plt.ylabel('Motor Command / Sensor Value')
    plt.title(Str)
    plt.grid(True)
    plt.show()


def fPlotCPG_Layer(RG_Activity, PF_Activity, MN_Activity, Joint_angles, JointIdxs, JointNames):

    RG_Activity_np = np.array(RG_Activity)
    PF_Activity_np = np.array(PF_Activity)
    MN_Activity_np = np.array(MN_Activity)
    Joint_angles_np = np.array(np.degrees(Joint_angles))

    fig, axs = plt.subplots(5, len(JointIdxs), sharex=True, figsize=(12, 14), gridspec_kw={"height_ratios":[0.02,1,1,1,1]})

    for idx, j in enumerate(JointIdxs):
        axs[0, idx].axis("off")
        axs[0, idx].set_title("Joint: " + JointNames[idx])

        # plot RG Layer Activity
        axs[1, idx].plot(range(RG_Activity_np.shape[1]), RG_Activity_np[0, :, j],'b', range(RG_Activity_np.shape[1]), RG_Activity_np[1, :, j],'r')
        axs[1, idx].grid(True)
        if idx == 0:
            axs[1, idx].set_ylabel('Potential')
        axs[1, idx].set_title("RG Layer")

        # plot PF Layer Activity
        axs[2, idx].plot(range(PF_Activity_np.shape[1]), PF_Activity_np[0, :, j],'b', range(PF_Activity_np.shape[1]), PF_Activity_np[1, :, j],'r')
        axs[2, idx].grid(True)
        if idx == 0:
            axs[2, idx].set_ylabel('Activity')
        axs[2, idx].set_title("PF Layer")

        # plot MN Layer Activity
        axs[3, idx].plot(range(MN_Activity_np.shape[1]), MN_Activity_np[0, :, j],'b', range(MN_Activity_np.shape[1]), MN_Activity_np[1, :, j],'r')
        axs[3, idx].grid(True)
        if idx == 0:
            axs[3, idx].set_ylabel('Activity')
        axs[3, idx].set_title("MN Layer")

        # plot Joint angles
        axs[4, idx].plot(range(Joint_angles_np.shape[1]), Joint_angles_np[0, :, j],'b', range(Joint_angles_np.shape[1]), Joint_angles_np[1, :, j],'r')
        axs[4, idx].grid(True)
        axs[4, idx].set_xlabel('Time')
        if idx == 0:
            axs[4, idx].set_ylabel('Joint angle')
        axs[4, idx].set_title("Motor Command / Sensor Value")

    fig.tight_layout(pad=2.75)
    plt.show()


def fPlot(sig, XLabel, YLabel, Title):
    plt.plot( range(len(sig)), sig,'b')
    plt.xlabel(XLabel)
    plt.ylabel(YLabel)
    plt.title(Title)
    plt.grid(True)
    plt.show()

"""
    # row and column sharing
    f, ((ax1, ax2), (ax3, ax4)) = plt.subplots(2, 2)
    ax1.plot( range(len(date2print1)), date2print1,'b', range(len(date2print2)),date2print2,'r')
    #ax1.set_title('Sharing x per column, y per row')
    ax2.plot( range(len(date2print1)), date2print1,'b', range(len(date2print2)),date2print2,'r')
    ax3.plot( range(len(date2print1)), date2print1,'b', range(len(date2print2)),date2print2,'r')
    ax4.plot( range(len(date2print1)), date2print1,'b', range(len(date2print2)),date2print2,'r')
    plt.grid(True)
    plt.show()

"""
