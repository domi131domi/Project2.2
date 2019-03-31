#pragma once
#include <stdexcept>

template<class Type>
class ElementWrapper {
public:
	ElementWrapper();
	ElementWrapper(ElementWrapper &element);
	ElementWrapper(Type* pointer);
	ElementWrapper(const Type& value);
	~ElementWrapper();

	Type operator*() const;
	Type& operator= (const Type& value);
private:
	class Pointer;
	Pointer* pointer;
};



//konstruktory i funkcje kopiujace/przypisania zwiekszaja licznik
//desktruktor cofa licznik, jesli licznik == 0 to usuwa wskaznik
//f: =,getTypename,getValue, getPointer(*dereferencja), googletest, wyjatki ale nie do pamieci
//testy jednostkowe
//czy obsluga bledow