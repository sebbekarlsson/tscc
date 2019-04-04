flags = -Wall -fPIC -g
exec = tscc.out
sources = $(wildcard src/*.c)
objects = $(sources:.c=.o)


$(exec): $(objects)
	gcc $(objects) $(flags) -o $(exec)

%.o: %.c include/%.h
	gcc -c $(flags) $< -o $@

install:
	-rm -rf /usr/local/include/tscc
	mkdir -p /usr/local/include/tscc
	cp bootstrap/bootstrap.h /usr/local/include/tscc/.

clean:
	-rm *.out
	-rm *.o
	-rm src/*.o
