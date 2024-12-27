all: libshared libstatic
	gcc -o main main.c -lcurl -L. -lcfetch

libshared:
	gcc -fPIC -shared -o libcfetch.so cfetch.c -lcurl

libstatic:
	gcc -c cfetch.c
	ar rcs libcfetch.a cfetch.o

clean:
	rm -f main

