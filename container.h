//#ifndef CONTAINER_H
//#define CONTAINER_H
//#endif
#pragma once
#include <vector>
#include "rectangle.h"




template <class type = int>
class Container
{
private:
	unsigned limit;  //maxymalna pojemnosc bufora
	int position; //indeks aktualnej pozycji bufora
	std::vector<Rect<type>> buf; //wektor bedacy buforem

public:
	Container(int lim = 4) : limit(lim) {}//konstruktor


	Container& operator += (const Rect<type> &rect);
	Rect<type>& operator [] (int n) { return buf[n]; }
	Container& add(const Rect<type> &rect);
	Container& remove(int n) { buf.erase(buf.begin() + n); return *this; }
	Container& resize(unsigned lim);


	template<class U>
	friend std::ostream& operator<<(std::ostream& str, const Container<U> rect);



	Rect<type> border() const;
	int size() { return buf.size(); }
	int max() { return limit; }






};
//*************************IMPLEMENTATION

template <class type>
Container<type>& Container<type>::operator +=(const Rect<type>& rect)
{
	if (buf.size() < limit)
	{
		buf.push_back(rect);

	}

	else
	{
		buf[position] = rect; // z buf.begin() + position?
		++position;
		position %= limit;
	}

	return *this;
}

template <class type>
Container<type>& Container<type>::add(const Rect<type>& rect)
{
	if (buf.size() < limit)
	{
		buf.push_back(rect);

	}

	else
	{
		buf[position] = rect;
		++position;
		position %= limit;
	}

	return *this;
}


template<class type>
Container<type>& Container<type>::resize(unsigned lim)
{
	limit = lim;
	if (lim < buf.size())
	{
		buf.resize(lim); //usuwamy nadmiarowe prostokaty
	}
	return *this;
}

template<class type>
Rect<type> Container<type>::border() const//zwraca maxa ze wszystkich moze zmienic na wydajniejsza funkcje?
{
	Rect<type> border;
	for (unsigned i = 0; i < buf.size(); i++)
	{
		border += buf[i];
	}
	return border;
}
























template<class type>
inline std::ostream & operator<<(std::ostream & str, const Container<type> cont)
{
	for (unsigned i = 0; i <cont.buf.size(); i++)
	{
		str << i+1 << ". " << cont.buf[i] << std::endl;
	}
	return str;
}
