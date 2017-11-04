from distutils.core import setup
from distutils.extension import Extension
from Cython.Build import cythonize
import numpy

ext = Extension('SumArray', sources=["SumArray.pyx"], include_path = [numpy.get_include()])

setup(name="SumArray", ext_modules = cythonize([ext]))
