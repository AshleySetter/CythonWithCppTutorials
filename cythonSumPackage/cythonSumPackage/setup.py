from setuptools import setup
from setuptools.extension import Extension
import numpy

extensions = [
    Extension(
    name="SumArrayCython",
    sources=["cythonSumPackage/SumArrayCython/SumArray.c"],)
]

setup(name='cythonSumPackage',
      version='1.0',
      description='...',
      author='Ashley Setter',
      author_email='A.Setter@soton.ac.uk',
      include_package_data=True,
      packages=['cythonSumPackage',
                'cythonSumPackage.SumArrayCython',
                'cythonSumPackage.UseSumArrayCython',
      ],
      ext_modules = extensions,
)
