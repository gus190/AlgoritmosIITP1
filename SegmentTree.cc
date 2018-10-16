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
	// if arr empty, no st
	if (arr.size() == 0){ 
		exist_ = false;
		return;
	}
	
	//set variables
	height_ = (size_t)(ceil(log2(arr.size()))); //height of the tree
	size_ = (size_t)(pow(2,height_));	// total size of the tree
	nodes_ = 2*size_-1;		//number of nodes
	
	cout << size_ << ',' << nodes_ << ',' << height_ << endl;
	// create the array for the st
	Array<Package> aux(nodes_); 
	st_ = aux;
	
	//load array in last part of array st
	for(size_t i = nodes_-arr.size(); i<nodes_; i++){
		st_[i] = arr[i-nodes_+arr.size()];
	}
	
	//cout << st_;
	
	//build all the tree
	this->build(0);
}
SegmentTree::~SegmentTree(){
}

//getters
size_t SegmentTree::size()const{
	return size_;
}
size_t SegmentTree::nodes()const{
	return nodes_;
}
bool SegmentTree::exist()const{
	return exist_;
}

//setters

//metods
void SegmentTree::clear(){
	st_.clear();
	exist_=false;
	size_=0;
	height_=0;
	nodes_=0;
}

Package& SegmentTree::build(const size_t& node){ //create the tree from the leafs
	if(haveChilds(node)){
		st_[node] = build(2*node+1) + build(2*node+2);
	} else {
		return st_[node];
	}
}

bool SegmentTree::haveChilds(const size_t& node)const{
	if(2*node+2 <= nodes_){ // if index 2*n+2 is in the array
		return true;
	}else{
		return false;
	}
}

//operators
SegmentTree& SegmentTree::operator=(const SegmentTree& st){
	exist_ = st.exist_;
	height_ = st.height_;
	nodes_ = st.nodes_;
	st_ = st.st_;
	return *this;
}

//stream operators
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