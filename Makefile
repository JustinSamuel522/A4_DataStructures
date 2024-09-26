a4: A4
	./A4

A4: A4.c
	gcc -o A4 A4.c

clean: # remove all machine-generated files
	rm -f a4 *.o memcheck.txt *~