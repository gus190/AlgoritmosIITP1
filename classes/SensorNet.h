#ifndef _SENSORNET_H_INCLUDED_
#define _SENSORNET_H_INCLUDED_

#include <cstdlib>
#include <iostream>
#include <classes/Array.h>
#include <classes/Sensor.h>

using namespace std;

class SensorNet{

	Array<Sensor> sensors_;
	Sensor sAvg_;
public:
	// Constructors / Destructor
	SensorNet();
	~SensorNet();
	
	// Setters
	
	// Getters
	size_t size();
	
	// Metods
	void clear();
	void createSAvg();
	size_t search(const string&);
	Sensor& sensorAvg();
	// Native operators
	SensorNet& operator=(const SensorNet&);
	SensorNet& operator+(const Sensor&);
	Sensor& operator[](const size_t&);
	
	// Stream operators
	friend std::ostream& operator<<(std::ostream&,const SensorNet&);
	friend std::istream& operator>>(std::istream&,SensorNet&); // parse file
};

#endif
