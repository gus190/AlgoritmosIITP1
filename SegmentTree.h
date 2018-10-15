#ifndef _SEGMENTTREE_H_INCLUDED_
#define _SEGMENTTREE_H_INCLUDED_

#include <cstdlib>
#include <iostream>
#include <Range.h>
#include <Package.h>
#include <Array.h>

using namespace std;

class SegmentTree{
public:
	//constructors/destructors
	SegmentTree(); // empty
	SegmentTree(const SegmentTree&); //copy
	SegmentTree(const Array<Package>&); //from array of elements
	~SegmentTree();
	
	//getters
	size_t size()const;
	bool exist()const;
	
	//setters
	
	//metods
	void clear();//clear
	void createST(const Array<Package>&); //create st from array
	
	//operators
	Package& operator=(const SegmentTree&); //asignation
	Package& operator+(const SegmentTree&); //avg of leaf values and reconstruct of st
	
	//stream operators
	friend std::ostream& operator<<(std::ostream&,const SegmentTree&);
	friend std::istream& operator>>(std::istream&,SegmentTree&);
private:	
	bool exist_;
	Array<Package> st_;
	size_t size_,height_,nodes_;
};

#endif
