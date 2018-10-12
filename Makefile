MCXXARGS  = -g -Wall
CXXFLAGS = -I. $(CXXARGS)
LDFLAGS  =
CXX      = c++

all: clean datagen querygen main 
	@/bin/true

main: main.o sensor.o cmdline.o data.o
	$(CXX) $(LDFLAGS) -o tp0 sensor.o main.o cmdline.o data.o

main.o: main.h array.h cmdline.h sensor.h data.h
	$(CXX) $(CXXFLAGS) -c main.cc

package.o: package.cc package.h
	$(CXX) $(CXXFLAGS) -c package.cc
	
range.o: range.cc range.h
	$(CXX) $(CXXFLAGS) -c range.cc
	
datagen: datagen.o cmdline.o
	$(CXX) $(LDFLAGS) -o datagen datagen.o cmdline.o

datagen.o: datagen.h cmdline.h
	$(CXX) $(CXXFLAGS) -c datagen.cc
	
querygen: querygen.o cmdline.o
	$(CXX) $(LDFLAGS) -o querygen querygen.o cmdline.o

querygen.o: querygen.h cmdline.h
	$(CXX) $(CXXFLAGS) -c querygen.cc
	
clean:
	rm -f *.o *.t datagen querygen tp0
