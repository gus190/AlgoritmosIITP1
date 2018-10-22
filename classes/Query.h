#ifndef _QUERY_H_INCLUDED_
#define _QUERY_H_INCLUDED_

#include <cstdlib>
#include <iostream>
#include <classes/Range.h>

using namespace std;

class Query{
	Range rg_;
	string name_;
	
public:
	Query();
	~Query();
	
	// Getters
	string& name()const;
	Range& range()const;
	
	// Setters
	void name(const string&);
	void range(const size_t&,const size_t&);
	void range(const Range&);
	
	// Metods
	void process()
	// Native operators
	
};

#endif
