// Template de arreglo dinamico

#ifndef ARRAYDIN_H
#define ARRAYDIN_H

#include <cassert>
#include <cstdlib>
#include <iostream>
//#include <sstream>
//#include <stdio.h>
using namespace std;

#define ARRAY_DEFAULT_SIZE 4
#define ARRAY_GROWTH_RATE 2

template <typename T>
class Array
{
public:
	Array();
	Array(size_t n); 
	Array( const Array<T> & ); 
	~Array( ); 
	
	size_t	size( ) const; 
	void push_back(const T&);
	void push_back(const Array&);
	int linear_search(T&);
	void clear();
	
	Array<T>& operator=( const Array<T> & ); 
	bool operator==( const Array<T> & ) const; 
	bool operator!=( const Array<T> & ) const; 
	T& operator[ ]( int );
	
	const T& operator[ ]( int ) const;
	template <typename TT>
	friend std::ostream& operator<<(std::ostream&,const Array<TT>&);
	template <typename TT>
	friend std::istream& operator>>(std::istream&,Array<TT>&);

private:
	size_t allocSize; 
	size_t usedSize;
	T *p = NULL; 
	void resize(size_t);
};

template <typename T> 
Array<T>::Array()
{
	allocSize = ARRAY_DEFAULT_SIZE;
	usedSize = 0;
	p = new T[allocSize];

	//cout << "Array created empty. " <<  endl;
}

template <typename T> 
Array<T>::Array(size_t n)
{
	allocSize = n;
	usedSize = n;
	p = new T[allocSize];

	//cout << "Array created n" <<  endl;
}

template <typename T> 
Array<T>::Array( const Array<T> &arr )
{
	usedSize = arr.usedSize;
	allocSize = arr.allocSize;
	p = new T[ allocSize ];
	for ( size_t i = 0; i < usedSize; i++ )
		p[ i ] = arr.p[ i ]; 
	//cout << "Array created. Copy " <<  endl;
	
}


template <typename T> 
Array<T>::~Array()
{
	//cout << "Array deleted. Size = " << usedSize << endl;
	if (p)
		delete[] p;
}

template <typename T> 
size_t Array<T>::size() const {
	return usedSize; 
}

template <typename T> 
Array<T>& Array<T>::operator=(const Array<T> &rValue){
	T* aux;
	if (&rValue == this){
		return *this;
	}
	// Después, cambiamos el tamaño del arreglo si es necesario y procedemos a copiar
	if ( allocSize != rValue.allocSize ){
		aux = new T[rValue.allocSize]; 
		delete [] p; 
		p = aux;
		allocSize = rValue.allocSize; 
		usedSize = rValue.usedSize;
	}
	usedSize = rValue.usedSize;
	for (size_t i=0;i<usedSize;i++)
		p[i] = rValue.p[i]; 
	return *this;
}
template <typename T> 
bool Array<T>::operator==( const Array<T> &rValue ) const{
	// Primero reviso si tienen igual tamaño. Si no, no pueden ser iguales.
	// Luego reviso miembro a miembro si estos son iguales.
	// Requiere que la clase tenga el operador !=

	if ( usedSize != rValue.usedSize )
		return false; 
	else{
		for (size_t i=0;i<usedSize;i++){
			if (p[i] != rValue.p[i])
       			return false; 
		}
	}
    return true; 
}

template <typename T> 
bool Array<T>::operator != (const Array<T> &rValue)const{
	// Si no son iguales son distintos
	if (rValue == *this)
		return false;
	return true;
}

template <typename T> 
T & Array<T>::operator [ ]( int pos )
{
	// Utilizamos assert para saber si se puede acceder al elemento.
	//assert( (0 < pos) || (pos < usedSize) ) ; 
	return p[pos]; 
}

template <typename T> 
const T & Array<T>::operator [ ]( int pos ) const
{
	// La diferencia acá es que tiene los operadores de const.
	// Es necesario si se llama desde dentro de una función que es const
	// El compilador se dará cuenta de cual usar

	//assert( (0 < pos) || (pos < usedSize) ) ; 
	return p[pos]; 
}

template <typename T> 
void Array<T>::clear()
{
	delete[] p;
	allocSize = ARRAY_DEFAULT_SIZE;
	usedSize = 0;
	p = new T[allocSize];
}

template <typename T> 
void Array<T>::resize(size_t new_size)
{
	// Redimensiono el arreglo, y copio todo hasta donde puedo.
	T *aux;

	aux = new T[new_size];
	if( new_size < usedSize ){
		usedSize = new_size;
	}
	for(size_t i=0;i<usedSize;++i){
		aux[i] = p[i];
	}
	delete [] p;
	p = aux;
	allocSize = new_size;
}

template <typename T> 
void Array<T>::push_back(const T& value)
{
	if(allocSize == usedSize){
		this->resize(allocSize*ARRAY_GROWTH_RATE);
	}	
	p[usedSize] = value;
	usedSize++;
}


template <typename T> 
void Array<T>::push_back(const Array& value)
{
	for(size_t i=0; i<value.size();i++){
		this->push_back(value[i]);
	}
}


template <typename T> 
std::ostream & operator<< (std::ostream& os,const Array<T> & arr)
{
	// Escribe el arreglo en el formato (T1,T2,T3 ... Tn)
	// Se asume que existe el operador << para la clase T
	
	if( arr.size() == 0 ){
		os << "()";
		return os;
	}
	os << "(";

	for(size_t i=0; i<arr.size()-1; ++i){
		os << arr[i] << ",";
	}
	os << arr[arr.size()-1];
	os << ")";
	return os;
}

template <typename T>
std::istream & operator>> (std::istream& is,Array<T>& arr)
{
	// Limpio el arreglo y leo en formato (T1,T2,...,Tn) de is. Si no se hace conforme a lo
	// esperado, limpio el arreglo (devuelvo uno sin elementos)
	// Si llega a EOF, marcará en el istream

	T aux = 0;
	char ch = 0;

	arr.clear();
	if( (is >> ch) && (ch == '(') && (is >> aux) ){
		arr.push_back(aux);
		while( (is >> ch) && (ch == ',') && (is >> aux) ){
			arr.push_back(aux);
		}
	} 
	if ( ch != ')' ){
		arr.clear();
	}

	return is;
}

template <typename T>
int Array<T>::linear_search(T& objective)
{
	// Devuelve la posición del objeto encontrado o -1 si no lo encontró

	if(this->size()==0)
		return -1;
	for(size_t i=0;i<this->size();++i){
		if((*this)[i] == objective)
			return i;
	}
	return -1;
}

#endif
