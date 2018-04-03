all:
	mpiCC -Iobjs/ -Wall -Wextra -pedantic -Wfatal-errors -std=c++11 -o  mpi mpi.C
run:
	./mpi 1
	sleep 1
	./mpi 4
	./parallel 16
	sleep 1
	./mpi 9

clean:
	rm -rf mpi
