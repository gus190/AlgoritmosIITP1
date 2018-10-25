#include <iostream>
#include <cstdlib>
#include <classes/Package.h>

// They can be as big as we want to
#define INFPOS 1000000
#define INFNEG -1000000

//-- Constructors / Destructor --
Package::Package():rg_(){ 
	// Empty
	exist_ = false;
	max_ = INFNEG;
	min_ = INFPOS;
	avg_ = 0;
	count_ = 0;
}
Package::Package(const Package& pkg){ 
	// Copy
	exist_ = pkg.exist_;
	max_ = pkg.max_;
	min_ = pkg.min_;
	avg_ = pkg.avg_;
	count_ = pkg.count_;
	rg_ =  pkg.rg_;
}
Package::Package(const double &max, const double &min ,const double &avg,const size_t &count, const Range &rg) 
				:rg_(rg){
	// Complete
	exist_ = true;
	max_ = max;
	min_ = min;
	avg_ = avg;
	count_ = count;
	if(count == 0){
		exist_ = false;
	}
}
Package::Package(const double &data,const Range &rg):rg_(rg){ 
	// Leafs
	exist_ = true;
	max_ = data;
	min_ = data;
	avg_ = data;
	count_ = 1;
}
Package::Package(const Package &pkg1,const Package &pkg2){ 
	// Parents (merge 2 pkg)
	*this = pkg1;
	*this + pkg2;
}
Package::~Package(){
	// Destructor
}
//-- Getters --
double Package::min()const{
	return min_;
}
double Package::max()const{
	return max_;
}
double Package::avg()const{
	return avg_;
}
Range Package::range()const{
	return rg_;
}
size_t Package::count()const{
	return count_;
}
bool Package::exist()const{
	return exist_;
}
//-- Setters --
void Package::min(const double& data){
	min_ = data;
}
void Package::max(const double& data){
	max_ = data;
}
void Package::avg(const double& data){
	avg_ = data;
}
void Package::range(const Range& data){
	rg_ = data;
}
void Package::range(const size_t& minrg,const size_t& maxrg){
	rg_.range(minrg,maxrg);
}
void Package::count(const size_t& data){
	count_ = data;
}
void Package::exist(const bool& data){
	exist_ = data;
}
void Package::set(const Range& rg,const double& data){ 
	// Range and data with count 1;
	rg_ = rg;
	min_ = data;
	max_ = data;
	avg_ = data;
	count_ = 1;
	exist_ = true;
}
void Package::set(const size_t& minrg,const size_t& maxrg,const double& data){ 
	// Range and data with count 1;
	rg_.range(minrg,maxrg);
	min_ = data;
	max_ = data;
	avg_ = data;
	count_ = 1;
	exist_ = true;
}
//-- Metods --
void Package::clear(){
	//Clear package
	rg_.clear();
	min_=INFPOS;
	max_=INFNEG;
	exist_=false;
	avg_=0;
	count_=0;
}
void Package::printStd(ostream& os){
	// Print the standar way
	if(count_ == 0){
		os << "NO DATA";
	}else{
		os << avg_ << ',' << min_ << ',' << max_ << ',' << count_;
	}
	os << endl;
}

//-- Native operators --
Package& Package::operator+(const Package& pkg){
	// Union of two packages
	// Exist
	exist_ = exist_ || pkg.exist_;
	// Min
	if(min_ > pkg.min_ && pkg.exist_ == true){ // If min is in pkg and exist
		min_ = pkg.min_;
	}
	// Max
	if(max_ < pkg.max_ && pkg.exist_ == true){ //If min is in pkg and exist
		max_ = pkg.max_;
	}
	// Avg
	if(exist_ == true){ // Si exist, average
		avg_=(avg_*count_ + pkg.avg_*pkg.count_)/(count_+pkg.count_);
	}
	// Range
	rg_ + pkg.rg_; // Union
	//count
	count_+=pkg.count_;
}
Package& Package::operator=(const Package& pkg){
	// Assignation
	exist_ = pkg.exist_;
	max_ = pkg.max_;
	min_ = pkg.min_;
	avg_ = pkg.avg_;
	count_ = pkg.count_;
	rg_ =  pkg.rg_;
	return *this;
}

//-- Stream operators -- 
std::ostream& operator<<(std::ostream& os,const Package& pkg){
	// Print Package
	os << '{' << pkg.rg_ << ',';
	if(!pkg.exist_){
	os << "noExist"  << '}';
	}else{
		os << pkg.avg_ << ','; 
		os << pkg.min_ << ',';
		os << pkg.max_ << ',';
		os << pkg.count_ << ',';
		if(pkg.exist_){
			os << "true";
		}else{
			os << "false";
		}
		os<<'}';
	}
	return os;
}
