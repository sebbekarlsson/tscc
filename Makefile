flags = -Wall -fPIC -g
exec = tscc.out
objects = $(wildcard src/*.c)


$(exec): $(objects)
	gcc $(objects) $(flags) -o $(exec)

%.o: %.c include/%.h
	gcc -c $(flags) $< -o $@

clean:
	-rm *.out
	-rm *.o
	-rm src/*.o
