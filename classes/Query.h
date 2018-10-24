#ifndef _QUERY_H_INCLUDED_
#define _QUERY_H_INCLUDED_
#include <sstream>
#include <iostream>
#include <classes/Query.h>
#include <classes/SensorNet.h>
#include <classes/Range.h>
#include <classes/Package.h>

using namespace std;

class Query{
	Range rg_;
	string name_;
	
public:
	Query();
	~Query();
	
	// Getters
	string name()const;
	Range range()const;
	size_t min()const;
	size_t max()const;
	
	// Setters
	void name(const string&);
	void range(const size_t&,const size_t&);
	void range(const Range&);
	void min(const size_t&);
	void max(const size_t&);

	
	// Metods
	void clear();
	void process(istream&,SensorNet&,ostream&);
	
	// Native operators

};

#endif
