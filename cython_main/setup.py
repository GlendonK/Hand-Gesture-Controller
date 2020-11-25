from distutils.core import setup
from distutils.extension import Extension
from Cython.Build import cythonize


examples_extension = Extension(
    name="C_py_interface",
    sources=["C_py_interface.pyx"],
    libraries=["examples"],
    library_dirs=["lib"],
    include_dirs=["lib"]
)
setup(
    name="C_py_interface",
    ext_modules=cythonize([examples_extension])
)