#ifndef _PACKAGE_H_INCLUDED_
#define _PACKAGE_H_INCLUDED_

#include <cstdlib>
#include <iostream>
#include <Range.h>
#include <Package.h>

using namespace std;

class Package{
public:
	//constructors/destructors
	Package(); // empty
	Package(const Package&); //copy
	Package(const double &max, const double &min ,const double &avg,const size_t &count, const Range &rg); //complete
	Package(const Package&,const Package&); //for parent, analog to merge 2 pkg
	Package(const double &data,const Range& rg); //for the leafs, data and index
	~Package();
	//getters
	double min() const;
	double max() const;
	double avg() const;
	Range range() const;
	size_t count() const;
	bool exist() const;
	//setters
	void min(const double&);
	void max(const double&);
	void avg(const double&);
	void range(const size_t&,const size_t&);
	void range(const Range&);
	void count(const size_t&);
	void exist(const bool&);
	//metods
	void clear();//clear data and exist tfalse
	Package& merge(const Package&);
	Package& merge(const Package&,const Package&);
	//operators
	Package& operator+(const Package&); //merge
	Package& operator=(const Package&); //asignation
	//stream operators
	friend std::ostream& operator<<(std::ostream&,const Package&);
	friend std::istream& operator>>(std::istream&,Package&);
private:	
	bool exist_;
	Range rg_;
	double max_,min_,avg_;
	size_t count_;
};

#endif
