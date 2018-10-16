MCXXARGS  = -g -Wall
CXXFLAGS = -I. $(CXXARGS)
LDFLAGS  =
CXX      = c++

all: cleanall datagen querygen main cleanobj
	@/bin/true

clean: cleanall
	@/bin/true
#main
main: main.o sensor.o cmdline.o data.o
	$(CXX) $(LDFLAGS) -o tp0 sensor.o main.o cmdline.o data.o

main.o: main.h array.h cmdline.h sensor.h data.h
	$(CXX) $(CXXFLAGS) -c main.cc

#class objects	
Range.o: Range.cc Range.h
	$(CXX) $(CXXFLAGS) -c Range.cc

Package.o: Package.cc Package.h
	$(CXX) $(CXXFLAGS) -c Package.cc
	
SegmentTree.o: SegmentTree.cc SegmentTree.h
	$(CXX) $(CXXFLAGS) -c SegmentTree.cc
	
#test objects generators
test-st: test-st.o SegmentTree.o Package.o Range.o
	$(CXX) $(LDFLAGS) -o test-st test-st.o SegmentTree.o Package.o Range.o
	
test-st.o: test-st.cc
	$(CXX) $(CXXFLAGS) -c test-st.cc
	
test-pkg: test-pkg.o Package.o Range.o
	$(CXX) $(LDFLAGS) -o test-pkg test-pkg.o Package.o Range.o
	
test-pkg.o: test-pkg.cc
	$(CXX) $(CXXFLAGS) -c test-pkg.cc

test-range: test-range.o Range.o
	$(CXX) $(LDFLAGS) -o test-range test-range.o Range.o
	
test-range.o: test-range.cc
	$(CXX) $(CXXFLAGS) -c test-range.cc

#file generators
querygen: querygen.o cmdline.o
	$(CXX) $(LDFLAGS) -o querygen querygen.o cmdline.o

querygen.o: querygen.h cmdline.h
	$(CXX) $(CXXFLAGS) -c querygen.cc

datagen: datagen.o cmdline.o
	$(CXX) $(LDFLAGS) -o datagen datagen.o cmdline.o

datagen.o: datagen.h cmdline.h
	$(CXX) $(CXXFLAGS) -c datagen.cc
	
#clean
cleanall:
	rm -f *.o *.t datagen querygen tp0 test-range test-pkg test-st
cleanobj:
	rm -f *.o *.t
