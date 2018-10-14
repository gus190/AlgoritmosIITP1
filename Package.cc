#include <iostream>
#include <cstdlib>
#include <Package.h>
#include <Range.h>

#define INFPOS 1000000
#define INFNEG -1000000

//constructors
Package::Package():rg_(){ // empty
	exist_ = false;
	max_ = INFNEG;
	min_ = INFPOS;
	avg_ = 0;
	count_ = 0;
}
Package::Package(const Package& pkg){ // copy
	exist_ = pkg.exist_;
	max_ = pkg.max_;
	min_ = pkg.min_;
	avg_ = pkg.avg_;
	count_ = pkg.count_;
	rg_ =  pkg.rg_;
}
Package::Package(const double &max, const double &min ,const double &avg,const size_t &count, const Range &rg) // complete
				:rg_(rg){

	exist_ = true;
	max_ = max;
	min_ = min;
	avg_ = avg;
	count_ = count;
	if(count == 0){
		exist_ = false;
	}
}
Package::Package(const double &data,const Range &rg):rg_(rg){ // leafs
	exist_ = true;
	max_ = data;
	min_ = data;
	avg_ = data;
	count_ = 1;
}
Package::Package(const Package &pkg1,const Package &pkg2){ // for parent (merge 2 pkg)
	*this = pkg1;
	this->merge(pkg2);
}
Package::~Package(){
}
//getters
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
//setters
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
	rg_.setRange(minrg,maxrg);
}
void Package::count(const size_t& data){
	count_ = data;
}
void Package::exist(const bool& data){
	exist_ = data;
}
void Package::clear(){
	rg_.clear();
	min_=0;
	max_=0;
	exist_=false;
	avg_=0;
	count_=0;
}
//metods
Package& Package::merge(const Package &pkg){ //merge this with a pkg
	//exist
	exist_ = exist_ || pkg.exist_;
	//min
	if(min_ > pkg.min_ && pkg.exist_ == true){ //if min is in pkg and exist
		min_ = pkg.min_;
	}
	//max
	if(max_ < pkg.max_ && pkg.exist_ == true){ //if min is in pkg and exist
		max_ = pkg.max_;
	}
	//avg
	if(exist_ == true){ // si existe, promedio ponderado
		avg_=(avg_*count_ + pkg.avg_*pkg.count_)/(count_+pkg.count_);
	}
	//range
	rg_ = rg_ + pkg.rg_; //union
	//count
	count_+=pkg.count_;
}
Package& Package::merge(const Package& pkg1,const Package& pkg2){ // merge 2 pkg in this
	*this = pkg1;
	this->merge(pkg2);
	return *this;
}
//operators
Package& Package::operator+(const Package& pkg){
	this->merge(pkg);
	return *this;
}
Package& Package::operator=(const Package& pkg){
	exist_ = pkg.exist_;
	max_ = pkg.max_;
	min_ = pkg.min_;
	avg_ = pkg.avg_;
	count_ = pkg.count_;
	rg_ =  pkg.rg_;
	return *this;
}
//stream operators
std::ostream & operator<< (std::ostream& os,const Package& pkg){
	os << pkg.rg_ << ',';
	if(!pkg.exist_){
		os << "NoData";
	}
	else{
		os << pkg.min_ << ',' << pkg.max_ << ',' << pkg.avg_ << ',' << pkg.count_; 
	}
	os << endl;
	return os;
}
std::istream & operator >> (std::istream& is,Package& Package){
	cout << " istream no implementado";
	return is;
}