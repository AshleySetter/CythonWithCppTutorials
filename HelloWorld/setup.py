from distutils.core import setup
from distutils.extension import Extension
from Cython.Build import cythonize

ext = Extension('helloworld', sources=["helloworld.pyx"], language="c++")

setup(name="helloworld", ext_modules = cythonize([ext]))
