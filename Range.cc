#include <cstdlib>
#include <iostream>
#include<range.h>

using namespace std;

//Constructores y destructor
Range::Range(){
	min_ = 0;
	max_ = 0;
	empty_ = true;
}
Range::Range(const Range& range){
	min_ = range.min_;
	max_ = range.min_;
	empty_ = range.empty_;
} 
Range::Range(const size_t& min,const size_t& max){
	min_ = min;
	max_ = max;
	if(min_ < max_)
		empty_ = false;
	else
		empty_ = true;
} 
Range::~Range(){
}

//metodos
void Range::clear(){
	min_ = 0;
	max_ = 0;
	empty_ = true;
} 
bool Range::empty()const{
	return empty_;
}
size_t Range::min()const{
	return min_;
}
size_t Range::max()const{
	return max_;
}
void Range::setRange(const size_t& min,const size_t& max){
	min_ = min;
	max_ = max;
	if(min_ < max_)
		empty_ = false;
	else
		empty_ = true;
}
void Range::setMin(const size_t& min){
	min_ = min;
	if(min_ < max_)
		empty_ = false;
	else
		empty_ = true;
}
void Range::setMax(const size_t& max){
	max_ = max;
	if(min_ < max_)
		empty_ = false;
	else
		empty_ = true;
}

	bool Range::isInside(const Range& range)const{
		// [min_,max_)  is inside [range.min_,range.max) ?
		if(min_ >= range.min_ && min_ < range.max_)
			if(max_ <= range.max_ && max_ > range.min_)
				return true;
		return false;
	}
	bool Range::intersects(const Range& range){
		// [min_,max_)  intersects [range.min_,range.max) ?
		if(min_ < range.max_ || max_ > range.min_)
			return true;
		return false;
	}
	
	Range& Range::intersection(const Range& range){
		// [min_,max_) n [range.min_,range.max)
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
	Range& Range::symDifference(const Range&){
		
	}
//Operaciones nativas
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

std::ostream& operator<<(std::ostream& os,const Range& range){
	if(range.empty() == false){
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
