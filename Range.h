// doubleemplate de arreglo dinamico

#ifndef DAdoubleA_H
#define DAdoubleA_H

#include <cstdlib>
#include <iostream>

using namespace std;

class Range{
public:
	Range();
	Range(const size_t&,const size_t&); 
	Range(const Range&); 
	~Range();
	
	void clear();
	bool empty()const;
	size_t min()const;
	size_t max()const;
	void setRange(const size_t&,const size_t&);
	void setMin(const size_t&);
	void setMax(const size_t&);
	
	bool operator==(const Range&)const;  // A == B
	bool operator!=(const Range&)const;  // A != B
	
	Range& operator=(const Range&); // asignation
	Range& operator+(const Range&); // union 
	Range& operator-(const Range&); // diference
	
	bool isInside(const Range&)const;	// check if A c= B
	bool intersects(const Range&);		// check if A n B != empty
	
	Range& intersection(const Range&);	// intersection
	Range& symDifference(const Range&);	// symetric diference
	
	friend std::ostream& operator<<(std::ostream&,const Range&);
	friend std::istream& operator>>(std::istream&,Range&);
	
private:
	size_t min_;
	size_t max_;
	bool empty_;
};


#endif