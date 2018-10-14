#include <cstdlib>
#include <iostream>
#include<range.h>

using namespace std;

//-- Constructors / Destructor --
Range::Range(){ 
//empty constructor
	min_ = 0;
	max_ = 0;
	empty_ = true;
}
Range::Range(const Range& range){ 
// copy constructor
	min_ = range.min_;
	max_ = range.max_;
	empty_ = range.empty_;
} 
Range::Range(const size_t& min,const size_t& max){ 
// range constructor
	min_ = min;
	max_ = max;
	if(min_ < max_)
		empty_ = false;
	else
		empty_ = true;
} 
Range::~Range(){ 
// destructor
}

//-- Metods --
void Range::clear(){ 
//clear range
	min_ = 0;
	max_ = 0;
	empty_ = true;
} 
bool Range::empty()const{ 
// is empty?
	return empty_;
}
size_t Range::min()const{ 
// get min
	return min_;
}
size_t Range::max()const{ 
// get max
	return max_;
}
void Range::setRange(const size_t& min,const size_t& max){ 
//set range from min max
	min_ = min;
	max_ = max;
	if(min_ < max_){
		empty_ = false;
	}else{
		empty_ = true;
	}
}
void Range::setMin(const size_t& min){ 
// set min
	min_ = min;
	if(min_ < max_){
		empty_ = false;
	}else{
		empty_ = true;
	}
}
void Range::setMax(const size_t& max){ 
// set max
	max_ = max;
	if(min_ < max_){
		empty_ = false;
	}else{
		empty_ = true;
	}
}

bool Range::isInside(const Range& range)const{ 
//A inside B?
	if(min_ >= range.min_ && min_ < range.max_)
		if(max_ <= range.max_ && max_ > range.min_)
			return true;
	return false;
}
bool Range::intersects(const Range& range){ 
//A intersects B?
	if(min_ < range.max_ || max_ > range.min_)
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
	if(min_ == range.min_ && max_ == range.min_ && empty_ == range.empty()){
		return true;
	}
	return false;
} 
bool Range::operator!=(const Range& range)const{
	if (*this == range)
		return false;
	return true;
}  
Range& Range::operator=(const Range& range){
	min_ = range.min_;
	max_ = range.max_;
	empty_ = range.empty_;
	return *this;
}  
Range& Range::operator+(const Range& range){
	if(range.min_ < min_){
		min_ = range.min_;
	}
	if(range.max_ > max_){
		max_ = range.max_;
	}
	return *this;
}  
Range& Range::operator-(const Range& range){
	if(range.min_ > min_ && range.min_ <= max_){
		min_ = range.min_;
	}
	if(range.max_ < max_ && range.max_ >= min_){
		max_ = range.max_;
	}
	if(min_ < max_){
		
		empty_ = false;
	}
	else
		this->clear();
		empty_ = true;
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
