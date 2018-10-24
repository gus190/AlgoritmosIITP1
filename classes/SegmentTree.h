#ifndef _SEGMENTTREE_H_INCLUDED_
#define _SEGMENTTREE_H_INCLUDED_

#include <cstdlib>
#include <iostream>
#include <classes/Range.h>
#include <classes/Package.h>
#include <classes/Array.h>

using namespace std;

class SegmentTree{
private:	
	bool exist_;
	Array<Package> st_;
	size_t samples_,leaves_,height_,nodes_; //leaves size, height, nodes size(total size)
	
public:
	// Constructors / Destructor
	SegmentTree(); // Empty
	SegmentTree(const SegmentTree&); // Copy
	~SegmentTree(); // Destructor 
	
	// Getters
	size_t size()const;
	size_t nodes()const;
	bool exist()const;
	
	// Setters
	
	// Metods
	void clear(); //clear
	
	bool haveChild(const size_t&)const; // ask if have children
	size_t lChild(const size_t&)const; // index of 1st child
	size_t rChild(const size_t&)const; // index of 2nd child
	
	Package& build(const size_t&); //create all parent nodes (recursive)
	
	void build(); //build st from scratch with the leaves added
	
	Package& leaf(const size_t&); //return leaf (can be done as operator[])
	
	void printLeaves(std::ostream&); // print leaves
	// Native operators
	SegmentTree& operator=(const SegmentTree&); //asignation
	SegmentTree& operator+(const Package&); //push to array
	Package& operator[](const size_t&); //push to array
	
	// Stream operators
	friend std::ostream& operator<<(std::ostream&,const SegmentTree&);


};

#endif
