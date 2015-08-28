all:test.so 
test.so:test.c
	arm-linux-gcc test.c -fpic -shared -o test.so  -I ../../libs/include/

clean:
	rm *.o *.so -rf

