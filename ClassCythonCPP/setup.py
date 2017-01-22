from distutils.core import setup
from distutils.extension import Extension
from Cython.Build import cythonize
import numpy

ext = Extension('TestClass', sources=["TestClass.pyx"], language="c++", include_dirs=[numpy.get_include()])

setup(name="TestClass", ext_modules = cythonize([ext]))
