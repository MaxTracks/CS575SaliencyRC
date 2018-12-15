CC = g++
CFLAGS = -std=c++11 -Ilib -g
#CFLAGS = -O3 -pipe -fomit-frame-pointer -funroll-all-loops -s -std=c++11 -Ilib -g
EXEC = saliency

src: seg.o EasyBMP.o saliencyRC.o main.o
	g++ $(CFLAGS) $^ -o $(EXEC)

EasyBMP.o: EasyBMP.cpp
	g++ $(CFLAGS) -c EasyBMP.cpp

seg.o: seg.cpp
	g++ $(CFLAGS) -c seg.cpp
	
saliencyRC.o: saliencyRC.cpp
	g++ $(CFLAGS) -c saliencyRC.cpp

main.o: main.cpp
	g++ $(CFLAGS) -c main.cpp -lm

clean: 
	rm -f EasyBMPoutput*.bmp
	rm -f *.o
