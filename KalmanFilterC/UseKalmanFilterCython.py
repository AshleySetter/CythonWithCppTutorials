import numpy as np
import KalmanFilter

kf = KalmanFilter.CKalmanFilter(3, np.array([[1, 2, 3], [4, 5, 6], [7, 8, 9.0]]))
