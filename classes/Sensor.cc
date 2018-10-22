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
void Sensor::buildST(){
	// Build st from array
	data_.build();
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
	data_ + sample;
}
Package& Sensor::operator[](const size_t& i){
	return data_.leaf(i);
}
void Sensor::printTree(){
	cout << data_;
}

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