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
	
	// load samples into auxiliary array
	for(int i=0;i<samples_;i++){
		arr.push_back(st_[nodes_-samples_+i]);
	}
	
	//set new sizes
	height_++; //height of the tree
	leaves_ = (size_t)(pow(2,height_));	// total size of the tree
	nodes_ = 2*leaves_-1;		//number of nodes
	
	//create new st array
	Array<Package> st(nodes_);
	// Load samples (leaves)
	for(size_t i = 0; i<arr.size(); i++){ // copy the array in the right location
		st[nodes_-leaves_+i] = arr[i];
	}
	for(size_t i = arr.size();i<leaves_;i++){ // fill the final empty elements of array with their range
		st[nodes_-leaves_+i].range(i,i+1);
	}
	st_ = st;
	this->build(0); //rebuild tree
	return;
}
Package& SegmentTree::build(const size_t& node){ 
	// Create the tree from the leafs
	// Recursive build, call until element with no childs,return node
	if(haveChild(node)){
		st_[node] = build(lChild(node));
		st_[node] + build(rChild(node)); // merge childs in father
	}
	return st_[node];
}
void SegmentTree::build(){
	// build st
	
	// Create auxiliary array with samples
	Array<Package> arr;
	
	for(int i=0;i<samples_;i++){
		arr.push_back(st_[nodes_-samples_+i]);
	}
	
	// Build tree from auxiliary array
	if (arr.size() == 0){ 
		exist_ = false;
		return;
	}
	
	exist_ = true;
	
	// Set variables
	height_++; //height of the tree
	leaves_ = (size_t)(pow(2,height_));	// total size of the tree
	nodes_ = 2*leaves_-1;		//number of nodes

	// Create the array for the st
	Array<Package> aux(nodes_); 
	st_ = aux;
	
	// Load array in last part of st
	for(size_t i = 0; i<arr.size(); i++){ // copy the array in the right location
		st_[nodes_-leaves_+i] = arr[i];
	}
	for(size_t i = arr.size();i<leaves_;i++){ // fill the final empty elements of array with their range
		st_[nodes_-leaves_+i].range(i,i+1);
	}
	
	// Build all the tree
	this->build(0);
}

Package& SegmentTree::leaf(const size_t& leafIndex){
	return st_[nodes_ - leaves_ + leafIndex];
}
void SegmentTree::printLeaves(std::ostream& os){
	// print leaves
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
	//push to segment tree
	if(leaves_ == 0){ //first time
		st_.push_back(data);
		nodes_++;
		leaves_++;
		exist_ = true;
		return *this;
	}else if(leaves_ == samples_){ //if leaves = samples (no more free space in st)
		this->expand();
	}
	st_[nodes_-leaves_+samples_] = data;	// put data in place
	samples_++;		//  incerment samples size
	this->build(0);	// rebuild the parents
	return *this;
}
Package& SegmentTree::operator[](const size_t& i){
	return st_[i];
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
