/*
Title:		ElementWrapper Class
Purpose:	Simplifying usage of pointers and dynamic memory
Author:		Dominik Szaci³owski
Version:	1.1 03/04/2019
*/

#pragma once
#include <stdexcept>
#include <utility>
#include <memory>
#include <iostream>


template<class Type>
class ElementWrapper {
public:
	//Creates clear, empty Wrapper (empty Wrapper means that it is not wrapping any pointer(even nullptr)) 
	ElementWrapper();
	//Creates Wrapper with dynamic allocated memory and value equal to given 
	ElementWrapper(const Type& value);
	//Creates Wrapper looking exacly like given and increases counter of Wrappers with same pointer by 1
	ElementWrapper(const ElementWrapper& element);
	//Creates Wrapper to given pointer
	//It is important that adress can not be already used by other Wrapper
	ElementWrapper(Type* const adress);
	//Before destroying itself, decreases counter by 1 and if adress is not used, releases memory
	~ElementWrapper();

	//Dereference wrapped pointer, throws exceptions when Wrapper is empty or pointer equals null
	Type operator*() const;
	//Sets Wrapper's value on given one but with new pointer to a dynamic allocated memory
	//also releases previously taken memory if neccessary
	Type& operator=(const Type& value);
	//Sets Wrapper's parameters on parameters from given Wrapper
	//also releases previously taken memory if neccessary
	ElementWrapper<Type>& operator=(const ElementWrapper& element);
	//Returns true if parameters of Wrapper are the same as from given one,
	//Empty Wrappers can never be equal
	bool operator==(const ElementWrapper& element) const;
	//Gives access to object member
	//throws exceptions if Wrapper is empty or pointer equals nullptr
	Type* operator->() const;
	//Returns Wrapped pointer
	//throws exception if Wrapper is empty 
	Type* getAdress() const;
	//Returns number of Wrappers with the same Wrapped pointer
	//throws exception if Wrapper is empty
	unsigned int count() const;
	//Swaps all parameters with other Wrapper
	//does not change value of counter or Wrapped pointer
	void swap(ElementWrapper& element);
	//Makes Wrapper empty
	//also releases previously taken memory if neccessary 
	void reset();
	//Sets Wrapper on new adress in memory
	//also releases previously taken memory if neccessary
	//It is important that adress can not be already used by other Wrapper
	void reset(Type* const adress);
	//Checks if it is the only Wrapper using this pointer
	//Empty Wrapper can never be unique
	bool isUnique() const;

private:
	class Pointer;
	Pointer* pointer;
};
#include "ElementWrapper.hpp"