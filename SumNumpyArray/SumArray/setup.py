from distutils.core import setup
from distutils.extension import Extension
from Cython.Build import cythonize

ext = Extension('SumArray', sources=["SumArray.pyx"], language="c++")

setup(name="SumArray", ext_modules = cythonize([ext]))
