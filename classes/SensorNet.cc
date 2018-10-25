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
	//linear search
	if(sensors_.size()==0)
		return -1;
	for(size_t i=0;i<sensors_.size();++i){
		if((*this)[i] == name)
			return i;
	}
	return -1;
}
void SensorNet::createSAvg(){
	// Average sensor
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
	//returns sensor average;
	return sAvg_;
}
//-- Native operators -- 
SensorNet& SensorNet::operator+(const Sensor& s){
	// Sum used as push_back 
	sensors_.push_back(s);
}
SensorNet& SensorNet::operator=(const SensorNet& s){
	// Assignation
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
	// Input parse
	// variables
	string line,token;
	istringstream lineStr;
	Sensor sensorAux;
	Package pkg;
	
	// First line (names)
	getline(is,line);					// Get line
	lineStr.str(line);					// Stream it
	while(getline(lineStr,token,',')){	// While comma separated values
		sensorAux = token;					// Set name to aux sensor
		sn + sensorAux;						// Push sensor to sensorNetwork array
	}
	
	// parse data
	size_t sampleCount = 0;		// Set sample count to 0
	while(getline(is,line)){	// While lines
		size_t sensorCount = 0; // Set sensor count to 0
		lineStr.clear();
		lineStr.str(line);
		while(getline(lineStr,token,',')){	// While comma separated values
			stringstream tokenStr;
			tokenStr.str(token);
			double num;
			pkg.clear();
			if (token.empty()){	 // If no data
				pkg.range(sampleCount,sampleCount+1);		// Only set range
			}else if(tokenStr >> num){ // If good number
				pkg.set(sampleCount,sampleCount+1,num);	// Set range and value
			}else{ // If no number (bad character)
				pkg.range(sampleCount,sampleCount+1);		// Only set range
			}
			sn.sensors_[sensorCount] + pkg;
			sensorCount++;
		}
		if(sensorCount == sn.size()-1){ // Case string end with comma (leaves while early if ends in ,\0\n
			pkg.clear();			// clear pkg
			pkg.range(sampleCount,sampleCount+1);		// only set range
			sn.sensors_[sensorCount] + pkg;
		}
	sampleCount++;
	}
	
	for(size_t i = 0; i < sn.size();i++){ // Build all the trees in network
		sn[i].buildTree();
	}
	sn.createSAvg(); // Create average sensor
	return is;
	
}

