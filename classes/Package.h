#ifndef _PACKAGE_H_INCLUDED_
#define _PACKAGE_H_INCLUDED_

#include <cstdlib>
#include <iostream>
#include <classes/Range.h>

using namespace std;

class Package{
public:
	// Constructors / Destructors
	Package(); // Empty
	Package(const Package&); // Copy
	Package(const double &max, const double &min ,const double &avg,const size_t &count, const Range &rg); // Complete
	Package(const Package&,const Package&); // For parent, analog to merge 2 pkg
	Package(const double &data,const Range& rg); // For the leafs, data and index
	~Package();
	
	// Getters
	double min() const;
	double max() const;
	double avg() const;
	Range range() const;
	size_t count() const;
	bool exist() const;
	
	// Setters
	void min(const double&);
	void max(const double&);
	void avg(const double&);
	void range(const size_t&,const size_t&);
	void range(const Range&);
	void count(const size_t&);
	void set(const Range&,const double&); // Range and data with count 1;
	void set(const size_t&,const size_t&,const double&); // Range and data with count 1;
	void exist(const bool&);
	
	// Metods
	void clear();// Clear package
	Package& merge(const Package&); // Merge 
	Package& merge(const Package&,const Package&); // Merge 2 pkg in this
	
	// Native operators
	Package& operator+(const Package&); // Merge
	Package& operator=(const Package&); // Asignation
	
	// Stream operators
	friend std::ostream& operator<<(std::ostream&,const Package&);
	friend std::istream& operator>>(std::istream&,Package&);
	
private:	
	bool exist_;
	Range rg_;
	double max_,min_,avg_;
	size_t count_;
};

#endif
