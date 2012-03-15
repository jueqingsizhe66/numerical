main : main.o mglin.o addint.o relax.o resid.o rstrc.o interp.o nrutil.o slvsml.o
	gcc -Wall -std=c99 -O3 -o main main.o mglin.o addint.o relax.o resid.o rstrc.o interp.o nrutil.o slvsml.o
main.o : main.c nrutil.h
	gcc -Wall -std=c99 -c -I. main.c
mglin.o : mglin.c nrutil.h mg.h
	gcc -Wall -std=c99 -c -I. mglin.c
addint.o : addint.c
	gcc -Wall -std=c99 -c addint.c
relax.o : relax.c
	gcc -Wall -std=c99 -O3 -c relax.c
resid.o : resid.c
	gcc -Wall -std=c99 -c resid.c
rstrc.o : rstrc.c
	gcc -Wall -std=c99 -c rstrc.c
interp.o : interp.c
	gcc -Wall -std=c99 -c interp.c
slvsml.o : slvsml.c
	gcc -Wall -std=c99 -c slvsml.c
nrutil.o : nrutil.c
	gcc -Wall -std=c99 -c -I. nrutil.c
clean:
	rm -f  *.o main *~
