from distutils.core import setup
from distutils.extension import Extension
from Cython.Build import cythonize

# file to build the cython.

examples_extension = Extension(
    name="C_py_interface",
    sources=["C_py_interface.pyx"],
    libraries=["sensors"],
    library_dirs=["lib"],
    include_dirs=["lib"]
)
setup(
    name="C_py_interface",
    ext_modules=cythonize([examples_extension])
)