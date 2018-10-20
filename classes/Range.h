#ifndef RANGE_H_INCLUDED_
#define RANGE_H_INCLUDED_

#include <cstdlib>
#include <iostream>

using namespace std;

class Range{
public:
	// Constructors / Destructor
	Range(); // Empty
	Range(const size_t&,const size_t&); // Complete
	Range(const Range&); // Copy
	~Range(); // Destructor
	
	// Getters
	bool empty()const;
	size_t min()const;
	size_t max()const;
	
	// Setters
	void range(const size_t&,const size_t&);
	void min(const size_t&);
	void max(const size_t&);
	
	// Native Operators
	bool operator==(const Range&)const;  // A == B
	bool operator!=(const Range&)const;  // A != B
	Range& operator=(const Range&); // Asignation
	Range& operator+(const Range&); // Union 
	
	// Metods
	void clear();
	bool isInside(const Range&)const;	// A inside B ?
	bool intersects(const Range&);		// A intesects B?
	
	// Stream Operators
	friend std::ostream& operator<<(std::ostream&,const Range&);
	friend std::istream& operator>>(std::istream&,Range&);
	
private:
	size_t min_; // min range
	size_t max_; // max range
	bool empty_; // bool exist
};


#endif