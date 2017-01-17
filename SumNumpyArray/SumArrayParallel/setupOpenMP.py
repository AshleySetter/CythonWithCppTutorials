from distutils.core import setup
from distutils.extension import Extension
from Cython.Build import cythonize

ext = Extension('SumArrayParallel', sources=["SumArrayParallel.pyx"], language="c++", extra_compile_args=['-fopenmp'], extra_link_args=['-lgomp'])

setup(name="SumArrayParallel", ext_modules = cythonize([ext]))
