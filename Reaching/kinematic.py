import numpy as np

def G(a, d, alph, theta):

    t1 = np.array([ [np.cos(theta), - np.sin(theta), 0,  0],[np.sin(theta), np.cos(theta), 0,  0],[0, 0, 1, 0],[0, 0, 0, 1]])
    bt = np.c_[ np.identity(3), np.array([0,0,d])]
    t2 = np.vstack([bt,[0,0,0,1]]) 
    
    ct =  np.c_[ np.identity(3), np.array([a,0,0])]
    t3 = np.vstack([ct,[0,0,0,1]])
    
    t4 = np.array([[1, 0, 0, 0],[ 0, np.cos(alph), -np.sin(alph), 0],[ 0, np.sin(alph), np.cos(alph), 0],[ 0, 0, 0, 1]])
 
    return np.matmul(np.matmul(np.matmul(t1,t2),t3),t4)
    
def wrist_position(a):  
    L1 = 0.05 
    L2 = 0.22 
    L3 = 0.16 

    theta2 = a[0] #np.radians(a1)#Shoulder yaw
    theta1 = a[1] #np.radians(a2)#Shoulder pitch
    theta3 = a[2] #np.radians(a3)#Shoulder roll
    theta4 = a[3] #np.radians(a4)#Elbow

    G_34 = G(L3, 0, 0, np.pi/2+theta4)
    G_23 = G(0, L2, np.pi/2, theta3+np.pi/2)
    G_12 = G(L1, 0, -np.pi/2, theta2+np.pi/2)
    G_01 = G(0, 0, -np.pi/2, theta1)

    G_02 = np.matmul(G_01,G_12)
    G_03 = np.matmul(G_02,G_23)
    G_04 = np.matmul(G_03,G_34)
    return G_04.dot(np.array([0, 0, 0, 1]).T)
    
def wrist_position2(a1,a2,a3,a4):  
    L1 = 0.05 
    L2 = 0.22 
    L3 = 0.16 

    theta2 = np.radians(a1)#Shoulder yaw
    theta1 = np.radians(a2)#Shoulder pitch
    theta3 = np.radians(a3)#Shoulder roll
    theta4 = np.radians(a4)#Elbow

    G_45 = G(-L3, 0, 0, np.pi/2+theta4)
    G_34 = G(0, L2, -np.pi/2, theta3+np.pi/2)
    G_23 = G(0, 0, np.pi/2, theta2/2+3*np.pi/4)
    G_12 = G(L1, 0, 0, theta2/2+3*np.pi/4)
    G_01 = G(0, 0, -np.pi/2, theta1+np.pi)

    G_02 = np.matmul(G_01, G_12)
    G_03 = np.matmul(G_02, G_23)
    G_04 = np.matmul(G_03, G_34)
    G_05 = np.matmul(G_04, G_45)
    return G_04.dot(np.array([0, 0, 0, 1]).T)
