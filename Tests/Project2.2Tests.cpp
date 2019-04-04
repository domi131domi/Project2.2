/*
Title:		ElementWrapper Tests
Purpose:	Testing ElementWrapper class with GoogleTests
Author:		Dominik Szaci³owski
Version:	1.1 03/04/2019
*/
#include <gtest/gtest.h>
#include "../Project2.2/ElementWrapper.h"
#include <stdexcept>
#include <vld.h>

TEST(Constructor, Blank) {
	ElementWrapper<float> element;
	EXPECT_THROW(*element, std::invalid_argument);
	EXPECT_THROW(element.getAdress(), std::invalid_argument);
}
 
TEST(Constructor, Value) {
	ElementWrapper<int> element(3);
	EXPECT_EQ(*element, 3);
	EXPECT_EQ(typeid(*element), typeid(int));
	ElementWrapper<int> element2(NULL);
	EXPECT_EQ(*element2, NULL);
}

TEST(Constructor, Copy) {
	ElementWrapper<float> element = 3.f;
	ElementWrapper<float> element2(element);
	EXPECT_EQ(*element2, *element);
	EXPECT_EQ(element.getAdress(), element2.getAdress());
}

TEST(Constructor, Pointer) {
	int* pointer = new int;
	ElementWrapper<int> element(pointer);
	EXPECT_EQ(element.getAdress(), pointer);
	ElementWrapper<int> element2(nullptr);
	EXPECT_EQ(element2.getAdress(), nullptr);
}

TEST(Destructor, Blank) {
	{
		ElementWrapper<int> element(3);
		{
			ElementWrapper<int> element2(element);
			EXPECT_EQ(element2.count(), 2);
		}
		EXPECT_EQ(element.count(), 1);
	}
}

TEST(Operator, Dereference) {
	ElementWrapper<int> element;
	EXPECT_THROW(*element, std::invalid_argument);
	ElementWrapper<int> element2(nullptr);
	EXPECT_THROW(*element2, std::invalid_argument);
	element = 4;
	EXPECT_EQ(*element, 4);
}

TEST(Operator, EqualValue) {
	ElementWrapper<int> element;
	element = 2;
	EXPECT_EQ(*element, 2);
	element = NULL;
	EXPECT_EQ(*element, NULL);
}

TEST(Operator, EqualElement) {
	ElementWrapper<int> element = 2;
	ElementWrapper<int> element2;
	element2 = element;
	EXPECT_EQ(element.getAdress(), element2.getAdress());
	EXPECT_EQ(element.count(), element2.count());
}

TEST(Operator, DoubleEqual) {
	ElementWrapper<int> element = 1, element2 = 2;
	EXPECT_FALSE(element == element2);
	element = element2;
	EXPECT_TRUE(element == element2);
}

TEST(Operator, MemoryAccess) {
	struct Str { int a = 2; };
	ElementWrapper<Str> element;
	EXPECT_THROW(element->a, std::invalid_argument);
	Str* nptr = nullptr;
	element.reset(nptr);
	EXPECT_THROW(element->a, std::invalid_argument);
	element.reset(new Str);
	EXPECT_EQ(element->a, 2);
}

TEST(Method, getAdress) {
	ElementWrapper<int> element, element2;
	EXPECT_THROW(element.getAdress(), std::invalid_argument);
	element = 2;
	element2 = element;
	EXPECT_EQ(element.getAdress(), element2.getAdress());
}

TEST(Method, count) {
	ElementWrapper<int> element = 1, element2 = 2, element3 = 3;
	EXPECT_EQ(element.count(), 1);
	element2 = element;
	EXPECT_EQ(element.count(), 2);
	element3 = element;
	EXPECT_EQ(element.count(), 3);
}

TEST(Method, swap) {
	ElementWrapper<int> element = 1, element2 = 2;
	EXPECT_EQ(*element, 1);
	EXPECT_EQ(*element2, 2);
	element.swap(element2);
	EXPECT_EQ(*element, 2);
	EXPECT_EQ(*element2, 1);
}

TEST(Method, resetVoid) {
	ElementWrapper<int> element = 1;
	ElementWrapper<int> element2(element);
	element.reset();
	EXPECT_EQ(element2.count(), 1);
}

TEST(Method, resetPointer) {
	ElementWrapper<int> element = 1;
	ElementWrapper<int> element2(element);
	int* ptr = new int;
	element.reset(ptr);
	EXPECT_EQ(element2.count(), 1);
	EXPECT_EQ(element.getAdress(), ptr);
}

TEST(Method, isUnique) {
	ElementWrapper<int> element = 1,element2 = 2;
	EXPECT_TRUE(element.isUnique());
	element = element2;
	EXPECT_FALSE(element.isUnique());
	element.reset();
	EXPECT_FALSE(element.isUnique());
}