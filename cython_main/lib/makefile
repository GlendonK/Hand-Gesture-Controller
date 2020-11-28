CC = gcc

default: libsensors.a

libsensors.a: sensors.o led_matrix.o
	ar rcs $@ $^
    
examples.o: examples.c examples.h led_matrix.o
	$(CC) -c $<

clean:
	rm *.o *.a