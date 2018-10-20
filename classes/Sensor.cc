#include <iostream>
#include <cstdlib>
#include <classes/Sensor.h>

//-- Constructors / Destructor -- 
Sensor::Sensor(){
	//Empty
	name_ = " ";
}
Sensor::Sensor(const string& name){
	// From name
	name_ = name;
}
Sensor::Sensor(const string& name, const Array<Package>& arr):data_(arr){
	// From name and array
	name_ = name;
}
Sensor::Sensor(const Sensor& s){
	// Copy
	name_ = s.name_;
	data_ = s.data_;
}
Sensor::~Sensor(){
	// Destructor
}

//-- Setters -- 
void Sensor::name(const string& name){
	name_ = name;
} 

//-- Getters -- 
string  Sensor::name()const{
	return name_;
}
size_t  Sensor::size()const{
	return data_.size();
}

//-- Metods -- 
void Sensor::clear(){
	name_ = " ";
	data_.clear();
}
void Sensor::build(const Array<Package>& arr){
	// Build st from array
	data_.build(arr);
}
void Sensor::add(const Package& sample){
	// add sample to st (has to be rebuilded later)
	data_ + sample;
}
//-- Native operations -- 
Sensor& Sensor::operator=(const string& name){
	name_ = name;
}
Sensor& Sensor::operator=(const Sensor& s){
	name_ = s.name_;
	data_ = s.data_;
}
Sensor& Sensor::operator+(const Package& sample){
	// Same as add metod;
	data_ + sample;
}
Package& Sensor::operator[](const size_t& i){
	return data_.leaf(i);
}
/* void Sensor::querry(ostream& output,size_t minRange,size_t maxRange){
	double avg = 0,min = 0,max = 0;
	int count = 0;
	bool hasPackage = false;
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
			hasPackage = true;
			if(data[i].getPackage() < min){
				min = data[i].getPackage();
			}
			if(data[i].getPackage() > max){
				max = data[i].getPackage();
			}
			avg+=data[i].getPackage();
			count++;
		}
	}
	if(!hasPackage){
		output << "NO DATA" << endl;
		return;
	}
	avg = avg/count;
	output << avg << ',' << min << ',' << max << ',' << count << endl;
} */

//-- Stream operations -- 
std::ostream& operator<<(std::ostream& os,Sensor& sensor){
	// Output stream
	os << "Sensor name: " << sensor.name() << endl;
	os << "Data:" << endl;
	sensor.data_.printLeaves(os);
	os << endl;
	os << "Samples: " << sensor.size() << endl;
	return os;
}

std::istream & operator >> (std::istream& is,Sensor& sensor){
	// Input stream
	cout << " istream no implementado";
	return is;
}