#include <iostream>
#include <cstdlib>
#include <cmath>
#include <classes/SegmentTree.h>

//-- Constructors / Destructor -- 
SegmentTree::SegmentTree(){ 
	// Empty
	exist_ = false;
}
SegmentTree::SegmentTree(const SegmentTree& st):st_(st.st_){ 
	// Copy
	exist_ = st.exist_;
	lSize_ = st.lSize_;
	nSize_ = st.nSize_;
	height_ = st.height_;
}
SegmentTree::SegmentTree(const Array<Package>& arr){ 
	// From array
	if (arr.size() == 0){ 
		exist_ = false;
		return;
	}
	exist_ = true;
	
	// Set variables
	height_ = (size_t)(ceil(log2(arr.size()))); //height of the tree
	lSize_ = (size_t)(pow(2,height_));	// total size of the tree
	nSize_ = 2*lSize_-1;		//number of nodes
	
	// Create the array for the st
	Array<Package> aux(nSize_); 
	st_ = aux;
	
	// Load array in last part of st
	for(size_t i = 0; i<arr.size(); i++){ // copy the array in the right location
		st_[i+nSize_-lSize_] = arr[i];
	}
	for(size_t i = arr.size();i<st_.size();i++){ // fill the final empty elements of array with their range
		st_[i+nSize_-lSize_].range(i,i+1);
	}
	
	// Build all the tree
	this->build(0);
}
SegmentTree::~SegmentTree(){
	// Destructor
}

//-- Getters --
size_t SegmentTree::size()const{
	return lSize_;
}
size_t SegmentTree::nodes()const{
	return nSize_;
}
bool SegmentTree::exist()const{
	return exist_;
}

//-- Setters --

// -- Metods -- 
void SegmentTree::clear(){
	// Clear
	st_.clear();
	exist_=false;
	lSize_=0;
	height_=0;
	nSize_=0;
}
Package& SegmentTree::build(const size_t& node){ 
	// Create the tree from the leafs
	// Recursive build, call until element with no childs,return node
	if(haveChild(node)){
		st_[node] = build(firstChild(node));
		st_[node] + build(secondChild(node)); // merge childs in father
	}
	return st_[node];
}
bool SegmentTree::haveChild(const size_t& node)const{
	// Check if node have children
	// If index 2*n+2 is in the array, then he have childs
	if(2*node+2 <= nSize_){ 
		return true;
	}else{
		return false;
	}
}
size_t SegmentTree::firstChild(const size_t& node)const{
	// Return index of 1st child
	return 2*node+1;
}
size_t SegmentTree::secondChild(const size_t& node)const{
	// Return index of 2nd child
	return 2*node+2;
}

//-- Operators --
SegmentTree& SegmentTree::operator=(const SegmentTree& st){
	exist_ = st.exist_;
	height_ = st.height_;
	nSize_ = st.nSize_;
	st_ = st.st_;
	return *this;
}

// -- Stream operators -- 
std::ostream & operator<< (std::ostream& os,const SegmentTree& st){
	if(st.exist_ == false){
		os << "empty st" << endl;
	}else{
		os << st.st_ << endl;
	}
	return os;
}

std::istream & operator >> (std::istream& is,SegmentTree& SegmentTree){
	cout << " istream no implementado";
	return is;
}