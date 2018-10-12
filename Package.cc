#include <iostream>
#include <cstdlib>
//#include <cmath>
//#include <cstring>
#include <Package.h>
//constructores
#define INFPOS 1000000
#define INFNEG -1000000
Package::Package():rg_(){
	exist_ = false;
	max_ = INFNEG;
	min_ = INFPOS;
	avg_ = 0;
	count_ = 0;
}	
Package::Package(const Package& pkg){
	exist_ = pkg.exist_;
	max_ = pkg.max_;
	min_ = pkg.min_;
	avg_ = pkg.avg_;
	count_ = pkg.count_;
	rg_ =  pkg.rg_;

}

Package::Package(const double &max, const double &min ,const double &avg,const size_t &count, const Range &rg)
				:rg_(rg){

	exist_ = true;
	max_ = max;
	min_ = min;
	avg_ = avg;
	count_ = count;
} //constructor completo

Package::Package(const double &max, const double &min ,const double &avg, const Range &rg)
				:rg_(rg){

	exist_ = true ;
	max_ = max;
	min_ = min;
	avg_ = avg;
}//constructor completo sin count


Package::Package(const double &max, const double &min ,const double &avg,const sizet &count, const sizet &minrg, const sizet &maxrg)
				:rg_(minrg,maxrg){

	exist_ = true;
	max_ = max;
	min_ = min;
	avg_ = av;
	count_ = count;
}
Package::Package(const Range &rg):rg_(rg){
	exist_ = false;
	max_ = INFNEG;
	min_ = INFPOS;
	avg_ = 0;
	count_ = 0;
}
Package::Package(const double &data,const Range &rg):rg_(rg){
	exist_ = true;
	max_ = data;
	min_ = data;
	avg_ = data;
	count_ = 1;
} //Para las hojas

Package::Package(const double &data, const sizet &minrg, const sizet &maxrg):rg_(minrg,maxrg){
	exist_ = true;
	max_ = data;
	min_ = data;
	avg_ = data;
	count_ = 1;
} //Para las hojas
		

Package::Package(const Package &pkg1,const Package &pkg2)
				:rg_(pkg1.rg_.min(),pkg2.rg_.max()){
	exist_ = true;
	min_=pkg1.min_;
	max_=pkg1.max_;
	avg_=(pkg1.avg_ * pkg1.count_+pkg2.avg_*pkg2.count_)/(pkg2.count_+pkg1.count_)=;

	if(pkg1.max_ < pkg2.max_){
		max_= pkg2.max_;
	}

	if(pkg1.min_ > pkg2.min_){
		min_= pkg2.min_;
	}

	count_=pkg2.count_+pkg1.count_;
	} //para crear un padre

//destructor
Package::~Package(){
}

double Package::min() const{
	return min_;
}

double Package::max() const{
	return max_;
}

double Package::avg() const{
	return avg_;
}

Range Package::rg() const{
	return rg_;
}

size_t Package::count() const{
	return count_;
}

void Package::clear(){
	rg_.clear();
	min_=0;
	max_=0;
	exist_=false;
	avg_=0;
	count_=0;
}//No existe todo en cero

bool Package::exist() const{
	return exist_;

}

void Package::setExist(bool &exist){
	exist_=exist;
}

Package& Package::merge(const Package &pkg){
	count_=pkg.count_+(*this).count_;
	//Si count = 0 significa que es *this tampoco tiene datos por lo tanto es un false en
	// todos y es lo que queda almacenado
	if(count_ != 0){
		exist_=true;
		avg_=((*this).avg_ * (*this).count_+pkg.avg_*pkg.count_)/(pkg.count_+(*this).count_)=;

		if((*this).max_ < pkg.max_){
			max_= pkg.max_;
		}

		if((*this).min_ > pkg.min_){
			min_= pkg.min_;
		}
		
		rg_((*this).rg_.min(),pkg.rg_.max())
		
	}
	
		
}

Package& Package::merge(const Package&,const Package&){

}
	

Package& Package::operator+(const Package &pkg){
	
	if(exist_ && pkg.exist_){
		*this.merge(pkg)

	}


pkg=pkg1+pkg2


}//Sumar dos aquetes y crear un paquete padre

Package& Package::operator=(const Package&){
	exist_ = pkg.exist_;
	max_ = pkg.max_;
	min_ = pkg.min_;
	avg_ = pkg.avg_;
	count_ = pkg.count_;
	rg_ =  pkg.rg_;
	return *this;
}





//obtener un valor de dataeratura
double Package::getData(int pos){
	return data[pos];
}
//obtener el nombre
const string& Package::getID()const{
	return ID;
}

size_t Package::size()const{
	return data.size();
}

void Package::clear(){
	data.clear();
	ID.clear();
}

void Package::querry(ostream& output,size_t minRange,size_t maxRange){
	double avg = 0,min = 0,max = 0;
	int count = 0;
	if(minRange > maxRange){
		output << "BAD QUERRY" << endl;
		return;
	}
	if(minRange > data.size()){
		output << "NO DATA" << endl;
		return;
	}
	if(maxRange > data.size()-1){
		maxRange = data.size();
	}
	min = max = data[minRange]; //inicializo los min y max
	for(size_t i = minRange; i<=maxRange-1;i++){
		if(data[i] < min){
			min = data[i];
		}else{
			if(data[i] > max){
				max = data[i];
			}
		}
		avg+=data[i];
		count++;
	}
	avg = avg/count;
	output << avg << ',' << min << ',' << max << ',' << count << endl;
}

std::ostream & operator<< (std::ostream& os,const Package& Package){

	os << "Package ID: " << Package.getID() << endl;
	os << "Dato:" << endl;
	os << Package.data << endl;
	os << "Cantidad de datos: " << Package.size() << endl;
	return os;
}

Package& Package::operator+(const double value){
	data.push_back(value);
	return *this;
}
Package& Package::operator+(const Package& s){
	data.push_back(s.data);
	return *this;
}

Package& Package::operator=(const string& name){
	ID = name;
	return *this;
}

Package& Package::operator=(const Package& s){
	ID = s.ID;
	data = s.data;
	return *this;
}

bool Package :: operator==(const Package& s){
	return s.ID==ID;
}

std::istream & operator >> (std::istream& is,Package& Package){
	cout << " istream no implementado";
	return is;
}