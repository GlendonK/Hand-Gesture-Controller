  
LIB_DIR = lib

default: C_py_interface

C_py_interface: setup.py C_py_interface.pyx $(LIB_DIR)/libsensors.a
	python3 setup.py build_ext --inplace && rm -f C_py_interface.c && rm -Rf build

$(LIB_DIR)/libexamples.a:
	make -C $(LIB_DIR) libsensors.a

clean:
	rm *.so