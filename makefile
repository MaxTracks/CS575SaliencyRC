CC = g++
CFLAGS = -O3 -pipe -fomit-frame-pointer -funroll-all-loops -s

src: clean EasyBMP.o main.o
	g++ $(CFLAGS) EasyBMP.o main.o -o src

EasyBMP.o: ./lib/EasyBMP.cpp ./lib/EasyBMP*.h
	cp ./lib/EasyBMP*.h .
	cp ./lib/EasyBMP.cpp .
	g++ $(CFLAGS) -c EasyBMP.cpp

main.o: main.cpp
	g++ -c main.cpp

clean: 
	rm -f EasyBMP*.h
	rm -f EasyBMP.cpp
	rm -f src
	rm -f EasyBMPoutput*.bmp
	rm -f *.o
