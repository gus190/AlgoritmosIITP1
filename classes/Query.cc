#include <classes/Query.h>


using namespace std;

//-- Constructors / Destructor --
Query::Query():rg_(){ 
	name_ = " ";
}
Query::~Query(){ 
	// Destructor
}

//-- Setters --
void Query::name(const string& name){ 
	// Set Name
	name_ = name;
	return;
}
void Query::range(const Range& rg){ 
	// Set range
	rg_ = rg;
	return;
}
void Query::range(const size_t& min,const size_t& max){ 
	// Set range
	rg_.range(min,max);
	return;
}
void Query::min(const size_t& min){ 
	// Set min
	rg_.min(min);
	return;
}
void Query::max(const size_t& max){ 
	// Set max
	rg_.min(max);
	return;
}

//-- Getters --
string Query::name()const{ 
	// get name
	return name_;
}
Range Query::range()const{ 
	// Get range
	return rg_;
}
size_t Query::min()const{ 
	// Get min
	return rg_.min();
}
size_t Query::max()const{ 
	// Get max
	return rg_.max();
}

//-- Metods --
void Query::clear(){ 
	// Clear
	rg_.clear();
	name_.clear();
} 
void Query::process(std::istream& is,SensorNet& sn,std::ostream& os){
	//variables
	string line,name;
	int pos;
	size_t min,max;
	char ch;
	bool good = false;
	
	// Read line
	while(getline(is,line)){
		Package ans;
		istringstream lineStr;
		lineStr.str(line);
		
		// read name
		getline(lineStr,name,',');
		
		// read min and max range
		if(lineStr >> rg_){
			good = true;	
		}else{
			good = false;
		}
		if(good){ // if good parse, validate ranges
			if(rg_.empty()){
				os << "BAD QUERRY" << endl;
				continue;
			}
		}else{ 		// if bad parse 
			os << "BAD QUERRY" << endl;
			continue;
		}
		// if empty name
		if(name.empty()){		
			// query avg sensor;
			ans = sn.sensorAvg().query(0,rg_);
		}else{
			// search name in sensor network
			pos = sn.search(name);
			//if didnt find it 
			if(pos == -1){
				os << "UNKNOWN ID" << endl;
				continue;
			}
			// if found it, query the sensor
			ans = sn[pos].query(0,rg_);
		}
		if(!ans.exist()){
			os << "NO DATA" << endl;
		}else{
			ans.printStd(os);
		}
	}
	return;
}

//-- Native Operators --

//-- Stream operators -- 
