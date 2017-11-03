from distutils.core import setup
from distutils.extension import Extension
from Cython.Distutils import build_ext as build_pyx
import numpy 


ext = [Extension('SumArrayParallel', ['SumArrayParallel.pyx'], include_dirs=[numpy.get_include()], extra_compile_args=['-O3', '-fopenmp'], extra_link_args=['-O3', '-lgomp'], language="c++")]

setup(name = 'SumArrayParallel', ext_modules=ext, cmdclass = { 'build_ext': build_pyx })

