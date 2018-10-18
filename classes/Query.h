#ifndef _SENSOR_H_INCLUDED_
#define _SENSOR_H_INCLUDED_

#include <cstdlib>
#include <iostream>
#include <array.h>
#include <data.h>

using namespace std;

class Sensor {
	string ID;
	Array<Data> data;
public:
	Sensor();
	Sensor(const string&);
	Sensor(const Sensor&);
	~Sensor();
	
	Data getData(int);
	size_t size() const;
	const string& getID()const;
	void clear();
	void querry(ostream&,size_t,size_t);
	
	Sensor& operator+(const double&);
	Sensor& operator+(const Data&);
	Sensor& operator+(const Sensor&);
	Sensor& operator=(const string&);
	Sensor& operator=(const Sensor&);
	bool operator==(const Sensor&);
	
	friend std::ostream& operator<<(std::ostream&,const Sensor&);
	friend std::istream& operator>>(std::istream&,Sensor&);
};

#endif
