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
	$(CXX) $(LDFLAGS) -o tp0 obj/sensor.o obj/main.o obj/cmdline.o obj/data.o

main.o: main.h classes/array.h classes/Cmdline.h classes/Sensor.h classes/Package.h
	$(CXX) $(CXXFLAGS) -o obj/main.o -c main.cc

#class objects	
Range.o: classes/Range.cc classes/Range.h
	$(CXX) $(CXXFLAGS) -o obj/Range.o -c classes/Range.cc

Package.o: classes/Package.cc classes/Package.h
	$(CXX) $(CXXFLAGS) -o obj/Package.o -c classes/Package.cc
	
SegmentTree.o: classes/SegmentTree.cc classes/SegmentTree.h
	$(CXX) $(CXXFLAGS) -o obj/SegmentTree.o -c classes/SegmentTree.cc
	
#test objects generators
test-st: test-st.o SegmentTree.o Package.o Range.o
	$(CXX) $(LDFLAGS) -o exec/test-st obj/test-st.o obj/SegmentTree.o obj/Package.o obj/Range.o
	
test-st.o: tests/test-st.cc
	$(CXX) $(CXXFLAGS) -o obj/test-st.o -c tests/test-st.cc
	
test-pkg: test-pkg.o Package.o Range.o
	$(CXX) $(LDFLAGS) -o exec/test-pkg obj/test-pkg.o obj/Package.o obj/Range.o
	
test-pkg.o: tests/test-pkg.cc
	$(CXX) $(CXXFLAGS) -c tests/test-pkg.cc

test-range: test-range.o Range.o
	$(CXX) $(LDFLAGS) -o exec/test-range obj/test-range.o obj/Range.o
	
test-range.o: tests/test-range.cc
	$(CXX) $(CXXFLAGS) -o test-range.o -c tests/test-range.cc

#file generators
querygen: querygen.o cmdline.o
	$(CXX) $(LDFLAGS) -o exec/querygen obj/querygen.o obj/cmdline.o

querygen.o: gens/querygen.h obj/cmdline.h
	$(CXX) $(CXXFLAGS) -o exec/querygen.o -c gens/querygen.cc

datagen: datagen.o cmdline.o
	$(CXX) $(LDFLAGS) -o exec/datagen obj/datagen.o obj/cmdline.o

datagen.o: gens/datagen.h classes/cmdline.h
	$(CXX) $(CXXFLAGS) -o datagen.o -c classes/datagen.cc
	
#clean
cleanall:
	rm -f obj/*.o exec/*
cleanobj:
	rm -f obj/*.o
