#include <gtest/gtest.h>
#include "../Project2.2/ElementWrapper.h"
#include"../Project2.2/ElementWrapper.cpp"
#include <stdexcept>

TEST(Operator, Equal) {
	ElementWrapper<int> element = 2;
	EXPECT_EQ(*element, 2);
	element = 3;
	EXPECT_EQ(*element, 3);
}

TEST(Operator, Dereference) {
	ElementWrapper<int> element;
	EXPECT_THROW(*element, std::invalid_argument);
	element = 4;
	EXPECT_EQ(*element, 4);
}

TEST(Constructor, Blank) {
	//ElementWrapper<float> element();
	//EXPECT_EQ(typeid(float))
}