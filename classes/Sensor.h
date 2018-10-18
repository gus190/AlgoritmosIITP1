#ifndef _SENSOR_H_INCLUDED_
#define _SENSOR_H_INCLUDED_

#include <cstdlib>
#include <iostream>
#include <classes/SegmentTree.h>

using namespace std;

class Sensor {
	string name_;
	SegmentTree data_;
public:
	// Constructors / Destructor
	Sensor();
	Sensor(const string&);
	Sensor(const Sensor&);
	~Sensor();
	
	// Setters
	void name(const string&);
	
	// Getters
	string name()const;
	size_t size()const;
	Package data(const size_t&);
	
	// Metods
	void clear();
	Package query(const Range&);
	
	// Native operations
	Sensor& operator=(const string&);

	friend std::ostream& operator<<(std::ostream&,const Sensor&);
	friend std::istream& operator>>(std::istream&,Sensor&);
};

#endif
