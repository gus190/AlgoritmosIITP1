#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
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
size_t SensorNet::search(const string& name){
	if(sensors_.size()==0)
		return -1;
	for(size_t i=0;i<sensors_.size();++i){
		if((*this)[i] == name)
			return i;
	}
	return -1;
}
void SensorNet::createSAvg(){
	sAvg_.clear();
	if(sensors_[0].size() == 0){
		return;
	}
	for (size_t i = 0; i < sensors_[0].size(); i++){ // for each sample time
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
		sAvg_ + aux;
	}
	sAvg_.buildTree();
}
Sensor& SensorNet::sensorAvg(){
	return sAvg_;
}
//-- Native operators -- 
SensorNet& SensorNet::operator+(const Sensor& s){
	sensors_.push_back(s);
}
SensorNet& SensorNet::operator=(const SensorNet& s){
	sensors_ = s.sensors_;
	sAvg_ = s.sAvg_;
}
Sensor& SensorNet::operator[](const size_t& pos){
	return sensors_[pos];
}
//-- Stream operators --
std::ostream& operator<<(std::ostream& os,SensorNet& sn){
	for(size_t i = 0; i < sn.sensors_.size();i++){
		os << sn.sensors_[i];
	}
	return os;
}
std::istream& operator>>(std::istream& is,SensorNet& sn){
	// parse input
	// variables utilizadas
	string line,token;
	istringstream lineStr;
	Sensor sensorAux;
	Package pkg;
	// parseo de la primera linea (nombres)

	getline(is,line);						//get line
	lineStr.str(line);						// stream it
	while(getline(lineStr,token,',')){		// get comma separated values
		sensorAux = token;					// set name to aux sensor
		sn.sensors_.push_back(sensorAux);		// push to array
	}
	
	// parse data
	size_t sampleCount = 0;		// set sample count to 0
	while(getline(is,line)){	// while lines
		size_t sensorCount = 0; // set sensor count to 0
		lineStr.clear();
		lineStr.str(line);
		while(getline(lineStr,token,',')){	//while comma separated values
			stringstream tokenStr;
			tokenStr.str(token);
			double num;
			pkg.clear();
			if (token.empty()){	 // if no data
				pkg.range(sampleCount,sampleCount+1);		// only set range
			}else if(tokenStr >> num){ // if good number
				pkg.set(sampleCount,sampleCount+1,atof(token.c_str()));	// set range and value
			}else{ //if no number (bad character)
				pkg.range(sampleCount,sampleCount+1);		// only set range
			}
			sn.sensors_[sensorCount] + pkg;
			sensorCount++;
		}
		if(sensorCount == sn.size()-1){ // case string end with comma 
			pkg.clear();			// clear pkg
			pkg.range(sampleCount,sampleCount+1);		// only set range
			sn.sensors_[sensorCount] + pkg;
		}
	sampleCount++;
	}
	
	for(size_t i = 0; i < sn.size();i++){
		sn[i].buildTree();
	}
	sn.createSAvg();
	return is;
	
}

