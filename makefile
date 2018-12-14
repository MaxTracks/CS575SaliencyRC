CC = g++
CFLAGS = -O3 -pipe -fomit-frame-pointer -funroll-all-loops -s

src: clean seg.o EasyBMP.o main.o
	g++ $(CFLAGS) seg.o EasyBMP.o main.o -o src

EasyBMP.o: ./lib/EasyBMP.cpp ./lib/EasyBMP*.h
	cp ./lib/EasyBMP*.h .
	cp ./lib/EasyBMP.cpp .
	g++ $(CFLAGS) -c EasyBMP.cpp

seg.o: ./lib/seg.cpp ./lib/seg.h
	cp ./lib/seg.h .
	cp ./lib/seg.cpp .
	g++ $(CFLAGS) -c seg.cpp

main.o: main.cpp
	g++ -c main.cpp

clean: 
	rm -f seg.h
	rm -f seg.cpp
	rm -f EasyBMP*.h
	rm -f EasyBMP.cpp
	rm -f src
	rm -f EasyBMPoutput*.bmp
	rm -f *.o
