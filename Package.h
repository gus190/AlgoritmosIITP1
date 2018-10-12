#ifndef _PACKAGE_H_INCLUDED_
#define _PACKAGE_H_INCLUDED_

#include <cstdlib>
#include <iostream>
//#include <string>
#include <array.h>

using namespace std;

class Package {
public:
	Package();
	Package(const Package&); //construcor copia
	Package(const double &max, const double &min ,const double &avg,const size_t &count, const Range &rg); //constructor completo
	Package(const double &max, const double &min ,const double &avg, const Range &rg); //constructor completo sin count
	Package(const double &max, const double &min ,const double &avg,const sizet &count, const sizet &minrg, const sizet &maxrg);
	Package(const Range &rg); //Por si creo primero la clase y despues cargo los datos
	Package(const double &data,const Range &rg); //Para las hojas
	Package(const double &data, const sizet &minrg, const sizet &maxrg);
	Package(const Package&,const Package&); //para crear un padre
	~Package();
	
	double min() const;
	double max() const;
	double avg() const;
	Range rg() const;
	size_t count() const;
	void clear();//No existe todo en cero
	bool exist() const;
	void setExist(bool &exist);
	Package& merge(const Package&);
	Package& merge(const Package&,const Package&);
	
	void querry(ostream&,size_t,size_t);
    

	Package& operator+(const Package&);//A partir de dos hijos me crea el padre
	Package& operator=(const Package&);
	
	friend std::ostream& operator<<(std::ostream&,const Package&);
	//friend std::istream& operator>>(std::istream&,Sensor&);

private:	
	bool exist_;
	Range rg_;
	double max_,min_,avg_;
	size_t count_;
};

#endif
