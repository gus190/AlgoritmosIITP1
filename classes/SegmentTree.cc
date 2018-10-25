#include <iostream>
#include <cstdlib>
#include <cmath>
#include <classes/SegmentTree.h>

//-- Constructors / Destructor -- 
SegmentTree::SegmentTree(){ 
	leaves_ = 0;
	samples_ = 0;
	nodes_ = 0;
	height_= 0;
	exist_ = false;
}
SegmentTree::SegmentTree(const SegmentTree& st):st_(st.st_){ 
	// Copy
	exist_ = st.exist_;
	leaves_ = st.leaves_;
	nodes_ = st.nodes_;
	height_ = st.height_;
}

SegmentTree::~SegmentTree(){
	// Destructor
}

//-- Getters --
size_t SegmentTree::size()const{
	return leaves_;
}
size_t SegmentTree::nodes()const{
	return nodes_;
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
	leaves_=0;
	height_=0;
	nodes_=0;
}
bool SegmentTree::haveChild(const size_t& node)const{
	// Check if node have children
	// If index 2*n+2 is in the array, then he have childs
	if(2*node+2 < st_.size()){ 
		return true;
	}else{
		return false;
	}
}
size_t SegmentTree::lChild(const size_t& node)const{
	// Return index of 1st child
	return 2*node+1;
}
size_t SegmentTree::rChild(const size_t& node)const{
	// Return index of 2nd child
	return 2*node+2;
}
void SegmentTree::expand(){
	Array<Package> arr;
	
	// Load samples into auxiliary array
	for(int i=0;i<samples_;i++){
		arr.push_back(st_[nodes_-samples_+i]);
	}
	
	// Set new sizes
	height_++; //height of the tree
	leaves_ = (size_t)(pow(2,height_));	// Total size of the tree
	nodes_ = 2*leaves_-1;		// Number of nodes
	
	// Create new st array
	Array<Package> st(nodes_);
	// Load samples (leaves)
	for(size_t i = 0; i<arr.size(); i++){ // Copy the array in the right location
		st[nodes_-leaves_+i] = arr[i];
	}
	for(size_t i = arr.size();i<leaves_;i++){ // Fill the final empty elements of array with their range
		st[nodes_-leaves_+i].range(i,i+1);
	}
	st_ = st;
	return;
}
Package& SegmentTree::build(const size_t& node){ 
	// Create the tree from the leafs
	// Recursive build, call until element with no childs,return node
	if(haveChild(node)){
		st_[node] = build(lChild(node));
		st_[node] + build(rChild(node)); // Merge childs in father
	}
	return st_[node];
}

void SegmentTree::build(){
	if(st_.size() != 0)
		this->build(0);
	return;
}

Package& SegmentTree::leaf(const size_t& leafIndex){
	// Return sample (leaf)
	return st_[nodes_ - leaves_ + leafIndex];
}
void SegmentTree::printLeaves(std::ostream& os){
	// Print samples (leaves)
	for(int i = nodes_-leaves_;i<nodes_;i++){
		os << st_[i] << ',';
	}
}

//-- Operators --
SegmentTree& SegmentTree::operator=(const SegmentTree& st){
	exist_ = st.exist_;
	height_ = st.height_;
	nodes_ = st.nodes_;
	st_ = st.st_;
	return *this;
}
SegmentTree& SegmentTree::operator+(const Package& data){
	// Push to segment tree
	if(leaves_ == 0){ // First time
		st_.push_back(data);
		nodes_++;
		leaves_++;
		samples_++;
		exist_ = true;
		return *this;
	}else if(leaves_ == samples_){ // If leaves = samples (no more free space in st)
		this->expand(); // Expand the tree
	}
	st_[nodes_-leaves_+samples_] = data;	// Put data in place
	samples_++;		//  Incerment samples size
	return *this;
}
Package& SegmentTree::operator[](const size_t& i){
	// Go to node
	return st_[i];
}
// -- Stream operators -- 
std::ostream & operator<< (std::ostream& os,const SegmentTree& st){
	// Print full segment tree
	if(st.exist_ == false){
		os << "empty st" << endl;
	}else{
		os << st.st_ << endl;
	}
	return os;
}
