#include "ElementWrapper.h"


template<class Type>
ElementWrapper<Type>::ElementWrapper() : pointer(nullptr) {
}

template<class Type>
ElementWrapper<Type>::ElementWrapper(ElementWrapper &element) : pointer(element.pointer) {
	if (element.pointer != nullptr)
		++element.pointer->counter;
}

template<class Type>
ElementWrapper<Type>::ElementWrapper(Type* pointer) {
	
}

template<class Type>
ElementWrapper<Type>::ElementWrapper(const Type& value) {
	pointer = new Pointer;
	pointer->adress = new Type;
	*(pointer->adress) = value;
	pointer->counter = 1;
}

template<class Type>
ElementWrapper<Type>::~ElementWrapper() {
	if (pointer != nullptr)
		if (--(pointer->counter) == 0) {
			delete pointer->adress;
			delete pointer;
		}
}

template<class Type>
Type ElementWrapper<Type>::operator*() const {
	if (pointer == nullptr)
		throw std::invalid_argument("Can not dereference nullptr");
	return *(pointer->adress);
}

template<class Type>
Type& ElementWrapper<Type>::operator=(const Type& value) {
	if (pointer != nullptr)
		if (--(pointer->counter) == 0) {
			delete pointer->adress;
			delete pointer;
		}
	pointer = new Pointer;
	pointer->adress = new Type;
	*(pointer->adress) = value;
	pointer->counter = 1;
	return *(pointer->adress);
}

template<class Type>
class ElementWrapper<Type>::Pointer {
public:
	Type* adress;
	unsigned int counter = 0;
};