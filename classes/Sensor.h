#ifndef _SENSOR_H_INCLUDED_
#define _SENSOR_H_INCLUDED_

#include <cstdlib>
#include <iostream>
#include <classes/SegmentTree.h>

using namespace std;

class Sensor {
	string name_;
	SegmentTree data_;
	Array<Package> aux;
	
public:
	// Constructors / Destructor
	Sensor(); // Empty
	Sensor(const string&); // Name
	Sensor(const Sensor&); // Copy
	~Sensor(); // Destructor
	
	// Setters
	void name(const string&); 
	
	// Getters
	string name()const;
	size_t size()const;
	
	// Metods
	void clear();
	void buildTree(); // Build the parents
	Package query(const size_t&,const Range&); // Query from range of index
	void printTree(); //Print the tree
	
	// Native operations
	Sensor& operator=(const string&);
	Sensor& operator=(const Sensor&);
	bool operator==(const string&);
	Sensor& operator+(const Package&);
	Package& operator[](const size_t&);

	friend std::ostream& operator<<(std::ostream&,Sensor&);
	friend std::istream& operator>>(std::istream&,Sensor&);
};

#endif
