#include <iostream>
#include <cstdlib>
#include <classes/SensorNet.h>
//-- Constructors / Destructor -- 
SensorNet::SensorNet(){
	
}
SensorNet::~SensorNet(){
	
}

//-- Setters --

//-- Getters --
size_t SensorNet::size(){
	return sensors_.size();
}
//-- Metods --
void SensorNet::clear(){
	sensors_.clear();
	sAvg_.clear();
}

void SensorNet::createSAvg(){
	sAvg_.clear();
	for (size_t i = 0; i < sensors_[0].size(); i++){ // for each sameple time
		double value = 0;
		int count = 0;
		for(size_t j=0;j<sensors_.size();j++){ // for each sensor
			if(sensors_[j][i].exist()){	// if sample exist
				value = value + sensors_[j][i].avg(); // add to value
				count++;	//increment count;
			}
		}
			Package aux;
			if(count == 0){			// if none exist
				aux.range(i,i+1);	// set range
				aux.exist(false);	//dont exist
			}else{
				value = value/count;  //get the avg of sum of values
				aux.set(i,i+1,value); // set range and value
			}
			sAvg_.add(aux);
	}
}

//-- Native operators -- 
SensorNet& SensorNet::operator+(const Sensor& s){
	sensors_.push_back(s);
}
SensorNet& SensorNet::operator=(const SensorNet& s){
	sensors_ = s.sensors_;
	sAvg_ = s.sAvg_;
}

//-- Stream operators --
std::ostream& operator<<(std::ostream& os,const SensorNet& sn){
	return os;
}
std::istream& operator>>(std::istream& is,SensorNet& sn){
	// parse input
	
	sn.createSAvg();
	return is;
}

