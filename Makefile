A4: A4.c
	gcc -o a4 A4.c

a4: A4
	./a4

clean: # remove all machine-generated files
	rm -f a4 *.o memcheck.txt *~