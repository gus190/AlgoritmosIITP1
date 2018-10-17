#ifndef _SEGMENTTREE_H_INCLUDED_
#define _SEGMENTTREE_H_INCLUDED_

#include <cstdlib>
#include <iostream>
#include <classes/Range.h>
#include <classes/Package.h>
#include <classes/Array.h>

using namespace std;

class SegmentTree{
public:
	// Constructors / Destructor
	SegmentTree(); // Empty
	SegmentTree(const SegmentTree&); // Copy
	SegmentTree(const Array<Package>&); // From array of elements
	~SegmentTree(); // Destructor 
	
	// Getters
	size_t size()const;
	size_t nodes()const;
	bool exist()const;
	
	// Setters
	
	// Metods
	void clear();//clear
	Package& build(const size_t&); //create all parent nodes
	bool haveChild(const size_t&)const;
	size_t firstChild(const size_t&)const;
	size_t secondChild(const size_t&)const;

	// Native operators
	SegmentTree& operator=(const SegmentTree&); //asignation
	
	// Stream operators
	friend std::ostream& operator<<(std::ostream&,const SegmentTree&);
	friend std::istream& operator>>(std::istream&,SegmentTree&);

	private:	
	bool exist_;
	Array<Package> st_;
	size_t lSize_,height_,nSize_; //leaves size, height of the tree, nodes size(total size)
};

#endif
