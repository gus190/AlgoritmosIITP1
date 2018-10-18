#include <iostream>
#include <cstdlib>
//#include <cmath>
//#include <cstring>
#include <sensor.h>
#include <data.h>

#define DBL_MIN -1000000.0
#define DBL_MAX 1000000.0
//constructores
Sensor::Sensor(){
	ID = "Sensor";
}
Sensor::Sensor(const string& name){
	ID = name;
}
Sensor::Sensor(const Sensor& s){
	ID = s.getID();
	data = s.data;
}
//destructor
Sensor::~Sensor(){
}

//obtener un valor de dataeratura
Data Sensor::getData(int pos){
	return data[pos];
}
//obtener el nombre
const string& Sensor::getID()const{
	return ID;
}

size_t Sensor::size()const{
	return data.size();
}

void Sensor::clear(){
	data.clear();
	ID.clear();
}

void Sensor::querry(ostream& output,size_t minRange,size_t maxRange){
	double avg = 0,min = 0,max = 0;
	int count = 0;
	bool hasData = false;
	if(minRange > maxRange){
		output << "BAD QUERRY" << endl;
		return;
	}
	if(minRange > data.size()){
		output << "NO DATA" << endl;
		return;
	}
	if(maxRange > data.size()-1){
		maxRange = data.size();
	}
	min = DBL_MAX;
	max = DBL_MIN;
	for(size_t i = minRange; i<=maxRange-1;i++){
		if(data[i].exist()){
			hasData = true;
			if(data[i].getData() < min){
				min = data[i].getData();
			}
			if(data[i].getData() > max){
				max = data[i].getData();
			}
			avg+=data[i].getData();
			count++;
		}
	}
	if(!hasData){
		output << "NO DATA" << endl;
		return;
	}
	avg = avg/count;
	output << avg << ',' << min << ',' << max << ',' << count << endl;
}

std::ostream& operator<<(std::ostream& os,const Sensor& sensor){

	os << "Sensor ID: " << sensor.getID() << endl;
	os << "Dato:" << endl;
	os << sensor.data << endl;
	os << "Cantidad de datos: " << sensor.size() << endl;
	return os;
}

Sensor& Sensor::operator+(const Data& value){
	data.push_back(value);
	return *this;
}
Sensor& Sensor::operator+(const double& value){
	Data d;
	d = value;
	data.push_back(d);
	return *this;
}
Sensor& Sensor::operator+(const Sensor& s){
	data.push_back(s.data);
	return *this;
}

Sensor& Sensor::operator=(const string& name){
	ID = name;
	return *this;
}

Sensor& Sensor::operator=(const Sensor& s){
	ID = s.ID;
	data = s.data;
	return *this;
}

bool Sensor :: operator==(const Sensor& s){
	return s.ID==ID;
}

std::istream & operator >> (std::istream& is,Sensor& sensor){
	cout << " istream no implementado";
	return is;
}