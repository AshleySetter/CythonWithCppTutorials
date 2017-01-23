import numpy as np
import sympy
import matplotlib.pyplot as plt
import timeit

import KalmanFilter
import KalmanFilterPurePython

# Calculate parameters for Kalman filter
t = sympy.symbols('t', real = True, positive=True)
s = sympy.symbols('s', real = True, positive=True)
w = sympy.symbols('w', real = True, positive=True)

F = sympy.Matrix([
                [0, 1, 0],
                [-w**2, 0, w**2],
                [0, 0, 0]
                ])

def TransformSystemsDynamicsMatrix(F):
    MatrixSize = F.shape[0]
    temp = s*sympy.eye(MatrixSize)-F #sI-F
    temp_inv = temp.inv()
    invLaplace = sympy.inverse_laplace_transform(temp_inv, s, t)
    return invLaplace

A_sympy = TransformSystemsDynamicsMatrix(F)
A_fn = sympy.lambdify([w,t], A_sympy)

Ts = 0.05
w = 1
A = A_fn(w, Ts)

class data:
        pass

data.time = np.arange(0, 100*2*np.pi/w, Ts) # 100 periods of oscillation
print("{} Points to be filtered".format(len(data.time)))
noiseAmp = 5
data.trueSignal = 300 + 5*np.sin(w*data.time + 0)
data.signal = data.trueSignal + np.random.normal(0, noiseAmp, len(data.trueSignal))
Q00 = Ts**3/3
Q10 = Ts**2/2
Q01 = Q10
Q11 = Ts

InitialStateError = 9999999999999.0
Proc_Noise_Sigma = 0.002

B = np.matrix("0")
H = np.matrix("1.0 0 1.0")
x_init = np.matrix("0 ; 0; 350.0")
P = np.matrix("{0} 0 0 ; 0 {0} 0 ; 0 0 {0}".format(InitialStateError))
Q = Proc_Noise_Sigma**2 * np.matrix("{0} {1} 0; {2} {3} 0 ; 0 0 0".format(Q00, Q10, Q01, Q11))
R = np.matrix(10.0)

    
N = 3

print("Constructing Filter")

kf = KalmanFilter.CKalmanFilter(N, np.array(A), np.array(P), np.array(Q), np.array(H).flatten(), np.array(x_init).flatten(), float(R))

print("Executing Filtering")

start_time = timeit.default_timer()
ResultData = kf.FilterData(data.signal, len(data.signal))
elapsed = timeit.default_timer() - start_time
print("C++ filtering took {}s".format(elapsed))

print("Constructing Python Filter")

KF2 =  KalmanFilterPurePython.KalmanFilterLinear(A, B, H, x_init, P, Q, R)

print("Executing Python Filtering")

start_time = timeit.default_timer()
KalmanPredictionArray = []
KalmanErrorArray = []
KalmanGainArray = []
for i, x in enumerate(data.signal):
    X_state = np.matrix('{0} ; {1}'.format(x, 0))
    KF2.Step(np.matrix([0]), np.matrix([x]))
    KalmanPredictionArray.append(KF2.current_state_estimate)
    KalmanErrorArray.append(KF2.current_prob_estimate)
    KalmanGainArray.append(KF2.KG)
    
KalmanPredictionArray = np.array(KalmanPredictionArray)
KalmanErrorArray = np.array(KalmanErrorArray)
KalmanGainArray = np.array(KalmanGainArray)

x = KalmanPredictionArray[:, 0] + KalmanPredictionArray[:, 2]
elapsed = timeit.default_timer() - start_time
print("C++ filtering took {}s".format(elapsed))

plt.figure(figsize=[10, 10])
plt.plot(data.time, data.signal, label="noisy sine wave", color='blue', alpha=0.6)
plt.plot(data.time, data.trueSignal, label="pure source sine wave", lw=3, color='red', alpha=0.8)
plt.plot(data.time, x, label="Pure Python Kalman Filter Output", lw=3, color='darkblue', alpha=0.9)
plt.plot(data.time, ResultData, label="C++ Kalman Filter Output", lw=3, color='darkred', alpha=0.9)

plt.legend(loc="best")
plt.xlabel("Time (s)")
plt.ylabel("x(t)")

plt.show()
