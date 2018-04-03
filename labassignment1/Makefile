SRC_S=main.C image.C sink.C source.C PNMreader.C PNMwriter.C filters_s.C
SRC_P=main.C image.C sink.C source.C PNMreader.C PNMwriter.C filters_p.C filters_ph.ispc
OBJ_S=$(SRC_S:.C=.o)
OBJ_P=main.o image.o sink.o source.o PNMreader.o PNMwriter.o filters_p.o filters_ph.o
ISPC=ispc
ISPCFLAGS=-O2 --arch=x86-64 --target=sse2

default: serial_invert parallel_invert

serial_invert: $(OBJ_S)
	g++ $(OBJ_S) -o serial_invert 

.C.o: $<
	g++ -g -I. -c $<

filters_ph_ispc.h filters_ph.o: filters_ph.ispc 
	$(ISPC) $(ISPCFLAGS) $< -o filters_ph.o -h filters_ph_ispc.h

parallel_invert: $(OBJ_P) filters_ph_ispc.h
	g++ $(OBJ_P) -o parallel_invert 

clean:
	rm *.o serial_invert parallel_invert
