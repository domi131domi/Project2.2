#include "ElementWrapper.h"

template<class Type>
ElementWrapper<Type>::ElementWrapper() : pointer(nullptr) {
}

template<class Type>
ElementWrapper<Type>::ElementWrapper(const Type& value) {
	pointer = new Pointer;
	pointer->adress = new Type;
	*(pointer->adress) = value;
	pointer->counter = 1;
}

template<class Type>
ElementWrapper<Type>::ElementWrapper(const ElementWrapper& element) : pointer(element.pointer) {
	if (element.pointer != nullptr)
		++element.pointer->counter;
}

template<class Type>
ElementWrapper<Type>::ElementWrapper(Type* const adress) {
	pointer = new Pointer;
	pointer->adress = adress;
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
		throw std::invalid_argument("Pointer does not storage an adress");
	else if(pointer->adress == nullptr)
		throw std::invalid_argument("Can not dereference nullptr");
	else
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
ElementWrapper<Type>& ElementWrapper<Type>::operator=(const ElementWrapper& element) {
	if (pointer != nullptr)
		if (--(pointer->counter) == 0) {
			delete pointer->adress;
			delete pointer;
		}
	pointer = element.pointer;
	if (element.pointer != nullptr)
		++(element.pointer->counter);
	return *this;
}

template<class Type>
bool ElementWrapper<Type>::operator==(const ElementWrapper& element) const {
	if (pointer != nullptr && pointer == element.pointer)
		return true;
	return false;
}

template<class Type>
Type* ElementWrapper<Type>::operator->() const {
	if (pointer == nullptr)
		throw std::invalid_argument("Pointer does not storage an adress");
	else if (pointer->adress == nullptr)
		throw std::invalid_argument("Pointer does storage nullptr. Use getAdress instead");
	else
		return pointer->adress;
}

template<class Type>
Type* ElementWrapper<Type>::getAdress() const {
	if (pointer == nullptr)
		throw std::invalid_argument("Pointer does not storage an adress");
	else
		return pointer->adress;
}

template<class Type>
unsigned int ElementWrapper<Type>::count() const {
	if (pointer == nullptr)
		throw std::invalid_argument("Pointer does not storage an adress");
	else
		return pointer->counter;
}

template<class Type>
void ElementWrapper<Type>::swap(ElementWrapper& element) {
	std::swap(pointer, element.pointer);
}

template<class Type>
void ElementWrapper<Type>::reset() {
	if(pointer != nullptr)
		if (--(pointer->counter) == 0) {
			delete pointer->adress;
			delete pointer;
		}
	pointer = nullptr;
}

template<class Type>
void ElementWrapper<Type>::reset(Type* const adress) {
	if (pointer != nullptr)
		if (--(pointer->counter) == 0) {
			delete pointer->adress;
			delete pointer;
		}
	pointer = new Pointer;
	pointer->adress = adress;
}

template<class Type>
bool ElementWrapper<Type>::isUnique() const {
	if (pointer != nullptr && pointer->counter == 1)
		return true;
	return false;
}

template<class Type>
class ElementWrapper<Type>::Pointer {
public:
	Type* adress = nullptr;
	unsigned int counter = 0;
};