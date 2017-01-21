from distutils.core import setup
from distutils.extension import Extension
from Cython.Build import cythonize
import numpy

ext = Extension('KalmanFilter', sources=["KalmanFilter.pyx"], language="c++", include_dirs=[numpy.get_include()])

setup(name="KalmanFilter", ext_modules = cythonize([ext]))
