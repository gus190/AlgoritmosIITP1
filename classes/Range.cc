#include <cstdlib>
#include <iostream>
#include <classes/range.h>

using namespace std;

//-- Constructors / Destructor --
Range::Range(){ 
	// Empty
	min_ = 0;
	max_ = 0;
	empty_ = true;
}
Range::Range(const Range& range){ 
	// Copy
	min_ = range.min_;
	max_ = range.max_;
	empty_ = range.empty_;
} 
Range::Range(const size_t& min,const size_t& max){ 
	// Complete
	min_ = min;
	max_ = max;
	if(min_ < max_)
		empty_ = false;
	else
		empty_ = true;
} 
Range::~Range(){ 
	// Destructor
}

//-- Metods --
void Range::clear(){ 
	// Clear range
	min_ = 0;
	max_ = 0;
	empty_ = true;
} 
bool Range::empty()const{ 
	// Is empty?
	return empty_;
}
size_t Range::min()const{ 
	// Get min
	return min_;
}
size_t Range::max()const{ 
	// Get max
	return max_;
}
void Range::setRange(const size_t& min,const size_t& max){ 
	// Set range from min max
	min_ = min;
	max_ = max;
	if(min_ < max_){
		empty_ = false;
	}else{
		empty_ = true;
	}
}
void Range::setMin(const size_t& min){ 
	// Set min
	min_ = min;
	if(min_ < max_){
		empty_ = false;
	}else{
		empty_ = true;
	}
}
void Range::setMax(const size_t& max){ 
	// Set max
	max_ = max;
	if(min_ < max_){
		empty_ = false;
	}else{
		empty_ = true;
	}
}

bool Range::isInside(const Range& range)const{ 
	// A inside B?
	if(min_ >= range.min_ && min_ < range.max_)
		if(max_ <= range.max_ && max_ > range.min_)
			return true;
	return false;
}
bool Range::intersects(const Range& range){ 
	// A intersects B?
	if(min_ >= range.max_)
		return false;
	if(max_ <= range.min_)
		return false;
	if(min_ < range.max_ && min_ >= range.min_)
		return true;
	if(max_ > range.min_ && max_ <= range.max_)
		return true;
	return false;
}

Range& Range::intersection(const Range& range){
	// A intersection B
	if(min_ <= range.min_)
		min_ = range.min_;
	if(max_ >= range.max_)
		max_ = range.max_;
	if(min_ < max_)
		empty_ = false;
	else
		empty_ = true;
	return *this;
}
//-- Native Operators --
bool Range::operator==(const Range& range)const{
	// Bool equal
	if(min_ == range.min_ && max_ == range.min_ && empty_ == range.empty()){
		return true;
	}
	return false;
} 
bool Range::operator!=(const Range& range)const{
	// Bool not equal
	if (*this == range)
		return false;
	return true;
}  
Range& Range::operator=(const Range& range){
	// Assignation
	min_ = range.min_;
	max_ = range.max_;
	empty_ = range.empty_;
	return *this;
}  
Range& Range::operator+(const Range& range){
	// Add (union)
	if(range.min_ < min_){
		min_ = range.min_;
	}
	if(range.max_ > max_){
		max_ = range.max_;
	}
	return *this;
}  
 
//-- Stream operators -- 
std::ostream& operator<<(std::ostream& os,const Range& range){
	if(range.empty() == true){
		os << "Empty";
	}else{
		os << '[' << range.min_ << ',' << range.max_ << ')';
	}
	return os;
}
std::istream& operator>>(std::istream& is,Range& range){
	char ch;
	if( is >> ch && ch == '[' && is >> range.min_ 
	  &&  is >> ch && ch == ',' && is >> range.max_
	  && is >> ch && ch == ')'){
		
	}else{
		range.clear();
		cout << "Bad range parse." << endl;
	}
	return is;
}
