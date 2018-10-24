MCXXARGS  = -g -Wall
CXXFLAGS = -I. $(CXXARGS)
LDFLAGS  =
CXX      = c++

all: clean main gens tests 
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
tests: test-rg test-pkg test-st

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

#file generators
gens: gen-query gen-data

gen-query: gen-query.o Cmdline.o
	@echo Compiling data generators ...
	@$(CXX) $(LDFLAGS) -o exec/gen-query obj/gen-query.o obj/Cmdline.o

gen-query.o: gens/gen-query.h classes/Cmdline.h
	@$(CXX) $(CXXFLAGS) -o obj/gen-query.o -c gens/gen-query.cc

gen-data: gen-data.o Cmdline.o
	@$(CXX) $(LDFLAGS) -o exec/gen-data obj/gen-data.o obj/cmdline.o

gen-data.o: gens/gen-data.h classes/Cmdline.h
	@$(CXX) $(CXXFLAGS) -o obj/gen-data.o -c gens/gen-data.cc
	
#clean
clean:
	@echo Cleaning files ...
	@rm -f obj/*.o exec/*

test-classes: 
	@echo Testing classes ...
	./exec/test-rg <files/tests/test-rg.in  >files/tests/test-rg.out
	diff -b files/tests/test-rg.out files/tests/test-rg.ref
	
	./exec/test-pkg <files/tests/test-pkg.in  >files/tests/test-pkg.out
	diff -b files/tests/test-pkg.out files/tests/test-pkg.ref
	
	./exec/test-st <files/tests/test-st.in  >files/tests/test-st.out
	diff -b files/tests/test-st.out files/tests/test-st.ref
	
	@echo Classes testing done.

test-valgrind:
	@echo testing valgrind ... 
	valgrind --leak-check=full ./exec/tp1 -i files/queryCatedra.csv -d files/dataCatedra.csv -o ../dev/null
	@echo valgrind test done.

files:
	@echo Processing all files
