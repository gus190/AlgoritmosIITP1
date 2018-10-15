#include <iostream>
#include <cstdlib>
#include <cmath>
#include <SegmentTree.h>
#include <Package.h>
#include <Range.h>
#include <Array.h>

//constructors
SegmentTree::SegmentTree(){ // empty
	exist_ = false;
}
SegmentTree::SegmentTree(const SegmentTree& st):st_(st.st_){ // copy
	exist_ = st.exist_;
	size_ = st.size_;
	nodes_ = st.nodes_;
	height_ = st.height_;
}
SegmentTree::SegmentTree(const Array<Package>& arr){ // from array
	
}
SegmentTree::~SegmentTree(){
}
//getters
size_t SegmentTree::size()const{
	return size_;
}
bool SegmentTree::exist()const{
	return exist_;
}
//setters
void SegmentTree::min(const double& data){
	min_ = data;
}
void SegmentTree::max(const double& data){
	max_ = data;
}
void SegmentTree::avg(const double& data){
	avg_ = data;
}
void SegmentTree::range(const Range& data){
	rg_ = data;
}
void SegmentTree::range(const size_t& minrg,const size_t& maxrg){
	rg_.setRange(minrg,maxrg);
}
void SegmentTree::count(const size_t& data){
	count_ = data;
}
void SegmentTree::exist(const bool& data){
	exist_ = data;
}
void SegmentTree::clear(){
	st_.clear();
	exist_=false;
	size_=0;
	height_=0;
	nodes_=0;
}
//metods
SegmentTree& SegmentTree::create(const Array<Package>& arr){ //create st from array
	Array<Package> aux;
	if (arr.size() == 0){
		exist_ = false;
		return;
	}
	height_ = (size_t)(ceil(log2(arr.size())));
	size_ = (size_t)(pow(2,height_));
	nodes_ = 2*size_-1;
	
	
}
SegmentTree& SegmentTree::merge(const SegmentTree& st1,const SegmentTree& st2){ // merge 2 st in this
	*this = st1;
	this->merge(st2);
	return *this;
}
//operators
SegmentTree& SegmentTree::operator+(const SegmentTree& st){
	this->merge(st);
	return *this;
}
SegmentTree& SegmentTree::operator=(const SegmentTree& st){
	exist_ = st.exist_;
	max_ = st.max_;
	min_ = st.min_;
	avg_ = st.avg_;
	count_ = st.count_;
	rg_ =  st.rg_;
	return *this;
}
//stream operators
std::ostream & operator<< (std::ostream& os,const SegmentTree& st){
	os << st.rg_ << ',';
	if(!st.exist_){
		os << "NoData";
	}
	else{
		os << st.min_ << ',' << st.max_ << ',' << st.avg_ << ',' << st.count_; 
	}
	os << endl;
	return os;
}
std::istream & operator >> (std::istream& is,SegmentTree& SegmentTree){
	cout << " istream no implementado";
	return is;
}