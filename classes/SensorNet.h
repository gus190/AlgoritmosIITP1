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
	SensorNet(); // Empty
	~SensorNet(); // Destructor
	
	// Setters
	
	// Getters
	size_t size();
	
	// Metods
	void clear(); // Clear
	void createSAvg(); // Create average sensor
	size_t search(const string&); // Search name in network
	Sensor& sensorAvg(); // Returns sensor average
	
	// Native operators
	SensorNet& operator=(const SensorNet&); // Assignation
	SensorNet& operator+(const Sensor&);	// Sum used as push back
	Sensor& operator[](const size_t&);	// Go to i sensor in network
	
	// Stream operators
	friend std::ostream& operator<<(std::ostream&,SensorNet&); // Sensor print
	friend std::istream& operator>>(std::istream&,SensorNet&); // Input parse
};

#endif
