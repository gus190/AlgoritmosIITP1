#ifndef _SENSOR_H_INCLUDED_
#define _SENSOR_H_INCLUDED_

#include <cstdlib>
#include <iostream>
#include <array.h>
#include <data.h>

using namespace std;

class Sensor {
	Array<Sensor> data_;
public:
	SensorNet();
	~SensorNet();
	
	void parse(istream&);
	void clear();
	size_t size();
	
	friend std::ostream& operator<<(std::ostream&,const Sensor&);
	friend std::istream& operator>>(std::istream&,Sensor&);
};

#endif
