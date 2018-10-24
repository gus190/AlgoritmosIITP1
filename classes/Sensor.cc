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
bool Sensor :: operator==(const string& str){
	return name_ == str;
}

Package Sensor::query(const size_t& node,const Range& rg){
	Package ans;
	if(!data_.exist()){
		ans.clear();
		return ans;
	}
	if(!data_[node].range().intersects(rg)){ // if node doesnt intersect range
		ans.clear();
		ans.range(data_[node].range());
		return ans;		// return empty package with propper range
	}else if(data_[node].range().isInside(rg)){ // if node range is inside range
		return data_[node];	//return complete node
		
	}else if(data_.haveChild(node)){	// if intersects and have children
		ans = query(data_.lChild(node),rg);	// return child1+child2
		ans + query(data_.rChild(node),rg);
		return ans;
		
	} else { // if doesnt have children, return node
		return data_[node]; 
	}
}



//-- Stream operations -- 
std::ostream& operator<<(std::ostream& os,Sensor& sensor){
	// Output stream
	os << "Sensor name: " << sensor.name() << endl;
	os << "Data:" << endl;
	//os << sensor.data_; // to print entire tree
	sensor.data_.printLeaves(os); // to print leaves
	return os;
}

std::istream & operator >> (std::istream& is,Sensor& sensor){
	// Input stream
	cout << " istream no implementado";
	return is;
}