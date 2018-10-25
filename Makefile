MCXXARGS  = -g -Wall
CXXFLAGS = -I. $(CXXARGS)
LDFLAGS  =
CXX      = c++

all: clean main gens tests test-classes test-valgrind test-files
#test-classes test-valgrind test-data

#main
main: obj main.o
	@$(CXX) $(LDFLAGS) -o exec/tp1 obj/main.o obj/Cmdline.o obj/SensorNet.o obj/Sensor.o obj/Range.o obj/SegmentTree.o obj/Package.o obj/Query.o

main.o: main.h classes/Array.h classes/Cmdline.h classes/Sensor.h classes/Package.h classes/SensorNet.h classes/SegmentTree.h classes/Range.h
	@$(CXX) $(CXXFLAGS) -o obj/main.o -c main.cc

#class objects	
obj: Range.o Package.o SegmentTree.o Cmdline.o Sensor.o SensorNet.o Query.o

Range.o: classes/Range.cc classes/Range.h
	@echo Compiling classes ... 
	@$(CXX) $(CXXFLAGS) -o obj/Range.o -c classes/Range.cc

Package.o: classes/Package.cc classes/Package.h
	@$(CXX) $(CXXFLAGS) -o obj/Package.o -c classes/Package.cc
	
SegmentTree.o: classes/SegmentTree.cc classes/SegmentTree.h
	@$(CXX) $(CXXFLAGS) -o obj/SegmentTree.o -c classes/SegmentTree.cc

Cmdline.o: classes/Cmdline.cc classes/Cmdline.h
	@$(CXX) $(CXXFLAGS) -o obj/Cmdline.o -c classes/Cmdline.cc	

Sensor.o: classes/Sensor.cc classes/Sensor.h
	@$(CXX) $(CXXFLAGS) -o obj/Sensor.o -c classes/Sensor.cc
	
SensorNet.o: classes/SensorNet.cc classes/SensorNet.h
	@$(CXX) $(CXXFLAGS) -o obj/SensorNet.o -c classes/SensorNet.cc
	
Query.o: classes/Query.cc classes/Query.h
	@$(CXX) $(CXXFLAGS) -o obj/Query.o -c classes/Query.cc
	
#test objects generators
tests: test-rg test-pkg test-st test-sensor

test-st: test-st.o SegmentTree.o Package.o Range.o
	@$(CXX) $(LDFLAGS) -o exec/test-st obj/test-st.o obj/SegmentTree.o obj/Package.o obj/Range.o
	
test-st.o: tests/test-st.cc
	@$(CXX) $(CXXFLAGS) -o obj/test-st.o -c tests/test-st.cc
	
test-pkg: test-pkg.o Package.o Range.o
	@$(CXX) $(LDFLAGS) -o exec/test-pkg obj/test-pkg.o obj/Package.o obj/Range.o
	
test-pkg.o: tests/test-pkg.cc
	@$(CXX) $(CXXFLAGS) -o obj/test-pkg.o -c tests/test-pkg.cc

test-rg: test-rg.o Range.o
	@$(CXX) $(LDFLAGS) -o exec/test-rg obj/test-rg.o obj/Range.o
	
test-rg.o: tests/test-rg.cc
	@echo Compiling class tests programs ...
	@$(CXX) $(CXXFLAGS) -o obj/test-rg.o -c tests/test-rg.cc

test-sensor: test-sensor.o Sensor.o SegmentTree.o Package.o Range.o
	@$(CXX) $(LDFLAGS) -o exec/test-sensor obj/test-sensor.o obj/Sensor.o obj/SegmentTree.o obj/Package.o obj/Range.o
	
test-sensor.o: tests/test-sensor.cc
	@$(CXX) $(CXXFLAGS) -o obj/test-sensor.o -c tests/test-sensor.cc


#file generators
gens: gen-query gen-data

gen-query: gen-query.o Cmdline.o
	@echo Compiling data generators ...
	@$(CXX) $(LDFLAGS) -o exec/gen-query obj/gen-query.o obj/Cmdline.o

gen-query.o: gens/gen-query.h classes/Cmdline.h
	@$(CXX) $(CXXFLAGS) -o obj/gen-query.o -c gens/gen-query.cc

gen-data: gen-data.o Cmdline.o
	@$(CXX) $(LDFLAGS) -o exec/gen-data obj/gen-data.o obj/Cmdline.o

gen-data.o: gens/gen-data.h classes/Cmdline.h
	@$(CXX) $(CXXFLAGS) -o obj/gen-data.o -c gens/gen-data.cc
	
#clean
clean:
	@echo Cleaning files ...
	@rm -f obj/*.o exec/*

test-classes: 
	@echo Testing classes ...
	
	@./exec/test-rg <files/testclasses/test-rg.in  >files/testclasses/test-rg.out
	@diff -b files/testclasses/test-rg.out files/testclasses/test-rg.ref
	
	@./exec/test-pkg <files/testclasses/test-pkg.in  >files/testclasses/test-pkg.out
	@diff -b files/testclasses/test-pkg.out files/testclasses/test-pkg.ref
	
	@./exec/test-st <files/testclasses/test-st.in  >files/testclasses/test-st.out
	@diff -b files/testclasses/test-st.out files/testclasses/test-st.ref
	
	@./exec/test-sensor <files/testclasses/test-sensor.in  >files/testclasses/test-sensor.out
	@diff -b files/testclasses/test-sensor.out files/testclasses/test-sensor.ref
	
	@echo Classes testing done.

test-valgrind:
	@echo testing valgrind ... 
	@valgrind --leak-check=full --log-file="files/valgrind.log" ./exec/tp1 -i files/testcases/practice.query -d files/testcases/practice.data -o files/testcases/practice.out
	@echo valgrind test done in files/valgrind.log.

test-files: main
	@echo Testing data cases ...
	@echo Testing practice data...
	@./exec/tp1 -d files/testcases/practice.data -i files/testcases/practice.query -o files/testcases/practice.out
	@diff -b files/testcases/practice.ref files/testcases/practice.out
	@echo Done.
	
	@echo Testing justNames data...
	@./exec/tp1 -d files/testcases/justNames.data -i files/testcases/justNames.query -o files/testcases/justNames.out
	@diff -b files/testcases/justNames.ref files/testcases/justNames.out
	@echo Done.
	
	@echo Testing emptySamples data...
	@./exec/tp1 -d files/testcases/emptySamples.data -i files/testcases/emptySamples.query -o files/testcases/emptySamples.out
	@diff -b files/testcases/emptySamples.ref files/testcases/emptySamples.out
	@echo Done.
	
	@echo Testing emptyCases data...
	@./exec/tp1 -d files/testcases/emptyCases.data -i files/testcases/emptyCases.query -o files/testcases/emptyCases.out
	@diff -b files/testcases/emptyCases.ref files/testcases/emptyCases.out
	@echo Done.
	@echo All files tested.

	

