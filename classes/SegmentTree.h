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
	void expand(); // expand the tree
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
	bool haveChild(const size_t&)const; // Ask if have children
	size_t lChild(const size_t&)const; // Index of 1st child
	size_t rChild(const size_t&)const; // Index of 2nd child
	
	Package& build(const size_t&); // Create all parent nodes (recursive)
	void build(); // Build tree
	
	Package& leaf(const size_t&); // Return leaf 
	void printLeaves(std::ostream&); // Print leaves
	
	// Native operators
	SegmentTree& operator=(const SegmentTree&); // Asignation
	SegmentTree& operator+(const Package&); // Push to array
	Package& operator[](const size_t&); // Return node
	
	// Stream operators
	friend std::ostream& operator<<(std::ostream&,const SegmentTree&); // Print full array st
};

#endif
