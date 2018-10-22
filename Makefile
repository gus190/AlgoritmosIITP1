MCXXARGS  = -g -Wall
CXXFLAGS = -I. $(CXXARGS)
LDFLAGS  =
CXX      = c++

all: cleanall obj gens tests main
	@/bin/true

clean: cleanall
	@/bin/true
#main
main: Range.o Package.o SegmentTree.o Sensor.o SensorNet.o Query.o Cmdline.o  main.o
	$(CXX) $(LDFLAGS) -o exec/tp1 obj/main.o obj/Cmdline.o obj/SensorNet.o obj/Sensor.o obj/Range.o obj/SegmentTree.o obj/Package.o

main.o: main.h classes/Array.h classes/Cmdline.h classes/Sensor.h classes/Package.h classes/SensorNet.h classes/SegmentTree.h classes/Range.h
	$(CXX) $(CXXFLAGS) -o obj/main.o -c main.cc

#class objects	
obj: Range.o Package.o SegmentTree.o Cmdline.o Sensor.o SensorNet.o

Range.o: classes/Range.cc classes/Range.h
	$(CXX) $(CXXFLAGS) -o obj/Range.o -c classes/Range.cc

Package.o: classes/Package.cc classes/Package.h
	$(CXX) $(CXXFLAGS) -o obj/Package.o -c classes/Package.cc
	
SegmentTree.o: classes/SegmentTree.cc classes/SegmentTree.h
	$(CXX) $(CXXFLAGS) -o obj/SegmentTree.o -c classes/SegmentTree.cc

Cmdline.o: classes/Cmdline.cc classes/Cmdline.h
	$(CXX) $(CXXFLAGS) -o obj/Cmdline.o -c classes/Cmdline.cc	

Sensor.o: classes/Sensor.cc classes/Sensor.h
	$(CXX) $(CXXFLAGS) -o obj/Sensor.o -c classes/Sensor.cc
	
SensorNet.o: classes/SensorNet.cc classes/SensorNet.h
	$(CXX) $(CXXFLAGS) -o obj/SensorNet.o -c classes/SensorNet.cc
	
Query.o: classes/Query.cc classes/Query.h
	$(CXX) $(CXXFLAGS) -o obj/Query.o -c classes/Query.cc
	
#test objects generators
tests: test-st test-pkg test-range

test-st: test-st.o SegmentTree.o Package.o Range.o
	$(CXX) $(LDFLAGS) -o exec/test-st obj/test-st.o obj/SegmentTree.o obj/Package.o obj/Range.o
	
test-st.o: tests/test-st.cc
	$(CXX) $(CXXFLAGS) -o obj/test-st.o -c tests/test-st.cc
	
test-pkg: test-pkg.o Package.o Range.o
	$(CXX) $(LDFLAGS) -o exec/test-pkg obj/test-pkg.o obj/Package.o obj/Range.o
	
test-pkg.o: tests/test-pkg.cc
	$(CXX) $(CXXFLAGS) -o obj/test-pkg.o -c tests/test-pkg.cc

test-range: test-range.o Range.o
	$(CXX) $(LDFLAGS) -o exec/test-range obj/test-range.o obj/Range.o
	
test-range.o: tests/test-range.cc
	$(CXX) $(CXXFLAGS) -o obj/test-range.o -c tests/test-range.cc

#file generators
gens: gen-query gen-data

gen-query: gen-query.o Cmdline.o
	$(CXX) $(LDFLAGS) -o exec/gen-query obj/gen-query.o obj/Cmdline.o

gen-query.o: gens/gen-query.h classes/Cmdline.h
	$(CXX) $(CXXFLAGS) -o obj/gen-query.o -c gens/gen-query.cc

gen-data: gen-data.o Cmdline.o
	$(CXX) $(LDFLAGS) -o exec/gen-data obj/gen-data.o obj/cmdline.o

gen-data.o: gens/gen-data.h classes/Cmdline.h
	$(CXX) $(CXXFLAGS) -o obj/gen-data.o -c gens/gen-data.cc
	
#clean
cleanall:
	rm -f obj/*.o exec/*
cleanobj:
	rm -f obj/*.o
